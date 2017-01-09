#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("://app.ico"));

    startTimer(100);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    static int count = 0;
    if(count) {
        QPixmap     pixmap("://app.ico");
        QPainter    painter(&pixmap);
        QFont       font;
        QRect       rect;

        int _pen_size = 20;
        int _size = pixmap.width() / 2 + _pen_size;
        rect.setRect(pixmap.width() - _size, 0, _size, _size);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        font = painter.font();

        if (count < 100) {
            font.setPixelSize(_size - _pen_size - 30);
        } else {
            font.setPixelSize(_size - _pen_size - 30 - 30);
            if (count >= 1000) {
                count = 999;
            }
        }
        painter.setFont(font);
        painter.setBrush(Qt::red);
        painter.setPen(QPen(QColor(150, 0, 24), 20));
        painter.drawEllipse(rect);
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, QString::number(count));
        setWindowIcon(QIcon(pixmap));

        ui->label->setPixmap(pixmap);
    }
    else {
        setWindowIcon(QIcon("://app.ico"));
    }

    count++;
}

MainWindow::~MainWindow()
{
    delete ui;
}
