#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLCDNumber>
#include <QTime>
#include <QTimer>

class LCDNumber : public QLCDNumber
{
    Q_OBJECT

public:
    explicit LCDNumber(QWidget *parent = 0);
    ~LCDNumber();

public slots:
    void setDisplay();

public:
    void start_Timer(int);
    void set_Time(int, int);

private:
    uint idleTime();
    bool shutDownComputer();

private:
    int timeEnd;
    bool firstTick;

private:
    QTimer* timer;
    QTime*  timeValue;
};

#endif // LCDNUMBER_H
