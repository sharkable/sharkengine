//
//  SoundPlayer.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

// TODO: Uses code from native-audio-jni.c in Android NDK examples. Check license.

#include "soundengine/sound_player.h"

using std::string;

static SoundPlayerImpl *soundInstance_ = NULL;

SoundPlayer *SoundPlayer::instance() {
  if (soundInstance_ == NULL) {
    soundInstance_ = new SoundPlayerImpl();
  }
  return soundInstance_;
}

SoundPlayerImpl::SoundPlayerImpl()
    : engine_object_(NULL),
      engine_engine_(NULL),
      output_mix_object_(NULL) {
}

//AVAudioSession *SoundPlayerImpl::session() {
//  return session_;
//}

bool SoundPlayerImpl::isMusicPlayingInITunes() {
  return false;
}

// allow sound effects to be clear by ducking the iTunes song
void SoundPlayerImpl::duckAudioFromITunes(bool duck) {
}

void SoundPlayerImpl::initialize() {
  SLresult result;

  // create engine
  result = slCreateEngine(&engine_object_, 0, NULL, 0, NULL, NULL);
  assert(SL_RESULT_SUCCESS == result);

  // realize the engine
  result = (*engine_object_)->Realize(engine_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);

  // get the engine interface, which is needed in order to create other objects
  result = (*engine_object_)->GetInterface(engine_object_, SL_IID_ENGINE, &engine_engine_);
  assert(SL_RESULT_SUCCESS == result);

  // create output mix, with environmental reverb specified as a non-required interface
  const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
  const SLboolean req[1] = {SL_BOOLEAN_FALSE};
  result = (*engine_engine_)->CreateOutputMix(engine_engine_, &output_mix_object_, 1, ids, req);
  assert(SL_RESULT_SUCCESS == result);

  // realize the output mix
  result = (*output_mix_object_)->Realize(output_mix_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);
}

bool SoundPlayerImpl::setGlobalVolume(float volume) {
}

bool SoundPlayerImpl::setVolume(Sound sound, float volume) {
}

bool SoundPlayerImpl::setPosition(Sound sound, float position) {
}

bool SoundPlayerImpl::playSound(Sound sound) {
}

bool SoundPlayerImpl::stopSound(Sound sound) {
}

void SoundPlayerImpl::playSong(string filename) {
}

void SoundPlayerImpl::stopSong() {
}

void SoundPlayerImpl::setMusicOn(bool on) {
}

void SoundPlayerImpl::setSoundEffectsOn(bool on) {
}

void SoundPlayerImpl::syncAudioSessionForITunes() {
}