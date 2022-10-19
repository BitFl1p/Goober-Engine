#pragma once
#include "Create1.h"
#include "Windows.h"
#include "SDL_image.h"
#include "SDL.h"
#include <time.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
namespace Create {
    struct Vector3 {
    public:
        float x, y, z;
        Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }
        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Vector3 Clamp(Vector3 coord, float min, float max) {

            coord.x = coord.x > max ? max : coord.x < min ? min : coord.x;
            coord.y = coord.y > max ? max : coord.y < min ? min : coord.y;
            coord.z = coord.z > max ? max : coord.z < min ? min : coord.z;
            return coord;
        }
        Vector3& operator+=(const Vector3& other);
        Vector3 operator+(Vector3 other);
        Vector3& operator-=(const Vector3& other);
        Vector3 operator-(Vector3 other);
        Vector3& operator+=(const float& other);
        Vector3 operator+(float other); 
        Vector3& operator-=(const float& other);
        Vector3 operator-(float other);
        Vector3& operator*=(const float& other);
        Vector3 operator*(float other); 
        Vector3& operator/=(const float& other);
        Vector3 operator/(float other);

    };
    struct Line {
    public:
        Vector3 start, end;
        Line() {
            start = Vector3();
            end = Vector3();
        }
        Line(Vector3 start, Vector3 end) {
            this->start = start;
            this->end = end;
        }
    }; 
    class GameObject;
    class Component {
    public:
        GameObject* parent = 0;
        virtual void Update() = 0; virtual void Start() = 0;
    };
    class Transform : virtual public Component
    {
    public:
        Vector3 position, eulerAngles, scale;
        Transform()
        {
            position = Vector3();
            eulerAngles = Vector3();
            scale = Vector3(1, 1, 1);
        }
        void Update() {} void Start() {}
    };
    class GameObject
    {
    public:
        double deltaTime;
        Transform transform;
        vector<Component*> components = vector<Component*>{};
        void Update();
        void Start();
        GameObject(Transform transform, vector<Component*> components) {
            this->transform = transform;
            this->components = components;
        }
        GameObject(vector<Component*> components) {
            this->transform = Transform();
            this->components = components;
        }
        GameObject() {}
       
        template <class T> bool GetComponent(T& component);
    };
    static Transform camera;
   
    class GL
	{
    public:
        GL();
        ~GL();

        void init(const char* title);

        static vector<GameObject> gameObjects;
        static GameObject MakeObject(GameObject* obj);
        void handleEvents();
        void start();
        void update();
        void render();
        void clean();

        bool running() { return isRunning; }
        static map<SDL_Texture*, SDL_Rect*> renderTextures;
        static double* deltaTime;
        
        static SDL_Renderer* renderer;
        
        static SDL_Window* window;
    private:
        
        bool isRunning;
        
    };
    static double DeltaTime() {
        return *GL::deltaTime;
    }
    class Sprite : virtual public Component
    {
    public:
        SDL_Texture* texture;
        SDL_Rect* rect = new SDL_Rect();
        const char* sprite;
        Sprite(const char* sprite) {
            this->sprite = sprite;
        }
        

        void Update() {
            int w, h, ww, wh;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h); 
            SDL_GetWindowSize(GL::window, &ww, &wh);
            rect->x = parent->transform.position.x - camera.position.x;
            rect->y = parent->transform.position.y - camera.position.y;
            rect->w = w * parent->transform.scale.x;
            rect->h = h * parent->transform.scale.y;
            GL::renderTextures[texture] = rect;
        }
        void Start() {
            SDL_Surface* surface = IMG_Load(sprite);
            cout << IMG_GetError() << endl;
            texture = SDL_CreateTextureFromSurface(GL::renderer, surface);
            SDL_FreeSurface(surface);
            int w, h, ww, wh;
            SDL_QueryTexture(texture, NULL, NULL, &w, &h);
            SDL_GetWindowSize(GL::window, &ww, &wh);
            rect->x = parent->transform.position.x - camera.position.x;
            rect->y = parent->transform.position.y - camera.position.y;
            rect->w = w * parent->transform.scale.x;
            rect->h = h * parent->transform.scale.y;
            GL::renderTextures.emplace(texture, rect);
        }
    };
}

