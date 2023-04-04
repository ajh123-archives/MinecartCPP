#ifndef MINECART_EDITOR_H
#define MINECART_EDITOR_H

#include <string.h>
#include <vector>
#include <map>

#include <mc_scene.h>

namespace minecart {
	namespace editor {
		minecart::engine::Scene* GetMainScene();
		minecart::engine::Scene* GetEditScene();
		struct Project {
			std::string name;
			std::vector<std::string> authors;
			std::map<std::string, std::string> scripts;
		};
		
	}
}

#endif // MINECART_EDITOR_H
