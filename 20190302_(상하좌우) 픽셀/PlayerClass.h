#pragma once
#include "gameNode.h"
struct tagSensor
{
	RECT sensorRc;
	float sX, sY;
	bool isTouch;
	bool isJump;
};

class PlayerClass : public gameNode
{
	RECT pRc;		//플레이어 렉트
	float pX, pY;	//플레이어 중심좌표
	float width;
	float height;
	float pSpeed;	//플레이어 속도
	float gravity;	//중력
	float addtionalPower;
	
	tagSensor sensorLeft;
	tagSensor sensorTop;
	tagSensor sensorRight;
	tagSensor sensorBottom;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playerMove();		//플레이어 이동관련 함수
	void sensorMove();
	void pixelCollision();

	RECT getPRc() { return pRc; }

	float getPX() { return pX; }

	float getPY() { return pY; }

	PlayerClass() {}
	~PlayerClass() {}
};

