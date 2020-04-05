#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#define CURVE_CNT 10 //最多显示几条曲线

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    botton = new CheckBoxUiList(this);
    ui->btn->addWidget(botton);
    plot  = new MultiCurvesPlot(CURVE_CNT, this);
    ui->wave->addWidget(plot);  //放进布局中使用addWidget(plot)放进去就能直接自动调整大小
    plot->yAxis->setRange(-2.5, 2.5);//设置Y轴的范围
    on_setCheckBoxText_clicked(1);
    connect(plot,SLOT(valueChanged()),this,SLOT(setValue()));
    this->startTimer(20);//启动定时器，用于生成模拟点
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

//    double t = (double)(QDateTime::currentMSecsSinceEpoch()) / 1000.0;//当前时间
    t++;
    plot->addData(0, &t, qSin(t));//曲线0，sin曲线
    plot->addData(1, &t, qCos(t));//曲线1，cos曲线
    plot->addData(2, &t, 0.6 * qSin(t));//曲线2，sin
    plot->addData(3, &t, 0.5 * qCos(t));//曲线3，cos
    plot->addData(4, &t, 1);//曲线4，水平直线
    plot->addData(5, &t, 1.1);//曲线4，水平直线
    plot->addData(6, &t, 1.2);//曲线4，水平直线
    plot->addData(7, &t, 1.3);//曲线4，水平直线
    plot->addData(8, &t, 1.4);//曲线4，水平直线
    plot->addData(9, &t, 1.5);//曲线4，水平直线
    list = botton->All_selectedItems();
    if(lastlist!=list)
    {
       lastlist=list;
       plot->showCurves(list);//显示0号、1号、3号曲线
    }
    qDebug()<<"t"<<t;
}



void MainWindow::on_checkBox_tracer_clicked(bool checked)
{
    plot->setTracerEnable(checked);
}

void MainWindow::on_checkBox_scroll_clicked(bool checked)
{
    plot->setAutoScroll(checked);
}

void MainWindow::on_setCheckBoxText_clicked(int idx)
{
    botton->setCheckBoxText( idx, plot->getCurveName(idx));
}

void MainWindow::on_setTipText_clicked(int idx,QString _Text)
{
    botton->setTipText(idx,_Text);
}
