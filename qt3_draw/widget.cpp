#include "widget.h"
#include "ui_widget.h"
#include"qpainter.h"
#include"led.h"
#include <qdatetime.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    colorflag=0;
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(time_update()));
    timer->start(5000);

    sys_timer=new QTimer();
    connect(sys_timer,SIGNAL(timeout()),this,SLOT(sys_time_update()));
    sys_timer->start(1000);



    led_open("/dev/leds");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){



    if(colorflag==0)  {
        QPainter painter(this); // 声明一个画家对象，this指绘图设备
        QBrush brush(Qt::blue,Qt::SolidPattern);

        painter.setBrush(brush);

        painter.drawEllipse(240,100,40,40);

        painter.end();


    }
    if(colorflag==1)   {
        QPainter painter(this); // 声明一个画家对象，this指绘图设备
        QBrush brush(Qt::red,Qt::SolidPattern);

        painter.setBrush(brush);

        painter.drawEllipse(240,100,40,40);

        painter.end();

    }
    if(colorflag==2)    {
        QPainter painter(this); // 声明一个画家对象，this指绘图设备
        QBrush brush(Qt::green,Qt::SolidPattern);

        painter.setBrush(brush);

        painter.drawEllipse(240,100,40,40);

        painter.end();
    }




}

void Widget::on_pushButton_clicked()//red
{

    colorflag=1;
    update();

}

void Widget::on_pushButton_2_clicked()//green
{
    colorflag=2;
    update();

}

void Widget::on_pushButton_3_clicked()//blue
{
    colorflag=0;
    update();

}

void Widget::time_update()
{
    colorflag++;
    update();
    if(colorflag==3) colorflag=0;
}

void Widget::on_led1_off_clicked()
{

    led_ioctl(0,1);
}

void Widget::on_led1_on_clicked()
{
    led_ioctl(1,1);
}


void Widget::on_led0_off_clicked()
{
    led_ioctl(0,0);
}


void Widget::on_led0_on_clicked()
{
    led_ioctl(1,0);
}


void Widget::sys_time_update(){
    QDateTime currenttime=QDateTime::currentDateTime();
    QString str=currenttime.toString();

    ui->label->setText(str);


}
