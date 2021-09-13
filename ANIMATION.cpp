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

//�摜�����A�摜�����A�t�@�C�����A�摜�T�C�Y�A�؂�ւ��Ԋu���w�肵�A�j���[�V�������쐬
void ANIMATION::create(int x, int y ,const char* filename, int chipsize, int animInterval){
	//�摜���̔z����m��
	int row = x / chipsize;
	int col = y / chipsize;
	NumImages = row * col;
	Images = new int[NumImages];
	//�摜�ǂݍ���
	int allImg = 0;
	allImg = loadImage(filename);
	//�摜���J�b�g����Image�Ɋi�[����
	//�L�����̏ꍇ 0�`2(�O)�A3�`5(��)�A6�`8(�E)�A9�`11(��)
	int n = 0;
	//n = �摜����
	if (n < NumImages) {
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				Images[n] = cutImage(allImg, chipsize * j, chipsize * i, chipsize, chipsize);
				n++;
			}
		}
	}
	//�e�摜�͒��Ԃ̉摜��+1�ǂݍ���ŃA�j��������
	int num = row + 1;//�摜��
	//�e�z����m��
	FrontImages = new int[num];
	BackImages = new int[num];
	LeftImages = new int[num];
	RightImages = new int[num];
	//�O�摜
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
		//���摜
		for (int i = 0; i < num; i++) {
			if (i != row) {
				LeftImages[i] = Images[n];
				n++;
			}
			else {
				LeftImages[i] = Images[n - 2];
			}
		}
		//�E�摜
		for (int i = 0; i < num; i++) {
			if (i != row) {
				RightImages[i] = Images[n];
				n++;
			}
			else {
				RightImages[i] = Images[n - 2];
			}
		}
		//��摜
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
		animCnt %= AnimInterval * numImages;//�Ō�܂ōs������0�ɖ߂�
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