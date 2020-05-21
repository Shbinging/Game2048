#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

#include <QWidget>
#include "square.h"
namespace Ui {
class Gamematrix;
}

class Gamematrix : public QWidget
{
    Q_OBJECT

public:
    explicit Gamematrix(QWidget *parent = nullptr);
    ~Gamematrix();
    void changemap(int a[][4], int x1= -1, int y1 = -1, int x2 = -1, int y2 = -1);
    square * f[10][10];
private:
    Ui::Gamematrix *ui;
};

#endif // GAMEMATRIX_H
