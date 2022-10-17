#include <iostream>
#include "Create1.h"
#include "SDL_image.h"
//#include "Windows.h"
#include "SDL.h"
#include <map>
//#include <GLFW/glfw3.h>
//#include <time.h>
using namespace std;
using namespace Create;


GL::GL() {}
GL::~GL() {}
void GL::init(const char* title) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        cout << "Subsystems Initialised!..." << endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
        if (window) cout << "Window Created!..." << endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
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
void GameObject::Start() {
    for (auto comp : this->components) (*comp).Start();
}
void GL::start() {
    for (auto obj : gameObjects) obj.Start();
}
vector<SDL_Texture*> GL::renderTextures;
SDL_Renderer* GL::renderer;
GameObject GL::MakeObject(GameObject* obj) {
    gameObjects.emplace_back(*obj);
    for (auto comp : (*obj).components) comp->parent = obj;
    return (*obj);
}
template <class T> bool GameObject::GetComponent(T& component) {
    for (auto comp : components) if (typeid((*comp)).name() == typeid(T).name) {
        component = *comp;
        return true;
    }
    return false;
}
void GL::update()
{
    for (GameObject obj : gameObjects) {
        obj.Update();
    }
    deltaTime = clock() * .01 - oldTime;
    oldTime = clock() * .01;
}
void GL::render() {
    SDL_RenderClear(renderer);
    for (SDL_Texture* tex : renderTextures) 
        SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

}
void GL::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game quit!..." << endl;
}