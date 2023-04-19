#include <minecart.h>
#include <backends/glfw_backend/mc_backend.h>

#include "editor.h"

int main(int, char**) {
	minecart::engine::SetSence(minecart::editor::GetMainScene());
	minecart::engine::GLFWBackend* backend = new minecart::engine::GLFWBackend();
	return minecart::engine::Run((minecart::engine::Backend*) backend, "Minecart Editor", 1100, 650);
}
