#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHostAddress>
#include <QString>
#include <QDateTime>

#include <iostream>
#include <cstdlib>
#include <ctime>
#define random(x) rand()%(x)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //固定窗口大小
    this->setFixedSize(this->width(), this->height());
    this->setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    setWindowTitle("串口助手2018");

    /*************曲线绘制区初始化**************/
    //添加图层
    ui->WID_customPlot->addGraph();
    //设置画笔颜色
    ui->WID_customPlot->graph(0)->setPen(QPen(Qt::red));// 设置画笔颜色
    ui->WID_customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);//设置连线
    ui->WID_customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);//设置坐标点形状
    ui->WID_customPlot->addGraph();
    ui->WID_customPlot->graph(1)->setPen(QPen(Qt::green));
    ui->WID_customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->WID_customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->WID_customPlot->addGraph();
    ui->WID_customPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->WID_customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
    ui->WID_customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->WID_customPlot->addGraph();
    ui->WID_customPlot->graph(3)->setPen(QPen(Qt::black));
    ui->WID_customPlot->graph(3)->setLineStyle(QCPGraph::lsLine);
    ui->WID_customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    //设置坐标轴标题
    ui->WID_customPlot->xAxis->setLabel("时间");
    ui->WID_customPlot->yAxis->setLabel("电压/电流/频率/功率");

    //ui->WID_customPlot->yAxis->setRange(0,300);
    //自适应坐标轴
    //ui->WID_customPlot->graph(0)->rescaleAxes();
    //ui->WID_customPlot->graph(1)->rescaleAxes();
    //ui->WID_customPlot->graph(2)->rescaleAxes();
    //ui->WID_customPlot->graph(3)->rescaleAxes();
    //可滚动变化
    ui->WID_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);//可拖拽 鼠标滚轮
    ui->WID_customPlot->legend->setVisible(true);//显示右上角折线标签
    ui->WID_customPlot->graph(0)->setName("电压");
    ui->WID_customPlot->graph(1)->setName("电流");
    ui->WID_customPlot->graph(2)->setName("频率");
    ui->WID_customPlot->graph(3)->setName("功率");

 /*   // 创建一个坐标轴矩形
    QCPAxisRect *volumeAxisRect = new QCPAxisRect(ui->WID_customPlot);
    ui->WID_customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
    volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
    // 设置自己构造的坐标轴矩形属性
    ui->WID_customPlot->plotLayout()->setRowSpacing(0);
    volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));*/
    // 构造一个新的坐标轴刻度计算类
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("hh:mm:ss");
    //volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);//赋予自己构造的坐标轴矩形的x轴一个新的刻度计算类
    //volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
    //ui->WID_customPlot->xAxis->setBasePen(Qt::NoPen);
    //customPlot->xAxis->setTickLabels(false);//不显示坐标轴文本
    //customPlot->xAxis->setTicks(false); //  不显示坐标轴
    ui->WID_customPlot->xAxis->setTicker(dateTimeTicker);//赋予默认的坐标轴矩形的x轴一个新的刻度计算类
    ui->WID_customPlot->xAxis->setTickLabelRotation(15);//x轴标签回转十五度
    ui->WID_customPlot->rescaleAxes();

}

MainWindow::~MainWindow()
{
   delete ui;
}

//清空接受窗口
void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

//发送数据
void MainWindow::on_sendButton_clicked()
{
    serial->write(ui->textEdit_2->toPlainText().toLatin1());
}

