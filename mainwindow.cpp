#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlabel.h"
#include "qpainter.h"
#include "game.h"
#include "qdebug.h"
#include "qtimer.h"
#include "QMessageBox"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->hide();
    setFixedSize(733, 783);
    QIcon win(":/win.png");
    QIcon reset(":/reset.png");
    ui->start->setIcon(win);
    ui->reset->setIcon(reset);
    help_con();
}
void Sleep(int t){
    QEventLoop eventloop;
    QTimer::singleShot(t, &eventloop, SLOT(quit()));
    eventloop.exec();
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/back.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

}

void MainWindow::help_con(){
    QString st = "按笑脸开始，按×可随时结束，上下左右移动分别为wsad";
    QMessageBox::information(NULL, "操作帮助", st, QMessageBox::NoButton);
}

void MainWindow::help_rule(){
    QString st = "传统2048规则";
    QMessageBox::information(NULL, "游戏规则", st, QMessageBox::NoButton);
}

void MainWindow::loser(){
    QString st ="游戏结束！\n 您最终的得分是:";
    st += QString::number(g.count);
    QMessageBox::information(NULL, "游戏结束", st, QMessageBox::NoButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_clicked()
{
    if (g.isplaying == 1) return;
    begin();
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(g.isplaying == 0) return;
    if (event->key() == Qt::Key_A){
        g.run('a');
        updateScr();
    }
    if (event->key() == Qt::Key_D){
        g.run('d');
        updateScr();
    }
    if (event->key() == Qt::Key_W){
        g.run('w');
        updateScr();
    }
    if (event->key() == Qt::Key_S){
        g.run('s');
        updateScr();
    }
    if (event->key() == Qt::Key_5){
        egg.clear();
        egg.push_back("5");
        qDebug()<< egg <<endl;
    }
    if (event->key() == Qt::Key_2){
        egg.push_back("2");
    }
    if (event->key() == Qt::Key_0){
        egg.push_back("0");
        if (egg == "520"){
            For(i, 0, 3) For(j, 0, 3) g.a[i][j] = 0;
            ui->gamepad->changemap(g.a);
            g.a[0][0] = 5;
            g.a[0][1] = 2;
            g.a[0][2] = 7;
            g.a[1][1] = 1;
            g.a[1][2] = 3;
            g.a[2][2] = 1;
            g.a[2][3] = 4;
            for(int i = 0; i <=3; i++)
                for(int j = 0; j <= 3;j ++)
                    ui->gamepad->f[i][j]->setnum(g.a[i][j], true, 1);
            ui->score->setDigitCount(7);
            ui->score->display("5201314");
        }
    }
}

void MainWindow::begin(){
    g.init();
    QIcon lose(":/lose.png");
    QIcon win(":/win.png");
    ui->start->setIcon(win);
    ui->score->display(g.count);
    updateScr();
    updateScr();
    //ui->gamepad->changemap(g.print().a);
    //ui->score->display(g.print().score);
}

void MainWindow::end(){
    g.isplaying = 0;
    QIcon lose(":/lose.png");
    ui->start->setIcon(lose);
    loser();

}

void MainWindow::updateScr(){
        ui->gamepad->changemap(g.print().a);
        ui->score->display(g.print().score);
        if (g.die()){
            end();
        }else{
            g.isplaying = 0;
            Game::node tmp1 = g.fresh();
            Sleep(500);
            ui->gamepad->changemap(g.print().a, tmp1.x, tmp1.y);
            ui->score->display(g.print().score);
            g.isplaying = 1;
        }
}

void MainWindow::on_reset_clicked()
{
    g.init();
    QIcon lose(":/lose.png");
    QIcon win(":/win.png");
    ui->start->setIcon(win);
    ui->score->display(g.count);
    ui->gamepad->changemap(g.print().a);
    g.isplaying = 0;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->hide();
}

void MainWindow::on_action_2_triggered()
{
    help_con();
}

void MainWindow::on_action_3_triggered()
{
    help_rule();
}

void MainWindow::about(){
    QString st = "Game Core @赵雯玥\n Powered by Shbing\n V1.0";
    QMessageBox::information(NULL, "操作帮助", st, QMessageBox::NoButton);
}

void MainWindow::on_action_4_triggered()
{
    about();
}
