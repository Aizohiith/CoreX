#include "corex/config.hpp"

#if INCLUDE_ImGUI == 1

#include "corex/imgui/imgui.h"

namespace CoreX
{
	namespace ImGUI
	{
		bool Initilize(GLFWwindow* pp_Window, const char* ps_Version)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGui::StyleColorsClassic();

			ImGui_ImplGlfw_InitForOpenGL(pp_Window, true);
			ImGui_ImplOpenGL3_Init(ps_Version);

			return true;
		}
		void Clear_Buffer()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void Render(GLFWwindow* pp_Window)
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				if (pp_Window)
					glfwMakeContextCurrent(pp_Window);
			}
		}

		void Modify_Config_Flags(ImGuiConfigFlags_ pp_Flag, bool pb_Set)
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			if (pb_Set)
				io.ConfigFlags |= pp_Flag;
			else
				io.ConfigFlags &= ~pp_Flag;
		}

	}

}
#endif