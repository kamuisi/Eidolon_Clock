#ifndef MANAGER_H
#define MANAGER_H
#include <ClassTime.h>
#include <QLabel>
#include <QApplication>
#include <QTimer>
#include <QHBoxLayout>
#include <QWidget>
#include <QProcess>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
class Manager : public QWidget
{
Q_OBJECT
private:
    std::string DayorNight;
    QProcess *process;
    QFile *FileVal;
    Time EidolonTime;
    std::fstream src;
    QLabel *LabelText;
public:
    Manager();
    void GetDataAPI();
    std::string GetTime();
public slots:
    void CounterTime();
};

#endif // MANAGER_H
