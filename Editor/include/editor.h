#ifndef MINECART_EDITOR_H
#define MINECART_EDITOR_H

#include <string.h>
#include <vector>
#include <map>

#include <mc_scene.h>

namespace minecart {
	namespace editor {
		minecart::engine::Scene* GetMainScene();
		struct Project {
			std::string projectDir;
			std::string name;
			std::vector<std::string> authors;
			std::map<std::string, std::string> scripts;
			bool loaded;
			bool hasError;
		};
		
		minecart::engine::Scene* GetEditScene(Project project);
	}
}

#endif // MINECART_EDITOR_H
