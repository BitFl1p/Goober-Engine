#include "Create1.h"
#include "Windows.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;
using namespace Create1;

class PlayerInput : virtual public Component {
public:
	GameObject player;

	PlayerInput(GameObject player) {
		this->player = player;
	}

	void Start() {}
	
	void Update() {
		//camera.position = camera.position + Vector3(0.01, 0.01, 0) * deltaTime;
		if(GetKeyState(VK_UP) & 0x8000) cout << "UP" << endl;
	}
};


GameObject player = GL::MakeObject(GameObject(vector<Component*>{
	new PlayerInput(player),
	new Sprite(player, "")
}));

