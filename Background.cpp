#include "Create1.h"
#include <iostream>
using namespace std;
using namespace Create;

class Background : public virtual Component {
public:
	void Start() {}
	int count = 0;
	void Update() 
	{
		parent->transform.scale = Vector2(44, 44);
	}
};

GameObject background = GameObject({
	new Background(),
	new Sprite("background.png"),
	new Collider(1, 1)
	});