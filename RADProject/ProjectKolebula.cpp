//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------



















USEFORM("Setting.cpp", Settings);
USEFORM("FP.cpp", FPG);
USEFORM("Camera.cpp", Cam);
USEFORM("About1.cpp", About);
USEFORM("Main.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TSettings), &Settings);
		Application->CreateForm(__classid(TFPG), &FPG);
		Application->CreateForm(__classid(TCam), &Cam);
		Application->CreateForm(__classid(TAbout), &About);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
