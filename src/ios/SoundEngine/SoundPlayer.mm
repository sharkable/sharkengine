//
//  SoundPlayer.m
//  SocialDeck
//
//  Created by Jonathan Sharkey on 09-10-21.
//  Copyright 2009 Sharkable. All rights reserved.
//

#import "SoundPlayer.h"

#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioServices.h>
#import <MediaPlayer/MPMusicPlayerController.h>

#import "TypeUtil.h"

static SoundPlayerImpl *soundInstance_ = NULL;

static const bool thisAppDoesDucking = NO; // if this gets changed to yes then it's all set up to duck the sound when iTunes is playing with Sound effects ON

@interface SoundHelpers : NSObject
+ (NSString *)getAudioServicesError:(OSStatus)err;
@end

@implementation SoundHelpers

+ (NSString *)getAudioServicesError:(OSStatus)err {
  if (err == kAudioSessionNoError) {
    return nil;
  }
  
  NSString *errStr = nil;
  
  switch (err) {
    case kAudioSessionNotInitialized:
      errStr = @"An Audio Session Services function was called without first initializing the "
          "session. To avoid this error, call the AudioSessionInitialize function before "
          "attempting to use the session.";
      break;
    case kAudioSessionAlreadyInitialized:
      errStr = @"The AudioSessionInitialize function was called more than once during the lifetime "
          "of your application.";
      break;
    case kAudioSessionInitializationError:
      errStr = @"There was an error during audio session initialization.";
      break;
    case kAudioSessionUnsupportedPropertyError:
      errStr = @"The audio session property is not supported.";
      break;
    case kAudioSessionBadPropertySizeError:
      errStr = @"The size of the audio session property data was not correct.";
      break;
    case kAudioSessionNotActiveError:
      errStr = @"The audio operation failed because your application’s audio session was not "
          "active.";
      break;
    case kAudioServicesNoHardwareError:
      errStr = @"The audio operation failed because the device has no audio input available.";
      break;
#if __IPHONE_OS_VERSION_MIN_REQUIRED > 30000      
    case kAudioSessionNoCategorySet:
      errStr = @"The audio operation failed because it requires the audio session to have an "
          "explicitly-set category, but none was set. To use a hardware codec you must explicitly "
          "initialize the audio session and explicitly set an audio session category.";
      break;
    case kAudioSessionIncompatibleCategory:
      errStr = @"The specified audio session category cannot be used for the attempted audio "
          "operation. For example, you attempted to play or record audio with the audio session "
          "category set to kAudioSessionCategory_AudioProcessing.";
      break;
#endif
    default:
      errStr = @"Unknown Audio Session Error\n";
      break;
  }
  return errStr;  
}

@end


static AVAudioSession *session_ = nil;
static bool musicIsPlayingInITunes_ = false;

SoundPlayer *SoundPlayer::instance() {
  if (soundInstance_ == nil) {
    soundInstance_ = new SoundPlayerImpl();
  }
  return soundInstance_;
}

AVAudioSession *SoundPlayerImpl::session() {
  return session_;
}

bool SoundPlayerImpl::isMusicPlayingInITunes() {
  return musicIsPlayingInITunes_;
}

// allow sound effects to be clear by ducking the iTunes song    
void SoundPlayerImpl::duckAudioFromITunes(bool duck) {
  // note: not sure if this is for all AudioSession properties, but at least with ducking the
  // session has to be inactive to make the change so here we set the session to inactive at the top
  // of the function, and set to active at the end after setting the property
  
  NSError *activeErr = nil;
  BOOL sessionActive = [session_ setActive:NO error:&activeErr];
  if (!sessionActive) {
    NSLog(@"ERROR setting audio session active .... \n\tERROR: %@\n", activeErr);
  }

  // if the user want's the sound effects on while iTunes is playing , then we duck the iTunes so
  // you can hear the sounds, if sounds are off, iTunes is full volume :P
  UInt32 allowDuck = thisAppDoesDucking && duck && musicIsPlayingInITunes_;    
  OSStatus propertySetError =
      AudioSessionSetProperty(kAudioSessionProperty_OtherMixableAudioShouldDuck, sizeof(allowDuck),
                              &allowDuck);
  if (propertySetError != kAudioSessionNoError) {
    NSString *errStr = [SoundHelpers getAudioServicesError: propertySetError];
    NSLog(@"ERROR setting iTunes audio ducking property to [%s] ... \n\t ERROR: %@\n",
          allowDuck ? "ON" : "OFF" ,errStr );
  }
  
  activeErr = nil;
  sessionActive = [session_ setActive:YES error:&activeErr];

  if(!sessionActive) {
    NSLog(@"ERROR setting audio session active .... \n\tERROR: %@\n", activeErr);
  }
}

NSURL *SoundPlayerImpl::filenameToUrl(NSString *name) {
  // Convert path to a URL 
  NSString *path = [NSString stringWithFormat:@"%@/%@", [[NSBundle mainBundle] resourcePath], name];
  NSURL *url  = [NSURL fileURLWithPath:path];
  return url;
}

void SoundPlayerImpl::loadSoundsWithDelegate(SoundInitializationDelegate *delegate) {
  NSAutoreleasePool *subpool = [[NSAutoreleasePool alloc] init];
  
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"score" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"score_final" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"paddle_hit" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"puck_rink_bounce" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"puck_puck_hit" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"beep" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"button_click" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"get_ready" andExt:@"wav"]];
  [sounds_ addObject:[[ALAudio alloc] initWithFilename:@"start" andExt:@"wav"]];

  delegate->SoundInitialized(this);

  [subpool release];
}

