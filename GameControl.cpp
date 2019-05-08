#include "GameControl.h"

GameControl::GameControl() :
	map(new Map),
	playerTank(new PlayerTank),
	playerBullet(new Bullet), hit(*map),
	enemies_total(20), cur_enemies_total(0)
{
	loadimage(&bumb_img[0], _T(".\\res\\image\\bumb1.gif"));
	loadimage(&bumb_img[1], _T(".\\res\\image\\bumb2.gif"));
	loadimage(&bumb_img[2], _T(".\\res\\image\\bumb3.gif"));

	addEnemy();
	addEnemy();
	addEnemy();
}

void GameControl::gameLoop() {
	soundManager.playMusic(START);//���ſ�ʼ��Ϸ����

	while (enemies_total) {
		//�ƶ����
		playerTank->move();
		hit.playerDection(playerTank, enemies);
		playerTank->show();

		//�ƶ�����ӵ�
		if (playerBullet->exist) {
			//����ӵ��Ƿ�������ͼ
			if (hit.blockDection(playerBullet->x, playerBullet->y, 12, 12)) {
				playerBullet->clearOld();
				playerBullet->exist = false;
			}
			//����ӵ��Ƿ�������Ե
			if (playerBullet->move()) {
				soundManager.playMusic(BIN);
				//blast(playerBullet->x, playerBullet->y);
			}

		}

		//��ҷ����ӵ�
		if (playerBullet->shoot(playerTank->x, playerTank->y, playerTank->dir, false))
			soundManager.playMusic(SHOOT);

		

		/**************************************************************************************************************/

		//�ƶ��з�̹�˲�����,�ƶ��ӵ�
		for (auto& enemy : enemies) {
			//�ƶ��ӵ�
			if (enemy.second->exist) {
				if (hit.blockDection(enemy.second->x, enemy.second->y, 12, 12)) {
					enemy.second->clearOld();
					enemy.second->exist = false;
				}
				enemy.second->move();
			}

			//�ı�з�̹�˷���
			if (enemy.first->target == PLAYER)
				enemy.first->changeDirToPlayer(playerTank->x, playerTank->y);
			else if (enemy.first->target == CAMP)
				enemy.first->changeDirToCamp();
			enemy.first->move();
			hit.enemyDection(enemy.first, playerTank, enemies);
			enemy.first->show();
			t.stop();
			if (!enemy.second->exist && t.times() >= 500) {
				enemy.second->shoot(enemy.first->x, enemy.first->y, enemy.first->dir, true);
				t.start();
			}
			
		}
		/**************************************************************************************************************/
		//�ж��ӵ��Ƿ���ײ
		for (auto& enemy : enemies)
			hit.bulletDection(playerBullet, enemy.second);


		//�ж��ӵ���̹���Ƿ���ײ
		auto ret = hit.focus(playerTank, playerBullet, enemies);
		if (ret == 1) {//�ӵ����ܵ���
			soundManager.playMusic(ENEMY_DIE);
			enemies_total--;
			cur_enemies_total--;
		} else if (ret == 0) {//�ӵ����е���
			soundManager.playMusic(BIN);
		} else if (ret == 2) {//��ұ�����
			playerTank->moveToStart();
		} else if (ret == 3) {//��ұ�����
			playerTank->clearOld();
			FlushBatchDraw();
			soundManager.playMusic(PLAYER_DIE);
			Sleep(2000);
			return;
		}

		if (cur_enemies_total < 3)
			addEnemy();

		//���µ�ͼ
		map->showMap();
		FlushBatchDraw();
		Sleep(3);
	}
}

inline
void GameControl::addEnemy() {
	static size_t id = 0;//�Ѿ������ĵз�̹������
	if (id == 20)return;

	//���õط�̹�˵�Ŀ��
	EnemyTarget target;
	if (rand() % 2)
		target = CAMP;
	else
		target = PLAYER;
	//����̹�˳���λ��
	int born_x = CENTER_X + id % 3 * 12 * BLOCK_SIZE;
	int born_y = CENTER_Y;
	if (isHaveTank(born_x, born_y))
		return;//������̹��

	//�����з�̹��
	std::shared_ptr<EnemyTank> tank(new EnemyTank(born_x, born_y, (EnemyType)(rand() % 4), target));
	std::shared_ptr<Bullet> bullet(new Bullet);
	std::pair<std::shared_ptr<EnemyTank>, std::shared_ptr<Bullet>> enemy(tank, bullet);
	enemies.push_back(enemy);

	++cur_enemies_total;
	++id;
}

void GameControl::blast(int x, int y) {
	static int n = 0;
	if (n == 0) {
		getimage(&temp, x, y, x + BLOCK_SIZE * 2, y + BLOCK_SIZE * 2);
	} else if (n > 2) {
		putimage(x, y, &temp);
		n = 0;
		return;
	}
	transparentimage(NULL, x - BLOCK_SIZE, y - BLOCK_SIZE, &bumb_img[n++], 0xffc4c4);
}

bool GameControl::isHaveTank(int x, int y) {
	for (auto& enemy : enemies) {
		if (hit.isIntersect(enemy.first->x, enemy.first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2,
			x, y, BLOCK_SIZE * 2, BLOCK_SIZE * 2))
		{
			return true;
		}
	}
	return false;
}
