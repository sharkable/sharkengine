//
//  AdEngineAndroid.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-04-09.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/android/modules/ad_engine_android.h"

#include "gameengine/coordinate_types.h"

using std::string;

// AdEngine

void AdEngineAndroid::SetPublisherId(std::string publisher_id) {
}

// TODO This is NOT really a ScreenPoint... nor is it a GamePoint. We need access
// to the GameEngine.
void AdEngineAndroid::SetAdAtPoint(ScreenPoint point) {
}

void AdEngineAndroid::RemoveAd() {
}

void AdEngineAndroid::PrepareFullScreenAd() {
}

bool AdEngineAndroid::ShowFullScreenAd() {
  return false;
}

bool AdEngineAndroid::IsShowingFullScreenAd() {
  return false;
}
