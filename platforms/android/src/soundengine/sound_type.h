//
//  sound_type.h
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SOUNDENGINE_SOUNDTYPE_H
#define SOUNDENGINE_SOUNDTYPE_H

#include <android/asset_manager.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

struct SoundInstanceNode;

class SoundType {
 public:
  SoundType(AAssetManager *asset_manager, SLEngineItf engine_engine, SLDataSink data_sink, std::string filename);
  void Play(float volume, float position);

 private:
  SLDataSink data_sink_;
  SLDataLocator_AndroidFD loc_fd;
  SLDataFormat_MIME format_mime;
  SLDataSource audioSrc;
  SoundInstanceNode *sound_instance_list_head_;
};

#endif
