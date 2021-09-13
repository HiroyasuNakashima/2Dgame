#include"CONTAINER.h"
#include"OBJECT.h"
#include"WINDOW.h"
CONTAINER* WINDOW::C = 0;

WINDOW::WINDOW(){
	WindowWidth = C->data("WindowWidth");
	WindowHeight = C->data("WindowHeight");
	WindowHalf_X = WindowWidth / 2;
	WindowHalf_Y = WindowHeight / 2;
	ScreenSize = C->data("ScreenSize");
	window("Game", WindowWidth, WindowHeight, ScreenSize);

	//OBJECT‚Öƒ|ƒCƒ“ƒ^‚ð“n‚·
	OBJECT::setWindow(this);
}

VECTOR2 WINDOW::winSize()
{
	return VECTOR2(WindowWidth, WindowHeight);
}

VECTOR2 WINDOW::winHalf()
{
	return VECTOR2(WindowHalf_X, WindowHalf_Y);
}
