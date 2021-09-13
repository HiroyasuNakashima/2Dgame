#include"graphic.h"
#include"CONTAINER.h"
#include"MAP1.h"

MAP1::MAP1(){
	//画像作成
	Road1.create(250, "assets/map/road1.png", ChipSize);
	Road2.create(250, "assets/map/road2.png", ChipSize);
	Forest1.create(250, "assets/map/forest1.png", ChipSize);
	Mountain1.create(250, "assets/map/mountain1.png", ChipSize);
	Mountain2.create(250, "assets/map/mountain2.png", ChipSize);
	Wood1.create(250, "assets/map/wood1.png", ChipSize);
	Water1.animCreate(400, 250, "assets/map/water1.png", ChipSize);
	//マップを読み込む
	loadMap("assets/map/map1.txt");

	//初期設定
	init();
}

void MAP1::draw(){
	//Data取り出し位置
	int leftCol = (int)World.x / ChipSize;
	int upRow   = (int)World.y / ChipSize;
	//描画をずらすドット数
	int offsetX = (int)World.x % (int)ChipSize;
	int offsetY = (int)World.y % (int)ChipSize;

	for (int col = 0; col < NumDispDataColumus; col++) {
		for (int row = 0; row < NumDispDataRows; row++) {
			int i = leftCol + col + (upRow + row) * NumDataColumus;
			if (Data[i] == '1') {
				int px = ChipSize * col - offsetX;
				int py = ChipSize * row - offsetY;
				image(Road1.images()[0], px, py);
			}
			if (Data[i] == '2') {
				int px = ChipSize * col - offsetX;
				int py = ChipSize * row - offsetY;
				image(Road2.images()[4], px, py);
			}
			if (Data[i] == '.') {
				int px = ChipSize * col - offsetX;
				int py = ChipSize * row - offsetY;
				Map->draw(Water1.animImage5(), VECTOR2(px, py), AnimCnt, 8, 5, COLOR(0,0,10,0));
			}
		}
	}
}