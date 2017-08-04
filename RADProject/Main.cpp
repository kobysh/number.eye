//---------------------------------------------------------------------------

#include <vcl.h>
#include <vfw.h>
#include <fstream.h>
#include <conio.h>
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip.h>
#include <sysmac.h>
#include <windows.h>
#include <winnt.h>
#include <cmath>
#include <cstdlib>
#pragma hdrstop

#include "Main.h"
#include "Camera.h"
#include "About1.h"
#include "Setting.h"
#include "FP.h"
#include "ruleget.h"
#include "Grad.h"
#include "Study.h"
#include "Imloc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int wglob=0, hglob=0; //для передачи в. и ш. выделенной цифры
int lwglob=0, lhglob=0; //для передачи в. и ш. нескольких выделенных цифр

int iml=0; //imagelist index

int rmas[1000][100]; //for get rules from db

/*for multilocation*/
int  vpixe=0, vmax=0; //конец выделяемой цифры, координата макс. черной верт. полосы на картинке
bool cid2=false;      // для запоминания цифры
bool durak=false;     //защита от "дурака"
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
		OpenDialog1->Title = "Save WEBCam Image";
		OpenDialog1->DefaultExt = "bmp";
		OpenDialog1->Filter = "Bmp files (*.bmp)|*.BMP";
		if (OpenDialog1->Execute())
		{
				Image1->Picture->Bitmap->LoadFromFile(OpenDialog1->FileName);
		}
		durak = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
 Cam->Show();
 durak = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
		int ch=0;
        int imas[1000], tmas[50][50];
        double ifmas[1000][10];

        for (int i=0; i<1000; i++) {imas[i]=0;}

        for (int i=0; i<50; i++)
                for (int j=0; j<50; j++)
                        tmas[i][j]=0;

        for (int i=0; i<1000; i++)
                for (int j=0; j<10; j++)
                        ifmas[i][j]=0;


        Edit1->Text="";
        ProgressBar1->Position=0;

		grayim(Image1);
		filpix(Image1);
        ProgressBar1->StepBy(15);
        location(wglob, hglob, sCl);
        ProgressBar1->StepBy(15);
        lwglob = wglob, lhglob = hglob;

        while((ch-1)<vmax){
        ch = vpixe;
        multiloc(Image1, Image2, vpixe, vmax, lwglob, lhglob, wglob, hglob, cid2, sCl);
        ProgressBar1->StepBy(15);
        Refresh();
        getnumgauss37(Image1, imas, ifmas, wglob, hglob, sCl, 8);
        ProgressBar1->StepBy(15);
        getidT(rmas, imas, tmas);
        ProgressBar1->StepBy(15);
        printid(Edit1, tmas);
        ProgressBar1->StepBy(25);
        if (vmax==0) ch=1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{//FUZZY
 if (durak) {
 ShowMessage("Ошибка! Загрузите новое изображение.");
 return;
 }
		int ch=0;
		int imas[1000], tmas[50][50];
		double ifmas[1000][10];

		for (int i=0; i<1000; i++) {imas[i]=0;}

		for (int i=0; i<50; i++)
				for (int j=0; j<50; j++)
						tmas[i][j]=0;

		for (int i=0; i<1000; i++)
				for (int j=0; j<10; j++)
						ifmas[i][j]=0;


        Edit1->Text="";
        ProgressBar1->Position=0;

		grayim(Image1);
		filpix(Image1);
        ProgressBar1->StepBy(15);
        location(wglob, hglob, sCl);
        ProgressBar1->StepBy(15);
        lwglob = wglob, lhglob = hglob;

		while((ch-1)<vmax){
		ch = vpixe;
		multiloc(Image1, Image2, vpixe, vmax, lwglob, lhglob, wglob, hglob, cid2, sCl);
        ProgressBar1->StepBy(35);
        Refresh();
        getnumgauss37(Image1, imas, ifmas, wglob, hglob, sCl, 8);
		ProgressBar1->StepBy(35);
		printidF(Edit1, getidF(rmas, imas, ifmas));
        ProgressBar1->StepBy(30);
        if (vmax==0) ch=1;
		}
		SetMemo(Edit1, Memo1);
		durak = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
		getrule(rmas);
		sCl=180;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Y1Click(TObject *Sender)
{
 Settings->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button6Click(TObject *Sender)
{
 grayim(Image1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
 About->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
 FPG->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
 Cam->Show();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N14Click(TObject *Sender)
{
        SaveDialog1->Title = "Save Image";
        SaveDialog1->DefaultExt = "bmp";
        SaveDialog1->Filter = "Bmp files (*.bmp)|*.BMP";
        if (SaveDialog1->Execute())
        {
                Image1->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N21Click(TObject *Sender)
{
		SaveDialog1->Title = "Save Image";
        SaveDialog1->DefaultExt = "bmp";
        SaveDialog1->Filter = "Bmp files (*.bmp)|*.BMP";
        if (SaveDialog1->Execute())
        {
                Image2->Picture->Bitmap->SaveToFile(SaveDialog1->FileName);
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
		OpenDialog1->Title = "Save WEBCam Image";
		OpenDialog1->DefaultExt = "bmp";
		OpenDialog1->Filter = "Bmp files (*.bmp)|*.BMP";
		if (OpenDialog1->Execute())
		{
				Image1->Picture->Bitmap->LoadFromFile(OpenDialog1->FileName);
		}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button5Click(TObject *Sender)
{
        location(wglob, hglob, sCl);
		lwglob = wglob, lhglob = hglob;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
multiloc(Image1, Image2, vpixe, vmax, lwglob, lhglob, wglob, hglob, cid2, sCl);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
		int ch=0;
		int imas[1000], tmas[50][50];
		double ifmas[1000][10];

		for (int i=0; i<1000; i++) {imas[i]=0;}

		for (int i=0; i<50; i++)
				for (int j=0; j<50; j++)
						tmas[i][j]=0;

		for (int i=0; i<1000; i++)
				for (int j=0; j<10; j++)
						ifmas[i][j]=0;
		getnumgauss37(Image1, imas, ifmas, wglob, hglob, sCl, 8);
		printidF(Edit1, getidF(rmas, imas, ifmas));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
 GroupBox1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N10Click(TObject *Sender)
{
 GroupBox1->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N12Click(TObject *Sender)
{
 ShellExecute(Handle, L"open", L"help.chm", NULL, NULL, SW_RESTORE);
}
//---------------------------------------------------------------------------

