#include "gui/gui.h"
#include "../imgui/imgui.h"
#include "misc/misc.h"
#include <thread>
#include<cstdio>

using namespace gui;

std::string currentText;
std::string currentFilePath;

bool OpentextFile(const char* filePath) {
	FILE* file = fopen(filePath, "rb");
	if (!file)
		return false;

	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	currentText.resize(fileSize);
	fread(&currentText[0], 1, fileSize, file);
	fclose(file);

	currentFilePath = filePath;
	return true;
}

bool SavetextFile(const char* filePath) {
	FILE* file = fopen(filePath, "wb");
	if (!file)
		return false;

	fwrite(currentText.c_str(), 1, currentText.size(), file);
	fclose(file);

	currentFilePath = filePath;
	return true;
}

void Render()
{
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGui::Begin(
		"Text Editor",
		&isRunning,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_MenuBar
	);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {
				OpentextFile(misc::OpenFileDialog());
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {
				SavetextFile(misc::SaveFileDialog());
			}
			if (ImGui::MenuItem("Close", "Ctrl+Q")) { isRunning = false; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Credits"))
		{
			if (ImGui::MenuItem("Github"))
			{
				
			}
			ImGui::EndMenu();
		}	
		ImGui::EndMenuBar();
	}
	
	static char buffer[10000]; //This is limit of characters in input 
	strcpy_s(buffer, currentText.c_str()); 
	ImGui::InputTextMultiline("##source", buffer, sizeof(buffer), ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_AllowTabInput);
	currentText = buffer; 

	ImGui::End();

}





int __stdcall wWinMain(
	HINSTANCE instance,
	HINSTANCE previousInstance,
	PWSTR arguments,
	int commandShow)
{
	// create gui
	gui::CreateHWindow("Text Editor");
	gui::CreateDevice();
	gui::CreateImGui();

	while (gui::isRunning)
	{
		gui::BeginRender();
		Render();
		gui::EndRender();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();

	return EXIT_SUCCESS;
}


