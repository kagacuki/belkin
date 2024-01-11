#include "mainwindow.h"
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>

int maxX=500, maxY=500;

float PL(float f, float d)
{
    return 28 + 22 * log10(d) + 20*log10(f);
}

float delay(int N, float f)
{
    if (N == 3)
    {
        return 23+0.3*f;
    }
    if (N == 2)
    {
        return 2+0.2*f;
    }
    if (N == 1)
    {
        return 4.85+0.12*f;
    }
    if (N == 0)
    {
        return 5+4*f;
    }

    else
    {
        return 0;
    }
}

int DrawPixel(QPainter* Pix, int x, int y)
{
    Pix->drawPoint(x + 1, y + 1);
    Pix->drawPoint(x + 1, y - 1);
    Pix->drawPoint(x - 1, y + 1);
    Pix->drawPoint(x - 1, y - 1);
    Pix->drawPoint(x, y);
    Pix->drawPoint(x, y - 1);
    Pix->drawPoint(x, y + 1);
    Pix->drawPoint(x - 1, y);
    Pix->drawPoint(x + 1, y);
    return 0;
}

int* N_of_obstructions(QPainter* Pix, QPixmap* Map, int *Number, int x0, int x1, int y0, int y1)
{
    QImage image = Map->toImage();
    int deltax = abs(x1 - x0);
    int deltay = abs(y1 - y0);
    int signx = x0 < x1 ? 1 : -1;
    int signy = y0 < y1 ? 1 : -1;
    int error = deltax - deltay;

    int Xless=-50;
    int Yless=-50;

    QRgb color1=image.pixel(x1, y1);
    int red1 = qRed(color1);
    int green1 = qGreen(color1);
    int blue1 = qBlue(color1);
    if (red1==34 && green1==34 && blue1==34) //бетон
    {
        Number[0]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==161 && green1==104 && blue1==7) //дерево
    {
        Number[1]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==77 && green1==101 && blue1==110) //IRR стекло
    {
        Number[2]+=1;
        Xless=x1;
        Yless=y1;
    }
    if (red1==190 && green1==208 && blue1==215) //Стеклопакет
    {
        Number[3]+=1;
        Xless=x1;
        Yless=y1;
    }
    while (x0 != x1 || y0 != y1)
    {

        QRgb color2=image.pixel(x0, y0);
        int red2 = qRed(color2);
        int green2 = qGreen(color2);
        int blue2 = qBlue(color2);

        if (red2==34 && green2==34 && blue2==34) //бетон
        {
            if ((Xless==-50) && (Yless==-50))
            {
                Number[0]+=1;
                Xless=x0;
                Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless)))
            {
            Xless=x0;
            Yless=y0;
            }
            else
            {
            Number[0]+=1;
            }
        }
        if (red2==161 && green2==104 && blue2==7) //дерево
        {
            if ((Xless==-50) && (Yless==-50))
            {
            Number[1]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless)))
            {
            Xless=x0;
            Yless=y0;
            }
            else
            {
            Number[1]+=1;
            }
        }
        if (red2==77 && green2==101 && blue2==110) //IRR стекло
        {
            if ((Xless==-50) && (Yless==-50))
            {
            Number[2]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless)))
            {
            Xless=x0;
            Yless=y0;
            }
            else
            {
            Number[2]+=1;
            }
        }
        if (red2==190 && green2==208 && blue2==215) //Стеклопакет
        {
            if ((Xless==-50) && (Yless==-50))
            {
            Number[3]+=1;
            Xless=x0;
            Yless=y0;
            }
            if (((x0-1==Xless) || (x0+1==Xless) || (x0==Xless)) && ((y0==Yless) || (y0-1==Yless) || (y0+1==Yless)))
            {
            Xless=x0;
            Yless=y0;
            }
            else
            {
            Number[3]+=1;
            }
        }

        int error2 = error*2;
        if (error2 > -deltay)
        {
            error -= deltay;
            x0 += signx;
        }
        if (error2 < deltax)
        {
            error += deltax;
            y0 += signy;
        }
    }
    return Number;
}

class Obstruction { //препятствия
public:
    bool irrglass; //IRR стекло
    bool doubleglass; //стеклопакет
    bool concrete; //бетон
    bool wood; //дерево
};

