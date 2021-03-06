#include "EnemyTank.h"


EnemyTank::EnemyTank(int x, int y, EnemyType t, EnemyTarget tar) :
	TankBase(x, y, DOWN, 1, 1), type(t), target(tar) {
	if (type == ORDINARY) { //普通坦克
		loadimage(&img_gray[ORDINARY][LEFT][0], _T(".\\res\\image\\gray-tank\\1-1-1.gif"));
		loadimage(&img_gray[ORDINARY][LEFT][1], _T(".\\res\\image\\gray-tank\\1-1-2.gif"));
		loadimage(&img_gray[ORDINARY][UP][0], _T(".\\res\\image\\gray-tank\\1-2-1.gif"));
		loadimage(&img_gray[ORDINARY][UP][1], _T(".\\res\\image\\gray-tank\\1-2-2.gif"));
		loadimage(&img_gray[ORDINARY][RIGHT][0], _T(".\\res\\image\\gray-tank\\1-3-1.gif"));
		loadimage(&img_gray[ORDINARY][RIGHT][1], _T(".\\res\\image\\gray-tank\\1-3-2.gif"));
		loadimage(&img_gray[ORDINARY][DOWN][0], _T(".\\res\\image\\gray-tank\\1-4-1.gif"));
		loadimage(&img_gray[ORDINARY][DOWN][1], _T(".\\res\\image\\gray-tank\\1-4-2.gif"));
	} else if (type == TOPSPEED) { //高速坦克
		speed = 2;
		loadimage(&img_gray[TOPSPEED][LEFT][0], _T(".\\res\\image\\gray-tank\\2-1-1.gif"));
		loadimage(&img_gray[TOPSPEED][LEFT][1], _T(".\\res\\image\\gray-tank\\2-1-2.gif"));
		loadimage(&img_gray[TOPSPEED][UP][0], _T(".\\res\\image\\gray-tank\\2-2-1.gif"));
		loadimage(&img_gray[TOPSPEED][UP][1], _T(".\\res\\image\\gray-tank\\2-2-2.gif"));
		loadimage(&img_gray[TOPSPEED][RIGHT][0], _T(".\\res\\image\\gray-tank\\2-3-1.gif"));
		loadimage(&img_gray[TOPSPEED][RIGHT][1], _T(".\\res\\image\\gray-tank\\2-3-2.gif"));
		loadimage(&img_gray[TOPSPEED][DOWN][0], _T(".\\res\\image\\gray-tank\\2-4-1.gif"));
		loadimage(&img_gray[TOPSPEED][DOWN][1], _T(".\\res\\image\\gray-tank\\2-4-2.gif"));
	} else if (type == SPEEDGUN) {
		loadimage(&img_gray[SPEEDGUN][LEFT][0], _T(".\\res\\image\\gray-tank\\3-1-1.gif"));
		loadimage(&img_gray[SPEEDGUN][LEFT][1], _T(".\\res\\image\\gray-tank\\3-1-2.gif"));
		loadimage(&img_gray[SPEEDGUN][UP][0], _T(".\\res\\image\\gray-tank\\3-2-1.gif"));
		loadimage(&img_gray[SPEEDGUN][UP][1], _T(".\\res\\image\\gray-tank\\3-2-2.gif"));
		loadimage(&img_gray[SPEEDGUN][RIGHT][0], _T(".\\res\\image\\gray-tank\\3-3-1.gif"));
		loadimage(&img_gray[SPEEDGUN][RIGHT][1], _T(".\\res\\image\\gray-tank\\3-3-2.gif"));
		loadimage(&img_gray[SPEEDGUN][DOWN][0], _T(".\\res\\image\\gray-tank\\3-4-1.gif"));
		loadimage(&img_gray[SPEEDGUN][DOWN][1], _T(".\\res\\image\\gray-tank\\3-4-2.gif"));
	} else if (type == ARMOURED) { //装甲坦克
		cur_blood = 3;
		loadimage(&img_gray[ARMOURED][LEFT][0], _T(".\\res\\image\\gray-tank\\4-1-1.gif"));
		loadimage(&img_gray[ARMOURED][LEFT][1], _T(".\\res\\image\\gray-tank\\4-1-2.gif"));
		loadimage(&img_gray[ARMOURED][UP][0], _T(".\\res\\image\\gray-tank\\4-2-1.gif"));
		loadimage(&img_gray[ARMOURED][UP][1], _T(".\\res\\image\\gray-tank\\4-2-2.gif"));
		loadimage(&img_gray[ARMOURED][RIGHT][0], _T(".\\res\\image\\gray-tank\\4-3-1.gif"));
		loadimage(&img_gray[ARMOURED][RIGHT][1], _T(".\\res\\image\\gray-tank\\4-3-2.gif"));
		loadimage(&img_gray[ARMOURED][DOWN][0], _T(".\\res\\image\\gray-tank\\4-4-1.gif"));
		loadimage(&img_gray[ARMOURED][DOWN][1], _T(".\\res\\image\\gray-tank\\4-4-2.gif"));
	}

	timer_move.setDifTime(10);
	timer_dir.setDifTime(1000);
}


void EnemyTank::move(int _x, int _y) {
	changeShape();
	if (flag_move == false) {
		//改变方向
		if (target == PLAYER)
			changeDirToPlayer(_x, _y);
		else if (target == CAMP)
			changeDirToCamp();

		if (timer_move.isTimeOut()) {
			flag_move = true;
		}
	} else {
		autoMove();
	}
}

void EnemyTank::show() {
	transparentimage(NULL, x, y, &img_gray[type][dir][cur_shape], 0xffc4c4);
}

void EnemyTank::changeDir(int _x, int _y) {
	if (timer_dir.isTimeOut()) {
		if (_x < x) {//目标在敌方坦克的左边
			if (_y < y) {//左上
				if (rand() % 2)	dir = UP;
				else dir = LEFT;
			} else {//左下
				if (rand() % 2)	dir = DOWN;
				else dir = LEFT;
			}
		} else {
			if (_y < y) {//右上
				if (rand() % 2)	dir = UP;
				else dir = RIGHT;
			} else {//右下
				if (rand() % 2)	dir = DOWN;
				else dir = RIGHT;
			}
		}
	}
}

inline void EnemyTank::changeDirToPlayer(int _x, int _y) {
	changeDir(_x, _y);
}

inline void EnemyTank::changeDirToCamp() {
	int camp_x = CENTER_X + 13 * BLOCK_SIZE;
	int camp_y = CENTER_Y + 25 * BLOCK_SIZE;
	changeDir(camp_x, camp_y);
}
