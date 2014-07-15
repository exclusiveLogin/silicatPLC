//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("opros.res");
USEFORM("..\code\FormOpros.cpp", PACQuery);
USEUNIT("..\MyCLASS\ClassArhiv.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TPACQuery), &PACQuery);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
