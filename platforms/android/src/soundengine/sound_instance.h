//
//  sound_instance.h
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SOUNDENGINE_SOUNDINSTANCE_H
#define SOUNDENGINE_SOUNDINSTANCE_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class SoundInstance {
 public:
  SoundInstance(SLEngineItf engine_engine, SLDataSource audioSrc, SLDataSink data_sink);
  void Play(float volume, float position);
  void Stop();

  bool is_busy() { return is_busy_; }

 private:
  bool is_busy_;
  // file descriptor player interfaces
  SLObjectItf fdPlayerObject;
  SLPlayItf fdPlayerPlay;
  SLSeekItf fdPlayerSeek;
  SLVolumeItf fdPlayerVolume;
};

#endif
