#ifndef _HIT_DECTION_H_
#define _HIT_DECTION_H_

#include <list>
#include "TankBase.h"
#include "Map.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "PlayerTank.h"
#include "Sound.h"

class Map;
class TankBase;
class Bullet;
class HitDection {
public:
	bool isIntersect(                                         //�ж����������Ƿ��ཻ
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2) const;
	bool isIntersect(TankBase &tank1, TankBase &tank2);       //�ж�����̹���Ƿ��ཻ
	void noKnockWall(TankBase& tank, Map& map);               //��ֹ̹��ײǽ
	void hitWall(Bullet& blt, Map& map);                      //�ӵ�����ǽ
	void impactTank(TankBase& tank1, TankBase& tank2);        //tank1ײtank2
	void focusBullet(TankBase& pl_tank, Bullet& pl_blt,       //�ӵ����У�̹�˻��ӵ���
		std::list<EnemyTank>& enemies_tank, std::list<Bullet>& enemies_blt);
};

#endif // !_HIT_DECTION_H_