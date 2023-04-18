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
			minecart::editor::SetupImGuiStyle();
			minecart::engine::GetLogger()->AddLog(LOG_DEBUG, "EDITOR: Main Scene Loaded");

			this->Loaded = true;
		}
		return;
	}

	void Shutdown() override {
		return;
	}

	minecart::editor::project::Project project;
	void Show() override {
		float w = (float)GetScreenWidth();
		float h = (float)GetScreenHeight();
		ImGui::SetNextWindowPos(ImVec2(0+w/4, 0+h/4));
		ImGui::SetNextWindowSizeConstraints(ImVec2(w/2, h/2), ImVec2(w/2, h/2));

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
				project = minecart::editor::project::ParseProject(data, filePath);
				project.projectSettingsPath = filePathName;
				if (!project.hasError) {
					minecart::engine::Scene* editScene = minecart::editor::GetEditScene(project);
					minecart::engine::SetSence(editScene);
				} else {
					ImGui::OpenPopup("Project Error");
				}
			}

			// close
			ImGuiFileDialog::Instance()->Close();
		}

		if (ImGui::BeginPopupModal("Project Error")) {
			ImGui::Text("There was a problem while loading the project.");
			ImGui::Text("Please check the file '%s'", project.projectSettingsPath.c_str());
			if (ImGui::Button("Close")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
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
