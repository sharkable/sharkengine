/*

 ===== IMPORTANT =====

 This is sample code demonstrating API, technology or techniques in development.
 Although this sample code has been reviewed for technical accuracy, it is not
 final. Apple is supplying this information to help you plan for the adoption of
 the technologies and programming interfaces described herein. This information
 is subject to change, and software implemented based on this sample code should
 be tested with final operating system software and final documentation. Newer
 versions of this sample code may be provid
 ed with future seeds of the API or
 technology. For information about updates to this and other developer
 documentation, view the New & Updated sidebars in subsequent documentation
 seeds.

 =====================

 File: Texture2D.m
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

#include "gameengine/opengl/texture2d.h"

using std::string;

int Texture2D::nameCounter_ = 0;
GLfloat Texture2D::globalAlpha_ = 1;
GLfloat Texture2D::screen_height_ = 480;

Texture2D::Texture2D(const void *data, Texture2DPixelFormat pixelFormat, uint32_t width,
                     uint32_t height, ScreenSize size, string filename, GLuint opengl_id) {
  Init(data, pixelFormat, width, height, size, filename, opengl_id);
}

void Texture2D::SetGlobalAlpha(GLfloat alpha) {
  globalAlpha_ = alpha;
}

void Texture2D::DrawAtPoint(ScreenPoint point) {
  DrawAtPoint(point, 1.f, 1.f, 0.f, 0.f);
}

void Texture2D::DrawAtPoint(ScreenPoint point, GLfloat alpha, GLfloat zoom, GLfloat angle, GLfloat z) {
  assert(opengl_id_);

  // Swap vertical coordinate system.
  point.y = screen_height_ - point.y;

  GLfloat width = (GLfloat)width_ * max_s_,
  height = (GLfloat)height_ * max_t_;

  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, opengl_id_);
  glVertexPointer(3, GL_FLOAT, 0, vertices_);
  glTexCoordPointer(2, GL_FLOAT, 0, coordinates_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
  glTranslatef(point.x + width / 2.0, point.y - height / 2.0, 0.0);
  glScalef(zoom, zoom, 0.0);
  glRotatef(-angle, 0.0, 0.0, 1.0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0, 1.0, 1.0, alpha * globalAlpha_);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::DrawAtPointLeftRatio(ScreenPoint point, GLfloat leftRatio) {
  assert(opengl_id_);

  // Swap vertical coordinate system.
  // TODO make this not screen size dependent.
  point.y = screen_height_ - point.y;

  GLfloat    width = (GLfloat)width_ * max_s_ * leftRatio,
  height = (GLfloat)height_ * max_t_;

  coordinates_[2] = coordinates_[6] = leftRatio * max_s_;

  vertices_[0] = -width/2.0;
  vertices_[1] = -height/2.0;

  vertices_[3] = width/2.0;
  vertices_[4] = -height/2.0;

  vertices_[6] = -width/2.0;
  vertices_[7] = height/2.0;

  vertices_[9] = width/2.0;
  vertices_[10] = height/2.0;

  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, opengl_id_);
  glVertexPointer(3, GL_FLOAT, 0, vertices_);
  glTexCoordPointer(2, GL_FLOAT, 0, coordinates_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTranslatef(point.x + width/2.0, point.y - height/2.0, 0.0);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::DrawAtPointRightRatio(ScreenPoint point, GLfloat rightRatio) {
  assert(opengl_id_);

  // Swap vertical coordinate system.
  point.y = screen_height_ - point.y;

  GLfloat    width = (GLfloat)width_ * max_s_ * rightRatio,
  height = (GLfloat)height_ * max_t_;

  coordinates_[0] = coordinates_[4] = (1.0 - rightRatio) * max_s_;

  vertices_[0] = -width/2.0;
  vertices_[1] = -height/2.0;

  vertices_[3] = width/2.0;
  vertices_[4] = -height/2.0;

  vertices_[6] = -width/2.0;
  vertices_[7] = height/2.0;

  vertices_[9] = width/2.0;
  vertices_[10] = height/2.0;

  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, opengl_id_);
  glVertexPointer(3, GL_FLOAT, 0, vertices_);
  glTexCoordPointer(2, GL_FLOAT, 0, coordinates_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTranslatef(point.x + width/2.0 + (1.0 - rightRatio) * (GLfloat)width_ * max_s_, point.y - height/2.0, 0.0);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void Texture2D::DrawAtPointAngle(ScreenPoint point, GLfloat angle) {
  assert(opengl_id_);

  // Swap vertical coordinate system.
  point.y = screen_height_ - point.y;

  GLfloat    width = (GLfloat)width_ * max_s_,
  height = (GLfloat)height_ * max_t_;

  glLoadIdentity();
  glBindTexture(GL_TEXTURE_2D, opengl_id_);
  glVertexPointer(3, GL_FLOAT, 0, vertices_);
  glTexCoordPointer(2, GL_FLOAT, 0, coordinates_);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTranslatef(point.x + width/2.0, point.y - height/2.0, 0.0);
  glRotatef(-angle, 0.f, 0.f, 1.f);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void Texture2D::Delete() {
  assert(opengl_id_);
  glDeleteTextures(1, &opengl_id_);
  opengl_id_ = 0;
}


#pragma mark - private

void Texture2D::Init(const void *data, Texture2DPixelFormat pixelFormat, uint32_t width,
                     uint32_t height, ScreenSize size, string filename, GLuint opengl_id) {
  GLint saveName;
  filename_ = filename;

  // TODO decide how we're generating names. Do some research.
  if (opengl_id) {
    opengl_id_ = opengl_id;
  } else {
    glGenTextures(1, &opengl_id_);
  }
  //opengl_id_ = ++nameCounter_;

  glGetIntegerv(GL_TEXTURE_BINDING_2D, &saveName);
  glBindTexture(GL_TEXTURE_2D, opengl_id_);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  switch(pixelFormat) {
    case kTexture2DPixelFormat_RGBA8888:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      break;
    case kTexture2DPixelFormat_RGB565:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
      break;
    case kTexture2DPixelFormat_A8:
      glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
      break;
    default:
      break;
      // TODO [NSException raise:NSInternalInconsistencyException format:@""];

  }
  // TODO what is this for?
  glBindTexture(GL_TEXTURE_2D, saveName);

  size_ = size;
  width_ = width;
  height_ = height;
  format_ = pixelFormat;
  max_s_ = size.width / (float)width;
  max_t_ = size.height / (float)height;

  coordinates_[0] = 0;
  coordinates_[1] = max_t_;

  coordinates_[2] = max_s_;
  coordinates_[3] = max_t_;

  coordinates_[4] = 0;
  coordinates_[5] = 0;

  coordinates_[6] = max_s_;
  coordinates_[7] = 0;


  vertices_[0] = -size.width/2.0;
  vertices_[1] = -size.height/2.0;
  vertices_[2] = 0;

  vertices_[3] = size.width/2.0;
  vertices_[4] = -size.height/2.0;
  vertices_[5] = 0;

  vertices_[6] = -size.width/2.0;
  vertices_[7] = size.height/2.0;
  vertices_[8] = 0.0;

  vertices_[9] = size.width/2.0;
  vertices_[10] = size.height/2.0;
  vertices_[11] = 0.0;
}
