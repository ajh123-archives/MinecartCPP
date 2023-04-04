#include <raylib.h>
#include <rlImGui.h>
#include <stdio.h>
#include <string>
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
bool running = true;
entt::registry registry;


entt::registry& minecart::engine::GetRegistry() {
	return registry;
}

void minecart::engine::SetSence(Scene* scene) {
	if (currentScene != nullptr) {
		currentScene->Shutdown();
	}
	currentScene = scene;
}

minecart::logging::Logger* minecart::engine::GetLogger() {
	return logger;
}

void CustomLog(int msgType, const char *text, va_list args) {
	logger->AddLog(msgType, text, args);
}
void minecart::engine::End() {
	running = false;
}
//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int minecart::engine::Run(std::string title, int screenWidth, int screenHeight) {
	// Initialization
	//--------------------------------------------------------------------------------------
	SetTraceLogCallback(CustomLog);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, title.c_str());
	rlImGuiSetup(true);
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsResizeFromEdges = true;

	logger->AddLog(LOG_INFO, "MAIN: Program Loaded");

	if (currentScene != nullptr) {
		currentScene->Setup();
		logger->AddLog(LOG_DEBUG, "MAIN: Scene Loaded");
	}

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
	SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose() && running) {   // Detect window close button or ESC key
		UpdateDrawFrame();
	}
#endif

	// De-Initialization
	//--------------------------------------------------------------------------------------
	if (currentScene != nullptr) {
		currentScene->Shutdown();
	}
	logger->AddLog(LOG_INFO, "MAIN: Program Shutdown");
	rlImGuiShutdown();
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
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
		rlImGuiEnd();
	EndDrawing();
	//----------------------------------------------------------------------------------
}
