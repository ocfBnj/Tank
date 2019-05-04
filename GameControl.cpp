#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank(
		CENTER_X + 8 * BLOCK_SIZE, CENTER_Y + 24 * BLOCK_SIZE)),
	playerBullet(new Bullet), hit(*map)
{
	addEnemy();
	addEnemy();

}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//���ſ�ʼ��Ϸ����

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

		//�ƶ��з�̹�˲�����,�ƶ��ӵ�
		for (auto& enemy : enemies) {
			enemy.first->move();
			hit.canGo(enemy.first->x, enemy.first->y, enemy.first->dir);
			enemy.first->show();
			enemy.second->shoot(enemy.first->x, enemy.first->y, enemy.first->dir, true);

			//�ƶ��ӵ�
			if (enemy.second->exist) {
				if (hit.dection(enemy.second->x, enemy.second->y, 12, 12)) {
					enemy.second->clearOld();
					enemy.second->exist = false;
				}
				enemy.second->move();
			}
		}
		/**************************************************************************************************************/

		//�ж��ӵ���̹���Ƿ���ײ
		hit.focus(playerTank, playerBullet, enemies);

		//���µ�ͼ
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

void GameControl::addEnemy() {
	std::shared_ptr<TankBase> tank(new EnemyTank(CENTER_X, CENTER_Y, ORDINARY));
	std::shared_ptr<Bullet> bullet(new Bullet);
	std::pair<std::shared_ptr<TankBase>, std::shared_ptr<Bullet>> enemy(tank, bullet);
	enemies.push_back(enemy);
}