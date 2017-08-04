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
#include <Clipbrd.hpp>
#pragma hdrstop

#include "Camera.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCam *Cam;
HWND hWndC;
//---------------------------------------------------------------------------
__fastcall TCam::TCam(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCam::Button1Click(TObject *Sender)
{
 capDriverDisconnect(hWndC);
 Timer1->Enabled=false;

 //int Height =  Image1->Picture->Bitmap->Height;
 //int Width =  Image1->Picture->Bitmap->Width;
 byte R, G, B;

   for(int x = 0; x < 400; x++) {
        for(int y = 0; y < 250; y++) {
				Form1->Image1->Picture->Bitmap->Canvas->Pixels[x][y] = RGB(0, 0, 0);
        }
  }

  for(int x = 0; x < 400; x++) {
        for(int y = 0; y < 250; y++) {
                R = GetRValue(Image1->Picture->Bitmap->Canvas->Pixels[x][y]);
                G = GetGValue(Image1->Picture->Bitmap->Canvas->Pixels[x][y]);
                B = GetBValue(Image1->Picture->Bitmap->Canvas->Pixels[x][y]);

                Form1->Image1->Picture->Bitmap->Canvas->Pixels[x][y]=RGB(R, G, B);
        }
  }
}
//---------------------------------------------------------------------------

void __fastcall TCam::Button2Click(TObject *Sender)
{
 Cam->Close();
}
//---------------------------------------------------------------------------

void __fastcall TCam::Timer1Timer(TObject *Sender)
{
 capGrabFrame(hWndC);
 if(capEditCopy(hWndC))
 Image1->Picture->LoadFromClipboardFormat(CF_BITMAP, Clipboard()->GetAsHandle(CF_BITMAP),0);
}
//---------------------------------------------------------------------------

void __fastcall TCam::FormClose(TObject *Sender, TCloseAction &Action)
{
 capDriverDisconnect(hWndC);
}
//---------------------------------------------------------------------------

void __fastcall TCam::FormShow(TObject *Sender)
{
 hWndC=capCreateCaptureWindow(_T(""), WS_CHILD, this->Left, this->Top, Image1->Width, Image1->Height, this->Handle, 11011);
 capDriverConnect (hWndC,0);
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

