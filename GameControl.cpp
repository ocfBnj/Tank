#include "GameControl.h"

GameControl::GameControl() : enemies_total(20), born_total(0) {}

void GameControl::gameLoop() {
	initGame();
	//����ȫ����������ȫ����������Ϸʤ��
	while ((enemies.size() != 0) || (born_total != enemies_total)) {
		updatePlayer();
		updataEnemies();

		hit.focusBullet(player, blt_player, enemies, blts_enemies);

		//map.setNeedUpdate(true);
		map.update();

		if (enemies.size() < 3) addEnemy(); //ÿ������3��̹��

		FlushBatchDraw();
		Sleep(6);
	}
}

void GameControl::initGame() {
	map.showMap();
	Sound::play(START);
}

void GameControl::updatePlayer() {
	//�������̹��
	player.move();
	//Sound::pauseMove(player.moveStatus());
	if (player.moveStatus()) {
		hit.noKnockWall(player, map);//̹����ǽ��ײ���
		//̹����̹��֮����ײ���
		for (auto &enemy : enemies) {
			hit.impactTank(player, enemy);
		}
	}

	player.show();

	//�����ӵ�
	blt_player.shoot(player, false);
	if (blt_player.isExist()) {
		hit.hitWall(blt_player, map);
		if (blt_player.move()) Sound::play(BIN);
	}

}

void GameControl::updataEnemies() {
	auto enemy = enemies.begin();
	auto blt = blts_enemies.begin();
	for (; enemy != enemies.end() && blt != blts_enemies.end(); enemy++, blt++) {
		//���µз�̹��
		enemy->move(player.getX(), player.getY());
		if (enemy->moveStatus()) {
			hit.noKnockWall(*enemy, map);
			hit.impactTank(*enemy, player);

			for (auto i_enemy = enemies.begin(); i_enemy != enemies.end(); i_enemy++) {
				if (enemy == i_enemy)continue;
				hit.impactTank(*enemy, *i_enemy);
			}
		}
		enemy->show();

		//�����ӵ�
		blt->shoot(*enemy, true);
		if (blt->isExist()) {
			hit.hitWall(*blt, map);
			blt->move();
		}
	}
}

void GameControl::addEnemy() {
	if (born_total == enemies_total) return;
	auto ret = makeNewPos();
	if (std::get<0>(ret) == -1 && std::get<1>(ret) == -1) 
		return; //����ʧ��

	unsigned type = rand() % 4;
	unsigned des = rand() % 2;
	enemies.push_back(EnemyTank(std::get<0>(ret), std::get<1>(ret),
		static_cast<EnemyType>(type), static_cast<EnemyTarget>(des)));
	blts_enemies.push_back(Bullet());

	born_total++;

}

std::tuple<int, int> GameControl::makeNewPos() {
	int id = rand() % 3;
	int x = CENTER_X + id * 12 * BLOCK_SIZE;
	int y = CENTER_Y;

	//�жϸ������Ƿ�����̹��
	for (auto &tank : enemies) {
		if (hit.isIntersect(tank.getX(), tank.getY(), TANK_SIZE, TANK_SIZE,
			x, y, TANK_SIZE, TANK_SIZE)) {
			return std::tuple<int, int>{-1, -1};
		}
	}
	if (hit.isIntersect(player.getX(), player.getY(), TANK_SIZE, TANK_SIZE,
		x, y, TANK_SIZE, TANK_SIZE)) {
		return std::tuple<int, int>{-1, -1};
	}

	return std::tuple<int, int>{x, y};
}