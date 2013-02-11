#import <AVFoundation/AVFoundation.h>
#import "Audio.h"



@interface AudioInterruptDelegate : NSObject <AVAudioPlayerDelegate> 
{
  
}

/* audioPlayerEndInterruption: is called when the audio session interruption has ended and this player had been interrupted while playing. 
 The player can be restarted at this point. */
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player;

@end



/**
 * Uses the Apple AV audio player to play a sample.
 * AV audio loads quickly, but has high latency.
 **/
@interface AVAudio : NSObject <Audio>
{
  AVAudioPlayer* player_;
}

-(AVAudio*) initWithURL:(NSURL*)url;

-(void) pause;

-(void) seek:(NSTimeInterval)idx;

// Set the volume
-(void) setVolume:(float)volume;

// Set the audio-session-interrupt handler
-(void) setInterruptDelegate:(AudioInterruptDelegate*)delegate;

@end
