#ifndef TIMETABLEMODEL_H
#define TIMETABLEMODEL_H

#include <QAbstractTableModel>

class TimeTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    int secSinceEpoch;

private:
    QString correctBinary(QString aString) const;

private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private slots:
    void changeSecs();

public:
    explicit TimeTableModel(QObject *parent = 0);

signals:

public slots:

};

#endif // TIMETABLEMODEL_H
