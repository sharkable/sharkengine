//
//  platform.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-10-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef GAMEENGINE_PLATFORMTYPES_H_
#define GAMEENGINE_PLATFORMTYPES_H_

class Platform {
 public:
  typedef enum {
    kScreenSizeGroupPhone = 0,
    kScreenSizeGroupTablet,
    kScreenSizeGroupPC
  } ScreenSizeGroup;

  typedef enum {
    kOSGroupIOS = 0,
    kOSGroupOSX,
    kOSGroupAndroid
  } OSGroup;

  typedef enum {
    kInputGroupTouchScreen = 0,
    kInputGroupPC
  } InputGroup;

  typedef enum {
    kTextureGroupIPhone35cmLowRes = 0,
    kTextureGroupIPhone35cmHighRes,
    kTextureGroupIPhone40cmHighRes,
    kTextureGroupIPadLowRes,
    kTextureGroupIPadHighRes,
    kTextureGroupAndroidLowRes,
    kTextureGroupAndroidHighRes,
    kTextureGroupPCHighRes,
    kTextureGroupPCUltraHighRes
  } TextureGroup;

  ScreenSizeGroup screen_size_group() { return screen_size_group_; }
  void set_screen_size_group(ScreenSizeGroup group) { screen_size_group_ = group; }

  OSGroup os_group() { return os_group_; }
  void set_os_group(OSGroup group) { os_group_ = group; }

  InputGroup input_group() { return input_group_; }
  void set_input_group(InputGroup group) { input_group_ = group; }

  TextureGroup texture_group() { return texture_group_; }
  void set_texture_group(TextureGroup group) { texture_group_ = group; }

 private:
  ScreenSizeGroup screen_size_group_;
  OSGroup os_group_;
  InputGroup input_group_;
  TextureGroup texture_group_;
};

#endif
