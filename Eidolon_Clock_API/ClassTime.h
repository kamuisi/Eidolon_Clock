#ifndef ClassTime_H
#define ClassTime_H
#include "Header.h"
class Time
{
private:
    int iHour;
    int iMinute;
    int iSecond;

public:
    friend class Manager;
    friend Time operator--(Time &a);
    Time(int hr = 0, int min = 0, int sec = 0);
};
#endif
