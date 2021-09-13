#include"common.h"
#include<stdio.h>
#include"libOne.h"
#include"graphic.h"
#include"CONTAINER.h"
#include"ANIMATION.h"
#include"memLeakPlace_Start.h"
CONTAINER* ANIMATION::C = 0;

ANIMATION::ANIMATION(){
	ChipSize = C->data("CharaChipSize");
}

ANIMATION::~ANIMATION() {
	SAFE_DELETE_ARRAY(FrontImages);
	SAFE_DELETE_ARRAY(BackImages);
	SAFE_DELETE_ARRAY(LeftImages);
	SAFE_DELETE_ARRAY(RightImages);
	SAFE_DELETE_ARRAY(Images);
}

//画像ｘ幅、画像ｙ幅、ファイル名、画像サイズ、切り替え間隔を指定しアニメーションを作成
void ANIMATION::create(int x, int y ,const char* filename, int chipsize, int animInterval){
	//画像数の配列を確保
	int row = x / chipsize;
	int col = y / chipsize;
	NumImages = row * col;
	Images = new int[NumImages];
	//画像読み込み
	int allImg = 0;
	allImg = loadImage(filename);
	//画像をカットしてImageに格納する
	//キャラの場合 0～2(前)、3～5(左)、6～8(右)、9～11(後)
	int n = 0;
	//n = 画像枚数
	if (n < NumImages) {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				Images[n] = cutImage(allImg, chipsize * j, chipsize * i, chipsize, chipsize);
				n++;
			}
		}
	}
	//各画像は中間の画像を+1読み込んでアニメさせる
	int num = row + 1;//画像数
	//各配列を確保
	FrontImages = new int[num];
	BackImages = new int[num];
	LeftImages = new int[num];
	RightImages = new int[num];
	//前画像
	n = 0;
	if (n < NumImages) {
		for (int i = 0; i < num; i++) {
			if (i != row){
				FrontImages[i] = Images[n];
				n++;
			}
			else {
				FrontImages[i] = Images[n - 2];
			}
		}
		//左画像
		for (int i = 0; i < num; i++) {
			if (i != row) {
				LeftImages[i] = Images[n];
				n++;
			}
			else {
				LeftImages[i] = Images[n - 2];
			}
		}
		//右画像
		for (int i = 0; i < num; i++) {
			if (i != row) {
				RightImages[i] = Images[n];
				n++;
			}
			else {
				RightImages[i] = Images[n - 2];
			}
		}
		//後画像
		for (int i = 0; i < num; i++) {
			if (i != row) {
				BackImages[i] = Images[n];
				n++;
			}
			else {
				BackImages[i] = Images[n - 2];
			}
		}
	}
	AnimInterval = animInterval;
}

void ANIMATION::draw(int* animImages, VECTOR2 pos, int animCnt, int numImages, COLOR color){
	
	int i = 0;
	if (numImages > 1) {
		i = animCnt / AnimInterval % numImages;
		animCnt %= AnimInterval * numImages;//最後まで行ったら0に戻す
	}
	image(animImages[i], pos.x, pos.y);
	COLOR(color.r, color.g, color.b, color.a);
}

int ANIMATION::animInterval() { return AnimInterval; }
int* ANIMATION::frontImage()  { return FrontImages;  }
int* ANIMATION::leftImage()   { return LeftImages;   }
int* ANIMATION::rightImage()  { return RightImages;  }
int* ANIMATION::backImage()   { return BackImages;   }

#include"memLeakPlace_End.h"