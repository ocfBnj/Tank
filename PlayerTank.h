#pragma once

#include <conio.h>
#include "TankBase.h"
#include "Sound.h"

class PlayerTank : public TankBase {
public:
	PlayerTank();
	void moveToStart();            //�ƶ�����ʼλ��
	void move();                   //̹���ƶ�
	void show();                   //��ʾ̹��
private:
	IMAGE img_player[4][2];        //���̹��ͼƬ
};