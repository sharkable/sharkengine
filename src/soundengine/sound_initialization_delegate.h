//
//  sound_initialization_delegate.h
//  GameEngine
//
//  Created by Jon Sharkey on 2009-10-26.
//  Copyright 2009 Sharkable. All rights reserved.
//

#ifndef AIRHOCKEY_SOUND_INITIALIZATION_DELEGATE_H
#define AIRHOCKEY_SOUND_INITIALIZATION_DELEGATE_H

class SoundPlayer;

class SoundInitializationDelegate {
 public:
  virtual void SoundInitialized(SoundPlayer *sound_player) = 0;
};

#endif
