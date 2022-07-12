#include "mainwindow.h"
#include "ui_mainwindow.h"


double op1;
char op=' ';
double op2;
int flag=0;
QList<QString> qlist_str;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_b1_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}

    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="1";
    else
        str=str+"1";
    ui->lineEdit->setText(str);

}


void MainWindow::on_b2_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="2";
    else
        str=str+"2";
    ui->lineEdit->setText(str);

}


void MainWindow::on_b3_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="3";
    else
        str=str+"3";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b4_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="4";
    else

        str=str+"4";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b5_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="5";
    else

        str=str+"5";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b6_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="6";
    else
        str=str+"6";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b7_clicked()
{

    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="7";
    else
        str=str+"7";
    ui->lineEdit->setText(str);

}


void MainWindow::on_b8_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();

    if(str.length()==1&&str=="0") str="8";
    else

        str=str+"8";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b9_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}



    QString str=ui->lineEdit->text();
    if(str.length()==1&&str=="0") str="9";
    else
        str=str+"9";
    ui->lineEdit->setText(str);

}

void MainWindow::on_b0_clicked()
{
    if(op!=' '&&flag==0){  ui->lineEdit->clear();flag=1;}
    QString str=ui->lineEdit->text();

    if(str=="0"||str=="")
        ui->lineEdit->setText("0");
    else
        str+="0";

    ui->lineEdit->setText(str);


    //    int a= str.lastIndexOf("+");
    //    int b= str.lastIndexOf("-");
    //    a>b?a:b;
    //    b=str.lastIndexOf("*");
    //    a>b?a:b;
    //    b=str.lastIndexOf("÷");
    //    a>b?a:b;
    //    if(str.length()==1&&QString::compare(str,"0")==0){
    //        str="0";

    //    }



    //   else if(str[a+1]=="0")
    //   {
    //       str="0";
    //   }




    //    else{
    //        str=str+"0";
    //        ui->lineEdit->setText(str);
    //    }

}


void MainWindow::on_clear_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit->setText("0");
    flag=0;
    op=' ';

}

//don't measure

void MainWindow::on_divi_clicked()
{
    QString str=ui->lineEdit->text();
    op1=str.toDouble();
    op='÷';
    ui->lineEdit->setText(str);
}


void MainWindow::on_add_clicked()
{
    QString str=ui->lineEdit->text();
    op1=str.toDouble();
    op='+';
    ui->lineEdit->setText(str);
}

void MainWindow::on_mul_clicked()
{
    QString str=ui->lineEdit->text();
    op1=str.toDouble();
    op='*';
    ui->lineEdit->setText(str);
}

void MainWindow::on_sub_clicked()
{
    QString str=ui->lineEdit->text();
    op1=str.toDouble();
    op='-';
    ui->lineEdit->setText(str);
}


void MainWindow::on_equ_clicked()
{
    QString str=ui->lineEdit->text();

//    qlist_str=str.split("+");

//    int sum=0;
//    for(int i=0;i<qlist_str.size();i++){
//        sum+=qlist_str[i].toDouble();
//    }

//    str = QString::number(sum, 'f', 2);



    op2=str.toDouble();

    switch(op){
    case  '+': str = QString::number((op1+op2), 'f', 2);break;
    case  '-': str = QString::number((op1-op2), 'f', 2);break;
    case '*': str = QString::number((op1*op2), 'f', 2);break;
    case '÷': str = QString::number((op1/op2), 'f', 2);break;
    }


    flag=0;
    op=' ';

    ui->lineEdit->setText(str);
}


void MainWindow::on_dot_clicked()
{
    QString str=ui->lineEdit->text();
    if(str.indexOf(".")==-1)
    {
        str+=".";
        ui->lineEdit->setText(str);
    }


}

void MainWindow::on_back_clicked()
{
     QString str=ui->lineEdit->text();

    str.chop(1);
     ui->lineEdit->setText(str);

}
