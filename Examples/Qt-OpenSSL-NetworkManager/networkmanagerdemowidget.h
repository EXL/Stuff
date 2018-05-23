#ifndef NETWORKMANAGERDEMOWIDGET_H
#define NETWORKMANAGERDEMOWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

namespace Ui {
class NetworkManagerDemoWidget;
}

class NetworkManagerDemoWidget : public QWidget {
    Q_OBJECT

public:
    explicit NetworkManagerDemoWidget( QWidget* parent = 0 );
    ~NetworkManagerDemoWidget();

private slots:
    void onGo();
    void onFinished( QNetworkReply* reply );

private:
    Ui::NetworkManagerDemoWidget* ui;

    QNetworkAccessManager m_manager;

};

#endif // NETWORKMANAGERDEMOWIDGET_H
