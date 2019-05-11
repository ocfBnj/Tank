#pragma once

#include "TankBase.h"
#include "Timer.h"

enum EnemyType {
	ORDINARY, TOPSPEED, SPEEDGUN, ARMOURED
};

enum EnemyTarget {
	PLAYER, CAMP
};

class EnemyTank : public TankBase {
public:
	EnemyTank(int, int, EnemyType, EnemyTarget);
	void move(int _x, int _y);
	void show();
	void changeDir(int, int);
	void changeDirToPlayer(int, int);
	void changeDirToCamp();
private:
	EnemyType type;                        //̹������
	EnemyTarget target;                    //�з�̹�˹���Ŀ��
	IMAGE img_gray[4][4][2];               //̹����ͼ

	Timer timer_move;
	Timer timer_dir;
};

