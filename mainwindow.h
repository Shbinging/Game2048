#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include<QKeyEvent>
#include"qstring.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    Game::game g;
    void updateScr();
    void begin();
    void end();
    void keyPressEvent(QKeyEvent *event);

    QString egg;
private slots:
    void on_pushButton_clicked();

    void on_start_clicked();

    void on_reset_clicked();

    void on_action_2_triggered();

    void loser();

    void help_con();

    void help_rule();

    void about();

    void on_action_3_triggered();

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
