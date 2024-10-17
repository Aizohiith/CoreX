#include "../config.hpp"

#if INCLUDE_GLEW == 1
#include "glew.h"
#include "iostream"

bool CoreX::GLEW::Initialize(const GLint& pi_Width, const GLint& pi_Height, const GLint& pi_X, const GLint& pi_Y)
{
	GLenum ll_InitResults = glewInit();
	if (ll_InitResults != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed: " << glewGetErrorString(ll_InitResults) << std::endl;
		return false;
	}

	CoreX::GLEW::Set_Viewport(pi_X, pi_Y, pi_Width, pi_Height);

	return true;
}

void CoreX::GLEW::Clear_Buffer()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreX::GLEW::Set_Viewport(const GLint& pi_Width, const GLint& pi_Height, const GLint& pi_X, const GLint& pi_Y)
{
	glViewport(pi_X, pi_Y, pi_Width, pi_Height);
}
#endif