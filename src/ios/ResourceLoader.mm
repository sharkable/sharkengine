//
//  ResourceLoader.mm
//  AirHockey
//
//  Created by Jon Sharkey on 4/29/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

#import <UIKit/UIKit.h>

#include "ios/TypeUtil.h"
#include "opengl/texture2D.h"

Texture2D ResourceLoader::Texture(string name) {
  if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
    name += "_iphone";
  }
  string high_res_name = name;
  if ([UIScreen mainScreen].scale == 2) {
    high_res_name += "@2x";
  }

  NSString *filename =
      [[NSBundle mainBundle] pathForResource:TypeUtil::string2NSString(high_res_name) ofType:@"tx"];
  FILE *fp = fopen(filename.UTF8String, "rb");
  if (!fp) {
    cout << "No high res file for " << name << endl;
    filename = [[NSBundle mainBundle] pathForResource:TypeUtil::string2NSString(name) ofType:@"tx"];
    fp = fopen(filename.UTF8String, "rb");
  }

  // TODO move this reading logic to pure C++ code.
  int real_width, real_height;
  int width, height;
  fread(&real_width, sizeof(int), 1, fp);
  fread(&real_height, sizeof(int), 1, fp);
  fread(&width, sizeof(int), 1, fp);
  fread(&height, sizeof(int), 1, fp);

  void *data = malloc(sizeof(char) * 4 * width * height);
  fread(data, sizeof(char), 4 * width * height, fp);

  ScreenSize imageSize = screen_size_make(real_width, real_height);
  Texture2D texture(data, kTexture2DPixelFormat_RGBA8888, width, height, imageSize, name);

  free(data);
  fclose(fp);
  return texture;
}
