#include"libOne.h"
#include"GAME.h"
void gmain() {
	GAME* game = new GAME;
	while (notQuit) {
		game->proc();
    }
	delete game;
}