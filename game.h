#ifndef GAME_H
#define GAME_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define For(i, l, r) for(int i= l; i<= r; i++)
namespace Game{
struct map{
    int a[4][4];
    int score;
};
struct node{
     int x= -1, y = -1;
     node(int a, int b){
           x = a;
           y = b;
     }
};
class game
{
public:
int a[4][4];// 主界面 4*4 ,二维数组表示, 0 表示空
int count = 0;// 游戏积分
bool isplaying;
map print()// count 表示积分
{
    map tmp;
    For(i, 0, 3) For(j, 0, 3)
        tmp.a[i][j] = a[i][j];
    tmp.score = count;
    return tmp;
}

void init()// 开始时任意位置生成两个2
{
    isplaying = 1;
    count = 0;
    memset(a, 0, sizeof(a));
   /* srand((unsigned)time(NULL));// 用时间作为随机数的种子，避免之后产生的随机数都一样，参考CSDN代
    int x, y;
    x = rand() % 4;// x取值为0,1,2,3
    y = rand() % 4;// y取值也0,1,2,3；x,y表示第一个随机数出现的横纵坐标
    a[x][y] = 2;
    x = rand() % 4;
    y = rand() % 4;// x,y取下一个位置，准备好，生成之后的随机数
    while (a[x][y] == 2) // 如果随机数取得和之前的一样，则重新取，直到取到不一样的
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    a[x][y] = 2;*/
}

node fresh()// 每一回合过后生成新的2 0成功 1 不成功
{
    bool f = 0;
    For(i, 0, 3) For(j, 0, 3) if (a[i][j] == 0) f = 1;
    if (!f) return node(-1, -1);
    srand((unsigned)time(NULL));
    int x, y;
    x = rand() % 4;
    y = rand() % 4;
    while (a[x][y] != 0) //当该位置不为0，重新取坐标
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    a[x][y] = 2;
    printf("%d %d\n", x+1, y+1);
    return node(x ,y);
}

bool die()// 判断游戏是否结束，即是否每个方向都无法移动
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            if (a[i][j] == a[i][j + 1])
                return false;// 左右有相等的，没死，返回false
            if (a[i][j] == a[i + 1][j])
                return false;// 上下有相等的，没死，返回false
        }
    isplaying = 0;
    return true;// 都没有相等的，都无法移动，死了，返回true
}

void run(char x)// 主函数
{
    switch (x)
    {
    case 'w':
        for (int j = 0; j < 4; ++j)
            for (int i = 3; i > 0; --i)
                if (a[i][j] != 0)
                    for (int h = i - 1; h >= 0; --h)
                        if (a[h][j] != 0)
                        {
                            if (a[h][j] == a[i][j])
                            {
                                a[h][j] *= 2;
                                count += a[h][j];
                                a[i][j] = 0;// 每向上移动时，上面的格子先翻倍，下面的格子都置成0；之后全盘扫描进行紧凑操作
                                i = h;// 一次移动回合中，刚发生过合并的格子不能再跟上面的合并
                                break;
                            }
                            else
                                break;
                        }
        for (int j = 0; j < 4; ++j)
            for (int i = 0; i < 3; ++i)
                if (a[i][j] == 0)
                    for (int h = i + 1; h < 4; ++h)
                        if (a[h][j] != 0)
                        {
                            a[i][j] = a[h][j];
                            a[h][j] = 0;
                            break;
                        }
        break;

    case 'a':
        for (int i = 0; i < 4; ++i)
            for (int j = 3; j > 0; --j)
                if (a[i][j] != 0)
                    for (int h = j - 1; h >= 0; --h)
                    {
                        if (a[i][h] != 0)
                            if (a[i][j] == a[i][h])
                            {
                                a[i][h] *= 2;
                                count += a[i][h];
                                a[i][j] = 0;
                                j = h;
                                break;
                            }
                            else
                                break;
                    }
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 3; ++j)
                if (a[i][j] == 0)
                    for (int h = j + 1; h < 4; ++h)
                        if (a[i][h] != 0)
                        {
                            a[i][j] = a[i][h];
                            a[i][h] = 0;
                            break;
                        }
        break;
    case 's':
        for (int j = 0; j < 4; ++j)
            for (int i = 0; i < 3; ++i)
                if (a[i][j] != 0)
                    for (int h = i + 1; h < 4; ++h)
                    {
                        if (a[h][j] == a[i][j])
                        {
                            a[h][j] *= 2;
                            count += a[h][j];
                            a[i][j] = 0;
                            i = h;
                            break;
                        }
                        else
                            break;
                    }
        for (int j = 0; j < 4; ++j)
            for (int i = 3; i > 0; --i)
                if (a[i][j] == 0)
                    for (int h = i - 1; h >= 0; --h)
                        if (a[h][j] != 0)
                        {
                            a[i][j] = a[h][j];
                            a[h][j] = 0;
                            break;
                        }
        break;

    case 'd':
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 3; ++j)
                if (a[i][j] != 0)
                    for (int h = j + 1; h < 4; ++h)
                    {
                        if (a[i][h] != 0)
                            if (a[i][j] == a[i][h])
                            {
                                a[i][h] *= 2;
                                count += a[i][h];
                                a[i][j] = 0;
                                j = h;
                                break;
                            }
                            else
                                break;
                    }
        for (int i = 0; i < 4; ++i)
            for (int j = 3; j > 0; --j)
                if (a[i][j] == 0)
                    for (int h = j - 1; h >= 0; --h)
                        if (a[i][h] != 0)
                        {
                            a[i][j] = a[i][h];
                            a[i][h] = 0;
                            break;
                        }
        break;

    default:
        break;
    }
}
    game(){
        isplaying = 0;
    }
};
}
#endif // GAME_H
