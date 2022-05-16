#include "Widget.h"
#include "ui_Widget.h"

#include "Dialog.h"

#include <QMessageBox>
#include <QLabel>
#include <QPicture>
#include <QDialog>
#include <QDir>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    openFiles("res.bin", "res-head.bin");
    openFiles("restit.bin", "restit-head.bin");

    showFiles(list);

    QStringList labels;
    labels << "Name" << "Preview";
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(previewImage(int,int)));
}

QByteArray Widget::getFileChunk(QFile &file, int offset, int byteSize) const
{
    file.seek(offset);
    return file.read(byteSize);
}

void Widget::openFiles(const QString& fileName, const QString& headerName)
{
    QFile fileRes(fileName);
    QFile fileResHead(headerName);

    if (fileRes.exists() && fileResHead.exists()) {
        fileRes.open(QIODevice::ReadOnly);
        fileResHead.open(QIODevice::ReadOnly);

        QString byteResHeadArray;
        byteResHeadArray = fileResHead.readAll();

        QStringList headerList = byteResHeadArray.split("\r\n");

        int header_size = headerList.at(0).toInt() * 2;

        int offset = 0;
        for (int i = 1; i < header_size; i+=2) {
            int size = headerList[i+1].toInt();
            QPair<QString, QByteArray> pair(headerList[i], getFileChunk(fileRes, offset, size));
            list.push_back(pair);
            offset+=size;
        }

        fileRes.close();
        fileResHead.close();
    }
}

void Widget::previewImage(int x, int y)
{
    if (y != 1) {
        return;
    }

    QImage image;
    image.loadFromData(list.at(x).second, "PNG");

    Dialog dialog;
    dialog.setImageData(image);
    dialog.exec();
}

void Widget::on_pushButton_clicked()
{
    writeFiles(list);
}

void Widget::writeFiles(const QList<QPair<QString, QByteArray> > list)
{
    ui->pushButton->setDisabled(true);
    QDir().mkdir("res");
    for (int i = 0; i < list.size(); ++i) {
        QFile writeFile(QString("res") + QDir().separator() + list.at(i).first);
        writeFile.open(QIODevice::WriteOnly);
        writeFile.write(list.at(i).second);
        writeFile.close();
    }
    QMessageBox::information(this, "The files were written!", QString("In directory res") + QDir().separator() + ".");
    ui->pushButton->setDisabled(false);
}

void Widget::showFiles(const QList<QPair<QString, QByteArray> > list)
{
    ui->tableWidget->setRowCount(list.size());
    ui->tableWidget->setColumnCount(2);

    for (int i = 0; i < list.size(); ++i) {
        QLabel *label = new QLabel(this);
        QTableWidgetItem *typeLabel = new QTableWidgetItem(list.at(i).first);
        QImage image;
        image.loadFromData(list.at(i).second, "PNG");

        label->setPixmap(QPixmap::fromImage(image));

        ui->tableWidget->setItem(i, 0, typeLabel);
        ui->tableWidget->setCellWidget(i, 1, label);
    }
}

Widget::~Widget()
{
    delete ui;
}
