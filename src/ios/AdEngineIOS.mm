//
//  AdEngineIOS.mm
//  AirHockey
//
//  Created by Jon Sharkey on 2/7/13.
//
//

#import "ios/AdEngineIOS.h"

#import "GADBannerView.h"
#import "GADRequest.h"
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
