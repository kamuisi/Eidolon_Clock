#include "ClassTime.h"
Time operator--(Time &a)
{
    a.iSecond--;
    if (a.iSecond == -1)
    {
        a.iSecond = 59;
        a.iMinute--;
        if (a.iMinute == -1)
        {
            a.iMinute = 59;
            a.iHour--;
        }
    }
    return Time(a.iHour, a.iMinute, a.iSecond);
}
Time::Time(int hr, int min, int sec)
    : iHour(hr), iMinute(min), iSecond(sec)
{}