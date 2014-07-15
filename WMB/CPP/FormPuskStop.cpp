//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormPuskStop.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPuskStop *FPuskStop;
//---------------------------------------------------------------------------
__fastcall TFPuskStop::TFPuskStop(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::BitBtn1Click(TObject *Sender)
{
 PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_PUSK,1);
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::BitBtn2Click(TObject *Sender)
{
 if (ID_PUSK!=ID_STOP) PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_STOP,1);
 else                  PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_STOP,0);
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::BitBtn3Click(TObject *Sender)
{
 PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_STOPA,1);
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::SpeedButton1Click(TObject *Sender)
{
 if ((SpeedButton1->Down)&&(Click))
  {
   PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_MODE,1);
//   ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::SpeedButton2Click(TObject *Sender)
{
 if ((SpeedButton2->Down)&&(Click))
  {
   PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_MODE,0);
  // ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFPuskStop::FormShow(TObject *Sender)
{
 if (ID_MODE>0)
  {
   Click = false;
   Variant Val;
   Val = DataSet->Lookup("IDTag",ID_MODE,"ValueTag");
   if (Val==1)  // Автоматический режим
    {
     SpeedButton1->Down=true;
     BitBtn1->Enabled  =false;
     BitBtn2->Enabled  =false;
    }
   else
    {
     SpeedButton2->Down=true;
     BitBtn1->Enabled  =true;
     BitBtn2->Enabled  =true;
    }
   Click = true;
  }
 else
  {
   BitBtn1->Enabled  =true;
   BitBtn2->Enabled  =true;
   Click=false;
  }
}
//---------------------------------------------------------------------------


