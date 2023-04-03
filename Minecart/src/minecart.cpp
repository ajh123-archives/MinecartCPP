#include <raylib.h>
#include <rlImGui.h>
#include "minecart.h"
#include "mc_logging.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame
minecart::engine::Scene* currentScene = nullptr;
minecart::logging::Logger* logger = new minecart::logging::Logger();

namespace minecart {
	namespace engine {
		void SetSence(Scene* scene) {
			currentScene = scene;
		}

		minecart::logging::Logger* GetLogger() {
			return logger;
		}
		//----------------------------------------------------------------------------------
		// Main Enry Point
		//----------------------------------------------------------------------------------
		int Run(std::string title, int screenWidth, int screenHeight) {
			// Initialization
			//--------------------------------------------------------------------------------------
			SetConfigFlags(FLAG_WINDOW_RESIZABLE);
			InitWindow(screenWidth, screenHeight, title.c_str());
			rlImGuiSetup(true);

			logger->AddLog("Hello Logging World");

			if (currentScene != nullptr) {
				currentScene->Setup();
			}

		#if defined(PLATFORM_WEB)
			emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
		#else
			SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
			//--------------------------------------------------------------------------------------

			// Main game loop
			while (!WindowShouldClose()) {   // Detect window close button or ESC key
				UpdateDrawFrame();
			}
		#endif

			// De-Initialization
			//--------------------------------------------------------------------------------------
			if (currentScene != nullptr) {
				currentScene->Shutdown();
			}
			rlImGuiShutdown();
			CloseWindow();        // Close window and OpenGL context
			//--------------------------------------------------------------------------------------

			return 0;
		}
	}
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void) {
	// Update
	//----------------------------------------------------------------------------------
	if (currentScene != nullptr) {
		currentScene->Update();
	}

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();
		rlImGuiBegin();
		ClearBackground(WHITE);
		if (currentScene != nullptr) {
			currentScene->Open = true;
			currentScene->Show();
		}
		logger->Draw("Debug");
		rlImGuiEnd();
	EndDrawing();
	//----------------------------------------------------------------------------------
}
