#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "videodevice.h"
#include <QPaintEvent>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString  cam_name;
    VideoDevice *  cam_vd;
     QTimer * timer  ;

     void  paintEvent( QPaintEvent *);

     int width, hight;

     QImage  *image;

     unsigned  char   *cam_raw_buf;
     unsigned  int    cam_raw_buf_len;


     unsigned  char   *cam_rgb_buf;
     unsigned  int     cam_rgb_buf_len;
     void yuyv422_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int w, int h);
     bool  get_frame_flag;



private slots:
     void slot_display_error(QString);

     void on_Record_clicked();

     void on_Pause_clicked();

     void on_Review_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
