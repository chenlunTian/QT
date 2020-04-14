#include "usart.h"
#include "ui_usart.h"
#include "flatui.h"

Usart::Usart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Usart)
{
    ui->setupUi(this);
    FlatUI::Instance()->setPushButtonQss(ui->ClearPortInfoBtn,4,1,100);
    FlatUI::Instance()->setPushButtonQss(ui->OpenPortBtn);
    FlatUI::Instance()->setPushButtonQss(ui->ClosePortBtn);
}

Usart::~Usart()
{
    delete ui;
}
