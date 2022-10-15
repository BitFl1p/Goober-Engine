#include "Create1.h"
#include <iostream>

using namespace std;
using namespace Create1;


GL* game = nullptr;

int main(int argc, char *argv[])
{
	game = new GL();

	game->init("Bruh");

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}
