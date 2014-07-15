//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("dozatory_arm.res");
USEFORM("..\code\Unit1.cpp", Form1);
USEUNIT("..\MyCLASS\ClassArhiv.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
