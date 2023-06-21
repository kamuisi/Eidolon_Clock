#include "ClassManager.h"
#include <cstdlib>
Manager::Manager() : QWidget()
{
    Input();
    CalculatePresentTime();
    QString qstr = QString::fromStdString(GetTime());
    LabelText = new QLabel(qstr);
    QHBoxLayout *fitwidget = new QHBoxLayout();
    fitwidget->addWidget(LabelText);
    this->setLayout(fitwidget);
    LabelText->setFont(QFont("Time New Roman", 20, 75));
    LabelText->setAlignment(Qt::AlignCenter);
    LabelText->setGeometry(0,0,300,100);
    QTimer *timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this,SLOT(CounterTime()));
    timer->start(1000);
}
void Manager::Input()
{
    src.open("src.txt");
    src >> BaseTime.iMonth;
    src.ignore(2, '/');
    src >> BaseTime.iDay;
    src.ignore(2, '/');
    src >> BaseTime.iYear;
    src >> BaseTime.iHour;
    src.ignore(2, ':');
    src >> BaseTime.iMinute;
    src.ignore(2, ':');
    src >> BaseTime.iSecond;
    src >> EidolonTime.iHour;
    src.ignore(2, ':');
    src >> EidolonTime.iMinute;
    src.ignore(2, ':');
    src >> EidolonTime.iSecond;
    src >> DayorNight;
    src.close();
}
void Manager::countLeapYears(long int &n1, long int &n2, std::tm *a)
{
    int years = BaseTime.iYear;
    if (BaseTime.iMonth <= 2)
        years--;
    n1 += years / 4 - years / 100 + years / 400;
    years = a->tm_year + 1900;
    if (a->tm_mon + 1 <= 2)
        years--;
    n2 += years / 4 - years / 100 + years / 400;
}
int Manager::FindNumberDifferentOfTwoDays(std::tm *a)
{
    long int n1 = BaseTime.iYear * 365 + BaseTime.iDay;
    for (int i = 0; i < BaseTime.iMonth - 1; i++)
    {
        n1 += monthDays[i];
    }
    long int n2 = (a->tm_year + 1900) * 365 + a->tm_mday;
    for (int i = 0; i < a->tm_mon; i++)
    {
        n2 += monthDays[i];
    }
    countLeapYears(n1, n2, a);
    return (n2 - n1);
}
void Manager::CalculatePresentTime()
{
    long DayTime = 6000;
    long NightTime = 3000;
    long int TotalTime = 0;
    int DifferentDay = 0;
    std::time_t PresentTime = std::time(0);
    std::tm *now = std::localtime(&PresentTime);
    EidolonTime.iHour = BaseTime.iHour - now->tm_hour + EidolonTime.iHour;
    DifferentDay = FindNumberDifferentOfTwoDays(now);
    if (DifferentDay != 0)
    {
        EidolonTime.iHour -= DifferentDay * 24;
    }
    EidolonTime.iMinute = BaseTime.iMinute - now->tm_min + EidolonTime.iMinute;
    EidolonTime.iSecond = BaseTime.iSecond - now->tm_sec + EidolonTime.iSecond;
    TotalTime+= EidolonTime.iHour * 3600 + EidolonTime.iMinute * 60 + EidolonTime.iSecond - 4 - 8 * DifferentDay - DifferentDay - 2 - (4 * now->tm_hour)/12;
    do
    {
        if (DayorNight == "day")
        {
            TotalTime = NightTime - abs(TotalTime);
            DayorNight.replace(DayorNight.begin(), DayorNight.end(), "night");
        }
        else
        {
            TotalTime = DayTime - abs(TotalTime);
            DayorNight.replace(DayorNight.begin(), DayorNight.end(), "day");
        }
    } while (TotalTime < 0);
    EidolonTime.iHour = TotalTime / 3600;
    EidolonTime.iMinute = TotalTime / 60 - EidolonTime.iHour * 60;
    EidolonTime.iSecond = TotalTime - EidolonTime.iHour * 3600 - EidolonTime.iMinute * 60;
    if(DayorNight == "day")
    {
        DayorNight.replace(DayorNight.begin(), DayorNight.end(), "night");
    }
    else
    {
       DayorNight.replace(DayorNight.begin(), DayorNight.end(), "day");
    }
}
std::string Manager::GetTime()
{
    return "Time until " + DayorNight + '\n' + std::to_string(EidolonTime.iHour) + ':' + std::to_string(EidolonTime.iMinute) + ':' + std::to_string(EidolonTime.iSecond);
}
void Manager::CounterTime()
{
    --EidolonTime;
    if (EidolonTime.iHour == -1)
    {
        switch (DayorNight == "day" ? 1 : 0)
        {
       case 0:
       {
            EidolonTime.iHour = 0;
            EidolonTime.iMinute = 49;
            EidolonTime.iSecond = 59;
            DayorNight.replace(DayorNight.begin(), DayorNight.end(), "day");
            break;
       }
        case 1:
        {
            EidolonTime.iHour = 1;
            EidolonTime.iMinute = 39;
            EidolonTime.iSecond = 59;
            DayorNight.replace(DayorNight.begin(), DayorNight.end(), "night");
            break;
        }
        }
    }
    QString qstr = QString::fromStdString(GetTime());
    LabelText->setText(qstr);
}
