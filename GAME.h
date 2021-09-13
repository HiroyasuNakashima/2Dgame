#pragma once
class CONTAINER;
class WINDOW;
class CAMERA;
class MAP1;
class PLAYER;
class CHARA_MANAGER;

class GAME {
public:
	GAME();
	~GAME();
	void proc();
private:
	CONTAINER* C = 0;
	WINDOW* W = 0;
	CAMERA* Camera = 0;
	MAP1* Map = 0;
	PLAYER* Player = 0;
	CHARA_MANAGER* Charas = 0;
};