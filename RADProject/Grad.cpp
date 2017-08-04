        //---------------------------------------------------------------------------
#include <vcl.h>
#include <vfw.h>
#include <fstream.h>
#include <conio.h>
#include <iostream.h>
#include <stdio.h>
#include <iomanip.h>
#include <sysmac.h>
#include <windows.h>
#include <winnt.h>
#include <cmath>
#include <cstdlib>


#include "Main.h"
#include "ruleget.h"
#include "Grad.h"
#include "Study.h"
#include "Imloc.h"

#pragma hdrstop
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

double F1(double a=0, double b=8, double u=0) {

    return exp(-( ((u-a)*(u-a))/(2*b*b) ) ); //функция
}
//---------------------------------------------------------------------------

double F1dx(double a=0, double b=8, double u=0) {
    double eps=0.1;
    return exp(-( ((u-(a+eps))*(u-(a+eps)))/(2*b*b) ) ); //функция
}
//---------------------------------------------------------------------------

double F1dy(double a=0, double b=8, double u=0) {
    double eps=0.0001;
    return exp(-( ((u-a)*(u-a))/(2*(b+eps)*(b+eps)) ) ); //функция
}
//---------------------------------------------------------------------------

double GradF2(double a=0, double b=8, double u=0) {
    double eps=0.1;
    return (F1dx(a, b, u)-F1(a, b, u))/eps;
}
//---------------------------------------------------------------------------

double GradF1(double a=0, double b=8, double u=0) {
    double eps=01;
    return (F1dy(a, b, u)-F1(a, b, u))/eps;
}
//---------------------------------------------------------------------------


double inner_prod(double x, double y) {return x*y;}
//---------------------------------------------------------------------------

//Одномерная оптимизация - применим метод золотого сечения
double FindMin(double a, double b)
{
    const double eps = 1e-8;
    const double tay = 1.618;
    double x1, x2, _x, xf1, xf2;
    int it(0);
    x1 = a + (b - a) / (tay * tay);
    x2 = a + (b - a) / tay;
    xf1 = F1(x1);
    xf2 = F1(x2);

  do
  {
    it++;
    if(xf1 >= xf2)
    {
        a = x1;
        x1 = x2;
        xf1 = F1(x2);
        x2 = a + (b - a) / tay;
        xf2 = F1(x2);
    }
    else
    {
        b = x2;
        x2 = x1;
        xf2 = xf1;
        x1 = a + (b - a) / (tay * tay);
        xf1 = F1(x1);
    }
  }
  while (fabs(b - a) > eps);

  return (a + b) / 2;
}
//---------------------------------------------------------------------------

double GradMethod(int rmas[1000][100], int wglob, int hglob, int sCl)
{
    double E;  //ср.кв. ошибка
    int iex=0;   //счетчик остановки

    double eps = 1e-1;
    const double EPS = 1e-1;

    //Начальное приближение
    double x=8;
    double Var = F1(x);
    double prVar = Var;
    double p, oldGrad, newGrad;
    p = - GradF1(x);
    //ShowMessage(AnsiString(p));

    oldGrad = - GradF1(x);

    double gradSquare = inner_prod(p, p);

    int numIter = 0;
    do
    {
        numIter++;
        double alpha, beta, newGradSquare, GradSquarePr;

        //Ищем минимум F1(x + alpha * p) с помощью метода одномерной оптимизации
        alpha = FindMin(x, p);
        //ShowMessage(AnsiString(alpha));

        x = x + alpha * p;

        if (numIter != 1){
                oldGrad = newGrad;
        }
        newGrad = - GradF1(x);

        oldGrad = newGrad - oldGrad;

        newGradSquare = inner_prod(newGrad, newGrad);
        GradSquarePr = inner_prod(newGrad, oldGrad);

        //ShowMessage(AnsiString(GradSquarePr));

        if (numIter == 1) beta = 0;
        else
        beta = GradSquarePr / newGradSquare;

        p = newGrad + beta * p;

        prVar = Var;
        Var = F1(x);

        gradSquare = GradSquarePr;

        E = getE(x, rmas, wglob, hglob, sCl);  //находим значение целевой функции (Study.cpp)
        iex++;
        if (iex == 25) break;
    }
    while (E > eps);



    //ShowMessage("Piter: " + AnsiString(numIter) + "\n Computed solution: [" + AnsiString(p[0]) + "; " + AnsiString(p[1]) + "] ");
    ShowMessage("Xiter: " + AnsiString(numIter) + "\n Computed solution: " + AnsiString(x) + "\n E: " + AnsiString(E));
    return x;
}
//---------------------------------------------------------------------------


