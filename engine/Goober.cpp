#include <iostream>
#include "SDL2/SDL.h"
#include <map>
#include <utility>
#include "Goober.h"
using namespace std;
using namespace goober;

Gl* Gl::game = nullptr;
Gl::Gl() = default;
Gl::~Gl() = default;
void Gl::Init(const char* title, int x, int y)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        cout << "Subsystems Initialised..." << endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
								  x, y, SDL_WINDOW_SHOWN);
        if (window) cout << "Window Created..." << endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
            cout << "Renderer Created..." << endl;
        }

        isRunning = true;
    }
    else isRunning = false;
}

[[maybe_unused]] void Gl::SetWindowTitle(const char* title) const {
    SDL_SetWindowTitle(window, title);
}

[[maybe_unused]] void Gl::SetWindowPos(Vector2 pos) const {
    SDL_SetWindowPosition(window, (int)pos.x, (int)-pos.y);
}
void Gl::HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
	    switch (event.type) {
	    case SDL_QUIT:
			isRunning = false;
	        break;

	    case SDL_KEYDOWN:
		    cout << "Key Down: " << char(event.key.keysym.sym) << "\n";
			break;

		case SDL_KEYUP:
		    cout << "Key Up: " << char(event.key.keysym.sym) << "\n";
			break;

		default:
			break;

	    }
	}
}
Gl* Gl::Game() {
    if (game == nullptr)
        game = new Gl;
    return game;
}
GameObject::GameObject(Transform transform, vector<Component*> components) {
    this->transform = std::move(transform);
    this->components = std::move(components);
    Gl::Game()->MakeObject(this);
}

GameObject::GameObject(vector<Component*> components) {
    this->transform = Transform();
    this->components = std::move(components);
	Gl::Game()->MakeObject(this);
}

void GameObject::Update() {
    for (Component* comp : this->components) {
        comp->Update();
        if (strcmp(SDL_GetError(), "") != 0)
        {
            cout << SDL_GetError() << endl;
            SDL_ClearError();
        }
    }
}
void GameObject::Start() {
    for (Component* comp : this->components) {
        comp->Start();
        if (strcmp(SDL_GetError(), "") != 0)
        {
            cout << SDL_GetError() << endl;
            SDL_ClearError();
        }
    }
}
void Gl::Start() {
    for (auto obj : Gl::Game()->gameObjects) obj->Start();
}
void Gl::MakeObject(GameObject* obj) {
    Gl::Game()->gameObjects.push_back(obj);
    for (auto comp : obj->components) comp->gameObject = obj;
}
void Gl::Update()
{
    for (GameObject* obj : Gl::Game()->gameObjects) {
        obj->Update();
    }
}
void Gl::Render() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (auto tex : renderTextures) {
        auto* pivot = new SDL_Point();
        pivot->x = tex->rect->w / 2;
        pivot->y = tex->rect->h / 2;
        SDL_RendererFlip flipArgs = SDL_FLIP_NONE;
        if (tex->flipX || tex->flipY) {
            flipArgs = (SDL_RendererFlip)NULL;
            if (tex->flipX) flipArgs = (SDL_RendererFlip)(flipArgs | SDL_FLIP_HORIZONTAL);
            if (tex->flipY) flipArgs = (SDL_RendererFlip)(flipArgs | SDL_FLIP_VERTICAL);
        }

        SDL_RenderCopyEx(renderer, tex->texture, nullptr, tex->rect, tex->gameObject->transform.angle, pivot, flipArgs);

    }
    if (debug) for (auto gameObject : Gl::Game()->gameObjects) {
        auto* collider = gameObject->GetComponent<Collider>();
        if (collider) SDL_RenderDrawRect(Gl::Game()->renderer, collider->rect);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);

}
void Gl::Clean() const {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game quit..." << endl;
}

