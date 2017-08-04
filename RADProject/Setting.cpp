//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Setting.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettings *Settings;
//---------------------------------------------------------------------------
__fastcall TSettings::TSettings(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettings::Button1Click(TObject *Sender)
{
        float xn;
         if(Edit1->Text.Length() == 0)
         {
			ShowMessage ("ќшибка! ¬ведите €ркость.");
			return;
         }
         else if (!TryStrToFloat(Edit1->Text, xn)||((StrToFloat(Edit1->Text))>255)||((StrToFloat(Edit1->Text))<0))
         {
                 ShowMessage("ќщибка! «начение €ркости должно быть в диапазоне 0-255");
                return;
         }

        Form1->sCl = StrToFloat(Edit1->Text);
        Close();
}
//---------------------------------------------------------------------------

void __fastcall TSettings::Button2Click(TObject *Sender)
{
        float xn;
		 if(Edit1->Text.Length() == 0)
         {
			ShowMessage ("ќшибка! ¬ведите €ркость.");
            return;
         }
         else if (!TryStrToFloat(Edit1->Text, xn)||((StrToFloat(Edit1->Text))>255)||((StrToFloat(Edit1->Text))<0))
		 {
				 ShowMessage("ќщибка! «начение €ркости должно быть в диапазоне 0-255");
                return;
         }

        Form1->sCl = StrToFloat(Edit1->Text);
}
//---------------------------------------------------------------------------



void __fastcall TSettings::FormCreate(TObject *Sender)
{
// Edit1->Text = FloatToStr(Form1->sCl);
}
//---------------------------------------------------------------------------

