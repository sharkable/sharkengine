//
//  IOSIAdAdModule.mm
//  SharkEngine
//
//  Created by Jon Sharkey on 2013-08-13.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "sharkengine/apple/modules/ios/IOSIAdAdModule.h"

#import <iAd/ADInterstitialAd.h>

using std::string;

@interface IAdInterstitialState : NSObject<ADInterstitialAdDelegate> {
 @private
  BOOL preparedCalledAlready_;
  BOOL showing_;
  ADInterstitialAd *interstitialAd_;
}

@property(nonatomic, readonly) BOOL showing;

- (void)prepareFullScreenAd;
- (BOOL)showFullScreenAdFromViewController:(UIViewController *)viewController;

@end


@implementation IAdInterstitialState

@synthesize showing = showing_;

- (void)dealloc {
  [interstitialAd_ release];
  [super dealloc];
}

- (void)prepareFullScreenAd {
  if (!preparedCalledAlready_) {
    [self prepareFullScreenAd_Delayed];
    preparedCalledAlready_ = YES;
  } else {
    [self performSelector:@selector(prepareFullScreenAd_Delayed)
               withObject:nil
               afterDelay:60];
  }
}

- (void)prepareFullScreenAd_Delayed {
  [interstitialAd_ release];
  interstitialAd_ = [[ADInterstitialAd alloc] init];
  interstitialAd_.delegate = self;
}

- (BOOL)showFullScreenAdFromViewController:(UIViewController *)viewController {
  if (!interstitialAd_.loaded) {
    return false;
  }
  [interstitialAd_ presentFromViewController:viewController];
  showing_ = YES;
  [self prepareFullScreenAd];
  return true;
}

// ADInterstitialAdDelegate

- (void)interstitialAdDidLoad:(ADInterstitialAd *)interstitialAd {
}

- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd {
  if (interstitialAd == interstitialAd_) {
    interstitialAd_ = nil;
    [interstitialAd_ release];
  }
}

- (BOOL)interstitialAdActionShouldBegin:(ADInterstitialAd *)interstitialAd
                   willLeaveApplication:(BOOL)willLeave {
  return YES;
}

- (void)interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd {
  showing_ = NO;
}

- (void)interstitialAd:(ADInterstitialAd *)interstitialAd
    didFailWithError:(NSError *)error {
  NSLog(@"iAd load failed: %@", error.debugDescription);
  [self prepareFullScreenAd];
  showing_ = NO;
}

@end


IOSIAdAdModule::IOSIAdAdModule(UIViewController *root_view_controller)
    : admob_module_(root_view_controller) {
  interstitial_state_ = [[IAdInterstitialState alloc] init];
  root_view_controller_ = [root_view_controller retain];
}

IOSIAdAdModule::~IOSIAdAdModule() {
  dispatch_async(dispatch_get_main_queue(), ^{
      [interstitial_state_ release];
      [root_view_controller_ release];
  });
}


// AdModule

void IOSIAdAdModule::SetPublisherId(const std::string & publisher_id) {
  admob_module_.SetPublisherId(publisher_id);
}

void IOSIAdAdModule::SetAdAtPoint(ScreenPoint point) {
  admob_module_.SetAdAtPoint(point);
}

void IOSIAdAdModule::RemoveAd() {
  admob_module_.RemoveAd();
}

void IOSIAdAdModule::PrepareFullScreenAd() {
  admob_module_.PrepareFullScreenAd();
  dispatch_async(dispatch_get_main_queue(), ^{
      [interstitial_state_ prepareFullScreenAd];
  });
}

bool IOSIAdAdModule::ShowFullScreenAd() {
  __block bool result = false;
  dispatch_sync(dispatch_get_main_queue(), ^{
      result = [interstitial_state_ showFullScreenAdFromViewController:root_view_controller_];
      if (!result) {
        result = admob_module_.ShowFullScreenAd();
      }
  });
  return result;
}

bool IOSIAdAdModule::IsShowingFullScreenAd() {
  return interstitial_state_.showing;
}
