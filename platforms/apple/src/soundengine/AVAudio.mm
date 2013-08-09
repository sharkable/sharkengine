#import "AVAudio.h"


@implementation AudioInterruptDelegate



 //audioPlayerEndInterruption: is called when the audio session interruption has ended and this player had been interrupted while playing. (phone rings, user ignores it... music stops, now its back on yay)
 //The player can be restarted at this point.

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player
{
// TODO: Fix for OS X.
#if TARGET_OS_IPHONE
  NSError* activationError = nil;
  [[AVAudioSession sharedInstance] setActive:YES error:&activationError];
#endif
  [player play];
}

@end


@implementation AVAudio


-(AVAudio*) initWithURL:(NSURL*)url
{
  if((self = [super init]) != nil)
  {
    NSError* error;
    player_ = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&error];

    if( player_ == nil )
    {
      NSLog( @"ERROR Initializing AVAudioPlayer in AVAudio::initWithURL \n\t%@\n\tURL [%@]\n", error, url );
    }
    else
    {
      NSLog( @"SUCCESS Initializing AVAudioPlayer [%p] in AVAudio::initWithURL \n\tURL [%@]\n", player_,  url );
    }


    [self loop:NO];
    [player_ prepareToPlay];
  }

  return self;
}

-(void) dealloc
{
  [self stop];

  [player_ release];
  [super dealloc];
}

-(void) play
{
  if(player_.playing) {
    [player_ stop];
  }
  [player_ play];
}

-(void) stop
{
  if(player_.playing == YES) {
    [player_ stop];
  }
}

-(void) rewind
{
  player_.currentTime = 0.0f;
}

-(bool)isPlaying
{
  return player_.playing;
}

-(void)loop:(bool)flag
{
  player_.numberOfLoops = (flag == YES ? -1 : 0);
}


-(void)setVolume:(float)volume
{
//  if     (volume < 0.0f) { volume = 0.0f; }
//  else if(volume > 1.0f) { volume = 1.0f; }
  player_.volume = volume;
}

-(void)setPosition:(float)position
{
  // TODO
  NSAssert(false, @"setPosition not implemented in AVAudio.");
}

-(void) pause
{
  if(player_.playing == YES) {
    [player_ pause];
  }
}

-(void) seek:(NSTimeInterval)idx
{
  if     (idx <              0.0f) { idx =              0.0f; }
  else if(idx > player_.duration) { idx = player_.duration; }
  player_.currentTime = idx;
}

// Set the audio-session-interrupt handler
-(void) setInterruptDelegate:(AudioInterruptDelegate*)delegate;
{
  player_.delegate = delegate;
}

@end
