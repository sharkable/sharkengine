//
//  main.m
//  GameEngine
//
//  Created by Jon Sharkey on 2010-05-07.
//  Copyright 2010 Sharkable. All rights reserved.
//

#import <UIKit/UIKit.h>

int main(int argc, char *argv[]) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  int retVal = UIApplicationMain(argc, argv, nil, @"AppDelegate");
  [pool release];
  return retVal;
}
