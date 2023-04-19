#include <stdio.h>
#include <string>
#include "minecart.h"
#include "mc_logging.h"

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame
minecart::engine::Scene* currentScene = nullptr;
minecart::logging::Logger* logger = new minecart::logging::Logger();
bool running = true;
entt::registry registry;
minecart::engine::Backend* mainBackennd;


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

minecart::engine::Backend* minecart::engine::GetBackend() {
	return mainBackennd;
}
//----------------------------------------------------------------------------------
// Main Enry Point
//----------------------------------------------------------------------------------
int minecart::engine::Run(Backend* backend, std::string title, int screenWidth, int screenHeight) {
	// Initialization
	//--------------------------------------------------------------------------------------
	if (!backend->Setup(title, screenWidth, screenHeight)) {
		logger->AddLog(LOG_FATAL, "MAIN: The backend failed to load");
	}
	mainBackennd = backend;
	// Main game loop
	while (!backend->ShouldClose() && running) {   // Detect window close button or ESC key
		UpdateDrawFrame();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	if (currentScene != nullptr) {
		currentScene->Shutdown();
	}
	backend->Shutdown();
	//--------------------------------------------------------------------------------------

	return 0;
}


//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void) {
	// Draw and Update
	//----------------------------------------------------------------------------------
	mainBackennd->Update();
	mainBackennd->BeginFrame();
		// Update / setup
		//----------------------------------------------------------------------------------
		if (currentScene != nullptr) {
			currentScene->Setup();
			currentScene->Update();
		// And draw
			currentScene->Open = true;
			currentScene->Show();
		}
	mainBackennd->EndFrame();
	//----------------------------------------------------------------------------------
}
