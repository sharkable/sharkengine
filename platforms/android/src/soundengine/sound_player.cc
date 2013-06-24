//
//  SoundPlayer.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-03-21.
//  Copyright 2013 Sharkable. All rights reserved.
//

// TODO: Uses code from native-audio-jni.c in Android NDK examples. Check license.

#include "soundengine/sound_player.h"

// TODO this is now tied to gameengine.
#include "gameengine/android/modules/asset_reader_android.h"

using std::string;

static SoundPlayerImpl *soundInstance_ = NULL;

SoundPlayer *SoundPlayer::instance() {
  if (soundInstance_ == NULL) {
    soundInstance_ = new SoundPlayerImpl();
  }
  return soundInstance_;
}

SoundPlayerImpl::SoundPlayerImpl()
    : engine_object_(NULL),
      engine_engine_(NULL),
      output_mix_object_(NULL),
      fdPlayerObject(NULL),
      fdPlayerPlay(NULL),
      fdPlayerVolume(NULL) {
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
  SLresult result;

  // create engine
  result = slCreateEngine(&engine_object_, 0, NULL, 0, NULL, NULL);
  assert(SL_RESULT_SUCCESS == result);

  // realize the engine
  result = (*engine_object_)->Realize(engine_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);

  // get the engine interface, which is needed in order to create other objects
  result = (*engine_object_)->GetInterface(engine_object_, SL_IID_ENGINE, &engine_engine_);
  assert(SL_RESULT_SUCCESS == result);

  // create output mix, with environmental reverb specified as a non-required interface
  const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
  const SLboolean req[1] = {SL_BOOLEAN_FALSE};
  result = (*engine_engine_)->CreateOutputMix(engine_engine_, &output_mix_object_, 1, ids, req);
  assert(SL_RESULT_SUCCESS == result);

  // realize the output mix
  result = (*output_mix_object_)->Realize(output_mix_object_, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);



// TEST CODE


  // SLresult result;
  // 
  // // convert Java string to UTF-8
  // const char *utf8 = (*env)->GetStringUTFChars(env, filename, NULL);
  // assert(NULL != utf8);
  // 
  // use asset manager to open asset by filename
  // AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
  assert(NULL != mgr_);
  AAsset* asset = AAssetManager_open(mgr_, "sounds/beep.wav", AASSET_MODE_UNKNOWN);
  // 
  // // release the Java string and UTF-8
  // (*env)->ReleaseStringUTFChars(env, filename, utf8);
  // 
  // the asset might not be found
  assert(NULL != asset);

  // open asset as file descriptor
  off_t start, length;
  int fd = AAsset_openFileDescriptor(asset, &start, &length);
  assert(0 <= fd);
  AAsset_close(asset);

  // AssetReaderAndroid test("assets/sounds/beep.wav");
  // size_t length = test.Size();
  // char *data = (char *)malloc(length * sizeof(char));
  // test.Read(data, sizeof(char), length);
  // s_log("LENGTH: %d", length);

  // configure audio source
  SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
  SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
  SLDataSource audioSrc = {&loc_fd, &format_mime};

  // configure audio sink
  SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, output_mix_object_};
  SLDataSink audioSnk = {&loc_outmix, NULL};
  
  // create audio player
  const SLInterfaceID ids_rename_this[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
  const SLboolean req_rename_this[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
  result = (*engine_engine_)->CreateAudioPlayer(engine_engine_, &fdPlayerObject, &audioSrc, &audioSnk,
          3, ids_rename_this, req_rename_this);
        s_log("RESULT: %d", result);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // realize the player
  result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // get the play interface
  result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // get the volume interface
  result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
  assert(SL_RESULT_SUCCESS == result);
  (void)result;
  
  // enable whole file looping
  // result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
  // assert(SL_RESULT_SUCCESS == result);
  // (void)result;
}

bool SoundPlayerImpl::setGlobalVolume(float volume) {
}

bool SoundPlayerImpl::setVolume(Sound sound, float volume) {
}

bool SoundPlayerImpl::setPosition(Sound sound, float position) {
}

bool SoundPlayerImpl::playSound(Sound sound) {
  SLresult result;

  // make sure the asset audio player was created
  if (NULL != fdPlayerPlay) {

      // set the player's state
      result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
      assert(SL_RESULT_SUCCESS == result);

  } 
}

bool SoundPlayerImpl::stopSound(Sound sound) {
}

void SoundPlayerImpl::playSong(string filename) {
}

void SoundPlayerImpl::stopSong() {
}

void SoundPlayerImpl::setMusicOn(bool on) {
}

void SoundPlayerImpl::setSoundEffectsOn(bool on) {
}

void SoundPlayerImpl::syncAudioSessionForITunes() {
}
