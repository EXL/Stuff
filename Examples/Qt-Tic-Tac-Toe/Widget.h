#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>

namespace Ui {
class Widget;
}

class Button;

#ifdef TEST
class QTextEdit;
class QDialog;
class QVBoxLayout;
class QPushButton;
#endif

class Widget : public QWidget
{
    Q_OBJECT

private:
    QGridLayout *gridLayout;
    Button *gameButton;
    bool qCross;
    bool qModeAI;
    int board[3][3];
    Button *buttonMatrix[3][3];

#ifdef TEST
    QDialog *testDialog;
    QTextEdit *textWidget;
    QHBoxLayout *othTestlayout;
    QPushButton *btn_OK;
    QPushButton *btn_Start;

    void destroyTestDialog();
    int test_setXO(int x, int y);
    QVector<QLine> *getTestVector() const;
#endif

private:
    int isGameOver();
    bool freeMoves() const;
    bool freeField(int x, int y) const;
    void clearGame();
    bool showMsgBox(int code);
    QPoint findFreeField() const;
    void aiMove();

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onButtonPushed();

#ifdef TEST
    void startTests();
    void testFunctions();
#endif

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
