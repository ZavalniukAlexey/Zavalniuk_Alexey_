#include <windows.h>
#include "Consts.h"
class CStopwatch
{
public:
	CStopwatch();
	void start();
	int now();
	int time();
private:
	LARGE_INTEGER m_liPerfFreq_;
	LARGE_INTEGER m_liPerfStart_;
};

#ifdef MY_PERFORMENCE_COUNTER

CStopwatch::CStopwatch() {
    QueryPerformanceFrequency(&m_liPerfFreq_);
    start();
}

void CStopwatch::start() {
    QueryPerformanceCounter(&m_liPerfStart_);
}

int CStopwatch::now() {
        LARGE_INTEGER liPerfNow;
        QueryPerformanceCounter(&liPerfNow);
	return (((liPerfNow.QuadPart - m_liPerfStart_.QuadPart) * getMillis()) / m_liPerfFreq_.QuadPart);
}

int CStopwatch::time() {
    LARGE_INTEGER liPerfNow;
	QueryPerformanceCounter(&liPerfNow);
	return ((liPerfNow.QuadPart * getMillis()) / m_liPerfFreq_.QuadPart);
}

#endif
