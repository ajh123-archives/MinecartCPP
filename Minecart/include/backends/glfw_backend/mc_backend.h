#ifndef MINECART_BACKEND_GLFW_H
#define MINECART_BACKEND_GLFW_H

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "backends/mc_backend.h"
#include "backends/glfw_backend/mc_framebuffer.h"

#define GLSL_VERSION "#version 150"

namespace minecart {
	namespace engine {
		class GLFWBackend : Backend {
		private:
			minecart::engine::FrameBuffer* SceneRenderBuffer;
			minecart::logging::Logger* Logger = minecart::engine::GetLogger();
			GLFWwindow* Window;
		public:
			GLFWBackend() {}
			bool Setup(std::string title, int screenWidth, int screenHeight);
			void Shutdown();
			void Update();
			void BeginFrame();
			void EndFrame();
			int ShouldClose();
			void EnterSceneMode();
			void ExitSceneMode();
			int GetHeight();
			int GetWidth();
			int GetWinPosX();
			int GetWinPosY();
		};
	}
}

#endif // MINECART_BACKEND_GLFW_H
