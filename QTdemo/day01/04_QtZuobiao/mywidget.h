#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "mybutton.h"


class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();  //析构函数

private:
     MyButton *b3;

};
#endif // MYWIDGET_H
