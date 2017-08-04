//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TImage *Image2;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TEdit *Edit1;
	TProgressBar *ProgressBar1;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N4;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N5;
	TMenuItem *N2;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *Y1;
	TMenuItem *N3;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TImageList *ImageList1;
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TButton *Button6;
	TMenuItem *N14;
	TMenuItem *N21;
	TMemo *Memo1;
	TGroupBox *GroupBox1;
	TButton *Button5;
	TButton *Button7;
	TButton *Button8;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Y1Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall N13Click(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N7Click(TObject *Sender);
	void __fastcall N14Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall N6Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall N9Click(TObject *Sender);
	void __fastcall N10Click(TObject *Sender);
	void __fastcall N12Click(TObject *Sender);
private:	// User declarations
public:	int sCl;	// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
