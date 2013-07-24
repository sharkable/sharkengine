//
//  sound_player.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "soundengine/sound_player.h"

// TODO this is now tied to gameengine.
#include "gameengine/android/modules/asset_reader_android.h"

using std::string;

static SoundPlayerImpl *soundInstance_ = NULL;

SoundPlayer *SoundPlayer::instance() {
  if (soundInstance_ == NULL) {
    soundInstance_ = new SoundPlayerImpl();
  }
  return soundInstance_;
}

SoundPlayer *SoundPlayer::shutdown() {
  delete soundInstance_;
  soundInstance_ = NULL;
}

SoundPlayerImpl::SoundPlayerImpl()
    : engine_object_(NULL),
      engine_engine_(NULL),
      output_mix_object_(NULL) {
}

SoundPlayerImpl::~SoundPlayerImpl() {
  for (auto i = sounds_.begin(); i != sounds_.end(); i++) {
    delete i->second;
  }
  if (output_mix_object_) {
    (*output_mix_object_)->Destroy(output_mix_object_);
  }
  if (engine_object_) {
    (*engine_object_)->Destroy(engine_object_);
  }
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

  const SLuint32 engineMixIIDCount = 1;
  const SLInterfaceID engineMixIIDs[] = {SL_IID_ENGINE};
  const SLboolean engineMixReqs[] = {SL_BOOLEAN_TRUE};

  // create engine  
  result = slCreateEngine(&engine_object_, 0, NULL, engineMixIIDCount, engineMixIIDs,
                          engineMixReqs);
  assert(SL_RESULT_SUCCESS == result);

  // realize the engine
  result = (*engine_object_)->Realize(engine_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);

  // get the engine interface, which is needed in order to create other objects
  result = (*engine_object_)->GetInterface(engine_object_, SL_IID_ENGINE, &engine_engine_);
  assert(SL_RESULT_SUCCESS == result);

  // create output mix
  result = (*engine_engine_)->CreateOutputMix(engine_engine_, &output_mix_object_, 0, NULL, NULL);
  assert(SL_RESULT_SUCCESS == result);

  // realize the output mix
  result = (*output_mix_object_)->Realize(output_mix_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);
  
  // configure audio sink
  loc_outmix_ = {SL_DATALOCATOR_OUTPUTMIX, output_mix_object_};
  audio_sink_ = {&loc_outmix_, NULL};

  sounds_[kSoundScore] = (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_,
                                                 "sounds/score.wav");
  sounds_[kSoundScoreFinal] = (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_,
                                                      "sounds/score_final.wav");
  sounds_[kSoundPaddleHit] = (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_,
                                                     "sounds/paddle_hit.wav");
  sounds_[kSoundPuckRinkBounce] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/puck_rink_bounce.wav");
  sounds_[kSoundTwoPuckHit] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/puck_puck_hit.wav");
  sounds_[kSoundButton] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/beep.wav");
  sounds_[kSoundMultiSelect] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/button_click.wav");
  sounds_[kSoundGetReady] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/get_ready.wav");
  sounds_[kSoundStart] =
      (new SoundType())->Init(asset_manager_, engine_engine_, audio_sink_, "sounds/start.wav");

  sound_volumes_[kSoundScore]  = 1;
  sound_volumes_[kSoundScoreFinal]  = 1;
  sound_volumes_[kSoundPaddleHit]  = 1;
  sound_volumes_[kSoundPuckRinkBounce]  = 1;
  sound_volumes_[kSoundTwoPuckHit]  = 1;
  sound_volumes_[kSoundButton]  = 1;
  sound_volumes_[kSoundMultiSelect]  = 1;
  sound_volumes_[kSoundGetReady]  = 1;
  sound_volumes_[kSoundStart]  = 1;
}

bool SoundPlayerImpl::setGlobalVolume(float volume) {
  global_volume_ = volume;
}

bool SoundPlayerImpl::setVolume(Sound sound, float volume) {
  sound_volumes_[sound] = volume;
}

bool SoundPlayerImpl::setPosition(Sound sound, float position) {
  sound_positions_[sound] = position;
}

bool SoundPlayerImpl::playSound(Sound sound) {
  sounds_[sound]->Play(global_volume_ * sound_volumes_[sound], sound_positions_[sound]);
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
