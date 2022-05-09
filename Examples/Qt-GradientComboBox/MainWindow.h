#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QComboBox;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initializeComboBox();
    qreal getValue(int aStep);
    QColor colorGenerator(QColor aBegin, QColor aEnd, int aStep, int aSize) const;
    void colorizeComboBox(QComboBox *aComboBox, QColor aBegin, QColor aEnd, QColor aMiddle = Qt::transparent);
    qreal colorInterpolate(qreal aBegin, qreal aEnd, int aStep, int aSize) const;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
