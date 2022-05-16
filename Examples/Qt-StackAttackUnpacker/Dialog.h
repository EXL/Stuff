#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QImage>
#include <QWheelEvent>
#include <QPaintEvent>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

    int w;
    int h;

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);

public:
    void setImageData(const QImage &image);

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    double scaledFactor;
    QPixmap originalPixmap;

private:
    void zoom();
    void zoomReset();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
