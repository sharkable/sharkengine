/*
 * Copyright 2013 - Sharkable Inc.
 */

#include <png.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

void abort_(const char * s, ...) {
  va_list args;
  va_start(args, s);
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
  abort();
}

struct PNG {
  unsigned short width;
  unsigned short height;
  png_bytep *row_pointers;
};

struct PNG read_png_file(char *file_name) {
  unsigned char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE *fp = fopen(file_name, "rb");
  if (!fp) {
    abort_("[read_png_file] File %s could not be opened for reading", file_name);
  }
  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
  }

  /* initialize stuff */
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    abort_("[read_png_file] png_create_read_struct failed");
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    abort_("[read_png_file] png_create_info_struct failed");
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    abort_("[read_png_file] Error during init_io");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  struct PNG png; 
  png.width = png_get_image_width(png_ptr, info_ptr);
  png.height = png_get_image_height(png_ptr, info_ptr);
  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGB_ALPHA) {
    abort_("[read_png_file] PNG %s must be RGB or RGBA", file_name);      
  }
  if (bit_depth != 8) {
    abort_("[read_png_file] PNG %s must be 8 bits per channel", file_name);
  }
  if (color_type == PNG_COLOR_TYPE_RGB) {
    png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);
  }

  png_read_update_info(png_ptr, info_ptr);

  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    abort_("[read_png_file] Error during read_image");
  }

  png.row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * png.height);

  int row_size = png.width * 4;
  int y;
  for (y = 0; y < png.height; y++) {
    png.row_pointers[y] = (png_byte *)malloc(row_size);
  }

  png_read_image(png_ptr, png.row_pointers);
  png_read_end(png_ptr, NULL);
  png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
  fclose(fp);

  return png;
}

void free_data(struct PNG png) {
  int y;
  for (y = 0; y < png.height; y++) {
    free(png.row_pointers[y]);
  }
  free(png.row_pointers);
}

void write_tx_file(struct PNG png, char *file_name) {
  FILE *fp = fopen(file_name, "wb");

  fwrite(&png.width, sizeof(unsigned short), 1, fp);
  fwrite(&png.height, sizeof(unsigned short), 1, fp);

  int y;
  for (y = 0; y < png.height; y++) {
    fwrite(png.row_pointers[y], sizeof(png_byte), png.width * 4, fp);
  }

  fclose(fp);
}

int main(int argc, char **argv) {
  if (argc < 2 || argc > 3) {
    abort_("Usage: png2tx file_in [file_out]");
  }

  struct PNG png = read_png_file(argv[1]);
  char *output_filename;
  if (argc == 3) {
    output_filename = argv[2];
  } else {
    output_filename = argv[1];
    int len = strlen(output_filename);
    output_filename[len - 3] = 't';
    output_filename[len - 2] = 'x';
    output_filename[len - 1] = '\0';
  }
  write_tx_file(png, output_filename);
  free_data(png);

  return 0;
}
