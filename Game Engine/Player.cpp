#include "Goober.h"
#include <iostream>
#include <math.h>  
using namespace std;
using namespace Goober;


class PlayerInput : virtual public Component {
public:
	float count = 0;
	float speed = 2.5;
	Sprite* sprite;
	void Start()
	{
		sprite = parent->GetComponent<Sprite>();
		GL::Game()->debug = true;

		GL::Game()->SetWindowTitle("penis");
	}
	void Update() {

		Camera()->position = Vector2::Lerp(Camera()->position, parent->transform.position, .5);
		GL::Game()->SetWindowPos(Camera()->position);
		parent->transform.scale = Vector2(3, 3);
		count += DeltaTime() / 10;
		//parent->transform.scale += sin(count);
		//parent->transform.angle += 5 * DeltaTime();
		if (Input::GetKey(VK_UP)) parent->transform.position.y += speed * DeltaTime();
		if (Input::GetKey(VK_DOWN)) parent->transform.position.y -= speed * DeltaTime();
		if (Input::GetKey(VK_LEFT)) parent->transform.position.x -= speed * DeltaTime();
		if (Input::GetKey(VK_RIGHT)) parent->transform.position.x += speed * DeltaTime();
	}
};

GameObject player = GameObject(
	{
		new PlayerInput(),
		new Sprite("Assets\\Images\\buh.png"),
		new Collider(16, 16, false)
	});