//读取接收到的数据
void MainWindow::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();
    QVector<QByteArray> datalist = buf.split(',').toVector();

    if( datalist.size() != 0  )
    {
        if(!buf.isEmpty())
        {

            QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            ui->textEdit->append(time);
            ui->textEdit->append(buf);


            QString tr(buf);
            tcpsocket->write(tr.toUtf8().data());


            QVector<double> posX,posY1,posY2,posY3,posY4;

            posY1.append(double(datalist[0].toDouble()));
            posY2.append(double(datalist[1].toDouble()));
            posY3.append(double(datalist[2].toDouble()));
            posY4.append(double(datalist[3].toDouble()));
            posX.append(double(QDateTime::fromString(time,"yyyy-MM-dd hh:mm:ss").toTime_t()+ 8*3600));


            qDebug()<<"posX:"<<posX;
            qDebug()<<"posY1:"<<posY1;
            qDebug()<<"posY2:"<<posY2;
            qDebug()<<"posY3:"<<posY3;
            qDebug()<<"posY4:"<<posY4;

            /****************曲线绘制****************/
////            ui->WID_customPlot->graph(0)->addData(posX,posY1);
////            ui->WID_customPlot->graph(0)->addData(x, y0);
////            ui->WID_customPlot->graph(0)->addData(x, y1);
////            //ui->WID_customPlot->graph(0)->rescaleAxes();
////            ui->WID_customPlot->graph(1)->addData(posX,posY2);
//            //ui->WID_customPlot->graph(1)->rescaleAxes();
//            ui->WID_customPlot->graph(2)->addData(posX,posY3);
//            //ui->WID_customPlot->graph(2)->rescaleAxes();
//            ui->WID_customPlot->graph(3)->addData(posX,posY4);
//            //ui->WID_customPlot->graph(3)->rescaleAxes();        后一条曲线的自适应会覆盖掉前一条曲线,因此选择整个界面自适应
//            ui->WID_customPlot->rescaleAxes();
//            ui->WID_customPlot->replot();
        }
    }
    buf.clear();

}

