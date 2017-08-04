//---------------------------------------------------------------------------

#ifndef GradH
#define GradH
//---------------------------------------------------------------------------

double F1(double x, double u);

double GradF1(double x, double u);

double GradF2(double x, double u);

double inner_prod(double x, double y);

double FindMin(double s, double p);

double GradMethod(int rmas[1000][100], int wglob, int hglob, int sCl);


//---------------------------------------------------------------------------
#endif
