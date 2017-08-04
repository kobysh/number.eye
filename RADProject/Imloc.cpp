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
//---------------------------------------------------------------------------

void location(int& wglob, int& hglob, int sCl=180)
{
 int Height =  Form1->Image1->Picture->Bitmap->Height;
        int Width =  Form1->Image1->Picture->Bitmap->Width;
        byte Color;

        int minh=0, minht=0, maxh=0, maxht=0;
        int minv=0, minvt=0, maxv=0, maxvt=0;
        bool min=true;

//horizontal
        for(int x = 0; x < Width; x++) {
                for(int y = 0; y < Height; y++) {
                        Color = GetRValue(Form1->Image1->Picture->Bitmap->Canvas->Pixels[x][y]);

                        if (Color > sCl) {
                                minht=x;
                                if (min){minh=x; min=false;}
				if (minh > minht) minh=minht;
			}

			if (Color > sCl) {
				maxht=x;
				if (maxh < maxht) maxh=maxht;
			}

                }
        }


//vertical
        min=true;

        for(int x = 0; x < Width; x++) {
                for(int y = 0; y < Height; y++) {

                        Color = GetRValue(Form1->Image1->Picture->Bitmap->Canvas->Pixels[x][y]);

                        if (Color > sCl) {
                                minvt=y;
                                if (min){minv=y; min=false;}
				if (minv > minvt) minv=minvt;
                        }

			if (Color > sCl) {
				maxvt=y;
			        if (maxv < maxvt) maxv=maxvt;
                        }

                }
        }

//выводим обрезанное изображение

//cler image2
        for(int x = 0; x < Width; x++) {
                for(int y = 0; y < Height; y++) {
						Form1->Image2->Picture->Bitmap->Canvas->Pixels[x][y] = RGB(255, 255, 255);
                }
        }
//end_clear


         //ShowMessage(maxh);
         //ShowMessage(maxv);

         for(int x = minh; x < maxh; x++) {
                for(int y = minv; y < maxv; y++) {

                        Color = GetRValue(Form1->Image1->Picture->Bitmap->Canvas->Pixels[x][y]);
                        Form1->Image2->Picture->Bitmap->Canvas->Pixels[x-minh][y-minv] = RGB(Color, Color, Color);
         //для вывода картинки с пикселя 1,1: Pixels[x-minh][y-minv]
                }
         }

        //передача ш. и в. выделенной картинки
         wglob = 0;
         hglob = 0;
         wglob = maxh-minh;
         hglob = maxv-minv;
        /* lwglob = wglob;
         lhglob = hglob;  */


}
//---------------------------------------------------------------------------

void grayim(TImage* AImage)
{
 int Height =  AImage->Picture->Bitmap->Height;
 int Width =  AImage->Picture->Bitmap->Width;
 byte Color[3];
 byte ColorMid;

 for(int y = 0; y < Height; y++) {
    for(int x = 0; x < Width; x++) {
     Color[0] = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
     Color[1] = GetGValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
     Color[2] = GetBValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);

    // ColorMid = Color[0]*0.3+Color[1]*0.59+Color[2]*0.11;
     ColorMid = Color[0]*0.21+Color[1]*0.72+Color[2]*0.07;

     AImage->Picture->Bitmap->Canvas->Pixels[x][y] = RGB(ColorMid, ColorMid, ColorMid);
    }
 }

}
//---------------------------------------------------------------------------

