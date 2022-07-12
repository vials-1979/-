#include "widget.h"
#include "ui_widget.h"
#include"qpainter.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){

    QPainter painter(this); // 声明一个画家对象，this指绘图设备
    QBrush brush(Qt::blue,Qt::SolidPattern);

    painter.setBrush(brush);

//    brush.setStyle(Qt::SolidPattern);

//    brush.setColor(Qt::blue);

    painter.drawEllipse(240,136,40,40);

    painter.end();

}
