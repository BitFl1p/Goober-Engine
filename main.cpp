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
	double last_tick_time = 0;
	double tick_time = clock();
	while (game->running()) {
		tick_time = clock();
		*GL::deltaTime = tick_time - last_tick_time;
		*GL::deltaTime /= 10;
		//cout << *GL::deltaTime << endl;
		last_tick_time = tick_time;
		game->handleEvents();
		game->update();
		game->render();
		
	}
	game->clean();
	return 0;
}
