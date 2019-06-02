#include "Timer.h"


Timer::Timer() : dif_time() {}

void Timer::setDifTime(double t) {
	dif_time = t;           //����ʱ���
	start();                //��ʼ��ʱ
}

bool Timer::isTimeOut() {
	stop(); //��ý���ʱ���Ա����ʱ���
	if (times() >= dif_time) {
		start(); //���¼�ʱ
		return true;
	}
	return false;
}

inline void Timer::start() {
	begin = std::chrono::steady_clock::now();
}

inline void Timer::stop() {
	end = std::chrono::steady_clock::now();
}

inline double Timer::times() {
	//��ʱ���תΪ����
	std::chrono::duration<double, std::ratio<1, 1000>> times = end - begin;
	return times.count();
}
