#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QPaintEvent>

class Button : public QPushButton
{
    Q_OBJECT

private:
    int size;
    int mark_size;
    bool isPressed;
    bool isCross;

public:
    explicit Button(QWidget *parent = 0);
    ~Button();

public:
    bool getIsPressed() const;
    bool getIsState() const;
    void setIsCross(bool value);
    void setIsPressed(bool value);

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void slotButtonPushed(bool qCross);
};

#endif // BUTTON_H
