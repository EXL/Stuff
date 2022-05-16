#include "Dialog.h"
#include "ui_Dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::wheelEvent(QWheelEvent *event)
{
    if (ui->label->pixmap()) {
        if (event->delta() < 0) {
            (scaledFactor < 0.2) ? scaledFactor = 0.1 : scaledFactor -= 0.1;
        } else {
            (scaledFactor > 9.9) ? scaledFactor = 10.0 : scaledFactor += 0.1;
        }
        zoom();
    }
    setWindowTitle(tr("Preview zoom x%1, %2x%3").arg(scaledFactor).arg(w).arg(h));
}

void Dialog::zoom()
{
    QMatrix tr;
    tr.scale(scaledFactor, scaledFactor);
    QPixmap pix = originalPixmap.transformed(tr);
    ui->label->setPixmap(pix);
}

void Dialog::zoomReset()
{
    scaledFactor = 1.0;
    setWindowTitle(tr("Preview zoom x1.0, %1x%2").arg(w).arg(h));
    zoom();
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        zoomReset();
    }
}

void Dialog::setImageData(const QImage &image)
{
    w = image.width();
    h = image.height();
    originalPixmap = QPixmap::fromImage(image);
    ui->label->setPixmap(originalPixmap);
    zoomReset();
}

Dialog::~Dialog()
{
    delete ui;
}
