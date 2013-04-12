//
//  SoundPlayer.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2009 Sharkable. All rights reserved.
//

#include "SoundPlayer.h"


using std::string;

static SoundPlayerImpl *soundInstance_ = NULL;

SoundPlayer *SoundPlayer::instance() {
  if (soundInstance_ == NULL) {
    soundInstance_ = new SoundPlayerImpl();
  }
  return soundInstance_;
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

void SoundPlayerImpl::playSong(string filename)
{
}

void SoundPlayerImpl::stopSong() {
}

void SoundPlayerImpl::setMusicOn(bool on) {
}

void SoundPlayerImpl::setSoundEffectsOn(bool on) {
}

SoundPlayerImpl::SoundPlayerImpl() {
}

void SoundPlayerImpl::syncAudioSessionForITunes() {
}

