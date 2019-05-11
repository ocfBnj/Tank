#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <graphics.h>
#pragma comment(lib, "MSIMG32.LIB")

// ͸����ͼ����
// ������
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);

//���ڴ�С
#define WINDOW_WIDTH	768
#define WINDOW_HEIGHT	672

//�м��ɫ��Ϸ����
#define CENTER_WIDTH	624
#define CENTER_HEIGHT	624

//��Ϸ����������Ͻǵ�����
#define CENTER_X		48
#define CENTER_Y		27

//��ͷλ��
#define ARROWS_X        210
#define ARROWS_Y        369
#define ARROWS_DIS      45

//�����С
#define BLOCK_SIZE      24

//�ӵ���С
#define BULLET_SIZE     12

//����
enum Dir {
	LEFT, UP, RIGHT, DOWN
};

#endif // !_STRUCT_H_