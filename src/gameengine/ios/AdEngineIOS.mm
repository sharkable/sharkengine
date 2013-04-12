//
//  AdEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-02-07.
//  Copyright 2013 Sharkable. All rights reserved.
//

#import "gameengine/ios/AdEngineIOS.h"

#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADBannerView.h"
#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADInterstitial.h"
#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADInterstitialDelegate.h"
#import "gameengine/ios/thirdparty/GoogleAdMobAdsSdkiOS-6.2.1/GADRequest.h"
#import "gameengine/coordinate_types.h"

// TODO Take this through a parameter.
static NSString *kPublisherId = @"a14bdda6dfc895a";

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
  SetUpNewInterstitial();
}

AdEngineIOS::~AdEngineIOS() {
  [banner_view_ release];
  [interstitial_ release];
  [interstitial_state_ release];
  [root_view_controller_ release];
}


// AdEngine

// TODO This is NOT really a ScreenPoint... nor is it a GamePoint. We need access
// to the GameEngine.
void AdEngineIOS::SetAdAtPoint(ScreenPoint point) {
  if (!banner_view_) {
    banner_view_ = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner];
    banner_view_.adUnitID = kPublisherId;
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

bool AdEngineIOS::ShowFullScreenAd() {
  if (!interstitial_.isReady) {
    return false;
  }
  [interstitial_ presentFromRootViewController:root_view_controller_];
  SetUpNewInterstitial();
  return true;
}

bool AdEngineIOS::IsShowingFullScreenAd() {
  return interstitial_state_.showing;
}


// private

void AdEngineIOS::SetUpNewInterstitial() {
  [interstitial_ release];
  interstitial_ = [[GADInterstitial alloc] init];
  interstitial_.delegate = interstitial_state_;
  interstitial_.adUnitID = kPublisherId;
  GADRequest *request = [GADRequest request];
  request.testDevices = [NSArray arrayWithObject:GAD_SIMULATOR_ID];
  [interstitial_ loadRequest:request];
}
