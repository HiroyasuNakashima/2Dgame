#include"common.h"
#include"input.h"
#include"graphic.h"
#include"ANIMATION.h"
#include"MAP.h"
#include"PLAYER.h"
#include"WINDOW.h"
#include"CONTAINER.h"
#include"PLAYER_BULLET.h"
#include"memLeakPlace_Start.h"

PLAYER::PLAYER() {
	//�f�[�^
	NumImages = C->data("CharaNumImages");
	ChipSize = C->data("CharaChipSize");
	AnimInterval = C->data("CharaAnimInterval");
	//�摜�쐬
	Anim = new ANIMATION;
	Anim->create(150,250,"assets/chara/majo.png", ChipSize, AnimInterval);

	//�����ݒ�
	init();

	//�e�쐬
	Bullet = new PLAYER_BULLET* [NumBullet];
	for (int i = 0; i < NumBullet; i++) {
		Bullet[i] = new PLAYER_BULLET;
	}

	//OBJECT�N���X�փ|�C���^��n��
	OBJECT::setPlayer(this);
	
}
PLAYER::~PLAYER() {
	SAFE_DELETE_ARRAY(Bullet);
	SAFE_DELETE(Bullet);
	SAFE_DELETE(Anim);
}

void PLAYER::init(){
	Pos.x = C->data("PlayerPx");
	Pos.y = C->data("PlayerPy");
	Color.r = C->data("CharaColorR");
	Color.g = C->data("CharaColorG");
	Color.b = C->data("CharaColorB");
	Color.a = C->data("CharaColorA");
	Speed = C->data("PlayerSpeed");
	OffsetTop = C->data("PlayerOffsetTop");
	OffsetBottom = C->data("PlayerOffsetBottom");
	OffsetLeft = C->data("PlayerOffsetLeft");
	OffsetRight = C->data("PlayerOffsetRight");
	Images = Anim->frontImage();
	//�e
	NumBullet = C->data("PlayerNumBullet");
}

void PLAYER::update() {
	//�A�j�[�V����
	AnimCnt++;
	//�ړ�
	Dir.x = 0.0f;
	Dir.y = 0.0f;
	//��Q���ɓ����������Ɍ��̏ꏊ�ɖ߂��p
	VECTOR2 currentWorld = Pos;

	if (isPress(KEY_A)) {
		Dir.x = -Speed;
		Images = Anim->leftImage();
	}
	if (isPress(KEY_D)) {
		Dir.x = Speed;
		Images = Anim->rightImage();
	}
	if (isPress(KEY_W)) {
		Dir.y = -Speed;
		Images = Anim->backImage();
	}
	if (isPress(KEY_S)) {
		Dir.y = Speed;
		Images = Anim->frontImage();
	}
	Pos += Dir;

	//�����蔻��
	//�}�b�v
	if (Images == Anim->backImage()) {
		if (Map->collisionCheckCharaTop(cTopLeft(),cTopRight())) {
			Pos = currentWorld;
		}
	}
	if (Images == Anim->frontImage()) {
		if (Map->collisionCheckCharaBottom(cBottomLeft(), cBottomRight())) {
			Pos = currentWorld;
		}
	}
	if (Images == Anim->leftImage()) {
		if (Map->collisionCheckCharaLeft(cLeftTop(),cLeftBottom())) {
			Pos = currentWorld;
		}
	}
	if (Images == Anim->rightImage()) {
		if (Map->collisionCheckCharaRight(cRightTop(),cRightBottom())) {
			Pos = currentWorld;
		}
	}
	//�X�N���[��
	if (cLeft() < Map->mDispLeft() || cRight() > Map->mDispRight() ||
		cTop() < Map->mDispTop() || cBottom() > Map->mDispBottom()) {
		Pos = currentWorld;
	}

	//�e�o��
	if (isTrigger(KEY_K)) {
		for (int i = 0; i < NumBullet; i++) {
			if (Bullet[i]->life() == 0) {
				Bullet[i]->init();
				break;
			}
		}
	}
	for (int i = 0; i < NumBullet; i++) {
		if (Bullet[i]->life() == 1) {
			Bullet[i]->update();
		}
	}
}

void PLAYER::draw(){
	World = Pos - Map->world();//World���W�ϊ�
	Anim->draw(Images, World, AnimCnt, 4, Color);
	//�e
	for (int i = 0; i < NumBullet; i++) {
		if (Bullet[i]->life() == 1) {
			Bullet[i]->draw();
		}
	}
}

#include"memLeakPlace_End.h"