#import "ALAudio.h"

ALCcontext* context_ = nil;
ALCdevice*  device_  = nil;


@implementation ALAudio

-(ALAudio*)initWithFilename:(NSString*)filename andExt:(NSString*)ext
{
  if((self = [self init]) != nil)
  {
    if(device_ == nil)
    {
      device_ = alcOpenDevice(NULL);
      if (device_)
      {
        context_ = alcCreateContext(device_,NULL);
        alcMakeContextCurrent(context_);
      }
    }

    ALvoid* audioData;
    ALenum  error = AL_NO_ERROR;
    ALenum  format;
    ALsizei size;
    ALsizei freq;

    NSBundle * bundle = [NSBundle mainBundle];

    // get some audio data from a wave file
    CFURLRef fileURL = (CFURLRef)[[NSURL fileURLWithPath:[bundle pathForResource:filename ofType:ext]] retain];
    if(!fileURL)
    {
      return nil;
    }

    audioData = MyGetOpenALAudioData(fileURL, &size, &format, &freq);

    CFRelease(fileURL);

    if((error = alGetError()) != AL_NO_ERROR) {
      printf("error loading sound: %x\n", error);
      exit(1);
    }

    // grab a buffer ID from openAL
    alGenBuffers(1, &buffer_id_);

    // load the awaiting data blob into the openAL buffer.
    alBufferData(buffer_id_,format,audioData,size,freq);

    // grab a source ID from openAL
    alGenSources(1, &source_id_);

    // attach the buffer to the source
    alSourcei(source_id_, AL_BUFFER, buffer_id_);

    alSourcef(source_id_, AL_PITCH, 1.0f);
    alSourcef(source_id_, AL_GAIN,  1.0f);
    alSourcef(source_id_, AL_MIN_GAIN,  0.0f);
    alSourcef(source_id_, AL_MAX_GAIN,  1.0f);
    //    if (loops) alSourcei(source_id_, AL_LOOPING, AL_TRUE);

    // clean up the buffer
    if (audioData)
    {
      free(audioData);
      audioData = NULL;
    }

  }

  return self;
}

-(void)dealloc
{
  alDeleteSources(1, &source_id_);
  alDeleteBuffers(1, &buffer_id_);

  alcDestroyContext(context_);
  alcCloseDevice(device_);

  [super dealloc];
}

-(void)play
{
  alSourcePlay(source_id_);
}

-(void)stop
{
  alSourceStop(source_id_);
}

-(void)rewind
{
  alSourceRewind(source_id_);
}

-(bool)isPlaying
{
  ALenum state;
  alGetSourcei(source_id_, AL_SOURCE_STATE, &state);
  return (state == AL_PLAYING);
}

-(void)loop:(bool)flag
{
  alSourcei(source_id_, AL_LOOPING, (flag == YES) ? AL_TRUE : AL_FALSE);
}

-(void)setVolume:(float)volume
{
  float gain = volume / 1.0f * 0.5f;
  alSourcef(source_id_, AL_GAIN, gain);
}

-(void)setPosition:(float)position {
  float sourcePosAL[] = {position, 0.0f, 0.0f};
  alSourcefv(source_id_, AL_POSITION, sourcePosAL);
}

@end
