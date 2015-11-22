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

void MainWindow::on_pushButton_clicked()
{
    QVector<double> x(101), y(101); // initialize with entries 0..100
       for (int i=0; i<101; ++i)
       {
         x[i] = i/50.0 - 1; // x goes from -1 to 1
         y[i] = x[i]*x[i]; // let's plot a quadratic function
       }
       // create graph and assign data to it:
       ui->widget->addGraph();
       ui->widget->graph(0)->setData(x, y);
       // give the axes some labels:
       ui->widget->xAxis->setLabel("x");
       ui->widget->yAxis->setLabel("y");
       // set axes ranges, so we see all data:
       ui->widget->xAxis->setRange(-1, 1);
       ui->widget->yAxis->setRange(0, 1);
       ui->widget->replot();
}

void MainWindow::f()
{

//the limit for triangular distribution
        double below_limit = -10;
        double top_limit = 10;
        double max_position = /*(((top_limit - below_limit) / 2) + below_limit)*/ 6;

//the limit for coordinate system
        double left_x = -10;
        double right_x = 10;

        double top_y = -10;
        double below_y = 10;

// the number of points on the coordinate system
        int dot_number = 10000;
        double step = (right_x - left_x) / dot_number;

        QVector<double> x(dot_number), y(dot_number); // initialize with entries 0..100
        for (int i=0; i<dot_number; ++i)
        {
          x[i] = i*step + left_x; // x goes from -1 to 1
          /*cout<<*/(y[i] =  triangular(below_limit, top_limit, max_position)); // let's plot a quadratic function
        }
        // create graph and assign data to it:
        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y);

        ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
        //формируем вид точек
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));

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
