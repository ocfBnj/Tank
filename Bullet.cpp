#include "Bullet.h"

Bullet::Bullet() :
	x(0), y(0), dir(UP),
	speed(2), exist(false) {
	loadimage(&img_bullet[LEFT], _T(".\\res\\image\\bullet-0.gif"));
	loadimage(&img_bullet[UP], _T(".\\res\\image\\bullet-1.gif"));
	loadimage(&img_bullet[RIGHT], _T(".\\res\\image\\bullet-2.gif"));
	loadimage(&img_bullet[DOWN], _T(".\\res\\image\\bullet-3.gif"));
}

inline
void Bullet::clearOld() {
	clearrectangle(x, y, x + 12, y + 12);//���ԭλ��
}

bool Bullet::shoot(int _x, int _y, Dir d, bool b) {
	//�ӵ��Ѿ�����
	if (exist)return false;

	//���¿ո���ǵ���, �����ӵ�
	if (GetAsyncKeyState(' ') & 0x8000 || b) {
		switch (d)//����̹�˷������ӵ�
		{
		case UP:
			x = _x + 18;
			y = _y + 2;
			break;
		case DOWN:
			x = _x + 18;
			y = _y + BLOCK_SIZE;
			break;
		case LEFT:
			x = _x + 2;
			y = _y + 20;
			break;
		case RIGHT:
			x = _x + BLOCK_SIZE;
			y = _y + 20;
			break;
		default:
			break;
		}
		dir = d;           //�ӵ������뷢���ӵ�ʱ̹�˷���һ��
		exist = true;      //�ӵ�����
		return true;
	}
	return false;
}

bool Bullet::move() {
	//�ӵ�������
	if (!exist)
		return false;

	clearOld();//�����λ��ͼ
	switch (dir) {
	case UP:
		//�ж��Ƿ������߽�
		if (y - 4 <= CENTER_Y) {
			exist = false;//��ը
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