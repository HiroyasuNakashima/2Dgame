#include"common.h"
#include"PLAYER.h"
#include"MAP.h"
#include"COLLISON_MAP.h"
#include"memLeakPlace_Start.h"

COLLISION_MAP::COLLISION_MAP(){
	init();
	OBJECT::setCollisionMap(this);
}

COLLISION_MAP::~COLLISION_MAP(){
	SAFE_DELETE_ARRAY(MapData);
}

void COLLISION_MAP::init(){
	NumData = 0;
	//マップ上全ての当たり判定のあるマップを洗い出す
	for (int col = 0; col < Map->numDataColumus(); col++) {
		for (int row = 0; row < Map->numDataRows(); row++) {
			int i = col + row * Map->numDataColumus();
			if (Map->data()[i] == '.') {
				NumData++;
			}
		}
	}
	//配列を確保
	MapData = new VECTOR2[NumData];
}

bool COLLISION_MAP::collisionMap(VECTOR2 pos, int chipsize) {
	//マップの座標取得
	int j = 0;
	if (j < NumData) {
		for (int col = 0; col < Map->numDataColumus(); col++) {
			for (int row = 0; row < Map->numDataRows(); row++) {
				int i = col + row * Map->numDataColumus();
				if (Map->data()[i] == '.') {
					MapData[j].x = Map->chipSize() * col;
					MapData[j].y = Map->chipSize() * row;
					j++;
				}
			}
		}
	}


	//キャラとの距離で当たり判定
	/*for (int i = 0; i < NumData; i++) {
		VECTOR2 a = pos - MapData[i];
		float b = length(a);
		if (b < chipsize) {
			return false;
		}
	}*/
	//ウィンドウの端
	if (pos.x < 0 || pos.x > Map->mapSize().x ||
		pos.y < 0 || pos.y > Map->mapSize().y ) {
		return false;
	}

	return true;
}

bool COLLISION_MAP::collisionCheck(float x, float y){
	int col = (int)x / Map->chipSize();
	int row = (int)y / Map->chipSize();
	//Dataの範囲外は除外
	if ( (col < 0) || (col >= Map->numDataColumus()) || (row < 0) || (row >= Map->numDataRows()) ) {
		return false;
	}
	//当たっているかチェック
	if (Map->data()[col + row * Map->numDataColumus()] == '.') {
		return true;
	}
	return false;
}

bool COLLISION_MAP::collisionCharaLeft(float x, float y){
	bool leftTop = collisionCheck(x, y);
	bool leftBottom = collisionCheck(x, y + Map->chipSize() - 1);
	return leftTop || leftBottom;
}
bool COLLISION_MAP::collisionCharaRight(float x, float y){
	bool rightTop = collisionCheck(x + Map->chipSize() - 1, y);
	bool rightBottom = collisionCheck(x + Map->chipSize() -1, y + Map->chipSize() - 1);
	return rightTop || rightBottom;
}
bool COLLISION_MAP::collisionCharaTop(float x, float y){
	bool topLeft = collisionCheck(x, y);
	bool topRight = collisionCheck(x + Map->chipSize() - 1, y);
	return topLeft || topRight;
}

bool COLLISION_MAP::collisionCharaBottom(float x, float y){
	bool bottomLeft = collisionCheck(x, y + Map->chipSize() - 1);
	bool bottomRight = collisionCheck(x + Map->chipSize() - 1, y + Map->chipSize() - 1);
	return bottomLeft || bottomRight;
}

#include"memLeakPlace_End.h"