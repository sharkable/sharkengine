//
//  sound_type.cc
//  SoundEngine
//
//  Created by Jon Sharkey on 2013-06-25.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "soundengine/sound_type.h"

#include "soundengine/sound_instance.h"

using std::string;

struct SoundInstanceNode {
  SoundInstance *value;
  SoundInstanceNode *next;

  SoundInstanceNode()
    : value(NULL),
      next(NULL) {
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

SoundType *SoundType::Init(AAssetManager *asset_manager, SLEngineItf sl_engine_itf,
                           SLDataSink sl_data_sink, string filename) {
  sl_engine_itf_ = sl_engine_itf;
  sl_data_sink_ = sl_data_sink;

  assert(NULL != asset_manager);
  AAsset* asset = AAssetManager_open(asset_manager, filename.c_str(), AASSET_MODE_UNKNOWN);
  // the asset might not be found
  assert(NULL != asset);

  // open asset as file descriptor
  off_t start, length;
  int fd = AAsset_openFileDescriptor(asset, &start, &length);
  assert(0 <= fd);
  AAsset_close(asset);

  // configure audio source
  sl_data_locator_ = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
  sl_format_mime_ = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
  sl_audio_source_ = {&sl_data_locator_, &sl_format_mime_};

  AddSoundInstance(&sound_instance_list_head_);

  return this;
}

void SoundType::Play(float volume, float position) {
  SoundInstanceNode *non_busy_node = sound_instance_list_head_;
  while (non_busy_node->next && non_busy_node->value->is_busy()) {
    non_busy_node = non_busy_node->next;
  }
  if (non_busy_node->value->is_busy()) {
    AddSoundInstance(&non_busy_node->next);
    non_busy_node = non_busy_node->next;
  }
  non_busy_node->value->Play(volume, position);
}


// private

void SoundType::AddSoundInstance(SoundInstanceNode **node) {
  *node = new SoundInstanceNode();
  (*node)->value = (new SoundInstance())->Init(sl_engine_itf_, sl_audio_source_, sl_data_sink_);
}
