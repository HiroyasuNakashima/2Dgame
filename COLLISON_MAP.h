#include"OBJECT.h"

class COLLISION_MAP : public OBJECT{
public:
	COLLISION_MAP();
	~COLLISION_MAP();
	void init();
	bool collisionMap(VECTOR2 pos, int chipsize);
	//“–‚½‚è”»’è—p
	bool collisionCheck(float x, float y);
	bool collisionCharaLeft(float x, float y);
	bool collisionCharaRight(float x, float y);
	bool collisionCharaTop(float x, float y);
	bool collisionCharaBottom(float x, float y);
private:
	int NumData = 0;
	VECTOR2* MapData = 0;
};