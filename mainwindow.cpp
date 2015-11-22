#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include<cmath>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::f()
{

    int dot_number = 150;

    buf_k_ = 1;
//the limit for coordinate system
    left_x = 0;
    right_x = 150;

    below_y = -10;
    top_y = 50;

     double h = 0.4;


   QVector<double> x(dot_number), y(dot_number); // initialize with entries 0..100

   QVector<double> z1(dot_number+1 ),  z2(dot_number+1),  z3(dot_number+1);
   double x_t = 2;
   double k = 10, a1 = 2, a2 = 3, b1 = 4, b2 = 3;


   for(int i = 1; i < dot_number; i++)
   {

       z1[i+1] = z1[i] +  h * z2[i];
       z2[i+1] = z2[i] + h * z3[i];

       z3[i+1] =z3[i] + h * ((x_t - (b2*b2 + 2 * b1 * b2) * z3[i] - (b1 + 2 * b2) * z2[i] - z1[i]) / (b1 * b2));

       x[i] = i*h + left_x; // x goes from -1 to 1
       y[i] = -(a1 * a2 * k) * z2[i+1] + z2[i]*(a1 - a2) + k*z1[i];

   }


  // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);

    ui->widget->graph(0)->setPen(QColor(Qt::black));//задаем цвет точки

    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(left_x, right_x);
    ui->widget->yAxis->setRange(below_y, top_y);
    ui->widget->replot();

    // paint experementl line
    //-------------------------------------------
    QVector<double> x1(dot_number), y1(dot_number);
    double dy = 0.2;

    for(int i = 1; i < dot_number; i++)
    {
        x1[i] = x [i];
        y1[i] = y[i] + triangular(-dy, dy, 1/dy)-0.8;
    }

    ui->widget->addGraph();
    ui->widget->graph(1)->setData(x1, y1);

    ui->widget->graph(1)->setPen(QColor(Qt::red));//задаем цвет точки

    ui->widget->replot();

    //-------------------------------------------
    QVector<double> x2(dot_number), y2(dot_number);
    /* double*/ dy = 0.1;

    for(int i = 1; i < dot_number; i++)
    {
        x2[i] = x [i];
        y2[i] = y[i] + triangular(-dy, dy, 1/dy)-0.8;
    }

    ui->widget->addGraph();
    ui->widget->graph(2)->setData(x2, y2);

    ui->widget->graph(2)->setPen(QColor(Qt::blue));//задаем цвет точки

    ui->widget->replot();

    //-------------------------------------------
    QVector<double> x3(dot_number), y3(dot_number);
    /*double*/ dy = 0.05;

    for(int i = 1; i < dot_number; i++)
    {
        x3[i] = x [i];
        y3[i] = y[i] + triangular(-dy, dy, 1/dy)-0.8;
    }

    ui->widget->addGraph();
    ui->widget->graph(3)->setData(x3, y3);

    ui->widget->graph(3)->setPen(QColor(Qt::gray));//задаем цвет точки

    ui->widget->replot();
//---------------------------------
    ui->horizontalSlider->setRange(1, 100);
    QObject::connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setCoordinate(int)));

}

//triangular distribution
double MainWindow::triangular(double a,double b,double c) {
   double U = rand() / (double) RAND_MAX;
   double F = (c - a) / (b - a);
   if (U <= F)
      return a + sqrt(U * (b - a) * (c - a));
   else
      return b - sqrt((1 - U) * (b - a) * (b - c));
}


//change
void MainWindow::setCoordinate(int k)
{
    ui->widget->xAxis->setRange(left_x, right_x - k*((right_x - left_x)/(top_y - below_y)) );
    ui->widget->yAxis->setRange(below_y, top_y - k);
    ui->widget->replot();

}
