#ifndef MINECART_H
#define MINECART_H

#include <string>
#include <raylib.h>

namespace minecart {
	namespace engine {
		int Run(std::string title, int screenWidth, int screenHeight);

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

		void SetSence(Scene* scene);
	}
}

#endif // MINECART_H
