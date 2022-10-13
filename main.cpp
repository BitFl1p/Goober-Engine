#include "Create1.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;
using namespace Create1;


void Update();

int main() 
{
	GL::init(Update, "title");
}

void Update() 
{
	camera.position = camera.position + Vector3(0.01, 0.01, 0) * deltaTime;
}
