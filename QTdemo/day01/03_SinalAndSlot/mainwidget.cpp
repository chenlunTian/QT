#include "mainwidget.h"
//#include <QPushButton>
#include <QDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setParent(this);          //setParent指定父对象
    b1.setText("close");           //注意是点 .
    b1.move(100,100);

    b2 = new QPushButton(this);  //通过构造函数指定父对象
    b2->setText("abc");          //注意是箭头 ->

    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);
    /* &b1:信号发生者，指针类型
     * &QPushButton::pressed ： 处理的信号， &发送者的类名::信号名字
     * this:信号接收者
     * &MainWidget::close: 槽函数，信号处理函数 &接收的类名::槽函数的名字
     */

    /* 自定义槽，普通函数的用法
     * Qt5：任意成员函数，普通全局函数，静态函数
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号都没有返回值，所以，槽函数一定没有返回值
     */
    connect(b2,&QPushButton::released,this,&MainWidget::mySlot);//注意b2不需要取地址
    connect(b2,&QPushButton::released,&b1,&QPushButton::hide);//注意b2不需要取地址

    /* 信号:短信
     * 槽函数：接收短信的手机
     */

    setWindowTitle("老大");   //等价于 this->setWindowTitle("老大");
    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50,50);

    //显示子窗口
//    w.show();
    connect(&b3,&QPushButton::released,this,&MainWidget::changeWin);

    //处理子窗口的信号
    void (SubWidget::*funSignal)()= &SubWidget::MySignal;
    connect(&w,funSignal,this,&MainWidget::dealSub);

//    void (SubWidget::*testSignal)(int,QString)=&SubWidget::MySignal;
//    connect(&w,testSignal,this,&MainWidget::dealSlot);

    //Qt4信号连接
    //Qt4槽函数必须有slots关键字来修饰
    connect(&w,SIGNAL(MySignal(int,QString)),this,SLOT(dealSlot(int,QString)));
    //SIGNAL SLOT 将函数名字 -> 字符串  不进行错误检查

    //Lambda表达式，匿名函数对象
    /*            [=]() mutable
            {
                b4->setText("123");
                qDebug()<<"1111111";
            }
     */
    //C++11增加的新特性， 项目文件： CONFIG += c++11
    //Qt配合信号一起使用，非常方便

    QPushButton *b4 = new QPushButton(this);
    b4->setText("Lambda表达式");
    b4->move(150,150);
    connect(b4,&QPushButton::released,
            // = :把外部所有局部变量、类中所有成员以值传递方式（只读）
            // this:类中所有成员以值传递方式（只读）
            // & : 把外部所有局部变量，引用符号（只读）
            // mutable可编辑
            [=]() mutable
            {
                b4->setText("123");
                qDebug()<<"1111111";
            }
            );
    //传参数的Lambda表达式方式
    connect(b4,&QPushButton::clicked,
            [=](bool isCheck)
            {
                qDebug()<<isCheck;
            }
            );
    resize(400,300);

}
void MainWidget::dealSlot(int a,QString str)
{
    //str.toUtf8() -> 字节数组 QByteArray
    //...data() -> QByteArray -> char *
    qDebug()<<a<<str.toUtf8().data();
}
void MainWidget::mySlot()
{
    b2->setText("123");
}

void MainWidget::changeWin()
{
    //显示子窗口
    w.show();
    //隐藏主窗口
    this->hide();

}

void MainWidget::dealSub()
{
    //隐藏子窗口
    w.hide();
    //显示主窗口
    this->show();

}

MainWidget::~MainWidget()
{

}

