#ifndef MINECART_BACKEND_H
#define MINECART_BACKEND_H

#include <string>

namespace minecart {
	namespace engine {
		class Backend {
		public:
			virtual bool Setup(std::string title, int screenWidth, int screenHeight) = 0;
			virtual void Shutdown() = 0;
			virtual void Update() = 0;
			virtual void BeginFrame() = 0;
			virtual void EndFrame() = 0;
			virtual int ShouldClose() = 0;
			virtual void EnterSceneMode() = 0;
			virtual void ExitSceneMode() = 0;
			virtual int GetHeight() = 0;
			virtual int GetWidth() = 0;
		};
	}
}

#endif // MINECART_BACKEND_H
