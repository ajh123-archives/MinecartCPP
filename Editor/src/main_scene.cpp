#include <minecart.h>

#include <imgui.h>
#include <ImGuiFileDialog.h>

#include <fstream>
#include <nlohmann/json.hpp>

#include <raylib.h>

#include "editor.h"
using json = nlohmann::json;

minecart::editor::Project ParseProject(json data, std::string filePath) {
	minecart::editor::Project project;
	project.loaded = false;
	project.hasError = false;
	project.projectDir = filePath;
	project.name = "";
	project.authors = {};
	project.scripts = {};

	// Load project name
	if (data["name"].is_string()) {
		project.name = data["name"].get<std::string>();
	} else {
		project.hasError = true;
	}
	// Load project authors
	if (data["authors"].is_array()) {
		std::vector<json> authors = data["authors"].get<std::vector<json>>();
		for(int index = 0; index < authors.size(); index++)    {
			if (authors[index].is_string()) {
				project.authors.push_back(authors[index].get<std::string>());
			}
		}
	} else {
		project.hasError = true;
	}
	// Load project scripts
	if (data["scripts"].is_object()) {
		// project.scripts = data["scripts"].get<std::map<std::string, std::string>>();
		std::map<json, json> scripts = data["scripts"].get<std::map<json, json>>();
		for(std::map<json, json>::iterator iter = scripts.begin(); iter != scripts.end(); ++iter) {
			json key =  iter->first;
			if (key.is_string()) {
				if (iter->second.is_string()) {
					std::string keyString = key.get<std::string>();
					std::string valueString = iter->second.get<std::string>();
					project.scripts.emplace(keyString, valueString);
				}
			}
		}
	} else {
		project.hasError = true;
	}

	return project;
}

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
				minecart::editor::Project project = ParseProject(data, filePath);
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
