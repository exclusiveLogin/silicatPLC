//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormEnterZadan.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFEnterZadan *FEnterZadan;
//---------------------------------------------------------------------------
__fastcall TFEnterZadan::TFEnterZadan(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFEnterZadan::BitBtn1Click(TObject *Sender)
{
 try
  {
   AnsiString SS =StringReplace(Edit1->Text.Trim(),",",".",TReplaceFlags());
   AnsiString SS1=StringReplace(Edit1->Text.Trim(),".",",",TReplaceFlags());
   try {   NewZad=StrToFloat(SS); }
   catch (...) { NewZad=StrToFloat(SS1); }
  }
 catch (...)
 {
  Application->MessageBoxA("¬ведите числовое значение!","ќшибка ввода!",MB_OK+MB_ICONSTOP);
  Abort();
 }
}
//---------------------------------------------------------------------------
