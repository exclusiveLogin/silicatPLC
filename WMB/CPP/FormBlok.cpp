//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormBlok.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFBlok *FBlok;
//---------------------------------------------------------------------------
__fastcall TFBlok::TFBlok(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFBlok::Timer1Timer(TObject *Sender)
{

 // Обновление установленных значений
  if (OnGetParam!=NULL)
  {
   double Val   ;
   int    Status;
   if (change) tim++; else L1->Visible=false;
   if (tim>=5) { L1->Visible=false;change=false;  }
   else if (change) { L1->Visible=true;L1->Caption=IntToStr(6-tim); }
   for (int i=0;i<36;i++)
    {
     OnGetParam(this,ID_Time_Blok[i],Val,Status);
     TStaticText *Tmp;
     Tmp = (TStaticText *)FindComponent("T"+IntToStr(i+1));
     if (Tmp!=NULL)
      {
       Tmp->Caption=FormatFloat("###0.0",Val);
       if (Status!=0) Tmp->Font->Color=clRed;
       else           Tmp->Font->Color=clLime;
       if (change) // 10 секунд после нажатия кнопки сохранения отображение текущих значений блокировок
        {
         TSpeedButton  *TmpSB_On,*TmpSB_Off;
         TmpSB_On  = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(i*2+1));
         TmpSB_Off = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(i*2+2));
         OnGetParam(this,ID_On_Blok[i],Val,Status);
         if ((TmpSB_On!=NULL)&&(TmpSB_Off!=NULL))
          {
           if (Status!=0)
            {
             TmpSB_On->Visible =false;
             TmpSB_Off->Visible=false;
            }
           else
            {
             TmpSB_On->Visible =true;
             TmpSB_Off->Visible=true;
             if (Val==0)
              {
               TmpSB_On->Down=true;
               TmpSB_On->Font->Color  = clGreen;
               TmpSB_Off->Font->Color = clBlack;
              }
             else
              {
               TmpSB_Off->Down=true;
               TmpSB_On->Font->Color  = clBlack;
               TmpSB_Off->Font->Color =   clRed;
              }
            }
          }
        }
       if (first[i])
        {
         TEdit         *TmpEdit ;
         TSpeedButton  *TmpSB_On,*TmpSB_Off;
         TmpEdit   = (TEdit *)FindComponent("E"+IntToStr(i+1));
         TmpSB_On  = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(i*2+1));
         TmpSB_Off = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(i*2+2));
         OnGetParam(this,ID_On_Blok[i],Val,Status);
         if ((TmpSB_On!=NULL)&&(TmpSB_Off!=NULL))
          {
           if (Status!=0)
            {
             TmpSB_On->Visible =false;
             TmpSB_Off->Visible=false;
            }
           else
            {
             TmpSB_On->Visible =true;
             TmpSB_Off->Visible=true;
             if (Val==0)
              {
               TmpSB_On->Down=true;
               TmpSB_On->Font->Color  = clGreen;
               TmpSB_Off->Font->Color = clBlack;
              }
             else
              {
               TmpSB_Off->Down=true;
               TmpSB_On->Font->Color  = clBlack;
               TmpSB_Off->Font->Color =   clRed;
              }
            }
          }
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
void __fastcall TFBlok::FormActivate(TObject *Sender)
{
 change=false;tim=0;
 for (int pc=0;pc<36;pc++) first[pc]=true;
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFBlok::BitBtn1Click(TObject *Sender)
{
 double ozn,nzn;
 bool izm=false;
 for (int pc1=0;pc1<36;pc1++)
  {
   TEdit       *E ;
   TStaticText *ST;
   ST = (TStaticText *)FindComponent("T"+IntToStr(pc1+1));
   E  = (TEdit *)FindComponent("E"+IntToStr(pc1+1))      ;
   if ((E!=NULL)&&(ST!=NULL))
    {
     if (E->Text.Trim()!=ST->Caption.Trim())
      {
       try
        {
         ozn = StrToFloat(StringReplace(ST->Caption.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll));
         nzn = StrToFloat(StringReplace(E->Text.Trim(),".",DecimalSeparator,TReplaceFlags()<<rfReplaceAll))    ;
         if (ozn!=nzn)
          {
           izm=true;
           int k = nzn*100.0;
           PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,ID_Time_Blok[pc1],k);
          }
        }
       catch (...)
        {
         AnsiString tmp="Константа №"+IntToStr(pc1+1)+" задана некорректно!";
         Application->MessageBoxA(tmp.c_str(),"Внимание!",MB_OK+MB_ICONSTOP);
        }
      }
    }
  }
 for (int pc1=0;pc1<36;pc1++)
  {
   TSpeedButton *On,*Off;
   float ozn,nzn;
   On  = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(pc1*2+1));
   Off = (TSpeedButton *)FindComponent("SpeedButton" + IntToStr(pc1*2+2));
   if ((On!=NULL)&&(Off!=NULL))
    {
     if (On->Font->Color==clGreen) ozn=0; else ozn=100;
     if (On->Down) nzn=0; else nzn=100;
     if (ozn!=nzn)
      {
       izm=true;
       int k=nzn;
       PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+2,ID_On_Blok[pc1],k);
      }

    }
  }
 if (izm)
  {
   change=true;tim=0;
  }
 //first=false;Sleep(1000);
}
//---------------------------------------------------------------------------

