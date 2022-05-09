#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

private:
    QRect ball;
    QRect board;

private:
    int ball_x;
    int ball_y;
    int ball_dx;
    int ball_dy;
    int board_x;
    int board_y;
    int board_dx;
    int board_dy;
    bool loose;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
