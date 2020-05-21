#ifndef SQUARE_H
#define SQUARE_H

#include <QWidget>

namespace Ui {
class square;
}

class square : public QWidget
{
    Q_OBJECT

public:
    explicit square(QWidget *parent = nullptr);
    ~square();
    void setnum(int n, bool isSlow = false, bool isegg = false);
    QColor getBackcolor(int n);

private:
    Ui::square *ui;
};

#endif // SQUARE_H
