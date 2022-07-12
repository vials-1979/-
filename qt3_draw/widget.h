#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtPrintSupport/QPrinter>
#include<QBrush>
#include<QPen>
#include<QPaintEvent>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void time_update();

    void sys_time_update();

    void on_led1_off_clicked();

    void on_led1_on_clicked();

    void on_led0_on_clicked();

    void on_led0_off_clicked();

private:
    Ui::Widget *ui;
    int colorflag;
    QTimer * timer;
    QTimer * sys_timer;
};
#endif // WIDGET_H
