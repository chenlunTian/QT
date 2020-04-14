#include "mywidget.h"

//QApplication应用程序类
//Qt头文件没有.h
//头文件和类名一样
#include <QApplication>

int main(int argc, char *argv[])
{
    //有且只有一个应用程序类对象
    QApplication a(argc, argv);

    //MyWidget继承与QWidget，QWidget是一个窗口基类
    //所以MyWidget也是窗口类
    //w就是一个窗口
    MyWidget w;

    //窗口创建默认是隐藏，需要人为显示
    w.show();

    //a.exec(); 让程序一直执行，等待用户操作
    return a.exec();
}
