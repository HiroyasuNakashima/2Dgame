#pragma once
#include"libOne.h"
#include"DATA.h"
#include"MAPIMG.h"
#include"ANIMATION.h"

class CONTAINER {
public:
	CONTAINER();
	~CONTAINER();
	//ファイルからデータを読み込む
	void loadData(const char* filename);
	//アクセッサ
	DATA& data(const char* name);
private:
	DATA** Data = 0;
	int NumData = 0;
	char* Buffer = 0;
	unsigned int Size = 0;
};