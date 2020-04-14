#include "mywidget.h"
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    /*对于父窗口（主窗口），坐标系统相对于屏幕
     * 原点：相对于屏幕左上角
     * x:往右递增
     * y:往下递增
    */
    move(100,100);

    /*子窗口，坐标系统相对于父窗口
     * 原点：相对于窗口空白区域（不包括边框）左上角
     * x:往右递增
     * y:往下递增
    */
    QPushButton *b1 = new QPushButton(this);
    b1->move(0,0);
    b1->setText("T.T");
    b1->resize(100,100);

    b3 = new MyButton(this);
    b3->setText("123");

    //1）指定父对象后  2）直接或间接继承QObject
    //子对象如果是动态分配空间的new，不需要手动释放
    //系统会自动释放

}

MyWidget::~MyWidget()
{
}

