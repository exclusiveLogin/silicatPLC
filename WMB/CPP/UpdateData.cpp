//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UpdateData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 QSource->Open();
 Q1->Open();
 while (!QSource->Eof)
  {
   Q1->Insert();
   Q1IDTag->AsInteger     = QSourceIDTag->AsInteger+300;
   Q1NameTag->AsString    = "DE2_"+QSourceNameTag->AsString.Trim();
   Q1CaptionTag->AsString = StringReplace(StringReplace(QSourceCaptionTag->AsString,"Ê3.","Ê4.",TReplaceFlags()<<rfReplaceAll),"K3.","Ê3.",TReplaceFlags()<<rfReplaceAll);
   Q1ValueTag->AsFloat    = QSourceValueTag->AsFloat;
   Q1StatusTag->AsInteger = QSourceStatusTag->AsInteger;
   Q1TypeOpros->AsInteger = 5;
   Q1Param1->AsString     = "MODBUS_TCP_3";
   Q1Param2->AsString     = QSourceParam2->AsString;
   Q1Param3->AsString     = QSourceParam3->AsString;
   Q1TypeValue->AsInteger = QSourceTypeValue->AsInteger;
   if (QSourceNumEkran->AsInteger>0)
    Q1NumEkran->AsInteger = 8;
   else
    Q1NumEkran->AsInteger = 0;
   Q1TypeVisibleElement->AsInteger = QSourceTypeVisibleElement->AsInteger;
   Q1VisParam1->AsString  = QSourceVisParam1->AsString;
   Q1VisParam2->AsString  = QSourceVisParam2->AsString;
   Q1VisParam3->AsString  = QSourceVisParam3->AsString;
   Q1VisParam4->AsString  = QSourceVisParam4->AsString;
   Q1MinVal->AsString     = QSourceMinVal->AsString;
   Q1MaxVal->AsString     = QSourceMaxVal->AsString;
   Q1MinValIn->AsString   = QSourceMinValIn->AsString;
   Q1MaxValIn->AsString   = QSourceMaxValIn->AsString;
   Q1ExtParam3->AsString  = QSourceExtParam3->AsString;
   Q1NameContr->AsString  = QSourceNameContr->AsString;
   Q1NameModul->AsString  = QSourceNameModul->AsString;
   Q1NumEnter->AsString   = QSourceNumEnter->AsString;
   Q1TypeArhiv->AsInteger = QSourceTypeArhiv->AsInteger;
   Q1UslWrite->AsInteger  = QSourceUslWrite->AsInteger;
   Q1UslAvar->AsInteger   = QSourceUslAvar->AsInteger;
   Q1TypeVisibleArhiv->AsInteger = QSourceTypeVisibleArhiv->AsInteger;
   Q1->Post();
   QSource->Next();
  }
 ConSource->Connected=false;
 Con1->Connected=false;
}
//---------------------------------------------------------------------------
