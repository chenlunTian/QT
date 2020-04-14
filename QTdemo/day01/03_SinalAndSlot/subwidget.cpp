#include "subwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("小弟");
    b.setParent(this);
    b.setText("切换到主窗口");

    connect(&b,&QPushButton::clicked,this,&SubWidget::SendSlot);
    resize(400,300);
}

void SubWidget::SendSlot()
{
    emit MySignal();
    emit MySignal(250,"我是子窗口");
}
