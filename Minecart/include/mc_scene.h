#ifndef MINECART_SCENE_H
#define MINECART_SCENE_H

#include <string>
#include <raylib.h>
#include "minecart.h"

namespace minecart {
	namespace engine {
		class Scene {
		protected:
			bool Loaded = false;
		public:
			bool Open = false;

			RenderTexture ViewTexture;

			virtual void Setup() = 0;
			virtual void Shutdown() = 0;
			virtual void Show() = 0;
			virtual void Update() = 0;

			bool Focused = false;

			Rectangle ContentRect = { 0 };
		};
	}
}

#endif // MINECART_SCENE_H
