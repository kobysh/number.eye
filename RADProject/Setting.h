//---------------------------------------------------------------------------

#ifndef SettingH
#define SettingH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TSettings : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Edit1;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label3;
	TComboBox *ComboBox2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSettings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettings *Settings;
//---------------------------------------------------------------------------
#endif
