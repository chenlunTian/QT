#ifndef USART_H
#define USART_H

#include <QWidget>

namespace Ui {
class Usart;
}

class Usart : public QWidget
{
    Q_OBJECT

public:
    explicit Usart(QWidget *parent = nullptr);
    ~Usart();

private:
    Ui::Usart *ui;
};

#endif // USART_H
