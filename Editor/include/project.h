#ifndef MINECART_EDITOR_PROJECT_H
#define MINECART_EDITOR_PROJECT_H

#include <string.h>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include <mc_scene.h>

namespace minecart {
	namespace editor {
		namespace project {
			struct Project {
				std::string projectDir;
				std::string projectSettingsPath;
				std::string name;
				std::vector<std::string> authors;
				std::map<std::string, std::string> scripts;
				bool loaded;
				bool hasError;
			};
			
			Project ParseProject(nlohmann::json data, std::string filePath);
			nlohmann::json SerialiseProject(Project project);
			void OpenProjectUI(Project *project, bool *p_open = (bool *)0);
		}
	}
}

#endif // MINECART_EDITOR_PROJECT_H
