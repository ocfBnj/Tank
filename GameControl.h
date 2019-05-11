#ifndef _GAME_CONTROL_
#define _GAME_CONTROL_

#include <graphics.h>
#include "struct.h"
#include "Map.h"
#include "PlayerTank.h"
#include "Bullet.h"
#include "HitDection.h"

class GameControl {
public:
	GameControl();
	void gameLoop();                     //��Ϸ��ѭ��
private:
	Map map;                             //��ͼ
	HitDection hit;                      //��ײ���
	PlayerTank player;                   //���
	Bullet bullet_player;                //����ӵ�

	void updatePlayer();
};

#endif // !_GAME_CONTROL_