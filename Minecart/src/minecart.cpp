#include <raylib.h>
#include <rlImGui.h>
#include "minecart.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame
minecart::engine::Scene* currentScene;

namespace minecart {
	namespace engine {
		void SetSence(Scene* scene) {
			currentScene = scene;
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

			currentScene->Setup();

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
			currentScene->Shutdown();
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
	// TODO: Update your variables here
	//----------------------------------------------------------------------------------

	// Draw
	//----------------------------------------------------------------------------------
	currentScene->Update();
	BeginDrawing();
		rlImGuiBegin();

		ClearBackground(RAYWHITE);

		int w = GetScreenWidth();
		int h = GetScreenHeight();
		std::string text = "Congrats! You created your first window!";
		size_t length = text.length();
		DrawText(text.c_str(), (w/2)-length, h/2, 20, LIGHTGRAY);
		currentScene->Open = true;
		currentScene->Show();
		rlImGuiEnd();
	EndDrawing();
	//----------------------------------------------------------------------------------
}
