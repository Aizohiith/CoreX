#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW == 1
#include "GL/glew.h"


namespace CoreX 
{
	namespace GLEW
	{
		class Texture
		{
			public:
				inline Texture(GLenum Type, int Width, int Height, GLenum Color_Type = GL_RGB, GLenum Data_Type = GL_UNSIGNED_BYTE, unsigned char* Data = nullptr) : gg_Type(Type), gi_Width(Width), gi_Height(Height) { glGenTextures(1, &gi_ID); Bind(); glTexImage2D(gg_Type, 0, Color_Type, gi_Width, gi_Height, 0, Color_Type, Data_Type, Data); };
				inline ~Texture() { if (gi_ID) { glDeleteTextures(1, &gi_ID); } };

				inline GLuint ID() const { return gi_ID; };
				inline GLenum Type() const { return gg_Type; };

				inline void Activate(GLuint Slot) const { glActiveTexture(GL_TEXTURE0 + Slot);  Bind(); };
				inline void Bind() const { glBindTexture(gg_Type, gi_ID); };
				inline void Unbind() const { glBindTexture(gg_Type, 0); };

				inline void Set_Parameter(GLenum Parameter, GLenum Value) { glTexParameteri(gg_Type, Parameter, Value); };
				inline void Bind_Framebuffer(GLenum Attachment)
				{
					if (gg_Type == GL_TEXTURE_2D)
						glFramebufferTexture2D(GL_FRAMEBUFFER, Attachment, gg_Type, gi_ID, 0);
				}


			protected:
				GLuint gi_ID;
				GLenum gg_Type;
				int gi_Width;
				int gi_Height;
		};
	}
}
#endif
