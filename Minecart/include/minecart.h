#ifndef MINECART_H
#define MINECART_H

#include <string>
#include <raylib.h>
#include <entt/entt.hpp>
#include "mc_logging.h"
#include "mc_scene.h"

namespace minecart {
	namespace engine {
		entt::registry& GetRegistry();
		int Run(std::string title, int screenWidth, int screenHeight);
		void End();
		void SetSence(minecart::engine::Scene* scene);
		minecart::logging::Logger* GetLogger();
	}
}

#endif // MINECART_H
