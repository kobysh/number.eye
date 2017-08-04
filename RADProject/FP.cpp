//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "FP.h"
#include "ruleget.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPG *FPG;
//---------------------------------------------------------------------------
__fastcall TFPG::TFPG(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFPG::FormShow(TObject *Sender)
{
        double gux[5];

        Chart1->Series[0]->Clear();
        for (int i=0; i<101; i++){
                gux[0]=fgauss(i, 0, 8);
                gux[1]=fgauss(i, 25, 8);
                gux[2]=fgauss(i, 50, 8);
                gux[3]=fgauss(i, 75, 8);
                gux[4]=fgauss(i, 100, 8);

                Chart1->Series[0]->AddXY(i,gux[0]);
				Chart1->Series[1]->AddXY(i,gux[1]);
                Chart1->Series[2]->AddXY(i,gux[2]);
                Chart1->Series[3]->AddXY(i,gux[3]);
                Chart1->Series[4]->AddXY(i,gux[4]);
        }
}
//---------------------------------------------------------------------------


