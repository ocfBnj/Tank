#include "Bullet.h"

Bullet::Bullet() :
	x(0), y(0), dir(UP),
	speed(2), exist(false) {
	loadimage(&img_bullet[LEFT], _T(".\\res\\image\\bullet-0.gif"));
	loadimage(&img_bullet[UP], _T(".\\res\\image\\bullet-1.gif"));
	loadimage(&img_bullet[RIGHT], _T(".\\res\\image\\bullet-2.gif"));
	loadimage(&img_bullet[DOWN], _T(".\\res\\image\\bullet-3.gif"));
}

inline void Bullet::clearOld() const {
	clearrectangle(x, y, x + BULLET_SIZE, y + BULLET_SIZE);
}

void Bullet::shoot(const TankBase & tank, bool is_enemy) {
	if (exist) return; //�ӵ��Ѿ�����

	//���¿ո���ǵ���, �����ӵ�
	timer_shoot.stop();
	if (GetAsyncKeyState(' ') & 0x8000 || (is_enemy && timer_shoot.times() >= 2000)) {
		timer_shoot.start();
		//����̹�˷������ӵ�
		switch (tank.getDir()) {
		case UP:
			x = tank.getX() + 18;
			y = tank.getY() + 2;
			break;
		case DOWN:
			x = tank.getX() + 18;
			y = tank.getY() + BLOCK_SIZE;
			break;
		case LEFT:
			x = tank.getX() + 2;
			y = tank.getY() + 20;
			break;
		case RIGHT:
			x = tank.getX() + BLOCK_SIZE;
			y = tank.getY() + 20;
			break;
		default:
			break;
		}
		dir = tank.getDir(); //�ӵ������뷢���ӵ�ʱ̹�˷���һ��
		exist = true;
		if (!is_enemy) Sound::play(SHOOT);
		if (!is_enemy) {
			//Sound::play(SHOOT);
		}
	}
}

bool Bullet::move() {
	//�ӵ�������
	if (!exist)	return false;

	clearOld();
	switch (dir) {
	case UP:
		//�ж��Ƿ������߽�
		if (y - 4 <= CENTER_Y) {
			exist = false;
			return true;
		}
		y -= speed;
		break;
	case DOWN:
		if (y + 16 >= CENTER_Y + CENTER_HEIGHT) {
			exist = false;
			return true;
		}
		y += speed;
		break;
	case LEFT:
		if (x - 4 <= CENTER_X) {
			exist = false;
			return true;
		}
		x -= speed;
		break;
	case RIGHT:
		if (x + 16 >= CENTER_X + CENTER_WIDTH) {
			exist = false;
			return true;
		}
		x += speed;
		break;
	default:
		break;
	}
	transparentimage(NULL, x, y, &img_bullet[dir], 0xffc4c4);
	return false;
}

bool Bullet::isExist() const {
	return exist;
}

int Bullet::getX() const {
	return x;
}

int Bullet::getY() const {
	return y;
}

void Bullet::adjust() {
	clearOld();
	exist = false;
}
