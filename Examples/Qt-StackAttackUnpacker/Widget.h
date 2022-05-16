#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void previewImage(int x, int y);
    void on_pushButton_clicked();

private:
    QByteArray getFileChunk(QFile& file, int offset, int byteSize) const;
    void openFiles(const QString &fileName, const QString &headerName);
    void writeFiles(const QList<QPair<QString, QByteArray> > list);
    void showFiles(const QList<QPair<QString, QByteArray> > list);

private:
    QList<QPair<QString, QByteArray> > list;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
