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

#include "Study.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


double sqerr(double a, double b) {

    return ((a-b)*(a-b));
}
//---------------------------------------------------------------------------


int returnid(int a, int tmas[50][50])
{
  int id=0, idw=0;

  if (a < 6)  idw=0; else
  if (a < 12) idw=1; else
  if (a < 18) idw=2; else
  if (a < 24) idw=3; else
  if (a < 30) idw=4; else
  if (a < 36) idw=5; else
  if (a < 42) idw=6; else
  if (a < 48) idw=7; else
  if (a < 54) idw=8; else
  if (a < 60) idw=9;

  if (tmas[2][0] < 10) id=0; else
  if (tmas[2][0] < 20) id=1; else
  if (tmas[2][0] < 30) id=2; else
  if (tmas[2][0] < 40) id=3; else
  if (tmas[2][0] < 50) id=4; else
  if (tmas[2][0] < 60) id=5; else
  if (tmas[2][0] < 70) id=6; else
  if (tmas[2][0] < 80) id=7; else
  if (tmas[2][0] < 90) id=8; else
  if (tmas[2][0] < 100) id=9;

  if(idw==id) id=1;
  else id=0;

  return id;
}
//---------------------------------------------------------------------------

int returnidF(int a, int idp)
{
  int id=0, idw=0;

  if (a < 6)  idw=0; else
  if (a < 12) idw=1; else
  if (a < 18) idw=2; else
  if (a < 24) idw=3; else
  if (a < 30) idw=4; else
  if (a < 36) idw=5; else
  if (a < 42) idw=6; else
  if (a < 48) idw=7; else
  if (a < 54) idw=8; else
  if (a < 60) idw=9;

  if (idp < 10) id=0; else
  if (idp < 20) id=1; else
  if (idp < 30) id=2; else
  if (idp < 40) id=3; else
  if (idp < 50) id=4; else
  if (idp < 60) id=5; else
  if (idp < 70) id=6; else
  if (idp < 80) id=7; else
  if (idp < 90) id=8; else
  if (idp < 100) id=9;

  if(idw==id) id=1;
  else id=0;

  return id;
}
//---------------------------------------------------------------------------


double getE(int c, int rmas[1000][100], int wglob, int hglob, int sCl)
{
        float a=60, b=0, bt=0, E=0;

        int imas[1000], tmas[50][50];
        for (int i=0; i<1000; i++) imas[i]=0;
        for (int i=0; i<50; i++)
                for (int j=0; j<50; j++)
                        tmas[i][j]=0;

        for (int i=0; i<60; i++)
        {
                Form1->ImageList1->GetBitmap(i,Form1->Image1->Picture->Bitmap);
                Form1->Refresh();

                location(wglob, hglob, sCl);

                getnumgauss(Form1->Image2, imas, wglob, hglob, sCl, c);

                getid(rmas, imas, tmas);

                b=b+returnid(i, tmas);

                bt=bt + sqerr(1, returnid(i, tmas));
        }

       return 1./60.*bt;


}
