#ifndef MINECART_EDITOR_H
#define MINECART_EDITOR_H

#include <string.h>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

#include <mc_scene.h>

#include "project.h"

namespace minecart {
	namespace editor {
		void SetupImGuiStyle();
		minecart::engine::Scene* GetMainScene();
		minecart::engine::Scene* GetEditScene(minecart::editor::project::Project project);
		std::pair<bool, std::pair<std::string, uint32_t>> DirectoryTreeView(std::string directoryPath, std::string name);
	}
}

#endif // MINECART_EDITOR_H
