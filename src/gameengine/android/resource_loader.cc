//
//  ResourceLoader.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2012-04-29.
//  Copyright 2012 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

#include "gameengine/opengl/texture2D.h"

using std::string;

Texture2D ResourceLoader::Texture(string name) {
  name += "_iphone@2x";
  string high_res_name = name;

  NSString *filename =
      [[NSBundle mainBundle] pathForResource:TypeUtil::string2NSString(high_res_name) ofType:@"tx"];

  FILE *fp = fopen(filename.UTF8String, "rb");
  if (!fp) {
    std::cout << "No high res file for " << name << std::endl;
    filename = [[NSBundle mainBundle] pathForResource:TypeUtil::string2NSString(name) ofType:@"tx"];
    fp = fopen(filename.UTF8String, "rb");
  }

  // TODO move this reading logic to pure C++ code.
  uint16_t image_width, image_height;
  fread(&image_width, sizeof(uint16_t), 1, fp);
  fread(&image_height, sizeof(uint16_t), 1, fp);
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
    fread(write_point, sizeof(char), 4 * image_width, fp);
    write_point += 4 * image_width;
    memset(write_point, 0, diff_width_size);
    write_point += diff_width_size;
  }
  memset(write_point, 0, texture_width * (texture_height - image_height) * 4);

  ScreenSize image_size = screen_size_make(image_width, image_height);
  Texture2D texture(data, kTexture2DPixelFormat_RGBA8888, texture_width, texture_height, image_size,
                    name);

  free(data);
  fclose(fp);
  return texture;
}
