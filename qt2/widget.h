#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<dialog1.h>
//add want to do .h



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



private slots:
    void on_Butt1_clicked();
    void on_Butt2_clicked();
    void on_Butt3_clicked();
    void on_Butt4_clicked();
    void setText(QString);
    void syn();


private:
    Ui::Widget *ui;
    QPushButton *Butt1;
    QPushButton *Butt2;
    QPushButton *Butt3;
    QPushButton *Butt4;

    QLineEdit *line;
    QHBoxLayout *layout;
    QHBoxLayout *layout1;
    QVBoxLayout *layout0;

    Dialog1  *dlg;



    // add obejct of kind instrctor
};
#endif // WIDGET_H
