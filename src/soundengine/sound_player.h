//
//  sound_player.h
//  AirHockey
//
//  Created by Jon Sharkey on 1/15/13.
//
//

#ifndef AIRHOCKEY_SOUND_PLAYER_H
#define AIRHOCKEY_SOUND_PLAYER_H

#include "soundengine/sound_initialization_delegate.h"

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
  virtual void initializeWithDelegate(SoundInitializationDelegate *delegate) = 0;
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
};

#endif
