#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
private:
    QRect buttonCoords() const;
    void moveButton();
    QPoint generateValidPoint() const;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void timerEvent(QTimerEvent *);
    bool eventFilter(QObject *, QEvent *);

private:
    Ui::Widget *ui;

private slots:
   void on_pushButton_clicked();
};

#endif // WIDGET_H
