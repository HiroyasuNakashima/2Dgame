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
	//データ一覧読み込み
	loadData("assets/data/data.txt");

	//コンテナ情報が必要なクラスへポインタを渡す
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
	//各オブジェクトの数が分かったのでポインタ配列確保
	if (NumData)Data = new DATA * [NumData]();
	//バッファからコンテナの各オブジェクトにデータを格納していく
	int dataIdx = 0;
	fb.restart();//バッファを最初から読み直す
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