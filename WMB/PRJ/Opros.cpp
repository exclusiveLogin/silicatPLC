//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Opros.res");
USEFORM("..\CPP\FormOpros.cpp", FOpros);
USEUNIT("..\MyCLASS\ClassArhiv.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
             if (FindWindow("TFOpros","Опрос по протоколу Modbus")!=NULL)
              {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFOpros), &FOpros);
                 Application->Run();
               }
         }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
