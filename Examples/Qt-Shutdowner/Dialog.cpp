#include "Dialog.h"
#include "ui_Dialog.h"

#include "LCDNumber.h"

#include <QSettings>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QSettings settings("config.ini", QSettings::IniFormat);
    settings.beginGroup("Time");
    int minutes = settings.value("Minutes").toInt();
    int seconds = settings.value("Seconds").toInt();
    settings.endGroup();

    if (minutes == 0 && seconds == 0) {
        seconds = 15;
    }

    ui->lcdNumber->set_Time(minutes, seconds);
    ui->lcdNumber->start_Timer(1000);

    setWindowTitle("Shutdowner for J()KER by EXL, 2016");
    // setWindowFlags(Qt::FramelessWindowHint);
}

Dialog::~Dialog()
{
    delete ui;
}
