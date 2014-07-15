//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormEnterKoef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEnterKoef *FEnterKoef;
//---------------------------------------------------------------------------
__fastcall TFEnterKoef::TFEnterKoef(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEnterKoef::BitBtn1Click(TObject *Sender)
{
 double val[8];
 try
  {
   val[0]=StrToFloat(StringReplace(Edit1->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   val[1]=StrToFloat(StringReplace(Edit2->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   val[2]=StrToFloat(StringReplace(Edit3->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   val[3]=StrToFloat(StringReplace(Edit4->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   val[4]=StrToFloat(StringReplace(Edit5->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
   for (int i=0;i<5;i++)
    {
     int k = val[i]*100;
     PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,id[i],k);
    }
   if (type_reg==1)
    {
     val[5]=StrToFloat(StringReplace(Edit6->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
     val[6]=StrToFloat(StringReplace(Edit7->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
     int k = val[5]*100;
     PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,id[5],k); k = val[6]*100;
     PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,id[6],k);
    }
  }
 catch (...)
  {
   Application->MessageBoxA("Одно или несколько значений заданы не верно. Должны быть вещественные числа!","Внимание!",MB_OK+MB_ICONSTOP);
   Abort();
  }
}
//---------------------------------------------------------------------------

