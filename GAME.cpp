#include"common.h"
#include"CONTAINER.h"
#include"WINDOW.h"
#include"MAP1.h"
#include"CAMERA.h"
#include"PLAYER.h"
#include"GAME.h"
#include"memLeakPlace_Start.h"

GAME::GAME() {
	C = new CONTAINER;
	W = new WINDOW;
	Map = new MAP1;//
	Player = new PLAYER;
	Camera = new CAMERA;
}
GAME::~GAME() {
	SAFE_DELETE(Camera);
	SAFE_DELETE(Player);
	SAFE_DELETE(Map);
	SAFE_DELETE(W);
	SAFE_DELETE(C);
}
void GAME::proc() {
	Player->update();
	Camera->update();
	clear(COLOR());
	Map->draw();
	Player->draw();
	present();
}

#include"memLeakPlace_End.h"