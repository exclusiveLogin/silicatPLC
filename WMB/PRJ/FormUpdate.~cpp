//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormUpdate.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFUpdate *FUpdate;
//---------------------------------------------------------------------------
__fastcall TFUpdate::TFUpdate(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFUpdate::Button1Click(TObject *Sender)
{
 if (!QListTags->Active) QListTags->Open();
 try
  {
   while (!QListTags->Eof)
    {
     int NewZn  = -1;
     int NewTVE = -1;
     switch (QListTagsIDTag->AsInteger)
      {
       case 45  : NewZn=17;break;
       case 1022: NewZn=20;break;
       case 1322: NewZn=24;break;
       case 3   : NewZn=17;break;
       case 4   : NewZn=17;break;
       case 1156: NewZn=16;NewTVE=2;break;
       case 1456: NewZn=16;NewTVE=2;break;
       case 1005: NewZn=20;break;
       case 1305: NewZn=24;break;
       case 42  : NewZn=17;break;
       case 1053: NewZn=20;break;
       case 1054: NewZn=20;break;
       case 1055: NewZn=20;break;
       case 1056: NewZn=20;break;
       case 1057: NewZn=20;break;
       case 1058: NewZn=20;break;
       case 1059: NewZn=20;break;
       case 1060: NewZn=20;break;
       case 1061: NewZn=20;break;
       case 1353: NewZn=24;break;
       case 1354: NewZn=24;break;
       case 1355: NewZn=24;break;
       case 1356: NewZn=24;break;
       case 1357: NewZn=24;break;
       case 1358: NewZn=24;break;
       case 1359: NewZn=24;break;
       case 1360: NewZn=24;break;
       case 1361: NewZn=24;break;
      }
     if (NewZn>0)
      {
       bool izm=false;
       QListTags->Edit();
       if (QListTagsNumEkran->AsInteger!=NewZn)
        {
         QListTagsNumEkran->AsInteger = NewZn;izm=true;
        }
       if (NewTVE>0)
        {
         if (QListTagsTypeVisibleElement->AsInteger!=NewTVE)
          {   QListTagsTypeVisibleElement->AsInteger=NewTVE;izm=true; }
        }
       if (izm)  QListTags->Post();
      }
     QListTags->Next();
    }
   Application->MessageBoxA("База обновлена!","Внимание",MB_OK);
  }
 catch (...)
  {
   Application->MessageBoxA("Ошибка обновления базы!","Внимание",MB_OK+MB_ICONSTOP);
  }
 ConArhiv->Connected=false;
}
//---------------------------------------------------------------------------
