#include "checkboxuilist.h"
#include "ui_checkboxuilist.h"
#include <QTimer>
#include <QRegExp>
#include <qDebug>

Widgets::Widgets(QWidget *parent):QWidget(parent)
{
    //this->resize(232, 27);
    formLayout = new QFormLayout(this);
    formLayout->setObjectName(QStringLiteral("formLayout"));
    formLayout->setHorizontalSpacing(0);
    formLayout->setVerticalSpacing(2);
    formLayout->setContentsMargins(2, 0, 0, 0);
    checkBox = new QCheckBox(this);
    checkBox->setObjectName(QStringLiteral("checkBox"));

    formLayout->setWidget(0, QFormLayout::LabelRole, checkBox);

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));
    lineEdit->setReadOnly(true);

    formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

    checkBox->setMinimumWidth(100);
    checkBox->setMaximumWidth(100);
    lineEdit->setMinimumWidth(50);

}



/*-------------------------*/
CheckBoxUiList::CheckBoxUiList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckBoxUiList)
//    ,leftBtnPressed(false)
{
    ui->setupUi(this);
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
//    setMouseTracking(true);//未按下鼠标时，也会触发mouseMove事件

    init(10);
}
void CheckBoxUiList::init(int cnt)
{
    ui->listWidget->clear();
    for(int i = 0; i < cnt; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        Widgets *itemWdt = new Widgets();

        map.insert(item, itemWdt->checkBox);
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, itemWdt);
        itemWdt->checkBox->setText(QString("checkBox_%1").arg(i));
        itemWdt->lineEdit->setText("NULL");
        connect(itemWdt->checkBox, SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
    }
    allCheckboxsConnect(true);
}

CheckBoxUiList::~CheckBoxUiList()
{
    delete ui;
}
void CheckBoxUiList::allCheckboxsConnect(bool enable)
{
    if(enable)
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
            connect(map[ui->listWidget->item(i)], SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
    }
    else
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
            disconnect(map[ui->listWidget->item(i)], SIGNAL(stateChanged(int)), this, SLOT(anyStateChanged()));
    }
}
/*
任何一个checkBox的状态改变
*/
void CheckBoxUiList::anyStateChanged()
{
    //qDebug() << "one checkBox State Changed";
    selectedItems.clear();
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(checkBox(i)->isChecked())
            selectedItems.append(i);
    }
    timer.start(200);//避免全选/全不选时，造成的频繁emit stateChanged(selectedItems);
}

/*
全选/全不选按钮，肯定会在ms级执行完毕，timer.start(100)可以避免频繁emit
*/
void CheckBoxUiList::timer_timeout()
{
//    qDebug() << "one checkBox State Changed";
    emit stateChanged(selectedItems);
}

/*
获取第idx个checkBox指针
*/
QCheckBox* CheckBoxUiList::checkBox(int idx)
{
    if(idx >= ui->listWidget->count())
        return NULL;

    QListWidgetItem *item = ui->listWidget->item(idx);//先获取QListWidgetItem
    Widgets *itemWdt = static_cast<Widgets*>(ui->listWidget->itemWidget(item));
    return itemWdt->checkBox;
}
QLineEdit* CheckBoxUiList::tipText(int idx)
{
    if(idx >= ui->listWidget->count())
        return NULL;

    QListWidgetItem *item = ui->listWidget->item(idx);//先获取QListWidgetItem
    Widgets *itemWdt = static_cast<Widgets*>(ui->listWidget->itemWidget(item));
    return itemWdt->lineEdit;
}

void CheckBoxUiList::setCheckBoxText(int idx, const QString text)
{
    QCheckBox* cBox = checkBox(idx);
    if(cBox != NULL)
        cBox->setText(text);
    else
        qDebug() << "warning: CheckBoxUiList::setCheckBoxText->checkBox not exist";
}

void CheckBoxUiList::setTipText(int idx, const QString text)
{
//    qDebug() << "CheckBoxUiList::setTipText:new data";
    QLineEdit* lineEdit = tipText(idx);
    if(lineEdit != NULL)
        lineEdit->setText(text);
    else
        qDebug() << "warning: CheckBoxUiList::setTipText->lineEdit not exist";
}


void CheckBoxUiList::on_regExpInput_textChanged(const QString &text)
{
    QRegExp re(text);

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        bool passCondition;
        if(ui->regExpEnable->isChecked())//使用正则
        {
            if(re.indexIn(checkBox(i)->text()) < 0)//匹配失败
                passCondition = false;
            else
                passCondition = true;
        }
        else//不使用正则
        {
            passCondition = checkBox(i)->text().contains(text, Qt::CaseInsensitive);//不区分大小写
        }

        if(passCondition)
            ui->listWidget->item(i)->setHidden(false);
        else
            ui->listWidget->item(i)->setHidden(true);
    }
}

void CheckBoxUiList::on_btnSelectAll_clicked()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(!ui->listWidget->item(i)->isHidden())
            checkBox(i)->setChecked(true);
    }
}

void CheckBoxUiList::on_btnSelectNone_clicked()
{
    allCheckboxsConnect(false);
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
       checkBox(i)->setChecked(false);
    }
    selectedItems.clear();
    emit stateChanged(selectedItems);
    allCheckboxsConnect(true);
}

void CheckBoxUiList::on_showTipFlag_toggled(bool checked)
{
    if(checked)
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            tipText(i)->show();
        }        
    }
    else
    {
        for(int i = 0; i < ui->listWidget->count(); i++)
        {
            tipText(i)->hide();
        }        
    }
}

QList<uint16_t> CheckBoxUiList::All_selectedItems()
{
    return selectedItems;
}
