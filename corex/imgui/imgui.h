#pragma once
///##################################################################
///In order to use:                                                 #
///    Add: corex/imgui/ImGui/*.cpp to project                      #
///##################################################################
#include "../config.hpp"

#if INCLUDE_ImGUI == 1
#include "ImGui/imgui.h"

#if INCLUDE_GLEW
	#include "GL/glew.h"
	#include "imgui_impl_opengl3.h"
#endif // INCLUDE_GLEW
#if INCLUDE_GLFW
	#include "GLFW/glfw3.h"
	#include "imgui_impl_glfw.h"
#endif // INCLUDE_GLFW

namespace CoreX
{
	namespace ImGUI
	{
		bool Initilize(GLFWwindow* Window, const char* Version = "#version 330");
		void Clear_Buffer();
		void Render();
	}
}
#endif