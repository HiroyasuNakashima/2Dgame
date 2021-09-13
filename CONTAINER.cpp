#include<stdio.h>
#include"common.h"
#include"DATA.h"
#include"FILE_BUFFER.h"
#include"WINDOW.h"
#include"OBJECT.h"
#include"CHARACTER.h"
#include"CONTAINER.h"
#include"memLeakPlace_Start.h"

CONTAINER::CONTAINER() {
	//�f�[�^�ꗗ�ǂݍ���
	loadData("assets/data/data.txt");

	//�R���e�i��񂪕K�v�ȃN���X�փ|�C���^��n��
	WINDOW::setContainer(this);
	OBJECT::setContainer(this);
	ANIMATION::setContainer(this);
	MAPIMG::setContainer(this);
}
CONTAINER::~CONTAINER() {
	for (int i = 0; i < NumData; i++) {
		SAFE_DELETE(Data[i]);
	}
	SAFE_DELETE_ARRAY(Data);
	NumData = 0;
}

void CONTAINER::loadData(const char* filename) {
	FILE_BUFFER fb(filename);
	while (fb.readString()) {
		if (fb == "d") {
			NumData++;
		}
	}
	//�e�I�u�W�F�N�g�̐������������̂Ń|�C���^�z��m��
	if (NumData)Data = new DATA * [NumData]();
	//�o�b�t�@����R���e�i�̊e�I�u�W�F�N�g�Ƀf�[�^���i�[���Ă���
	int dataIdx = 0;
	fb.restart();//�o�b�t�@���ŏ�����ǂݒ���
	while (fb.readString()) {
		if (fb == "d") {
			Data[dataIdx] = new DATA(fb);
			dataIdx++;
		}
	}
}

DATA& CONTAINER::data(const char* name) {
	int i;
	for (i = 0; i < NumData; i++) {
		if (Data[i]->name() == name) {
			break;
		}
	}
	WARNING(i == NumData, "Data not found", name);
	return *Data[i];
}

#include"memLeakPlace_End.h"