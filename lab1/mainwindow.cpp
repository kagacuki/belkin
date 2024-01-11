#include "mainwindow.h"
#include "QtMath"
#include "iostream"
#include "QGraphicsScene"
#include "QGraphicsView"


float PL(float f, float d){
return 28 + 22 * log10(f) + 20* log10(d);
}

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
{

QGraphicsScene* scene = new QGraphicsScene();
int maxX = 1000;
int maxY = 1000;
int onePixDistance = 100; //[m]
int TxPower = 23; // [dBm]
int antGain = 12; // [dBi]
float freq = 2.5; // [GHz]
int cellPosX = 500;
int cellPosY = 500;
QPixmap map(maxX, maxY); // создаем карту для рисования
QPainter p(&map);
//p.setPen(QColor(0, 0, 0, 255)); // <— задание цвета
for(int i = 0; i < maxX; i++){
for(int j = 0; j < maxY; j++)
{
float distance = 0;
distance = sqrt(pow(abs(cellPosX - i),2) + pow(abs(cellPosY - j),2)); // [pix]
distance *= onePixDistance; // [meters]
float sigPower = TxPower + antGain - PL(freq, distance);
if(sigPower < -34 && sigPower >= -44)
{
p.setPen(QColor(0, 0, 0, 255)); // <— задание цвета
}
else if(sigPower < -44 && sigPower >= -54)
{
p.setPen(QColor(255, 0, 0, 255)); // <— задание цвета
}
else if (sigPower < -54 && sigPower >= -74)
{
p.setPen(QColor(255, 102, 0, 255)); // <— задание цвета
}
else if (sigPower < -74 && sigPower >= -84)
{
p.setPen(QColor(255, 255, 0, 255)); // <— задание цвета
}
else if (sigPower < -84 && sigPower >= -114)
{
p.setPen(QColor(153, 255, 153, 255)); // <— задание цвета
}
else if (sigPower < -114 && sigPower >= -124)
{
p.setPen(QColor(128, 166, 255, 255)); // <— задание цвета
}
else if (sigPower < -124 && sigPower >= -144)
{
p.setPen(QColor(0, 0, 255, 255)); // <— задание цвета
}
p.drawPoint(i, j);
}
}
p.end();
scene->addPixmap(map);
QGraphicsView* view = new QGraphicsView(scene);
setCentralWidget(view);

}

MainWindow::~MainWindow()
{
}
