#include "HitDection.h"

HitDection::HitDection(Map& m) :
	map(m), map_x(), map_y(),
	hit_flag(false) {}

bool HitDection::isIntersect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	//�ж��Ƿ��ཻ
	//�жϲ��ཻ�������Ȼ��ȡ�������ཻ�����
	return !(x1 + w1 <= x2 || y1 + h1 <= y2 || x2 + w2 <= x1 || y2 + h2 <= y1);
}

bool HitDection::dection(int x, int y, int w, int h) {
	bool flag = false;
	//���������Ƿ��ཻ
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			//ֻ��ǽ��������
			if (map.map[i][j] == '0') continue;
			//���Ͻ�����
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;

			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE, x, y, w, h)) {
				if (map.map[i][j] == '3')
					map.map[i][j] = 100;//��ǽ������
				flag = true;
			}
		}
	}
	return flag;
}

void HitDection::canGo(int& x, int& y, Dir d)
{
	//���������Ƿ��ཻ
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (map.map[i][j] == '0') continue;
			//���Ͻ�����
			map_x = j * BLOCK_SIZE + CENTER_X;
			map_y = i * BLOCK_SIZE + CENTER_Y;

			if (isIntersect(map_x, map_y, BLOCK_SIZE, BLOCK_SIZE, x, y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
				if (d == UP) y += 1;
				else if (d == DOWN)y -= 1;
				else if (d == LEFT) x += 1;
				else if (d == RIGHT) x -= 1;

				return;
			}
		}
	}
}

int HitDection::focus(std::shared_ptr<TankBase> & pl_tank,
	std::shared_ptr<Bullet> & pl_blt,
	std::list<std::pair<std::shared_ptr<TankBase>, std::shared_ptr<Bullet>>> & enemies)
{
	//�ж���ҵ��ӵ��Ƿ���е���
	for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++) {
		if (pl_blt->exist && isIntersect(pl_blt->x, pl_blt->y, 12, 12, enemy->first->x, enemy->first->y, BLOCK_SIZE * 2, BLOCK_SIZE * 2)) {
			//��Ѫ
			enemy->first->blood--;
			//�����ӵ�
			pl_blt->exist = false;
			pl_blt->clearOld();
			//�������
			if (enemy->first->blood <= 0) {
				enemy->first->clearOld();
				enemy->second->clearOld();
				enemies.erase(enemy);
			}
			return 1;
		}
	}
	return 0;
}