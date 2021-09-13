#include<stdio.h>
#include"common.h"
#include"graphic.h"
#include"CONTAINER.h"
#include"MAPIMG.h"
#include"memLeakPlace_Start.h"
CONTAINER* MAPIMG::C = 0;

MAPIMG::MAPIMG() {
	ChipSize = C->data("MapChipSize");
}
MAPIMG::~MAPIMG(){
	SAFE_DELETE_ARRAY(AnimImage1);
	SAFE_DELETE_ARRAY(AnimImage2);
	SAFE_DELETE_ARRAY(AnimImage3);
	SAFE_DELETE_ARRAY(AnimImage4);
	SAFE_DELETE_ARRAY(AnimImage5);
	SAFE_DELETE_ARRAY(Images);
}

//画像ｘ幅、ファイル名、画像サイズ
void MAPIMG::create(int y, const char* filename, int chipsize) {
	//画像数の配列を確保
	int col = y / chipsize;
	Images = new int[col];
	//画像読み込み
	int allImg = loadImage(filename);
	for (int i = 0; i < col; i++) {
		Images[i] = cutImage(allImg, 0, chipsize * i, chipsize, chipsize);
	}
}

// 画像ｘ幅、画像ｙ幅、ファイル名
void MAPIMG::animCreate(int x, int y, const char* filename, int chipsize) {
	//画像数の配列を確保
	int row = x / chipsize;
	int col = y / chipsize;
	NumImages = row * col;
	Images = new int[NumImages];
	//画像読み込み
	int allImg = loadImage(filename);

	int n = 0;
	if (n < NumImages) {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				Images[n] = cutImage(allImg, chipsize * j, chipsize * i, chipsize, chipsize);
				n++;
			}
		}
	}

	//各anim画像ごとに分ける
	//要素数を確保
	AnimImage1 = new int[row];
	AnimImage2 = new int[row];
	AnimImage3 = new int[row];
	AnimImage4 = new int[row];
	AnimImage5 = new int[row];

	//各画像を格納
	n = 0;
	if (n < NumImages) {
		//画像1
		for (int i = 0; i < row; i++) {
			AnimImage1[i] = Images[n];
			n++;
		}
		//画像2
		for (int i = 0; i < row; i++) {
			AnimImage2[i] = Images[n];
			n++;
		}
		//画像3
		for (int i = 0; i < row; i++) {
			AnimImage3[i] = Images[n];
			n++;
		}
		//画像4
		for (int i = 0; i < row; i++) {
			AnimImage4[i] = Images[n];
			n++;
		}
		//画像5
		for (int i = 0; i < row; i++) {
			AnimImage5[i] = Images[n];
			n++;
		}
	}
}

#include"memLeakPlace_End.h"