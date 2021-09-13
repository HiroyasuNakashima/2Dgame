#include"WINDOW.h"
#include"PLAYER.h"
#include"MAP.h"
#include "CAMERA.h"

CAMERA::CAMERA(){
	init();
}

void CAMERA::init(){
}

void CAMERA::update(){
	Px = Player->pos().x;
	Py = Player->pos().y;
	WinX = Px - W->winHalf().x;
	WinY = Py - W->winHalf().y;

	Map->world().x = WinX;
	Map->world().y = WinY;
	Map->update();
}
