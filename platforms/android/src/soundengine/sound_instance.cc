//
//  sound_instance.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "soundengine/sound_instance.h"

#include <math.h>

void play_callback(SLPlayItf sl_caller_itf, void *context, SLuint32 event) {
  assert(event == SL_PLAYEVENT_HEADATEND);
  ((SoundInstance *)context)->Stop();
}

SoundInstance::SoundInstance()
    : is_busy_(false),
      sl_player_object_(NULL),
      sl_play_itf_(NULL),
      sl_volume_itf_(NULL) {
}

SoundInstance::~SoundInstance() {
  (*sl_player_object_)->Destroy(sl_player_object_);
}

SoundInstance *SoundInstance::Init(SLEngineItf sl_engine_itf, SLDataSource sl_audio_source,
                                   SLDataSink sl_data_sink) {
  assert(NULL == sl_player_object_);
  SLresult result;

  // create audio player
  const SLInterfaceID interface_ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
  const SLboolean interfaces_required[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
  result = (*sl_engine_itf)->CreateAudioPlayer(sl_engine_itf, &sl_player_object_, &sl_audio_source,
                                               &sl_data_sink, 3, interface_ids,
                                               interfaces_required);
  assert(SL_RESULT_SUCCESS == result);

  // realize the player
  result = (*sl_player_object_)->Realize(sl_player_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);

  // get the play interface
  result = (*sl_player_object_)->GetInterface(sl_player_object_, SL_IID_PLAY, &sl_play_itf_);
  assert(SL_RESULT_SUCCESS == result);

  // get the volume interface
  result = (*sl_player_object_)->GetInterface(sl_player_object_, SL_IID_VOLUME, &sl_volume_itf_);
  assert(SL_RESULT_SUCCESS == result);

  // register a callback
  result = (*sl_play_itf_)->SetCallbackEventsMask(sl_play_itf_, SL_PLAYEVENT_HEADATEND);
  assert(SL_RESULT_SUCCESS == result);
  (*sl_play_itf_)->RegisterCallback(sl_play_itf_, play_callback, this);

  // enable position
  (*sl_volume_itf_)->EnableStereoPosition(sl_volume_itf_, true);

  return this;
}

void SoundInstance::Play(float volume, float position) {
  assert(NULL != sl_player_object_);
  assert(!is_busy_);

  if (volume <= 0) {
    return;
  }

  (*sl_volume_itf_)->SetVolumeLevel(sl_volume_itf_, 1500.0f * log(volume));
  is_busy_ = true;

  SLresult result = (*sl_play_itf_)->SetPlayState(sl_play_itf_, SL_PLAYSTATE_PLAYING);
  assert(SL_RESULT_SUCCESS == result);
}

void SoundInstance::Stop() {
  assert(NULL != sl_player_object_);

  SLresult result = (*sl_play_itf_)->SetPlayState(sl_play_itf_, SL_PLAYSTATE_STOPPED);
  assert(SL_RESULT_SUCCESS == result);

  is_busy_ = false;
}
