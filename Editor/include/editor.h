#ifndef MINECART_EDITOR_H
#define MINECART_EDITOR_H

#include <mc_scene.h>

namespace minecart {
	namespace editor {
		minecart::engine::Scene* GetMainScene();
		minecart::engine::Scene* GetEditScene();
	}
}

#endif // MINECART_EDITOR_H
