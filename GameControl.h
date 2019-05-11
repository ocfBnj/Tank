#ifndef _GAME_CONTROL_
#define _GAME_CONTROL_

#include <graphics.h>
#include <list>
#include <iterator>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Bullet.h"
#include "HitDection.h"
#include "Timer.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                     //��Ϸ��ѭ��
private:
	Map map;                             //��ͼ
	HitDection hit;                      //��ײ���
	PlayerTank player;                   //���
	Bullet blt_player;                   //����ӵ�
	std::list<EnemyTank> enemies;        //�����б�
	std::list<Bullet> blts_enemies;      //�����ӵ��б�

	void updatePlayer();
	void updataEnemies();
	void addEnemy();
};

#endif // !_GAME_CONTROL_