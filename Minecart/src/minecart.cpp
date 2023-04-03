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

namespace minecart {
	namespace engine {
		//----------------------------------------------------------------------------------
		// Main Enry Point
		//----------------------------------------------------------------------------------
		int run(std::string title, int screenWidth, int screenHeight) {
			// Initialization
			//--------------------------------------------------------------------------------------
			SetConfigFlags(FLAG_WINDOW_RESIZABLE);
			InitWindow(screenWidth, screenHeight, title.c_str());
			rlImGuiSetup(true);

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
			CloseWindow();        // Close window and OpenGL context
			rlImGuiShutdown();
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
	BeginDrawing();
		rlImGuiBegin();

		ClearBackground(RAYWHITE);

		int w = GetScreenWidth();
		int h = GetScreenHeight();
		std::string text = "Congrats! You created your first window!";
		size_t length = text.length();
		DrawText(text.c_str(), (w/2)-length, h/2, 20, LIGHTGRAY);

		ImGui::ShowDemoWindow();
		rlImGuiEnd();
	EndDrawing();
	//----------------------------------------------------------------------------------
}