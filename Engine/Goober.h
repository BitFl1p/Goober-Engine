#pragma once
#include "Goober.h"
#include "SDL_image.h"
#include "SDL.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <map>

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
	    enum Key {
		    A = 'a', B = 'b', C = 'c', D = 'd', E = 'e', F = 'f',
		    G = 'g', H = 'h', I = 'i', J = 'j', K = 'k', L = 'l',
		    M = 'm', N = 'n', O = 'o', P = 'p', Q = 'q', R = 'r',
		    S = 's', T = 't', U = 'u', V = 'v', W = 'w', X = 'x', Y = 'y', Z = 'z',
		    ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, ZERO = 0,
		    NUM_ONE, NUM_TWO, NUM_THREE, NUM_FOUR, NUM_FIVE, NUM_SIX, NUM_SEVEN, NUM_EIGHT, NUM_NINE, NUM_ZERO,
		    SPACE, L_ALT, R_ALT, L_CTRL, R_CTRL, L_SHIFT, R_SHIFT, TAB, CAPS_LOCK, ESC,
	    };
	private:
	    static map<Key, bool>* keys;
	public:
	    [[maybe_unused]] static bool GetKey(Key key);
    };

    class GL {
    private:
        bool isRunning{};
        GL();
        static GL* game;
    public:
        static GL* Game();
        bool debug = false;
        vector<GameObject*> gameObjects;
        ~GL();
        void Init(const char* title, int x, int y);
        static void MakeObject(GameObject* obj);
        void HandleEvents();
        static void Start();
        static void Update();
        void Render();
        void Clean() const;
        [[nodiscard]] bool running() const { return isRunning; }

	    [[maybe_unused]] void SetWindowTitle(const char* title) const;
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

