#include"PLAYER.h"
#include"MAP.h"
#include"PLAYER_BULLET.h"
#include"memLeakPlace_Start.h"

PLAYER_BULLET::PLAYER_BULLET(){
	Img = loadImage("assets/chara/bullet.png");
	Speed = C->data("BulletSpeed");
	OffsetTop = C->data("BulletOffsetTop");
	OffsetBottom = C->data("BulletOffsetBottom");
	OffsetLeft = C->data("BulletOffsetLeft");
	OffsetRight = C->data("BulletOffsetRight");
}

void PLAYER_BULLET::init(){
	Dir = { 0,0 };
	Life = 1;
	//キャラの位置を弾の出現位置にする
	Pos.x = Player->pos().x;
	Pos.y = Player->pos().y;
	//画像の向きから飛ばす方向を決める
	if (Player->images() == Player->anim()->frontImage()) {
		Dir.y = Speed;
	}
	if (Player->images() == Player->anim()->backImage()) {
		Dir.y = -Speed;
	}
	if (Player->images() == Player->anim()->leftImage()) {
		Dir.x = -Speed;
	}
	if (Player->images() == Player->anim()->rightImage()) {
		Dir.x = Speed;
	}
}

void PLAYER_BULLET::update() {
	Pos += Dir;
	//当たり判定
	//マップ
	if (Map->collisionCheckCharaTop		(cTopLeft(), cTopRight()		)	|| 
		Map->collisionCheckCharaBottom	(cBottomLeft(), cBottomRight()	)	||
		Map->collisionCheckCharaLeft	(cLeftTop(), cLeftBottom()		)	|| 
		Map->collisionCheckCharaRight	(cRightTop(), cRightBottom()	))	{
		Life = 0;
	}
	//スクリーン外に行ったら消える
	if (cRight() < Map->mDispLeft() || cLeft() > Map->mDispRight() ||
		cBottom() < Map->mDispTop() || cTop() > Map->mDispBottom()) {
		Life = 0;
	}
}

void PLAYER_BULLET::draw() {
	//弾をキャラの中心から発射させる為、表示位置をoffset分ずらす
	float px = Pos.x + OffsetLeft - Map->world().x;
	float py = Pos.y + OffsetTop  - Map->world().y;
	image(Img, px, py);
}

int PLAYER_BULLET::life() { return Life; }

#include"memLeakPlace_End.h"