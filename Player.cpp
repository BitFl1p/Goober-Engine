#include "Create1.h"
#include "Windows.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace Create;

class PlayerInput : virtual public Component {
public:
	int count = 0;
	bool goDown = false;
	void Start() { cout << "Start" << endl; }
	void Update() {
		parent->transform.scale = Vector3(3,3,3);
		camera.position = parent->transform.position;
		if(GetKeyState(VK_UP) & 0x8000) parent->transform.position.y -= 5 * DeltaTime();
		if(GetKeyState(VK_DOWN) & 0x8000) parent->transform.position.y += 5 * DeltaTime();
		if(GetKeyState(VK_LEFT) & 0x8000) parent->transform.position.x -= 5 * DeltaTime();
		if(GetKeyState(VK_RIGHT) & 0x8000) parent->transform.position.x += 5 * DeltaTime();
	}
};

GameObject player = GL::MakeObject(new GameObject({
	new PlayerInput(),
	new Sprite("buh.png")
	}));

