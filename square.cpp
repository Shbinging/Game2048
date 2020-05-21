#include "square.h"
#include "ui_square.h"
#include "math.h"
#include "qdebug.h"
#include"qtimer.h"
square::square(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::square)
{
    ui->setupUi(this);
    setnum(0);
}
void SSleep(int t){
    QEventLoop eventloop;
    QTimer::singleShot(t, &eventloop, SLOT(quit()));
    eventloop.exec();
}

void square::setnum(int n,bool isSlow, bool isegg){
    QFont ft;
    ft.setPointSize(20);
    ui->label->setFont(ft);
    if (n == 0)
    {
        ui->label->setText("");
        QPalette col;
        col.setColor(QPalette::Background, QColor(174,166,170, 100));
        ui->label->setPalette(col);
        ui->label->setAutoFillBackground(true);
        col.setColor(QPalette::WindowText, Qt::white);
        ui->label->setPalette(col);
    }
    else
    {
        ui->label->show();
        ui->label->setText(QString::number(n));
//egg
        if (isegg && n == 7) ui->label->setText("0");
//
        ui->label->setAutoFillBackground(true);
        QPalette col;
        col.setColor(QPalette::WindowText, Qt::white);
        ui->label->setPalette(col);
        QColor tmp = getBackcolor(n);
//egg
        if (isegg) tmp.setRgb(255,0,0);
//
        int a;
        if (isSlow) a = 0;
        else a = 255;
        while (a <= 255){
            tmp.setAlpha(a);
            col.setColor(QPalette::Background, tmp);
            ui->label->setPalette(col);
            ui->label->setAutoFillBackground(true);
            a +=10;
            if (a >=255) break;
            SSleep(10);
        }

        ui->label->setWordWrap(true);
        //QFont c;
        //c.setPixelSize(140);
       // ui->label->setFont(c);
    }
}

QColor square::getBackcolor(int n){
    int m = log(n)/log(2);
    double delta1 = 196.0/15;
    double delta2 = -121.0/15;
    double delta3 = -121.0/15;
    int r = 60 + delta1 * m;
    int g = 122 + delta2 * m;
    int b = 122 + delta3 * m;
    qDebug() <<r <<" "<< g <<" " <<b<<endl;
    return QColor(r, g, b, 250);
}

square::~square()
{
    delete ui;
}
