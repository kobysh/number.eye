//---------------------------------------------------------------------------

#ifndef CameraH
#define CameraH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCam : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TButton *Button1;
	TButton *Button2;
	TTimer *Timer1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCam(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCam *Cam;
//---------------------------------------------------------------------------
#endif
