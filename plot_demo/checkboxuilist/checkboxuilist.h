#ifndef CHECKBOXUILIST_H
#define CHECKBOXUILIST_H

#include <QWidget>
#include <QTimerEvent>
#include <QCheckBox>
#include <QTimer>
#include <QListWidgetItem>
#include <QMap>
#include <QMouseEvent>
#include "stdint.h"
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFormLayout>

namespace Ui {
class CheckBoxUiList;
}


class Widgets: public QWidget
{
    Q_OBJECT
public:
    explicit Widgets(QWidget *parent = 0);    
    QCheckBox *checkBox;
    QLineEdit *lineEdit;

private:
    QFormLayout *formLayout;
};

class CheckBoxUiList : public QWidget
{
    Q_OBJECT

public:
    explicit CheckBoxUiList(QWidget *parent = 0);
    ~CheckBoxUiList();
    /*放置cnt个checkBox*/
    void init(int cnt);

public slots:
    void setCheckBoxText(int idx, const QString text);
    void setTipText(int idx, const QString text);
    QList<uint16_t> All_selectedItems();

signals:
    void stateChanged(QList<uint16_t> selectedItems);//任何一个checkBox状态改变


protected:

private slots:
    void anyStateChanged();//任何一个checkBox状态改变
    void timer_timeout();
    void on_regExpInput_textChanged(const QString &arg1);
    void on_btnSelectAll_clicked();
    void on_btnSelectNone_clicked();
    void on_showTipFlag_toggled(bool checked);//显示数值



private:

    void allCheckboxsConnect(bool enable);
    Ui::CheckBoxUiList *ui;
    QTimer timer;
    QList<uint16_t> selectedItems;//保存哪些checkBox被勾选了
    QCheckBox *checkBox(int idx);
    QLineEdit *tipText(int idx);
    QMap<QListWidgetItem*, QCheckBox*> map;//item映射到CheckBox
//    bool leftBtnPressed;
//    int oldWidth;
};

#endif // CHECKBOXUILIST_H
