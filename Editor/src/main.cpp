#include <minecart.h>
#include <raylib.h>
#include <raymath.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <rlImGui.h>
#include <rlImGuiColors.h>

class EditorScene : public minecart::engine::Scene {
private:
	bool UI_Loaded = false;
public:
	Camera3D Camera = { 0 };

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
			this->Loaded = true;
		}
	}

	void Shutdown() override {
		UnloadRenderTexture(this->ViewTexture);
		UnloadTexture(GridTexture);
	}

	void Show() override {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				ImGui::Separator();
				if (ImGui::MenuItem("Close")) {
					minecart::engine::End();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

		ImGui::Begin("3D View", &this->Open, ImGuiWindowFlags_NoScrollbar);
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

		minecart::engine::GetLogger()->Draw("Debug");
	}

	void Update() override {
		if (!Open)
			return;

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



int main(int, char**) {
	minecart::engine::SetSence(new EditorScene());
	return minecart::engine::Run("Minecart Editor", 1100, 650);
}
