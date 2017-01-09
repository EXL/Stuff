#include "Widget.h"
#include "ui_Widget.h"

#include <QCursor>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->pushButton->installEventFilter(this);

    startTimer(10);
}

void Widget::timerEvent(QTimerEvent *)
{
    if (buttonCoords().contains(QCursor::pos())) {
        moveButton();
    }
}

bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->pushButton) {
        if (event->type() == QEvent::KeyPress) {
            return true;
        }
    }

    return QWidget::eventFilter(obj, event);
}

QRect Widget::buttonCoords() const
{
    QPoint globalCoords = ui->pushButton->mapToGlobal(QPoint(0,0));

    int x = globalCoords.x();
    int y = globalCoords.y();

    QPoint lastCorner;
    lastCorner.setX(x + ui->pushButton->width());
    lastCorner.setY(y + ui->pushButton->height());

    return QRect(globalCoords, lastCorner);
}

void Widget::moveButton()
{
    ui->pushButton->move(generateValidPoint());
}

QPoint Widget::generateValidPoint() const
{
    int eps = 5;

    int x = ui->pushButton->pos().x();
    int y = ui->pushButton->pos().y();

    if (buttonCoords().center().x() < QCursor::pos().x()) {
        x = qrand() % eps - ui->pushButton->width() / 4 + ui->pushButton->pos().x();
    }

    if (buttonCoords().center().y() < QCursor::pos().y()) {
        y = qrand() % eps - ui->pushButton->height() / 2 + ui->pushButton->pos().y();
    }

    if (buttonCoords().center().x() >= QCursor::pos().x()) {
        x = qrand() % eps + ui->pushButton->width() / 4 + ui->pushButton->pos().x();
    }

    if (buttonCoords().center().y() >= QCursor::pos().y()) {
        y = qrand() % eps + ui->pushButton->height() / 2 + ui->pushButton->pos().y();
    }

    if (!rect().contains(QRect(x, y, ui->pushButton->width(), ui->pushButton->height()))) {
        if (rect().x() < x) {
            x = qrand() % eps - ui->pushButton->width() / 4 + ui->pushButton->pos().x();
        }

        if (rect().y() < y) {
            y = qrand() % eps - ui->pushButton->height() / 2 + ui->pushButton->pos().y();
        }

        if (rect().x() >= x) {
            x = qrand() % eps + ui->pushButton->width() / 4 + ui->pushButton->pos().x();
        }

        if (rect().y() >= y) {
            y = qrand() % eps + ui->pushButton->height() / 2 + ui->pushButton->pos().y();
        }
    }

    return QPoint(x, y);
}

void Widget::on_pushButton_clicked()
{
    QMessageBox::information(this, tr("Win!"), tr("Oh Yeah! You win!"));
}

Widget::~Widget()
{
    delete ui;
}
