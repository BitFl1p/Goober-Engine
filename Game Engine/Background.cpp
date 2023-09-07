#include "Goober.h"
#include <iostream>
#include <math.h>  
using namespace std;
using namespace Goober;


class Background : virtual public Component {
public:
	float count = 0;
	float speed = 2.5;
	Sprite* sprite;
	void Start()
	{
		sprite = parent->GetComponent<Sprite>();
		GL::Game()->debug = true;
		parent->transform.position = Vector2(200, -200);
	}
};

GameObject background = GameObject(
	{
		new Background(),
		new Sprite("Assets\\Images\\bah.png")
	});

