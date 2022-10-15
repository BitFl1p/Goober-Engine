#pragma once
#include "Create1.h"
#include "Windows.h"
#include "SDL_image.h"
#include "SDL.h"
#include <map>
#include <GLFW/glfw3.h>
#include <time.h>
#include <vector>
using namespace std;
namespace Create1 {
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
        Vector3 operator+=(Vector3 other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator-=(Vector3 other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        Vector3 operator+(Vector3 other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator-(Vector3 other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        
        Vector3 operator+=(float other) {
            return Vector3(x + other, y + other, z + other);
        }
        Vector3 operator-=(float other) {
            return Vector3(x - other, y - other, z - other);
        }
        Vector3 operator+(float other) {
            return Vector3(x + other, y + other, z + other);
        }
        Vector3 operator-(float other) {
            return Vector3(x - other, y - other, z - other);
        }
        Vector3 operator*=(float other) {
            return Vector3(x * other, y * other, z * other);
        }
        Vector3 operator*(float other) {
            return Vector3(x * other, y * other, z * other);
        }
        Vector3 operator/=(float other) {
            return Vector3(x / other, y / other, z / other);
        }
        Vector3 operator/(float other) {
            return Vector3(x / other, y / other, z / other);
        }
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
    class Component {
    public:
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
            scale = Vector3();
        }
        void Update() {} void Start() {}
    };
    class GameObject
    {
    public:
        Transform transform;

        void Update();
        void init();
        GameObject(Transform transform, vector<Component*> components) {
            this->transform = transform;
            this->components = components;
        }
        GameObject(vector<Component*> components) {
            this->transform = Transform();
            this->components = components;
        }
        GameObject() {}
    private:
        vector<Component*> components;
    };
    static Transform camera;
    static float deltaTime;
    static float oldTime;
    class GL
	{
    public:
        GL();
        ~GL();

        void init(const char* title);

        static vector<GameObject> gameObjects;
        static GameObject MakeObject(GameObject obj);
        void handleEvents();
        void update();
        void render();
        void clean();

        bool running() { return isRunning; }
        
        static vector<SDL_Texture*> renderTextures;
        bool isRunning;
        static SDL_Window *window;
        static SDL_Renderer *renderer;
        
    };
    class Sprite : virtual public Component
    {
    public:
        GameObject parent;
        const char* sprite;
        Sprite(GameObject parent, const char* sprite) {
            this->parent = parent;
            this->sprite = sprite;
        }
        SDL_Texture* texture;

        void Update() {}
        void Start() {
            SDL_Surface* surface = IMG_Load(sprite);
            texture = SDL_CreateTextureFromSurface(GL::renderer, surface);
            SDL_FreeSurface(surface);
            GL::renderTextures.emplace_back(texture);
        }
    };
}

