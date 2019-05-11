#ifndef _HIT_DECTION_H_
#define _HIT_DECTION_H_

#include <list>
#include "TankBase.h"
#include "Map.h"
#include "Bullet.h"
#include "EnemyTank.h"

class Map;
class TankBase;
class Bullet;
class HitDection {
public:
	HitDection();
	bool isIntersect(                                   //�ж����������Ƿ��ཻ
		int x1, int y1, int w1, int h1,
		int x2, int y2, int w2, int h2) const;
	void tankMove(TankBase& tank, Map& map);            //���̹��ײǽ
	void hitWall(Bullet& blt, Map& map);                //�ӵ�����ǽ
	void hitTank(TankBase& tank1, TankBase& tank2);     //tank1ײtank2
	void focusTank(TankBase& pl_tank, Bullet& pl_blt,   //�ӵ�����̹��
		std::list<EnemyTank>& enemies_tank, std::list<Bullet>& enemies_blt); 
private:
	int map_x, map_y;                                   //�Ƚ���ײʱ��ͼ�����Ͻ�����
};

#endif // !_HIT_DECTION_H_