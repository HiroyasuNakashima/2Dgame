#pragma once
#include"CHARACTER.h"
class PLAYER_BULLET;

class PLAYER : public CHARACTER{
public:
	PLAYER();
	~PLAYER();
	void init();
	void update();
	void draw();
private:
	int NumBullet;//�e��
	PLAYER_BULLET** Bullet = 0;
};