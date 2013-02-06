#ifndef __FRAMEBUFFERGL_HPP__
#define __FRAMEBUFFERGL_HPP__

#include <GL/glew.h>

namespace renderer{

struct FramebufferGL
{
	GLuint fbo;
	GLuint * colorTexId;
	GLuint   depthTexId;
	GLenum * drawBuffers;
	int width;
	int height;
	int outCount;
};

int  build_framebuffer(FramebufferGL & fb, int width, int height, int outCount);
int  destroy_framebuffer(FramebufferGL & fb);

}//namespace renderer

#endif
