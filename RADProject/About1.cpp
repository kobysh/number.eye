//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout *About;
int about=0, cn=0;
//---------------------------------------------------------------------------
__fastcall TAbout::TAbout(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout::Image1Click(TObject *Sender)
{
 if (cn==10){
		ImageList1->GetBitmap(2,Image1->Picture->Bitmap);
		Refresh();
		cn=0;
		about=1;
 }
 else
 {
 if (about==1) about=0;
 else about=1;
 ImageList1->GetBitmap(about,Image1->Picture->Bitmap);
 Refresh();
 cn++;
 }
}
//---------------------------------------------------------------------------

void __fastcall TAbout::FormShow(TObject *Sender)
{
 ImageList1->GetBitmap(0,Image1->Picture->Bitmap);
}
//---------------------------------------------------------------------------

