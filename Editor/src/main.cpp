#include <minecart.h>

#include "editor.h"



int main(int, char**) {
	minecart::engine::SetSence(minecart::editor::GetEditScene());
	return minecart::engine::Run("Minecart Editor", 1100, 650);
}
