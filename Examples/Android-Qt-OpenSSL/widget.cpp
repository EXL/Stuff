#include "widget.h"
#include "ui_widget.h"

#include <QtNetwork/QSslSocket>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QString fb = QString("SSL version use for build: ") + QSslSocket::sslLibraryBuildVersionString() + "\n";
    QString fr = QString("SSL version use for run-time: ") + QSslSocket::sslLibraryVersionString() + "\n";
    QString fs = QString("SSL support: %1").arg(QSslSocket::supportsSsl()) + "\n";

    ui->textBrowser->setPlainText(fb + fr + fs);
}

Widget::~Widget()
{
    delete ui;
}
