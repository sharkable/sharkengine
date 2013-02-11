//
//  sound_initialization_delegate.h
//  AirHockey
//
//  Created by Jonathan Sharkey on 09-10-26.
//  Copyright 2012 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_SOUND_INITIALIZATION_DELEGATE_H
#define AIRHOCKEY_SOUND_INITIALIZATION_DELEGATE_H

class SoundPlayer;

class SoundInitializationDelegate {
 public:
  virtual void SoundInitialized(SoundPlayer *sound_player) = 0;
};

#endif
