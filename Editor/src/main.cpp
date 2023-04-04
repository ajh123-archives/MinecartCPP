#include <minecart.h>
#include <mc_testing.h>

int main(int, char**) {
	minecart::engine::SetSence(minecart::testing::GetTestScene());
	return minecart::engine::Run("Minecart Editor", 1100, 650);
}
