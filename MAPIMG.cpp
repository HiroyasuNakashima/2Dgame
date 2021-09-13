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

//�摜�����A�t�@�C�����A�摜�T�C�Y
void MAPIMG::create(int y, const char* filename, int chipsize) {
	//�摜���̔z����m��
	int col = y / chipsize;
	Images = new int[col];
	//�摜�ǂݍ���
	int allImg = loadImage(filename);
	for (int i = 0; i < col; i++) {
		Images[i] = cutImage(allImg, 0, chipsize * i, chipsize, chipsize);
	}
}

// �摜�����A�摜�����A�t�@�C����
void MAPIMG::animCreate(int x, int y, const char* filename, int chipsize) {
	//�摜���̔z����m��
	int row = x / chipsize;
	int col = y / chipsize;
	NumImages = row * col;
	Images = new int[NumImages];
	//�摜�ǂݍ���
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

	//�eanim�摜���Ƃɕ�����
	//�v�f�����m��
	AnimImage1 = new int[row];
	AnimImage2 = new int[row];
	AnimImage3 = new int[row];
	AnimImage4 = new int[row];
	AnimImage5 = new int[row];

	//�e�摜���i�[
	n = 0;
	if (n < NumImages) {
		//�摜1
		for (int i = 0; i < row; i++) {
			AnimImage1[i] = Images[n];
			n++;
		}
		//�摜2
		for (int i = 0; i < row; i++) {
			AnimImage2[i] = Images[n];
			n++;
		}
		//�摜3
		for (int i = 0; i < row; i++) {
			AnimImage3[i] = Images[n];
			n++;
		}
		//�摜4
		for (int i = 0; i < row; i++) {
			AnimImage4[i] = Images[n];
			n++;
		}
		//�摜5
		for (int i = 0; i < row; i++) {
			AnimImage5[i] = Images[n];
			n++;
		}
	}
}

#include"memLeakPlace_End.h"