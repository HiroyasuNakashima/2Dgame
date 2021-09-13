#pragma once
#include"OBJECT.h"
#include"CONTAINER.h"
#include"CHARACTER.h"
class ANIMATION;

class CHARACTER : public OBJECT{
public:
	virtual ~CHARACTER();
	virtual void init();
	virtual void update();
	virtual void draw();
	//当たり判定用
	float cTop();
	float cBottom();
	float cLeft();
	float cRight();
	//当たり判定用(キャラの各座標)
	VECTOR2 cLeftTop();
	VECTOR2 cLeftBottom();
	VECTOR2 cRightTop();
	VECTOR2 cRightBottom();
	VECTOR2 cTopLeft();
	VECTOR2 cTopRight();
	VECTOR2 cBottomLeft();
	VECTOR2 cBottomRight();

	VECTOR2 pos() { return Pos; }
	VECTOR2 dir() { return Dir; }
	VECTOR2 world() { return World; }
	int chipSize() { return ChipSize; }
	int* images() { return Images; }
	ANIMATION* anim() { return Anim; }

protected:
	ANIMATION* Anim = 0;
	int NumImages = 0;
	int* Images = 0;//描画する画像達
	int ChipSize = 0;
	int AnimInterval = 0;
	int AnimCnt = 0;
	int Life = 0;
	VECTOR2 Pos;
	VECTOR2 Dir;//Direction
	VECTOR2 World;//World座標
	float Speed = 0;
	COLOR Color;
	float OffsetLeft = 0;
	float OffsetTop = 0;
	float OffsetRight = 0;
	float OffsetBottom = 0;
};