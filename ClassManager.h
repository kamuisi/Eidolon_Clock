#ifndef ClassManager_H
#define ClassManager_H
#include "ClassTime.h"
class Manager
{
private:
    Time BaseTime;
    Time EidolonTime;
    std::string DayorNight;
    std::fstream src;

public:
    void Input();
    void countLeapYears(long int &n1, long int &n2, std::tm *a);
    int FindNumberDifferentOfTwoDays(std::tm *a);
    void CalculatePresentTime();
    void CounterTime();
};
#endif