Vector2& Vector2::operator+=(const Vector2& other) {
    this->x = this->x + other.x;
    this->y = this->y + other.y;
    return *this;
}
Vector2 Vector2::operator+(const Vector2 other) {
    return *this += other;
}
Vector2& Vector2::operator-=(const Vector2& other) {
    this->x = this->x - other.x;
    this->y = this->y - other.y;
    return *this;
}
Vector2 Vector2::operator-(const Vector2 other) {
    return *this -= other;
}
Vector2& Vector2::operator+=(const double& other) {
    this->x = this->x + other;
    this->y = this->y + other;
    return *this;
}
Vector2 Vector2::operator+(const double other) {
    return *this += other;
}
Vector2& Vector2::operator-=(const double& other) {
    this->x = this->x - other;
    this->y = this->y - other;
    return *this;
}
Vector2 Vector2::operator-(const double other) {
    return *this -= other;
}
Vector2& Vector2::operator*=(const double& other) {
    this->x = this->x * other;
    this->y = this->y * other;
    return *this;
}
Vector2 Vector2::operator*(const double other) {
    return *this -= other;
}
Vector2& Vector2::operator/=(const double& other) {
    this->x = this->x * other;
    this->y = this->y * other;
    return *this;
}
Vector2 Vector2::operator/(const double other) {
    return *this -= other;
}
Vector2 Vector2::Lerp(Vector2 from, Vector2 to, double t) {
    Vector2 target = to - from;
    target *= t / 10 * DeltaTime();
    return from + target;
}
Collider::Collider(double w, double h) {
    this->w = w;
    this->h = h;
}
Collider::Collider(double w, double h, bool lock) {
    this->w = w;
    this->h = h;
    locked = lock;
}

void Collider::Update() {
    rect->x = gameObject->transform.TruePosition().x - (rect->w * .5);
    rect->y = gameObject->transform.TruePosition().y - (rect->h * .5);
    rect->w = w * gameObject->transform.scale.x;
    rect->h = h * gameObject->transform.scale.y;
    for (auto gameObject : Gl::Game()->gameObjects) {
        auto* collider = gameObject->GetComponent<Collider>();
        auto* intersect = new SDL_Rect();
        if (collider) if (this != collider && SDL_IntersectRect(this->rect, collider->rect, intersect)) {
            if (!locked) {
                if (intersect->w > intersect->h) {
                    if (intersect->y > collider->rect->y) gameObject->transform.position.y -= intersect->h;
                    else gameObject->transform.position.y += intersect->h;
                }
                else if (intersect->h > intersect->w) {
                    if (intersect->x > collider->rect->x) gameObject->transform.position.x += intersect->w;
                    else gameObject->transform.position.x -= intersect->w;
                }
            }
        }
    }
}
void Sprite::Update() {
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    rect->x = gameObject->transform.TruePosition().x - (w * gameObject->transform.scale.x) / 2;
    rect->y = gameObject->transform.TruePosition().y - (h * gameObject->transform.scale.y) / 2;
    rect->w = w * gameObject->transform.scale.x;
    rect->h = h * gameObject->transform.scale.y;
}
Vector2 Gl::GetScreenSize() const {
    int x, y;
    SDL_GetWindowSize(Gl::window, &x, &y);
    return {(double)x, (double)y};
}
Vector2 Transform::TruePosition() const {
    Vector2 truePos = Vector2();
    Vector2 screen = Gl::Game()->GetScreenSize();
    truePos.x = (position.x - Camera()->position.x) + (screen.x / 2);
    truePos.y = (-position.y + Camera()->position.y) + (screen.y / 2);
    return truePos;
}

[[maybe_unused]] void Sprite::SetImage(const char* spr) {
    sprite = spr;
    texture = IMG_LoadTexture(Gl::Game()->renderer, sprite);
    cout << IMG_GetError() << endl;
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    rect->x = gameObject->transform.TruePosition().x - (w * gameObject->transform.scale.x) / 2;
    rect->y = gameObject->transform.TruePosition().y - (h * gameObject->transform.scale.y) / 2;
    rect->w = w * gameObject->transform.scale.x;
    rect->h = h * gameObject->transform.scale.y;
}
void Sprite::Start() {
    texture = IMG_LoadTexture(Gl::Game()->renderer, sprite);
    cout << IMG_GetError() << endl;
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    rect->x = gameObject->transform.TruePosition().x - (w * gameObject->transform.scale.x) / 2;
    rect->y = gameObject->transform.TruePosition().y - (h * gameObject->transform.scale.y) / 2;
    rect->w = w * gameObject->transform.scale.x;
    rect->h = h * gameObject->transform.scale.y;
    Gl::Game()->renderTextures.emplace_back(this);
}
