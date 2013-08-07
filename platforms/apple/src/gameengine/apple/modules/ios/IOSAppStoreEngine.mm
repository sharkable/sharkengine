//
//  AppStoreEngineIOS.mm
//  GameEngine
//
//  Created by Jon Sharkey on 2013-03-20.
//  Copyright 2013 Sharkable. All rights reserved.
//

#include "gameengine/apple/modules/ios/AppStoreEngineIOS.h"

#include <StoreKit/StoreKit.h>
#include <UIKit/UIKit.h>

#include "gameengine/apple/TypeUtil.h"
#include "gameengine/apple/thirdparty/ios/appirater/Appirater.h"

@interface PopupHandler : NSObject<SKPaymentTransactionObserver, SKProductsRequestDelegate,
    UIAlertViewDelegate> {
 @private
  UIAlertView *_upgradePopup;
  NSString *_appId;
  SKProductsRequest *_request;
  SKProduct *_product;
  AppStoreEngineDelegate *_delegate;  // weak
}

- (void)upgradeApp;
- (void)restoreUpgrade;
- (void)showFailure:(NSString *)message;

@end

@implementation PopupHandler

- (id)init {
  self = [super init];
  if (self) {
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
  }
  return  self;
}

- (void)dealloc {
  [_upgradePopup release];
  [_appId release];
  [_request release];
  [_product release];

  [super dealloc];
}

- (void)askForUpgradeAppNamed:(NSString *)appName
    purchaseId:(NSString *)purchaseId
    delegate:(AppStoreEngineDelegate *)delegate {
  _delegate = delegate;
  if (![SKPaymentQueue canMakePayments]) {
    [[[[UIAlertView alloc] initWithTitle:@"Cannot upgrade"
                                 message:@"You aren't set up to do purchases on this device."
                                delegate:nil
                       cancelButtonTitle:@"OK"
                       otherButtonTitles:nil] autorelease] show];
    return;
  }
  
  [_request release];
  _request =
      [[SKProductsRequest alloc] initWithProductIdentifiers:[NSSet setWithObject:purchaseId]];
  _request.delegate = self;
  [_request start];
}

- (void)upgradeApp {
  NSLog(@"upgrading: %@", _product.productIdentifier);
  SKPayment *payment = [SKPayment paymentWithProduct:_product];
  [[SKPaymentQueue defaultQueue] addPayment:payment];
  NSLog(@"done");
}

- (void)restoreUpgrade {
  [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)showFailure:(NSString *)message {
  if (!message) {
    message = @"There was an error.";
  }
  [[[[UIAlertView alloc] initWithTitle:@"Cannot upgrade"
                               message:message
                              delegate:nil
                     cancelButtonTitle:@"OK"
                     otherButtonTitles:nil] autorelease] show];
}


// SKPaymentTransactionObserver

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
  for (SKPaymentTransaction *transaction in transactions) {
    switch (transaction.transactionState) {
      case SKPaymentTransactionStatePurchased:
      case SKPaymentTransactionStateRestored:
        if (_delegate) {
          _delegate->UpgradeSucceeded();
          [[[[UIAlertView alloc] initWithTitle:@"Congrats!"
                                       message:@"No more ads. Thanks for your support!"
                                      delegate:nil
                             cancelButtonTitle:@"OK"
                             otherButtonTitles:nil] autorelease] show];
        } else {
          NSString *message = @"There was a problem upgrading the app. Please try again and choose "
              "\"Restore existing purchase\". You won't be charged again.";
          [[[[UIAlertView alloc] initWithTitle:@"Error"
                                       message:message
                                      delegate:nil
                             cancelButtonTitle:@"OK"
                             otherButtonTitles:nil] autorelease] show];
        }
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        break;
      case SKPaymentTransactionStateFailed:
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
        NSLog(@"ERROR: %d", transaction.error.code);
        [self showFailure:transaction.error.localizedDescription];
        break;
      default:
        break;
    }
  }
}

- (void)paymentQueue:(SKPaymentQueue *)queue
    restoreCompletedTransactionsFailedWithError:(NSError *)error {
  [self showFailure:error.localizedDescription];
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray *)downloads {
}


// SKProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request
     didReceiveResponse:(SKProductsResponse *)response {
  NSArray *products = response.products;
  if (products.count < 1) {
    [self showFailure:nil];
    return;
  }
  [_product release];
  _product = [[response.products objectAtIndex:0] retain];

  NSNumberFormatter *numberFormatter = [[[NSNumberFormatter alloc] init] autorelease];
  [numberFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
  [numberFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
  [numberFormatter setLocale:_product.priceLocale];
  NSString *price = [numberFormatter stringFromNumber:_product.price];
  NSString *restore = @"Restore existing purchase";

  [_upgradePopup release];
  _upgradePopup = [[UIAlertView alloc] initWithTitle:_product.localizedTitle
                                             message:_product.localizedDescription
                                            delegate:self
                                   cancelButtonTitle:@"No thanks"
                                   otherButtonTitles:price, restore, nil];
  [_upgradePopup show];

  [_request release];
  _request = nil;
}


// UIAlertViewDelegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
  if (alertView == _upgradePopup) {
    if (buttonIndex == _upgradePopup.firstOtherButtonIndex) {
      [self upgradeApp];
    } else if (buttonIndex == _upgradePopup.firstOtherButtonIndex + 1) {
      [self restoreUpgrade];
    }
    [_upgradePopup release];
    _upgradePopup = nil;
  }

  [_appId release];
  _appId = nil;
}

@end


AppStoreEngineIOS::AppStoreEngineIOS() {
  popup_handler_ = [[PopupHandler alloc] init];
}

AppStoreEngineIOS::~AppStoreEngineIOS() {
  [popup_handler_ release];
}

void AppStoreEngineIOS::AskForRate() {
  [Appirater rateApp];
}

void AppStoreEngineIOS::AskForUpgrade(std::string app_name, std::string purchase_id,
                                      AppStoreEngineDelegate *delegate) {
  [popup_handler_ askForUpgradeAppNamed:TypeUtil::string2NSString(app_name)
                             purchaseId:TypeUtil::string2NSString(purchase_id)
                               delegate:delegate];
}
