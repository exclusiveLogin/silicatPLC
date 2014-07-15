//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormReg.h"
#include "FormPassword.h"
#include "FormEnterKoef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma resource "*.dfm"
TFReg *FReg;
//---------------------------------------------------------------------------
__fastcall TFReg::TFReg(TComponent* Owner)
        : TForm(Owner)
{
 AnsiString TmpFile      ;
 AnsiString TekDir       ;
 TIniFile   *Ini         ;
 char       NameFile[255];
 GetCurrentDirectory(255,NameFile);
 TekDir    =NameFile;
 TmpFile = (String) NameFile + "\\opros.ini";
 KoefMas = 1;
 FReg->Width = 851;
 if (FileExists(TmpFile))
  {
   if ((Ini = new TIniFile(TmpFile))!=NULL)
    {
     NewSizeWidth     = Ini->ReadInteger("SCREEN","Width",1600);
     FReg->ScaleBy(NewSizeWidth,1600);
     KoefMas = (double)NewSizeWidth/1600;
     Panel10->Width = Panel10->Width * (1/KoefMas);
     Panel10->Left  = Panel10->Left  + 20 * (1-KoefMas);
     Panel9->Width  = Panel9->Width * (1/KoefMas);
     Panel9->Left   = Panel9->Left   + 20 * (1-KoefMas);
     Panel11->Width = Panel11->Width * (1/KoefMas);
     Panel11->Left  = Panel11->Left   + 20 * (1-KoefMas);
     delete Ini;
    }
  }
 else
  {

   NewSizeWidth = 1600;
   KoefMas=1;
   Panel10->Width = Panel10->Width * (1/KoefMas);
   Panel10->Left  = Panel10->Left  + 20 * (1-KoefMas);
   Panel9->Width  = Panel9->Width * (1/KoefMas);
   Panel9->Left   = Panel9->Left   + 20 * (1-KoefMas);
   Panel11->Width = Panel11->Width * (1/KoefMas);
   Panel11->Left  = Panel11->Left   + 20 * (1-KoefMas);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar3Change(TObject *Sender)
{
 Panel9->Height = 387 * KoefMas -((double)TrackBar3->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;
 Panel9->Top    = 408 * KoefMas -Panel9->Height;;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar3->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 MaskEdit1->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar3Enter(TObject *Sender)
{
 Panel9->Height = 387 * KoefMas -((double)TrackBar3->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;
 Panel9->Top    = 408 * KoefMas - Panel9->Height;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar3->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 MaskEdit1->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::FormShow(TObject *Sender)
{
  Timer1->Enabled=true;
  if (QListTrend->Active) QListTrend->Requery(TExecuteOptions());
  else                    QListTrend->Open();
  DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"01:00:00");
  DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"01:00:00");
  DTPTime_endTrend->DateTime   = (TTime)Now();
  DTPDate_endTrend->DateTime   = (TDate)Now();
  STTimeTrend->Caption = Now().FormatString("dd.mm.yyyy hh:nn:ss");
  SpeedButton3->Down = true;
  SpeedButton3Click(Sender);
  TrackBar3Enter(Sender);
  TrackBar2Enter(Sender);
  TrackBar1Enter(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar2Change(TObject *Sender)
{
 Panel10->Height = 387 * KoefMas - ((double)TrackBar2->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;// + 4.9 = 0.83  5 = 1   4.9 = 0.83 * �
 Panel10->Top    = 408 * KoefMas - Panel10->Height;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar2->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 if (ModeReg) FAutoZadReg = (100-(double)TrackBar2->Position/100)*FMn+SmFMn;
 else         FHandZadReg = (100-(double)TrackBar2->Position/100)*FMn+SmFMn;
 MaskEdit2->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar2Enter(TObject *Sender)
{
 Panel10->Height = 387 * KoefMas - ((double)TrackBar2->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;// + 5 * KoefMas;
 Panel10->Top    = 408 * KoefMas - Panel10->Height;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar2->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 MaskEdit2->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar1Change(TObject *Sender)
{
 Panel11->Height = 387 * KoefMas -((double)TrackBar1->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;
 Panel11->Top    = 408 * KoefMas -Panel11->Height;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar1->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 MaskEdit3->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TrackBar1Enter(TObject *Sender)
{
 Panel11->Height = 387 * KoefMas -((double)TrackBar1->Position/100)*(0.59*KoefMas+3.3)*KoefMas+29.4*KoefMas-29.4;
 Panel11->Top    = 408 * KoefMas -Panel11->Height;;
 AnsiString Tmp = FormatFloat("###0.0",(100-(double)TrackBar1->Position/100)*FMn+SmFMn);
 for (int pc=Tmp.Length();pc<6;pc++) Tmp=" "+Tmp;
 MaskEdit3->Text = Tmp;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetModeReg(bool Value)
{
 FModeReg = Value;
 if (Value)
  {
   StaticText2->Caption     = "���" ;
   StaticText2->Font->Color = clLime;
   BitBtn1->Enabled         = false ;
   BitBtn2->Enabled         = true  ;
   StaticText1->Caption     = FEdIzm;
   double mn = (FMaxValue - FMinValue)/10;
   FMn   = mn*0.1;
   SmFMn = FMinValue;
   for (int pc=0;pc<=10;pc++)
    {
     TStaticText *tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Whod");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);
     tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Zad");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);
     tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Exit");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);
    }
  }
 else
  {
   StaticText2->Caption     = "���"   ;
   StaticText2->Font->Color = clYellow;
   BitBtn2->Enabled         = false   ;
   BitBtn1->Enabled         = true    ;
   StaticText1->Caption     = "� %"   ;
   double mn = (FMaxValue - FMinValue)/10; //++?
   // FMn = 1;
   SmFMn = FMinValue;
   FMn = mn*0.1     ; //++?
   for (int pc=0;pc<=10;pc++)
    {
     TStaticText *tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Whod");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);//10);
     tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Zad");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);//10);
     tmp = (TStaticText *)FindComponent("L"+IntToStr(pc+1)+"_Exit");
     if (tmp!=NULL) tmp->Caption = FormatFloat("###0.0",pc*mn + FMinValue);//10);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetShkals(double MinValue, double MaxValue)
{
 FMinValue = MinValue;
 FMaxValue = MaxValue;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetZadAuto(double Value)
{
 // ��������� ������� ��� ��������������� ������
 double pos = 0;
 double Val=Value;
 if (Value<FMinValue) Val=FMinValue;
 else if (Value>FMaxValue) Val=FMaxValue;
 FAutoZadReg = Val;
 if (FModeReg) // �������������� ����� - ���������� �� �����
  {
   if ((FMaxValue-FMinValue)>0)
    pos = (Val-FMinValue) / (FMaxValue-FMinValue) * 10000;
   else pos=0;
   if ((pos>=0)&&(pos<=10000)) TrackBar2->Position = 10000 - pos;
   TrackBar2Enter(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetZadHand(double Value)
{
 double Val=Value;
 double pos =0;
// if (Value<0) Val = 0;
// else if (Value>100) Val=100;
 if (Value<FMinValue) Val=FMinValue;
 else if (Value>FMaxValue) Val=FMaxValue;
 FHandZadReg = Val;
 if (!FModeReg) // ������ ����� - ���������� �� �����
  {
//   pos = Val * 100;
//   if ((pos>=0)&&(pos<=10000)) TrackBar2->Position = 10000 - pos;
//   TrackBar2Enter(this);
   if ((FMaxValue-FMinValue)>0)
    pos = (Val-FMinValue) / (FMaxValue-FMinValue) * 10000;
   else pos=0;
   if ((pos>=0)&&(pos<=10000)) TrackBar2->Position = 10000 - pos;
   TrackBar2Enter(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetEnter(double Value)
{
 // ���� ������ � �������� ���������
 double Val=Value;
 double pos=0;
 if (Value<FMinValue) Val=FMinValue;
 else if (Value>FMaxValue) Val=FMaxValue;
 FEnterReg = Val;
 if ((FMaxValue-FMinValue)>0)
  pos = (Val-FMinValue) / (FMaxValue-FMinValue) * 10000;
 else pos=0;
 if ((pos>=0)&&(pos<=10000)) TrackBar3->Position = 10000 - pos;
 TrackBar3Enter(this);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SetExit(double Value)
{
 // ����� ������ � ���������
 double Val=Value;
 double pos=0;
 if (Value<0) Val=0;
 else if (Value>100) Val=100;
 FExitReg = Val;
 pos = Val * 100;
 if ((pos>=0)&&(pos<=10000)) TrackBar1->Position = 10000 - pos;
 TrackBar1Enter(this);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::Timer1Timer(TObject *Sender)
{
 double Val   ;
 int    Status;
 if (OnGetParam!=NULL)
  {
   OnGetParam(this,IDTAG_ENTER,Val,Status);
   if (Status==0) { TrackBar3->Visible=true;MaskEdit1->Visible=true; SetEnter(Val); }
   else { TrackBar3->Visible=false;MaskEdit1->Visible = false; }

  }
 if (OnGetParam!=NULL)
  {
   OnGetParam(this,IDTAG_EXIT,Val,Status) ;
   if (Status==0) { TrackBar1->Visible=true;MaskEdit3->Visible=true; SetExit(Val); }
   else { TrackBar1->Visible=false;MaskEdit3->Visible = false; }
  }
 if (OnGetParam!=NULL)
  {
   OnGetParam(this,IDTAG_MODE,Val,Status);
   if (Status==0) { if (ModeReg!=Val) { ModeReg = Val;TrackBar2Change(this); } else ModeReg = Val; }
  }
 if (SpeedButton3->Down)
  {
   DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"00:15:00");
   DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"00:15:00");
   DTPTime_endTrend->DateTime   = (TTime)Now();
   DTPDate_endTrend->DateTime   = (TDate)Now();
   BBBuilderTrendClick(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::FormHide(TObject *Sender)
{
 Timer1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::MaskEdit2Exit(TObject *Sender)
{
 // ���������� �������� �������
 try
  {
   double NewZad = StrToFloat(MaskEdit2->Text.Trim());
   if (FModeReg) // �������������� �����
    {
     if ((NewZad<FMinValue)||(NewZad>FMaxValue))
      {
       Application->MessageBoxA("������� ������� ��� ����������� ���������! (���� � �������� ���������)","��������!",MB_OK+MB_ICONSTOP);
       TrackBar2Enter(this);
      }
     else  SetZadAuto(NewZad);
    }
   else
    {
     if ((NewZad<FMinValue)||(NewZad>FMaxValue)) // ++? ((NewZad<0)||(NewZad>100))
      {
       Application->MessageBoxA("������� ������� ��� ����������� ���������! (���� � ���������)","��������!",MB_OK+MB_ICONSTOP);
       TrackBar2Enter(this);
      }
     else SetZadHand(NewZad);
    }
  }
 catch (...)
  {
   Application->MessageBoxA("������� ������� �����������!","��������!",MB_OK+MB_ICONSTOP);
   TrackBar2Enter(this);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::BitBtn1Click(TObject *Sender)
{
 // ������������ � �������������� �����
 if (TypeReg==0)
  PostMessage(FindWindow("TFOpros","����� �� ��������� Modbus"),WM_USER+1,IDTAG_MODE,1);
 else ModalResult=0;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::BitBtn2Click(TObject *Sender)
{
 // ������������ � ������ �����
 if (TypeReg==0)
  PostMessage(FindWindow("TFOpros","����� �� ��������� Modbus"),WM_USER+1,IDTAG_MODE,0);
 else ModalResult=0; 
}
//---------------------------------------------------------------------------
void __fastcall TFReg::BitBtn3Click(TObject *Sender)
{
 // ���������� �������
 int newval;
 int id    ;
 if (FModeReg) { newval = FAutoZadReg * 100; id = IDTAG_ZADAUTO; }
 else          { newval = FHandZadReg * 100; id = IDTAG_ZADHAND; }
 PostMessage(FindWindow("TFOpros","����� �� ��������� Modbus"),WM_USER+2,id,newval);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::BitBtn4Click(TObject *Sender)
{
 // ��������� ������������� ����������
 FPassword->Edit1->Text="";
 FPassword->Caption = "������� ������ �������:";
 FPassword->Edit1->PasswordChar = '*';
 if (FPassword->ShowModal()==mrOk)
  {
   if (FPassword->Edit1->Text == Password)
    {
     FEnterKoef->Caption = FReg->Caption + " ������������." ;
     double Val;
     int    Status;
     if (OnGetParam!=NULL)  OnGetParam(this,ID_K1,Val,Status);
     else return;
     if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
     FEnterKoef->StaticText7->Caption  = FormatFloat("###0.00",Val);
     FEnterKoef->Edit1->Text           = FormatFloat("###0.00",Val);
     OnGetParam(this,ID_K2,Val,Status);
     if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
     FEnterKoef->StaticText8->Caption  = FormatFloat("###0.00",Val);
     FEnterKoef->Edit2->Text           = FormatFloat("###0.00",Val);
     OnGetParam(this,ID_K3,Val,Status);
     if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
     FEnterKoef->StaticText9->Caption  = FormatFloat("###0.00",Val);
     FEnterKoef->Edit3->Text           = FormatFloat("###0.00",Val);
     OnGetParam(this,ID_K4,Val,Status);
     if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
     FEnterKoef->StaticText10->Caption = FormatFloat("###0.00",Val);
     FEnterKoef->Edit4->Text           = FormatFloat("###0.00",Val);
     OnGetParam(this,ID_K5,Val,Status);
     if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
     FEnterKoef->StaticText11->Caption = FormatFloat("###0.00",Val);
     FEnterKoef->Edit5->Text           = FormatFloat("###0.00",Val);
     FEnterKoef->id[0] = ID_K1;
     FEnterKoef->id[1] = ID_K2;
     FEnterKoef->id[2] = ID_K3;
     FEnterKoef->id[3] = ID_K4;
     FEnterKoef->id[4] = ID_K5;
     FEnterKoef->type_reg = TypeReg;
     if (TypeReg==0)
      {
       FEnterKoef->StaticText1->Caption = "����������� ������������������:";
       FEnterKoef->StaticText2->Caption = "����� ��������������          :";
       FEnterKoef->StaticText4->Caption = "���� ������������������       :";
       FEnterKoef->StaticText3->Caption = "����� ���� (� ���.)           :";
       FEnterKoef->StaticText6->Caption = "����������� ������� (� ���.)  :";
       FEnterKoef->StaticText22->Visible = false;
       FEnterKoef->StaticText23->Visible = false;
       FEnterKoef->StaticText12->Visible = false;
       FEnterKoef->StaticText13->Visible = false;
       FEnterKoef->Edit6->Visible = false;
       FEnterKoef->Edit7->Visible = false;
       FEnterKoef->BitBtn1->Top = 139;
       FEnterKoef->BitBtn2->Top = 139;
       FEnterKoef->Height       = 191;
      }
     else
      {
       OnGetParam(this,ID_K6,Val,Status);
       if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
       FEnterKoef->StaticText12->Caption = FormatFloat("###0.00",Val);
       FEnterKoef->Edit6->Text           = FormatFloat("###0.00",Val);
       OnGetParam(this,ID_K7,Val,Status);
       if (Status!=0)  Application->MessageBoxA("��� ����� � ������������!","��������!",MB_OK+MB_ICONSTOP);
       FEnterKoef->StaticText13->Caption = FormatFloat("###0.00",Val);
       FEnterKoef->Edit7->Text           = FormatFloat("###0.00",Val);
       FEnterKoef->StaticText1->Caption  = "����� ������� (��)            :";
       FEnterKoef->StaticText2->Caption  = "����������� ��                :";
       FEnterKoef->StaticText4->Caption  = "����������� ������������������:";
       FEnterKoef->StaticText3->Caption  = "����������� ��������������    :";
       FEnterKoef->StaticText6->Caption  = "����������� ����������������� :";
       FEnterKoef->StaticText22->Caption = "����������� ��                :";
       FEnterKoef->StaticText23->Caption = "����� �������� (����)         :";
       FEnterKoef->StaticText22->Visible = true;
       FEnterKoef->StaticText23->Visible = true;
       FEnterKoef->StaticText12->Visible = true;
       FEnterKoef->StaticText13->Visible = true;
       FEnterKoef->Edit6->Visible = true;
       FEnterKoef->Edit7->Visible = true;
       FEnterKoef->BitBtn1->Top = 194;
       FEnterKoef->BitBtn2->Top = 194;
       FEnterKoef->Height       = 247;
       FEnterKoef->id[5] = ID_K6;
       FEnterKoef->id[6] = ID_K7;
      }
     FEnterKoef->ShowModal();
    }
   else
    {
     Application->MessageBoxA("��� ����� �� ��������� ������������� �����������!","��������!",MB_OK+MB_ICONSTOP);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBPlusClick(TObject *Sender)
{
 Mashtab = Mashtab * 2;
 SBMinus->Enabled = true;
 if (Mashtab>1024) { Mashtab=1024;SBPlus->Enabled=false; }
 else
  {
   Trends->LeftAxis->Increment = Trends->LeftAxis->Increment/2;
   Trends->LeftAxis->Minimum   = Trends->LeftAxis->Minimum/2;
   Trends->LeftAxis->Maximum   = Trends->LeftAxis->Maximum/2;
   double shag = (Trends->LeftAxis->Maximum - Trends->LeftAxis->Minimum-10/Mashtab)/100;
   TBValue->Max        = 25 / shag;
   TBValue->Min        = 0;
   TBValue->Frequency  = 5/shag;
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFReg::GetNameEdIzm(int IDTag)
{
 Variant tmp;
 AnsiString Ret="";
 int type_visible=0;
 tmp = QListTags->Lookup("IDTag",IDTag,"TypeVisibleElement");
 if ((tmp.IsEmpty())||(tmp.IsNull()))  type_visible = 0 ;  else  type_visible = tmp;
 if ((type_visible==17)||(type_visible==18))
  { Ret="&�."; } // ++? ������� ��������� ���������� � ����������� �� ������
 else
  {
   tmp=QListTags->Lookup("IDTag",IDTag,"VisParam2");
   if ((!tmp.IsNull())&&(!tmp.IsEmpty())) Ret=tmp;
  }
 return Ret;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBMinusClick(TObject *Sender)
{
 Mashtab = Mashtab / 2;
 SBPlus->Enabled = true;
 if (Mashtab<1) { Mashtab=1;SBMinus->Enabled=false; }
 else
  {
   Trends->LeftAxis->Increment = Trends->LeftAxis->Increment*2;
   Trends->LeftAxis->Maximum   = Trends->LeftAxis->Maximum*2;
   Trends->LeftAxis->Minimum   = Trends->LeftAxis->Minimum*2;
   double shag = (Trends->LeftAxis->Maximum - Trends->LeftAxis->Minimum-10/Mashtab)/100;
   if (shag!=0)
    {
     TBValue->Max        = 25 / shag;
     TBValue->Min        = 0;
     TBValue->Frequency  = 5/shag;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBTagMinusClick(TObject *Sender)
{
 // ���� �����
 TDateTime beg,end;
 beg.Val =  (double)((unsigned long)DTPDate_beginTrend->DateTime.Val) + ((DTPTime_beginTrend->DateTime).Val - (double)((unsigned long)DTPTime_beginTrend->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDate_endTrend->DateTime.Val)   + ((DTPTime_endTrend->DateTime).Val   - (double)((unsigned long)DTPTime_endTrend->DateTime.Val)  );
 beg.Val = beg.Val - 1;
 end.Val = end.Val - 1;
 DTPDate_beginTrend->DateTime = beg;
 DTPTime_beginTrend->DateTime = beg;
 DTPDate_endTrend->DateTime   = end;
 DTPTime_endTrend->DateTime   = end;
 BBBuilderTrendClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBHourMinusClick(TObject *Sender)
{
 // ��� �����
 TDateTime beg,end;
 TTime     tmp=(TTime)"01:00:00";
 beg.Val =  (double)((unsigned long)DTPDate_beginTrend->DateTime.Val) + ((DTPTime_beginTrend->DateTime).Val - (double)((unsigned long)DTPTime_beginTrend->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDate_endTrend->DateTime.Val)   + ((DTPTime_endTrend->DateTime).Val   - (double)((unsigned long)DTPTime_endTrend->DateTime.Val)  );
 beg.Val = beg.Val - tmp.Val;
 end.Val = end.Val - tmp.Val;
 DTPDate_beginTrend->DateTime = beg;
 DTPTime_beginTrend->DateTime = beg;
 DTPDate_endTrend->DateTime   = end;
 DTPTime_endTrend->DateTime   = end;
 BBBuilderTrendClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBHourPlusClick(TObject *Sender)
{
 // ��� �����
 TDateTime beg,end;
 TTime     tmp=(TTime)"01:00:00";
 beg.Val =  (double)((unsigned long)DTPDate_beginTrend->DateTime.Val) + ((DTPTime_beginTrend->DateTime).Val - (double)((unsigned long)DTPTime_beginTrend->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDate_endTrend->DateTime.Val)   + ((DTPTime_endTrend->DateTime).Val   - (double)((unsigned long)DTPTime_endTrend->DateTime.Val)  );
 beg.Val = beg.Val + tmp.Val;
 end.Val = end.Val + tmp.Val;
 DTPDate_beginTrend->DateTime = beg;
 DTPTime_beginTrend->DateTime = beg;
 DTPDate_endTrend->DateTime   = end;
 DTPTime_endTrend->DateTime   = end;
 BBBuilderTrendClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SBTagPlusClick(TObject *Sender)
{
 // ���� �����
 TDateTime beg,end;
 beg.Val =  (double)((unsigned long)DTPDate_beginTrend->DateTime.Val) + ((DTPTime_beginTrend->DateTime).Val - (double)((unsigned long)DTPTime_beginTrend->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDate_endTrend->DateTime.Val)   + ((DTPTime_endTrend->DateTime).Val   - (double)((unsigned long)DTPTime_endTrend->DateTime.Val)  );
 beg.Val = beg.Val + 1;
 end.Val = end.Val + 1;
 DTPDate_beginTrend->DateTime = beg;
 DTPTime_beginTrend->DateTime = beg;
 DTPDate_endTrend->DateTime   = end;
 DTPTime_endTrend->DateTime   = end;
 BBBuilderTrendClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::TBValueChange(TObject *Sender)
{
 if (Mashtab!=0)
  {
   double shag = (Trends->LeftAxis->Maximum - Trends->LeftAxis->Minimum-10/Mashtab)/100;
   try
    {
     Trends->LeftAxis->Minimum = shag * -5  + TBValue->Position*(100-100/Mashtab)/(TBValue->Max-TBValue->Min);
     Trends->LeftAxis->Maximum = shag * 105 + TBValue->Position*(100-100/Mashtab)/(TBValue->Max-TBValue->Min);
    }
   catch (...)
    {
     Trends->LeftAxis->Maximum = shag * 105 + TBValue->Position*(100-100/Mashtab)/(TBValue->Max-TBValue->Min);
     Trends->LeftAxis->Minimum = shag * -5  + TBValue->Position*(100-100/Mashtab)/(TBValue->Max-TBValue->Min);
    }
  }
}
//---------------------------------------------------------------------------
int __fastcall TFReg::RecNo(int IDTag)
{
 for (int pc=0;pc<Trends->SeriesCount();pc++)
  if (IDTags_Trends[pc]==IDTag) return pc;
 return -1;
}
//---------------------------------------------------------------------------

void __fastcall TFReg::TrendsGetAxisLabel(TChartAxis *Sender,
      TChartSeries *Series, int ValueIndex, AnsiString &LabelText)
{
 // ����������� ����� �� �������� ������
 if (QViewData->Active)
  {
   int ind = RecNo(QViewDataIDTag->AsInteger);
   if (ind>=0)
    {
     if (Sender==Trends->LeftAxis)
      {
       try
        {
         double tmp=StrToFloat(LabelText);
         Trends->LeftAxis->Title->Caption = GetNameEdIzm(IDTags_Trends[ind]);
         if ((Shkals_Max[ind]-Shkals_Min[ind])>0) // ������ � ��������������� �������� (% � ��������������� �������)
           tmp = (tmp / 100) * (Shkals_Max[ind]-Shkals_Min[ind])     + Shkals_Min[ind];
         else if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) //  �������� � ���������� �������� (% � ���������� �������)
          {
           tmp = (tmp / 100) * (Shkals_InMax[ind]-Shkals_InMin[ind]) + Shkals_InMin[ind];
          }
         else ; // ��������  � %       LabelText = tmp - ;
         LabelText = FormatFloat(FormatTrend[ind],tmp);
        }
       catch (...) { }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::TrendsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft) MoveVizir=true;
}
//---------------------------------------------------------------------------

void __fastcall TFReg::TrendsMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
 if (MoveVizir)
  {
   if ((X>Trends->Left+20)&&(X<(Trends->Width-Trends->Width*(Trends->MarginRight*0.01)-3)))
    {
     Vizir->Left = X;
     double vx    = Trends->Series[0]->XScreenToValue(X+1);
     TDateTime TD;  TD.Val = vx;
     STTimeTrend->Caption = TD.FormatString("dd.mm.yyyy hh:nn:ss");
     Trends->Refresh();
     DBGridEh6->Refresh();
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::TrendsMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft)  MoveVizir=false;
}
//---------------------------------------------------------------------------

void __fastcall TFReg::TrendsResize(TObject *Sender)
{
 // ��������� ������� ���� � ��������� ������� ��������
 Vizir->Top    = Trends->Height*(Trends->MarginTop*0.01)+Trends->Top+13+(1600-NewSizeWidth)/45;
 Vizir->Height = Trends->Height - Vizir->Top - 50 - 30 - 3 - (1600-NewSizeWidth)/45;
/* Vizir->Top    = Trends->Height*(Trends->MarginTop*0.01)+Trends->Top+3;
 Vizir->Height = Trends->Height - Vizir->Top - 50 - 30 - 3; */
}
//---------------------------------------------------------------------------

void __fastcall TFReg::DBGridEh6DrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
 if ((Column->ID==1)||(Column->ID==2))
  {
   DBGridEh6->Canvas->Brush->Color = clBlack;
   DBGridEh6->Canvas->Font->Color  = (TColor) Column->Field->DataSet->FieldByName("ColorLine")->AsInteger;
  }
 else  if ((Column->ID==3)||(Column->ID==5))
  {
   int IDTag = Column->Field->DataSet->FieldByName("IDTag")->AsInteger;
   try
    {
     TDateTime tmp = (TDateTime)STTimeTrend->Caption;
     if (Arhiv->DataTag[tmp][IDTag].Status==1)
      {
       DBGridEh6->Canvas->Brush->Color = clRed;
       DBGridEh6->Canvas->Font->Color  = clWhite;
      }
     else
      {
       DBGridEh6->Canvas->Brush->Color = clWhite;
       DBGridEh6->Canvas->Font->Color  = clBlack;
      }
    }
   catch (...) { ; }
  }
 else
  {
   DBGridEh6->Canvas->Font->Color = clBlack;
   DBGridEh6->Canvas->Brush->Color = clWhite;
  }
 DBGridEh6->DefaultDrawDataCell(Rect,Column->Field, State);
}
//---------------------------------------------------------------------------
void __fastcall TFReg::DBGridEh6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssDouble)) // ������� �������
  {
    int ind = RecNo(DBGridEh6->DataSource->DataSet->FieldByName("IDTag")->AsInteger);
    if ((ind>=0)&&(ind<Trends->SeriesCount()))
     {
      Trends->Series[ind]->Active = !Trends->Series[ind]->Active;
      QViewData->Requery(TExecuteOptions());
     }

  }
}
//---------------------------------------------------------------------------
__fastcall TFReg::~TFReg(void)
{
 if (ConListTrend->Connected) ConListTrend->Connected   = false;
 if (ConViewData->Connected)  ConViewData->Connected    = false;
 if (ConCheckTrend->Connected) ConCheckTrend->Connected = false;
}
void __fastcall TFReg::QConCheckTrendTDTGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   Text = STTimeTrend->Caption;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFReg::QViewDataIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   if (QListTags->Active)
    {
     Variant tmp;
     tmp = QListTags->Lookup("IDTag",Sender->AsInteger,"CaptionTag");
     if ((tmp.IsNull())||(tmp.IsEmpty())) Text="";
     else Text=tmp;
    }
   else Text="";
  }
}
//---------------------------------------------------------------------------


void __fastcall TFReg::QViewDataValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 // ������� �������� �������
 if (DisplayText)
  {
   int IDTag = Sender->DataSet->FieldByName("IDTag")->AsInteger;
   try
    {
     TDateTime tmp = (TDateTime)STTimeTrend->Caption;
     AnsiString Format="###0.0";
     double val = Arhiv->DataTag[tmp][IDTag].Val;
     int    ind = RecNo(IDTag);
     if (ind>=0)
      {
       if (((Shkals_Max[ind]-Shkals_Min[ind])>0)&&((Shkals_InMax[ind]-Shkals_InMin[ind])>0)) // ���������� �������� � �������� ���������
        {
         val = (val - Shkals_InMin[ind])/(Shkals_InMax[ind]-Shkals_InMin[ind])*(Shkals_Max[ind]-Shkals_Min[ind])+Shkals_Min[ind];
         Format = FormatTrend[ind];
        }
       else Format=FormatTrend[ind];
      }
     Text = FormatFloat(Format,val);
    }
   catch (...) { Text=""; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::QViewDataStatusGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   int IDTag = Sender->DataSet->FieldByName("IDTag")->AsInteger;
   try
    {
     TDateTime tmp = (TDateTime)STTimeTrend->Caption;
     if (Arhiv->DataTag[tmp][IDTag].Status==1) Text="���";
     else                                      Text="��";
    }
   catch (...) { Text=""; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::QViewDataValProcGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 // ���������� �������� �� �����
 if (DisplayText)
  {
   int IDTag = Sender->DataSet->FieldByName("IDTag")->AsInteger;
   TDateTime tmp = (TDateTime)STTimeTrend->Caption;
   try
    {
     int ind = RecNo(IDTag);
     if (ind>=0)
      {
       double val = Arhiv->DataTag[tmp][IDTag].Val;
       if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) // �������� � ���������� �������� ������� � %
         val = (val - Shkals_InMin[ind])/(Shkals_InMax[ind]-Shkals_InMin[ind])*100;
       else if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) // �������� � ����������� �������� ������� � %
         val = (val - Shkals_Min[ind])/(Shkals_Max[ind]-Shkals_Min[ind])*100;
       else  ;// �������� ��� � ���������
       Text = FormatFloat(FormatTrend[ind],val);
      }
     else Text=""; 
    }
   catch (...) { Text=""; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::QViewDataActiveGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (Sender->AsBoolean) Text=" + ";
 else Text = " - ";
}
//---------------------------------------------------------------------------

void __fastcall TFReg::QViewDataTDTGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   Text = STTimeTrend->Caption;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFReg::QViewDataAfterScroll(TDataSet *DataSet)
{
 Trends->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFReg::QViewDataCalcFields(TDataSet *DataSet)
{
 int id = DataSet->FieldByName("IDTag")->AsInteger;
 id = RecNo(id);
 if (id>=0) QViewDataActive->AsBoolean = Trends->Series[id]->Active;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::BBBuilderTrendClick(TObject *Sender)
{
 double min_v,max_v;
 // ������������ ���������� ������
 if (FIDTrends>0)
  {
   int    CountSeries;
   int IDTrend=FIDTrends;
   // 1 - ���������� ���������� �����, ����� �� ��� OY (�����������, ������������ ��������) - � ��� �� ��� Y, ������������ �����
   QViewData->Parameters->ParamByName("IDTrend")->Value = IDTrend;
   if (QViewData->Active) QViewData->Requery(TExecuteOptions());
   else                   QViewData->Open();
   CountSeries=GetCountSeries(IDTrend,&Shkals_Min[0],    &Shkals_Max[0],
                                      &Shkals_InMin[0],  &Shkals_InMax[0],
                                      &IDTags_Trends[0], &ColorTrend[0], &min_v, &max_v);
   if (CountSeries==0)
    { Application->MessageBoxA("�� ������� ������� ��� ����������� �� �������!","��������!",MB_OK+MB_ICONSTOP);SpeedButton3->Down=false;SpeedButton3Click(Sender); }
   else
    {
     if (QListTrend->Locate("IDTrend",IDTrend,TLocateOptions()))
      {
       for (int pc=0;pc<Trends->SeriesCount();pc++)
        Trends->Series[pc]->Active=false;
       for (int pc=Trends->SeriesCount();pc<CountSeries;pc++)
        {
         TLineSeries *Ser;
         Ser = new TLineSeries(Trends);
         Ser->Active = false;
         Trends->AddSeries(Ser);
        }
       for (int pc=0;pc<CountSeries;pc++)
        {
         Trends->Series[pc]->Clear();
         Trends->Series[pc]->Active=false;
         Trends->Series[pc]->XValues->DateTime = true;
        }
       try
        {
         Trends->LeftAxis->Minimum =  -5; //min_v;
         Trends->LeftAxis->Maximum = 105; //max_v;
        }
       catch (...)
        {
         Trends->LeftAxis->Maximum = 105; //max_v;
         Trends->LeftAxis->Minimum =  -5; //min_v;
        }
       Trends->LeftAxis->Title->Caption = GetNameEdIzm(IDTags_Trends[0]); // ������������ ������ ���������
       Trends->LeftAxis->Increment      = 10; //(max_v-min_v)/ 10;
       Trends->LeftAxis->MinorTickCount = 9;
       Trends->Title->Text->Strings[0]  = QListTrendCaptionTrend->AsString.Trim();
       Trends->Series[0]->Active = true;
       // 2 - ���������� �����������, ������������ ����� (����� �� ��� OX) � ��� �� ��� X
       TDateTime beg,end;
       TTime     tmp=(TTime)"00:00:01";
       unsigned int count_point=0;
       beg.Val =  (double)((unsigned long)DTPDate_beginTrend->DateTime.Val) + ((DTPTime_beginTrend->DateTime).Val - (double)((unsigned long)DTPTime_beginTrend->DateTime.Val));
       end.Val =  (double)((unsigned long)DTPDate_endTrend->DateTime.Val)   + ((DTPTime_endTrend->DateTime).Val   - (double)((unsigned long)DTPTime_endTrend->DateTime.Val)  );
       count_point = (end.Val-beg.Val)/tmp.Val;
       Trends->BottomAxis->Increment      = tmp.Val/10;
       Trends->BottomAxis->MinorTickCount = 9;
       Trends->BottomAxis->LabelsMultiLine = true;
       Trends->BottomAxis->DateTimeFormat = "hh:nn:ss dd.mm.yyyy";
       if (beg.Val<Trends->BottomAxis->Maximum)
        {
         Trends->BottomAxis->Minimum = beg.Val;
         Trends->BottomAxis->Maximum = end.Val;
        }
       else
        {
         Trends->BottomAxis->Maximum = end.Val;
         Trends->BottomAxis->Minimum = beg.Val;
        }
       if (count_point>3600/*(Trends->Width-Trends->Width*(Trends->MarginRight*0.01)-3-Trends->Left-60)*/)
        {
         count_point =3600;//(Trends->Width-Trends->Width*(Trends->MarginRight*0.01)-3-Trends->Left-60);
         tmp.Val     =(end.Val-beg.Val)/count_point;
        }
       for (double ft=beg.Val;ft<end.Val;ft=ft+tmp.Val)
        {
         for (int pc=0;pc<CountSeries;pc++)
          {
           double Y = Arhiv->DataTag[ft][IDTags_Trends[pc]].Val;
           if ((Shkals_InMax[pc] - Shkals_InMin[pc])>0) // ������� ���������� ������ � �������� (�������� � ���������� ��������)
            Y = (Y - Shkals_InMin[pc])/(Shkals_InMax[pc]-Shkals_InMin[pc]) * 100;
           else
           if ((Shkals_Max[pc]-Shkals_Min[pc])>0) // ������� �������� � �������� (�������� � ��������������� ��������)
            Y = (Y-Shkals_Min[pc])/(Shkals_Max[pc]-Shkals_Min[pc]) * 100;
           else ; // �������� ��� � % (�������� � ���������)
           Trends->Series[pc]->AddXY(ft,Y,"",(TColor)ColorTrend[pc]);
          }
        }
       if (Mashtab==0)
        {
         Mashtab = 1.0;
         SBPlus->Enabled = true;
         SBMinus->Enabled=false;
         TBValue->Position = 0;
         TBValue->Min      = 0;
         TBValue->Max      =25;
         TBValue->Frequency= 5;
         SpeedButton3Click(Sender);
         TBValueChange(Sender);
        }
       else
        {
         Trends->LeftAxis->Increment = Trends->LeftAxis->Increment/Mashtab;
         Trends->LeftAxis->Minimum   = Trends->LeftAxis->Minimum/Mashtab;
         Trends->LeftAxis->Maximum   = Trends->LeftAxis->Maximum/Mashtab;
         double shag = (Trends->LeftAxis->Maximum - Trends->LeftAxis->Minimum-10/Mashtab)/100;
         TBValue->Max        = 25 / shag;
         TBValue->Min        = 0;
         TBValue->Frequency  = 5/shag;
         TBValueChange(Sender);
        }
       for (int pc=0;pc<CountSeries;pc++) Trends->Series[pc]->Active=true;
       QViewData->Requery(TExecuteOptions());
      }
    }
   Trends->Refresh();
   MoveVizir=true;
   TrendsMouseMove(Sender,TShiftState(),Vizir->Left,Vizir->Top);
   MoveVizir=false;
   DBGridEh6->Refresh();
  }
 else { Application->MessageBoxA("�� ������ ������ ��� �����������!","��������!",MB_OK+MB_ICONSTOP);SpeedButton3->Down=false;SpeedButton3Click(Sender); }
}
//---------------------------------------------------------------------------
int __fastcall TFReg::GetCountSeries(int IDTrends, double *Shkals_min, double *Shkals_max, double *min_insh, double *max_insh, int *IDTags, unsigned int *ColorTrend, double *tmp_min, double *tmp_max)
{
 int ret=0;
 QConCheckTrend->Parameters->ParamByName("IDTrend")->Value = IDTrends;
 if (QConCheckTrend->Active) QConCheckTrend->Requery(TExecuteOptions());
 else                        QConCheckTrend->Open();
 while (!QConCheckTrend->Eof)
  {
   IDTags[ret]     = QConCheckTrendIDTag->AsInteger;
   ColorTrend[ret] = (TColor)QConCheckTrendColorLine->AsInteger;
   if (QListTags->Active)
    {
     Variant tmp;
     tmp = QListTags->Lookup("IDTag",IDTags[ret],"MinVal");
     if ((tmp.IsEmpty())||(tmp.IsNull()))  Shkals_min[ret] = 0 ;  else  Shkals_min[ret] = tmp;
     tmp = QListTags->Lookup("IDTag",IDTags[ret],"MaxVal");
     if ((tmp.IsEmpty())||(tmp.IsNull()))  Shkals_max[ret] = 100;  else  Shkals_max[ret] = tmp;
     tmp = QListTags->Lookup("IDTag",IDTags[ret],"MinValIn");
     if ((tmp.IsEmpty())||(tmp.IsNull()))  min_insh[ret] = 0 ;  else  min_insh[ret] = tmp;
     tmp = QListTags->Lookup("IDTag",IDTags[ret],"MaxValIn");
     if ((tmp.IsEmpty())||(tmp.IsNull()))  max_insh[ret] = 0 ;  else  max_insh[ret] = tmp;
     FormatTrend[ret] = "###0.0";
     int type_visible=0;
     tmp = QListTags->Lookup("IDTag",IDTags[ret],"TypeVisibleElement");
     if ((tmp.IsEmpty())||(tmp.IsNull()))  type_visible = 0 ;  else  type_visible = tmp;
     if ((type_visible==17)||(type_visible==18))
      {
       tmp = QListTags->Lookup("IDTag",IDTags[ret],"VisParam2");
       if ((!tmp.IsEmpty())&&(!tmp.IsNull())) FormatTrend[ret]=tmp;
      }
     else
      {
       tmp = QListTags->Lookup("IDTag",IDTags[ret],"VisParam1");
       if ((!tmp.IsEmpty())&&(!tmp.IsNull())) FormatTrend[ret]=tmp;
       tmp = QListTags->Lookup("IDTag",IDTags[ret],"VisParam2");
       if ((!tmp.IsEmpty())&&(!tmp.IsNull()))
        {
         AnsiString Ed=tmp;
         FormatTrend[ret] = FormatTrend[ret] + " " + Ed;
        }
      }
    }
   else
    {
     min_insh  [ret] =   0;
     max_insh  [ret] =   0;
     Shkals_min[ret] =   0;
     Shkals_max[ret] = 100;
    }
   if (ret==0)
    {
     *tmp_min = Shkals_min[0];
     *tmp_max = Shkals_max[0];
    }
   else
    {
     if (*tmp_min>Shkals_min[ret]) *tmp_min=Shkals_min[ret];
     if (*tmp_max<Shkals_max[ret]) *tmp_max=Shkals_max[ret];
    }
   ret++;
   if (ret>199) return ret;
   QConCheckTrend->Next();
  }
 return ret;
}
//---------------------------------------------------------------------------
void __fastcall TFReg::SpeedButton3Click(TObject *Sender)
{
 if (SpeedButton3->Down) // ���������� �� �������� ����������� � �������� �������
  {
   SBTagMinus->Enabled  =false;
   SBTagPlus->Enabled   =false;
   SBHourMinus->Enabled  =false;
   SBHourPlus->Enabled   =false;
   DTPTime_beginTrend->Enabled = false;
   DTPTime_endTrend->Enabled   = false;
   DTPDate_beginTrend->Enabled = false;
   DTPDate_endTrend->Enabled   = false;
   DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"00:15:00");
   DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"00:15:00");
   DTPTime_endTrend->DateTime   = (TTime)Now();
   DTPDate_endTrend->DateTime   = (TDate)Now();
   BBBuilderTrendClick(this);
  }
 else //
  {
   SBTagMinus->Enabled  =true;
   SBTagPlus->Enabled   =true;
   SBHourMinus->Enabled  =true;
   SBHourPlus->Enabled   =true;
   DTPTime_beginTrend->Enabled = true;
   DTPTime_endTrend->Enabled   = true;
   DTPDate_beginTrend->Enabled = true;
   DTPDate_endTrend->Enabled   = true;
  }
}
//---------------------------------------------------------------------------

