#include "struct.h"

void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg, UINT transparentcolor) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
	TransparentBlt(dstDC, x, y, w * 3, h * 3, srcDC, 0, 0, w, h, transparentcolor);
}

