//
//  sound_player.h
//  GameEngine
//
//  Created by Jon Sharkey on 2013-01-15.
//  Copyright 2013 Sharkable. All rights reserved.
//

#ifndef SOUNDENGINE_SOUNDPLAYER_H_
#define SOUNDENGINE_SOUNDPLAYER_H_

#include <string>

#include "gameengine/module.h"

typedef enum {
  kSoundScore = 0,
  kSoundScoreFinal,
  kSoundPaddleHit,
  kSoundPuckRinkBounce,
  kSoundTwoPuckHit,
  kSoundButton,
  kSoundMultiSelect,
  kSoundGetReady,
  kSoundStart,
  kNumSounds
} Sound;

class SoundPlayer : public Module {
 public:
  virtual void initialize() {};
  virtual void syncAudioSessionForITunes() {};
  virtual void duckAudioFromITunes(bool duck) {};
  virtual bool setGlobalVolume(float volume) { return false; };
  virtual bool setVolume(Sound sound, float volume) { return false; };
  virtual bool setPosition(Sound sound, float position) { return false; };
  virtual bool playSound(Sound sound) { return false; };
  virtual bool stopSound(Sound sound) { return false; };
  virtual void playSong(std::string filename) {};
  virtual void stopSong() {};
  virtual void setMusicOn(bool on) {};
  virtual void setSoundEffectsOn(bool on) {};

  static SoundPlayer *instance();
  static void shutdown();
};

#endif
