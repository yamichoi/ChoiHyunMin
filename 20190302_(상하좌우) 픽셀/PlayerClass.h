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
	RECT pRc;		//�÷��̾� ��Ʈ
	float pX, pY;	//�÷��̾� �߽���ǥ
	float width;
	float height;
	float pSpeed;	//�÷��̾� �ӵ�
	float gravity;	//�߷�
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

	void playerMove();		//�÷��̾� �̵����� �Լ�
	void sensorMove();
	void pixelCollision();

	RECT getPRc() { return pRc; }

	float getPX() { return pX; }

	float getPY() { return pY; }

	PlayerClass() {}
	~PlayerClass() {}
};

