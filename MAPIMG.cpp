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

//ζAt@CΌAζTCY
void MAPIMG::create(int y, const char* filename, int chipsize) {
	//ζΜzρπmΫ
	int col = y / chipsize;
	Images = new int[col];
	//ζΗέέ
	int allImg = loadImage(filename);
	for (int i = 0; i < col; i++) {
		Images[i] = cutImage(allImg, 0, chipsize * i, chipsize, chipsize);
	}
}

// ζAζAt@CΌ
void MAPIMG::animCreate(int x, int y, const char* filename, int chipsize) {
	//ζΜzρπmΫ
	int row = x / chipsize;
	int col = y / chipsize;
	NumImages = row * col;
	Images = new int[NumImages];
	//ζΗέέ
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

	//eanimζ²ΖΙͺ―ι
	//vfπmΫ
	AnimImage1 = new int[row];
	AnimImage2 = new int[row];
	AnimImage3 = new int[row];
	AnimImage4 = new int[row];
	AnimImage5 = new int[row];

	//eζπi[
	n = 0;
	if (n < NumImages) {
		//ζ1
		for (int i = 0; i < row; i++) {
			AnimImage1[i] = Images[n];
			n++;
		}
		//ζ2
		for (int i = 0; i < row; i++) {
			AnimImage2[i] = Images[n];
			n++;
		}
		//ζ3
		for (int i = 0; i < row; i++) {
			AnimImage3[i] = Images[n];
			n++;
		}
		//ζ4
		for (int i = 0; i < row; i++) {
			AnimImage4[i] = Images[n];
			n++;
		}
		//ζ5
		for (int i = 0; i < row; i++) {
			AnimImage5[i] = Images[n];
			n++;
		}
	}
}

#include"memLeakPlace_End.h"