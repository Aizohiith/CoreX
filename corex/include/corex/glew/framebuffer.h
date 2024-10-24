#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW == 1
#include "GL/glew.h"


namespace CoreX {
	namespace GLEW
	{
		class Framebuffer
		{
			public:
				inline Framebuffer() { glGenFramebuffers(1, &gi_ID); Bind(); };
				inline ~Framebuffer() { if (gi_ID) { glDeleteFramebuffers(1, &gi_ID); } };
				inline void Bind() const { glBindFramebuffer(GL_FRAMEBUFFER, gi_ID); };
				inline static void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); };
				inline GLuint ID() const { return gi_ID; };
			protected:
				GLuint gi_ID;
		};

	}
}
#endif

