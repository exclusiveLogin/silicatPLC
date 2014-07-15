//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFormKS.h"
#include "FormReg.h"
#include "FormEnterString.h"
#include "FormPuskStop.h"
#include "FormOnOffRezerv.h"
#include "FormEnterShkals.h"
#include "FormEnterUst.h"
#include "FormDiag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma resource "*.dfm"
TFMainForm *FMainForm;
//---------------------------------------------------------------------------
__fastcall TFMainForm::TFMainForm(TComponent* Owner)
        : TForm(Owner)
{
 AnsiString TmpFile      ;
 AnsiString TekDir       ;
 TIniFile   *Ini         ;
 char       NameFile[255];

 // чтение установочного файла
 STTimeTrend->Caption = Now().FormatString("dd.mm.yyyy hh:nn:ss");
 GetCurrentDirectory(255,NameFile);
 Mashtab = 0;
 TekDir    =NameFile;
 TmpFile = (String) NameFile + "\\wmb.ini";
 if (FileExists(TmpFile))
  {
   if ((Ini = new TIniFile(TmpFile))!=NULL)
    {
     Password         = Ini->ReadString("USER","Password","010101");
     Timer2->Interval = Ini->ReadInteger("DISK","Timer",3600000);
     FreeKBytes       = Ini->ReadInteger("DISK","Free",524288000);
     ModeApp          = Ini->ReadInteger("DISK","NotShow",0);
     NewSizeWidth     = Ini->ReadInteger("SCREEN","Width",1600);
     TekDir           = Ini->ReadString("DISK","CurrenDIR","D:\\Программа");
     Lic              = Ini->ReadInteger("USER","Lic",1000)                ;
     SetCurrentDir(TekDir);

     FMainForm->ScaleBy(NewSizeWidth,1600);

     delete Ini;
    }
   else Password="010101";
  }
 else Password="010101";
 if (ModeApp==0) // запустить опрос, спрятать кнопки управления
  {
   TBorderIcons tempBI = BorderIcons;
   tempBI >> biSystemMenu >> biMinimize >> biMaximize;
   BorderIcons = tempBI;
   WindowState = wsMaximized;
   if (FindWindow("TFOpros","Опрос по протоколу Modbus")==NULL) WinExec("opros.exe",SW_RESTORE);
  }
 if (!QListTags->Active) QListTags->Open();
 if (!QFiltr->Active)    QFiltr->Open()   ;
 // построение списка объектов и формировании таблицы фильтрации
 CLBFS->Items->Clear();
 int ind=0;
 int CountArhivTag = 0;
 while (!QListTags->Eof)
  {
   if (QFiltr->Locate("IDTag",QListTagsIDTag->AsInteger,TLocateOptions())) QFiltr->Edit();
   else                                                                    QFiltr->Insert();
   if (QListTagsIDTag->AsInteger<10000) CountArhivTag++;
   QFiltrIDRec->AsInteger     = QListTagsIDTag->AsInteger;
   QFiltrIDTag->AsInteger     = QListTagsIDTag->AsInteger;
   QFiltrActive->AsBoolean    = false;
   QFiltrTypeFiltr->AsInteger = QListTagsTypeArhiv->AsInteger;
   if (QListTagsTypeArhiv->AsInteger==1)
    {
     ind++;QFiltrIndexInList->AsInteger = ind;
    }
   else QFiltrIndexInList->AsInteger = -1;
   QFiltr->Post();
   if (QListTagsTypeArhiv->AsInteger==1) CLBFS->Items->Add(QListTagsCaptionTag->AsString.Trim());
   QListTags->Next();
  }
 DTPTime_begin->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDate_begin->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTime_end->DateTime   = (TTime)Now();
 DTPDate_end->DateTime   = (TDate)Now();
 DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTime_endTrend->DateTime   = (TTime)Now();
 DTPDate_endTrend->DateTime   = (TDate)Now();
 DTPTimeBegin->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDateBegin->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTimeEnd->DateTime   = (TTime)Now();
 DTPDateEnd->DateTime   = (TDate)Now();
 Arhiv = new MyArhiv(this,Lic,1000);
 TDateTime t1 = (TDateTime)"20.05.2013 11:06:00";
 TDateTime t2 = (TDateTime)"20.05.2013 11:07:00";
 int ls=0;
 for (double t=t1.Val;t<t2.Val;t=t+(TTime)"00:00:01")
  {
   double k=Arhiv->DataTag[t][1].Val;
   ls++;
   k++;
  }
 SetShagArhiv();
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::TrackBar1Change(TObject *Sender)
{
 // определение даты архива
 TDateTime beg;
 TTime     sec = (TTime)"00:00:01";
 beg.Val =  (double)((unsigned long)DTPDateBegin->DateTime.Val) + ((DTPTimeBegin->DateTime).Val - (double)((unsigned long)DTPTimeBegin->DateTime.Val));
 DateArhiv.Val = beg.Val + TrackBar1->Position * sec.Val;
 PLUS_COUNT = true;
 Timer1Timer(Sender);
 PLUS_COUNT = false;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::SetShagArhiv(void)
{
 // установить сетку архива
 // расчёт количества точек архивных данных
 TTime shag= (TTime)"00:00:01";
 TDateTime beg,end;
 beg.Val =  (double)((unsigned long)DTPDateBegin->DateTime.Val) + ((DTPTimeBegin->DateTime).Val - (double)((unsigned long)DTPTimeBegin->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDateEnd->DateTime.Val)   + ((DTPTimeEnd->DateTime).Val   - (double)((unsigned long)DTPTimeEnd->DateTime.Val)  );
 double t1 = (end.Val - beg.Val)/shag.Val;
 if (t1>10000000) { Application->MessageBoxA("Указан слишком большой временной интервал","Внимание!",MB_OK+MB_ICONSTOP);return; }
 else
  {
   TrackBar1->Min =  0;
   TrackBar1->Max = t1;
   TrackBar1->Position = 0;
   TrackBar1Change(this);
   t1 = t1 / 5000;
   if (t1<1) t1=1;
   TrackBar1->Frequency = t1;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn3Click(TObject *Sender)
{
 // показать архив
 SetShagArhiv();
 Panel69->Visible = false;
 PListArhiv->Align = alClient;
 SpeedButton2->Down = false;
 BitBtn2->Visible = true   ;
 PListArhiv->Visible=true;
 TrackBar1Change(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn4Click(TObject *Sender)
{
 Panel69->Visible = false;
 BitBtn2->Visible = true   ;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn2Click(TObject *Sender)
{
 // выбор дат архива
 Panel69->Align   = alClient;
 PListArhiv->Visible = false;
 BitBtn2->Visible = false   ;
 Panel69->Visible = true    ;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::SpeedButton2Click(TObject *Sender)
{
 if (SpeedButton2->Down) // текущие даные
  {
   PListArhiv->Visible=false;
  }
 else  // архивные данные
  {
   PListArhiv->Align = alClient;
   PListArhiv->Visible=true;
   TrackBar1Change(Sender);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Timer1Timer(TObject *Sender)
{
 // отображение текущих данных
 static unsigned int count=0;
 static unsigned int check_exec=0;
 double      val;
 TImage      *TmpImage;
 TControl    *TmpCont;
 TStaticText *TmpStaticText;
 TLabel      *TmpLabel;
 TShape      *TmpShape;
 TCGauge     *TmpCGauge;
 TStaticText *Por1,*Por2,*Otkaz;
 TPanel      *TmpPanel ;
 unsigned long ret ;
 unsigned long ret1;
 static int kr=0;
 kr++;
 if (kr==20)
  {
   if (CheckPravInitShkals()) Button5->Visible=true;
   else Button5->Visible=false;
   kr=0;
  }
// int l=1;
 check_exec++;
 if (check_exec>10)
  {
   if (!ModeApp)
    if (FindWindow("TFOpros","Опрос по протоколу Modbus")==NULL) WinExec("opros.exe",SW_RESTORE);
   check_exec=0;
  }
 if (PageControl1->ActivePageIndex==NumPageTrends)
  {
   if (SpeedButton3->Down)
    {
     Timer1->Enabled = false;
     DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"00:15:00");
     DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"00:15:00");
     DTPTime_endTrend->DateTime   = (TTime)Now();
     DTPDate_endTrend->DateTime   = (TDate)Now();
     BBBuilderTrendClick(this);
     Timer1->Enabled = true;
    }
  }
 else if (PageControl1->ActivePageIndex==NumPageArhivSob)
  {
   Timer1->Enabled=false;
   try
    {
     if (SpeedButton1->Down)
      {
       if (QActiveSob->Active) QActiveSob->Requery(TExecuteOptions());
       if (QListSob->Active)
        {
         BBLastHourClick(Sender);
         BitBtn12Click(Sender);
        }
      }
    }
   catch (...) { }
   Timer1->Enabled=true;
  }
 else if ((PageControl1->ActivePageIndex>=0)&&(PageControl1->ActivePageIndex<=4)) // отображение активных данных
  {
   if (QListTags->Active) QListTags->Requery(TExecuteOptions());
   else                   QListTags->Open();
   int NumAct=0;
   switch (PageControl1->ActivePageIndex)
    {
     case 0: NumAct=1; break;
     case 1: NumAct=2; break;
     case 2: NumAct=4; break;
     case 3: NumAct=8; break;
     case 4: NumAct=16;break;
    }
   if (!PLUS_COUNT) count++;
   vismig = (count%4)<2;
   QListTags->First();
   MigEkran = 0;
   bool yes_data=true;
   while (!QListTags->Eof)
    {
     double MyValTags     = QListTagsValueTag->AsFloat   ;
     int    MyStatusTags  = QListTagsStatusTag->AsInteger;
     if (QListTagsIDTag->AsInteger==138)
      int d1111=0;
     if (!SpeedButton2->Down)
      {
         MyValTags = Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].Val;MyStatusTags =Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].Status;
         if (QListTagsIDTag->AsInteger==1001)
          {
           int l=0;
          }
         if (QListTagsIDTag->AsInteger<10000)   yes_data  = Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].YesData;
         if (!yes_data)
          int l= QListTagsIDTag->AsInteger;
      }
     if ((QListTagsNumEkran->AsInteger&NumAct)==NumAct)
      {
       TmpCont = (TControl *)FindComponent(QListTagsNameTag->AsString.Trim()+"_E"+IntToStr(PageControl1->ActivePageIndex+1));
       if (TmpCont!=NULL)
        {
         TmpCont->ShowHint = true;
         TmpCont->Hint = QListTagsCaptionTag->AsString;
         int Code=0,avco=0;          AnsiString T1="";
         switch (QListTagsTypeVisibleElement->AsInteger)
          {
           case 20: TmpLabel = (TLabel *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpLabel->Visible = false;
                     }
                    else
                     {
                       TmpLabel->Visible = true;
                       if ((int)MyValTags==1) TmpLabel->Font->Color = clInactiveCaption;
                       else                   TmpLabel->Font->Color = clRed;
                     }
                    break;
           case 19: // код ошибки
                    TmpLabel = (TLabel *)TmpCont;
                    TmpLabel->Color = clWhite;
                    if (MyStatusTags==1)
                     {
                      TmpLabel->Font->Color=clRed;
                      TmpLabel->Caption    ="Нет связи";
                     }
                    else
                     {
                      TmpLabel->Font->Color = clInactiveCaption;
                      TmpLabel->Caption    ="Нет связи";
                      /*
                      switch ((int)MyValTags)
                       {
                        case 0 : TmpLabel->Font->Color=clBlack ; TmpLabel->Caption="";break;
                        default: TmpLabel->Font->Color=clBlack ; TmpLabel->Caption="Код ошибки:" + IntToStr((int)MyValTags); break;
                       } */
                     }
                    break;
           case 18: // отображение этапа
                    TmpLabel = (TLabel *)TmpCont;
                    switch ((int)MyValTags)
                     {
                      case 0 : Code=13;break;
                      case 1 : Code=14;break;
                      case 10: Code= 1;break;
                      case 12: Code= 2;break;
                      case 20:
                      case 21: Code= 3;break;
                      case 22: Code= 4;break;
                      case 24: Code= 5;break;
                      case 30:
                      case 31:
                      case 32:
                      case 33:
                      case 34: Code= 6;break;
                      case 36: Code=15;break;
                      case 38: Code= 7;break;
                      case 40:
                      case 42:
                      case 50:
                      case 52:
                      case 54:
                      case 44: Code= 8;break;
                      case 60: Code= 9;break;
                      case 62: Code=16;break;
                      case 70: Code=10;break;
                      case 72:
                      case 75:
                      case 76:
                      case 77:
                      case 78:
                      case 74: Code=11;break;
                      case 79:
                      case 80:
                      case 81:
                      case 82:
                      case 83: Code=12;break;
                     }
                    for (int i=1;i<16;i++)
                     {
                      TmpLabel = (TLabel *)FindComponent("L"+IntToStr(i)+"_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL) TmpLabel->Font->Color = clInactiveCaption;
                     }
                    TmpLabel = (TLabel *)FindComponent("L"+IntToStr(Code)+"_E"+IntToStr(PageControl1->ActivePageIndex+1));
                    if (TmpLabel!=NULL)
                     {
                       if ((int)MyValTags==1) TmpLabel->Font->Color = clInactiveCaption;
                       else                   TmpLabel->Font->Color = clGreen;
                     }
                    break;
           case  1: // дискретный сигнал 0 - элемент не виден, 1 - элемент виден если нет связи мигает
                    if (MyStatusTags==1)
                     {
                      TmpCont->Visible = (count%4)<2 ;
                     }
                    else
                    if (MyValTags==1)
                     {
                      if (!TmpCont->Visible) TmpCont->Visible=true; // без мигания
                     }
                    else
                     { if (TmpCont->Visible) TmpCont->Visible=false; }
                    break;
           case  2: // аналоговый сигнал с переносом единиц измерения
           case  3: // аналоговый сигнал без переноса единиц измерения
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      if (QListTagsTypeVisibleElement->AsInteger==2) TmpStaticText->Caption = " \r"+QListTagsVisParam2->AsString;
                      else                                           TmpStaticText->Caption = QListTagsVisParam2->AsString;
                     }
                    else
                     {
                      val = MyValTags;
                      if (QListTagsTypeValue->AsInteger==1)
                       {
                        if ( ((QListTagsMaxValIn->AsFloat-QListTagsMinValIn->AsFloat)>0) &&
                             ((QListTagsMaxVal->AsFloat-QListTagsMinVal->AsFloat)>0) )
                         val =  (val-QListTagsMinValIn->AsFloat) * (QListTagsMaxVal->AsFloat-QListTagsMinVal->AsFloat)/(QListTagsMaxValIn->AsFloat-QListTagsMinValIn->AsFloat) + QListTagsMinVal->AsFloat;
                       }
                      if (QListTagsTypeVisibleElement->AsInteger==2) TmpStaticText->Caption = FormatFloat(QListTagsVisParam1->AsString.Trim(),val) + "\r" + QListTagsVisParam2->AsString;
                      else                                           TmpStaticText->Caption = FormatFloat(QListTagsVisParam1->AsString.Trim(),val) + " " + QListTagsVisParam2->AsString ;
                     }
                    break;
           case  4: // дискретный сигнал 1 - элемент не виден, 0 - элемент виден если нет связи мигает
                    if (MyStatusTags==1)
                     {
                      TmpCont->Visible = (count%4)<2 ;
                     }
                    else
                    if (MyValTags==0)
                     {
                      if (TmpCont->Visible) TmpCont->Visible=false; // без мигания
                     }
                    else
                     { if (!TmpCont->Visible) TmpCont->Visible=true; }
                    break;
           case  5: // вывод уровня по дискретному сигналу
                    TmpCGauge = (TCGauge *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      if (TmpCGauge->Visible) TmpCGauge->Visible=false;
                     }
                    else
                     {
                      if (!TmpCGauge->Visible) TmpCGauge->Visible=true;
                      if (MyValTags==1) // уровень в баке высокий
                       {
                        TmpCGauge->Progress =  100;
                        TmpCGauge->ForeColor=clRed;
                       }
                      else  // уровень в  баке низкий
                       {
                        TmpCGauge->Progress =   10;
                        TmpCGauge->ForeColor=clGreen;
                       }
                     }
                    break;
           case  6: // отображение надписи зелёным цветом (дискретный сигнал)
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1) // ошибка чтения
                     {
                      TmpStaticText->Visible=false;
                     }
                    else
                     {
                      TmpStaticText->Visible=true;
                      if (MyValTags==0) TmpStaticText->Font->Color = clSilver;
                      else              TmpStaticText->Font->Color = clGreen ;
                     }
                    break;
           case  7: // отображение надписи оранжевым цветом (дискретный сигнал)
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1) // ошибка чтения
                     {
                      TmpStaticText->Visible=false;
                     }
                    else
                     {
                      TmpStaticText->Visible=true;
                      if (MyValTags==0) TmpStaticText->Font->Color = clSilver;
                      else              TmpStaticText->Font->Color = (TColor)0x000080FF;
                     }
                    break;
           case  8: // аналоговый сигнал для уровня
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpStaticText->Caption = " \r"+QListTagsVisParam2->AsString;
                      TmpCGauge = (TCGauge *)FindComponent(QListTagsNameTag->AsString.Trim()+"L_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpCGauge!=NULL)
                       TmpCGauge->Progress = 0;
                     }
                    else
                     {
                     if ( ((QListTagsMaxValIn->AsFloat-QListTagsMinValIn->AsFloat)>0) &&
                          ((QListTagsMaxVal->AsFloat-QListTagsMinVal->AsFloat)>0) )
                         MyValTags =  (MyValTags-QListTagsMinValIn->AsFloat) * (QListTagsMaxVal->AsFloat-QListTagsMinVal->AsFloat)/(QListTagsMaxValIn->AsFloat-QListTagsMinValIn->AsFloat) + QListTagsMinVal->AsFloat;
                      TmpStaticText->Caption = FormatFloat(QListTagsVisParam1->AsString.Trim(),MyValTags) + "\r" + QListTagsVisParam2->AsString;
                      TmpCGauge = (TCGauge *)FindComponent(QListTagsNameTag->AsString.Trim()+"L_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpCGauge!=NULL)
                       {
                        if (QListTagsMaxVal->AsFloat>0)  TmpCGauge->MaxValue = QListTagsMaxVal->AsFloat;
                        if ((MyValTags>=0)&&(MyValTags<=TmpCGauge->MaxValue))
                         {
                           TmpCGauge->Progress = MyValTags;
                         }
                        else if (MyValTags<0) TmpCGauge->Progress = 0;
                        else                  TmpCGauge->Progress = TmpCGauge->MaxValue;
                       }
                     }
                    break;
           case  9: // картинка АВО
                    TmpImage = (TImage *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      if (TmpImage->Visible) TmpImage->Visible=false;
                     }
                    else
                     {
                      if (!TmpImage->Visible) TmpImage->Visible=true;
                        if (MyValTags==1) TmpImage->Picture->LoadFromFile("avo_on.bmp");
                        else                                 TmpImage->Picture->LoadFromFile("avo_off.bmp");
                     }
                    break;
           case 10: // отображение горизонтального клапана по двум дискретным сигналам
           case 21: // отображение вертикального клапана по двум дискретным сигналам
           case 22: // отображение трехходового клапана по двум дискретным сигналам
                    TmpImage = (TImage *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpImage->Visible= (count%4)<2;
                     }
                    else
                     {
                      if (!TmpImage->Visible) TmpImage->Visible=true;
                      if (MyValTags==0)
                       if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1) // открыт
                        switch (QListTagsTypeVisibleElement->AsInteger)
                         {
                          case 10: TmpImage->Picture->LoadFromFile("klapnetopen.bmp");break;
                          case 21: TmpImage->Picture->LoadFromFile("vklapnetopen.bmp");break;
                          case 22: TmpImage->Picture->LoadFromFile("klapmg.bmp");break;
                         }
                       else // промежуточное положение - нет сигналов
                       switch (QListTagsTypeVisibleElement->AsInteger)
                        {
                         case 10: TmpImage->Picture->LoadFromFile("klapnet.bmp");break;
                         case 21: TmpImage->Picture->LoadFromFile("vklapnet.bmp");break;
                         case 22: TmpImage->Picture->LoadFromFile("klapms.bmp");break;
                        }
                      else
                       if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1) // ошибочное состояние клапана
                        TmpImage->Visible = (count%4)<2 ;
                       else // закрыт
                        {
                         switch (QListTagsTypeVisibleElement->AsInteger)
                          {
                           case 10: TmpImage->Picture->LoadFromFile("klapnetclose.bmp");break;
                           case 21: TmpImage->Picture->LoadFromFile("vklapnetclose.bmp");break;
                           case 22: TmpImage->Picture->LoadFromFile("klapmr.bmp");break;
                          }
                        }
                     }
                    break;
           case 11: // картинка клапана горизонтальная
                    TmpImage = (TImage *)TmpCont;
                    if (MyStatusTags==1) TmpCont->Visible = (count%4)<2 ;
                    else
                     {
                      if (!TmpCont->Visible) TmpCont->Visible=true;
                      if (MyValTags==0) // Задвижка закрыта
                       TmpImage->Picture->LoadFromFile("KlapRed.bmp");
                      else if (MyValTags==1) // Задвижка открыта
                       TmpImage->Picture->LoadFromFile("KlapGreen.bmp");
                      else TmpImage->Picture->LoadFromFile("KlapSer.bmp");
                     }
                    break;
           case 14: // картинка клапана вертикальная
                    TmpImage = (TImage *)TmpCont;
                    if (MyStatusTags==1) TmpCont->Visible = (count%4)<2 ;
                    else
                     {
                      if (!TmpCont->Visible) TmpCont->Visible=true;
                      if (MyValTags==0) // Задвижка закрыта
                       TmpImage->Picture->LoadFromFile("KlapRedV.bmp");
                      else if (MyValTags==1) // Задвижка открыта
                       TmpImage->Picture->LoadFromFile("KlapGreenV.bmp");
                      else TmpImage->Picture->LoadFromFile("KlapSerV.bmp");
                     }
                    break;
           case 112:// уровень по двум дискретным сигналам в предположении что среднего нет
                    TmpCGauge = (TCGauge *)TmpCont;
                    if ((MyStatusTags==1)||(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==2)||(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==2))
                     {
                      if (TmpCGauge->Visible)
                       {
                        TmpCGauge->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Mid_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Min_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                       }
                     }
                    else
                     {
                      if (!TmpCGauge->Visible) TmpCGauge->Visible=true;
                      avco=1; // предполагаем что есть сигналы неправильные
                      T1=QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1);
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (MyValTags==0) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Mid_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (0==MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Min_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (0==MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==0))      avco=0; // нет ничего
                      else if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний
                      else if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний средний
                      else if ((MyValTags==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний средний верхний
                      else if ((MyValTags==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний верхний
                      if (avco==1) // неправильный уровень
                       {
                        TmpCGauge->Progress =       100;
                        TmpCGauge->ForeColor= clFuchsia;
                       }
                      else
                      if (MyValTags==1) // уровень в баке высокий
                       {
                        TmpCGauge->Progress =   90;
                        TmpCGauge->ForeColor=clRed;
                       }
                      else if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1) // уровень в  баке средний
                       {
                        TmpCGauge->Progress =   60;
                        TmpCGauge->ForeColor=clGreen;
                       }
                      else if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1) // уровень в  баке низкий
                       {
                        TmpCGauge->Progress =      50; // 10;
                        TmpCGauge->ForeColor= clGreen; // clYellow;
                       }
                      else
                       {
                        TmpCGauge->Progress =      10;//0;
                        TmpCGauge->ForeColor=clYellow;
                       }
                     }
                    break;
           case 12: // уровень по трем дискретным сигналам
                    TmpCGauge = (TCGauge *)TmpCont;
                    if ((MyStatusTags==1)||(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==2)||(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==2))
                     {
                      if (TmpCGauge->Visible)
                       {
                        TmpCGauge->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Mid_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                        TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Min_E"+IntToStr(PageControl1->ActivePageIndex+1));
                        if (TmpLabel!=NULL) TmpLabel->Visible=false;
                       }
                     }
                    else
                     {
                      if (!TmpCGauge->Visible) TmpCGauge->Visible=true;
                      avco=1; // предполагаем что есть сигналы неправильные
                      T1=QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1);
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Max_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (MyValTags==0) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Mid_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (0==MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      TmpLabel=(TLabel *)FindComponent(QListTagsNameTag->AsString.Trim()+"_Min_E"+IntToStr(PageControl1->ActivePageIndex+1));
                      if (TmpLabel!=NULL)
                       if (0==MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]) TmpLabel->Visible=false; else TmpLabel->Visible=true;
                      if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==0))      avco=0; // нет ничего
                      else if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний
                      else if ((MyValTags==0)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний средний
                      else if ((MyValTags==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1)&&(MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1)) avco=0; // нижний средний верхний
                      if (avco==1) // неправильный уровень
                       {
                        TmpCGauge->Progress =       100;
                        TmpCGauge->ForeColor= clFuchsia;
                       }
                      else
                      if (MyValTags==1) // уровень в баке высокий
                       {
                        TmpCGauge->Progress =   90;
                        TmpCGauge->ForeColor=clRed;
                       }
                      else if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-1]==1) // уровень в  баке средний
                       {
                        TmpCGauge->Progress =   60;
                        TmpCGauge->ForeColor=clGreen;
                       }
                      else if (MasBits[PageControl1->ActivePageIndex][StrToInt(QListTagsVisParam1->AsString.Trim())-2]==1) // уровень в  баке низкий
                       {
                        TmpCGauge->Progress =   10;
                        TmpCGauge->ForeColor=clYellow;
                       }
                      else
                       {
                        TmpCGauge->Progress =      0;
                        TmpCGauge->ForeColor=clYellow;
                       }
                     }
                    break;
           case 13: // Дискретный сигнал 0 - красный, 1 - зелёный. Если нет связи то красный
                    TmpShape = (TShape *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpShape->Brush->Color = clWhite;
                      TmpShape->Pen->Color   = clWhite;
                      TmpShape->Visible = (count%4)<2 ;
                     }
                    else
                     {
                      TmpShape->Visible = true;
                      if (MyValTags==1)
                       { TmpShape->Brush->Color = clLime;TmpShape->Pen->Color   = clLime; }
                      else
                       { TmpShape->Brush->Color = clRed ;TmpShape->Pen->Color   = clRed; }
                     }
                    break;
           case  15: // отображение надписи красным цветом (дискретный сигнал)
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1) // ошибка чтения
                     {
                      TmpStaticText->Visible=false;
                     }
                    else
                     {
                      TmpStaticText->Visible=true;
                      if (MyValTags==0) TmpStaticText->Font->Color = clSilver;
                      else              TmpStaticText->Font->Color = clRed;
                     }
                    break;
           case 16: // режим регулятора
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpStaticText->Caption     = "???";
                      TmpStaticText->Color       = clRed;
                      TmpStaticText->Font->Color = clWhite;
                     }
                    else
                     {
                      if (MyValTags==1)
                       {
                        TmpStaticText->Caption     = "АВТ";
                        TmpStaticText->Color       = clBlack;
                        TmpStaticText->Font->Color = clLime;
                       }
                      else
                       {
                        TmpStaticText->Caption     = "РУЧ";
                        TmpStaticText->Color       = clBlack;
                        TmpStaticText->Font->Color = clWhite;
                       }
                     }
                    break;
           case 17: // задание в ручном режиме
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1)     TmpStaticText->Caption = "   ";
                    else                     TmpStaticText->Caption = FormatFloat(QListTagsVisParam1->AsString,MyValTags);
                    TmpStaticText->Font->Color = clYellow;
                    break;
           case 23: // отображение сигнализации
                    TmpLabel = (TLabel *)TmpCont;
                    if (MyValTags==1) // красный фон, цвет текста белый
                     {
                      TmpLabel->Color       = clYellow;
                      TmpLabel->Font->Color = clRed;
                     }
                    else // отображение как обычно
                     {
                      TmpLabel->Color       = clSilver;
                      TmpLabel->Font->Color = clBlack;
                     }
                    if (MyStatusTags==1) // мигание
                     TmpLabel->Visible = (count%2)==1 ;
                    else  TmpLabel->Visible     = true;
                    break;
           case 24: // отображение неисправностей
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags!=0)
                     {
                       TmpStaticText->Visible=(count%2)==1;
                     }
                    else
                     {
                      if (MyValTags!=0) TmpStaticText->Visible=true;
                      else              TmpStaticText->Visible=false;
                     }
                    break;
          }
        }
       else // нет визуального элемента
        {
         switch (QListTagsTypeVisibleElement->AsInteger)
          {
           case -1: // сохранение параметра в ОП
                    if (MyStatusTags==0)
                     {
                      MasBits[0][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[1][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[2][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[3][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                     }
                    break;
           case -2: // сохранение параметра в ОП
                    if (MyStatusTags==0)
                     {
                      MasBits[0][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[1][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[2][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                      MasBits[3][StrToInt(QListTagsVisParam1->AsString.Trim())]=MyValTags;
                     }
                    else
                     {
                      MasBits[0][StrToInt(QListTagsVisParam1->AsString.Trim())]=2;
                      MasBits[1][StrToInt(QListTagsVisParam1->AsString.Trim())]=2;
                      MasBits[2][StrToInt(QListTagsVisParam1->AsString.Trim())]=2;
                      MasBits[3][StrToInt(QListTagsVisParam1->AsString.Trim())]=2;
                     }
                    break;
          }
        }
      }
     else //  проверка мигания на не активных экранах
      {
       for (int ne=1;ne<4;ne++)
        {
         int codekr;
         switch (ne)
          {
           case 1: codekr=1 ;break;
           case 2: codekr=2 ;break;
           case 3: codekr=4 ;break;
           case 4: codekr=8 ;break;
           case 5: codekr=16;break;
          }
         if  ((QListTagsNumEkran->AsInteger&codekr)==codekr)
          {
            TmpCont = (TControl *)FindComponent(QListTagsNameTag->AsString.Trim()+"_E"+IntToStr(ne));
            if (TmpCont!=NULL)
             {
              switch (QListTagsTypeVisibleElement->AsInteger)
               {
                case  1: // дискретный сигнал 0 - элемент не виден, 1 - элемент виден если нет связи мигает
                         break;
               }
             }
            else // нет визуального элемента
             {
             }
          }
        }
      }
     QListTags->Next();
    }
   // unsigned long tmp=0,tmp1=0,tmp2=0;
   TDateTime TempDT = Now();
   switch (PageControl1->ActivePageIndex)
    {
     case 4:
             if (SpeedButton2->Down)
              {
               Time_E5->Color =  clSilver;
               Time_E5->Font->Color = clBlack;
               Time_E5->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText50->Visible = false;
              }
             else
              {
                if (!yes_data)
                 {
                  Time_E5->Color = clRed;
                  Time_E5->Font->Color = clWhite;
                 }
                else
                 {
                  Time_E5->Color = clSilver;
                  Time_E5->Font->Color = clBlack;
                 }
               TempDT = DateArhiv;
               Time_E5->Caption      = DateArhiv.FormatString("dd.mm.yyyy hh:mm:ss");
               StaticText50->Visible = (count%4)<2 ;
              }
             break;
     case 3:
             if (SpeedButton2->Down)
              {
               Time_E4->Color =  clSilver;
               Time_E4->Font->Color = clBlack;
               Time_E4->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText49->Visible = false;
              }
             else
              {
                if (!yes_data)
                 {
                  Time_E4->Color = clRed;
                  Time_E4->Font->Color = clWhite;
                 }
                else
                 {
                  Time_E4->Color = clSilver;
                  Time_E4->Font->Color = clBlack;
                 }
               TempDT = DateArhiv;
               Time_E4->Caption      = DateArhiv.FormatString("dd.mm.yyyy hh:mm:ss");
               StaticText49->Visible = (count%4)<2 ;
              }
             break;
     case 2: // вывод сложных элементов
             if (SpeedButton2->Down)
              {
               Time_E3->Color =  clSilver;
               Time_E3->Font->Color = clBlack;
               Time_E3->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText42->Visible = false;
              }
             else
              {
                if (!yes_data)
                 {
                  Time_E3->Color = clRed;
                  Time_E3->Font->Color = clWhite;
                 }
                else
                 {
                  Time_E3->Color = clSilver;
                  Time_E3->Font->Color = clBlack;
                 }
               TempDT = DateArhiv;
               Time_E3->Caption      = DateArhiv.FormatString("dd.mm.yyyy hh:mm:ss");
               StaticText42->Visible = (count%4)<2 ;
              }
             break;
     case 1: // вывод сложных элементов
             if (SpeedButton2->Down)
              {
               Time_E2->Color =  clSilver;
               Time_E2->Font->Color = clBlack;
               Time_E2->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText26->Visible = false;
              }
             else
              {
                if (!yes_data)
                 {
                  Time_E2->Color = clRed;
                  Time_E2->Font->Color = clWhite;
                 }
                else
                 {
                  Time_E2->Color = clSilver;
                  Time_E2->Font->Color = clBlack;
                 }
               TempDT = DateArhiv;
               Time_E2->Caption      = DateArhiv.FormatString("dd.mm.yyyy hh:mm:ss");
               StaticText26->Visible = (count%4)<2 ;
              }
             break;
     case 0: // вывод сложных элементов
/*             if ((DI_09_E1->Visible)&&(!DI_08_E1->Visible))       { CGDI8_DI9->Progress = 70;CGDI8_DI9->ForeColor=clYellow;  }
             else if ((!DI_09_E1->Visible)&&(DI_08_E1->Visible))  { CGDI8_DI9->Progress = 35;CGDI8_DI9->ForeColor=clYellow;}
             else if ((!DI_09_E1->Visible)&&(!DI_08_E1->Visible)) { CGDI8_DI9->Progress = 50;CGDI8_DI9->ForeColor=clGreen;}
             else { CGDI8_DI9->Progress = 100;CGDI8_DI9->ForeColor=clRed;}
             if ((DI_03_E1->Visible)&&(!DI_02_E1->Visible))       { CGDI02_DI03->Progress = 70;CGDI02_DI03->ForeColor=clYellow;  }
             else if ((!DI_03_E1->Visible)&&(DI_02_E1->Visible))  { CGDI02_DI03->Progress = 35;CGDI02_DI03->ForeColor=clYellow;}
             else if ((!DI_03_E1->Visible)&&(!DI_02_E1->Visible)) { CGDI02_DI03->Progress = 50;CGDI02_DI03->ForeColor=clGreen;}
             else { CGDI02_DI03->Progress = 100;CGDI02_DI03->ForeColor=clRed;}
             if       ((DI_34_E1->Visible)&&(!DI_33_E1->Visible)) { CGDI33_DI34->Progress = 70;CGDI33_DI34->ForeColor=clYellow;  }
             else if ((!DI_34_E1->Visible)&&(DI_33_E1->Visible))  { CGDI33_DI34->Progress = 35;CGDI33_DI34->ForeColor=clYellow;}
             else if ((!DI_34_E1->Visible)&&(!DI_33_E1->Visible)) { CGDI33_DI34->Progress = 50;CGDI33_DI34->ForeColor=clGreen;}
             else { CGDI33_DI34->Progress = 100;CGDI33_DI34->ForeColor=clRed;} */
             // Вывод времени
             if (SpeedButton2->Down)
              {
               Time_E1->Color =  clSilver;
               Time_E1->Font->Color = clBlack;
               Time_E1->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText40->Visible = false;
              }
             else
              {
                if (!yes_data)
                 {
                  Time_E1->Color = clRed;
                  Time_E1->Font->Color = clWhite;
                 }
                else
                 {
                  Time_E1->Color = clSilver;
                  Time_E1->Font->Color = clBlack;
                 }
               TempDT = DateArhiv;
               Time_E1->Caption      = DateArhiv.FormatString("dd.mm.yyyy hh:mm:ss");
               StaticText40->Visible = (count%4)<2 ;
              }
             break;
    }
  }
 PageControl1->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::Timer2Timer(TObject *Sender)
{
 // Проверка дискового пространства
 __int64 FaktFreeKBytes = DiskFree(0)/1024;
 if (FaktFreeKBytes<FreeKBytes)
  {
   Application->MessageBoxA("ВНИМАНИЕ! ТРЕБУЕТСЯ СОХРАНЕНИЕ ТЕХНОЛОГИЧЕСКОГО АРХИВА НА ВНЕШНИЙ НОСИТЕЛЬ!","ВНИМАНИЕ! ТРЕБУЕТСЯ ПРОВЕСТИ ТЕХНИЧЕСКОЕ ОБСЛУЖИВАНИЕ.",MB_OK+MB_ICONSTOP);
  }
}
//---------------------------------------------------------------------------
int __fastcall TFMainForm::GetIDFromString(AnsiString text)
{
 AnsiString zhal="";
 AnsiChar   sim;
 int ret=0;
 for (int pc=1;pc<text.Length();pc++)
  {
   if (text.c_str()[0]=='[')
    {
     if ((text.c_str()[pc]>='0')&&(text.c_str()[pc]<='9'))
      {
       sim = text.c_str()[pc];
       zhal = zhal + sim ;
      }
     else if (text.c_str()[pc]==']')
      {
       try { ret = StrToInt(zhal); return ret; } catch (...) { return 0; }
      }
     else return ret;
    }
   else return ret;
  }
 return ret;
}
//---------------------------------------------------------------------------
int __fastcall TFMainForm::GetCountSeries(int IDTrends, double *Shkals_min, double *Shkals_max, double *min_insh, double *max_insh, int *IDTags, unsigned int *ColorTrend, double *tmp_min, double *tmp_max)
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
AnsiString __fastcall TFMainForm::GetNameEdIzm(int IDTag)
{
 Variant tmp;
 AnsiString Ret="";
 int type_visible=0;
 tmp = QListTags->Lookup("IDTag",IDTag,"TypeVisibleElement");
 if ((tmp.IsEmpty())||(tmp.IsNull()))  type_visible = 0 ;  else  type_visible = tmp;
 if ((type_visible==17)||(type_visible==18))
  { Ret="&Р."; } // ++? Единицы измерения в зависимости от режима регулятора.
 else
  {
   tmp=QListTags->Lookup("IDTag",IDTag,"VisParam2");
   if ((!tmp.IsNull())&&(!tmp.IsEmpty())) Ret=tmp;
  }
 return Ret;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BBBuilderTrendClick(TObject *Sender)
{
 double min_v,max_v;
 // формирование выбранного тренда
 if (LBListTrends->ItemIndex>=0)
  {
   int    CountSeries;
   int IDTrend=GetIDFromString(LBListTrends->Items->Strings[LBListTrends->ItemIndex]);
   // 1 - определить количество серий, шкалу по оси OY (минимальное, максимальное значение) - и шаг по оси Y, наименование шкалы
   QViewData->Parameters->ParamByName("IDTrend")->Value = IDTrend;
   if (QViewData->Active) QViewData->Requery(TExecuteOptions());
   else                   QViewData->Open();
   CountSeries=GetCountSeries(IDTrend,&Shkals_Min[0],    &Shkals_Max[0],
                                      &Shkals_InMin[0],  &Shkals_InMax[0],
                                      &IDTags_Trends[0], &ColorTrend[0], &min_v, &max_v);
   if (CountSeries==0)
    { Application->MessageBoxA("Не выбраны позиции для отображения на графике!","Внимание!",MB_OK+MB_ICONSTOP);SpeedButton3->Down=false;SpeedButton3Click(Sender); }
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
       Trends->LeftAxis->Title->Caption = GetNameEdIzm(IDTags_Trends[0]); // Наименование единиц измерения
       Trends->LeftAxis->Increment      = 10; //(max_v-min_v)/ 10;
       Trends->LeftAxis->MinorTickCount = 9;
       Trends->Title->Text->Strings[0]  = QListTrendCaptionTrend->AsString.Trim();
       Trends->Series[0]->Active = true;
       // 2 - определить минимальное, максимальное время (шкалу по оси OX) и шаг по оси X
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
           if ((Shkals_InMax[pc] - Shkals_InMin[pc])>0) // перевод инженерных единиц в проценты (значение в инженерных единицах)
            Y = (Y - Shkals_InMin[pc])/(Shkals_InMax[pc]-Shkals_InMin[pc]) * 100;
           else
           if ((Shkals_Max[pc]-Shkals_Min[pc])>0) // перевод значения в проценты (значение в технологических единицах)
            Y = (Y-Shkals_Min[pc])/(Shkals_Max[pc]-Shkals_Min[pc]) * 100;
           else ; // значение уже в % (значение в процентах)
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
 else { Application->MessageBoxA("Не выбран график для отображения!","Внимание!",MB_OK+MB_ICONSTOP);SpeedButton3->Down=false;SpeedButton3Click(Sender); }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::BBLastHourClick(TObject *Sender)
{
 DTPTime_begin->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDate_begin->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTime_end->DateTime   = (TTime)Now();
 DTPDate_end->DateTime   = (TDate)Now();
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn12Click(TObject *Sender)
{
 // выборка данных
 TDateTime beg,end;
 beg.Val =  (double)((unsigned long)DTPDate_begin->DateTime.Val) + ((DTPTime_begin->DateTime).Val - (double)((unsigned long)DTPTime_begin->DateTime.Val));
 end.Val =  (double)((unsigned long)DTPDate_end->DateTime.Val)   + ((DTPTime_end->DateTime).Val   - (double)((unsigned long)DTPTime_end->DateTime.Val)  );
 ConListSob->Connected=false;
 if (BitBtn1->Enabled)
  QListSob->SQL->Text = "select * from ListSob where (DTSob>=:DTMin) AND (DTSob<=:DTMax) AND (IDTag in (###)) ORDER BY DTSob DESC";
 else
  QListSob->SQL->Text = "select * from ListSob where (DTSob>=:DTMin) AND (DTSob<=:DTMax) ORDER BY DTSob DESC";
 if (BitBtn1->Enabled) // формирование фильтра
  {
   // сброс старого фильтра
   try
    {
     if (!QFiltr->Bof) QFiltr->First();
     while (!QFiltr->Eof)
      {
       if (QFiltrActive->AsBoolean)
        {
         QFiltr->Edit();
         QFiltrActive->AsBoolean=false;
         QFiltr->Post();
        }
       QFiltr->Next();
      }
     AnsiString Tmp="";
     for (int pc=0;pc<CLBFS->Items->Count;pc++)
      {
       if (CLBFS->Checked[pc])
        {
         int ind = pc+1;
         Variant locval[] = { ind, 1 } ;
         if (QFiltr->Locate("IndexInList;TypeFiltr", VarArrayOf(locval,1), TLocateOptions()<<loPartialKey<<loCaseInsensitive))
          {
           QFiltr->Edit();
           if (Tmp=="") Tmp = IntToStr(QFiltrIDTag->AsInteger);
           else         Tmp = Tmp+","+IntToStr(QFiltrIDTag->AsInteger);
           QFiltrActive->AsBoolean = true;
           QFiltr->Post();
          }
        }
      }
     QListSob->SQL->Text=StringReplace(QListSob->SQL->Text,"###",Tmp,TReplaceFlags()<<rfReplaceAll<<rfIgnoreCase);
    }
   catch (...) {    QListSob->SQL->Text = "select * from ListSob where (DTSob>=:DTMin) AND (DTSob<=:DTMax) ORDER BY DTSob DESC"; }
  }
 QListSob->Parameters->ParamByName("DTMin")->Value = beg;
 QListSob->Parameters->ParamByName("DTMax")->Value = end;
 QListSob->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::SpeedButton3Click(TObject *Sender)
{
 if (SpeedButton3->Down) // наблюдение за текущими параметрами в реальном времени
  {
   BitBtn6->Enabled     =false;
   BitBtn7->Enabled     =false;
   DBGridEh4->Enabled   =false;
   BitBtn8->Enabled     =false;
   BitBtn9->Enabled     =false;
   DBGridEh5->Enabled   =false;
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
   BitBtn6->Enabled     =true;
   BitBtn7->Enabled     =true;
   DBGridEh4->Enabled   =true;
   BitBtn8->Enabled     =true;
   BitBtn9->Enabled     =true;
   DBGridEh5->Enabled   =true;
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
void __fastcall TFMainForm::TBValueChange(TObject *Sender)
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

void __fastcall TFMainForm::TrendsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft) MoveVizir=true;
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::TrendsMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if (MoveVizir)
  {
   if ((X>Trends->Left+60)&&(X<(Trends->Width-Trends->Width*(Trends->MarginRight*0.01)-3)))
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

void __fastcall TFMainForm::TrendsMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft)  MoveVizir=false;        
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::TrendsResize(TObject *Sender)
{
 // изменение размера ведёт к изменению размера ползунка
 Vizir->Top    = Trends->Height*(Trends->MarginTop*0.01)+Trends->Top+3+(1600-NewSizeWidth)/45;
 Vizir->Height = Trends->Height - Vizir->Top - 50 - 30 - 3 - (1600-NewSizeWidth)/45;
}
//---------------------------------------------------------------------------
int __fastcall TFMainForm::RecNo(int IDTag)
{
 for (int pc=0;pc<Trends->SeriesCount();pc++)
  if (IDTags_Trends[pc]==IDTag) return pc;
 return -1;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::TrendsGetAxisLabel(TChartAxis *Sender,
      TChartSeries *Series, int ValueIndex, AnsiString &LabelText)
{
 // отображение шкалы по активной записи
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
         if ((Shkals_Max[ind]-Shkals_Min[ind])>0) // график в технологичесикх единицах (% в технологические единицы)
           tmp = (tmp / 100) * (Shkals_Max[ind]-Shkals_Min[ind])     + Shkals_Min[ind];
         else if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) //  значение в инженерных единицах (% в инженерные единицы)
          {
           tmp = (tmp / 100) * (Shkals_InMax[ind]-Shkals_InMin[ind]) + Shkals_InMin[ind];
          }
         else ; // значение  в %       LabelText = tmp - ;
         LabelText = FormatFloat(FormatTrend[ind],tmp);
        }
       catch (...) { }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::SBPlusClick(TObject *Sender)
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

void __fastcall TFMainForm::SBMinusClick(TObject *Sender)
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

void __fastcall TFMainForm::SBTagMinusClick(TObject *Sender)
{
 // День назад
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

void __fastcall TFMainForm::SBHourMinusClick(TObject *Sender)
{
 // Час назад
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

void __fastcall TFMainForm::SBHourPlusClick(TObject *Sender)
{
 // Час вперёд
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
void __fastcall TFMainForm::SBTagPlusClick(TObject *Sender)
{
 // День вперёд
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

void __fastcall TFMainForm::PageControl1Change(TObject *Sender)
{
 if (PageControl1->ActivePageIndex==NumPageArhivSob) // страница архивов
  {
   if (QActiveSob->Active) QActiveSob->Requery(TExecuteOptions());
   else                    QActiveSob->Open();
   BitBtn12Click(this);
  }
 if (PageControl1->ActivePageIndex==NumPageTrends) // страница трендов
  {
   if (QListPos->Active) QListPos->Requery(TExecuteOptions());
   else                  QListPos->Open();
   if (QListTrend->Active) { QListTrend->Requery(TExecuteOptions());QListTrendAfterOpen(QListTrend); }
   else                    QListTrend->Open();
   if (LBListTrends->ItemIndex==-1)  LBListTrends->ItemIndex = 0;
   LBListTrendsClick(Sender)  ;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PageControl1DrawTab(TCustomTabControl *Control,
      int TabIndex, const TRect &Rect, bool Active)
{
 // мигание
 bool Mig=false;
 switch (TabIndex)
  {
   case 0: Mig = ((MigEkran&1)==1); break;
/*   case 1: Mig = ((MigEkran&2)==2); break;
   case 2: Mig = ((MigEkran&4)==4); break; */
  }
 if (TabIndex==NumPageArhivSob)
  {
   if (NewSob)
    {
     if (Active)
      {
       if (vismig)
        {
         Control->Canvas->Brush->Color = clYellow;
         Control->Canvas->Font->Color  = clGreen  ;
         Control->Canvas->TextRect(Rect,Rect.Left+2,Rect.Top+4,PageControl1->Pages[TabIndex]->Caption);
        }
       else
        {
         Control->Canvas->Brush->Color = clSilver;
         Control->Canvas->Font->Color  = clLime  ;
         Control->Canvas->TextRect(Rect,Rect.Left+2,Rect.Top+4,PageControl1->Pages[TabIndex]->Caption);
        }
      }
     else
      {
       if (vismig)
        {
         Control->Canvas->Brush->Color = clYellow;
         Control->Canvas->Font->Color  = clRed ;
         Control->Canvas->TextRect(Rect,Rect.Left,Rect.Top,PageControl1->Pages[TabIndex]->Caption);
        }
       else
        {
          Control->Canvas->Brush->Color = clSilver;
          Control->Canvas->Font->Color =  clBlack ;
          Control->Canvas->TextRect(Rect,Rect.Left,Rect.Top,PageControl1->Pages[TabIndex]->Caption);
        }

      }
    }
   else
    {
     if (Active)
      {
       Control->Canvas->Brush->Color = clSilver;
       Control->Canvas->Font->Color = clLime  ;
       Control->Canvas->TextRect(Rect,Rect.Left+2,Rect.Top+4,PageControl1->Pages[TabIndex]->Caption);
      }
     else
      {
       Control->Canvas->Brush->Color =clSilver;
       Control->Canvas->Font->Color =clBlack ;
       Control->Canvas->TextRect(Rect,Rect.Left,Rect.Top,PageControl1->Pages[TabIndex]->Caption);
      }
    }
  }
 else
 if (Active)
  {
   if ((!Mig)||(vismig))
    {
     Control->Canvas->Brush->Color = clSilver;
     Control->Canvas->Font->Color = clLime  ;
    }
   else
    {
     Control->Canvas->Brush->Color = clYellow;
     Control->Canvas->Font->Color = clRed   ;
    }
   Control->Canvas->TextRect(Rect,Rect.Left+2,Rect.Top+4,PageControl1->Pages[TabIndex]->Caption);
  }
 else
  {
   if ((!Mig)||(!vismig))
    {
     Control->Canvas->Brush->Color = clSilver;
     Control->Canvas->Font->Color =clBlack ;
    }
   else
    {
     Control->Canvas->Brush->Color = clYellow;
     Control->Canvas->Font->Color = clRed  ;
    }
   Control->Canvas->TextRect(Rect,Rect.Left,Rect.Top,PageControl1->Pages[TabIndex]->Caption);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::QListTrendAfterOpen(TDataSet *DataSet)
{
 // построение списка
 AnsiString Tmp="";
 if (LBListTrends->ItemIndex>=0) Tmp=LBListTrends->Items->Strings[LBListTrends->ItemIndex];
 LBListTrends->Items->Clear();
 QListTrend->First();
 while (!QListTrend->Eof)
  {
   LBListTrends->Items->Add("[" + QListTrendIDTrend->AsString + "]. " + QListTrendCaptionTrend->AsString);
   QListTrend->Next();
  }
 for (int pc=0;pc<LBListTrends->Items->Count;pc++)
  {
   if (LBListTrends->Items->Strings[pc]==Tmp) { LBListTrends->ItemIndex=pc;break; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::LBListTrendsClick(TObject *Sender)
{
 if (LBListTrends->ItemIndex>=0)
  {
   int ID = GetIDFromString(LBListTrends->Items->Strings[LBListTrends->ItemIndex]);
   QConCheckTrend->Parameters->ParamByName("IDTrend")->Value = ID;
   if (QConCheckTrend->Active) QConCheckTrend->Requery(TExecuteOptions());
   else                        QConCheckTrend->Open();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::OnArhivSob(TMessage& Message)
{
 if (!QActiveSob->Active) QActiveSob->Open();
 else                     QActiveSob->Requery(TExecuteOptions());
 if (QActiveSob->Active)
  {
   bool byl=false;
   QActiveSob->Requery(TExecuteOptions());
   while (!QActiveSob->Eof)
    {
     if (QActiveSobKvitirov->AsBoolean) { byl=true;break; }
     QActiveSob->Next();
    }
   NewSob = byl;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::Button4Click(TObject *Sender)
{
 if (QActiveSob->Active)
  {
    if (!QActiveSob->Bof) QActiveSob->First();
    while (QActiveSob->Eof)
     {
      if (QActiveSobKvitirov->AsBoolean)  PostMessage(FindWindow("TFOpros_PC","Программа сбора данных от котроллеров"),WM_USER+3,QActiveSobIDSob->AsInteger,1);
      QActiveSob->Next();
     }
    if (!QActiveSob->Bof) QActiveSob->First();
    NewSob = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::QViewDataAfterScroll(TDataSet *DataSet) { Trends->Refresh(); }
//---------------------------------------------------------------------------
void __fastcall TFMainForm::ChangeColor(TCanvas *Canvas, TDataSet *DataSet)
{
 Variant val=QListTags->Lookup("IDTag", DataSet->FieldByName("IDTag")->AsInteger,"UslAvar");
 int    v  =DataSet->FieldByName("Val")->AsInteger;
 int    ct;
 if ((!val.IsEmpty())&&(!val.IsNull())) ct=val;
 else ct=0;
 switch (ct)
  {
   case 0:
   case 1:
   case 2:
   case 3:
           if (v==0)  Canvas->Font->Color = clRed;
           else       Canvas->Font->Color = clGreen;
           break;
   case 4:
           if (v==1) Canvas->Font->Color = clRed  ;
           else      Canvas->Font->Color = clGreen;
           break;
   case 5: if (v==0) Canvas->Font->Color = clGray;
           else      Canvas->Font->Color = clBlack;
           break;
   case 6: if (v==0) Canvas->Font->Color = clGreen;
           else if (v==1) Canvas->Font->Color = clFuchsia;
           else           Canvas->Font->Color = clRed;
           break;
   case 7: if (v==0) Canvas->Font->Color = clYellow;
           else      Canvas->Font->Color = clLime  ;
           break;
   case 8: if (v!=0) Canvas->Font->Color = clRed  ;
           else      Canvas->Font->Color = clGreen;
           break;
   case 10: Canvas->Font->Color = clBlack;break;
   case 9: switch (v)
            {
             case  1:
             case  3:
             case  4:
             case  6:
             case  7:
             case  8:
             case  9:
             case  0: Canvas->Font->Color = clYellow;break;
             case  2: Canvas->Font->Color = clBlack ;break;
             case 14:
             case 16:
             case 10:
             case  5: Canvas->Font->Color = clRed   ;break;
             case 11:
             case 12:
             case 13: Canvas->Font->Color = clBlue  ;break;
             case 15: Canvas->Font->Color = clGreen ;break;
             default: Canvas->Font->Color = clRed   ;break;
            }
           break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DBGridEh2DrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
 ChangeColor(DBGridEh2->Canvas,Column->Field->DataSet);
 DBGridEh2->DefaultDrawDataCell(Rect,Column->Field, State);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DBGridEh3DrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
 ChangeColor(DBGridEh3->Canvas,Column->Field->DataSet);
 DBGridEh3->DefaultDrawDataCell(Rect,Column->Field, State);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::CLBFSClickCheck(TObject *Sender)
{
 int ret=0;
 for (int i=0;i<CLBFS->Items->Count;i++)
  if (CLBFS->Checked[i]) { ret=1;break; }
 if (ret) BitBtn1->Enabled=true;
 else     BitBtn1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DBGridEh4DrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumnEh *Column,
      TGridDrawState State)
{
 if (Column->ID==1)
  {
   DBGridEh4->Canvas->Brush->Color= (TColor) Column->Field->DataSet->FieldByName("ColorLine")->AsInteger;
  }
 else
  {
   DBGridEh4->Canvas->Brush->Color= clWhite;
   DBGridEh4->Canvas->Font->Color = clBlack;
  }
 DBGridEh4->DefaultDrawDataCell(Rect,Column->Field, State);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DBGridEh4EditButtonClick(TObject *Sender)
{
 // Редактирование цвета
 ColorDialog1->Color = (TColor) QConCheckTrendColorLine->AsInteger;
 if (ColorDialog1->Execute())
  {
   QConCheckTrend->Edit();
   QConCheckTrendColorLine->AsInteger = ColorDialog1->Color;
   QConCheckTrend->Post();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn6Click(TObject *Sender)
{
  // Создание нового графика
  // Ввести наименование графика
  int IDTrend = GetIDTrends();
  if (FEnterString->ShowModal()==mrOk)
   {
    if (FEnterString->Edit1->Text.Trim()!="")
     {
      QListTrend->Insert();
      QListTrendIDTrend->AsInteger     = IDTrend;
      QListTrendCaptionTrend->AsString = FEnterString->Edit1->Text.Trim();
      QListTrend->Post();
      int id=LBListTrends->ItemIndex;
      LBListTrends->Items->Add("[" + QListTrendIDTrend->AsString + "]. " + QListTrendCaptionTrend->AsString);
      if (id==0) // скопировать информацию из временного тренда
       {
        if (QConCheckTrend->Active)
         {
          if (!QConCheckTrend->Bof) QConCheckTrend->First();
          while (!QConCheckTrend->Eof)
           {
            if (QConCheckTrendIDTrend->AsInteger==1)
             {
              QConCheckTrend->Edit();
              QConCheckTrendIDTrend->AsInteger = IDTrend;
              QConCheckTrend->Post();
             }
            QConCheckTrend->Next();
           }
         }
       }
      LBListTrends->ItemIndex=LBListTrends->Items->Count-1;
      LBListTrendsClick(Sender);
     }
   }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::BitBtn7Click(TObject *Sender)
{
 // удаление графика
 if (LBListTrends->ItemIndex<0)
  Application->MessageBoxA("Не выбран график для удаления!","Внимание!",MB_OK+MB_ICONSTOP);
 else
  {
   int ID = GetIDFromString(LBListTrends->Items->Strings[LBListTrends->ItemIndex]);
   if (ID<100) Application->MessageBoxA("Указанный график нельзя удалить (график не является пользовательским)","Внимание!",MB_OK+MB_ICONSTOP);
   else
    {
     // удаление информации из таблицы InfoTrends текущего графика
     if (!QConCheckTrend->Bof) QConCheckTrend->First();
     while (!QConCheckTrend->Eof) QConCheckTrend->Delete();
     if (QListTrend->Locate("IDTrend",ID,TLocateOptions()))
      {
       try
        {
         QListTrend->Delete();
         LBListTrends->Items->Delete(LBListTrends->ItemIndex);
         QListTrend->Requery(TExecuteOptions());
         QListTrendAfterOpen(QListTrend)       ;
        }
       catch (...)
        {
         Application->MessageBoxA("Ошибка при удалении графика!", "Внимание!",MB_OK+MB_ICONSTOP);
        }
      }
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::BitBtn8Click(TObject *Sender)
{
 // Добавление позиции для выбранного тэга
 // запрет изменения для системных графиков
 if (LBListTrends->ItemIndex<0)
  { Application->MessageBoxA("Не выбран график для редактивроания!","Внимание!",MB_OK+MB_ICONSTOP);return; }
 int IDTrend=GetIDFromString(LBListTrends->Items->Strings[LBListTrends->ItemIndex]);
 if ((IDTrend<100)&&(IDTrend!=1)) { Application->MessageBoxA("Редактирование системных графиков запрещено!","Внимание!",MB_OK+MB_ICONSTOP);return; }
 if ((QListPos->Active)&&(LBListTrends->ItemIndex>=0))
  {
   int IDInfo =GetIDInfo();
   int IDTag  =QListPosIDTag->AsInteger                                                                 ;
   // поиск указанной позиции в таблице
   if (!QConCheckTrend->Bof) QConCheckTrend->First();
   while (!QConCheckTrend->Eof)
    {
     if (QConCheckTrendIDTag->AsInteger==IDTag) { Application->MessageBoxA("Указаная позиция уже добавлена!","Внимание!",MB_OK+MB_ICONSTOP); return; }
     QConCheckTrend->Next();
    }
   QConCheckTrend->Insert();
   QConCheckTrendIDInfo->AsInteger  = IDInfo;
   QConCheckTrendIDTag->AsInteger   = IDTag;
   QConCheckTrendIDTrend->AsInteger = IDTrend;
   QConCheckTrend->Post();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::BitBtn9Click(TObject *Sender)
{
 // удаление позиции из графика
 // запрет изменения для системных графиков
 if (QConCheckTrend->Active)
  {
   int IDTrend=QConCheckTrendIDTag->AsInteger;
   if ((IDTrend<100)&&(IDTrend!=1)) { Application->MessageBoxA("Редактирование системных графиков запрещено!","Внимание!",MB_OK+MB_ICONSTOP);return; }
   QConCheckTrend->Delete();
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DBGridEh6DrawColumnCell(TObject *Sender,
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
int __fastcall TFMainForm::GetIDTrends(void)
{
 // определить ID для записи
 QTmp->SQL->Text="select * from ListTrends ORDER BY IDTrend";
 int ret=101;
 QTmp->Open();
 while (!QTmp->Eof)
  {
   if (QTmp->FieldByName("IDTrend")->AsInteger==ret) { ret++; QTmp->Next(); }
   else if (QTmp->FieldByName("IDTrend")->AsInteger>100)    break;
   else QTmp->Next();
  }
 ConTmp->Connected = false;
 return ret;
}
//---------------------------------------------------------------------------
int __fastcall TFMainForm::GetIDInfo(void)
{
 // определить ID для записи
 QTmp->SQL->Text="select * from InfoTrends ORDER BY IDInfo";
 int ret=1;
 QTmp->Open();
 while (!QTmp->Eof)
  {
   if (QTmp->FieldByName("IDInfo")->AsInteger==ret) { ret++;QTmp->Next(); }
   else break;
  }
 ConTmp->Connected = false;
 return ret;
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QConCheckTrendIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
   if (QListPos->Active)
    {
     Variant tmp;
     tmp = QListPos->Lookup("IDTag",Sender->AsInteger,"CaptionTag");
     if ((tmp.IsNull())||(tmp.IsEmpty())) Text="";
     else Text=tmp;
    }
   else Text="";
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QConCheckTrendColorLineGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)  Text = "     ";
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QViewDataIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   if (QListPos->Active)
    {
     Variant tmp;
     tmp = QListPos->Lookup("IDTag",Sender->AsInteger,"CaptionTag");
     if ((tmp.IsNull())||(tmp.IsEmpty())) Text="";
     else Text=tmp;
    }
   else Text="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QViewDataTDTGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   Text = STTimeTrend->Caption;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QViewDataValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 // текущее значение графика
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
       if (((Shkals_Max[ind]-Shkals_Min[ind])>0)&&((Shkals_InMax[ind]-Shkals_InMin[ind])>0)) // Приведение значения к единицам измерения
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

void __fastcall TFMainForm::QViewDataStatusGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   int IDTag = Sender->DataSet->FieldByName("IDTag")->AsInteger;
   try
    {
     TDateTime tmp = (TDateTime)STTimeTrend->Caption;
     if (Arhiv->DataTag[tmp][IDTag].Status==1) Text="Нет";
     else                                      Text="Да";
    }
   catch (...) { Text=""; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QViewDataValProcGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 // вычисление процента от шкалы
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
       if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) // значение в инженерных единицах перевод в %
         val = (val - Shkals_InMin[ind])/(Shkals_InMax[ind]-Shkals_InMin[ind])*100;
       else if ((Shkals_InMax[ind] - Shkals_InMin[ind])>0) // значение в технических единицах перевод в %
         val = (val - Shkals_Min[ind])/(Shkals_Max[ind]-Shkals_Min[ind])*100;
       else  ;// значение уже в процентах
       Text = FormatFloat(FormatTrend[ind],val);
      }
     else Text=""; 
    }
   catch (...) { Text=""; }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QViewDataActiveGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (Sender->AsBoolean) Text=" + ";
 else Text = " - ";
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QListSobIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText) Text = GetIDTagCaption(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QListSobValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText) Text = GetIDTagCaptionValue(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QListSobDlitGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   if (Sender->AsFloat!=0)
    {
     TDateTime dt = Sender->AsDateTime;
     int count_syt = dt.Val;
     if (count_syt>0)
      Text = IntToStr(count_syt) + " дней " + dt.TimeString();
     else
      Text = dt.TimeString();
    }
   else Text="";
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QActiveSobIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText) Text = GetIDTagCaption(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::QActiveSobValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)  { Text=GetIDTagCaptionValue(Sender);  }        
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFMainForm::GetIDTagCaption(TField *Sender)
{
 AnsiString Ret="";
 if (QListTags->Active)
  {
   Variant val=QListTags->Lookup("IDTag",Sender->AsInteger,"CaptionTag");
   if ((!val.IsEmpty())&&(!val.IsNull()))
      {
       Ret = val;
      }
     else Ret = "";
   }
 else Ret = "";
 return Ret;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFMainForm::GetIDTagCaptionValue(TField *Sender)
{
 AnsiString Ret="";
 if (QListTags->Active)
  {
   Variant val=QListTags->Lookup("IDTag",Sender->DataSet->FieldByName("IDTag")->AsInteger,"TypeVisibleArhiv");
   int ct;
   if ((!val.IsEmpty())&&(!val.IsNull())) ct=val;
   else                                   ct=0;
   int Code;
   switch (ct)
    {
     case 0: // Как есть!
             Ret=Sender->AsString.Trim();
             break;
     case 1: switch (Sender->AsInteger)
              {
               case  0: Ret = "Нет связи!";break;
               case  1: Ret = "Связь установлена!";break;
               case  2: Ret = "Нет связи! Неправильный IP адрес или нет доступа!";break;
               default: Ret = "???";break;
              }
             break;
     case 2: switch (Sender->AsInteger)
              {
               case  0: Ret = "Выключен";break;
               case  1: Ret = "Включен";break;
               default: Ret = "???";break;
              }
             break;
     case 3: switch (Sender->AsInteger)
              {
               case  0: Ret = "Загружена"    ;break;
               case  1: Ret = "Идёт загрузка";break;
               case  2: Ret = "Не запущена"  ;break;
               default: Ret = "???";break;
              }
             break;
     case 4: switch (Sender->AsInteger)
              {
               case  0: Ret = "Нет"; break;
               case  1: Ret = "Да" ; break;
               default: Ret ="???";  break;
              }
             break;
     case 5: switch (Sender->AsInteger)
              {
               case  0: Ret = "Включен ручной режим"; break;
               case  1: Ret = "Включен автоматический режим" ; break;
               default: Ret ="???";  break;
              }
             break;
     case 6: // переключение управление на ПК
             switch (Sender->AsInteger)
              {
               case  0: Ret = "Выключено управление с ПК"; break;
               case  1: Ret = "Включено управление с ПК" ; break;
               default: Ret ="???";  break;
              }
             break;
     case 7: // нажатие клавиши
             switch (Sender->AsInteger)
              {
               case  0: Ret = "ШУ. Кнопка отпущена"; break;
               case  1: Ret = "ШУ. Кнопка нажата"  ; break;
               default: Ret ="???";  break;
              }
             break;
     case 8: // режим работы
             switch (Sender->AsInteger)
              {
               case  0: Ret = "Включен ручной режим";           break;
               case  1: Ret = "Включен автоматический режим"  ; break;
               default: Ret ="???";  break;
              }
             break;
     case 9: // нажатие кнопок на ПК.
             switch (Sender->AsInteger)
              {
               case  0: Ret = "ПК. Кнопка отпущена"; break;
               case  1: Ret = "ПК. Кнопка нажата"  ; break;
               default: Ret ="???";  break;
              }
             break;
     case 10: switch (Sender->AsInteger)
              {
               case  1: Ret = "Нет"; break;
               case  0: Ret = "Да" ; break;
               default: Ret ="???";  break;
              }
             break;
     case 12: // расшифровка неисправности оборудования
              Ret="";
              if (Sender->AsInteger==0) Ret="Исправно!";
              else
               {
                if ((Sender->AsInteger&  1)==  1) Ret = Ret +"Предох.1 (диск.входа);";
                if ((Sender->AsInteger&  2)==  2) Ret = Ret +"Предох.2 (диск.входа);";
                if ((Sender->AsInteger&  4)==  4) Ret = Ret +"Предох.3 (диск.входа);";
                if ((Sender->AsInteger&  8)==  8) Ret = Ret +"Предох.4 (диск.входа);";
                if ((Sender->AsInteger& 16)== 16) Ret = Ret +"Предох.1(диск.выхода);";
                if ((Sender->AsInteger& 32)== 32) Ret = Ret +"Предох.2(диск.выхода);";
                if ((Sender->AsInteger& 64)== 64) Ret = Ret +"Предох.3(диск.выхода);";
                if ((Sender->AsInteger&128)==128) Ret = Ret +"Предох.4(диск.выхода);";
                if (Ret=="") Ret="Неизвестный код ошибки:" + IntToStr(Sender->AsInteger);
               }
              break;
     case 13: Ret="";
              if (Sender->AsInteger==0) Ret="Нет обрывов (1гр)";
              else
               {
                if ((Sender->AsInteger&  1) ==   1) Ret = Ret +"Обрыв(PT201);";
                if ((Sender->AsInteger&  2) ==   2) Ret = Ret +"Обрыв(PT202);";
                if ((Sender->AsInteger&  4) ==   4) Ret = Ret +"Обрыв(PT203);";
                if ((Sender->AsInteger&  8) ==   8) Ret = Ret +"Обрыв(PT204);";
                if ((Sender->AsInteger& 16) ==  16) Ret = Ret +"Обрыв(PT205);";
                if ((Sender->AsInteger& 32) ==  32) Ret = Ret +"Обрыв(LI401);";
                if ((Sender->AsInteger& 64) ==  64) Ret = Ret +"Обрыв(LI402);";
                if ((Sender->AsInteger&256) == 256) Ret = Ret +"Обрыв(LI403);";
                if ((Sender->AsInteger&512) == 512) Ret = Ret +"Обрыв(PT206);";
                if ((Sender->AsInteger&1024)==1024) Ret = Ret +"Обрыв(LI404);";
                if ((Sender->AsInteger&2048)==2048) Ret = Ret +"Обрыв(PT207);";
                if (Ret=="") Ret="Неизвестный код ошибки:" +IntToStr(Sender->AsInteger);
               }
              break;
     case 14: Ret="";
              if (Sender->AsInteger==0) Ret="Нет обрывов (2гр)";
              else
               {
                if ((Sender->AsInteger&  1) ==   1) Ret = Ret +"Обрыв(PT210);";
                if ((Sender->AsInteger&  2) ==   2) Ret = Ret +"Обрыв(PT211);";
                if ((Sender->AsInteger&  4) ==   4) Ret = Ret +"Обрыв(PT212);";
                if ((Sender->AsInteger&  8) ==   8) Ret = Ret +"Обрыв(PT213);";
                if (Ret=="") Ret="Неизвестный код ошибки:" +IntToStr(Sender->AsInteger);
               }
              break;
     case 15:  Ret="";
              if (Sender->AsInteger==0) Ret="Нет обрывов (3гр)";
              else
               {
                if ((Sender->AsInteger&  1) ==   1) Ret = Ret +"Обрыв(TI101);";
                if ((Sender->AsInteger&  2) ==   2) Ret = Ret +"Обрыв(TI102);";
                if ((Sender->AsInteger&  4) ==   4) Ret = Ret +"Обрыв(TI103);";
                if ((Sender->AsInteger&  8) ==   8) Ret = Ret +"Обрыв(TI104);";
                if ((Sender->AsInteger& 16) ==  16) Ret = Ret +"Обрыв(TI105);";
                if ((Sender->AsInteger& 32) ==  32) Ret = Ret +"Обрыв(TI106);";
                if ((Sender->AsInteger& 64) ==  64) Ret = Ret +"Обрыв(TI107);";
                if ((Sender->AsInteger&128) == 128) Ret = Ret +"Обрыв(TI108);";
                if (Ret=="") Ret="Неизвестный код ошибки:" +IntToStr(Sender->AsInteger);
               }
              break;
     case 11: // расшифровка этапа
              switch (Sender->AsInteger)
                     {
                      case 0 : Code=13;break;
                      case 1 : Code=14;break;
                      case 10: Code= 1;break;
                      case 12: Code= 2;break;
                      case 20:
                      case 21: Code= 3;break;
                      case 22: Code= 4;break;
                      case 24: Code= 5;break;
                      case 30:
                      case 31:
                      case 32:
                      case 33:
                      case 34: Code= 6;break;
                      case 36: Code=15;break;
                      case 38: Code= 7;break;
                      case 40:
                      case 42:
                      case 50:
                      case 52:
                      case 54:
                      case 44: Code= 8;break;
                      case 60: Code= 9;break;
                      case 62: Code=16;break;
                      case 70: Code=10;break;
                      case 72:
                      case 75:
                      case 76:
                      case 77:
                      case 78:
                      case 74: Code=11;break;
                      case 79:
                      case 80:
                      case 81:
                      case 82:
                      case 83: Code=12;break;
                      default: Code=150;break;
                     }
              switch (Code)
               {
                case  1: Ret="Установка исполнительных механизмов в исходное положение";break;
                case  2: Ret="Режим ожидания";break;
                case  3: Ret="Запуск 1-ый этап";break;
                case  4: Ret="Включение вентилятора";break;
                case  5: Ret="Подготовка к вентиляции";break;
                case  6: Ret="Вентиляция";break;
                case  7: Ret="Розжиг";break;
                case  8: Ret="Малое горение";break;
                case  9: Ret="Работа";break;
                case 10: Ret="Выключение";break;
                case 11: Ret="Аварийная вентиляция";break;
                case 12: Ret="Проверка оборудования";break;
                case 13: Ret="Режим безопасности";break;
                case 14: Ret="Пуск заблокирован";break;
                case 15: Ret="Подготовка к розжигу";break;
                case 16: Ret="Подготовка к останову";break;
                default: Ret="Код этапа:"+IntToStr(Sender->AsInteger);break;
               }
             break;
     case 16: Ret="";
              if ((Sender->AsInteger&1)==1) Ret="с датчиком температуры;";
              if ((Sender->AsInteger&2)==2) Ret=Ret + "с датчиком давления;";
              if ((Sender->AsInteger&4)==4) Ret=Ret + "с датчиком уровня;";
              if ((Sender->AsInteger&8)==8) Ret=Ret + "с датчиком ch4;";
              break;
    }
  }
 else Ret=Sender->AsString.Trim();
 return Ret;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PuskStopClick(TObject *Sender, int X, int Y, int IDPusk, int IDStop, AnsiString Text, bool AutoMode, int IDMode)
{
 // диалог ПУСК/СТОП
 if (!AutoMode)  FPuskStop->Height =  65;
 else            FPuskStop->Height =  97;
 if (SpeedButton2->Down)
  {
   FPuskStop->ID_MODE = IDMode;
   FPuskStop->ID_PUSK = IDPusk;
   FPuskStop->ID_STOP = IDStop;
   FPuskStop->Caption = Text  ;
   FPuskStop->Left    = X;
   FPuskStop->Top     = Y;
   FPuskStop->DataSet = QListTags;
   FPuskStop->BitBtn1->Caption = "ПУСК";
   FPuskStop->BitBtn2->Caption = "СТОП";
   FPuskStop->Width = 237;
   FPuskStop->ShowModal();
  }
 else Application->MessageBoxA("Команда не допустима в режиме просмотра архива!","Внимание!",MB_OK+MB_ICONSTOP);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N1pit_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image11->Left-60,Image11->Top+80,301,302,"Питательный насос №1",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N2pit_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image12->Left-90,Image12->Top+80,303,304,"Питательный насос №2",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N3pit_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image13->Left-160,Image13->Top+80,305,306,"Питательный насос №3",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N1pod_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image27->Left-60,Image27->Top+80,307,308,"Подпиточный насос №1",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N2pod_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image28->Left-60,Image28->Top+80,309,310,"Подпиточный насос №2",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N1set_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image23->Left-60,Image23->Top+80,311,312,"Сетевой насос №1",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N2set_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image24->Left-60,Image24->Top+80,313,314,"Сетевой насос №2",false,-1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::N3set_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image25->Left-60,Image25->Top+80,315,316,"Сетевой насос №3",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N10con_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image10->Left-60,Image10->Top+80,317,318,"Конденсатный насос",true,344);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N1pov_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image8->Left-60,Image8->Top+80,319,320,"Повысительный насос №1",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N2pov_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image9->Left-60,Image9->Top+80,321,322,"Повысительный насос №2",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N3pov_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image14->Left-60,Image14->Top+80,323,324,"Повысительный насос №3",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N1gvs_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image31->Left-60,Image31->Top+80,327,328,"Насос ГВС №1",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N2gvs_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image32->Left-60,Image32->Top+80,329,330,"Насос ГВС №2",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N3gvs_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image33->Left-60,Image33->Top+80,331,332,"Насос ГВС №3",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N4gvs_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image34->Left-60,Image34->Top+80,333,334,"Насос ГВС №4",false,-1);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::N11dre_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image40->Left-60,Image40->Top+80,325,326,"Дренажный насос",true,345);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Mode_ConN10_E2Click(TObject *Sender)
{
 PuskStopClick(Sender,Image10->Left-60,Image10->Top+80,317,318,"Конденсатный насос",true,344);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::Mode_DreN11_E2Click(TObject *Sender)
{
 PuskStopClick(Sender,Image40->Left-60,Image40->Top+80,325,326,"Дренажный насос",true,345);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::OnOffRezerv(TObject *Sender, int X, int Y, AnsiString Text, AnsiString Text1, AnsiString Text2, AnsiString Text3,
                                        int ID_Rez1, int ID_Rez2, int ID_Rez3, int ID_WRez1, int ID_WRez2, int ID_WRez3)
{
 // диалог включение/выключение резервных насосов
 if (SpeedButton2->Down)
  {
   FOnOffRezerv->Caption = Text;
   FOnOffRezerv->Left    =    X;
   FOnOffRezerv->Top     =    Y;
   FOnOffRezerv->StaticText1->Caption = Text1.Trim();
   FOnOffRezerv->StaticText2->Caption = Text2.Trim();
   FOnOffRezerv->StaticText3->Caption = Text3.Trim();
   FOnOffRezerv->DataSet  = QListTags;
   FOnOffRezerv->ID_REZ1  = ID_Rez1  ;
   FOnOffRezerv->ID_REZ2  = ID_Rez2  ;
   FOnOffRezerv->ID_REZ3  = ID_Rez3  ;
   FOnOffRezerv->ID_WREZ1 = ID_WRez1 ;
   FOnOffRezerv->ID_WREZ2 = ID_WRez2 ;
   FOnOffRezerv->ID_WREZ3 = ID_WRez3 ;
   FOnOffRezerv->ShowModal();
  }
 else Application->MessageBoxA("Команда не допустима в режиме просмотра архива!","Внимание!",MB_OK+MB_ICONSTOP);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Button1Click(TObject *Sender)
{
 OnOffRezerv(Sender,416,696,"Насосы ГВС", "Насос ГВС №2:", "Насос ГВС №3:", "Насос ГВС №4:",341,342,343,352,353,354);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Button2Click(TObject *Sender)
{
 OnOffRezerv(Sender,907,696,"Сетевые насосы", "Сетевой насос №1:", "Сетевой насос №2:", "Сетевой насос №3:",338,339,340,349,350,351);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Button3Click(TObject *Sender)
{
 OnOffRezerv(Sender,1100,696,"Питательные насосы", "Питательный насос №1:", "Питательный насос №2:", "Питательный насос №3:",335,336,337,346,347,348);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::OpenCloseClick(TObject *Sender, int X, int Y, int IDPusk, int IDStop, int IDStopA, AnsiString Text, bool AutoMode, int IDMode)
{
 // диалог ПУСК/СТОП
 if (!AutoMode) FPuskStop->Height =  65;
 else           FPuskStop->Width  =  97;
 if (SpeedButton2->Down)
  {
   FPuskStop->ID_MODE = IDMode;
   FPuskStop->ID_PUSK = IDPusk;
   FPuskStop->ID_STOP = IDStop;
   FPuskStop->ID_STOPA= IDStopA;
   FPuskStop->Caption = Text  ;
   FPuskStop->Left    = X;
   FPuskStop->Top     = Y;
   FPuskStop->Width = 353;
   FPuskStop->BitBtn1->Caption = "ОТКРЫТЬ";
   FPuskStop->BitBtn2->Caption = "ЗАКРЫТЬ";
   FPuskStop->BitBtn3->Caption = "СТОП"   ;
   FPuskStop->ShowModal();
  }
 else Application->MessageBoxA("Команда не допустима в режиме просмотра архива!","Внимание!",MB_OK+MB_ICONSTOP);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Z3_C_E2Click(TObject *Sender)
{
 OpenCloseClick(Sender,Z3_C_E2->Left-40,Z3_C_E2->Top+40,355,356,357,"Задвижка Z-3",false,0);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Label97Click(TObject *Sender)
{
 OpenCloseClick(Sender,Z3_C_E2->Left-40,Z3_C_E2->Top+40,355,356,357,"Задвижка Z-3",false,0);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R1_PC204_Mode_E2Click(TObject *Sender)
{
 RunRegul(1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::RunRegul(int NumReg)
{
 double Val   ;
 int    Status;
 int    id1,id2,id3,id4;
 double VMin, VMax;
 if (SpeedButton2->Down)
  {
   FReg->TypeReg = 0;
   switch (NumReg)
    {
     case 1 : id1 =  104; // - входящий сигнал
              id2 =  508; // - выход
              id3 =  501; // - режим
              id4 =  502; // - задание
              FReg->Caption = "Регулятор №1. Давление водобратной воды в системе отопления";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 2;
              FReg->ID_K1 = 503;
              FReg->ID_K2 = 504;
              FReg->ID_K3 = 505;
              FReg->ID_K4 = 506;
              FReg->ID_K5 = 507;
              break;
     case 2 : id1 =  137; // - входящий сигнал
              id2 =  528; // - выход
              id3 =  521; // - режим
              id4 =  522; // - задание
              FReg->Caption = "Регулятор №2. Температура воды после сетевого деаэратора.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 3;
              FReg->ID_K1 = 523;
              FReg->ID_K2 = 524;
              FReg->ID_K3 = 525;
              FReg->ID_K4 = 526;
              FReg->ID_K5 = 527;
              break;
     case 3 : id1 =  112; // - входящий сигнал
              id2 =  548; // - выход
              id3 =  541; // - режим
              id4 =  542; // - задание
              FReg->Caption = "Регулятор №3. Давление в питательном деаэраторе.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 4;
              FReg->ID_K1 = 543;
              FReg->ID_K2 = 544;
              FReg->ID_K3 = 545;
              FReg->ID_K4 = 546;
              FReg->ID_K5 = 547;
              break;
     case 4 : id1 =  119; // - входящий сигнал
              id2 =  568; // - выход
              id3 =  561; // - режим
              id4 =  562; // - задание
              FReg->Caption = "Регулятор №4. Давление пара на выходе РУ №1.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 5;
              FReg->ID_K1 = 563;
              FReg->ID_K2 = 564;
              FReg->ID_K3 = 565;
              FReg->ID_K4 = 566;
              FReg->ID_K5 = 567;
              break;
     case 5 : id1 =  120; // - входящий сигнал
              id2 =  588; // - выход
              id3 =  581; // - режим
              id4 =  582; // - задание
              FReg->Caption = "Регулятор №5. Давление пара на выходе РУ №2";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 6;
              FReg->ID_K1 = 583;
              FReg->ID_K2 = 584;
              FReg->ID_K3 = 585;
              FReg->ID_K4 = 586;
              FReg->ID_K5 = 587;
              break;
     case 6 : id1 =  109; // - входящий сигнал
              id2 =  608; // - выход
              id3 =  601; // - режим
              id4 =  602; // - задание
              FReg->Caption = "Регулятор №6. Уровень в сетевом деаэраторе";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 7;
              FReg->ID_K1 = 603;
              FReg->ID_K2 = 604;
              FReg->ID_K3 = 605;
              FReg->ID_K4 = 606;
              FReg->ID_K5 = 607;
              break;
     case 7 : id1 =  111; // - входящий сигнал
              id2 =  628; // - выход
              id3 =  621; // - режим
              id4 =  622; // - задание
              FReg->Caption = "Регулятор №7. Уровень в питательном деаэраторе";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 8;
              FReg->ID_K1 = 623;
              FReg->ID_K2 = 624;
              FReg->ID_K3 = 625;
              FReg->ID_K4 = 626;
              FReg->ID_K5 = 627;
              break;
     case 8 : id1 =  1004; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1023; // - режим
              id4 =  1156; // - задание
              FReg->Caption = "Регулятор №8. Давление пара. Котёл №3.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 9;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1157;
              FReg->ID_K2 = 1158;
              FReg->ID_K3 = 1159;
              FReg->ID_K4 = 1160;
              FReg->ID_K5 = 1161;
              FReg->ID_K6 = 1162;
              FReg->ID_K7 = 1163;
              break;
     case 9 : id1 =  1002; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1024; // - режим
              id4 =  1164; // - задание
              FReg->Caption = "Регулятор №9. Давление воздуха перед горелкой. Котёл №3.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 10;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1165;
              FReg->ID_K2 = 1166;
              FReg->ID_K3 = 1167;
              FReg->ID_K4 = 1168;
              FReg->ID_K5 = 1169;
              FReg->ID_K6 = 1170;
              FReg->ID_K7 = 1171;
              break;
     case 10: id1 =  1003; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1025; // - режим
              id4 =  1172; // - задание
              FReg->Caption = "Регулятор №10. Давление разрежения в топке. Котёл №3.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 11;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1173;
              FReg->ID_K2 = 1174;
              FReg->ID_K3 = 1175;
              FReg->ID_K4 = 1176;
              FReg->ID_K5 = 1177;
              FReg->ID_K6 = 1178;
              FReg->ID_K7 = 1179;
              break;
     case 11: id1 =  1005; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1026; // - режим
              id4 =  1180; // - задание
              FReg->Caption = "Регулятор №11. Уровень в барабане котла. Котёл №3.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 12;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1181;
              FReg->ID_K2 = 1182;
              FReg->ID_K3 = 1183;
              FReg->ID_K4 = 1184;
              FReg->ID_K5 = 1185;
              FReg->ID_K6 = 1186;
              FReg->ID_K7 = 1187;
              break;
     case 12: id1 =  1304; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1323; // - режим
              id4 =  1456; // - задание
              FReg->Caption = "Регулятор №12. Давление пара. Котёл №4.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 13;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1457;
              FReg->ID_K2 = 1458;
              FReg->ID_K3 = 1459;
              FReg->ID_K4 = 1460;
              FReg->ID_K5 = 1461;
              FReg->ID_K6 = 1462;
              FReg->ID_K7 = 1463;
              break;
     case 13: id1 =  1302; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1324; // - режим
              id4 =  1464; // - задание
              FReg->Caption = "Регулятор №13. Давление воздуха перед горелкой. Котёл №4.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 14;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1465;
              FReg->ID_K2 = 1466;
              FReg->ID_K3 = 1467;
              FReg->ID_K4 = 1468;
              FReg->ID_K5 = 1469;
              FReg->ID_K6 = 1470;
              FReg->ID_K7 = 1471;
              break;
     case 14: id1 =  1303; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1325; // - режим
              id4 =  1472; // - задание
              FReg->Caption = "Регулятор №14. Давление разрежения в топке. Котёл №4.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 15;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1473;
              FReg->ID_K2 = 1474;
              FReg->ID_K3 = 1475;
              FReg->ID_K4 = 1476;
              FReg->ID_K5 = 1477;
              FReg->ID_K6 = 1478;
              FReg->ID_K7 = 1479;
              break;
     case 15: id1 =  1305; // - входящий сигнал
              id2 =     0; // - выход
              id3 =  1326; // - режим
              id4 =  1480; // - задание
              FReg->Caption = "Регулятор №15. Уровень в барабане котла. Котёл №4.";
              FReg->Arhiv      = Arhiv;
              FReg->QListTags  = QListTags;
              FReg->IDTrend_Reg = 16;
              FReg->TypeReg = 1;
              FReg->ID_K1 = 1481;
              FReg->ID_K2 = 1482;
              FReg->ID_K3 = 1483;
              FReg->ID_K4 = 1484;
              FReg->ID_K5 = 1485;
              FReg->ID_K6 = 1486;
              FReg->ID_K7 = 1487;
              break;
     default: return;
    }
   Variant EdIzm=QListTags->Lookup("IDTag",id1,"VisParam2") ;
   if ((EdIzm.IsNull())||(EdIzm.IsEmpty())) FReg->EdIzm="";
   else FReg->EdIzm = EdIzm;
   Variant v1,v2;
   v1 = QListTags->Lookup("IDTag",id1,"MinVal") ;
   v2 = QListTags->Lookup("IDTag",id1,"MaxVal") ;
   if ((v1.IsNull())||(v1.IsEmpty())) VMin=0;
   else VMin = v1;
   if ((v2.IsNull())||(v2.IsEmpty())) VMax=0;
   else VMax = v2;
   GetParamValue(this,id3,Val,Status);
   if (Status!=0) return;
   FReg->SetShkals(VMin,VMax);
   FReg->ModeReg = Val == 1  ;
   GetParamValue(this,id2,Val,Status);
   FReg->ZadanieHand = Val;
   GetParamValue(this,id4,Val,Status);
   FReg->ZadanieAuto = Val;
   FReg->ZadanieHand = Val;
   FReg->IDTAG_ENTER   =  id1;
   FReg->IDTAG_EXIT    =  id2;
   FReg->IDTAG_MODE    =  id3;
   FReg->IDTAG_ZADHAND =  id4; // id2 - задание в ручном совпадает с заданием автоматического режима
   FReg->IDTAG_ZADAUTO =  id4;
   FReg->Password      = Password;
   FReg->OnGetParam    = GetParamValue;
   FReg->ShowModal();
  }
 else Application->MessageBoxA("Команда не допустима в режиме просмотра архива!","Внимание!",MB_OK+MB_ICONSTOP);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::GetParamValue(System::TObject *Sender, int IDTag, double &ValParam, int &StatusParam)
{
 // по ID определить значение тэга и его статус
 Variant Val,Status;
 if (IDTag<100001)
  {
   Val   =QListTags->Lookup("IDTag",IDTag,"ValueTag") ;
   Status=QListTags->Lookup("IDTag",IDTag,"StatusTag");
  }
 else if (IDTag<200001)
  {
   Val   =QListTags->Lookup("IDTag",IDTag-100000,"MinVal")   ;
   Status=QListTags->Lookup("IDTag",IDTag-100000,"StatusTag");
  }
 else
  {
   Val   =QListTags->Lookup("IDTag",IDTag-200000,"MaxVal")   ;
   Status=QListTags->Lookup("IDTag",IDTag-200000,"StatusTag");
  }
 if ((Val.IsNull())||(Val.IsEmpty())) ValParam=0;
 else ValParam = Val;
 if ((Status.IsNull())||(Status.IsEmpty())) StatusParam=0;
 else StatusParam = Status;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R2_PC206_Mode_E2Click(TObject *Sender)
{
 RunRegul(2);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R3_PC207_Mode_E2Click(TObject *Sender)
{
 RunRegul(3);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R4_PC212_Mode_E2Click(TObject *Sender)
{
 RunRegul(4);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R5_PC213_Mode_E2Click(TObject *Sender)
{
 RunRegul(5);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R7_LC404_Mode_E2Click(TObject *Sender)
{
 RunRegul(7);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::R6_LC403_Mode_E2Click(TObject *Sender)
{
 RunRegul(6);
}
//---------------------------------------------------------------------------
bool __fastcall TFMainForm::CheckPravInitShkals(void)
{
 bool       ret = false  ;
 AnsiString TmpFile      ;
 AnsiString TekDir       ;
 TIniFile   *Ini         ;
 char       NameFile[255];

 // чтение установочного файла
 GetCurrentDirectory(255,NameFile);
 TekDir    =NameFile;
 TmpFile = (String) NameFile + "\\wmb_oper.ini";
 if (FileExists(TmpFile))
  {
   if ((Ini = new TIniFile(TmpFile))!=NULL)
    {
     int id_op=0;
     id_op = Ini->ReadInteger("USER","Operator",2);
     if (id_op==0) ret=true;
     delete Ini;
    }
  }
 return ret;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PT_201_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление в питательной линии №1. Шкала.", 100101, 200101, PT_201_E2->Left, PT_201_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::RunInitShkals(AnsiString NameWindow, int ID_K4ma, int ID_K20ma, int X, int Y)
{
 // Изменение шкалы позиции
 if (CheckPravInitShkals())  // Есть право на изменение шкалы
  {
    FEnterShkal->Caption = NameWindow;
    double Val;
    int    Status;
    GetParamValue(this,ID_K4ma,Val,Status);
    if (Status!=0)  { Application->MessageBoxA("Нет связи с контроллером!","Внимание!",MB_OK+MB_ICONSTOP);return; }
    FEnterShkal->StaticText7->Caption  = FormatFloat("###0.00",Val);
    FEnterShkal->Edit1->Text           = FormatFloat("###0.00",Val);
    GetParamValue(this,ID_K20ma,Val,Status);
    if (Status!=0)  { Application->MessageBoxA("Нет связи с контроллером!","Внимание!",MB_OK+MB_ICONSTOP);return; }
    FEnterShkal->StaticText8->Caption  = FormatFloat("###0.00",Val);
    FEnterShkal->Edit2->Text           = FormatFloat("###0.00",Val);
    FEnterShkal->id[0] = ID_K4ma ;
    FEnterShkal->id[1] = ID_K20ma;
    FEnterShkal->Left  = X-350   ;
    FEnterShkal->Top   = Y+30    ;
    FEnterShkal->ShowModal();
  }
 else return; // нет права на изменение шкалы
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PT_202_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление в питательной линии №2. Шкала.", 100102, 200102, PT_202_E2->Left-110, PT_202_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PT_203_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление прямой воды в системе отопления. Шкала.", 100103, 200103, PT_203_E2->Left, PT_203_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PC_204_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление обратной воды в системе отопления. Шкала.", 100104, 200104, PC_204_E2->Left, PC_204_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PT_205_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление подачи ГВС. Шкала.", 100105, 200105, PT_205_E2->Left, PT_205_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::LI_401_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Уровень в баке аккумуляторе №1. Шкала.", 100106, 200106, LI_401_E2->Left, LI_401_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::LI_402_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Уровень в баке аккумуляторе №2. Шкала.", 100107, 200107, LI_402_E2->Left, LI_402_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::LC_403_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Уровень в сетевом деaэраторе. Шкала.", 100109, 200109, LC_403_E2->Left, LC_403_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::LC_404_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Уровень в питательном деaэраторе. Шкала.", 100111, 200111, LC_404_E2->Left, LC_404_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PC_206_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление в сетевом деaэраторе. Шкала.", 100110, 200110, PC_206_E2->Left, PC_206_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PC_207_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление в питательном деaэраторе. Шкала.", 100112, 200112, PC_207_E2->Left-110, PC_207_E2->Top);
  }
}
//---------------------------------------------------------------------------


void __fastcall TFMainForm::PT_210_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
//   RunInitShkals("Давление пара в сепараторе.", 100117, 200117, PT_210_E2->Left, PT_210_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PT_211_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление пара на гребёнке. Шкала.", 100118, 200118, PT_211_E2->Left, PT_211_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PC_212_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление пара на выходе РУ №1. Шкала.", 100119, 200119, PC_212_E2->Left, PC_212_E2->Top);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PC_213_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbRight) // вызов окна установки шкал
  {
   RunInitShkals("Давление пара на выходе РУ №2. Шкала.", 100120, 200120, PC_213_E2->Left, PC_213_E2->Top);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PV711_C_E2Click(TObject *Sender)
{
 if (R1_PC204_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV711_C_E2->Left-40,PV711_C_E2->Top+40,509,510,511,"Задвижка PV-711",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PV741_C_E2Click(TObject *Sender)
{
 if (R2_PC206_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV741_C_E2->Left-40,PV741_C_E2->Top+40,529,530,531,"Задвижка PV-741",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PV751_C_E2Click(TObject *Sender)
{
 if (R3_PC207_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV751_C_E2->Left-40,PV751_C_E2->Top+40,549,550,551,"Задвижка PV-751",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PV761_C_E2Click(TObject *Sender)
{
 if (R4_PC212_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV761_C_E2->Left-40,PV761_C_E2->Top+40,569,570,571,"Задвижка PV-761",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::PV771_C_E2Click(TObject *Sender)
{
 if (R5_PC213_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV771_C_E2->Left-40,PV771_C_E2->Top+40,589,590,591,"Задвижка PV-771",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PV721_C_E2Click(TObject *Sender)
{
 if (R6_LC403_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV721_C_E2->Left-40,PV721_C_E2->Top+40,609,610,611,"Задвижка PV-721",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::PV731_C_E2Click(TObject *Sender)
{
 if (R7_LC404_Mode_E2->Caption=="РУЧ")
  OpenCloseClick(Sender,PV731_C_E2->Left-40,PV731_C_E2->Top+40,629,630,631,"Задвижка PV-731",false,0);
 else
  {
   Application->MessageBoxA("Для управления задвижкой переведите регулятор в ручной режим","Внимание!",MB_OK+MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::Button5Click(TObject *Sender)
{
 // Задание уставок
 FEnterUst->OnGetParam    = GetParamValue;
 for (int i=0;i<31;i++)
  {
   FEnterUst->id[i]   =800+i;
   FEnterUst->first[i]= true;
  }
 FEnterUst->Timer1->Enabled=true;
 FEnterUst->ShowModal();
 FEnterUst->Timer1->Enabled=false;


}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn5Click(TObject *Sender)
{
 // сигнал квитирование
 PostMessage(FindWindow("TFOpros","Опрос по протоколу Modbus"),WM_USER+1,831,1);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::TNO_E2Click(TObject *Sender)
{
 //
 double Val;
 int Status;
 GetParamValue(this,373,Val,Status);
 unsigned int tc = Val;
 AnsiString Str="";
 if ((tc&  1)==  1) Str=Str+"Сгорел предохранитель вход. дискр. сигналов 1 гр.\r\n";
 if ((tc&  2)==  2) Str=Str+"Сгорел предохранитель вход. дискр. сигналов 2 гр.\r\n";
 if ((tc&  4)==  4) Str=Str+"Сгорел предохранитель вход. дискр. сигналов 3 гр.\r\n";
 if ((tc&  8)==  8) Str=Str+"Сгорел предохранитель вход. дискр. сигналов 4 гр.\r\n";
 if ((tc& 16)== 16) Str=Str+"Сгорел предохранитель выход. дискр. сигналов 1 гp.\r\n";
 if ((tc& 32)== 32) Str=Str+"Сгорел предохранитель выход. дискр. сигналов 2 гр.\r\n";
 if ((tc& 64)== 64) Str=Str+"Сгорел предохранитель выход. дискр. сигналов 3 гр.\r\n";
 if ((tc&128)==128) Str=Str+"Сгорел предохранитель выход. дискр. сигналов 4 гр.\r\n";
 Application->MessageBoxA(Str.c_str(),"Неисправность оборудования",MB_ICONWARNING+MB_ICONSTOP);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::TOB1_E2Click(TObject *Sender)
{
 double Val;
 int Status;
 GetParamValue(this,374,Val,Status);
 unsigned int tc = Val;
 AnsiString Str="";
 if ((tc&  1)==  1) Str=Str+"Обрыв 1 канала. Давление в пит. линии №1\r\n";
 if ((tc&  2)==  2) Str=Str+"Обрыв 2 канала. Давление в пит. линии №2\r\n";
 if ((tc&  4)==  4) Str=Str+"Обрыв 3 канала. Давление в сист. отопления.\r\n";
 if ((tc&  8)==  8) Str=Str+"Обрыв 4 канала. Давление обратной воды в системе отопления\r\n";
 if ((tc& 16)== 16) Str=Str+"Обрыв 5 канала. Давление подачи ГВС.\r\n";
 if ((tc& 32)== 32) Str=Str+"Обрыв 6 канала. Уровень в баке акк. №1.\r\n";
 if ((tc& 64)== 64) Str=Str+"Обрыв 7 канала. Уровень в баке акк. №2\r\n";
// if ((tc&128)==128) Str=Str+"Обрыв 8 канала. .\r\n";
 if ((tc& 256)== 256) Str=Str+"Обрыв 9 канала.  Давление в сет. сепараторе.\r\n";
 if ((tc& 512)== 512) Str=Str+"Обрыв 10 канала. Давление в сет. сепараторе.\r\n";
 if ((tc&1024)==1024) Str=Str+"Обрыв 11 канала. Давление в пит. сепараторе.\r\n";
 if ((tc&2048)==2048) Str=Str+"Обрыв 12 канала. Давление в пит. сепараторе.\r\n";
 Application->MessageBoxA(Str.c_str(),"Обрыв канала 1-ой группы",MB_ICONWARNING+MB_ICONSTOP);

}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::TOB2_E2Click(TObject *Sender)
{
 double Val;
 int Status;
 GetParamValue(this,375,Val,Status);
 unsigned int tc = Val;
 AnsiString Str="";
 if ((tc&  1)==  1) Str=Str+"Обрыв 1 канала. Давление пара в сепараторе\r\n";
 if ((tc&  2)==  2) Str=Str+"Обрыв 2 канала. Давление пара на гребёнке\r\n";
 if ((tc&  4)==  4) Str=Str+"Обрыв 3 канала. Давление пара на выходе РУ №1.\r\n";
 if ((tc&  8)==  8) Str=Str+"Обрыв 4 канала. Давление пара на выходе РУ №2\r\n";
 Application->MessageBoxA(Str.c_str(),"Обрыв канала 2-ой группы",MB_ICONWARNING+MB_ICONSTOP);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::TOB3_E2Click(TObject *Sender)
{
 double Val;
 int Status;
 GetParamValue(this,376,Val,Status);
 unsigned int tc = Val;
 AnsiString Str="";
 if ((tc&  1)==  1) Str=Str+"Обрыв канала 1. Темпер. обратной воды №1.\r\n";
 if ((tc&  2)==  2) Str=Str+"Обрыв канала 2. Темпер. обратной воды №2.\r\n";
 if ((tc&  4)==  4) Str=Str+"Обрыв канала 3. Темпер. обратной воды №3.\r\n";
 if ((tc&  8)==  8) Str=Str+"Обрыв канала 4. Темпер. прямой воды.\r\n";
 if ((tc& 16)== 16) Str=Str+"Обрыв канала 5. Темпер. воды после сетевого деаэратора.\r\n";
 if ((tc& 32)== 32) Str=Str+"Обрыв канала 6. Темпер. воды после питательного деаэратора.\r\n";
 if ((tc& 64)== 64) Str=Str+"Обрыв канала 7. Темпер. ХОВ на питательный деаэратор.\r\n";
 if ((tc&128)==128) Str=Str+"Обрыв канала 8. Темпер. подачи ГВС.\r\n";
 Application->MessageBoxA(Str.c_str(),"Неисправность оборудования",MB_ICONWARNING+MB_ICONSTOP);

}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn1Click(TObject *Sender)
{
 for (int i=0;i<CLBFS->Items->Count;i++) CLBFS->Checked[i]=false;
 BitBtn1->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::BitBtn10Click(TObject *Sender)
{
 FDiag->Password   = Password     ;
 FDiag->OnGetParam = GetParamValue;
 FDiag->IDOsn       =1198;
 FDiag->IDRez       =1199;
 FDiag->IDTag_UPS[0]=1188;
 FDiag->IDTag_UPS[1]=1189;
 FDiag->IDTag_UPS[2]=1190;
 FDiag->IDTag_UPS[3]=1191;
 FDiag->IDTag_UPS[4]=1192;
 FDiag->IDTag_UPS[5]=1193;
 FDiag->IDTag_UPS[6]=1194;
 FDiag->IDTag_UPS[7]=1195;
 FDiag->IDTag_CRP[0][0]=1027;
 FDiag->IDTag_CRP[0][1]=1028;
 FDiag->IDTag_CRP[0][2]=1029;
 FDiag->IDTag_CRP[0][3]=1030;
 FDiag->IDTag_CRP[0][4]=1031;
 FDiag->IDTag_CRP[0][5]=1032;
 FDiag->IDTag_CRP[1][0]=1033;
 FDiag->IDTag_CRP[1][1]=1034;
 FDiag->IDTag_CRP[1][2]=1035;
 FDiag->IDTag_CRP[1][3]=1036;
 FDiag->IDTag_CRP[1][4]=1037;
 FDiag->IDTag_CRP[1][5]=1038;
 FDiag->IDDop[0]       =1196;
 FDiag->IDDop[1]       =1197;
 for (int pc=0;pc<36;pc++)
  {
   FDiag->IDTag_Time_Blok[pc]=1120+pc;
   FDiag->IDTag_On_Blok[pc]  =1084+pc;
  }
 FDiag->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1ModeGaz_E3Click(TObject *Sender)
{
 RunRegul(8);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::K1PC_04_E3Click(TObject *Sender)
{
 RunRegul(8);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::K1ModeVoz_E3Click(TObject *Sender)
{
 RunRegul(9);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1PC_02_E3Click(TObject *Sender)
{
 RunRegul(9);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1PI_03_E3Click(TObject *Sender)
{
 RunRegul(10);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1ModeDym_E3Click(TObject *Sender)
{
 RunRegul(10);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1ModeVod_E3Click(TObject *Sender)
{
 RunRegul(11);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::K1LI_01_E3Click(TObject *Sender)
{
 RunRegul(11);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1ModeVod_E4Click(TObject *Sender)
{
 RunRegul(15);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1ModeDym_E4Click(TObject *Sender)
{
 RunRegul(14);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1LI_01_E4Click(TObject *Sender)
{
 RunRegul(15);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::BitBtn11Click(TObject *Sender)
{
 FDiag->Password   = Password     ;
 FDiag->OnGetParam = GetParamValue;
 FDiag->IDOsn       =1498;
 FDiag->IDRez       =1499;
 FDiag->IDTag_UPS[0]=1488;
 FDiag->IDTag_UPS[1]=1489;
 FDiag->IDTag_UPS[2]=1490;
 FDiag->IDTag_UPS[3]=1491;
 FDiag->IDTag_UPS[4]=1492;
 FDiag->IDTag_UPS[5]=1493;
 FDiag->IDTag_UPS[6]=1494;
 FDiag->IDTag_UPS[7]=1495;
 FDiag->IDTag_CRP[0][0]=1327;
 FDiag->IDTag_CRP[0][1]=1328;
 FDiag->IDTag_CRP[0][2]=1329;
 FDiag->IDTag_CRP[0][3]=1330;
 FDiag->IDTag_CRP[0][4]=1331;
 FDiag->IDTag_CRP[0][5]=1332;
 FDiag->IDTag_CRP[1][0]=1333;
 FDiag->IDTag_CRP[1][1]=1334;
 FDiag->IDTag_CRP[1][2]=1335;
 FDiag->IDTag_CRP[1][3]=1336;
 FDiag->IDTag_CRP[1][4]=1337;
 FDiag->IDTag_CRP[1][5]=1338;
 FDiag->IDDop[0]       =1496;
 FDiag->IDDop[1]       =1497;
 for (int pc=0;pc<36;pc++)
  {
   FDiag->IDTag_Time_Blok[pc]=1420+pc;
   FDiag->IDTag_On_Blok[pc]  =1384+pc;
  }
 FDiag->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DE2_K1PC_04_E4Click(TObject *Sender)
{
 RunRegul(12);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1PI_03_E4Click(TObject *Sender)
{
 RunRegul(14);
}
//---------------------------------------------------------------------------

void __fastcall TFMainForm::DE2_K1ModeGaz_E4Click(TObject *Sender)
{
 RunRegul(12);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1PC_02_E4Click(TObject *Sender)
{
 RunRegul(13);
}
//---------------------------------------------------------------------------
void __fastcall TFMainForm::DE2_K1ModeVoz_E4Click(TObject *Sender)
{
 RunRegul(13);
}
//---------------------------------------------------------------------------


void __fastcall TFMainForm::Npod_E2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button==mbLeft) PuskStopClick(Sender,Image3->Left-60,Image3->Top+80,377,378,"Подмешивающий насос",false,-1);
}
//---------------------------------------------------------------------------

