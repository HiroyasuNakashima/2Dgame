#include "OBJECT.h"
#include"CONTAINER.h"
#include"WINDOW.h"
#include"MAP.h"
#include"PLAYER.h"
CONTAINER* OBJECT::C = 0;
WINDOW* OBJECT::W = 0;
MAP* OBJECT::Map = 0;
PLAYER* OBJECT::Player = 0;
void OBJECT::setContainer(CONTAINER* c) {
	C = c;
}
void OBJECT::setWindow(WINDOW* w) {
	W = w;
}
void OBJECT::setMap(MAP* m) {
	Map = m;
}
void OBJECT::setPlayer(PLAYER* p) {
	Player = p;
}