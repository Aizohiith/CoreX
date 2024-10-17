#include "../config.hpp"

#if INCLUDE_ImGUI == 1
#include "imgui.h"

bool CoreX::ImGUI::Initilize(GLFWwindow* pp_Window, const char* ps_Version)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
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

void CoreX::ImGUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#endif