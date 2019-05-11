#include "SelectPanel.h"
#include "struct.h"
#include "GameControl.h"
#include "Timer.h"
#include <iostream>

int main(void) {
	srand((unsigned)time(NULL));
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);            //���ڴ�С
	BeginBatchDraw();                                  //��ʼ������ͼ

	while (1) {
		SelectPanel s;                                     //ѡ�����
		s.select();
		GameControl gm;                                    //������Ϸ
		gm.gameLoop();
	}

	EndBatchDraw();                                    //����������ͼ
	closegraph();                                      //�رմ���
	return 0;
}