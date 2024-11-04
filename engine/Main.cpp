#include <SDL2/SDL.h>
#include <cstdlib>
#include "Goober.h"
using namespace goober;

int main(int argc, char* argv[])
{

	Gl::Game()->Init("Bruh", 600, 400);
	Gl::Game()->Start();
    double last_tick_time = 0;
    double tick_time = clock();
    while (Gl::Game()->Running()) {


        tick_time = clock();
	    Gl::Game()->deltaTime = tick_time - last_tick_time;
	    Gl::Game()->deltaTime /= 10;
        //cout << *Gl::deltaTime << endl;
        last_tick_time = tick_time;
	    Gl::Game()->HandleEvents();
	    Gl::Game()->Update();
	    Gl::Game()->Render();
        //if (Input::GetKey(VK_F4 & VK_ALT)) break;
    }
	Gl::Game()->Clean();
    return 0;
}