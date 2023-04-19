#ifndef MINECART_H
#define MINECART_H

#include <string>
#include <entt/entt.hpp>
#include "mc_logging.h"
#include "mc_scene.h"
#include "backends/mc_backend.h"

namespace minecart {
	namespace engine {
		entt::registry& GetRegistry();
		int Run(Backend* Backend, std::string title, int screenWidth, int screenHeight);
		void End();
		void SetSence(minecart::engine::Scene* scene);
		minecart::logging::Logger* GetLogger();
		Backend* GetBackend();
	}
}

#endif // MINECART_H
