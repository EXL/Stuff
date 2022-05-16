#include "Button.h"

#include <QPainter>

Button::Button(QWidget *parent) :
    QPushButton(parent),
    size(50), mark_size(2),
    isPressed(false), isCross(true)
{
    setFixedSize(QSize(size, size));
}

void Button::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    QRect buttonSubStrate(0, 0, height() - painter.pen().width(), width() - painter.pen().width());
    painter.drawRect(buttonSubStrate);

    QRect buttonRect(mark_size, mark_size,
                     height() - mark_size * 2 - painter.pen().width(),
                     width() - mark_size * 2 - painter.pen().width());

    painter.drawRect(buttonRect);

    painter.setPen(QPen(Qt::black, 3));
    if (isPressed) {
        if (!isCross) {
            painter.drawEllipse(mark_size + painter.pen().width(), mark_size + painter.pen().width(),
                                width() - mark_size * 2 - painter.pen().width() - painter.pen().width(),
                                height() - mark_size * 2 - painter.pen().width() - painter.pen().width());
        } else {
            painter.drawLine(mark_size + painter.pen().width(), mark_size + painter.pen().width(),
                             width() - mark_size - painter.pen().width(), height() - mark_size - painter.pen().width());
            painter.drawLine(width() - mark_size - painter.pen().width(), mark_size + painter.pen().width(),
                             mark_size + painter.pen().width(), height() - mark_size - painter.pen().width());
        }
    }
}

void Button::slotButtonPushed(bool qCross)
{
    if (!isPressed) {
        isCross = qCross;
        isPressed = true;
    }

    emit update();
}

void Button::setIsCross(bool value)
{
    isCross = value;
}

void Button::setIsPressed(bool value)
{
    isPressed = value;
}

bool Button::getIsPressed() const
{
    return isPressed;
}

bool Button::getIsState() const
{
    return isCross;
}

Button::~Button()
{

}
