#ifndef ClassManager_H
#define ClassManager_H
#include "ClassTime.h"
#include <QLabel>
#include <QString>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include <QHBoxLayout>
class Manager : public QWidget
{
Q_OBJECT
private:
    Time BaseTime;
    Time EidolonTime;
    std::string DayorNight;
    std::fstream src;
    QLabel *LabelText;
public:
    Manager();
    void Input();
    void countLeapYears(long int &n1, long int &n2, std::tm *a);
    int FindNumberDifferentOfTwoDays(std::tm *a);
    void CalculatePresentTime();
    std::string GetTime();
public slots:
    void CounterTime();
};
#endif
