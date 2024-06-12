#include "../Engine/Goober.h"
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
		GL::Game()->debug = true;
	}
	void Update() override {

		Camera()->position = Vector2::Lerp(Camera()->position, parent->transform.position, .5);
		GL::Game()->SetWindowPos(Camera()->position);
		parent->transform.scale = Vector2(3, 3);
		count += DeltaTime() / 10;
		parent->transform.position.x = sin(count / 100.f) * 1000;
		//parent->transform.scale += sin(count);
		//parent->transform.angle += 5 * DeltaTime();
		//if (Input::GetKey(VK_UP)) parent->transform.position.y += speed * DeltaTime();
		//if (Input::GetKey(VK_DOWN)) parent->transform.position.y -= speed * DeltaTime();
		//if (Input::GetKey(VK_LEFT)) parent->transform.position.x -= speed * DeltaTime();
		//if (Input::GetKey(VK_RIGHT)) parent->transform.position.x += speed * DeltaTime();
	}
};

GameObject player = GameObject({
	new PlayerInput(),
    new Sprite("../Assets/Sprites/buh.png"),
    new Collider(16, 16, false)
});

