//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormEnterShkals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEnterShkal *FEnterShkal;
//---------------------------------------------------------------------------
__fastcall TFEnterShkal::TFEnterShkal(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEnterShkal::BitBtn1Click(TObject *Sender)
{
 double Val[2];
 try
  {
   Val[0]=StrToFloat(StringReplace(Edit1->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   Val[1]=StrToFloat(StringReplace(Edit2->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   for (int i=0;i<2;i++)
    {
     int k = Val[i]*100;
     PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,id[i],k);
    }
  }
 catch (...)
  {
   Application->MessageBoxA("Одно или несколько значений заданы не верно. Должны быть вещественные числа!","Внимание!",MB_OK+MB_ICONSTOP);
   Abort();
  }
}
//---------------------------------------------------------------------------
