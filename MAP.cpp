#include<stdio.h>
#include"common.h"
#include"CONTAINER.h"
#include"WINDOW.h"
#include"PLAYER.h"
#include"MAP.h"
#include"memLeakPlace_Start.h"

MAP::MAP(){
	//データ
	ChipSize = C->data("MapChipSize");
	Color.r = C->data("MapColorR");
	Color.b = C->data("MapColorB");
	Color.b = C->data("MapColorG");
	Color.a = C->data("MapColorA");
}
MAP::~MAP() {
	SAFE_DELETE(Data);
}
void MAP::loadMap(const char* filename){
	//ファイルを開く
	FILE* fp = 0;
	fopen_s(&fp, filename, "rb");
	WARNING(fp == 0, "マップデータを読み込めません", filename);
	//ファイルサイズを調べる
	fseek(fp, 0L, SEEK_END);
	Size = ftell(fp);
	rewind(fp);
	//リトライ時、Dataは０でないので開放
	SAFE_DELETE(Data);
	//サイズ分のDataを用意する
	Data = new char [Size];
	//1文字ずつ読み込みData[i]に入れていく。同時に列数と行数も求める
	NumDataColumus = 0;
	NumDataRows = 0;
	char c = 0;
	int i = 0;
	while (fscanf_s(fp, "%c", &c, Size) != EOF) {
		if (c != '\n') {
			Data[i] = c;
			i++;
		}
		else {//改行文字の時
			if (NumDataRows == 0) {
				NumDataColumus = i;
			}
			NumDataRows++;
		}
	}
	fclose(fp);
}

void MAP::init() {
	//ワールド座標
	World.x = 0;
	World.y = 0;
	//ワールド座標の最大値
	MaxWorld.x = ChipSize * (NumDataColumus-1) - W->winSize().x;
	MaxWorld.y = ChipSize *  NumDataRows	   - W->winSize().y;
	//マップデータの行列数
	NumDispDataColumus = W->winSize().x / ChipSize + 1;
	NumDispDataRows    = W->winSize().y / ChipSize + 1;

	//OBJECTに情報を渡す
	OBJECT::setMap(this);
}

void MAP::update() {
	AnimCnt++;

	//上下左右の描画限界範囲を設定
	//左
	if (World.x <= 0) {
		World.x = 0;
	}
		//上
	if (World.y <= 0) {
		World.y = 0;
	}
		//右
	if (World.x >= MaxWorld.x) {
		World.x = MaxWorld.x;
	}
		//下
	if (World.y >= MaxWorld.y) {
		World.y = MaxWorld.y;
	}
}

void MAP::draw() {}

void MAP::draw(int* animImages, VECTOR2 pos, int animCnt, int numImages, int animInterval, COLOR color) {

	int i = 0;
	if (numImages > 1) {
		i = animCnt / animInterval % numImages;
		animCnt %= animInterval * numImages;//最後まで行ったら0に戻す
	}
	image(animImages[i], pos.x, pos.y);
	COLOR(color.r, color.g, color.b, color.a);
}


//ブロックとキャラの当たり判定用関数群
//指定した座標が、ブロックの中に入っているかチェックする
bool MAP::collisionCheck(VECTOR2 pos) {
	//ワールド座標が属しているマップDataの列colと行rowを求める
	int col = (int)pos.x / ChipSize;
	int row = (int)pos.y / ChipSize;
	//マップ範囲外は除外
	if ((col < 0) || (col >= NumDataColumus) || (row < 0) || (row >= NumDataRows)) {
		return false;
	}
	//ブロックに食い込んでいるか判定
	if (Data[col + row * NumDataColumus] == '.') {
		return true;
	}
	return false;
}
//ブロックとキャラの左辺が重なってないか
bool MAP::collisionCheckCharaLeft(VECTOR2 lefttop, VECTOR2 leftbottom) {
	bool leftTop = collisionCheck(lefttop);
	bool leftBottom = collisionCheck(leftbottom);
	return leftTop || leftBottom;
}
//ブロックとキャラの右辺が重なってないか
bool MAP::collisionCheckCharaRight(VECTOR2 righttop, VECTOR2 rightbottom) {
	bool rightTop = collisionCheck(righttop);
	bool rightBottom = collisionCheck(rightbottom);
	return rightTop || rightBottom;
}
//ブロックとキャラの上辺が重なってないか
bool MAP::collisionCheckCharaTop(VECTOR2 topleft, VECTOR2 topright) {
	bool topLeft = collisionCheck(topleft);
	bool topRight = collisionCheck(topright);
	return topLeft || topRight;
}
//ブロックとキャラの下辺が重なってないかまたは、接しているか
bool MAP::collisionCheckCharaBottom(VECTOR2 bottomleft, VECTOR2 bottomright) {
	bool bottomLeft = collisionCheck(bottomleft);
	bool bottomRight = collisionCheck(bottomright);
	return bottomLeft || bottomRight;
}

float MAP::mDispLeft()	 { return World.x; }
float MAP::mDispRight()	 { return World.x + W->winSize().x; }
float MAP::mDispTop()	 { return World.y; }
float MAP::mDispBottom() { return World.y + W->winSize().y; }

#include"memLeakPlace_End.h"