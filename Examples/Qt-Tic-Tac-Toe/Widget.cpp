#include "Widget.h"
#include "ui_Widget.h"
#include "Button.h"

#include <QMessageBox>
#include <QDebug>

#ifdef TEST
#include <QVector>
#include <QDialog>
#include <QTextEdit>
#include <QSpacerItem>
#include <QDateTime>
#endif

Widget::Widget(QWidget *parent) :
    QWidget(parent), qCross(false),
    qModeAI(false), ui(new Ui::Widget)
{
    ui->setupUi(this);

    gridLayout = new QGridLayout();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            gameButton = new Button(this);
            board[i][j] = 0;
            buttonMatrix[i][j] = gameButton;
            gameButton->setObjectName(QString("%1%2").arg(i).arg(j));
            gameButton->setIsCross(qCross);
            gridLayout->addWidget(gameButton, i, j);
            connect(gameButton, SIGNAL(clicked()), this, SLOT(onButtonPushed()));
        }
    }

    setLayout(gridLayout);
    setFixedSize(sizeHint());
}

int Widget::isGameOver()
{
    for (int k = 1; k <= 2; ++k) {
        int diaX = 0;
        int diaY = 0;
        for (int i = 0; i < 3; ++i) {
            int ver = 0;
            int hor = 0;
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == k) {
                    ++ver;
                }
                if (board[j][i] == k) {
                    ++hor;
                }
                if (ver == 3 || hor == 3) {
                    return k;
                }
            }
            if (board[i][i] == k) {
                ++diaX;
            }
            if (board[2 - i][i] == k) {
                ++diaY;
            }
            if (diaX == 3 || diaY == 3) {
                return k;
            }
        }
    }

    if (!freeMoves()) {
        return 3;
    }

    return 0;
}

bool Widget::freeMoves() const
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Widget::freeField(int x, int y) const
{
    return (board[x][y] > 0) ? false : true;
}

void Widget::clearGame()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = 0;
            buttonMatrix[i][j]->setIsCross(qCross);
            buttonMatrix[i][j]->setIsPressed(false);
        }
    }

    emit update();
}

bool Widget::showMsgBox(int code)
{
    if (code != 3 && code != 0) {
        if (!freeMoves()) {
            qCross = !qCross;
        }
        QString cross = tr("cross");
        QString circle = tr("circle");
        QMessageBox::information(this, tr("Victory!"), tr("Win a player who played for the %1.").arg( (code == 2) ? cross : circle ));
        clearGame();
        return true;
    }

    if (code == 3) {
        qCross = !qCross;
        QMessageBox::information(this, tr("Draw!"), tr("The game ended in a draw."));
        clearGame();
        return true;
    }
    return false;
}

QPoint Widget::findFreeField() const
{
    int x;
    int y;

    for (int i = 0; i < 50; ++i) {
        x = qrand() % 2 + 1;
        y = qrand() % 2 + 1;
        if (freeField(x, y)) {
            return QPoint(x, y);
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (freeField(i, j)) {
                x = i;
                y = j;
            }
        }
    }
    return QPoint(x, y);
}

void Widget::aiMove()
{
    QPoint freeField = findFreeField();

    Button *button = buttonMatrix[freeField.x()][freeField.y()];
    bool qPressed = button->getIsPressed();

    if (!qPressed) {
        button->slotButtonPushed(qCross);
        qCross = !qCross;
        board[QString(button->objectName().at(0)).toInt()][QString(button->objectName().at(1)).toInt()] = (qCross) ? 1 : 2;
    }

    showMsgBox(isGameOver());
}

void Widget::onButtonPushed()
{
    Button *button = qobject_cast<Button *>(sender());
    bool qPressed = button->getIsPressed();

    if (!qPressed) {
        button->slotButtonPushed(qCross);
        qCross = !qCross;
        board[QString(button->objectName().at(0)).toInt()][QString(button->objectName().at(1)).toInt()] = (qCross) ? 1 : 2;

        if (qModeAI) {
            aiMove();
        }
    }

    if (showMsgBox(isGameOver())) {
        return;
    }
}

Widget::~Widget()
{
    delete gameButton;
    delete ui;
}

