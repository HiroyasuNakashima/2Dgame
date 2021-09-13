#pragma once
#include"MAP.h"

class MAP1 : public MAP {
public:
	MAP1();
	void draw();
private:
	//‰æ‘œ
	MAPIMG Road1;
	MAPIMG Road2;
	MAPIMG Forest1;
	MAPIMG Mountain1;
	MAPIMG Mountain2;
	MAPIMG Wood1;
	MAPIMG Water1;
};