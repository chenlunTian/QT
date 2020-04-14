#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "usart.h"
#include "multicurvesplot.h"
#include "checkboxuilist.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void changePage();

private:
    Ui::Widget *ui;
    Usart *usart;
    MultiCurvesPlot *plot;
    CheckBoxUiList *BtnGroup;
};
#endif // WIDGET_H
