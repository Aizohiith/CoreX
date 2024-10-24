#pragma once
///##################################################################
///In order to use:                                                 #
///    Add: corex/glew/GLEW/include to include dir                  #
///    Add: glew lib or a file from core/glew/GLEW/lib              #
///    Link Flags: glew, opengl                                     #
///    Config: Set INCLUDE_GLEW in corex/congif.hpp                 #
///    MUST BE INCLUDED BEFORE GLFW AND INITIALIZE AFTER GLFW       #
///##################################################################
#include "../config.hpp"

#if INCLUDE_GLEW == 1
#include "GL/glew.h"


namespace CoreX {
	namespace GLEW
	{
		bool Initialize(const GLint& Width = 1024, const GLint& Height = 768, const GLint& X = 0, const GLint& Y = 0);
		void Set_Viewport(const GLint& Width, const GLint& Height, const GLint& X = 0, const GLint& Y = 0);
		
		void Clear_Buffer();
		void Clear_Buffer(GLint Width, GLint Height);
	}
}
#endif