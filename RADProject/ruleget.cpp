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
#include <stdlib.h>
#include <time.h>

#include <Clipbrd.hpp>
#include "Main.h"
#include "ruleget.h"
#include "Grad.h"
#include "Study.h"
#include "Imloc.h"
#include "Setting.h"
#pragma hdrstop
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

double fgauss(double u, double b, double c)
{
    return exp(-( ((u-b)*(u-b))/(2*c*c) ) );
}
//---------------------------------------------------------------------------

int gauss(double u, double c=8)
{
       double guxx, gux[5];
       int id;
      //  gux=exp(-( ((u-b)*(u-b))/(2*c*c) ) );
       gux[0]=fgauss(u, 0, c);
       gux[1]=fgauss(u, 25, 8);
       gux[2]=fgauss(u, 50, 8);
       gux[3]=fgauss(u, 75, 8);
       gux[4]=fgauss(u, 100, 8);

       guxx=max(gux[0], max(gux[1], max(gux[2], max(gux[3], gux[4]) ) ) );

       if (guxx==gux[0]) id=0;
       else
       if (guxx==gux[1]) id=1;
       else
       if (guxx==gux[2]) id=2;
       else
       if (guxx==gux[3]) id=3;
       else
       if (guxx==gux[4]) id=4;


       return id;
}
//---------------------------------------------------------------------------

double gaussFZ(double u)
{
       double guxx, gux[5];
       int id;
      //  gux=exp(-( ((u-b)*(u-b))/(2*c*c) ) );
       gux[0]=fgauss(u, 0, 8);
       gux[1]=fgauss(u, 25, 8);
       gux[2]=fgauss(u, 50, 8);
       gux[3]=fgauss(u, 75, 8);
       gux[4]=fgauss(u, 100, 8);

       guxx=max(gux[0], max(gux[1], max(gux[2], max(gux[3], gux[4]) ) ) );

       return guxx;
}
//---------------------------------------------------------------------------

void getrule(int rmas[1000][100])   //считывание базы правил из файла в массив программы
{
 FILE *inf = fopen("rules37.txt", "r");

 char f;
 int g, iw=0, jw=0;

  for (int i=0; i<999; i++){
  for (int j=0; j<99; j++){
		rmas[i][j]=0;
		}
  }
	 while (!feof(inf))
	 {
			  fscanf(inf, "%c", &f);
			  //ShowMessage(f);
			  if (f!=' '){
					if (f!='\n'){
							g=(int)f-'0';
							rmas[iw][jw]=g;
							//ShowMessage(rmas[iw][jw]);
							jw++;
					}
			  }
			  if (f == '\n') {iw++; jw=0;}
	 }
 //}
 fclose(inf);
/*end void*/}
//---------------------------------------------------------------------------

void getid(int rmas[1000][100], int imas[1000], int tmas[50][50]) //определение цифры путем сравнивания двух массивов
{
  int k=0;
  bool kobysh=true;

 	for (int i=0; i<100; i++){
                for(int j=0; j<25; j++)
                        {

                        if (imas[j]==rmas[i][j]){
                                tmas[k][0]=i;
                                tmas[k][1]++;
                                }

          /*end cycle2*/}


	if (kobysh) k++;
	if (k==2){
	        tmas[2][1]=max(tmas[0][1], tmas[1][1]);

	        if (tmas[2][1]==tmas[0][1]) tmas[2][0]=tmas[0][0];
	        else tmas[2][0]=tmas[1][0];

	        k=0;
	        tmas[0][1]=0;
	        tmas[1][1]=0;
	        kobysh=false;
	}
	/*---------*/
	if (!kobysh){
                if (tmas[2][1]<tmas[0][1]){
                        tmas[2][1]=tmas[0][1];
                        tmas[2][0]=tmas[0][0];
                }
	        tmas[0][1]=0;
	}


	/*end cycle1*/}
 //ShowMessage(tmas[2][0]);
 //ShowMessage(tmas[2][1]);
}
//---------------------------------------------------------------------------

