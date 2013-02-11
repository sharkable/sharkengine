//
//  resource_loader.cc
//  AirHockey
//
//  Created by Jon Sharkey on 4/29/12.
//  Copyright (c) 2012 Sharkable. All rights reserved.
//

#include "gameengine/resource_loader.h"

#import <UIKit/UIKit.h>

#include "ios/TypeUtil.h"
#include "opengl/texture2D.h"

Texture2D ResourceLoader::Texture(string name) {
  BOOL sizeToFit = NO;
  
  NSString *imageName = nil;
  if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
    imageName = [NSString stringWithFormat:@"%@.png", TypeUtil::string2NSString(name)];
  } else {
    imageName = [NSString stringWithFormat:@"%@_iphone.png", TypeUtil::string2NSString(name)];
  }
  UIImage *uiImage = [UIImage imageNamed:imageName];
  
  CGImageRef image = [uiImage CGImage];
  
  if (image == NULL) {
    image = [[UIImage imageNamed:@"yellowright.png"] CGImage];
    NSLog(@"Image is Null");
    return Texture2D();
  }
    
  CGImageAlphaInfo info = CGImageGetAlphaInfo(image);
  BOOL hasAlpha = ((info == kCGImageAlphaPremultipliedLast) ||
                   (info == kCGImageAlphaPremultipliedFirst) ||
                   (info == kCGImageAlphaLast) ||
                   (info == kCGImageAlphaFirst) ? YES : NO);
  Texture2DPixelFormat pixelFormat;

  if (CGImageGetColorSpace(image)) {
    if(hasAlpha) {
      pixelFormat = kTexture2DPixelFormat_RGBA8888;
    } else {
      pixelFormat = kTexture2DPixelFormat_RGB565;
    }
  } else {  // NOTE: No colorspace means a mask image
    pixelFormat = kTexture2DPixelFormat_A8;
  }
  
  ScreenSize imageSize = screen_size_make(CGImageGetWidth(image), CGImageGetHeight(image));
  CGAffineTransform transform = CGAffineTransformIdentity;
  
  NSUInteger width = imageSize.width;

  if ((width != 1) && (width & (width - 1))) {
    NSUInteger i = 1;
    while ((sizeToFit ? 2 * i : i) < width) {
      i *= 2;
    }
    width = i;
  }
  NSUInteger height = imageSize.height;
  if ((height != 1) && (height & (height - 1))) {
    NSUInteger i = 1;
    while ((sizeToFit ? 2 * i : i) < height) {
      i *= 2;
    }
    height = i;
  }
  while ((width > kMaxTextureSize) || (height > kMaxTextureSize)) {
    width /= 2;
    height /= 2;
    transform = CGAffineTransformScale(transform, 0.5, 0.5);
    imageSize.width *= 0.5;
    imageSize.height *= 0.5;
  }
  
  CGContextRef context = NULL;
  void *data = NULL;
  CGColorSpaceRef colorSpace = NULL;

  switch(pixelFormat) {    
    case kTexture2DPixelFormat_RGBA8888:
      colorSpace = CGColorSpaceCreateDeviceRGB();
      data = malloc(height * width * 4);
      context = CGBitmapContextCreate(data, width, height, 8, 4 * width, colorSpace,
                                      kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
      CGColorSpaceRelease(colorSpace);
      break;
    case kTexture2DPixelFormat_RGB565:
      colorSpace = CGColorSpaceCreateDeviceRGB();
      data = malloc(height * width * 4);
      context = CGBitmapContextCreate(data, width, height, 8, 4 * width, colorSpace,
                                      kCGImageAlphaNoneSkipLast | kCGBitmapByteOrder32Big);
      CGColorSpaceRelease(colorSpace);
      break;
      
    case kTexture2DPixelFormat_A8:
      data = malloc(height * width);
      context = CGBitmapContextCreate(data, width, height, 8, width, NULL, kCGImageAlphaOnly);
      break;        
    default:
      [NSException raise:NSInternalInconsistencyException format:@"Invalid pixel format"];
  }
  
  
  CGContextClearRect(context, CGRectMake(0, 0, width, height));
  CGContextTranslateCTM(context, 0, height - imageSize.height);
  
  if (!CGAffineTransformIsIdentity(transform)) {
    CGContextConcatCTM(context, transform);
  }
  CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)),
                     image);
  //Convert "RRRRRRRRRGGGGGGGGBBBBBBBBAAAAAAAA" to "RRRRRGGGGGGBBBBB"
  if (pixelFormat == kTexture2DPixelFormat_RGB565) {
    void *tempData = malloc(height * width * 2);
    unsigned int *inPixel32 = (unsigned int*)data;
    unsigned short *outPixel16 = (unsigned short*)tempData;
    for (NSUInteger i = 0; i < width * height; ++i, ++inPixel32)
      *outPixel16++ = ((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) |
                      ((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) |
                      ((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);
    free(data);
    data = tempData;
    
  }
  Texture2D texture(data, pixelFormat, width, height, imageSize, name);

  CGContextRelease(context);
  free(data);
  return texture;
}
