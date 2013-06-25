//
//  sound_type.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "soundengine/sound_type.h"

#include "soundengine/sound_instance.h"

struct SoundInstanceNode {
  SoundInstance *value;
  SoundInstanceNode *next;

  SoundInstanceNode() {
    value = NULL;
    next = NULL;
  }

  ~SoundInstanceNode() {
    if (value) {
      delete value;
    }
    if (next) {
      delete next;
    }    
  }
};

SoundType::SoundType(AAssetManager *asset_manager, SLEngineItf engine_engine, SLDataSink data_sink,
    std::string filename) {
  engine_engine_ = engine_engine;
  data_sink_ = data_sink;

  // SLresult result;
  assert(NULL != asset_manager);
  AAsset* asset = AAssetManager_open(asset_manager, filename.c_str(), AASSET_MODE_UNKNOWN);
  // 
  // // release the Java string and UTF-8
  // (*env)->ReleaseStringUTFChars(env, filename, utf8);
  // 
  // the asset might not be found
  s_log("Loading sound: %s", filename.c_str());
  assert(NULL != asset);

  // open asset as file descriptor
  off_t start, length;
  int fd = AAsset_openFileDescriptor(asset, &start, &length);
  assert(0 <= fd);
  AAsset_close(asset);

  // configure audio source
  loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
  format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
  audioSrc = {&loc_fd, &format_mime};

  // enable whole file looping
  // result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
  // assert(SL_RESULT_SUCCESS == result);
  // (void)result;
  sound_instance_list_head_ = new SoundInstanceNode();
  sound_instance_list_head_->value = new SoundInstance(engine_engine, audioSrc, data_sink_);
}

void SoundType::Play(float volume, float position) {
  SoundInstanceNode *non_busy_node = sound_instance_list_head_;
  while (non_busy_node->next && non_busy_node->value->is_busy()) {
    non_busy_node = non_busy_node->next;
  }
  if (non_busy_node->value->is_busy()) {
    non_busy_node->next = new SoundInstanceNode();
    non_busy_node = non_busy_node->next;
    non_busy_node->value = new SoundInstance(engine_engine_, audioSrc, data_sink_);
    s_log("CREATING NEW NODE!");
  }
  non_busy_node->value->Play(volume, position);
}
