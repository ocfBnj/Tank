#pragma once

#include <conio.h>
#include "TankBase.h"

class PlayerTank : public TankBase {
	friend class GameControl;
public:
	PlayerTank(int, int);
private:
	void move();                   //̹���ƶ�
	void show();                   //��ʾ̹��

	IMAGE img_player[4][2];        //���̹��ͼƬ
};