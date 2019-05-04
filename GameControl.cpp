#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank(
		CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE)),
	playerBullet(new Bullet), hit(*map)
{
	addEnemy();

}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//���ſ�ʼ��Ϸ����
	auto enemy_beg = enemiesTank.begin();
	auto blt_beg = enemiesBullet.begin();

	while (true) {
		//�ƶ����
		playerTank->move();
		hit.canGo(playerTank->x, playerTank->y, playerTank->dir);
		playerTank->show();

		//��ҷ����ӵ�
		if (playerBullet->shoot(playerTank->x, playerTank->y, playerTank->dir, false))
			soundManager.playMusic(SHOOT);

		//�ƶ�����ӵ�
		if (playerBullet->exist) {
			//����ӵ��Ƿ�������ͼ
			if (hit.dection(playerBullet->x, playerBullet->y, 12, 12)) {
				playerBullet->clearOld();
				playerBullet->exist = false;
			}
			//����ӵ��Ƿ�������Ե
			if (playerBullet->move())
				soundManager.playMusic(BIN);

		}

		/**************************************************************************************************************/

		//�ƶ��з�̹�˲������ӵ�
		enemy_beg = enemiesTank.begin();
		blt_beg = enemiesBullet.begin();
		for (; enemy_beg != enemiesTank.end() && blt_beg != enemiesBullet.end(); ++enemy_beg, ++blt_beg) {

			if ((*enemy_beg)->blood > 0) {
				(*enemy_beg)->move();
				hit.canGo((*enemy_beg)->x, (*enemy_beg)->y, (*enemy_beg)->dir);
				(*enemy_beg)->show();
				(*blt_beg)->shoot((*enemy_beg)->x, (*enemy_beg)->y, (*enemy_beg)->dir, true);
			}

		}

		//�ƶ��з�̹���ӵ�
		for (auto& bullet : enemiesBullet) {
			if (bullet->exist) {
				if (hit.dection(bullet->x, bullet->y, 12, 12)) {
					bullet->clearOld();
					bullet->exist = false;
				}
				bullet->move();
			}
		}
		/**************************************************************************************************************/

		//�ж��ӵ���̹���Ƿ���ײ
		hit.focus(playerTank, playerBullet, enemiesTank, enemiesBullet);

		//���µ�ͼ
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

void GameControl::addEnemy() {
	std::shared_ptr<TankBase> tank(new EnemyTank(CENTER_X, CENTER_Y, ORDINARY));
	std::shared_ptr<Bullet> bullet(new Bullet);
	enemiesTank.push_back(tank);
	enemiesBullet.push_back(bullet);
}