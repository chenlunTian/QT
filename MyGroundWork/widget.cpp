#include "widget.h"
#include "ui_widget.h"
//#include "flatui.h"
#define CURVE_CNT 10 //最多显示几条曲线
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    usart = new Usart(this);
    ui->usart->addWidget(usart);
    plot = new MultiCurvesPlot(CURVE_CNT,this);
    ui->customplot_2->addWidget(plot);
    plot->yAxis->setRange(-2.5, 2.5);//设置Y轴的范围
    plot->xAxis->setRange(0, 100);//设置X轴的范围
//    FlatUI::Instance()->setPushButtonQss(ui->CostBtn);
//    FlatUI::Instance()->setPushButtonQss(ui->HelpBtn);
//    FlatUI::Instance()->setPushButtonQss(ui->AboutBtn);

    connect(ui->List,&QComboBox::currentIndex,ui->stackedWidget,&QStackedWidget::currentIndex);


}

void Widget::changePage()
{
    int nCount = ui->stackedWidget->count();
        int nIndex = ui->stackedWidget->currentIndex();

        // 获取下一个需要显示的页面索引
        ++nIndex;

        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex >= nCount)
            nIndex = 0;

        ui->stackedWidget->setCurrentIndex(nIndex);
}

Widget::~Widget()
{
    delete ui;
}

