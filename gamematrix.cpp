#include "gamematrix.h"
#include "ui_gamematrix.h"
#include "qlabel.h"
#include "square.h"
#define For(i, l, r) for(int i = l; i <= r; i++)
Gamematrix::Gamematrix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gamematrix)
{
    ui->setupUi(this);
    for(int i = 0; i <= 3; i++)
       for(int j = 0; j <= 3; j++){
        f[i][j] = new square;
        f[i][j]->setnum(0);
        ui->grid->addWidget(f[i][j], i, j);
    }
}

void Gamematrix::changemap(int a[][4], int x1, int y1, int x2, int y2){
    for(int i = 0; i <=3; i++)
        for(int j = 0; j <= 3; j++){
            if ((i == x1 && j == y1 ) || (i == x2 && j == y2)) f[i][j]->setnum(a[i][j], 1);
            else f[i][j]->setnum(a[i][j], 0);
        }
}

Gamematrix::~Gamematrix()
{
    delete ui;
}
