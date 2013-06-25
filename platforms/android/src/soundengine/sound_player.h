//
//  sound_player.h
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

// TODO rename this file... depending on SoundEngine redesign.
#ifndef SOUNDENGINE_SOUNDPLAYERIMPL_H
#define SOUNDENGINE_SOUNDPLAYERIMPL_H

#include <android/asset_manager.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <map>

#include "gameengine/modules/sound_player.h"

#include "soundengine/sound_type.h"

class SoundPlayerImpl : public SoundPlayer {
 public:
  SoundPlayerImpl();

  // AVAudioSession* session();
  bool isMusicPlayingInITunes();
  void syncAudioSessionForITunes();
  void duckAudioFromITunes(bool duck);

  void initialize();
  bool setGlobalVolume(float volume);
  bool setVolume(Sound sound, float volume);
  bool setPosition(Sound sound, float position);
  bool playSound(Sound sound);
  bool stopSound(Sound sound);
  void playSong(std::string filename);
  void stopSong();
  void setMusicOn(bool on);
  void setSoundEffectsOn(bool on);

  void setAssetManager(AAssetManager *asset_manager) { asset_manager_ = asset_manager; }

 private:
   AAssetManager *asset_manager_;

   std::map<Sound, SoundType *> sounds_;

   SLDataLocator_OutputMix loc_outmix_;
   SLDataSink audio_sink_;
   SLObjectItf engine_object_;
   SLEngineItf engine_engine_;
   SLObjectItf output_mix_object_;
};

#endif