void getnum(int imas[1000], int wglob, int hglob, int sCl=180)
{
  byte Color;
  float w, wt, h, ht, t1=0, t2=0;  //ш. и в.
  float s, st, stw, sth;         //площадь
  float ccol=0;        //кол-во "белых" пикселей
  float temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
  float pc=0, pc1=0, pc2=0, pc3=0, pc4=0, pc5=0;            //процент "белых" пикселей

  bool check1=true, check2=false, check3=false, check4=false, check5=false;
  int check=0;

	//разделение изобр. на целые части
	w = wglob/5;
	w = (int)w;
	h = hglob/5;
	h = (int)h;

	//остаток
	wt = wglob-(w*5);
	ht = hglob-(h*5);
	
	//окончательная ш. и в.
	if (wt<5){
		t1 = 5-wt;
		w = (wglob+t1)/5;
	}
	else{
		wt=w;
	}
	
	if (ht<5){
		t2 = 5-ht;
		h = (hglob+t2)/5;
	}
	else{
		ht=h;
	}
	//площадь (всего пикселей в сегменте)
	s = w*h;
	st = wt*ht;
	stw = wt*h;
	sth = w*ht;
	/*END=======DATA======GEN*/



    /*=================================*/
  for(int y = 0; y < hglob; y++) {
   for(int x = 0; x < wglob; x++) {

    Color = GetRValue(Form1->Image2->Picture->Bitmap->Canvas->Pixels[x][y]);
    if (Color > sCl) ccol=ccol+1;

                if (y<h){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check1){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;

                                                 /* ShowMessage(temp5);
                                                  ShowMessage(pc5);     */

						if  (pc1<20)             imas[0]=0;   else
						if ((pc1>=20)&&(pc1<40)) imas[0]=1;   else
						if ((pc1>=40)&&(pc1<60)) imas[0]=2;   else
						if ((pc1>=60)&&(pc1<80)) imas[0]=3;   else
						if  (pc1>80)             imas[0]=4;   
                                                              
						if  (pc2<20)             imas[1]=0;   else
						if ((pc2>=20)&&(pc2<40)) imas[1]=1;   else
						if ((pc2>=40)&&(pc2<60)) imas[1]=2;   else
						if ((pc2>=60)&&(pc2<80)) imas[1]=3;   else
						if  (pc2>80)             imas[1]=4;   
                                                              
						if  (pc3<20)             imas[2]=0;   else
						if ((pc3>=20)&&(pc3<40)) imas[2]=1;   else
						if ((pc3>=40)&&(pc3<60)) imas[2]=2;   else
						if ((pc3>=60)&&(pc3<80)) imas[2]=3;   else
						if  (pc3>80)             imas[2]=4;   
                                                              
						if  (pc4<20)             imas[3]=0;   else
						if ((pc4>=20)&&(pc4<40)) imas[3]=1;   else
						if ((pc4>=40)&&(pc4<60)) imas[3]=2;   else
						if ((pc4>=60)&&(pc4<80)) imas[3]=3;   else
						if  (pc4>80)             imas[3]=4;   
                                                              
						if  (pc5<20)              imas[4]=0;  else
						if ((pc5>=20)&&(pc5<40))  imas[4]=1;  else
						if ((pc5>=40)&&(pc5<60))  imas[4]=2;  else
						if ((pc5>=60)&&(pc5<80))  imas[4]=3;  else
						if  (pc5>80)              imas[4]=4;

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check1=false;
                                                check2=true;
                                        }
				}

               if ((y>=h)&&(y<h*2)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {

                                        if (check2){



						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						if  (pc1<20)             imas[5]=0;      else
						if ((pc1>=20)&&(pc1<40)) imas[5]=1;      else
						if ((pc1>=40)&&(pc1<60)) imas[5]=2;      else
						if ((pc1>=60)&&(pc1<80)) imas[5]=3;      else
						if  (pc1>80)             imas[5]=4;      
                                                                 
						if  (pc2<20)             imas[6]=0;      else
						if ((pc2>=20)&&(pc2<40)) imas[6]=1;      else
						if ((pc2>=40)&&(pc2<60)) imas[6]=2;      else
						if ((pc2>=60)&&(pc2<80)) imas[6]=3;      else
						if  (pc2>80)             imas[6]=4;      
                                                                 
						if  (pc3<20)             imas[7]=0;      else
						if ((pc3>=20)&&(pc3<40)) imas[7]=1;      else
						if ((pc3>=40)&&(pc3<60)) imas[7]=2;      else
						if ((pc3>=60)&&(pc3<80)) imas[7]=3;      else
						if  (pc3>80)             imas[7]=4;      
                                                                 
						if  (pc4<20)             imas[8]=0;      else
						if ((pc4>=20)&&(pc4<40)) imas[8]=1;      else
						if ((pc4>=40)&&(pc4<60)) imas[8]=2;      else
						if ((pc4>=60)&&(pc4<80)) imas[8]=3;      else
						if  (pc4>80)             imas[8]=4;      
                                                                 
						if  (pc5<20)              imas[9]=0;     else
						if ((pc5>=20)&&(pc5<40))  imas[9]=1;     else
						if ((pc5>=40)&&(pc5<60))  imas[9]=2;     else
						if ((pc5>=60)&&(pc5<80))  imas[9]=3;     else
						if  (pc5>80)              imas[9]=4;

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check2=false;
                                                check3=true;
                                        }
				}

               if ((y>=h*2)&&(y<h*3)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check3){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						if  (pc1<20)             imas[10]=0;   else
						if ((pc1>=20)&&(pc1<40)) imas[10]=1;   else
						if ((pc1>=40)&&(pc1<60)) imas[10]=2;   else
						if ((pc1>=60)&&(pc1<80)) imas[10]=3;   else
						if  (pc1>80)             imas[10]=4;   
                                                               
						if  (pc2<20)             imas[11]=0;   else
						if ((pc2>=20)&&(pc2<40)) imas[11]=1;   else
						if ((pc2>=40)&&(pc2<60)) imas[11]=2;   else
						if ((pc2>=60)&&(pc2<80)) imas[11]=3;   else
						if  (pc2>80)             imas[11]=4;   
                                                               
						if  (pc3<20)             imas[12]=0;   else
						if ((pc3>=20)&&(pc3<40)) imas[12]=1;   else
						if ((pc3>=40)&&(pc3<60)) imas[12]=2;   else
						if ((pc3>=60)&&(pc3<80)) imas[12]=3;   else
						if  (pc3>80)             imas[12]=4;   
                                                               
						if  (pc4<20)             imas[13]=0;   else
						if ((pc4>=20)&&(pc4<40)) imas[13]=1;   else
						if ((pc4>=40)&&(pc4<60)) imas[13]=2;   else
						if ((pc4>=60)&&(pc4<80)) imas[13]=3;   else
						if  (pc4>80)             imas[13]=4;   
                                                               
						if  (pc5<20)              imas[14]=0;  else
						if ((pc5>=20)&&(pc5<40))  imas[14]=1;  else
						if ((pc5>=40)&&(pc5<60))  imas[14]=2;  else
						if ((pc5>=60)&&(pc5<80))  imas[14]=3;  else
						if  (pc5>80)              imas[14]=4;

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check3=false;
                                                check4=true;
                                        }
				}

               if ((y>=h*3)&&(y<h*4)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check4){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						if  (pc1<20)             imas[15]=0;   else
						if ((pc1>=20)&&(pc1<40)) imas[15]=1;   else
						if ((pc1>=40)&&(pc1<60)) imas[15]=2;   else
						if ((pc1>=60)&&(pc1<80)) imas[15]=3;   else
						if  (pc1>80)             imas[15]=4;   
                                                               
						if  (pc2<20)             imas[16]=0;   else
						if ((pc2>=20)&&(pc2<40)) imas[16]=1;   else
						if ((pc2>=40)&&(pc2<60)) imas[16]=2;   else
						if ((pc2>=60)&&(pc2<80)) imas[16]=3;   else
						if  (pc2>80)             imas[16]=4;   
                                                               
						if  (pc3<20)             imas[17]=0;   else
						if ((pc3>=20)&&(pc3<40)) imas[17]=1;   else
						if ((pc3>=40)&&(pc3<60)) imas[17]=2;   else
						if ((pc3>=60)&&(pc3<80)) imas[17]=3;   else
						if  (pc3>80)             imas[17]=4;   
                                                               
						if  (pc4<20)             imas[18]=0;   else
						if ((pc4>=20)&&(pc4<40)) imas[18]=1;   else
						if ((pc4>=40)&&(pc4<60)) imas[18]=2;   else
						if ((pc4>=60)&&(pc4<80)) imas[18]=3;   else
						if  (pc4>80)             imas[18]=4;   
                                                               
						if  (pc5<20)              imas[19]=0;  else
						if ((pc5>=20)&&(pc5<40))  imas[19]=1;  else
						if ((pc5>=40)&&(pc5<60))  imas[19]=2;  else
						if ((pc5>=60)&&(pc5<80))  imas[19]=3;  else
						if  (pc5>80)              imas[19]=4;

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check4=false;
                                                check5=true;
                                        }
				}

               if ((y>=h*4)&&(y<(hglob-1))){

                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {          if (check5){
						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						if  (pc1<20)             imas[20]=0;    else
						if ((pc1>=20)&&(pc1<40)) imas[20]=1;    else
						if ((pc1>=40)&&(pc1<60)) imas[20]=2;    else
						if ((pc1>=60)&&(pc1<80)) imas[20]=3;    else
						if  (pc1>80)             imas[20]=4;    
                                                                
						if  (pc2<20)             imas[21]=0;    else
						if ((pc2>=20)&&(pc2<40)) imas[21]=1;    else
						if ((pc2>=40)&&(pc2<60)) imas[21]=2;    else
						if ((pc2>=60)&&(pc2<80)) imas[21]=3;    else
						if  (pc2>80)             imas[21]=4;    
                                                                
						if  (pc3<20)             imas[22]=0;    else
						if ((pc3>=20)&&(pc3<40)) imas[22]=1;    else
						if ((pc3>=40)&&(pc3<60)) imas[22]=2;    else
						if ((pc3>=60)&&(pc3<80)) imas[22]=3;    else
						if  (pc3>80)             imas[22]=4;    
                                                                
						if  (pc4<20)             imas[23]=0;    else
						if ((pc4>=20)&&(pc4<40)) imas[23]=1;    else
						if ((pc4>=40)&&(pc4<60)) imas[23]=2;    else
						if ((pc4>=60)&&(pc4<80)) imas[23]=3;    else
						if  (pc4>80)             imas[23]=4;    
                                                                
						if  (pc5<20)              imas[24]=0;   else
						if ((pc5>=20)&&(pc5<40))  imas[24]=1;   else
						if ((pc5>=40)&&(pc5<60))  imas[24]=2;   else
						if ((pc5>=60)&&(pc5<80))  imas[24]=3;   else
						if  (pc5>80)              imas[24]=4;

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check5=false;
                                        }
				}


     }
    }


 check1=true;
 check2=false;
 check3=false;
 check4=false;
 check5=false;


}
//---------------------------------------------------------------------------

