#ifndef _TANK_BASE_
#define _TANK_BASE_

#include "struct.h"

class TankBase {
public:
	TankBase(int _x, int _y, Dir d, int s, int b);
	virtual ~TankBase() = default;
	int getX() const;
	int getY() const;
	Dir getDir() const;
	void adjust();                    //��ײ�����λ��
	bool isMoving();                  //�Զ��ƶ��Ƿ���
	void died();                      //�����������ͼƬ
	void disBlood();                  //��һ��Ѫ
	bool haveDied();                  //����
protected:
	int x, y;                         //̹�ˣ����Ͻǣ�����
	Dir dir;                          //����
	bool flag_move;                   //�Զ��ƶ����
	int speed;                        //̹���ٶ�
	int cur_blood;                    //��ǰѪ��
	int cur_shape;                    //��ǰ����
	int steep;                        //�Զ��ƶ�ʱ�ƶ��˵Ĳ���

	void changeShape();               //�л�����
	void autoMove();                  //�����Զ��ƶ�
	void stopMove();                  //ֹͣ�Զ��ƶ�
	void clearOld() const;            //�����ͼ
};

#endif // !_TANK_BASE_