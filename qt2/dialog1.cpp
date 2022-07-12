#include "dialog1.h"
#include "ui_dialog1.h"

extern QString globaldata;


Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
    line=new QLineEdit();

    layout=new QHBoxLayout();

    layout->addWidget(line);

    connect(line,SIGNAL(textChanged(QString)),this,SLOT(setText1(QString)));



    setLayout(layout);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::show_text(){

    line->setText(globaldata);
}

void Dialog1::setText1(QString str){
    emit sendmessage(str);
    \

}
