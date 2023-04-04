#include <minecart.h>

#include <imgui.h>
#include <ImGuiFileDialog.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include <raylib.h>

#include "editor.h"
using json = nlohmann::json;

minecart::editor::Project ParseProject(json data) {
	minecart::editor::Project project;
	project.authors = {};
	project.scripts = {};

	return project;
}

class MainScene : public minecart::engine::Scene {
public:
	void Setup() override {
		if (this->Loaded == false) {
			this->Loaded = true;
		}
		return;
	}

	void Shutdown() override {
		return;
	}

	void Show() override {
		ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

		ImGui::Begin("Projects", &this->Open);

		if (ImGui::Button("Open Project")) {
			ImGuiFileDialog::Instance()->OpenDialog("ChooseProjectDlgKey", "Choose Project", ".json", ".");
		}

		ImGui::End();

		if (ImGuiFileDialog::Instance()->Display("ChooseProjectDlgKey")) {
			// action if OK
			if (ImGuiFileDialog::Instance()->IsOk()) {
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();

				std::ifstream f(filePathName);
				json data = json::parse(f);
				minecart::editor::Project project = ParseProject(data);
				minecart::engine::GetLogger()->AddLog(LOG_DEBUG, "%s", project.name);
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}
	}

	void Update() override {
		return;
	}
};

MainScene* scene = new MainScene();

minecart::engine::Scene* minecart::editor::GetMainScene() {
	return scene;
}
