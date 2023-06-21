

#include <QApplication>
#include <QProcess>
#include <Header.h>
#include <ClassTime.h>
#include <Manager.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager b;
    b.show();
    return a.exec();
}
