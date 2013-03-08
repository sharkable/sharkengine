//
//  AdEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-07.
//  Copyright 2012 Sharkable. All rights reserved.
//

#import "gameengine/ios/AdEngineIOS.h"

#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADBannerView.h"
#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADRequest.h"
#import "gameengine/coordinate_types.h"

AdEngineIOS::AdEngineIOS(UIViewController *root_view_controller) {
  banner_view_ = nil;
  root_view_controller_ = [root_view_controller retain];
}

AdEngineIOS::~AdEngineIOS() {
  [banner_view_ release];
  [root_view_controller_ release];
}


// AdEngine

// TODO This is NOT really a ScreenPoint... nor is it a GamePoint. We need access
// to the GameEngine.
void AdEngineIOS::SetAdAtPoint(ScreenPoint point) {
  if (!banner_view_) {
    banner_view_ = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    banner_view_.adUnitID = @"a14bdda6dfc895a";
    banner_view_.rootViewController = root_view_controller_;
    GADRequest *request = [GADRequest request];
    request.testDevices = [NSArray arrayWithObject:GAD_SIMULATOR_ID];
    [banner_view_ loadRequest:request];
  }
  [banner_view_.rootViewController.view addSubview:banner_view_];
  CGRect frame = banner_view_.frame;
  frame.origin = CGPointMake(point.x, point.y);
  banner_view_.frame = frame;
}

void AdEngineIOS::RemoveAd() {
  [banner_view_ removeFromSuperview];
  [banner_view_ release];
  banner_view_ = nil;
}
