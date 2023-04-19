#ifndef MINECART_SCENE_H
#define MINECART_SCENE_H

#include <string>

namespace minecart {
	namespace engine {
		class Scene {
		protected:
			bool Loaded = false;
		public:
			bool Open = false;

			virtual void Setup() = 0;
			virtual void Shutdown() = 0;
			virtual void Show() = 0;
			virtual void Update() = 0;

			bool Focused = false;
		};
	}
}

#endif // MINECART_SCENE_H
