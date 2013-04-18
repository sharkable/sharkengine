//
//  ResourceLoader.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2012-04-29.
//  Copyright 2012 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

#include "gameengine/opengl/texture2D.h"

#include "libzip/zip.h"
#include "app.h"

using std::string;

Texture2D ResourceLoader::Texture(string name) {
  name += "_iphone@2x";
  string high_res_name = name;

  string filename = "assets/textures/" + name + ".tx";

  zip_file *fp = zip_fopen(APKArchive, filename.c_str(), 0);
  if (!fp) {
    s_log("No high res file for %s", filename.c_str());
  }

  // TODO move this reading logic to pure C++ code.
  uint16_t image_width, image_height;
  zip_fread(fp, &image_width, sizeof(uint16_t));
  zip_fread(fp, &image_height, sizeof(uint16_t));

  s_log("reading texture: %s  %d %d", filename.c_str(), image_width, image_height);

  uint16_t texture_width = 1;
  uint16_t texture_height = 1;
  while (texture_width < image_width) {
    texture_width *= 2;
  }
  while (texture_height < image_height) {
    texture_height *= 2;
  }
  unsigned char *data = (unsigned char *)malloc(sizeof(char) * 4 * texture_width * texture_height);
  unsigned char *write_point = data;
  uint16_t diff_width_size = (texture_width - image_width) * 4;
  for (int y = 0; y < image_height; y++) {
    zip_fread(fp, write_point, sizeof(char) * 4 * image_width);
    write_point += 4 * image_width;
    memset(write_point, 0, diff_width_size);
    write_point += diff_width_size;
  }
  memset(write_point, 0, texture_width * (texture_height - image_height) * 4);

  ScreenSize image_size = screen_size_make(image_width, image_height);
  Texture2D texture(data, kTexture2DPixelFormat_RGBA8888, texture_width, texture_height, image_size,
                    name);

  free(data);
  zip_fclose(fp);
  return texture;
}
