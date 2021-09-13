#pragma once
class CONTAINER;

class MAPIMG {
public:
	MAPIMG();
	~MAPIMG();
	//�摜�쐬
	//�摜��y�A�t�@�C�����A�摜�T�C�Y
	void create(int y, const char* filename, int chipsize);
	//�A�j���摜�쐬�p
	void animCreate(int x, int y, const char* filename, int chipsize);
	int numimg() { return NumImages; }
	int* images() { return Images; }
	int** animImages() { return AnimImages; }
	int* animImage1() { return AnimImage1; }
	int* animImage2() { return AnimImage2; }
	int* animImage3() { return AnimImage3; }
	int* animImage4() { return AnimImage4; }
	int* animImage5() { return AnimImage5; }
	static void setContainer(CONTAINER* c) { C = c; }
private:
	int NumImages = 0;
	int* Images = 0;
	int** AnimImages = 0;
	int ChipSize = 0;
	int* AnimImage1 = 0;
	int* AnimImage2 = 0;
	int* AnimImage3 = 0;
	int* AnimImage4 = 0;
	int* AnimImage5 = 0;
	static CONTAINER* C;
};