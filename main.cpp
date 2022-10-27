#include "Create1.h"
using namespace Create;

int main(int argc, char* argv[])
{
    
    GL::Game()->init("Bruh");
    GL::Game()->start();
    double last_tick_time = 0;
    double tick_time = clock();
    while (GL::Game()->running()) {
        tick_time = clock();
        GL::Game()->deltaTime = tick_time - last_tick_time;
        GL::Game()->deltaTime /= 10;
        //cout << *GL::deltaTime << endl;
        last_tick_time = tick_time;
        GL::Game()->handleEvents();
        GL::Game()->update();
        GL::Game()->render();

    }
    GL::Game()->clean();
    return 0;
}