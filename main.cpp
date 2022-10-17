#include "Create1.h"
#include <iostream>

using namespace std;
using namespace Create;


GL* game = nullptr;
int main(int argc, char *argv[])
{
	GL* game = new GL();
	game->init("Bruh");
	game->start();
	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
}
