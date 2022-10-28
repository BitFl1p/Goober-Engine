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
    class Sprite;
    struct Vector2 {
    public:
        float x, y;
        Vector2() {
            x = 0;
            y = 0;
        }
        Vector2(float x, float y) {
            this->x = x;
            this->y = y;
        }
        static Vector2 Lerp(Vector2 from, Vector2 to, float t);
        Vector2& operator+=(const Vector2& other);
        Vector2 operator+(Vector2 other);
        Vector2& operator-=(const Vector2& other);
        Vector2 operator-(Vector2 other);
        Vector2& operator+=(const float& other);
        Vector2 operator+(float other); 
        Vector2& operator-=(const float& other);
        Vector2 operator-(float other);
        Vector2& operator*=(const float& other);
        Vector2 operator*(float other); 
        Vector2& operator/=(const float& other);
        Vector2 operator/(float other);

    }; 
    class GameObject;
    class Component {
    public:
        GameObject* parent = 0;
        Component() {}
        virtual void Update() = 0; virtual void Start() = 0;
    };
    class Transform : virtual public Component
    {
    public:
        Vector2 position, scale;
        float angle;
        Transform()
        {
            position = Vector2();
            angle = 0;
            scale = Vector2(1, 1);
        }
        Vector2 TruePos();
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
        GameObject(Transform transform, vector<Component*> components);
        template <typename T> T* GetComponent() {
            for (auto comp : components) {
                if (dynamic_cast<T*>(comp)) return dynamic_cast<T*>(comp);
            }
            return NULL;
        }
        GameObject(vector<Component*> components);

        GameObject() {}

       
    };
    static class Input {
    public:
        static bool GetKey(int key);
    };
    class GL
	{    
    private:
        bool isRunning;
        GL();
        static GL* game;
    public:
        static GL* Game();
        bool debug = false;
        vector<GameObject*> gameObjects;
        ~GL();
        void init(const char* title);
        void MakeObject(GameObject* obj);
        void handleEvents();
        void start();
        void update();
        void render();
        void clean();
        bool running() { return isRunning; }
        vector<Sprite*> renderTextures;
        double deltaTime;
        
        SDL_Renderer* renderer;
        
        SDL_Window* window;
        Vector2 GetScreenSize();

        Transform* camera;
    
    };
    static Transform* Camera() {
        if (GL::Game()->camera == nullptr)
            GL::Game()->camera = new Transform();
        return GL::Game()->camera;
    }

    static double DeltaTime() {
        return GL::Game()->deltaTime;
    }
    /*class Rect {
    public:
        double x1, x2, y1, y2;
        Rect(double x1, double x2, double y1, double y2) {
            this->x1 = x1;
            this->x2 = x2;
            this->y1 = y1;
            this->y2 = y2;
        }
        static bool IsOverlapped(Rect* first, Rect* second) {
            if(first->x1 < second->x1 && first->x2 < second->x1 || first->x1 < second->x2 && first->x2 < second->x2)
            if(first->y1 < second->y1 && first->y2 < second->y1 || first->y1 < second->y2 && first->y2 < second->y2)
        }
    };*/
    class Sprite : virtual public Component
    {
    public:
        bool flipX = false, flipY = false;
        SDL_Texture* texture;
        SDL_Rect* rect = new SDL_Rect();
        const char* sprite;
        void SetImage(const char* spr);
        Sprite(const char* sprite) { this->sprite = sprite; }
        Sprite() {}
        void Update();
        void Start();
    };
    class Collider : virtual public Component {
    public:
        SDL_Rect* rect = new SDL_Rect();
        double w, h;
        bool locked = true;
        Collider(double w, double h);
        Collider(double w, double h, bool lock);
        
        void Update();
        void Start() {}
    };
}

