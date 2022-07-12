#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include<QPainter>


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

    cam_raw_buf_replay_len =  width * hight * 4;
    cam_rgb_buf_replay_len =  width * hight * 4;

    cam_raw_buf = (unsigned char *) malloc (cam_raw_buf_len);
    if (cam_raw_buf  == (void *) -1 )
    {
        qDebug()  <<   "mem malloc cam_raw_buf failed ,program exit!!";
        exit(1);

    }


    cam_rgb_buf = (unsigned char *) malloc (cam_rgb_buf_len);

    if (cam_rgb_buf  == (void *) -1 )
    {
        qDebug()  <<   "mem malloc cam_rgb_buf failed ,program exit!!";
        exit(1);

    }

    cam_raw_buf_replay = (unsigned char *) malloc (cam_raw_buf_replay_len);
    if (cam_raw_buf_replay  == (void *) -1 )
    {
        qDebug()  <<   "mem malloc cam_raw_buf_replay failed ,program exit!!";
        exit(1);

    }


    cam_rgb_buf_replay = (unsigned char *) malloc (cam_rgb_buf_replay_len);

    if (cam_rgb_buf_replay  == (void *) -1 )
    {
        qDebug()  <<   "mem malloc cam_rgb_buf_replay failed ,program exit!!";
        exit(1);

    }
    //QImage(uchar *data, int width, int height, QImage::Format format, QImageCleanupFunction cleanupFunction = nullptr, void *cleanupInfo = nullptr)

    image  = new QImage(cam_rgb_buf,width,hight,QImage::Format_RGB888);
    image_replay  = new QImage(cam_rgb_buf_replay,width,hight,QImage::Format_RGB888);


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

        //save yuv to file

        if(record_flag==true)
            fwrite(cam_raw_buf, cam_raw_buf_len, 1, record_file);



        //image->loadFromData(cam_rgb_buf,cam_rgb_buf_len);   // Qt5 failed.
        *image = QImage(cam_rgb_buf,width,hight,QImage::Format_RGB888);

        cam_vd->unget_frame();
        this->update();
    });

    timer->start(30);

}



Widget::~Widget()
{
    delete ui;
}


void  Widget::paintEvent( QPaintEvent *)

{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
    painter.drawEllipse(680,20,20,20);
    painter.end();

    if(replay_flag==false)
    {
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap::fromImage(*image));
    }
    else
    {
        //replay
        //read video frame and show on label
        if(replay_flag==true)
        {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            if(!File_replay.atEnd())//file not end
            {
                out << File_replay.read(153600);
                char *temp_char;
                temp_char=block.data();

                cam_raw_buf_replay=(uchar *)temp_char;

                //convert_yuv_to_rgb_buffer(p,pp,320,240/*QWidget::width(),QWidget::height()*/);
                yuyv422_to_rgb888(cam_raw_buf_replay,cam_rgb_buf_replay,width,hight);
                *image_replay = QImage(cam_rgb_buf_replay,width,hight,QImage::Format_RGB888);
                ui->label->setScaledContents(true);
                ui->label->setPixmap(QPixmap::fromImage(*image_replay));
                //frame->loadFromData((uchar *)pp,/*len*/320 * 240 * 3 * sizeof(char));
                //label->setPixmap(QPixmap::fromImage(*frame,Qt::AutoColor));
            }
            else //file end
            {
                replay_flag=false;
                fclose(record_file);
                File_replay.close();
                qDebug()<<"File replay end!";
            }

        }



        //end replay

    }
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

void Widget::on_pushButton_clicked()//Record
{
    if(record_flag==false)
    {
        record_flag=true;
        record_file=fopen("record.yuv","wa+");
    }
}

void Widget::on_pushButton_2_clicked()//Stop
{
    if(record_flag==true)
    {

        record_flag=false;
        fclose(record_file);
    }
}

void Widget::on_pushButton_3_clicked()//Replay
{
    replay_flag=true;
    record_file=fopen("record.yuv","r");
    File_replay.open(record_file,QIODevice::ReadOnly);
    qDebug()<<"Open file OK!";
    qDebug("File length=%d\n",File_replay.size());
}
