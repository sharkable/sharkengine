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

class SoundPlayer {
 public:
  virtual void initialize() = 0;
  virtual void syncAudioSessionForITunes() = 0;
  virtual void duckAudioFromITunes(bool duck) = 0;
  virtual bool setGlobalVolume(float volume) = 0;
  virtual bool setVolume(Sound sound, float volume) = 0;
  virtual bool setPosition(Sound sound, float position) = 0;
  virtual bool playSound(Sound sound) = 0;
  virtual bool stopSound(Sound sound) = 0;
  virtual void playSong(std::string filename) = 0;
  virtual void stopSong() = 0;
  virtual void setMusicOn(bool on) = 0;
  virtual void setSoundEffectsOn(bool on) = 0;

  static SoundPlayer *instance();
  static void shutdown();
};

#endif
