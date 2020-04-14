#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar=menuBar();
    setMenuBar(mBar);
    QMenu *menu = mBar->addMenu("对话框");
    QAction *p1 = menu->addAction("模态对话框");
    connect(p1,&QAction::triggered,
            [=]()
            {
                QDialog dlg;
                dlg.exec();
                qDebug()<<"1111111";
            }
            );

    QAction *p2 = menu->addAction("非模态对话框");
    connect(p2,&QAction::triggered,
            [=]()
            {

//                dlg.show();   //最简单，不会导致内存泄漏
//                qDebug()<<"222222";


//            QDialog *p=new QDialog(this);//指定父对象点的越多出现的越多，内存越用越小，不推荐
//            p->show();

            QDialog *p=new QDialog;//推荐使用，关闭时释放内存空间
            p->setAttribute(Qt::WA_DeleteOnClose); //设置属性，关闭时候才释放内存空间
            p->show();
            }
            );

    QAction *p3 = menu->addAction("关于对话框");
    connect(p3,&QAction::triggered,
            [=]()
            {
                QMessageBox::about(this,"about","关于QT");
            }
            );

    QAction *p4 = menu->addAction("问题对话框");
    connect(p4,&QAction::triggered,
            [=]()
            {
               int ret = QMessageBox::question(this,
                               "question","Are you ok?"
                               ,QMessageBox::Yes|QMessageBox::No);
               switch (ret)
               {
               case QMessageBox::Yes :
                   qDebug()<<"i am ok";
                   break;
               case QMessageBox::No  :
                   qDebug()<<"i am bad";
                   break;
               default:
                   break;

               }
            }
            );
    QAction *p5 = menu->addAction("文件对话框");
    connect(p5,&QAction::triggered,
            [=]()
            {
                QString path = QFileDialog::getOpenFileName(
                            this,
                            "open",
                            "../",
                  "souce(*.cpp *.h);;"
                  "Text(*.txt);;"
                  "All(*.*)"
                            );
                qDebug()<<path;
            }
            );

}

MainWindow::~MainWindow()
{
}

