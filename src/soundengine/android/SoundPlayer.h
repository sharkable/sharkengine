//
//  SoundPlayer.h
//  SoundEngine
//
//  Created by Jon Sharkey on 2009-10-21.
//  Copyright 2009 Sharkable. All rights reserved.
//

#include "soundengine/sound_player.h"

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
};