void multiloc(TImage* AImage, TImage* BImage, int& vpixe, int& vmax, int& lwglob, int& lhglob, int& wglob, int& hglob, bool& cid2, int sCl=180)
{
        int Width = lwglob;
        int Height = lhglob;

        int vpixb=0, vtmp=0, vmaxt=0;
        int minh=0, minht=0, maxh=0, maxht=0;
        int minv=0, minvt=0, maxv=0, maxvt=0;
        bool min=true, cid=false;
        byte Color;

/* определение предела*/
        if (vmax==0){
                for(int x = 0; x < Width; x++) {
                       for(int y = 0; y < Height; y++) {

                                Color = GetRValue(BImage->Picture->Bitmap->Canvas->Pixels[x][y]);

                                if (Color < sCl) vmaxt++;
                       }
                        //ShowMessage(vmaxt);
                       if (vmaxt==Height) vmax=x;
                       else vmaxt=0;
                }
                //ShowMessage(vmax);
        }
/* определение предела*/

//numbers search

			for(int x = vpixe; x < Width; x++) {
                                for(int y = 0; y < Height; y++) {

                                        Color = GetRValue(BImage->Picture->Bitmap->Canvas->Pixels[x][y]);

                                        if (Color < sCl) vtmp++;
                  /*end cycleY*/}


                                if (min){
                                        if (vtmp<Height){ vpixb = x; min=false; }
                                }
                                //ShowMessage(vpixb);
                                else if (vtmp==Height) {
                                        vpixe = x;
                                        cid=true;
                                }
                                else  if (cid) break;

                                vtmp=0;



          /*end cycleX*/}


                        Form1->Color=clBtnFace;
                        //ShowMessage(vpixe);
                        if (vmax==0) vpixe=Width;
                        else
                        if (cid2){ vpixe=Width; cid2=false;}
                        else
                        if (((vpixe-1)==vmax)||((vpixe)==vmax)||((vpixe+1)==vmax)) cid2=true;

//horizontal
                        min=true;

			for(int x = vpixb; x < vpixe; x++) {
                                for(int y = 0; y < Height; y++) {
				        Color = GetRValue(BImage->Picture->Bitmap->Canvas->Pixels[x][y]);

					if (Color > sCl) {
						minht=x;
						if (min){minh=x; min=false;}
					        if (minh > minht) minh=minht;
				        }

				        if (Color > sCl) {
					        maxht=x;
					        if (maxh < maxht) maxh=maxht;
				        }

                                }
			}


//vertical
			min=true;

			for(int x = vpixb; x < vpixe; x++) {
                                for(int y = 0; y < Height; y++) {

				        Color = GetRValue(BImage->Picture->Bitmap->Canvas->Pixels[x][y]);

					if (Color > sCl) {
					        minvt=y;
						if (min){minv=y; min=false;}
					        if (minv > minvt) minv=minvt;
				       	}

				        if (Color > sCl) {
					        maxvt=y;
						if (maxv < maxvt) maxv=maxvt;
                                        }

                                }
			}

//выводим обрезанное изображение

//cler image2
        for(int x = 0; x < 400; x++) {
                for(int y = 0; y < 250; y++) {
                        AImage->Picture->Bitmap->Canvas->Pixels[x][y] = RGB(255, 255, 255);
                }
        }
//end_clear

         /*
           maxh - Width
           maxv - Height
         */
         for(int x = minh; x < maxh; x++) {
                for(int y = minv; y < maxv; y++) {

                        Color = GetRValue(BImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                        AImage->Picture->Bitmap->Canvas->Pixels[x-minh][y-minv] = RGB(Color, Color, Color);
                        
         //для вывода картинки с пикселя 1,1: Pixels[x-minh][y-minv]
                }
         }

        //передача ш. и в. выделенной картинки
         wglob = 0;
         hglob = 0;
         wglob = maxh-minh;
         hglob = maxv-minv;


//обнуление переменных
        if (vpixe==Width){
                vpixb=0, vpixe=0, vtmp=0, vmax=0, vmaxt=0;
        }

Form1->Color=clBtnFace;
}

//---------------------------------------------------------------------------
int filpix(TImage* AImage)
{
 int Height =  AImage->Picture->Bitmap->Height;
 int Width =  AImage->Picture->Bitmap->Width;
 byte Color;

 bool kobush=true;
 byte cmin, cmax, cmins, cmaxs, cmint, cmaxt, pmax;
 int i=2;

 byte *pix = new byte [Height*Width+6];
 byte *mediana = new byte [Height*Width+6];
 for (int n=0; n<Height*Width+6; n++){
        pix[n] = 0;
        mediana[n] = 0;
 }

 //считывание значение пикселей
 for(int x = 0; x < Height; x++) {
        for(int y = 0; y < Width; y++)
        {
                i++;
                if ((x==0)&&(y==0)){
                pix[0] = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                pix[1] = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                pix[2] = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                }

                pix[i]= GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);

                if ((x==Height-1)&&(y==Width-1)){
                pix[i+1]= GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                pix[i+2]= GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                pix[i+3]= GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
                }
        }
 }

 //фильтрация с помощью метода медиан (m=2)
 for(int j = 3; j < i+3; j++)
 {
        cmin = min( pix[j], min(pix[j-1], pix[j+1]) );
        cmax = max( pix[j], max(pix[j-1], pix[j+1]) );
        cmins = min( cmin, min(pix[j-2], pix[j+2]) );
        cmaxs = max( cmax, max(pix[j-2], pix[j+2]) );
        cmint = min( cmins, min(pix[j-3], pix[j+3]) );
        cmaxt = max( cmaxs, max(pix[j-3], pix[j+3]) );

        if ((cmin!=pix[j-3])&&(cmax!=pix[j-3])&&(cmins!=pix[j-3])&&(cmaxs!=pix[j-3])&&(cmint!=pix[j-3])&&(cmaxt!=pix[j-3]))
                mediana[j-3] = pix[j-3];
        else if ((cmin!=pix[j-2])&&(cmax!=pix[j-2])&&(cmins!=pix[j-2])&&(cmaxs!=pix[j-2])&&(cmint!=pix[j-2])&&(cmaxt!=pix[j-2]))
                mediana[j-3] = pix[j-2];
        else if ((cmin!=pix[j-1])&&(cmax!=pix[j-1])&&(cmins!=pix[j-1])&&(cmaxs!=pix[j-1])&&(cmint!=pix[j-1])&&(cmaxt!=pix[j-1]))
                mediana[j-3] = pix[j-1];
        else if ((cmin!=pix[j])&&(cmax!=pix[j])&&(cmins!=pix[j])&&(cmaxs!=pix[j])&&(cmint!=pix[j])&&(cmaxt!=pix[j]))
                mediana[j-3] = pix[j];
        else if ((cmin!=pix[j+1])&&(cmax!=pix[j+1])&&(cmins!=pix[j+1])&&(cmaxs!=pix[j+1])&&(cmint!=pix[j+1])&&(cmaxt!=pix[j+1]))
                mediana[j-3] = pix[j+1];
        else if ((cmin!=pix[j+2])&&(cmax!=pix[j+2])&&(cmins!=pix[j+2])&&(cmaxs!=pix[j+2])&&(cmint!=pix[j+2])&&(cmaxt!=pix[j+2]))
                mediana[j-3] = pix[j+2];
        else if ((cmin!=pix[j+3])&&(cmax!=pix[j+3])&&(cmins!=pix[j+3])&&(cmaxs!=pix[j+3])&&(cmint!=pix[j+3])&&(cmaxt!=pix[j+3]))
                mediana[j-3] = pix[j+3];
 }

 //max pix
 for(int j = 1; j < i; j++)
 {
        if (kobush){
                if (mediana[j]>mediana[j-1])
                       pmax = mediana[j];
                else pmax = mediana[j-1];
                kobush = false;
        }

        if (mediana[j]>pmax)
                pmax = mediana[j];
 }

 double pm;

 pm = pmax;
 pm = floor(pm/10);
 pm = pm*10;
 Form1->sCl = pm - 10;
 return pm;
 delete [] pix;
 delete [] mediana;
}
//---------------------------------------------------------------------------