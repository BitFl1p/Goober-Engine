#include <iostream>
#include "Create1.h"
#include "SDL_image.h"
//#include "Windows.h"
#include "SDL.h"
#include <map>
//#include <GLFW/glfw3.h>
//#include <time.h>
using namespace std;
using namespace Create1;


GL::GL() {}
GL::~GL() {}
SDL_Renderer* GL::renderer;
SDL_Window* GL::window;
void GL::init(const char* title) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystems Initialised!..." << endl;

        SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
        if (window) cout << "Window Created!..." << endl;

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            cout << "Renderer Created!..." << endl;
        }

        

        isRunning = true;
    }
    else isRunning = false;
}

void GL::handleEvents() 
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
        {
            isRunning = false;
            break; 
        }
        default: break;
    }
}
vector<GameObject> GL::gameObjects;
void GameObject::Update() {
    for (auto comp : this->components) (*comp).Update();
}
void GameObject::init() {
    for (auto comp : this->components) (*comp).Start();
}

GameObject GL::MakeObject(GameObject obj) {
    gameObjects.emplace_back(obj);
    obj.init();
    return obj;
}

void GL::update()
{
    for (GameObject obj : gameObjects) {
        obj.Update();
    }
    deltaTime = clock() * .01 - oldTime;
    oldTime = clock() * .01;
}
vector<SDL_Texture*> GL::renderTextures;
void GL::render() {
    SDL_RenderClear(renderer);
    for (SDL_Texture* tex : renderTextures) SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

}
void GL::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game quit!..." << endl;
}