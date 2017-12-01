#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QString decodePackedGSM7HexString(unsigned char *in);
    ~Widget();

private:
    Ui::Widget *ui;

private slots:
   void on_decodedTE_textChanged();
};

#endif // WIDGET_H
