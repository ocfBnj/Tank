#pragma once

#include <chrono>
class Timer {
public:
	Timer();
	void setDifTime(double t);    
	bool isTimeOut();                                   //ʱ�䵽
	
private:
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	double dif_time;                                    //��¼ʱ����

	void start();                                       //��ʼ��ʱ
	void stop();                                        //��ý���ʱ��
	double times();                                     //����ʱ���
};

