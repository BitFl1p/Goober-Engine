#include "../../engine/Goober.h"
#include <cmath>
using namespace std;
using namespace goober;


class PlayerInput : virtual public Component {
public:
	double count = 0;
	float speed = 2.5;
	Sprite* sprite = nullptr;

	void Start() override {
		sprite = parent->GetComponent<Sprite>();
		Gl::Game()->debug = true;
	}
	void Update() override {

		Camera()->position = Vector2::Lerp(Camera()->position, parent->transform.position, .5);
		Gl::Game()->SetWindowPos(Camera()->position);
		parent->transform.scale = Vector2(3, 3);
		count += DeltaTime() / 10;
		parent->transform.position.x = sin(count / 100.f) * 500 + 700;
		parent->transform.position.y = cos(count / 100.f) * 500 - 200;
	}
};

GameObject player = GameObject({
	new PlayerInput(),
    new Sprite("../root/sprites/buh.png"),
    new Collider(16, 16, false)
});