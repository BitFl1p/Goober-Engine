#pragma once
#include "Goober.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include <boost/signals2/signal.hpp>

using namespace std;

namespace goober {
    class Sprite;
    struct Vector2 {
    public:
        double x, y;
        Vector2() : x(0), y(0) {}
        Vector2(double x, double y) : x(x), y(y) {}

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
        GameObject* gameObject = nullptr;
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
        [[nodiscard]] Vector2 TruePosition() const;
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

    class Gl {
    private:
        bool isRunning{};
        Gl();
        static Gl* game;
    public:
        static Gl* Game();
        bool debug = false;
        vector<GameObject*> gameObjects;
        ~Gl();
        void Init(const char* title, int x, int y);
        static void MakeObject(GameObject* obj);
        void HandleEvents();
        static void Start();
        static void Update();
        void Render();
        void Clean() const;
        [[nodiscard]] bool Running() const { return isRunning; }

	    [[maybe_unused]] void SetWindowTitle(const char* title) const;
        void SetWindowPos(Vector2 pos) const;
        vector<Sprite*> renderTextures;
        double deltaTime{};

        SDL_Renderer* renderer{};

        SDL_Window* window{};
        [[nodiscard]] Vector2 GetScreenSize() const;

        Transform* camera{};
    };

    static Transform* Camera() {
        if (Gl::Game()->camera == nullptr)
	        Gl::Game()->camera = new Transform();
        return Gl::Game()->camera;
    }

    static double DeltaTime() {
        return Gl::Game()->deltaTime;
    }

    class Sprite : virtual public Component
    {
    public:
        bool flipX = false, flipY = false;
        SDL_Texture* texture = nullptr;
        SDL_Rect* rect = new SDL_Rect();
        const char* sprite{};

	    [[maybe_unused]] void SetImage(const char* spr);
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

