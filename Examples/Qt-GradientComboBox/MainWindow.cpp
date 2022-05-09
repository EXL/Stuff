#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeComboBox();

    colorizeComboBox(ui->comboBox, Qt::green, Qt::red, Qt::yellow);
}

void MainWindow::initializeComboBox()
{
    const int n = 50;
    for (size_t i = 0; i <= n; ++i) {
        ui->comboBox->insertItem(i, QString::number(getValue(i), 'f', 2));
        // ui->comboBox->setItemData(i, colorGenerator(Qt::green, Qt::red, i, n), Qt::BackgroundRole);
    }
}

qreal MainWindow::getValue(int aStep)
{
    return (qreal) aStep / 10;
}

QColor MainWindow::colorGenerator(QColor aBegin, QColor aEnd, int aStep, int aSize) const
{
    qreal rB, gB, bB;
    qreal rE, gE, bE;
    aBegin.getRgbF(&rB, &gB, &bB);
    aEnd.getRgbF(&rE, &gE, &bE);

    QColor color;
    color.setRgbF(colorInterpolate(rB, rE, aStep, aSize),
                  colorInterpolate(gB, gE, aStep, aSize),
                  colorInterpolate(bB, bE, aStep, aSize));
    return color;
}

void MainWindow::colorizeComboBox(QComboBox *aComboBox, QColor aBegin, QColor aEnd, QColor aMiddle)
{
    int _size = aComboBox->count();
    int _middle = _size / 2;

    qreal rB, gB, bB;
    qreal rE, gE, bE;
    qreal rM, gM, bM;

    aBegin.getRgbF(&rB, &gB, &bB);
    aEnd.getRgbF(&rE, &gE, &bE);
    aMiddle.getRgbF(&rM, &gM, &bM);

    for (int i = 0; i < _size; ++i) {
        QColor color;
        if (aMiddle != Qt::transparent) {
            if (i < _middle) {
                color.setRgbF(colorInterpolate(rB, rM, i, _middle),
                              colorInterpolate(gB, gM, i, _middle),
                              colorInterpolate(bB, bM, i, _middle));
            } else {
                color.setRgbF(colorInterpolate(rM, rE, i - _middle, _middle),
                              colorInterpolate(gM, gE, i - _middle, _middle),
                              colorInterpolate(bM, bE, i - _middle, _middle));
            }
        } else {
            color.setRgbF(colorInterpolate(rB, rE, i, _size),
                          colorInterpolate(gB, gE, i, _size),
                          colorInterpolate(bB, bE, i, _size));
        }
        aComboBox->setItemData(i, color, Qt::BackgroundRole);
    }
}

qreal MainWindow::colorInterpolate(qreal aBegin, qreal aEnd, int aStep, int aSize) const
{
    return (aBegin < aEnd) ? qAbs(((aEnd - aBegin) * ((qreal) aStep / aSize)) + aBegin) :
                             qAbs(((aBegin - aEnd) * (1 - ((qreal) aStep / aSize))) + aEnd);
}

MainWindow::~MainWindow()
{
    delete ui;
}
