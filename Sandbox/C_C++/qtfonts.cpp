// g++ -fPIC -I/usr/include/x86_64-linux-gnu/qt5/ -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore qfonts.cpp -lQt5Core -lQt5Gui -lQt5Widgets

#include <QApplication>
#include <QWidget>
#include <QPainter>

class Widget : public QWidget
{
protected:
    void paintEvent(QPaintEvent *)
    {
        const auto weights = {
            QFont::Thin,
            QFont::ExtraLight,
            QFont::Light,
            QFont::Normal,
            QFont::Medium,
            QFont::DemiBold,
            QFont::Bold,
            QFont::ExtraBold,
            QFont::Black
        };

        QPainter p(this);
        p.fillRect(rect(), Qt::white);
        p.setPen(Qt::black);

        int y = 30;
        for (const auto weight : weights) {
            QFont f("Consolas", 14, weight);
            Q_ASSERT(f.weight() == weight);

            p.setFont(f);
            p.drawText(5, y, QString("Qt Framework (%1)").arg(weight));
            y += p.fontMetrics().height();
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.setMinimumSize(200, 300);
    w.show();

    return a.exec();
}

