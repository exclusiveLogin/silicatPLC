//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("WBDKS.res");
USEFORM("..\CPP\MainFormKS.cpp", FMainForm);
USEUNIT("..\MyCLASS\ClassArhiv.cpp");
USEFORM("..\CPP\FormEnterString.cpp", FEnterString);
USEFORM("..\CPP\FormPuskStop.cpp", FPuskStop);
USEFORM("..\CPP\FormOnOffRezerv.cpp", FOnOffRezerv);
USEFORM("..\CPP\FormPassword.cpp", FPassword);
USEFORM("..\CPP\FormEnterKoef.cpp", FEnterKoef);
USEFORM("..\CPP\FormReg.cpp", FReg);
USEFORM("..\CPP\FormEnterShkals.cpp", FEnterShkal);
USEFORM("..\CPP\FormEnterUst.cpp", FEnterUst);
USEFORM("..\CPP\FormDiag.cpp", FDiag);
USEFORM("..\CPP\FormBlok.cpp", FBlok);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFMainForm), &FMainForm);
                 Application->CreateForm(__classid(TFEnterString), &FEnterString);
                 Application->CreateForm(__classid(TFPuskStop), &FPuskStop);
                 Application->CreateForm(__classid(TFOnOffRezerv), &FOnOffRezerv);
                 Application->CreateForm(__classid(TFPassword), &FPassword);
                 Application->CreateForm(__classid(TFEnterKoef), &FEnterKoef);
                 Application->CreateForm(__classid(TFReg), &FReg);
                 Application->CreateForm(__classid(TFEnterShkal), &FEnterShkal);
                 Application->CreateForm(__classid(TFEnterUst), &FEnterUst);
                 Application->CreateForm(__classid(TFDiag), &FDiag);
                 Application->CreateForm(__classid(TFBlok), &FBlok);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
