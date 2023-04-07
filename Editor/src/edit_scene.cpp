#include <filesystem>

#include <minecart.h>
#include <mc_script.h>

#include <raylib.h>
#include <raymath.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <rlImGui.h>
#include <rlImGuiColors.h>

#include "editor.h"
using json = nlohmann::json;

class EditorScene : public minecart::engine::Scene {
private:
	bool UI_Loaded = false;
	bool ProjectUI = false;
	minecart::editor::project::Project project;
public:
	Camera3D Camera = { 0 };
	void BuildEditorLayout() {
		ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiViewport *viewport = ImGui::GetMainViewport();
		ImGuiID dock = ImGui::GetID("Dockspace");
	    ImGui::DockSpace(dock, ImVec2(0.0f, 0.0f), dockspace_flags);

		if (!this->UI_Loaded) {
			ImGui::DockBuilderRemoveNode(dock); // clear any previous layout
			ImGui::DockBuilderAddNode(dock, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dock, viewport->Size);

			// Define our dock spaces ids
			ImGuiID dock_id_up;
			ImGuiID dock_id_down;
			ImGuiID dock_id_left;
			ImGuiID dock_id_middle;
			ImGuiID dock_id_middle1;
			ImGuiID dock_id_right;

			// Split docks where needed
			ImGui::DockBuilderSplitNode(dock, ImGuiDir_Right, 0.15f, &dock_id_right, &dock_id_middle1);
			ImGui::DockBuilderSplitNode(dock_id_middle1, ImGuiDir_Up, 0.75f, &dock_id_up, &dock_id_down);
			ImGui::DockBuilderSplitNode(dock_id_up, ImGuiDir_Left, 0.15f, &dock_id_left, &dock_id_middle);

			// Dock our windows
			ImGui::DockBuilderDockWindow("Console", dock_id_down);
			ImGui::DockBuilderDockWindow("Main View", dock_id_middle);
			ImGui::DockBuilderDockWindow("Inspector", dock_id_right);
			ImGui::DockBuilderDockWindow("Files", dock_id_left);

			// Finish dock bulder
			ImGui::DockBuilderFinish(dock);
		}
		this->UI_Loaded = true;
	}

	void Init(minecart::editor::project::Project project) {
		if (this->Loaded) {
			this->Shutdown();
			this->UI_Loaded = false;
			this->ProjectUI = false;
			this->Loaded = false;
		}
		this->project = project;
	}

	void Setup() override {
		if (this->Loaded == false) {
			this->ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

			Camera.fovy = 45;
			Camera.up.y = 1;
			Camera.position.y = 3;
			Camera.position.z = -25;

			Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
			GridTexture = LoadTextureFromImage(img);
			UnloadImage(img);
			GenTextureMipmaps(&GridTexture);
			SetTextureFilter(GridTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
			SetTextureWrap(GridTexture, TEXTURE_WRAP_CLAMP);

			const auto entity = minecart::engine::GetRegistry().create();

			if (project.scripts.count("main") == 1) {
				std::filesystem::path dir (this->project.projectDir);
				std::filesystem::path scripts ("Scripts");
				std::filesystem::path file (this->project.scripts["main"]);
				std::filesystem::path full_path = dir / scripts / file;
				minecart::engine::GetRegistry().emplace<minecart::scripting::Script>(entity, full_path.u8string());
			}

			auto view = minecart::engine::GetRegistry().view<minecart::scripting::Script>();
			view.each([](minecart::scripting::Script script) {
				script.Start();
			});

			minecart::engine::GetLogger()->AddLog(LOG_DEBUG, "EDITOR: Edit Scene Loaded");

			this->Loaded = true;
		}
	}

	void Shutdown() override {
		auto view = minecart::engine::GetRegistry().view<minecart::scripting::Script>();
		view.each([](minecart::scripting::Script script) {
			script.Shutdown();
		});

		UnloadRenderTexture(this->ViewTexture);
		UnloadTexture(GridTexture);
	}

	void Show() override {
		ClearBackground(BLACK);
		ImGui::SetNextWindowPos(ImVec2(0, 0));                                                  // always at the window origin
		ImGui::SetNextWindowSize(ImVec2(float(GetScreenWidth()), float(GetScreenHeight())));    // always at the window size

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoBringToFrontOnFocus |                 // we just want to use this window as a host for the menubar and docking
			ImGuiWindowFlags_NoNavFocus |                                                      // so turn off everything that would make it act like a window
			ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_NoBackground;                                                      // we want our game content to show through this window, so turn off the background.

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));                          // we don't want any padding for windows docked to this window frame

