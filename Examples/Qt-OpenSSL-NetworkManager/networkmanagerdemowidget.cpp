#include "networkmanagerdemowidget.h"
#include "ui_networkmanagerdemowidget.h"

#include <QtNetwork/QSslSocket>
#include <QNetworkReply>
#include <QApplication>

NetworkManagerDemoWidget::NetworkManagerDemoWidget( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::NetworkManagerDemoWidget ) {
    ui->setupUi( this );

    connect( ui->bnGo, SIGNAL( clicked( bool ) ), SLOT( onGo() ) );
    connect( &m_manager, SIGNAL( finished( QNetworkReply* ) ), SLOT( onFinished( QNetworkReply* ) ) );
    connect( ui->pushButton, SIGNAL( clicked( bool ) ), qApp, SLOT( aboutQt() ) );

    QString fb = QString("SSL version use for build: ") + QSslSocket::sslLibraryBuildVersionString() + "\n";
    QString fr = QString("SSL version use for run-time: ") + QSslSocket::sslLibraryVersionString() + "\n";
    QString fs = QString("SSL support: %1").arg(QSslSocket::supportsSsl()) + "\n";
    ui->textEdit->setPlainText(fb + fr + fs);
}

NetworkManagerDemoWidget::~NetworkManagerDemoWidget() {
    delete ui;
}

void NetworkManagerDemoWidget::onGo() {
    ui->lbStatus->setText( "Working..." );

    QString urlText = ui->edUrl->text().trimmed();
    m_manager.get( QNetworkRequest( QUrl( urlText ) ) );
}

void NetworkManagerDemoWidget::onFinished( QNetworkReply* reply ) {
    if( reply->error() == QNetworkReply::NoError ) {
        QString data = QString::fromUtf8( reply->readAll() );
        ui->textEdit->setText( data );

        ui->lbStatus->setText( "Ready!" );
    } else {
        ui->lbStatus->setText( reply->errorString() );
    }
    reply->deleteLater();
}
