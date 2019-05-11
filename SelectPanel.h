#ifndef  _SELECT_PANEL_H_
#define _SELECT_PANEL_H_

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
	SelectResult select();

private:
	void runUp();                    //��������
	void changeShape();              //�ı��ͷ����
	void showArrow();                //��ʾ��ͷ
	int moveArrows();                //�ƶ���ͷλ��
	void clearOld();                 //���������ͼ

	IMAGE select_img;                //ѡ�����ͼƬ
	IMAGE arrows_img[2];             //��ͷͼƬ
	int arrows_pos;                  //��ͷλ��
	int cur_shape;                   //��ͷ��ǰ����
};

#endif // ! _SELECT_PANEL_H_