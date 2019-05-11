#include "GameControl.h"

GameControl::GameControl() {}

void GameControl::gameLoop() {
	map.showMap();
	addEnemy();
	enemies.push_back(EnemyTank(CENTER_X + BLOCK_SIZE*6, CENTER_Y, ORDINARY, PLAYER));
	blts_enemies.push_back(Bullet());
	while (true) {
		updatePlayer();
		updataEnemies();

		hit.focusTank(player, blt_player, enemies, blts_enemies);
		map.update();
		FlushBatchDraw();
		Sleep(5);
	}
}

inline void GameControl::updatePlayer() {
	//����̹��
	player.move();
	if (player.isMoving()) {
		hit.tankMove(player, map);//̹����ǽ��ײ���
		//̹����̹��֮����ײ���
		for (auto& enemy : enemies) {
			hit.hitTank(player, enemy);
		}
	}
	player.show();

	//�����ӵ�
	blt_player.shoot(player, false);
	if (blt_player.isExist()) {
		hit.hitWall(blt_player, map);
		blt_player.move();
	}

}

inline void GameControl::updataEnemies() {
	auto enemy = enemies.begin();
	auto blt = blts_enemies.begin();
	for (; enemy != enemies.end() && blt != blts_enemies.end(); enemy++, blt++) {
		//����̹��
		enemy->move(player.getX(), player.getY());
		if (enemy->isMoving()) {
			hit.tankMove(*enemy, map);
			hit.hitTank(*enemy, player);

			for (auto i_enemy = enemies.begin(); i_enemy != enemies.end(); i_enemy++) {
				if (enemy == i_enemy)continue;
				hit.hitTank(*enemy, *i_enemy);
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
	enemies.push_back(EnemyTank(CENTER_X, CENTER_Y, ORDINARY, PLAYER));
	blts_enemies.push_back(Bullet());
}