#include <SDL.h>
#include <cstdlib>
#include "Goober.h"
using namespace goober;

SDL_Event event;
int main(int argc, char* argv[])
{

	GL::Game()->Init("Bruh", 600, 400);
	GL::Game()->Start();
    double last_tick_time = 0;
    double tick_time = clock();
    while (GL::Game()->running()) {
        tick_time = clock();
        GL::Game()->deltaTime = tick_time - last_tick_time;
        GL::Game()->deltaTime /= 10;
        //cout << *GL::deltaTime << endl;
        last_tick_time = tick_time;
	    GL::Game()->HandleEvents();
	    GL::Game()->Update();
	    GL::Game()->Render();
        //if (Input::GetKey(VK_F4 & VK_ALT)) break;
    }
	GL::Game()->Clean();
    return 0;
}