void getnumgauss(TImage* AImage, int imas[1000], int wglob, int hglob, int sCl=180, double c=8)
{
  byte Color;
  double w, wt, h, ht, t1=0, t2=0;  //ш. и в.
  double s, st, stw, sth;         //площадь
  double ccol=0;        //кол-во "белых" пикселей
  double temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
  double pc=0, pc1=0, pc2=0, pc3=0, pc4=0, pc5=0;            //процент "белых" пикселей

  bool check1=true, check2=false, check3=false, check4=false, check5=false;
  int check=0;

	//разделение изобр. на целые части
	w = wglob/5;
	w = (int)w;
	h = hglob/5;
	h = (int)h;

	//остаток
	wt = wglob-(w*5);
	ht = hglob-(h*5);

	//окончательная ш. и в.
	if (wt<5){
		t1 = 5-wt;
		w = (wglob+t1)/5;
	}
	else{
		wt=w;
	}

	if (ht<5){
		t2 = 5-ht;
		h = (hglob+t2)/5;
	}
	else{
		ht=h;
	}
	//площадь (всего пикселей в сегменте)
	s = w*h;
	st = wt*ht;
	stw = wt*h;
	sth = w*ht;
	/*END=======DATA======GEN*/



    /*=================================*/
  for(int y = 0; y < hglob; y++) {
   for(int x = 0; x < wglob; x++) {

    Color = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
    if (Color > sCl) ccol=ccol+1;

                if (y<h){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check1){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;

                                                 /* ShowMessage(temp5);
                                                  ShowMessage(pc5);     */

						imas[0]=gauss(pc1, c);
                                                imas[1]=gauss(pc2);
                                                imas[2]=gauss(pc3);
                                                imas[3]=gauss(pc4);
                                                imas[4]=gauss(pc5);


						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check1=false;
                                                check2=true;
                                        }
				}

               if ((y>=h)&&(y<h*2)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {

                                        if (check2){



						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						imas[5]=gauss(pc1);
                                                imas[6]=gauss(pc2);
                                                imas[7]=gauss(pc3);
                                                imas[8]=gauss(pc4);
                                                imas[9]=gauss(pc5);

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check2=false;
                                                check3=true;
                                        }
				}

               if ((y>=h*2)&&(y<h*3)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check3){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						imas[10]=gauss(pc1);
                                                imas[11]=gauss(pc2);
                                                imas[12]=gauss(pc3);
                                                imas[13]=gauss(pc4);
                                                imas[14]=gauss(pc5);

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check3=false;
                                                check4=true;
                                        }
				}

               if ((y>=h*3)&&(y<h*4)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check4){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						imas[15]=gauss(pc1);
                                                imas[16]=gauss(pc2);
                                                imas[17]=gauss(pc3);
                                                imas[18]=gauss(pc4);
                                                imas[19]=gauss(pc5);

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check4=false;
                                                check5=true;
                                        }
				}

               if ((y>=h*4)&&(y<(hglob-1))){

                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {          if (check5){
						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						imas[20]=gauss(pc1);
                                                imas[21]=gauss(pc2);
                                                imas[22]=gauss(pc3);
                                                imas[23]=gauss(pc4);
                                                imas[24]=gauss(pc5);

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check5=false;
                                        }
				}


     }
    }


 check1=true;
 check2=false;
 check3=false;
 check4=false;
 check5=false;


}
//---------------------------------------------------------------------------

