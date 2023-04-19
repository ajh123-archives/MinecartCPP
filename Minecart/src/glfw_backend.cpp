#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "backends/glfw_backend/mc_backend.h"

static void glfw_error_callback(int error, const char* description) {
	minecart::logging::Logger* logger = minecart::engine::GetLogger();
    logger->AddLog(LOG_ERROR, "GLFW: %i %s", error, description);
}

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

namespace minecart {
	namespace engine {
		bool GLFWBackend::Setup(std::string title, int screenWidth, int screenHeight){
			glfwSetErrorCallback(glfw_error_callback);
			if (!glfwInit())
				return false;

			// Decide GL+GLSL versions
			// GL 3.2 + GLSL 150
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

			this->Window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
			if (this->Window == NULL) {
				this->Logger->AddLog(LOG_FATAL, "GLFW: Unable to initalise window");
				return false;
			}

			glfwMakeContextCurrent(this->Window);
			glfwSwapInterval(1); // Enable vsync

			// Initialize OpenGL loader
			bool err = gladLoadGL() == 0;
			if (err) {
				this->Logger->AddLog(LOG_FATAL, "GLFW: Unable to load Open GL (GLAD)");
				return false;
			}

			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();

			// Setup Platform/Renderer bindings
			ImGui_ImplGlfw_InitForOpenGL(this->Window, true);
			ImGui_ImplOpenGL3_Init(GLSL_VERSION);

			this->Logger->AddLog(LOG_INFO, "GLFW: Program Loaded");
			return true;
		}
		void GLFWBackend::Shutdown(){
			glfwDestroyWindow(this->Window);
			glfwTerminate();
			this->Logger->AddLog(LOG_INFO, "GLFW: Program Finished");
		}
		void GLFWBackend::BeginFrame() {
			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}
		void GLFWBackend::EndFrame() {
			ImGuiIO& io = ImGui::GetIO();
			// Rendering
			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(this->Window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(this->Window);			
		}
		int GLFWBackend::GetWidth() {
			int display_w, display_h;
			glfwGetFramebufferSize(this->Window, &display_w, &display_h);
			return display_w;
		}
		int GLFWBackend::GetHeight() {
			int display_w, display_h;
			glfwGetFramebufferSize(this->Window, &display_w, &display_h);
			return display_h;
		}
		int GLFWBackend::ShouldClose() {
			int close = glfwWindowShouldClose(this->Window);
			return close;
		}
		void GLFWBackend::EnterSceneMode() {
			//Bind the scene Frame Buffer
		}
		void GLFWBackend::ExitSceneMode() {
			//Unbind the frame buffer
		}
		void GLFWBackend::Update() {
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();
		}
	}
}