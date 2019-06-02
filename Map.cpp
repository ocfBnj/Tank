#include "Map.h"

Map::Map() : need_update(true) {
	//����ͼƬ
	loadimage(&block_img[WALL], _T(".\\res\\image\\wall.gif"));
	loadimage(&block_img[STONE], _T(".\\res\\image\\stone.gif"));
	loadimage(&block_img[NOR_CAMP], _T(".\\res\\image\\camp0.gif"));
	loadimage(&block_img[DIS_CAMP], _T(".\\res\\image\\camp1.gif"));
	loadimage(&black, _T(".\\res\\image\\black.gif"));

	//��ʼ����Ϸ����
	setbkcolor(RGB(100, 100, 100));                           //��ɫ����
	cleardevice();                                            //��������Ϊ��ɫ
	setfillcolor(BLACK);                                      //��Ϸ����Ϊ��ɫ
	solidrectangle(CENTER_X, CENTER_Y, CENTER_X + CENTER_WIDTH, CENTER_Y + CENTER_HEIGHT);
	setbkcolor(BLACK);
}

void Map::showMap() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			switch (map[i][j]) {
			//case -1: //ש���ϽǱ�����
			//	//transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
			//	transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &black, 0xffc4c4);
			//	break;
			//case -2: //���Ͻ�
			//	//transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
			//	transparentimage(NULL, CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE / 2, CENTER_Y + i * BLOCK_SIZE, &black, 0xffc4c4);
			//	break;
			//case -3: //���½�
			//	//transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
			//	transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE / 2, &black, 0xffc4c4);
			//	break;
			//case -4: //���½�
			//	//transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
			//	transparentimage(NULL, CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE / 2, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE / 2, &black, 0xffc4c4);
			//	break;
			case '1': //��Ӫ
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[NOR_CAMP], 0xffc4c4);
				break;
			case '3': //ש
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[WALL], 0xffc4c4);
				coverWall(i, j);
				//transparentimage(NULL, CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE / 2, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE / 2, &black, 0xffc4c4);
				break;
			case '5': //��
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[STONE], 0xffc4c4);
				break;
			case 100: //���ӵ�ײ����ש
				solidrectangle(CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE,
					CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE);
				map[i][j] = '0';
				break;
			case 101: //��Ӫ���ݻ�
				transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &block_img[DIS_CAMP], 0xffc4c4);
				break;
			default:
				break;
			}
		}
	}
	need_update = false;
}

void Map::adjust(int i, int j) {
	if (map[i][j] == '3')                          //ǽ������
		map[i][j] = 100;
	else if (map[i][j] == '1' || map[i][j] == '9') //��Ӫ���ݻ�
		map[24][12] = 101;

	need_update = true;
}

void Map::adjust(int i, int j, int val) {
	cover[i][j][val] = 1;
	if (cover[i][j][0] == 1 && cover[i][j][1] == 1 && cover[i][j][2] == 1 && cover[i][j][3] == 1) {
		map[i][j] = 100;
	}
	need_update = true;
}

void Map::update() {
	if (need_update)
		showMap();
}

void Map::setNeedUpdate(bool b) {
	need_update = b;
}

void Map::coverWall(int i, int j) {
	if (cover[i][j][0] == 1) {
		transparentimage(NULL, CENTER_X + j * BLOCK_SIZE, CENTER_Y + i * BLOCK_SIZE, &black, 0xffc4c4);
	}
	if (cover[i][j][1] == 1) {
		transparentimage(NULL, CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE / 2, CENTER_Y + i * BLOCK_SIZE, &black, 0xffc4c4);
	}
	if (cover[i][j][2] == 1) {
		transparentimage(NULL, CENTER_X + j * BLOCK_SIZE , CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE / 2, &black, 0xffc4c4);
	}
	if (cover[i][j][3] == 1) {
		transparentimage(NULL, CENTER_X + j * BLOCK_SIZE + BLOCK_SIZE / 2, CENTER_Y + i * BLOCK_SIZE + BLOCK_SIZE / 2, &black, 0xffc4c4);
	}
}