#ifdef TEST
void Widget::startTests()
{
    testDialog = new QDialog(this);
    textWidget = new QTextEdit(testDialog);
    textWidget->setReadOnly(true);
    QFont font("Monospace");
    textWidget->setFont(font);

    testDialog->setLayout(new QVBoxLayout());
    testDialog->layout()->addWidget(textWidget);

    othTestlayout = new QHBoxLayout();
    btn_OK = new QPushButton(tr("OK"), testDialog);
    btn_Start = new QPushButton(tr("Start"), testDialog);
    othTestlayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    othTestlayout->addWidget(btn_Start);
    othTestlayout->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Maximum));
    othTestlayout->addWidget(btn_OK);
    testDialog->layout()->addItem(othTestlayout);

    connect(btn_OK, SIGNAL(clicked()), testDialog, SLOT(close()));
    connect(btn_Start, SIGNAL(clicked()), this, SLOT(testFunctions()));

    testDialog->setWindowTitle(tr("Tic-Tac-Toe Tests"));
    testDialog->setFixedSize(400, 600);
    testDialog->exec();

    destroyTestDialog();
    clearGame();
}

void Widget::testFunctions()
{
    clearGame();
    textWidget->clear();
    textWidget->append("Start Tests: " + QDateTime::currentDateTime().toString(Qt::TextDate));

    QVector<QLine > *vect = getTestVector();

    for (int k = 0; k < 1; ++k) {

        qCross = !qCross;

        for (int i = 0; i < vect->size(); ++i) {

            if (test_setXO(vect->at(i).p1().x(), vect->at(i).p1().y())) {
                clearGame();
                qCross = false;
                continue;
            }
            if (test_setXO(vect->at(i).p2().x(), vect->at(i).p2().y())) {
                clearGame();
                qCross = false;
                continue;
            }
        }
    }

    delete vect;
}

int Widget::test_setXO(int x, int y)
{
    if (x > 2 || y > 2) {
        textWidget->append(QString("Error range: %1, %2").arg(x).arg(y));
        return 4;
    }

    textWidget->append(QString("Move: %1, %2").arg(x).arg(y));

    Button *button = buttonMatrix[x][y];
    bool qPressed = button->getIsPressed();

    if (!qPressed) {
        button->slotButtonPushed(qCross);
        qCross = !qCross;
        board[QString(button->objectName().at(0)).toInt()][QString(button->objectName().at(1)).toInt()] = (qCross) ? 1 : 2;
    }

    for (int i = 0; i < 3; ++i) {
        QString str = "|";
        for (int j = 0; j < 3; ++j) {
            str.append(((board[i][j] == 0) ? "E" : (board[i][j] == 1) ? "O" : "X")  + QString("|"));
        }
        textWidget->append(str);
    }

    textWidget->append("--------------");

    int res = isGameOver();

    switch (res) {
        case 1:
            textWidget->append("<font color=\"red\"><b>Circle Wins!</b></font>");
            break;
        case 2:
            textWidget->append("<font color=\"blue\"><b>Cross Wins!</b></font>");
            break;
        case 3:
            textWidget->append("<font color=\"green\"><b>Draw!</b></font>");
            break;
    }

    return res;
}

QVector<QLine> *Widget::getTestVector() const
{
    QVector<QLine >  *vect = new QVector<QLine >;
    vect->push_back(QLine(0, 0, 0, 2));
    vect->push_back(QLine(1, 0, 1, 2));
    vect->push_back(QLine(2, 0, 2, 2));

    vect->push_back(QLine(0, 1, 0, 2));
    vect->push_back(QLine(1, 1, 1, 2));
    vect->push_back(QLine(2, 1, 2, 2));

    vect->push_back(QLine(0, 2, 0, 0));
    vect->push_back(QLine(1, 2, 1, 0));
    vect->push_back(QLine(2, 2, 2, 0));
    //-------------------//
    vect->push_back(QLine(0, 0, 2, 0));
    vect->push_back(QLine(0, 1, 2, 1));
    vect->push_back(QLine(0, 2, 2, 2));

    vect->push_back(QLine(1, 0, 2, 0));
    vect->push_back(QLine(1, 1, 2, 1));
    vect->push_back(QLine(1, 2, 2, 2));

    vect->push_back(QLine(2, 0, 0, 0));
    vect->push_back(QLine(2, 1, 0, 1));
    vect->push_back(QLine(2, 2, 0, 2));
    //-------------------//
    vect->push_back(QLine(0, 0, 0, 1));
    vect->push_back(QLine(1, 1, 0, 2));
    vect->push_back(QLine(2, 2, 1, 2));

    vect->push_back(QLine(0, 2, 0, 1));
    vect->push_back(QLine(1, 1, 0, 0));
    vect->push_back(QLine(2, 0, 1, 0));
    //-------------------//
    vect->push_back(QLine(2, 1, 2, 2));
    vect->push_back(QLine(1, 2, 1, 1));
    vect->push_back(QLine(0, 1, 0, 2));
    vect->push_back(QLine(0, 0, 1, 0));
    vect->push_back(QLine(2, 0, 0, 0));

    return vect;
}

void Widget::destroyTestDialog()
{
    delete testDialog;
    delete ui;
}
#endif
