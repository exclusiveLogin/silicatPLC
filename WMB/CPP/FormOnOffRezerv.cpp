//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormOnOffRezerv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFOnOffRezerv *FOnOffRezerv;
//---------------------------------------------------------------------------
__fastcall TFOnOffRezerv::TFOnOffRezerv(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFOnOffRezerv::FormShow(TObject *Sender)
{
 Click = false;
 Variant Val1,Val2,Val3;
 Val1 = DataSet->Lookup("IDTag",ID_REZ1,"ValueTag");
 Val2 = DataSet->Lookup("IDTag",ID_REZ2,"ValueTag");
 Val3 = DataSet->Lookup("IDTag",ID_REZ3,"ValueTag");
 SpeedButton1->Down=false;
 SpeedButton2->Down=false;
 SpeedButton3->Down=false;
 if (Val1==1) SpeedButton1->Down=true; else
 if (Val2==1) SpeedButton2->Down=true; else
 if (Val3==1) SpeedButton3->Down=true;
 if (SpeedButton1->Down) { StaticText4->Caption="В резерве";SpeedButton1->Caption="Отключить резерв"; } else { StaticText4->Caption="";SpeedButton1->Caption="Включить резерв"; }
 if (SpeedButton2->Down) { StaticText5->Caption="В резерве";SpeedButton2->Caption="Отключить резерв"; } else { StaticText5->Caption="";SpeedButton2->Caption="Включить резерв"; }
 if (SpeedButton3->Down) { StaticText6->Caption="В резерве";SpeedButton3->Caption="Отключить резерв"; } else { StaticText6->Caption="";SpeedButton3->Caption="Включить резерв"; }
 Click = true;

}
//---------------------------------------------------------------------------
void __fastcall TFOnOffRezerv::SpeedButton1Click(TObject *Sender)
{
 if (Click)
  {
   PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_WREZ1,1);
   ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOnOffRezerv::SpeedButton2Click(TObject *Sender)
{
 if (Click)
  {
   PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_WREZ2,1);
   ModalResult = mrOk;
  }

}
//---------------------------------------------------------------------------
void __fastcall TFOnOffRezerv::SpeedButton3Click(TObject *Sender)
{
 if (Click)
  {
   PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,ID_WREZ3,1);
   ModalResult = mrOk;
  }
}
//---------------------------------------------------------------------------
