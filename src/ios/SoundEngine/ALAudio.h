#import "Audio.h"
#import "MyOpenALSupport.h"

@interface ALAudio : NSObject<Audio> {
 @private
  ALuint buffer_id_;
  ALuint source_id_;
}

- (ALAudio *)initWithFilename:(NSString *)filename andExt:(NSString *)ext;

@end
