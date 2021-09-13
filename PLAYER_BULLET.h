#pragma once
#include"CHARACTER.h"

class PLAYER_BULLET : public CHARACTER {
public:
	PLAYER_BULLET();
	void init();
	void update();
	void draw();
	int life();
private:
	int Img = 0;
	int Life = 0;
};