		ImGui::Begin("Main", NULL, windowFlags);                                   // show the "window"
		ImGui::PopStyleVar();

		this->BuildEditorLayout();

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Project Settings")) {
					this->ProjectUI = true;
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Close")) {
					minecart::engine::End();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View")) {
				if (ImGui::MenuItem("Reset Layout")) {
					this->UI_Loaded = false;
					this->BuildEditorLayout();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

		ImGui::Begin("Main View", nullptr, ImGuiWindowFlags_NoScrollbar);
		this->Focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);

		ImVec2 size = ImGui::GetContentRegionAvail();

		Rectangle viewRect = { 0 };
		viewRect.x = this->ViewTexture.texture.width / 2 - size.x / 2;
		viewRect.y = this->ViewTexture.texture.height / 2 - size.y / 2;
		viewRect.width = size.x;
		viewRect.height = -size.y;

		// draw the view
		rlImGuiImageRect(&this->ViewTexture.texture, (int)size.x, (int)size.y, viewRect);

		ImGui::End();
		ImGui::PopStyleVar();

		minecart::engine::GetLogger()->Draw("Console");

		std::pair<bool, std::pair<std::string, uint32_t>> fileState = minecart::editor::DirectoryTreeView(project.projectDir, "Files");

		if (fileState.first != 0 || fileState.second.second != 0)
		minecart::engine::GetLogger()->AddLog(LOG_DEBUG, "%i %i %s", fileState.first, fileState.second.second, fileState.second.first.c_str());

		ImGui::Begin("Inspector");

		ImGui::End();

		if (this->ProjectUI) {
			minecart::editor::project::OpenProjectUI(&project, &this->ProjectUI);
		}
	}

	void Update() override {
		if (!Open)
			return;

		auto view = minecart::engine::GetRegistry().view<minecart::scripting::Script>();
		view.each([](minecart::scripting::Script script) {
			script.Update();
		});

		if (IsWindowResized()) {
			UnloadRenderTexture(this->ViewTexture);
			this->ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
		}

		float period = 10;
		float magnitude = 25;

		Camera.position.x = (float)(sinf((float)GetTime() / period) * magnitude);

		BeginTextureMode(this->ViewTexture);
		ClearBackground(SKYBLUE);

		BeginMode3D(Camera);

		// grid of cube trees on a plane to make a "world"
		DrawPlane(Vector3 { 0, 0, 0 }, Vector2{ 50, 50 }, BEIGE); // simple world plane
		float spacing = 4;
		int count = 5;

		for (float x = -count * spacing; x <= count * spacing; x += spacing) {
			for (float z = -count * spacing; z <= count * spacing; z += spacing) {
				Vector3 pos = { x, 0.5f, z };

				Vector3 min = { x - 0.5f,0,z - 0.5f };
				Vector3 max = { x + 0.5f,1,z + 0.5f };

				DrawCube(Vector3{ x, 1.5f, z }, 1, 1, 1, GREEN);
				DrawCube(Vector3{ x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
			}
		}

		EndMode3D();
		EndTextureMode();
	}

	Texture2D GridTexture = { 0 };
};

EditorScene* mainScene = new EditorScene();

minecart::engine::Scene* minecart::editor::GetEditScene(minecart::editor::project::Project project) {
	mainScene->Init(project);
	return mainScene;
}