void fpgauss(int wglob, int hglob)
{

  FILE *out1 = fopen("rules.kb", "a+");
  /* РАБОТАЕТ, НО ЧЕРЕЗ!!! */
  byte Color;
  double w, wt, h, ht, t1=0, t2=0;  //ш. и в.
  double s, st, stw, sth;         //площадь
  double ccol=0;        //кол-во "белых" пикселей
  double temp1=0, temp2=0, temp3=0, temp4=0, temp5=0;
  double pc=0, pc1=0, pc2=0, pc3=0, pc4=0, pc5=0;            //процент "белых" пикселей

  bool check1=true, check2=false, check3=false, check4=false, check5=false;
  int check=0;

  //разделение изобр. на целые части
  w = wglob/5;
  w = (int)w;
  h = hglob/5;
  h = (int)h;


  //остаток
  wt = wglob-(w*5);
  ht = hglob-(h*5);

  //окончательная ш. и в.
  if (wt<5){
  t1 = 5-wt;
  w = (wglob+t1)/5;
  }
  else{
   wt=w;
  }

  if (ht<5){
  t2 = 5-ht;
  h = (hglob+t2)/5;
  }
  else{
   ht=h;
  }

  //площадь (всего пикселей в сегменте)
  s = w*h;
  st = wt*ht;
  stw = wt*h;
  sth = w*ht;

  //генерация правил
  /*
    0 - пустой               x<20%
    1 - почти пустой         20%<=x<40%
    2 - наполовину заполнен  40%<=x<60%
    3 - почти заполнен       60%<=x<80%
    4 - заполнен             80%<=x
  */

  //Гаусс: u(x)=exp(-(((u-b)^2)/(2*c^2)))

  for(int y = 0; y < hglob; y++) {
   for(int x = 0; x < wglob; x++) {

    Color = GetRValue(Form1->Image2->Picture->Bitmap->Canvas->Pixels[x][y]);
    if (Color > 180) ccol=ccol+1;

                if (y<h){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check1){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;

                                                 /* ShowMessage(temp5);
                                                  ShowMessage(pc5);     */

						fprintf(out1, "%d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));
                                                fprintf(out1, " %d", gauss(pc4));
                                                fprintf(out1, " %d", gauss(pc5));


						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check1=false;
                                                check2=true;
                                        }
				}

               if ((y>=h)&&(y<h*2)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {

                                        if (check2){



						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


                                                fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));
                                                fprintf(out1, " %d", gauss(pc4));
                                                fprintf(out1, " %d", gauss(pc5));

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check2=false;
                                                check3=true;
                                        }
				}

               if ((y>=h*2)&&(y<h*3)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check3){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;

                                                fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));
                                                fprintf(out1, " %d", gauss(pc4));
                                                fprintf(out1, " %d", gauss(pc5));

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check3=false;
                                                check4=true;
                                        }
				}

               if ((y>=h*3)&&(y<h*4)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {
                                        if (check4){

						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));
                                                fprintf(out1, " %d", gauss(pc4));
                                                fprintf(out1, " %d", gauss(pc5));

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check4=false;
                                                check5=true;
                                        }
				}

               if ((y>=h*4)&&(y<(hglob-1))){

                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==w*3) {temp3=temp3+ccol; ccol=0;}
                        else
                        if (x==w*4) {temp4=temp4+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp5=temp5+ccol; ccol=0;}
                }
				else {          if (check5){
						pc1=(temp1/s)*100;
						pc2=(temp2/s)*100;
						pc3=(temp3/s)*100;
						pc4=(temp4/s)*100;
						pc5=(temp5/s)*100;


						fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));
                                                fprintf(out1, " %d", gauss(pc4));
                                                fprintf(out1, " %d", gauss(pc5));

                                                fprintf(out1, "\r\n");

						temp1=0;
						temp2=0;
						temp3=0;
						temp4=0;
						temp5=0;

						pc1=0;
						pc2=0;
						pc3=0;
						pc4=0;
						pc5=0;

						check5=false;
                                        }
				}


     }
    }


 check1=true;
 check2=false;
 check3=false;
 check4=false;
 check5=false;

 fclose(out1);


}
//---------------------------------------------------------------------------