class Wall: public Obstruction
{
public:
    void wall(QPainter* Pix, int x0, int x1, int y0, int y1) //линия
    {
        int deltax = abs(x1 - x0);
        int deltay = abs(y1 - y0);
        int signx = x0 < x1 ? 1 : -1;
        int signy = y0 < y1 ? 1 : -1;
        int error = deltax - deltay;
        if (concrete == true)
        {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true)
        {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doubleglass == true)
        {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrglass == true)
        {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        DrawPixel(Pix, x1, y1);
        while (x0 != x1 || y0 != y1)
        {
            DrawPixel(Pix, x0, y0);
            int error2 = error*2;
            if (error2 > -deltay)
            {
                error -= deltay;
                x0 += signx;
            }
            if (error2 < deltax)
            {
                error += deltax;
                y0 += signy;
            }
        }
    }
};

class Circle: public Obstruction
{
public:
    void circle(QPainter* Pix, int X1, int Y1, int R) //круг
    {
        int x = 0;
        int y = R;
        int delta = 1 - 2 * R;
        int error = 0;
        if (concrete == true)
        {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true)
        {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doubleglass == true)
        {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrglass == true)
        {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        while (y >= x)
        {
            DrawPixel(Pix, X1 + x, Y1 + y);
            DrawPixel(Pix, X1 + x, Y1 - y);
            DrawPixel(Pix, X1 - x, Y1 + y);
            DrawPixel(Pix, X1 - x, Y1 - y);
            DrawPixel(Pix, X1 + y, Y1 + x);
            DrawPixel(Pix, X1 + y, Y1 - x);
            DrawPixel(Pix, X1 - y, Y1 + x);
            DrawPixel(Pix, X1 - y, Y1 - x);
            error = 2 * (delta + y) - 1;
            if ((delta < 0) && (error <= 0))
            {
                delta += 2 * ++x + 1;
                continue;
            }
            if ((delta > 0) && (error > 0))
            {
                delta -= 2 * --y + 1;
                continue;
            }
            delta += 2 * (++x - --y);
        }
    }
};

class Square: public Obstruction
{
public:
    void square(QPainter* Pix, int x0, int x1, int y0, int y1) //прямоугольник
    {
        if (concrete == true)
        {
            Pix->setPen(QColor(34, 34, 34, 255));
        }
        if (wood == true)
        {
            Pix->setPen(QColor(161, 104, 7, 255));
        }
        if (doubleglass == true)
        {
            Pix->setPen(QColor(77, 101, 110, 255));
        }
        if (irrglass == true)
        {
            Pix->setPen(QColor(190, 208, 215, 255));
        }
        if (x0<x1)
        {
            for (int x=x0; x<x1; x++)
            {
                DrawPixel(Pix, x, y0);
                DrawPixel(Pix, x, y1);
            }
        }
        if (x1<x0)
        {
            for (int x=x1; x<x0; x++)
            {
                DrawPixel(Pix, x, y0);
                DrawPixel(Pix, x, y1);
            }
        }
        if (y0<y1)
        {
            for (int y=y0; y<y1; y++)
            {
                DrawPixel(Pix, x0, y);
                DrawPixel(Pix, x1, y);
            }
        }
        if (y1<y0)
        {
            for (int y=y1; y<y0; y++)
            {
                DrawPixel(Pix, x0, y);
                DrawPixel(Pix, x1, y);
            }
        }
    }
};


void Pen_Color (QPainter* p,float sigPower)
{
    if(sigPower >= -54)
    {
        p->setPen(QColor(255, 0, 0, 255)); // <-- задание цвета красный
    }
    if (sigPower < -54 && sigPower >= -59)
    {
        p->setPen(QColor(246, 70, 0, 255)); //
    }
    if (sigPower < -59 && sigPower >= -64)
    {
        p->setPen(QColor(228, 110, 0, 255)); // красноорнжевый
    }
    if (sigPower < -64 && sigPower >= -69)
    {
        p->setPen(QColor(228, 140, 0, 255)); //
    }
    if (sigPower < -69 && sigPower >= -74)
    {
        p->setPen(QColor(255, 175, 0, 255)); //оранжевый
    }
    if (sigPower < -74 && sigPower >= -79)
    {
        p->setPen(QColor(255, 200, 0, 255)); //
    }
    if (sigPower < -79 && sigPower >= -84)
    {
        p->setPen(QColor(255, 255, 0, 255)); //желтый
    }
    if (sigPower < -84 && sigPower >= -89)
    {
        p->setPen(QColor(230, 255, 0, 255)); //
    }
    if (sigPower < -89 && sigPower >= -94)
    {
        p->setPen(QColor(216, 255, 0, 255)); //лаймовый
    }
    if (sigPower < -94 && sigPower >= -99)
    {
        p->setPen(QColor(150, 255, 0, 255)); //
    }
    if (sigPower < -99 && sigPower >= -104)
    {
        p->setPen(QColor(36, 255, 0, 255)); //зелёный
    }
    if (sigPower < -104 && sigPower >= -109)
    {
        p->setPen(QColor(0, 255, 70, 255)); //
    }
    if (sigPower < -109 && sigPower >= -114)
    {
        p->setPen(QColor(0, 255, 143, 255)); //зелёноголубой
    }
    if (sigPower < -114 && sigPower >= -119)
    {
        p->setPen(QColor(0, 255, 180, 255)); //
    }
    if (sigPower < -119 && sigPower >= -124)
    {
        p->setPen(QColor(0, 255, 255, 255)); //голубой
    }
    if (sigPower < -124 && sigPower >= -129)
    {
        p->setPen(QColor(0, 180, 255, 255)); //
    }
    if (sigPower < -129 && sigPower >= -134)
    {
        p->setPen(QColor(0, 130, 255, 255)); //синий
    }
    if (sigPower < -134)
    {
        p->setPen(QColor(40, 0, 255, 255)); //глубокий синий
    }
        /*if (abs(sigPower) > 200)
        {
            p->setPen(QColor(255,255,255,255));
        }*/
}

void Fill_Field(QPainter* p, QPixmap* map,QImage* image, int cellPosX, int cellPosY, int onePixDistance, int TxPower, int antGain, float freq)
{
    for(int i = 0; i < maxX; i++)
    {
        for(int j = 0; j < maxY; j++)
        {
            float distance = 0;
            distance =sqrt (pow(abs(cellPosX - i), 2) + pow(abs(cellPosY-j), 2));
            distance *= onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, distance);
            int NumObs[4]{}; //пустой массив препятствий
            N_of_obstructions(p, map, NumObs, cellPosX, i, cellPosY, j); //заполнение массива
            if (NumObs[0] > 0 || NumObs[1] > 0 || NumObs[2] > 0 || NumObs[3] > 0)
            {
                //затухание
                sigPower=sigPower-NumObs[0]*delay(0, freq)-NumObs[1]*delay(1, freq)-NumObs[2]*delay(2, freq)-NumObs[3]*delay(3, freq);
            }

            Pen_Color(p, sigPower);

            QRgb color=image->pixel(i, j); //оставляем нарисованные препятствия
            int red = qRed(color);
            int green = qGreen(color);
            int blue = qBlue(color);
            if (red==34 && green==34 && blue==34)
            {
                p->setPen(QColor(34, 34, 34, 255));
            }
            if (red==161 && green==104 && blue==7)
            {
                p->setPen(QColor(161, 104, 7, 255));
            }
            if (red==77 && green==101 && blue==110)
            {
                p->setPen(QColor(77, 101, 110, 255));
            }
            if (red==190 && green==208 && blue==215)
            {
                p->setPen(QColor(190, 208, 215, 255));
            }
            //рисуем пиксель
            p->drawPoint(i, j);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGraphicsScene* scene = new QGraphicsScene();

    int onePixDistance = 10; //m
    int TxPower = 23;
    int antGain = 12;
    float freq=2.5;
    srand(time(NULL)); //установка точки 5G New Radio
    int cellPosX =rand()%maxX;
    int cellPosY=rand()%maxY;
    QPixmap map(maxX, maxY); // создаем карту для рисования
    QPainter p(&map);

    Circle wall; //стена
    wall.concrete = true;
    wall.circle(&p, 500, 450, 130);

    Wall Fence; //забор
    Fence.wood = true;
    Fence.wall(&p, 200, 500, 100, 50);

    Square Office; //офис
    Office.doubleglass = true;
    Office.square(&p, 50, 300, 150, 400);

    QImage image = map.toImage();

    Fill_Field(&p, &map,&image, cellPosX, cellPosY, onePixDistance, TxPower, antGain, freq);

    p.setPen(QColor(255, 255, 255, 255)); //нарисованная точка доступа
    p.drawPoint(cellPosX, cellPosY);

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}
