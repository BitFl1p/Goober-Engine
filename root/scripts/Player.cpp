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
		sprite = gameObject->GetComponent<Sprite>();
		Gl::Game()->debug = true;
	}
	void Update() override {

		Camera()->position = Vector2::Lerp(Camera()->position, gameObject->transform.position, .5);
		Gl::Game()->SetWindowPos(Camera()->position);
		gameObject->transform.scale = Vector2(3, 3);
		count += DeltaTime() / 10;
		gameObject->transform.position.x = sin(count / 100.f) * 500 + 700;
		gameObject->transform.position.y = cos(count / 100.f) * 500 - 200;
	}
};

GameObject player = GameObject({
	new PlayerInput(),
    new Sprite("../root/sprites/buh.png"),
    new Collider(16, 16, false)
});