void printid(TEdit* AEdit, int tmas[50][50])
{
  int id=0;

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

  AEdit->Text = AEdit->Text +""+ IntToStr(id);
}
//---------------------------------------------------------------------------





void getnumgauss37(TImage* AImage, int imas[1000], double ifmas[1000][10], int wglob, int hglob, int sCl=180, double c=8)
{
  byte Color;
  double w, wt, h, ht, t1=0, t2=0;  //ш. и в.
  double s, st, stw, sth;         //площадь
  double ccol=0;        //кол-во "белых" пикселей
  double temp1=0, temp2=0, temp3=0;
  double pc=0, pc1=0, pc2=0, pc3=0;            //процент "белых" пикселей

  bool check1=true, check2=false, check3=false, check4=false, check5=false, check6=false, check7=false;
  int check=0;

	//разделение изобр. на целые части
	w = wglob/3;
	w = (int)w;
	h = hglob/7;
	h = (int)h;

	//остаток
	wt = wglob-(w*3);
	ht = hglob-(h*7);

	//окончательная ш. и в.
	if (wt<3){
		t1 = 3-wt;
		w = (wglob+t1)/3;
	}
	else{
		wt=w;
	}

	if (ht<7){
		t2 = 7-ht;
		h = (hglob+t2)/7;
	}
	else{
		ht=h;
	}
	//площадь (всего пикселей в сегменте)
	s = w*h;
	st = wt*ht;
	stw = wt*h;
	sth = w*ht;
	/*END=======DATA======GEN*/



    /*=================================*/
  for(int y = 0; y < hglob; y++) {
   for(int x = 0; x < wglob; x++) {

    Color = GetRValue(AImage->Picture->Bitmap->Canvas->Pixels[x][y]);
    if (Color > sCl) ccol=ccol+1;

                if (y<h){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check1){

                                        pc1=(temp1/s)*100;
                                        pc2=(temp2/s)*100;
                                        pc3=(temp3/s)*100;
						
                                        imas[0]=gauss(pc1, c);
                                        imas[1]=gauss(pc2);
                                        imas[2]=gauss(pc3);

                                        ifmas[0][0]=fgauss(pc1, 0, 8);
										ifmas[0][1]=fgauss(pc1, 25, 8);
										ifmas[0][2]=fgauss(pc1, 50, 8);
										ifmas[0][3]=fgauss(pc1, 75, 8);
										ifmas[0][4]=fgauss(pc1, 100, 8);
										ifmas[1][0]=fgauss(pc2, 0, 8);
										ifmas[1][1]=fgauss(pc2, 25, 8);
										ifmas[1][2]=fgauss(pc2, 50, 8);
										ifmas[1][3]=fgauss(pc2, 75, 8);
										ifmas[1][4]=fgauss(pc2, 100, 8);
										ifmas[2][0]=fgauss(pc3, 0, 8);
										ifmas[2][1]=fgauss(pc3, 25, 8);
										ifmas[2][2]=fgauss(pc3, 50, 8);
										ifmas[2][3]=fgauss(pc3, 75, 8);
										ifmas[2][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;

												pc1=0;
												pc2=0;
												pc3=0;

												check1=false;
                                                check2=true;
                                        }
				}

// 2
               if ((y>=h)&&(y<h*2)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {

                                        if (check2){
												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;						
						
												imas[3]=gauss(pc1);
                                                imas[4]=gauss(pc2);
                                                imas[5]=gauss(pc3);
												
												ifmas[3][0]=fgauss(pc1, 0, 8);
												ifmas[3][1]=fgauss(pc1, 25, 8);
												ifmas[3][2]=fgauss(pc1, 50, 8);
												ifmas[3][3]=fgauss(pc1, 75, 8);
												ifmas[3][4]=fgauss(pc1, 100, 8);
												ifmas[4][0]=fgauss(pc2, 0, 8);
												ifmas[4][1]=fgauss(pc2, 25, 8);
												ifmas[4][2]=fgauss(pc2, 50, 8);
												ifmas[4][3]=fgauss(pc2, 75, 8);
												ifmas[4][4]=fgauss(pc2, 100, 8);
												ifmas[5][0]=fgauss(pc3, 0, 8);
												ifmas[5][1]=fgauss(pc3, 25, 8);
												ifmas[5][2]=fgauss(pc3, 50, 8);
												ifmas[5][3]=fgauss(pc3, 75, 8);
												ifmas[5][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check2=false;
                                                check3=true;
                                        }
				}
// 3
               if ((y>=h*2)&&(y<h*3)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                if (check3){

										pc1=(temp1/s)*100;
										pc2=(temp2/s)*100;
										pc3=(temp3/s)*100;
										
										imas[6]=gauss(pc1);
                                        imas[7]=gauss(pc2);
                                        imas[8]=gauss(pc3);
												
										ifmas[6][0]=fgauss(pc1, 0, 8);
										ifmas[6][1]=fgauss(pc1, 25, 8);
										ifmas[6][2]=fgauss(pc1, 50, 8);
										ifmas[6][3]=fgauss(pc1, 75, 8);
										ifmas[6][4]=fgauss(pc1, 100, 8);
										ifmas[7][0]=fgauss(pc2, 0, 8);
										ifmas[7][1]=fgauss(pc2, 25, 8);
										ifmas[7][2]=fgauss(pc2, 50, 8);
										ifmas[7][3]=fgauss(pc2, 75, 8);
										ifmas[7][4]=fgauss(pc2, 100, 8);
										ifmas[8][0]=fgauss(pc3, 0, 8);
										ifmas[8][1]=fgauss(pc3, 25, 8);
										ifmas[8][2]=fgauss(pc3, 50, 8);
										ifmas[8][3]=fgauss(pc3, 75, 8);
										ifmas[8][4]=fgauss(pc3, 100, 8);

										temp1=0;
										temp2=0;
										temp3=0;
						
										pc1=0;
										pc2=0;
										pc3=0;
						
										check3=false;
                                        check4=true;
                                }
				}
// 4
               if ((y>=h*3)&&(y<h*4)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
									if (check4){

										pc1=(temp1/s)*100;
										pc2=(temp2/s)*100;
										pc3=(temp3/s)*100;
						                
										imas[9]=gauss(pc1);
                                        imas[10]=gauss(pc2);
                                        imas[11]=gauss(pc3);
												
										ifmas[9][0]=fgauss(pc1, 0, 8);
										ifmas[9][1]=fgauss(pc1, 25, 8);
										ifmas[9][2]=fgauss(pc1, 50, 8);
										ifmas[9][3]=fgauss(pc1, 75, 8);
										ifmas[9][4]=fgauss(pc1, 100, 8);
										ifmas[10][0]=fgauss(pc2, 0, 8);
										ifmas[10][1]=fgauss(pc2, 25, 8);
										ifmas[10][2]=fgauss(pc2, 50, 8);
										ifmas[10][3]=fgauss(pc2, 75, 8);
										ifmas[10][4]=fgauss(pc2, 100, 8);
										ifmas[11][0]=fgauss(pc3, 0, 8);
										ifmas[11][1]=fgauss(pc3, 25, 8);
										ifmas[11][2]=fgauss(pc3, 50, 8);
										ifmas[11][3]=fgauss(pc3, 75, 8);
										ifmas[11][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check4=false;
                                                check5=true;
                                    }
				}
// 5				
               if ((y>=h*4)&&(y<h*5)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check5){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;
						
												imas[12]=gauss(pc1);
                                                imas[13]=gauss(pc2);
                                                imas[14]=gauss(pc3);
												
										ifmas[12][0]=fgauss(pc1, 0, 8);
										ifmas[12][1]=fgauss(pc1, 25, 8);
										ifmas[12][2]=fgauss(pc1, 50, 8);
										ifmas[12][3]=fgauss(pc1, 75, 8);
										ifmas[12][4]=fgauss(pc1, 100, 8);
										ifmas[13][0]=fgauss(pc2, 0, 8);
										ifmas[13][1]=fgauss(pc2, 25, 8);
										ifmas[13][2]=fgauss(pc2, 50, 8);
										ifmas[13][3]=fgauss(pc2, 75, 8);
										ifmas[13][4]=fgauss(pc2, 100, 8);
										ifmas[14][0]=fgauss(pc3, 0, 8);
										ifmas[14][1]=fgauss(pc3, 25, 8);
										ifmas[14][2]=fgauss(pc3, 50, 8);
										ifmas[14][3]=fgauss(pc3, 75, 8);
										ifmas[14][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check5=false;
                                                check6=true;
                                        }
				}				
// 6
               if ((y>=h*5)&&(y<h*6)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check6){

                                        pc1=(temp1/s)*100;
                                        pc2=(temp2/s)*100;
                                        pc3=(temp3/s)*100;
						
                                        imas[15]=gauss(pc1);
                                        imas[16]=gauss(pc2);
                                        imas[17]=gauss(pc3);
												
                                        ifmas[15][0]=fgauss(pc1, 0, 8);
										ifmas[15][1]=fgauss(pc1, 25, 8);
										ifmas[15][2]=fgauss(pc1, 50, 8);
										ifmas[15][3]=fgauss(pc1, 75, 8);
										ifmas[15][4]=fgauss(pc1, 100, 8);
										ifmas[16][0]=fgauss(pc2, 0, 8);
										ifmas[16][1]=fgauss(pc2, 25, 8);
										ifmas[16][2]=fgauss(pc2, 50, 8);
										ifmas[16][3]=fgauss(pc2, 75, 8);
										ifmas[16][4]=fgauss(pc2, 100, 8);
										ifmas[17][0]=fgauss(pc3, 0, 8);
										ifmas[17][1]=fgauss(pc3, 25, 8);
										ifmas[17][2]=fgauss(pc3, 50, 8);
										ifmas[17][3]=fgauss(pc3, 75, 8);
										ifmas[17][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check6=false;
                                                check7=true;
                                        }
				}
				
// 7
               if ((y>=h*6)&&(y<(hglob-1))){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {          		if (check7){
												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;
						
												imas[18]=gauss(pc1);
                                                imas[19]=gauss(pc2);
                                                imas[20]=gauss(pc3);
												
										ifmas[18][0]=fgauss(pc1, 0, 8);
										ifmas[18][1]=fgauss(pc1, 25, 8);
										ifmas[18][2]=fgauss(pc1, 50, 8);
										ifmas[18][3]=fgauss(pc1, 75, 8);
										ifmas[18][4]=fgauss(pc1, 100, 8);
										ifmas[19][0]=fgauss(pc2, 0, 8);
										ifmas[19][1]=fgauss(pc2, 25, 8);
										ifmas[19][2]=fgauss(pc2, 50, 8);
										ifmas[19][3]=fgauss(pc2, 75, 8);
										ifmas[19][4]=fgauss(pc2, 100, 8);
										ifmas[20][0]=fgauss(pc3, 0, 8);
										ifmas[20][1]=fgauss(pc3, 25, 8);
										ifmas[20][2]=fgauss(pc3, 50, 8);
										ifmas[20][3]=fgauss(pc3, 75, 8);
										ifmas[20][4]=fgauss(pc3, 100, 8);

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check7=false;
                                        }
				}


     }
    }


 check1=true;
 check2=false;
 check3=false;
 check4=false;
 check5=false;
 check6=false;
 check7=false;


}
//---------------------------------------------------------------------------

void fpgauss37(int wglob, int hglob)
{
  FILE *out1 = fopen("rules37.kb", "a+");
  /* РАБОТАЕТ, НО ЧЕРЕЗ!!! */
  byte Color;
  double w, wt, h, ht, t1=0, t2=0;  //ш. и в.
  double s, st, stw, sth;         //площадь
  double ccol=0;        //кол-во "белых" пикселей
  double temp1=0, temp2=0, temp3=0;
  double pc=0, pc1=0, pc2=0, pc3=0;            //процент "белых" пикселей

  bool check1=true, check2=false, check3=false, check4=false, check5=false, check6=false, check7=false;
  int check=0;

  //разделение изобр. на целые части
  w = wglob/3;
  w = (int)w;
  h = hglob/7;
  h = (int)h;


  //остаток
  wt = wglob-(w*3);
  ht = hglob-(h*7);

  //окончательная ш. и в.
  if (wt<3){
  t1 = 3-wt;
  w = (wglob+t1)/3;
  }
  else{
   wt=w;
  }

  if (ht<7){
  t2 = 7-ht;
  h = (hglob+t2)/7;
  }
  else{
   ht=h;
  }

  //площадь (всего пикселей в сегменте)
  s = w*h;
  st = wt*ht;
  stw = wt*h;
  sth = w*ht;

  //генерация правил
  /*
    0 - пустой               x<20%
    1 - почти пустой         20%<=x<40%
    2 - наполовину заполнен  40%<=x<60%
    3 - почти заполнен       60%<=x<80%
    4 - заполнен             80%<=x
  */
  //Гаусс: u(x)=exp(-(((u-b)^2)/(2*c^2)))

  for(int y = 0; y < hglob; y++) {
   for(int x = 0; x < wglob; x++) {

    Color = GetRValue(Form1->Image2->Picture->Bitmap->Canvas->Pixels[x][y]);
    if (Color > 180) ccol=ccol+1;

                if (y<h){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check1){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;

												fprintf(out1, "%d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check1=false;
                                                check2=true;
                                        }
				}

				
// 2
               if ((y>=h)&&(y<h*2)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {

                                        if (check2){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;

                                                fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check2=false;
                                                check3=true;
                                        }
				}

				
// 3
               if ((y>=h*2)&&(y<h*3)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check3){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;

                                                fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check3=false;
                                                check4=true;
                                        }
				}

// 4
               if ((y>=h*3)&&(y<h*4)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check4){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;
						
												fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check4=false;
                                                check5=true;
                                        }
				}
				
// 5				
				if ((y>=h*4)&&(y<h*5)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check5){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;
						
						
												fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check5=false;
                                                check6=true;
                                        }
				}

				
// 6				
				if ((y>=h*5)&&(y<h*6)){
                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {
                                        if (check6){

												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;
						
						
												fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;
						
												check6=false;
                                                check7=true;
                                        }
				}
				
// 7
               if ((y>=h*6)&&(y<(hglob-1))){

                        if (x==w)   {temp1=temp1+ccol; ccol=0;}
                        else
                        if (x==w*2) {temp2=temp2+ccol; ccol=0;}
                        else
                        if (x==wglob-1) {temp3=temp3+ccol; ccol=0;}
                }
				else {         
											if (check7){
												pc1=(temp1/s)*100;
												pc2=(temp2/s)*100;
												pc3=(temp3/s)*100;						
						
												fprintf(out1, " %d", gauss(pc1));
                                                fprintf(out1, " %d", gauss(pc2));
                                                fprintf(out1, " %d", gauss(pc3));

                                                fprintf(out1, "\r\n");

												temp1=0;
												temp2=0;
												temp3=0;
						
												pc1=0;
												pc2=0;
												pc3=0;

												check7=false;
											}
				}

//end cycles
     }
    }


 check1=true;
 check2=false;
 check3=false;
 check4=false;
 check5=false;
 check6=false;
 check7=false;

 fclose(out1);
}
//---------------------------------------------------------------------------

void getidT(int rmas[1000][100], int imas[1000], int tmas[50][50]) //определение цифры путем сравнивания двух массивов
{
  int k=0;
  bool kobysh=true;

 	for (int i=0; i<100; i++){
			for(int j=0; j<21; j++){

					if (imas[j]==rmas[i][j]){
					tmas[k][0]=i;
					tmas[k][1]++;
					}

			/*end cycle2*/}


	if (kobysh) k++;
	if (k==2){
	tmas[2][1]=max(tmas[0][1], tmas[1][1]);

	if (tmas[2][1]==tmas[0][1]) tmas[2][0]=tmas[0][0];
	else tmas[2][0]=tmas[1][0];

	k=0;
	tmas[0][1]=0;
	tmas[1][1]=0;
	kobysh=false;
	}
	/*---------*/
	if (!kobysh){
			if (tmas[2][1]<tmas[0][1]){
			tmas[2][1]=tmas[0][1];
			tmas[2][0]=tmas[0][0];
			}
	tmas[0][1]=0;
	}


	/*end cycle1*/}
 //ShowMessage(tmas[2][0]);
 //ShowMessage(tmas[2][1]);
}
//---------------------------------------------------------------------------

int getidF(int rmas[1000][100], int imas[1000], double ifmas[1000][10]) //(F-fuzzy) определение цифры путем сравнивания двух массивов
{
  double k=0, rfmas[500];
  for (int i=0; i<500; i++){
        rfmas[i]=1;
  }
  int id=0;

   	for (int i=0; i<100; i++){
		for(int j=0; j<21; j++){

                        if (rfmas[i]>ifmas[j][rmas[i][j]]) rfmas[i]=ifmas[j][rmas[i][j]];
                        
                /*end cycle2*/}
        /*end cycle1*/}

        k=rfmas[0];
        for (int i=0; i<100; i++)
        {
                if (k<rfmas[i]) {
                        k=rfmas[i];
                        id=i;
                }
        }
  return id;
}
//---------------------------------------------------------------------------

void printidF(TEdit* AEdit, int idp)
{
  int id;

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

  AEdit->Text = AEdit->Text +""+ IntToStr(id);
}
//---------------------------------------------------------------------------

void SetMemo(TEdit* AEdit, TMemo* AMemo)
{
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);

  AMemo->Lines->Add(AEdit->Text +" : "+ asctime(timeinfo));
}
//---------------------------------------------------------------------------


