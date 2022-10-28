#include "Create1.h"
#include <iostream>
using namespace std;
using namespace Create;

class Background : public virtual Component {
public:
	void Start() {}
	void Update() 
	{
		parent->transform.position = Vector2(0,-9*44);
		parent->transform.scale = Vector2(44, 44);
	}
};

GameObject background = GameObject({
	new Background(),
	new Sprite("background.png"),
	new Collider(16, 16)
	});