#include "Create1.h"
#include "Windows.h"
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
	//camera.position = camera.position + Vector3(0.01, 0.01, 0) * deltaTime;
	if (GetKeyState('W') & 0x8000) {
		camera.position = camera.position + Vector3(0, 0.01, 0) * deltaTime;
	}
	if (GetKeyState('A') & 0x8000) {
		camera.position = camera.position + Vector3(-0.01, 0, 0) * deltaTime;
	}
	if (GetKeyState('S') & 0x8000) {
		camera.position = camera.position + Vector3(0, -0.01, 0) * deltaTime;
	}
	if (GetKeyState('D') & 0x8000) {
		camera.position = camera.position + Vector3(0.01, 0, 0) * deltaTime;
	}
}
