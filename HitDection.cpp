#include "HitDection.h"

bool HitDection::isIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) const {
	return !(x1 + w1 <= x2 || y1 + h1 <= y2 || x2 + w2 <= x1 || y2 + h2 <= y1);
}

bool HitDection::isIntersect(TankBase& tank1, TankBase& tank2) {
	return isIntersect(tank1.getX(), tank1.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2,
		tank2.getX(), tank2.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2);
}

void HitDection::noKnockWall(TankBase& tank, Map& map) {
	//�ж��Ƿ�ײǽ
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//���Ͻ�����
			int map_x = j * BLOCK_SIZE + CENTER_X;
			int map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				tank.getX(), tank.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
				tank.adjust();
				return;
			}
		}
	}
}

void HitDection::hitWall(Bullet& blt, Map& map) {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//���Ͻ�����
			int map_x = j * BLOCK_SIZE + CENTER_X;
			int map_y = i * BLOCK_SIZE + CENTER_Y;
			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE,
				blt.getRealX(), blt.getRealY(), blt.getWidth(), blt.getHeight())) {

				if (map.map[i][j] == '3' ||
					map.map[i][j] == '-1' ||
					map.map[i][j] == '-2' ||
					map.map[i][j] == '-3' ||
					map.map[i][j] == '-4') {

					if (isIntersect(map_x, map_y, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
						blt.getRealX(), blt.getRealY(), blt.getWidth(), blt.getHeight())
						&& map.cover[i][j][0] != 1) { //����
						map.adjust(i, j, 0);
						blt.adjust();
					}
					if (isIntersect(map_x + BLOCK_SIZE / 2, map_y, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
						blt.getRealX(), blt.getRealY(), blt.getWidth(), blt.getHeight())
						&& map.cover[i][j][1] != 1) { //����
						map.adjust(i, j, 1);
						blt.adjust();
					}
					if (isIntersect(map_x, map_y + BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
						blt.getRealX(), blt.getRealY(), blt.getWidth(), blt.getHeight())
						&& map.cover[i][j][2] != 1) { //����
						map.adjust(i, j, 2);
						blt.adjust();
					}
					if (isIntersect(map_x + BLOCK_SIZE / 2, map_y + BLOCK_SIZE / 2, BLOCK_SIZE / 2, BLOCK_SIZE / 2,
						blt.getRealX(), blt.getRealY(), blt.getWidth(), blt.getHeight())
						&& map.cover[i][j][3] != 1) { //����
						map.adjust(i, j, 3);
						blt.adjust();
					}
				} else {
					map.adjust(i, j);
					blt.adjust();
				}


			}
		}
	}
}

void HitDection::impactTank(TankBase& tank1, TankBase& tank2) {
	if (isIntersect(tank1, tank2)) {
		tank1.adjust();
		return;
	}
}

void HitDection::focusBullet(TankBase& player, Bullet& pl_blt,
	std::list<EnemyTank>& enemies, std::list<Bullet>& enemies_blt) {

	auto enemy = enemies.begin();
	auto enemy_blt = enemies_blt.begin();

	for (; enemy != enemies.end() && enemy_blt != enemies_blt.end(); enemy++, enemy_blt++) {
		//�ж�����ӵ��Ƿ���е���
		if (pl_blt.isExist() && isIntersect(pl_blt.getRealX(), pl_blt.getRealY(), pl_blt.getWidth(), pl_blt.getHeight(),
			enemy->getX(), enemy->getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {

			pl_blt.adjust();
			enemy->disBlood();

			if (enemy->isDied()) {
				Sound::play(ENEMY_DIE);
				enemy->die();
				enemy_blt->adjust();
				enemies_blt.erase(enemy_blt);
				enemies.erase(enemy);
			}
			break;
		}

		//�ж��ӵ����ӵ�֮������
		if (pl_blt.isExist() && enemy_blt->isExist() &&
			isIntersect(pl_blt.getRealX(), pl_blt.getRealY(), BULLET_SIZE, BULLET_SIZE,
				enemy_blt->getRealX(), enemy_blt->getRealY(), enemy_blt->getWidth(), enemy_blt->getHeight())) {
			pl_blt.adjust();
			enemy_blt->adjust();
			break;
		}

		//�жϵ����ӵ��Ƿ�������
		if (enemy_blt->isExist() && isIntersect(enemy_blt->getRealX(), enemy_blt->getRealY(), BULLET_SIZE, BULLET_SIZE,
			player.getX(), player.getY(), BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {

			enemy_blt->adjust();
			player.disBlood();
			dynamic_cast<PlayerTank&>(player).moveToStart();
			Sound::play(PLAYER_DIE);
			if (player.isDied()) {
				player.die();
			}
			break;
		}
	}
}