#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTcpSocket>
#include <QPrinter>
#include <QTimer>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool saveFile(const QString& filename);
    void senddata();

private slots:
    void on_clearButton_clicked();

    void on_sendButton_clicked();

    void on_openButton_clicked();

    void Read_Data();

    void on_pushButtonConnect_clicked();

    void on_openPlot_triggered();

    void on_actionConnect_triggered();

    void on_save_document_as_text_triggered();

    void on_save_document_as_jpg_triggered();

    void on_openFile_triggered();

    void on_sendFile_triggered();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QTcpSocket *tcpsocket;//用于发送/接收信息
    QTcpSocket *tcpsocket2;//用于发送/接收文件
    QFile file;//文件对象
    QString filename;//文件名字
    qint64 filesize;//文件大小
    qint64 sendsize;
    QTimer timer;

    //int flag = 0;
};

#endif // MAINWINDOW_H
