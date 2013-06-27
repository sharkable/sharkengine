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
  SoundType *Init(AAssetManager *asset_manager, SLEngineItf sl_engine_itf, SLDataSink sl_data_sink,
                  std::string filename);
  void Play(float volume, float position);

 private:
  void AddSoundInstance(SoundInstanceNode **node);

  SoundInstanceNode *sound_instance_list_head_;

  // OpenSL ES objects
  SLEngineItf sl_engine_itf_;
  SLDataSink sl_data_sink_;
  SLDataLocator_AndroidFD sl_data_locator_;
  SLDataFormat_MIME sl_format_mime_;
  SLDataSource sl_audio_source_;
};

#endif
