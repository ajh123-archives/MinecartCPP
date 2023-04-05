#include <minecart.h>

#include <imgui.h>
#include <ImGuiFileDialog.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include <raylib.h>

#include "editor.h"
using json = nlohmann::json;

class MainScene : public minecart::engine::Scene {
public:
	void Setup() override {
		if (this->Loaded == false) {
			minecart::engine::GetLogger()->AddLog(LOG_DEBUG, "EDITOR: Main Scene Loaded");

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
				f.close();
				minecart::editor::project::Project project = minecart::editor::project::ParseProject(data, filePath);
				project.projectSettingsPath = filePathName;
				minecart::engine::Scene* editScene = minecart::editor::GetEditScene(project);
				minecart::engine::SetSence(editScene);
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
