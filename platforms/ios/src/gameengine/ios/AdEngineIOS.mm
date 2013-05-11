//
//  AdEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/ios/AdEngineIOS.h"

#import "gameengine/ios/thirdparty/admob/GADBannerView.h"
#import "gameengine/ios/thirdparty/admob/GADInterstitial.h"
#import "gameengine/ios/thirdparty/admob/GADInterstitialDelegate.h"
#import "gameengine/ios/thirdparty/admob/GADRequest.h"
#import "gameengine/ios/TypeUtil.h"
#import "gameengine/coordinate_types.h"

using std::string;

@interface InterstitialState : NSObject<GADInterstitialDelegate> {
 @private
  BOOL _showing;
}

@property(nonatomic, readonly) BOOL showing;

@end


@implementation InterstitialState

@synthesize showing = _showing;

// GADInterstitialDelegate

- (void)interstitialWillPresentScreen:(GADInterstitial *)ad {
  _showing = YES;
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad {
  _showing = NO;
}

@end


AdEngineIOS::AdEngineIOS(UIViewController *root_view_controller) {
  banner_view_ = nil;
  interstitial_ = nil;
  interstitial_state_ = [[InterstitialState alloc] init];
  root_view_controller_ = [root_view_controller retain];
}

AdEngineIOS::~AdEngineIOS() {
  [banner_view_ release];
  [interstitial_ release];
  [interstitial_state_ release];
  [root_view_controller_ release];
}


// AdEngine

void AdEngineIOS::SetPublisherId(string publisher_id) {
  publisher_id_ = publisher_id;
}

// TODO This is NOT really a ScreenPoint... nor is it a GamePoint. We need access
// to the GameEngine.
void AdEngineIOS::SetAdAtPoint(ScreenPoint point) {
  if (!banner_view_) {
    assert(publisher_id_.length());
    banner_view_ = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    banner_view_.adUnitID = TypeUtil::string2NSString(publisher_id_);
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

void AdEngineIOS::PrepareFullScreenAd() {
  assert(publisher_id_.length());
  [interstitial_ release];
  interstitial_ = [[GADInterstitial alloc] init];
  interstitial_.delegate = interstitial_state_;
  interstitial_.adUnitID = TypeUtil::string2NSString(publisher_id_);
  GADRequest *request = [GADRequest request];
  request.testDevices = [NSArray arrayWithObject:GAD_SIMULATOR_ID];
  [interstitial_ loadRequest:request];
}

bool AdEngineIOS::ShowFullScreenAd() {
  if (!interstitial_.isReady) {
    return false;
  }
  [interstitial_ presentFromRootViewController:root_view_controller_];
  PrepareFullScreenAd();
  return true;
}

bool AdEngineIOS::IsShowingFullScreenAd() {
  return interstitial_state_.showing;
}
