//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormEnterUst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEnterUst *FEnterUst;
//---------------------------------------------------------------------------
__fastcall TFEnterUst::TFEnterUst(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEnterUst::BitBtn1Click(TObject *Sender)
{
 double val[40];
 try
  {
   TEdit *Tmp;
   for (int pc=0;pc<31;pc++)
    {
     Tmp     = (TEdit *)FindComponent("E"+IntToStr(pc+1));
     val[pc] = StrToFloat(StringReplace(Tmp->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
     int k = val[pc]*100;
     PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,id[pc],k);
    }
  }
 catch (...)
  {
   Application->MessageBoxA("Одно или несколько значений заданы не верно. Должны быть вещественные числа!","Внимание!",MB_OK+MB_ICONSTOP);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFEnterUst::Timer1Timer(TObject *Sender)
{
 if (OnGetParam!=NULL)
  {
   double Val   ;
   int    Status;
   for (int i=0;i<31;i++)
    {
     OnGetParam(this,id[i],Val,Status);
     TStaticText *Tmp;
     Tmp = (TStaticText *)FindComponent("T"+IntToStr(i+1));
     if (Tmp!=NULL)
      {
       Tmp->Caption=FormatFloat("###0.0",Val);
       if (Status!=0) Tmp->Font->Color=clRed;
       else           Tmp->Font->Color=clLime;
       if (first[i])
        {
         TEdit *TmpEdit;
         TmpEdit = (TEdit *)FindComponent("E"+IntToStr(i+1));
         if (TmpEdit!=NULL)
          {
           TmpEdit->Text = Tmp->Caption;
           first[i]      = false;
          }
        }
      }
    }
  }
}
//---------------------------------------------------------------------------
