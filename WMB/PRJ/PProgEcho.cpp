//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("PProgEcho.res");
USEFORM("..\CPP\FormProgEcho.cpp", FPEcho);
USEUNIT("..\MyCLASS\ClassArhiv.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFPEcho), &FPEcho);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
