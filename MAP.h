#include"VECTOR2.h"
#include"MAPIMG.h"
#include"OBJECT.h"
#include"COLOR.h"
class CONTAINER;

class MAP : public  OBJECT{
public:
	MAP();
	~MAP();
	void loadMap(const char* filename);
	void init();
	void update();
	void draw(int* animImage, VECTOR2 pos, int animCnt, int numImages, int animInterval, COLOR color);
	virtual void draw();
	//ゲッター、セッター
	int chipSize() { return ChipSize; }
	//カメラで使用
	VECTOR2& world(){ return World; }
	void setWorld(VECTOR2 world) { World = world; }
	//当たり判定用
	bool collisionCheck(VECTOR2 pos);
	//キャラ
	bool collisionCheckCharaLeft(VECTOR2 lefttop, VECTOR2 leftbottom);
	bool collisionCheckCharaRight(VECTOR2 righttop, VECTOR2 rightbottom);
	bool collisionCheckCharaTop(VECTOR2 topleft, VECTOR2 topright);
	bool collisionCheckCharaBottom(VECTOR2 bottomleft, VECTOR2 bottomright);
	//スクリーンの右端
	float mDispLeft();
	float mDispRight();
	float mDispTop();
	float mDispBottom();
protected:
	char* Data = 0;
	unsigned int Size = 0;
	int NumDataColumus = 0;
	int NumDataRows = 0;
	int NumDispDataColumus = 0;//画面表示の列数
	int NumDispDataRows = 0;//画面表示の行数
	VECTOR2 World; //ワールド座標
	VECTOR2 MaxWorld; //画面移動の最大値
	int ChipSize = 0;
	VECTOR2 MapSize = 0;//Mapの大きさ
	int AnimCnt = 0;
	COLOR Color;
};