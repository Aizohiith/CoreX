#include "../config.hpp"

#if INCLUDE_ImGUI == 1

#include "imgui.h"

bool CoreX::ImGUI::Initilize(GLFWwindow* pp_Window, const char* ps_Version)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(pp_Window, true);
	ImGui_ImplOpenGL3_Init(ps_Version);

	return true;
}
void CoreX::ImGUI::Clear_Buffer()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void CoreX::ImGUI::Render(GLFWwindow* pp_Window)
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

#endif