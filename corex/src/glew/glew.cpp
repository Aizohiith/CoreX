#include "corex/config.hpp"

#if INCLUDE_GLEW == 1
#include "corex/glew/glew.h"
#include "iostream"

bool CoreX::GLEW::Initialize(const GLint& pi_Width, const GLint& pi_Height, const GLint& pi_X, const GLint& pi_Y)
{
	GLenum ll_InitResults = glewInit();
	if (ll_InitResults != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed: " << glewGetErrorString(ll_InitResults) << std::endl;
		return false;
	}

	CoreX::GLEW::Set_Viewport(pi_Width, pi_Height, pi_X, pi_Y);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);     // Enable face culling
	//glCullFace(GL_BACK);        // Cull back faces (default)
	////glFrontFace(GL_CW);        // Specify counter-clockwise winding as front-facing (default)


	return true;
}

void CoreX::GLEW::Clear_Buffer()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CoreX::GLEW::Clear_Buffer(GLint pi_Width, GLint pi_Height)
{
	Set_Viewport(pi_Width, pi_Height, 0, 0);
	Clear_Buffer();
}

void CoreX::GLEW::Set_Viewport(const GLint& pi_Width, const GLint& pi_Height, const GLint& pi_X, const GLint& pi_Y)
{
	glViewport(pi_X, pi_Y, pi_Width, pi_Height);
}
#endif