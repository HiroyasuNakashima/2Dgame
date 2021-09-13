#pragma once
#include"libOne.h"
#include"DATA.h"
#include"MAPIMG.h"
#include"ANIMATION.h"

class CONTAINER {
public:
	CONTAINER();
	~CONTAINER();
	//�t�@�C������f�[�^��ǂݍ���
	void loadData(const char* filename);
	//�A�N�Z�b�T
	DATA& data(const char* name);
private:
	DATA** Data = 0;
	int NumData = 0;
	char* Buffer = 0;
	unsigned int Size = 0;
};