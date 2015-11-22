#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    double left_x;
    double right_x;

    double below_y;
    double top_y;

    int buf_k_;

    int dot_number;

    double dy;
    double h;

void f();
void distributionF005(void);
void distributionF01(void);
void distributionF02(void);
double triangular(double a,double b,double c);
private slots:
    void setCoordinate(int);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
