#pragma once
#include"COLOR.h"

class CONTAINER;
class VECTOR2;

class ANIMATION {
public:
	ANIMATION();
	~ANIMATION();
	void create(int x, int y, const char* filename, int chipsize, int animInterval);
	void draw(int* animImage, VECTOR2 pos, int animCnt, int numImages, COLOR color);
	int animInterval();
	int* frontImage();
	int* leftImage();
	int* rightImage();
	int* backImage();
	static void setContainer(CONTAINER* c) { C = c; }
private:
	int NumImages = 0;
	int* Images = 0;
	int* FrontImages = 0;
	int* LeftImages = 0;
	int* RightImages = 0;
	int* BackImages = 0;
	int AnimDirction = 0;//アニメの向きの数
	int AnimDirImages = 0;//一つのアニメの向きを読み込む数
	int AnimInterval = 1;
	int ChipSize = 0;
	static CONTAINER* C;
};