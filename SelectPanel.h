#pragma

#include "struct.h"
#include <graphics.h>
#include <conio.h>

//ѡ����
enum SelectResult {
	OnePlayer = 1,
	TwoPlater,
	Custom
};

class SelectPanel {
public:
	SelectPanel();
	SelectResult select();           //�ⲿ�ӿ�

private:
	void runUp();                    //��������
	void changeShape();              //�ı��ͷ����
	void showArrow();                //��ʾ��ͷ
	int moveArrows();                //�ƶ���ͷλ��

	IMAGE select_img;                //ѡ�����ͼƬ
	IMAGE arrows_img[2];             //��ͷͼƬ
	int arrows_pos;                  //��ͷλ��
	int cur_shape;                   //��ͷ��ǰ����
};

inline
SelectPanel::SelectPanel() :
	arrows_pos(1), cur_shape(0)
{
	//����ͼƬ
	loadimage(&select_img, _T(".\\res\\image\\select_player.gif"));
	loadimage(&arrows_img[0], _T(".\\res\\image\\0Player\\m0-2-1.gif"));
	loadimage(&arrows_img[1], _T(".\\res\\image\\0Player\\m0-2-2.gif"));
}

inline
void SelectPanel::runUp() {
	char c = 0;
	for (int y = WINDOW_HEIGHT; y > 0; y -= 4) {
		if (_kbhit())//����س���������
			if ((c = _getch()) == '\r') {
				break;
			}
		transparentimage(NULL, 0, y, &select_img, 0xffc4c4);
		FlushBatchDraw();
		Sleep(66);
	}
	transparentimage(NULL, 0, 0, &select_img, 0xffc4c4);
	FlushBatchDraw();
}

inline void SelectPanel::changeShape() {
	if (cur_shape == 0)
		cur_shape = 1;
	else
		cur_shape = 0;
}

inline
void SelectPanel::showArrow() {
	transparentimage(NULL, ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS, &arrows_img[cur_shape], 0xffc4c4);
	FlushBatchDraw();
	Sleep(10);
	changeShape();
}

inline
int SelectPanel::moveArrows() {
	showArrow();
	static char c = 0;
	if (_kbhit()) {
		c = _getch();
		switch (c) {
		case 'w':
			if (arrows_pos > 1 && arrows_pos <= 3) {
				//�����ǰλ�õļ�ͷ
				clearrectangle(ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS,
					ARROWS_X + BLOCK_SIZE * 2, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS + BLOCK_SIZE * 2);
				--arrows_pos;//�����ƶ�
			}
			break;
		case 's':
			if (arrows_pos >= 1 && arrows_pos < 3) {
				clearrectangle(ARROWS_X, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS,
					ARROWS_X + BLOCK_SIZE * 2, ARROWS_Y + (arrows_pos - 1) * ARROWS_DIS + BLOCK_SIZE * 2);
				++arrows_pos;//�����ƶ�
			}
			break;
		case '\r':
			return arrows_pos;
		default:
			break;
		}
	}
	return 0;
}

inline
SelectResult SelectPanel::select() {
	SelectResult ret;
	runUp();//��ʾ��������

	//�ƶ���ͷ
	while (!(ret = (SelectResult)moveArrows()));

	return ret;
}