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

int x, y;

int width, height, width2, height2, rowbytes;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void read_png_file(char *file_name) {
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
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    abort_("[read_png_file] png_create_read_struct failed");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    abort_("[read_png_file] png_create_info_struct failed");
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    abort_("[read_png_file] Error during init_io");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGB_ALPHA) {
	abort_("[read_png_file] PNG %s must be RGB or RGBA", file_name);    	
  }
  if (bit_depth != 8) {
	abort_("[read_png_file] PNG %s must be 8 bits per channel", file_name);
  }
  if (color_type == PNG_COLOR_TYPE_RGB) {
	png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);
  }

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    abort_("[read_png_file] Error during read_image");
  }

  row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);

  rowbytes = width * 4;
  for (y = 0; y < height; y++) {
    row_pointers[y] = (png_byte *) malloc(rowbytes);
  }

  png_read_image(png_ptr, row_pointers);
  fclose(fp);
}

void write_txtr_file(char *file_name) {
  int y, x;

  FILE *fp = fopen(file_name, "wb");

  width2 = 1;
  while (width2 < width) {
	width2 *= 2;
  }
  height2 = 1;
  while (height2 < height) {
	height2 *= 2;
  }

  fwrite(&width, sizeof(int), 1, fp);
  fwrite(&height, sizeof(int), 1, fp);
  fwrite(&width2, sizeof(int), 1, fp);
  fwrite(&height2, sizeof(int), 1, fp);

  png_byte zero = 0;
  for (y = 0; y < height; y++) {
    fwrite(row_pointers[y], sizeof(png_byte), width * 4, fp);
	for (x = width * 4; x < width2 * 4; x++) {
	  fwrite(&zero, sizeof(png_byte), 1, fp);
	}
  }
  for (y = height; y < height2; y++) {
	for (x = 0; x < width2 * 4; x++) {
	  fwrite(&zero, sizeof(png_byte), 1, fp);
	}
  }

  fclose(fp);
}

int main(int argc, char **argv) {
  int i;

  if (argc < 2) {
    abort_("Usage: png2tx <file_in>");
  }

  for (i = 1; i < argc; i++) {
    read_png_file(argv[i]);
    int len = strlen(argv[i]);
    argv[i][len - 3] = 't';
    argv[i][len - 2] = 'x';
    argv[i][len - 1] = '\0';
    write_txtr_file(argv[i]);
  }

  return 0;
}
