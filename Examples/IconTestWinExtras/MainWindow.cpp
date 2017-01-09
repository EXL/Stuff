#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QStatusBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon("://app.ico"));
    label = new QLabel(this);
    ui->statusBar->addWidget(label);

#ifdef Q_OS_WIN
    QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
    buttonTaskBar = new QWinTaskbarButton(this);
    buttonTaskBar->setWindow(windowHandle());
    progressTaskBar = buttonTaskBar->progress();
    progressTaskBar->setRange(0, 999);
    progressTaskBar->show();
#endif

    startTimer(100);
}

void MainWindow::timerEvent(QTimerEvent *)
{
    static int count = 0;
    QPixmap pixmap("://ellipse.png");

    if(count) {
        QPainter painter(&pixmap);
        QFont font;
        QRect rect;

        rect.setRect(0, 0, pixmap.width(), pixmap.height());
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        font = painter.font();

        if (count < 100) {
            font.setPixelSize(10);
        } else {
            font.setPixelSize(8);
            if (count >= 1000) {
                count = 999;
            }
        }
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(rect, Qt::AlignCenter, QString::number(count));
#ifdef Q_OS_WIN
        buttonTaskBar->setOverlayIcon(QIcon(pixmap));
#endif
        label->setPixmap(pixmap);
    }
    else {
#ifdef Q_OS_WIN
        buttonTaskBar->clearOverlayIcon();
        label->setPixmap(pixmap);
#endif
    }
#ifdef Q_OS_WIN
    progressTaskBar->setValue(count);
#endif

    count++;
}

MainWindow::~MainWindow()
{
    delete ui;
}
