#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QString>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

     timer =  new QTimer(this);

     QString  msg;

     width = 320;
     hight = 240;
     cam_raw_buf_len =  width * hight * 4;
     cam_rgb_buf_len =  width * hight * 4;

     cam_raw_buf = (unsigned char *) malloc (cam_raw_buf_len);
     if (cam_raw_buf  == (void *) -1 )
     {
         qDebug()  <<   "mem malloc failed ,program exit!!";
         exit(1);

     }


     cam_rgb_buf = (unsigned char *) malloc (cam_rgb_buf_len);

     if (cam_rgb_buf  == (void *) -1 )
     {
         qDebug()  <<   "mem malloc failed ,program exit!!";
         exit(1);

     }

     //QImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr)

     image  = new QImage(cam_rgb_buf,width,hight,QImage::Format_RGB888);



    cam_name = "/dev/video0";
    cam_vd  =  new  VideoDevice(cam_name);


    connect(cam_vd,&VideoDevice::display_error,this,[=](QString msg){
        QMessageBox::critical(this,"Device Error",QString("Device %1  failed!").arg(msg));
        qDebug() << msg;
        exit(1);
    });
    cam_vd->open_device();
    cam_vd->init_device();
    cam_vd->start_capturing();

    //get_frame_flag  = false;
    connect(timer,&QTimer::timeout,this,[=]{
        cam_vd->get_frame((void **) &cam_raw_buf, (size_t *) &cam_raw_buf_len);
        yuyv422_to_rgb888(cam_raw_buf,cam_rgb_buf,width,hight);

        //image->loadFromData(cam_rgb_buf,cam_rgb_buf_len);   // Qt5 failed.
        *image = QImage(cam_rgb_buf,width,hight,QImage::Format_RGB888);


//        if (image->save("1.png"))
//            qDebug() <<  "save success";
//        else
//            qDebug() << "save failed!!";


        cam_vd->unget_frame();
        this->update();
    });

    timer->start(1/30);

}



Widget::~Widget()
{
    delete ui;
}


void  Widget::paintEvent( QPaintEvent *)

{
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap::fromImage(*image));
}


void Widget::yuyv422_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int w, int h)
{
    //码流Y0 U0 Y1 V1 Y2 U2 Y3 V3 --》YUYV像素[Y0 U0 V1] [Y1 U0 V1] [Y2 U2 V3] [Y3 U2 V3]--》RGB像素
    int r1, g1, b1;
    int r2, g2, b2;
    int i;

    for(i=0; i<w*h/2; i++)
    {
        char data[4];
        memcpy(data, yuyvdata+i*4, 4);
        unsigned char Y0=data[0];
        unsigned char U0=data[1];
        unsigned char Y1=data[2];
        unsigned char V1=data[3];

        r1 = Y0+1.4075*(V1-128);
        if(r1>255) r1=255;
        if(r1<0)   r1=0;

        g1 =Y0- 0.3455 * (U0-128) - 0.7169*(V1-128);
        if(g1>255)  g1=255;
        if(g1<0)    g1=0;

        b1 = Y0 + 1.779 * (U0-128);
        if(b1>255)  b1=255;
        if(b1<0)    b1=0;

        r2 = Y1+1.4075*(V1-128);
        if(r2>255)  r2=255;
        if(r2<0)    r2=0;

        g2 = Y1- 0.3455 * (U0-128) - 0.7169*(V1-128);
        if(g2>255)    g2=255;
        if(g2<0)      g2=0;

        b2 = Y1 + 1.779 * (U0-128);
        if(b2>255)    b2=255;
        if(b2<0)      b2=0;

        rgbdata[i*6+0]=r1;
        rgbdata[i*6+1]=g1;
        rgbdata[i*6+2]=b1;
        rgbdata[i*6+3]=r2;
        rgbdata[i*6+4]=g2;
        rgbdata[i*6+5]=b2;
    }
}







void Widget::slot_display_error(QString msg){

    qDebug() << "slot msg"  << msg;

}

void Widget::on_Record_clicked()
{

}

void Widget::on_Pause_clicked()
{

}

void Widget::on_Review_clicked()
{

}
