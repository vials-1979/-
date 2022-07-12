#include "widget.h"
#include "ui_widget.h"
#include <vector>
using namespace std;


int list1[8]={12,14,16,18,19,20,22,30};


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{


    ui->setupUi(this);
    QImage *img=new QImage();
    img->load("1.jpeg");
    ui->label->setPixmap(QPixmap::fromImage(*img));
    ui->comboBox->addItems({"clock 0","clock 3","clock 6","clock 9","clock 12","clock 15","clock 18","clock 21"});
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_2_clicked()//draw_temp
{
    draw_temp();
}


void Widget::draw_temp(){
    QPixmap  temp(460,200);//
    temp.fill(Qt::white);

    QPainter  painer(&temp);
    QPen pen;
    pen.setColor(Qt::black);

    //   pen.setWidth(2);
    painer.setPen(pen);

    painer.drawLine(20,140,400,140);//x
    painer.drawLine(20,0,20,140);//y


    //temp %c  y
    for(int i=0;i<8;i++){
        painer.drawText(5,140-i*18,QString::number(i*5));

    }

    //x

    for(int i=0;i<8;i++){
        painer.drawText(20+i*48,150,QString::number(i*3));

    }




    // point

    for(int i=0;i<8;i++){
        painer.setPen(QPen(Qt::black,5,Qt::SolidLine,Qt::RoundCap));

        painer.drawPoint(20+i*48,140-list1[i]*4);
        painer.setPen(QPen(Qt::black,1,Qt::SolidLine,Qt::RoundCap));
        if(i+1!=8)
            painer.drawLine(20+i*48,140-list1[i]*4,20+(i+1)*48,140-list1[i+1]*4);
    }



    ui->label->setPixmap(temp);

}

void Widget::on_pushButton_clicked()
{

    list1[ui->comboBox->currentIndex()]=ui->lineEdit->text().toInt();


}
