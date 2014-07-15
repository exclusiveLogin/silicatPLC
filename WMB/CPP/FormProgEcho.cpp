//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormProgEcho.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPEcho *FPEcho;
//---------------------------------------------------------------------------
__fastcall TFPEcho::TFPEcho(TComponent* Owner)
        : TForm(Owner)
{
 int CountArhivTag = 0;
 if (!QListTags->Active) QListTags->Open();
 while (!QListTags->Eof)
  {
   if (QListTagsIDTag->AsInteger<10000) CountArhivTag++;
   QListTags->Next();
  }
 Arhiv = new MyArhiv(this,CountArhivTag,1000);
 SSocket->Active=true;

}
//---------------------------------------------------------------------------
__fastcall TFPEcho::~TFPEcho(void)
{
 ConArhiv->Connected=false;
}
//---------------------------------------------------------------------------
void __fastcall TFPEcho::SSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
 // ���� �������� �������
 // �������:
 // [1][dd.mm.yyyy hh:nn:ss] - (24 �����)  ������ ������
 // ����������:
 // [ERROR.__1] - 1. ������������ �������
 // [ERROR.__2] - 2. ������������ ������ �������
 // [ERROR.__3] - 3. ��������� ����� ������
 // [ERROR.__4] - 4. ������������ ������ �������
 int len;
 unsigned char buffer[1000];
 if ((len=Socket->ReceiveLength())>0)
  {
   if (len<30) // ����� ������� <30
    {
     Socket->ReceiveBuf(&buffer[0],len);
     if ((buffer[0]=='[')&&(buffer[2]==']'))
      {
       if (buffer[1]=='1') // ������� ������
        {
         AnsiString DTInf  ; // �� ����� ������ ������� ����� ����������
         TDateTime  Tmp    ;
         for (int i=0;i<19;i++)
          {
           AnsiChar sim = buffer[i+4];
           DTInf = DTInf + sim;
          }
         try
          {
           Tmp = DTInf;
           struct  TTemp
            {
             double Val   ;
             int    IDTag ;
             int    Status;
            } *data_temp;
           data_temp = (struct TTemp *)calloc(Arhiv->CountTags,sizeof(struct TTemp));
           for (int pc=0;pc<Arhiv->CountTags;pc++)
            {
             data_temp[pc].IDTag  = Arhiv->IDTags[pc];
             if (data_temp[pc].IDTag>0)
              {
               data_temp[pc].Val    = Arhiv->DataTag[Tmp][data_temp[pc].IDTag].Val   ;
               data_temp[pc].Status = Arhiv->DataTag[Tmp][data_temp[pc].IDTag].Status;
              }
             else
              {
               data_temp[pc].Val    = 0;
               data_temp[pc].Status = 1;
              }
            }
           Socket->SendBuf(data_temp,Arhiv->CountTags*sizeof(struct TTemp));
          }
         catch (...)
          {
           memcpy(buffer,"[ERROR.__4]\0",12);
           Socket->SendBuf(buffer,12);
          }
        }
       else //++? ������ ������ ������
        {
         memcpy(buffer,"[ERROR.__1]\0",12);
         Socket->SendBuf(buffer,12)       ;
        }
      }
     else
      {
       memcpy(buffer,"[ERROR.__2]\0",12);
       Socket->SendBuf(buffer,12)       ;
      }
    }
   else
    {
     memcpy(buffer,"[ERROR.__3]\0",12);
     Socket->SendBuf(buffer,12)       ;
    }
  }

}
//---------------------------------------------------------------------------
void __fastcall TFPEcho::SSocketClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 int k=1;
 if (k==1)
  {
    k=k+1;
  }
}
//---------------------------------------------------------------------------

