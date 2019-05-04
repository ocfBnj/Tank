#pragma once

#include "TankBase.h"

enum EnemyType {
	ORDINARY, TOPSPEED, SPEEDGUN, ARMOURED
};

class EnemyTank : public TankBase {
	friend class GameControl;
	friend class HitDection;
public:
	EnemyTank(int, int, EnemyType);
private:
	void move();
	void show();
	void changeDir();

	EnemyType type;                        //̹������
	IMAGE img_gray[4][4][2];               //̹����ͼ
	Timer dir_timer;
	Timer move_timer;
};

