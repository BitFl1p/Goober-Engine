#pragma once
#include "Goober.h"
#include "SDL_image.h"
#include "SDL.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
namespace Goober {
    class Sprite;
    struct Vector2 {
    public:
        double x, y;
        Vector2() {
            x = 0;
            y = 0;
        }
        Vector2(double x, double y) {
            this->x = x;
            this->y = y;
        }
        static Vector2 Lerp(Vector2 from, Vector2 to, double t);
        Vector2& operator+=(const Vector2& other);
        Vector2 operator+(Vector2 other);
        Vector2& operator-=(const Vector2& other);
        Vector2 operator-(Vector2 other);
        Vector2& operator+=(const double& other);
        Vector2 operator+(double other);
        Vector2& operator-=(const double& other);
        Vector2 operator-(double other);
        Vector2& operator*=(const double& other);
        Vector2 operator*(double other);
        Vector2& operator/=(const double& other);
        Vector2 operator/(double other);

    };
    class GameObject;
    class Component {
    public:
        GameObject* parent = nullptr;
        Component() = default;
        virtual void Update() {}; virtual void Start() {};
    };
    class Transform : virtual public Component
    {
    public:
        Vector2 position, scale;
        double angle;
        Transform()
        {
            position = Vector2();
            angle = 0;
            scale = Vector2(1, 1);
        }
        Vector2 TruePos() const;
        void Update() override {} void Start() override {}
    };
    class GameObject
    {
    public:
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
        explicit GameObject(vector<Component*> components);

        GameObject() = default;


    };
    class Input {
    public:
        //static bool GetKey(int key);
    };
    class GL
    {
    private:
        bool isRunning{};
        GL();
        static GL* game;
    public:
        static GL* Game();
        bool debug = false;
        vector<GameObject*> gameObjects;
        ~GL();
        void init(const char* title);
        static void MakeObject(GameObject* obj);
        void handleEvents();
        static void start();
        static void update();
        void render();
        void clean() const;
        [[nodiscard]] bool running() const { return isRunning; }
        void SetWindowTitle(const char* title) const;
        void SetWindowPos(Vector2 pos) const;
        vector<Sprite*> renderTextures;
        double deltaTime{};

        SDL_Renderer* renderer{};

        SDL_Window* window{};
        Vector2 GetScreenSize() const;

        Transform* camera{};

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
        SDL_Texture* texture = nullptr;
        SDL_Rect* rect = new SDL_Rect();
        const char* sprite{};
        void SetImage(const char* spr);
        explicit Sprite(const char* sprite) : sprite(sprite) {}
        Sprite() = default;
        void Update() override;
        void Start() override;
    };
    class Collider : virtual public Component {
    public:
        SDL_Rect* rect = new SDL_Rect();
        double w, h;
        bool locked = true;
        Collider(double w, double h);
        Collider(double w, double h, bool lock);

        void Update() override;
        void Start() override {}
    };
}

