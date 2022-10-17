#include "Create1.h"
#include "Windows.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace Create;

class PlayerInput : virtual public Component {
public:
	void Start() { cout << "Start" << endl; }
	void Update() {
		parent->transform.position = Vector3(0, 0, 0);
		if(GetKeyState(VK_UP) & 0x8000) cout << "UP" << endl;
	}
};

GameObject player = GL::MakeObject(new GameObject({
	new PlayerInput(),
	new Sprite("buh.png")
	}));

