#include "stdafx.h"
#include "PlayerClass.h"

HRESULT PlayerClass::init(void)
{
	pX = 150;
	pY = WINSIZEY / 2;
	width = 50;
	height = 50;
	pRc = RectMake(pX, pY, width, height);
	pSpeed = 5.f;
	gravity = 0.0f;
	addtionalPower = 0.0f;

	//센서 초기화
	//왼쪽
	sensorLeft.sX = pX;
	sensorLeft.sY = pY + height / 2;
	sensorLeft.isJump = false;
	sensorLeft.isTouch = false;
	//탑
	sensorTop.sX = pX + width / 2;
	sensorTop.sY = pY;
	sensorTop.isJump = false;
	sensorTop.isTouch = false;
	//오른쪽
	sensorRight.sX = pX + width;
	sensorRight.sY = pY + height / 2;
	sensorRight.isJump = false;
	sensorRight.isTouch = false;
	//바텀
	sensorBottom.sX = pX + width / 2;
	sensorBottom.sY = pY + height;
	sensorBottom.isJump = false;
	sensorBottom.isTouch = false;

	return S_OK;
}

void PlayerClass::release(void)
{

}

void PlayerClass::update(void)
{
	//상시중력
	gravity += 0.2f;
	
	this->playerMove();
	this->sensorMove();
	this->pixelCollision();

	pY += gravity;

}

void PlayerClass::render(void)
{


	//왼쪽
	Rectangle(getMemDC(), 
		sensorLeft.sensorRc.left - CAMERA->getCRc().left,
		sensorLeft.sensorRc.top - CAMERA->getCRc().top,
		sensorLeft.sensorRc.right - CAMERA->getCRc().left,
		sensorLeft.sensorRc.bottom - CAMERA->getCRc().top);
	//탑
	Rectangle(getMemDC(), 
		sensorTop.sensorRc.left - CAMERA->getCRc().left,
		sensorTop.sensorRc.top - CAMERA->getCRc().top,
		sensorTop.sensorRc.right - CAMERA->getCRc().left,
		sensorTop.sensorRc.bottom - CAMERA->getCRc().top);
	//오른쪽
	Rectangle(getMemDC(), 
		sensorRight.sensorRc.left - CAMERA->getCRc().left,
		sensorRight.sensorRc.top - CAMERA->getCRc().top,
		sensorRight.sensorRc.right - CAMERA->getCRc().left,
		sensorRight.sensorRc.bottom - CAMERA->getCRc().top);
	//바텀
	Rectangle(getMemDC(),
		sensorBottom.sensorRc.left - CAMERA->getCRc().left,
		sensorBottom.sensorRc.top - CAMERA->getCRc().top,
		sensorBottom.sensorRc.right - CAMERA->getCRc().left,
		sensorBottom.sensorRc.bottom - CAMERA->getCRc().top);

	//플레이어
	Rectangle(getMemDC(),
		{ pRc.left - CAMERA->getCRc().left,
		pRc.top - CAMERA->getCRc().top,
		pRc.right - CAMERA->getCRc().left,
		pRc.bottom - CAMERA->getCRc().top });

}

void PlayerClass::playerMove()
{
	//조작키
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		pX += pSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		pX -= pSpeed;
	}

	if (sensorBottom.isJump == false)
	{
		//점프
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			pY -= 5;
			gravity = -3.0f;

		}
		if (KEYMANAGER->isStayKeyDown('C'))
		{

			if (addtionalPower <= 2.0f)
			{
				addtionalPower += 0.2f;
			}

			if (addtionalPower <= 2.0f)
			{
				gravity -= addtionalPower;
				
			}

		}
		if (KEYMANAGER->isOnceKeyUp('C'))
		{
			//gravity = 0;
			addtionalPower = 0;
			sensorBottom.isJump = true;
		}
	}
	//위치 조정후 대입시키기
	pRc = RectMake(pX, pY, width, height);
}
void PlayerClass::sensorMove()
{
	sensorLeft.sX = pX;
	sensorLeft.sY = pY + height / 2 ;

	sensorBottom.sX = pX + width / 2;
	sensorBottom.sY = pY + height;

	sensorRight.sX = pX + width;
	sensorRight.sY = pY + height / 2;

	sensorTop.sX = pX + width / 2;
	sensorTop.sY = pY;

	sensorLeft.sensorRc = RectMakeCenter(sensorLeft.sX, sensorLeft.sY, 5, 5);
	sensorBottom.sensorRc = RectMakeCenter(sensorBottom.sX, sensorBottom.sY, 5, 5);
	sensorRight.sensorRc = RectMakeCenter(sensorRight.sX, sensorRight.sY, 5, 5);
	sensorTop.sensorRc = RectMakeCenter(sensorTop.sX, sensorTop.sY, 5, 5);
}
void PlayerClass::pixelCollision()
{
	for (int i = sensorBottom.sY - 5; i < sensorBottom.sY + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("map1")->getMemDC(), sensorBottom.sX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 255 && b == 0))
		{
			pY = i - height;
			gravity = 0.0f;
			sensorBottom.isJump = false;
			break;
		}
	}

	for (int i = sensorRight.sX - 5; i < sensorRight.sX + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("map1")->getMemDC(), i, sensorRight.sY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 255))
		{
			 pX = i - width;
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				gravity = 0.0f;
			}
			break;
		}

	}


	for (int i = sensorLeft.sX - 10; i < sensorLeft.sX + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("map1")->getMemDC(), i, sensorLeft.sY);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if ((r == 0 && g == 255 && b == 0))
		{
			pX = i + 10;
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				gravity = 0.0f;
			}
			break;
		}
	
	}

	for (int i = sensorTop.sY - 5; i < sensorTop.sY + 5; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("map1")->getMemDC(), sensorTop.sX, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 0 && g == 0 && b == 0))
		{
			pY += 5;
			gravity = 0.0f;
			break;
		}

	}
}

