#include "widget.h"
#include "ui_widget.h"


QString globaldata;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Butt1=new QPushButton();
    Butt2=new QPushButton();
    Butt3=new QPushButton();
    Butt4=new QPushButton();
    line=new QLineEdit();
    layout=new QHBoxLayout();//shui ping zujian,

    layout1=new QHBoxLayout();
    layout0=new QVBoxLayout();

    // Init the object;

    Butt1->setText("A");
    Butt2->setText("B");
    Butt3->setText("C");
    Butt4->setText("D");


    layout->addWidget(line);
    layout->addWidget(Butt1);




    layout1->addWidget(Butt2);
    layout1->addWidget(Butt3);
    layout1->addWidget(Butt4);


    layout0->addLayout(layout);
    layout0->addLayout(layout1);
    //setLayout(layout0);
    setLayout(layout0);

    connect(line,SIGNAL(textChanged(QString)),this,SLOT(syn()));


    connect(Butt1,SIGNAL(clicked()),this,SLOT(on_Butt1_clicked()));
    connect(Butt2,SIGNAL(clicked()),this,SLOT(on_Butt2_clicked()));
    connect(Butt3,SIGNAL(clicked()),this,SLOT(on_Butt3_clicked()));
    connect(Butt4,SIGNAL(clicked()),this,SLOT(on_Butt4_clicked()));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Butt1_clicked()
{

    line->setText("AAA");
    globaldata="AAA";
    dlg->show_text();


}

void Widget::on_Butt2_clicked()
{

    line->setText("BBB");

    globaldata="BBB";
    dlg->show_text();


}

void Widget::syn(){
    globaldata=line->text();
    dlg->show_text();




}

void Widget::on_Butt3_clicked()
{

    line->setText("CCC");
    globaldata="CCC";

    dlg->show_text();




}


void Widget::setText(QString str){
    line->setText(str);
}



void Widget::on_Butt4_clicked()
{
    globaldata="DDD";

    dlg=new Dialog1();
    line->setText("DDD");
    connect(dlg,SIGNAL(sendmessage(QString)),this->line,SLOT(setText(QString)));
    dlg->show_text();
    dlg->show();
}

