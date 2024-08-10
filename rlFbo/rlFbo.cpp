#include "rlFbo.hpp"

rlFbo::rlFbo(int _width, int _height, int format, int numSamples)
    : width(_width), height(_height) {
  // generate framebuffer and bind it
  GLuint fbo;
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  // generate texture for color attachment and attach to fbo
  GLuint colorAttachment;
  glGenTextures(1, &colorAttachment);
  glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorAttachment);
  glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, numSamples, format, width,
                          height, GL_TRUE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D_MULTISAMPLE, colorAttachment, 0);

  // generate depth buffer and bind it
  GLuint depthBuffer;
  glGenRenderbuffers(1, &depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
  glRenderbufferStorageMultisample(GL_RENDERBUFFER, numSamples,
                                   GL_DEPTH_COMPONENT24, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_RENDERBUFFER, depthBuffer);

  // unbind framebuffer after use
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  renderTarget.id = fbo;
  renderTarget.texture.id = colorAttachment;
  renderTarget.texture.width = width;
  renderTarget.texture.height = height;
  renderTarget.texture.mipmaps = 1;
  renderTarget.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
  renderTarget.depth.id = 0;
  renderTarget.depth.width = width;
  renderTarget.depth.height = height;
  renderTarget.depth.mipmaps = 1;
  renderTarget.depth.format = 0;
}

void rlFbo::begin() { BeginTextureMode(renderTarget); }

void rlFbo::end() { EndTextureMode(); }

void rlFbo::draw() {
  glBindFramebuffer(GL_READ_FRAMEBUFFER, renderTarget.id);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, width, height, 0, 0, width, height,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
