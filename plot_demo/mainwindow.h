#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "customplot/multicurvesplot.h"
#include "checkboxuilist/checkboxuilist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
      void timerEvent(QTimerEvent *event);

private slots:
      void on_checkBox_tracer_clicked(bool checked);
      void on_checkBox_scroll_clicked(bool checked);
      void on_setCheckBoxText_clicked(int idx);
      void on_setTipText_clicked(int idx,QString _Text);  
private:
    Ui::MainWindow *ui;
    MultiCurvesPlot *plot;
    CheckBoxUiList *botton;
    QList<uint16_t> list;
    QList<uint16_t> lastlist;
    double t;


};

#endif // MAINWINDOW_H
