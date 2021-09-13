#pragma once
#include"VECTOR2.h"
class CONTAINER;

class WINDOW {
public:
	WINDOW();
	static void setContainer(CONTAINER* c) { C = c; }
	VECTOR2 winSize();
	VECTOR2 winHalf();
private:
	int WindowWidth = 0;
	int WindowHeight = 0;
	float WindowHalf_X = 0;//ウィンドウサイズの半分
	float WindowHalf_Y = 0;
	int ScreenSize = 0;
	static CONTAINER* C;
};