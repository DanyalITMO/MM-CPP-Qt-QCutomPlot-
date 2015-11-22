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

//the limit for coordinate system
     double left_x = 0;
     double right_x = 100;

     double top_y = 25;
     double below_y = -10;

     double h = 0.4;


   QVector<double> x(dot_number), y(dot_number); // initialize with entries 0..100

   QVector<double> z1(dot_number+1 ),  z2(dot_number+1),  z3(dot_number+1);
   double x_t = 2;/*double z1 = 0,  z2 = 0,  z3 = 0, z1_old, z2_old, z3_old, x_t = 2;*/
   double k = 10, a1 = 2, a2 = 3, b1 = 4, b2 = 3;


   for(int i = 1; i < dot_number; i++)
   {

       z1[i+1] = z1[i] +  h * z2[i];
       z2[i+1] = z2[i] + h * z3[i];

      // z3[i+1] =z3[i] + h * ((2 * b1 * b2 + b2*b2) * z3[i] + (b1 + 2 * b2) * z2[i] + z1[i] - x_t) / ((- b1) * b2 * b2);
       z3[i+1] =z3[i] + h * ((x_t - (b2*b2 + 2 * b1 * b2) * z3[i] - (b1 + 2 * b2) * z2[i] - z1[i]) / (b1 * b2));

        x[i] = i*h + left_x; // x goes from -1 to 1
        //y[i] = k * (a1*a2 * z3[i] - (a1 - a2) * z2[i] + z1[i]);
        y[i] = -(a1 * a2 * k) * z2[i+1] + z2[i]*(a1 - a2) + k*z1[i];

   }


  // create graph and assign data to it:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);

    ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки

    // give the axes some labels:
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(left_x, right_x);
    ui->widget->yAxis->setRange(below_y, top_y);
    ui->widget->replot();

}


double MainWindow::triangular(double a,double b,double c) {
   double U = rand() / (double) RAND_MAX;
   double F = (c - a) / (b - a);
   if (U <= F)
      return a + sqrt(U * (b - a) * (c - a));
   else
      return b - sqrt((1 - U) * (b - a) * (b - c));
}
