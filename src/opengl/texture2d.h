/*
 
 ===== IMPORTANT =====
 
 This is sample code demonstrating API, technology or techniques in development.
 Although this sample code has been reviewed for technical accuracy, it is not
 final. Apple is supplying this information to help you plan for the adoption of
 the technologies and programming interfaces described herein. This information
 is subject to change, and software implemented based on this sample code should
 be tested with final operating system software and final documentation. Newer
 versions of this sample code may be provided with future seeds of the API or
 technology. For information about updates to this and other developer
 documentation, view the New & Updated sidebars in subsequent documentation
 seeds.
 
 =====================
 
 File: Texture2D.h
 Abstract: Creates OpenGL 2D textures from images or text.
 
 Version: 1.6
 
 Disclaimer: IMPORTANT:  This Apple software is supplied to you by Apple Inc.
 ("Apple") in consideration of your agreement to the following terms, and your
 use, installation, modification or redistribution of this Apple software
 constitutes acceptance of these terms.  If you do not agree with these terms,
 please do not use, install, modify or redistribute this Apple software.
 
 In consideration of your agreement to abide by the following terms, and subject
 to these terms, Apple grants you a personal, non-exclusive license, under
 Apple's copyrights in this original Apple software (the "Apple Software"), to
 use, reproduce, modify and redistribute the Apple Software, with or without
 modifications, in source and/or binary forms; provided that if you redistribute
 the Apple Software in its entirety and without modifications, you must retain
 this notice and the following text and disclaimers in all such redistributions
 of the Apple Software.
 Neither the name, trademarks, service marks or logos of Apple Inc. may be used
 to endorse or promote products derived from the Apple Software without specific
 prior written permission from Apple.  Except as expressly stated in this notice,
 no other rights or licenses, express or implied, are granted by Apple herein,
 including but not limited to any patent rights that may be infringed by your
 derivative works or by other works in which the Apple Software may be
 incorporated.
 
 The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
 WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
 WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
 COMBINATION WITH YOUR PRODUCTS.
 
 IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR
 DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF
 CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF
 APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 Copyright (C) 2008 Apple Inc. All Rights Reserved.
 
 */

#ifndef AIRHOCKEY_OPENGL_TEXTURE2D_H_
#define AIRHOCKEY_OPENGL_TEXTURE2D_H_

#import <OpenGLES/ES1/gl.h>
#import <string>
using namespace std;

// TODO this is overreaching... this shouldn't know about the game engine.
#include "gameengine/coordinate_types.h"

#define kMaxTextureSize   1024

typedef enum {
  kTexture2DPixelFormat_Automatic = 0,
  kTexture2DPixelFormat_RGBA8888,
  kTexture2DPixelFormat_RGB565,
  kTexture2DPixelFormat_A8,
} Texture2DPixelFormat;

/*
 This class allows to easily create OpenGL 2D textures from images, text or raw data.
 The created Texture2D object will always have power-of-two dimensions.
 Depending on how you create the Texture2D object, the actual image area of the texture might be
 smaller than the texture dimensions i.e. "contentSize" != (pixelsWide, pixelsHigh) and
 (maxS, maxT) != (1.0, 1.0).
 Be aware that the content of the generated textures will be upside-down!
 */
class Texture2D {
 public:
  Texture2D() : name_(0) { }
  Texture2D(const void *data, Texture2DPixelFormat pixelFormat, uint32_t width, uint32_t height,
            ScreenSize size, string filename);

  static void SetGlobalAlpha(GLfloat alpha);
  void DrawAtPoint(ScreenPoint point);
  void DrawAtPoint(ScreenPoint point, GLfloat alpha, GLfloat zoom, GLfloat angle, GLfloat z);
  void DrawAtPointLeftRatio(ScreenPoint point, GLfloat leftRatio);
  void DrawAtPointRightRatio(ScreenPoint point, GLfloat rightRatio);
  void DrawAtPointAngle(ScreenPoint point, GLfloat angle);
  void Delete();
  
  bool loaded() { return name_ != 0; }  // TODO identical to data_loaded
  GLuint name() { return name_; }
  string filename() { return filename_; }
  bool data_loaded() { return name_ != 0; }
  ScreenSize content_size() { return size_; }

 private:
  void Init(const void *data, Texture2DPixelFormat pixelFormat, uint32_t width, uint32_t height,
            ScreenSize size, string filename);

  static int nameCounter_;
  static GLfloat globalAlpha_;
  GLuint name_;
  string filename_;
  ScreenSize size_;
  uint32_t width_;
  uint32_t height_;
  Texture2DPixelFormat format_;
  GLfloat max_s_;
  GLfloat max_t_;
  GLfloat coordinates_[8];
  GLfloat vertices_[12];  
};

#endif
