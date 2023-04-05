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
		minecart::engine::Scene* GetMainScene();
		minecart::engine::Scene* GetEditScene(minecart::editor::project::Project project);
	}
}

#endif // MINECART_EDITOR_H
