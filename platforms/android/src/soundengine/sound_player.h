//
//  SoundPlayer.h
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <android/asset_manager.h>

#include "gameengine/modules/sound_player.h"

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

  void setAssetManager(AAssetManager *mgr) { mgr_ = mgr; }

 private:
   AAssetManager *mgr_;
   
   SLObjectItf engine_object_;
   SLEngineItf engine_engine_;
   SLObjectItf output_mix_object_;

   // file descriptor player interfaces
   SLObjectItf fdPlayerObject;
   SLPlayItf fdPlayerPlay;
   SLVolumeItf fdPlayerVolume;   
};
