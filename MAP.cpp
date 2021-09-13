#include<stdio.h>
#include"common.h"
#include"CONTAINER.h"
#include"WINDOW.h"
#include"PLAYER.h"
#include"MAP.h"
#include"memLeakPlace_Start.h"

MAP::MAP(){
	//�f�[�^
	ChipSize = C->data("MapChipSize");
	Color.r = C->data("MapColorR");
	Color.b = C->data("MapColorB");
	Color.b = C->data("MapColorG");
	Color.a = C->data("MapColorA");
}
MAP::~MAP() {
	SAFE_DELETE(Data);
}
void MAP::loadMap(const char* filename){
	//�t�@�C�����J��
	FILE* fp = 0;
	fopen_s(&fp, filename, "rb");
	WARNING(fp == 0, "�}�b�v�f�[�^��ǂݍ��߂܂���", filename);
	//�t�@�C���T�C�Y�𒲂ׂ�
	fseek(fp, 0L, SEEK_END);
	Size = ftell(fp);
	rewind(fp);
	//���g���C���AData�͂O�łȂ��̂ŊJ��
	SAFE_DELETE(Data);
	//�T�C�Y����Data��p�ӂ���
	Data = new char [Size];
	//1�������ǂݍ���Data[i]�ɓ���Ă����B�����ɗ񐔂ƍs�������߂�
	NumDataColumus = 0;
	NumDataRows = 0;
	char c = 0;
	int i = 0;
	while (fscanf_s(fp, "%c", &c, Size) != EOF) {
		if (c != '\n') {
			Data[i] = c;
			i++;
		}
		else {//���s�����̎�
			if (NumDataRows == 0) {
				NumDataColumus = i;
			}
			NumDataRows++;
		}
	}
	fclose(fp);
}

void MAP::init() {
	//���[���h���W
	World.x = 0;
	World.y = 0;
	//���[���h���W�̍ő�l
	MaxWorld.x = ChipSize * (NumDataColumus-1) - W->winSize().x;
	MaxWorld.y = ChipSize *  NumDataRows	   - W->winSize().y;
	//�}�b�v�f�[�^�̍s��
	NumDispDataColumus = W->winSize().x / ChipSize + 1;
	NumDispDataRows    = W->winSize().y / ChipSize + 1;

	//OBJECT�ɏ���n��
	OBJECT::setMap(this);
}

void MAP::update() {
	AnimCnt++;

	//�㉺���E�̕`����E�͈͂�ݒ�
	//��
	if (World.x <= 0) {
		World.x = 0;
	}
		//��
	if (World.y <= 0) {
		World.y = 0;
	}
		//�E
	if (World.x >= MaxWorld.x) {
		World.x = MaxWorld.x;
	}
		//��
	if (World.y >= MaxWorld.y) {
		World.y = MaxWorld.y;
	}
}

void MAP::draw() {}

void MAP::draw(int* animImages, VECTOR2 pos, int animCnt, int numImages, int animInterval, COLOR color) {

	int i = 0;
	if (numImages > 1) {
		i = animCnt / animInterval % numImages;
		animCnt %= animInterval * numImages;//�Ō�܂ōs������0�ɖ߂�
	}
	image(animImages[i], pos.x, pos.y);
	COLOR(color.r, color.g, color.b, color.a);
}


//�u���b�N�ƃL�����̓����蔻��p�֐��Q
//�w�肵�����W���A�u���b�N�̒��ɓ����Ă��邩�`�F�b�N����
bool MAP::collisionCheck(VECTOR2 pos) {
	//���[���h���W�������Ă���}�b�vData�̗�col�ƍsrow�����߂�
	int col = (int)pos.x / ChipSize;
	int row = (int)pos.y / ChipSize;
	//�}�b�v�͈͊O�͏��O
	if ((col < 0) || (col >= NumDataColumus) || (row < 0) || (row >= NumDataRows)) {
		return false;
	}
	//�u���b�N�ɐH������ł��邩����
	if (Data[col + row * NumDataColumus] == '.') {
		return true;
	}
	return false;
}
//�u���b�N�ƃL�����̍��ӂ��d�Ȃ��ĂȂ���
bool MAP::collisionCheckCharaLeft(VECTOR2 lefttop, VECTOR2 leftbottom) {
	bool leftTop = collisionCheck(lefttop);
	bool leftBottom = collisionCheck(leftbottom);
	return leftTop || leftBottom;
}
//�u���b�N�ƃL�����̉E�ӂ��d�Ȃ��ĂȂ���
bool MAP::collisionCheckCharaRight(VECTOR2 righttop, VECTOR2 rightbottom) {
	bool rightTop = collisionCheck(righttop);
	bool rightBottom = collisionCheck(rightbottom);
	return rightTop || rightBottom;
}
//�u���b�N�ƃL�����̏�ӂ��d�Ȃ��ĂȂ���
bool MAP::collisionCheckCharaTop(VECTOR2 topleft, VECTOR2 topright) {
	bool topLeft = collisionCheck(topleft);
	bool topRight = collisionCheck(topright);
	return topLeft || topRight;
}
//�u���b�N�ƃL�����̉��ӂ��d�Ȃ��ĂȂ����܂��́A�ڂ��Ă��邩
bool MAP::collisionCheckCharaBottom(VECTOR2 bottomleft, VECTOR2 bottomright) {
	bool bottomLeft = collisionCheck(bottomleft);
	bool bottomRight = collisionCheck(bottomright);
	return bottomLeft || bottomRight;
}

float MAP::mDispLeft()	 { return World.x; }
float MAP::mDispRight()	 { return World.x + W->winSize().x; }
float MAP::mDispTop()	 { return World.y; }
float MAP::mDispBottom() { return World.y + W->winSize().y; }

#include"memLeakPlace_End.h"