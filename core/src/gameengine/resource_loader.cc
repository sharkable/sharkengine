//
//  ResourceLoader.m
//  GameEngine
//
//  Created by Jon Sharkey on 2009-09-28.
//  Copyright 2009 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

#include "gameengine/asset_reader.h"
#include "gameengine/game_engine.h"

using std::map;
using std::string;

ResourceLoader::ResourceLoader(GameEngine &game_engine) : game_engine_(game_engine) {
}

Texture2D ResourceLoader::TextureWithName(const std::string &name) {
  if (resource_counter_[name] == 0) {
    Texture2D tex = Texture(name);
    resource_counter_[name]++;
    resources_[name] = tex;
    return tex;
  }

  Texture2D texture = resources_[name];
  resource_counter_[name]++;

  return texture;
}

void ResourceLoader::ReleaseResource(const string &name) {
  int count = resource_counter_[name];
  if (count == 0) {
    return;
  } else if (count == 1) {
    resources_[name].Delete();
    resources_.erase(name);
    resource_counter_.erase(name);
  } else {
    resource_counter_[name] = count - 1;
  }
}

void ResourceLoader::ReleaseResource(Texture2D resource) {
  for (auto i = resources_.begin(); i != resources_.end(); i++) {
    if (i->second.opengl_id() == resource.opengl_id()) {
      ReleaseResource(i->first);
      return;
    }
  }
  assert(false);
}

void ResourceLoader::ReloadTextures() {
  for (auto i = resources_.begin(); i != resources_.end(); i++) {
    resources_[i->first] = Texture(i->first, i->second.opengl_id());
  }
}


#pragma mark - private

Texture2D ResourceLoader::Texture(string name, int opengl_id) {
// TODO think about this
#if __ANDROID__ || TARGET_OS_MAC
  string filename = "assets/textures/" + name;
#else
  string filename = name;
#endif
  if (game_engine_.platform_type() == kPlatformTypePhone ||
      game_engine_.platform_type() == kPlatformTypePC) {
    filename += "_iphone";
  }
  string high_res_filename = filename;
  if (game_engine_.platform_resolution() == kPlatformResolutionHigh) {
    high_res_filename += "@2x";
  }

  high_res_filename += ".tx";
  filename += ".tx";

  AssetReader *asset_reader = game_engine_.LoadAsset(high_res_filename);
  if (!asset_reader->IsOpen()) {
    std::cout << "No high res file for " << name << std::endl;
    delete asset_reader;
    asset_reader = game_engine_.LoadAsset(filename);
    assert(asset_reader->IsOpen());
  }

  uint16_t image_width, image_height;
  asset_reader->Read(&image_width, sizeof(uint16_t), 1);
  asset_reader->Read(&image_height, sizeof(uint16_t), 1);
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
    asset_reader->Read(write_point, sizeof(char), 4 * image_width);
    write_point += 4 * image_width;
    memset(write_point, 0, diff_width_size);
    write_point += diff_width_size;
  }
  memset(write_point, 0, texture_width * (texture_height - image_height) * 4);

  ScreenSize image_size = screen_size_make(image_width, image_height);
  Texture2D texture(data, kTexture2DPixelFormat_RGBA8888, texture_width, texture_height, image_size,
                    name, opengl_id);

  free(data);
  asset_reader->Close();
  delete asset_reader;
  return texture;
}
