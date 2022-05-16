#include "TimeDialog.h"
#include "ui_TimeDialog.h"

#include "TimeTableModel.h"

#include <QTimer>

TimeDialog::TimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeDialog)
{
    ui->setupUi(this);

    tableModel = new TimeTableModel();
    ui->tableView->setModel(tableModel);
    ui->tableView->setColumnWidth(1, 250);

    setWindowTitle(tr("2038 problem"));
}

TimeDialog::~TimeDialog()
{
    delete ui;
}
