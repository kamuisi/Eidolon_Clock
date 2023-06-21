#include <QApplication>
#include <Header.h>
#include <ClassTime.h>
#include <ClassManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Manager c;
    c.show();
    return a.exec();
}
