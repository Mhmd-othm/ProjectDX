#include "Window.h"
#include <iostream>
int main(int argc, char** argv) {


	Window& win = Window::getInstance();

	if (win.Initialize("DirectX App", 1280, 720)) {
		win.MessageLoop();
		return 0;
	}
	else
	{
		std::cerr << "Failed to create window\n";
	}
	return 1;
}