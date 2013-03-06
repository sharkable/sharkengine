/**
 * The Audio protocal ensures a standardised set of functionality for any 
 * class that implements it.
 **/
@protocol Audio
-(void)play;
-(void)stop;
-(void)rewind;
-(bool)isPlaying;
-(void)loop:(bool)flag;
-(void)setVolume:(float)volume;
-(void)setPosition:(float)position;
@end