void *loadSounds(void *delegate) {
  soundInstance_->loadSoundsWithDelegate((SoundInitializationDelegate *)delegate);
  pthread_exit(NULL);
}

void SoundPlayerImpl::initializeWithDelegate(SoundInitializationDelegate *delegate) {
  pthread_t thread;
  pthread_create(&thread, NULL, loadSounds, delegate);
}

bool SoundPlayerImpl::setGlobalVolume(float volume) {
  globalVolume_ = volume / 2;
  for (ALAudio* ALSound in sounds_) {
    [ALSound setVolume:globalVolume_];
  }
  return true;
}

bool SoundPlayerImpl::setVolume(Sound sound, float volume) {
  if (soundEffectsOn_) {
    if (sounds_.count > sound) {
      ALAudio* ALSound = (ALAudio*)[sounds_ objectAtIndex:sound];
      [ALSound setVolume:volume * globalVolume_];
      return true;
    }
    return false;
  }
  return true;
}

bool SoundPlayerImpl::setPosition(Sound sound, float position) {
  if (soundEffectsOn_) {
    if (sounds_.count > sound) {
      ALAudio* ALSound = (ALAudio*)[sounds_ objectAtIndex:sound];
      [ALSound setPosition:position];
      return true;
    }
    return false;
  }
  return true;
}

bool SoundPlayerImpl::playSound(Sound sound) {
  if (soundEffectsOn_) {
    if (sounds_.count > sound) {
      ALAudio* ALSound = (ALAudio*)[sounds_ objectAtIndex:sound];
      [ALSound play];
      return true;
    }
    return false;
  }
  return true;
}

bool SoundPlayerImpl::stopSound(Sound sound) {
  if (soundEffectsOn_) {
    if (sounds_.count > sound) {
      [(ALAudio*)[sounds_ objectAtIndex:sound] stop];
      return true;
    }
    return false;
  }
  return true;
}

void SoundPlayerImpl::playSong(string filename)
{
  return ;

  // no game songs if iTunes is playing
  if( musicIsPlayingInITunes_ )
    return;
  
  stopSong();
  if (musicOn_) {
    song_ = [[AVAudio alloc] initWithURL:filenameToUrl(TypeUtil::string2NSString(filename))];
    [song_ play];
  }
}

void SoundPlayerImpl::stopSong() {
  [song_ stop];
  [song_ release];
  song_ = nil;
}

void SoundPlayerImpl::setMusicOn(bool on) {
  musicOn_ = on;
}

void SoundPlayerImpl::setSoundEffectsOn(bool on) {
  soundEffectsOn_ = on;
}

SoundPlayerImpl::SoundPlayerImpl() {
  sounds_ = [[NSMutableArray alloc] initWithCapacity:kNumSounds];
  song_ = nil;
  
  AudioInterruptDelegate* delegate = [[AudioInterruptDelegate alloc] init];

  delegate_ = delegate;
}

//  SOUND-ENABLED  MUSIC-ENABLED  ITUNES-PLAYING    OUTCOME
//    NO        NO        NO          no sound obviously
//    NO        NO        YES          iTunes keeps playing , full volume
//    NO        YES        NO          Game music plays , full volume
//    NO        YES        YES          iTunes keeps playing , full volume ( NO GAME MUSIC )
//    YES        NO        NO          just sound effects, full volume
//    YES        NO        YES          iTunes keeps playing w/ ducked volume, sound effects play over iTunes music
//    YES        YES        NO          Game music plays , full volume with sound effects
//    YES        YES        YES          iTunes keeps playing w/ ducked volume, sound effects play over iTunes music ( NO GAME MUSIC )


// NOTE: if iTunes is playing all calls to playSong will be ignored, as well as any changes to music being enabled.... 
// NOTE: if iTunes is playing calls to enableSound will trigger the enabling , disabling of the 'ducking' 


//
// Funtionality to allow iTunes songs to play under our game audio
//
void SoundPlayerImpl::syncAudioSessionForITunes()
{
  //
  // In order to allow iTunes songs to play under our game music/effects
  // we need to set the category of our audio session.
  //
  AVAudioSession *session = [AVAudioSession sharedInstance];
  session_ = session;
  NSError *sessionError = nil;
  BOOL success = [session setCategory:AVAudioSessionCategoryAmbient error:&sessionError];
  if( success == NO )
  {
    //DOH!
    NSLog( @"ERROR Setting audio session category to allow itunes playback\n\t%@", sessionError ); 
  }
  else 
  {
    NSLog( @"SUCCESS Setting audio session category to allow itunes playback\n");
    
    MPMusicPlayerController* iPodMusicPlayer = [MPMusicPlayerController iPodMusicPlayer];
    
    // we need to know if a song is playing, because if one is not playing then we will want
    // to turn on our music (if the user has the music enabled - which is done elsewhere using
    // this 'musicIsPlayingInITunes_' member )
    MPMediaItem * currentlyPlayingItem = [iPodMusicPlayer nowPlayingItem];
    BOOL isPlayingITunes = (currentlyPlayingItem != nil ) && ( iPodMusicPlayer.playbackState == MPMusicPlaybackStatePlaying );
    musicIsPlayingInITunes_ = isPlayingITunes;    
  }  
}
