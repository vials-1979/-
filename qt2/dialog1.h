#ifndef DIALOG1_H
#define DIALOG1_H

#include <QDialog>
#include<QLineEdit>
#include<QHBoxLayout>

namespace Ui {
class Dialog1;
}

class Dialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog1(QWidget *parent = nullptr);
    ~Dialog1();
    void show_text();

    //dialog->widget syn

signals:
    void sendmessage(QString);

private slots:
    void setText1(QString);

private:
    Ui::Dialog1 *ui;
    QHBoxLayout *layout;
    QLineEdit *line;

};

#endif // DIALOG1_H
