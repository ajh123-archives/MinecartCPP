#include <nlohmann/json.hpp>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <minecart.h>
#include <mc_string_utils.h>

#include <fstream>

#include "project.h"
using json = nlohmann::json;

minecart::editor::project::Project minecart::editor::project::ParseProject(nlohmann::json data, std::string filePath) {
	minecart::editor::project::Project project;
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


nlohmann::json minecart::editor::project::SerialiseProject(minecart::editor::project::Project project) {
	json data;
	data["name"] = project.name;
	data["authors"] = project.authors;
	data["scripts"] = project.scripts;
	return data;
}

void minecart::editor::project::OpenProjectUI(minecart::editor::project::Project *project, bool *p_open) {
	ImGui::Begin("Project Settings", p_open);

	ImGui::InputText("Project Name", &project->name);

	std::string authors = minecart::utils::JoinStringVector("\n", project->authors);
	if (ImGui::InputTextMultiline("Project Authors", &authors)) {
		project->authors = minecart::utils::SplitStringToVector('\n', authors);
	}

	if (ImGui::Button("Save")) {
		json data = minecart::editor::project::SerialiseProject(*project);
		std::string output = data.dump(4);
		std::ofstream f(project->projectSettingsPath);
		f << data;
		f.close();
		*p_open = false;
	}
	ImGui::SameLine();
	if (ImGui::Button("Close")) {
		*p_open = false;
	}

	ImGui::End();
}
