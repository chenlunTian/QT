#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>
class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = nullptr);
    void SendSlot();
private:
    QPushButton b;

signals:
    /*信号必须有signals关键字声明
     * 信号没有返回值，但可以有参数
     * 信号就是函数声明，只需声明，无需定义
     * 使用： emit MySignal();
     * 信号可以重载
     */
    void MySignal();
    void MySignal(int,QString);

};

#endif // SUBWIDGET_H
