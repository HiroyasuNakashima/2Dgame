#pragma once
#include"OBJECT.h"

class CAMERA : public OBJECT {
public:
	CAMERA();
	void init();
	void update();
private:
	float Px = 0.0f;
	float Py = 0.0f;
	float WinX = 0.0f;//•\Ž¦”ÍˆÍ
	float WinY = 0.0f;
};