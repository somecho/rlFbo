#pragma once
#include <glad/glad.h>
#include <raylib.h>

/// A utility class for generating multisampled framebuffers that interfaces
/// with Raylib's `RenderTexture2D`.
class rlFbo {
 public:
  /// Creates the necessary OpenGL structures and instantiate a
  /// `RenderTexture2D` with it.
  rlFbo(int _width, int _height, int format = GL_RGB, int numSamples = 4);

  /// Calls Raylib's `BeginTextureMode` with own `renderTarget`
  void begin();

  /// Calls Raylib's `EndTextureMode`
  void end();

  /// Draws the content of the fbo's color attachment to the main framebuffer
  /// using `glBlitFramebuffer`. This is done because using Raylib's
  /// `DrawTextureRec` does not work with multisampled framebuffers.
  void draw();

  int width, height;

  /// Initialized after the constructor is called.
  RenderTexture2D renderTarget;
};