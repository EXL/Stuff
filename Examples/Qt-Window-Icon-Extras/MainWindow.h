#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;

#ifdef Q_OS_WIN
#include <QtWinExtras>
#endif

namespace Ui {
class MainWindow;
}

QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)
QT_FORWARD_DECLARE_CLASS(QWinTaskbarProgress)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void timerEvent(QTimerEvent *);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *label;
#ifdef Q_OS_WIN
    QWinTaskbarProgress *progressTaskBar;
    QWinTaskbarButton *buttonTaskBar;
#endif
};

#endif // MAINWINDOW_H