void MainWindow::on_openButton_clicked()
{
    if(ui->PortBox->currentText().isEmpty() == false)
    {    if(ui->openButton->text() == tr("打开串口"))
        {
            serial = new QSerialPort(this);
            //设置串口名
            serial->setPortName(ui->PortBox->currentText());
            //打开串口
            serial->open(QIODevice::ReadWrite);
            //设置波特率
            serial->setBaudRate(ui->BaudBox->currentText().toInt());
            //设置数据位数
            switch(ui->BitNumBox->currentIndex())
            {
                case 8: serial->setDataBits(QSerialPort::Data8); break;
                default: break;
            }
            //设置奇偶校验
            switch(ui->ParityBox->currentIndex())
            {
                case 0: serial->setParity(QSerialPort::NoParity); break;
                default: break;
            }
            //设置停止位
            switch(ui->StopBox->currentIndex())
            {
                case 1: serial->setStopBits(QSerialPort::OneStop); break;
                case 2: serial->setStopBits(QSerialPort::TwoStop); break;
            default: break;
            }
            //设置流控制
            serial->setFlowControl(QSerialPort::NoFlowControl);

            //关闭设置菜单使能
            ui->PortBox->setEnabled(false);
            ui->BaudBox->setEnabled(false);
            ui->BitNumBox->setEnabled(false);
            ui->ParityBox->setEnabled(false);
            ui->StopBox->setEnabled(false);
            ui->openButton->setText(tr("关闭串口"));
            ui->sendButton->setEnabled(true);

            //连接信号槽
            QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
            //QObject::connect(serial, &QSerialPort::readyRead, this, &MainWindow::readMeassage);
        }
        else
        {
            //关闭串口
            serial->clear();
            serial->close();
            serial->deleteLater();

            //恢复设置使能
            ui->PortBox->setEnabled(true);
            ui->BaudBox->setEnabled(true);
            ui->BitNumBox->setEnabled(true);
            ui->ParityBox->setEnabled(true);
            ui->StopBox->setEnabled(true);
            ui->openButton->setText(tr("打开串口"));

            ui->sendButton->setEnabled(false);
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","没有可用的串口！");
    }
}

void MainWindow::on_pushButtonConnect_clicked()
{
    qDebug()<<"连接成功";
    QString timer = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
     qDebug()<<"time:"<<timer;
     while(1)
     {
    // 生成模拟数据点 (x-y0 第一条曲线, x-y1为第2条曲线):
    QVector<double> posX, y0, y1;
    posX.append(double(QDateTime::fromString(timer,"yyyy-MM-dd hh:mm:ss").toTime_t()+ 8*3600));
    qDebug()<<"posX:"<<posX;
    srand((int)time(0));  // 产生随机种子  把0换成NULL也行
       for (int i = 0; i < 10; i++)
       {
           y0[i] = random(100);
           y1[i] = random(100);
           qDebug()<<"y0[i]"<<y0[i];
           qDebug()<<"y1[i]"<<y1[i];
       }
    ui->WID_customPlot->graph(0)->addData(posX, y0);
    ui->WID_customPlot->graph(0)->addData(posX, y1);
    ui->WID_customPlot->graph(0)->rescaleAxes(true);    //自动调整XY轴的范围，以便显示出graph(1)中所有的点
    ui->WID_customPlot->graph(1)->rescaleAxes(true);    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    }
}



void MainWindow::on_openPlot_triggered()
{
    on_openButton_clicked();
}

void MainWindow::on_actionConnect_triggered()
{
    on_pushButtonConnect_clicked();
}

void MainWindow::on_save_document_as_text_triggered()
{
    //QMessageBox::information(this,"信息","开发中敬请期待...");
    if (ui->textEdit->document()->isEmpty()) {
        QMessageBox::warning(this, "警告", "数据记录为空，无法保存！", QMessageBox::Ok);
    } else {
        QString filename = QFileDialog::getSaveFileName(this,"保存数据记录", "数据记录", "文本(*.txt);;所有文件(*.*)");
        if(!filename.isEmpty())
        {
          saveFile(filename);
        }
    }
}

bool MainWindow::saveFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"保存文件",tr("无法保存文件   %1:\n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();

    return true;
}

void MainWindow::on_save_document_as_jpg_triggered()
{
    //QMessageBox::information(this,"信息","开发中敬请期待...");
    QString pdfName = QFileDialog::getSaveFileName(this, "数据统计图", "数据统计图", "文本(*.jpg);;所有文件(*.*)");
    if(!pdfName.isEmpty())
    {
       ui->WID_customPlot->saveJpg(pdfName,800,600);//直接调用save接口保存
    }
}

void MainWindow::on_openFile_triggered()
{
    //QMessageBox::information(this,"信息","开发中敬请期待...");
    tcpsocket2->abort();
    QString ip = ui->lineEditIP->text();
    tcpsocket2->connectToHost(QHostAddress(ip),6666);

    if( tcpsocket2->waitForConnected(300) == false )
    {
      QMessageBox::warning(this,"警告","没有传输对象！");
    }
    else
    {

        connect(tcpsocket2,&QTcpSocket::connected,
            [=]()
        {
            qDebug()<<"成功建立连接";
        }
        );


        QString filepath = QFileDialog::getOpenFileName(this,"open","../");
        if(false == filepath.isEmpty())
        {
            filename.clear();
            filesize = 0;
            //获取文件信息
            QFileInfo info(filepath);
            filename = info.fileName();
            filesize = info.size();

            sendsize = 0;

            qDebug()<<"我在获取信息";
            //只读打开文件
            file.setFileName(filepath);
            //打开文件
            bool isok = file.open(QIODevice::ReadOnly);
            if (false == isok)
            {
            QMessageBox::warning(this,"警告","只读方式打开文件失败");

            }

            // ui->openFile->setEnabled(false);
            // ui->sendFile->setEnabled(true);
        }
        else
        {
            QMessageBox::warning(this,"警告","文件选择出错");
        }
    }
}

void MainWindow::on_sendFile_triggered()
{
   // QMessageBox::information(this,"信息","开发中敬请期待...");
    //先发送文件头信息
    QString head = QString("%1##%2").arg(filename).arg(filesize);
    qDebug()<<"我在发送信息";
    qint64 len = tcpsocket2->write(head.toUtf8());
    if(len >0)//头部信息发送成功
    {
     //发送文件真正信息
     //防止TCP黏包
     //需要通过定时器延时·
      timer.start(20);
     }
     else
     {
            QMessageBox::warning(this,"警告","文件发送失败");
            file.close();
          //  ui->openFile->setEnabled(true);
          //  ui->sendFile->setEnabled(false);

     }
}

void MainWindow::senddata()
{
    qint64 len = 0;
    //QMessageBox::information(this,"信息","文件发送中...");
        do
        {
                //每次发送数据的大小4k
                char buf[4*1024] = {0};
                len = 0;
                //往文件中读数据
                len = file.read(buf,sizeof(buf));
                //发送数据 读多少 发多少
                tcpsocket2->write(buf,len);
                qDebug()<<"信息发送中";
                //发送的数据需要累计
                sendsize += len;
               // ui->progressBar->setRange(0,filesize);
                //ui->progressBar->setValue(sendsize);
         }while(len > 0);
}


void MainWindow::on_pushButton_clicked()
{
    on_openFile_triggered();
}

void MainWindow::on_pushButton_2_clicked()
{
    on_sendFile_triggered();
}
