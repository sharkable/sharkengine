//
//  AppStoreEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/ios/AppStoreEngineIOS.h"

#include <UIKit/UIKit.h>

#include "gameengine/ios/TypeUtil.h"

@interface PopupHandler : NSObject<UIAlertViewDelegate> {
 @private
  UIAlertView *_ratePopup;
  UIAlertView *_upgradePopup;
  NSString *_appId;
}

- (void)askForRateAppNamed:(NSString *)appName appId:(NSString *)appId;
- (void)askForUpgradeAppNamed:(NSString *)appName appId:(NSString *)appId;
- (void)rateApp;
- (void)upgradeApp;

@end

@implementation PopupHandler

- (void)dealloc {
  [_ratePopup release];
  [_upgradePopup release];
  [_appId release];

  [super dealloc];
}

- (void)askForRateAppNamed:(NSString *)appName appId:(NSString *)appId {
  [_appId release];
  _appId = [appId retain];
  NSString *message =
      [NSString stringWithFormat:@"Are you enjoying %@?\n\nGive it a rating in the app store!",
       appName];
  [_ratePopup release];
  _ratePopup = [[UIAlertView alloc] initWithTitle:@"Rate this game!"
                                          message:message
                                         delegate:self
                                cancelButtonTitle:@"No thanks"
                                otherButtonTitles:@"Rate!", nil];
  [_ratePopup show];
}

- (void)askForUpgradeAppNamed:(NSString *)appName appId:(NSString *)appId {
  [_appId release];
  _appId = [appId retain];
  NSString *message =
      [NSString stringWithFormat:@"Are you enjoying %@?\n\nGive it a rating in the app store!",
       appName];
  [_upgradePopup release];
  _upgradePopup = [[UIAlertView alloc] initWithTitle:@"Upgrade!"
                                             message:message
                                            delegate:self
                                   cancelButtonTitle:@"No thanks"
                                   otherButtonTitles:@"Upgrade!", nil];
  [_upgradePopup show];
}


// UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
  if (alertView == _ratePopup) {
    if (buttonIndex == _ratePopup.firstOtherButtonIndex) {
      [self rateApp];
    }
    [_ratePopup release];
    _ratePopup = nil;
  } else if (alertView == _upgradePopup) {
    if (buttonIndex == _upgradePopup.firstOtherButtonIndex) {
      [self upgradeApp];
    }
    [_upgradePopup release];
    _upgradePopup = nil;
  }

  [_appId release];
  _appId = nil;
}

- (void)rateApp {
  NSString *url = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@",
                      _appId];
  [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

- (void)upgradeApp {
}

@end


AppStoreEngineIOS::AppStoreEngineIOS() {
  popup_handler_ = [[PopupHandler alloc] init];
}

AppStoreEngineIOS::~AppStoreEngineIOS() {
  [popup_handler_ release];
}

void AppStoreEngineIOS::AskForRate(std::string app_name, std::string app_id) {
  [popup_handler_ askForRateAppNamed:TypeUtil::string2NSString(app_name)
                               appId:TypeUtil::string2NSString(app_id)];
}

void AppStoreEngineIOS::AskForUpgrade(std::string app_name, std::string app_id) {
  [popup_handler_ askForUpgradeAppNamed:TypeUtil::string2NSString(app_name)
                                  appId:TypeUtil::string2NSString(app_id)];
}
