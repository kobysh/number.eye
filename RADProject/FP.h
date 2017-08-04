//---------------------------------------------------------------------------

#ifndef FPH
#define FPH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
//---------------------------------------------------------------------------
class TFPG : public TForm
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TImage *Image1;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TLineSeries *Series5;
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFPG(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPG *FPG;
//---------------------------------------------------------------------------
#endif
