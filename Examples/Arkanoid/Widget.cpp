#include "Widget.h"
#include "ui_Widget.h"

#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ball(0, 0, 10, 10), board(0, 0, 50, 5),
    ball_x(0), ball_y(0), ball_dx(2), ball_dy(2),
    board_x(0), board_y(0), board_dx(18), board_dy(18),
    loose(false),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    startTimer(20);

    ball_x = rect().center().x();
    ball_y = 10;

    board_x = rect().center().x();
    board_y = rect().height() - 20;

    ball.moveCenter(rect().center());
    board.moveCenter(QPoint(board_x, board_y));
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!loose) {
        painter.setPen(QPen(Qt::red, 1));
        painter.setBrush(QBrush(Qt::Dense4Pattern));
        painter.drawEllipse(ball);
        painter.drawRect(board);
    } else {
        QString str = tr("You loose!");
        QString str_please = tr("Please press \"Space\" bar");
        QFont font = painter.font();
        font.setPixelSize(72);
        painter.fillRect(rect(), Qt::red);
        painter.setPen(Qt::white);
        painter.setFont(font);
        painter.drawText(rect().center().x() - painter.fontMetrics().width(str) / 2,
                         rect().center().y() + 72 / 3, str);
        font.setPixelSize(24);
        painter.setFont(font);
        painter.drawText(rect().center().x() - painter.fontMetrics().width(str_please) / 2,
                         rect().center().y() + 24 * 2 + 10, str_please);
    }
}

void Widget::timerEvent(QTimerEvent *)
{
    int rx = ball.right() + ball.width() / 2;
    int ry = ball.bottom() + ball.height() / 2;
    int sx = ball.left();
    int sy = ball.top();

    if (rx > rect().width() || sx <= rect().left()) {
        ball_dx = -ball_dx;
    }

    if (ry > board.top()) {
        if (rx > board.left() && rx <= board.right()) {
            ball_dy = -ball_dy;
        }
    }

    if (ry > rect().height()) {
        loose = true;
        ball_x = ball_y = 0;
    }

    if(sy <= rect().top()) {
        ball_dy = -ball_dy;
    }

    ball_x+=ball_dx;
    ball_y+=ball_dy;

    ball.moveTo(QPoint(ball_x, ball_y));

    emit update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            if (board.left() > rect().left()) {
                board_x-=board_dx;
            }
            break;
        case Qt::Key_Right:
            if (board.right() < rect().right()) {
                board_x+=board_dx;
            }
            break;
        case Qt::Key_Space:
            ball_x = rect().center().x();
            ball_y = 10;
            board_x = rect().center().x();
            board_y = rect().height() - 20;
            loose = false;
            break;
        default:
            break;
    }

    board.moveCenter(QPoint(board_x, board_y));

    emit update();
}

Widget::~Widget()
{
    delete ui;
}
