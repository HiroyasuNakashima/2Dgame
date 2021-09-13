#include"VECTOR2.h"
#include"MAPIMG.h"
#include"OBJECT.h"
#include"COLOR.h"
class CONTAINER;

class MAP : public  OBJECT{
public:
	MAP();
	~MAP();
	void loadMap(const char* filename);
	void init();
	void update();
	void draw(int* animImage, VECTOR2 pos, int animCnt, int numImages, int animInterval, COLOR color);
	virtual void draw();
	//�Q�b�^�[�A�Z�b�^�[
	int chipSize() { return ChipSize; }
	//�J�����Ŏg�p
	VECTOR2& world(){ return World; }
	void setWorld(VECTOR2 world) { World = world; }
	//�����蔻��p
	bool collisionCheck(VECTOR2 pos);
	//�L����
	bool collisionCheckCharaLeft(VECTOR2 lefttop, VECTOR2 leftbottom);
	bool collisionCheckCharaRight(VECTOR2 righttop, VECTOR2 rightbottom);
	bool collisionCheckCharaTop(VECTOR2 topleft, VECTOR2 topright);
	bool collisionCheckCharaBottom(VECTOR2 bottomleft, VECTOR2 bottomright);
	//�X�N���[���̉E�[
	float mDispLeft();
	float mDispRight();
	float mDispTop();
	float mDispBottom();
protected:
	char* Data = 0;
	unsigned int Size = 0;
	int NumDataColumus = 0;
	int NumDataRows = 0;
	int NumDispDataColumus = 0;//��ʕ\���̗�
	int NumDispDataRows = 0;//��ʕ\���̍s��
	VECTOR2 World; //���[���h���W
	VECTOR2 MaxWorld; //��ʈړ��̍ő�l
	int ChipSize = 0;
	VECTOR2 MapSize = 0;//Map�̑傫��
	int AnimCnt = 0;
	COLOR Color;
};