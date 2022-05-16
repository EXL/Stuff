#ifndef TIMEDIALOG_H
#define TIMEDIALOG_H

#include <QDialog>

namespace Ui {
class TimeDialog;
}

class TimeTableModel;

class TimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeDialog(QWidget *parent = 0);
    ~TimeDialog();

private:
    Ui::TimeDialog *ui;

private:
    TimeTableModel *tableModel;
};

#endif // TIMEDIALOG_H
