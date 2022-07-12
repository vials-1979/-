#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "videodevice.h"
#include <QPaintEvent>
#include <QImage>
#include <QFile>

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
    QImage  *image_replay;
    unsigned  char   *cam_raw_buf;
    unsigned  int    cam_raw_buf_len;


    unsigned  char   *cam_rgb_buf;
    unsigned  int     cam_rgb_buf_len;

    unsigned  char   *cam_raw_buf_replay;
    unsigned  int    cam_raw_buf_replay_len;

    unsigned  char   *cam_rgb_buf_replay;
    unsigned  int     cam_rgb_buf_replay_len;

    void yuyv422_to_rgb888(unsigned char *yuyvdata, unsigned char *rgbdata, int w, int h);
    bool  get_frame_flag;

    //record and replay

    bool record_flag,replay_flag;
    FILE *record_file;
    QFile File_replay;

private slots:
    void slot_display_error(QString);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
