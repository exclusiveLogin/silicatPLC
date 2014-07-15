//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Update.res");
USEFORM("FormUpdate.cpp", FUpdate);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFUpdate), &FUpdate);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
