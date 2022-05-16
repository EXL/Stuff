#include "TimeTableModel.h"

#include <QTimer>
#include <QDateTime>
#include <QColor>

#include <climits>
#include <time.h>

TimeTableModel::TimeTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    secSinceEpoch = INT_MAX - 6;

    QTimer *timer = new QTimer(this);
    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(changeSecs()));
}

QString TimeTableModel::correctBinary(QString aString) const
{
    aString.insert(0, "0");
    if (secSinceEpoch < 0) {
        aString.remove(0, 33);
    }

    /* |........8........17........26........35| */
    for (int i = 8; i < 36; i+=8+1) {
        aString.insert(i, " ");
    }

    return aString;
}

int TimeTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

int TimeTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

QVariant TimeTableModel::data(const QModelIndex &index, int role) const
{
    QString answer;

    if (role == Qt::BackgroundColorRole) {
        switch (index.column()) {
        case 0: {
            return QColor(72, 209, 204);
            break;
        }
        case 1: {
            return (secSinceEpoch > 0) ? QColor(152, 251, 152) : QColor(240, 128, 128);
            break;
        }
        default: {
            return QColor(255, 255, 255);
            break;
        }
        }
    }

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            switch (index.row()) {
            case 0:
            default:
                answer = QString("Binary:");
                break;
            case 1:
                answer = QString("Decimal:");
                break;
            case 2:
                answer = QString("Computer Date:");
                break;
            case 3:
                answer = QString("Real Date:");
                break;
            }
        } else if (index.column() == 1) {
            switch (index.row()) {
            case 0:
            default: {
                answer = correctBinary(QString::number(secSinceEpoch, 2));
                break;
            }
            case 1: {
                answer = QString::number(secSinceEpoch);
                break;
            }
            case 2: {
                time_t rawtime = secSinceEpoch;
                tm *tim = gmtime(&rawtime);

                /* Tue Jan 5 03:14:06 2038
                 * format:
                 * ddd MMM d HH:mm:ss yyyy */

                answer = QString(asctime(tim)).remove('\n').replace("  ", " ");
                break;
            }
            case 3: {
                answer = QString(QDateTime::fromTime_t(secSinceEpoch).toUTC().toString("ddd MMM d HH:mm:ss yyyy"));
                break;
            }
            }
        }
        return QVariant(answer);
    }
    return QVariant();
}

QVariant TimeTableModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QVariant();
}

void TimeTableModel::changeSecs()
{
    beginResetModel();
    secSinceEpoch++;
    endResetModel();
}
