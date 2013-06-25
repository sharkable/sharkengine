//
//  sound_instance.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "soundengine/sound_instance.h"

void play_callback(SLPlayItf caller, void *pContext, SLuint32 event) {
  assert(event == SL_PLAYEVENT_HEADATEND);
  ((SoundInstance *)pContext)->Stop();
}

SoundInstance::SoundInstance(SLEngineItf engine_engine, SLDataSource audioSrc, SLDataSink data_sink) {
  is_busy_ = false;

  SLresult result;

  // create audio player
  const SLInterfaceID ids_rename_this[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
  const SLboolean req_rename_this[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
  fdPlayerObject = NULL;
  result = (*engine_engine)->CreateAudioPlayer(engine_engine, &fdPlayerObject, &audioSrc, &data_sink,
          3, ids_rename_this, req_rename_this);
        s_log("RESULT: %d", result);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // realize the player
  result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // get the play interface
  result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  (*fdPlayerPlay)->RegisterCallback(fdPlayerPlay, play_callback, this);

  result = (*fdPlayerPlay)->SetCallbackEventsMask(fdPlayerPlay, SL_PLAYEVENT_HEADATEND);  
  assert(SL_RESULT_SUCCESS == result);
  (void)result;

  // get the volume interface
  result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
}

void SoundInstance::Play(float volume, float position) {
  assert(!is_busy_);
  is_busy_ = true;

  SLresult result;
  result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
  assert(SL_RESULT_SUCCESS == result);
}

void SoundInstance::Stop() {
  SLresult result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_STOPPED);
  assert(SL_RESULT_SUCCESS == result);
  is_busy_ = false;
}
