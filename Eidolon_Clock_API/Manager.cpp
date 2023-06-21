#include <Manager.h>
Manager::Manager() : QWidget()
{
    GetDataAPI();
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
    connect(timer, SIGNAL(timeout()), this, SLOT(CounterTime()));
    timer->start(1000);
}
void Manager::GetDataAPI()
{
    QString val;
    char a;
    int b;
    process = new QProcess();
    process->setProgram( "sus.bat" );
    process->setArguments({"sus.bat"});
    process->start();
    if(process->waitForFinished() == 1)
    {
        FileVal = new QFile();
        FileVal->setFileName("sus.json");
        FileVal->open(QIODevice::ReadOnly | QIODevice::Text);
        val = FileVal->readAll();
        FileVal->close();
        QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject set = d.object();
        QJsonValue value1 = set.value(QString("timeLeft"));
        QJsonValue value2 = set.value(QString("state"));
        DayorNight = QString(value2.toString()).toStdString();
        src.open("src.txt");
        src << QString(value1.toString()).toStdString();
        src.close();
        src.open("src.txt");
        src >> EidolonTime.iHour;
        src >> a;
        src >> EidolonTime.iMinute;
        src >> EidolonTime.iSecond;
        src.close();
        if ( a == 'm')
        {
            b = EidolonTime.iMinute;
            EidolonTime.iMinute = EidolonTime.iHour;
            EidolonTime.iSecond = b;
            EidolonTime.iHour = 0;
        }
        if( DayorNight == "day")
        {
            DayorNight = "night";
        }
        else
        {
            DayorNight = "day";
        }
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
