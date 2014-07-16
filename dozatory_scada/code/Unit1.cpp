//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBGridEh"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 confirmArmed=false;
 izvActEdToggle = false;
 neededPerfToggle = false;
 MVtoggle = false;
 NewSizeWidth=1600;
 FIDTrends = 2;
 Timer2->Enabled=true;
 Lic = 100;
 Arhiv                = new MyArhiv(this,Lic,1000);
 Arhiv->ActiveWrite   = false;
 if (!QFiltr->Active)    QFiltr->Open()   ;
 // построение списка объектов и формировании таблицы фильтрации
 CLBFS->Items->Clear();
 int ind=0;
 int CountArhivTag = 0;

 if (QListTags->Active)  QListTags->Requery(TExecuteOptions());
 else                    QListTags->Open();
 if (QListTrend->Active) QListTrend->Requery(TExecuteOptions());
 else                    QListTrend->Open();
 DTPTime_beginTrend->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDate_beginTrend->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTime_endTrend->DateTime   = (TTime)Now();
 DTPDate_endTrend->DateTime   = (TDate)Now();
 STTimeTrend->Caption = Now().FormatString("dd.mm.yyyy hh:nn:ss");
 SpeedButton3->Down = true;
 SpeedButton3Click(this);
 QListTags->First();
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

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
// отображение текущих данных
 static unsigned int count=0;
 static unsigned int check_exec=0;
 double      val;
 TImage      *TmpImage;
 TImage      *TmpImage1;
 TControl    *TmpCont;
 TStaticText *TmpStaticText;
 TLabel      *TmpLabel;
 TShape      *TmpShape;
 TStaticText *Por1,*Por2,*Otkaz;
 TPanel      *TmpPanel ;
 unsigned long ret ;
 unsigned long ret1;
// int l=1;
 check_exec++;

 if (FindWindow("TPACQuery","Модуль опроса")==NULL){// WinExec("opros.exe",SW_RESTORE);
        statusDebug1_S1->Caption="Нет связи с модулем опроса";
        statusDebug1_S1->Font->Color=clRed;
    }
 else{
        statusDebug1_S1->Caption="Связь с модулем опроса в норме";
        statusDebug1_S1->Font->Color=clLime;
    }
 if(confirmArmed){
        btn_confirm1_S1->Visible=true;
        }
 else{
        btn_confirm1_S1->Visible=false;
        }

 date1->Caption = Now().FormatString("dd.mm.yyyy");
 time1->Caption = Now().FormatString("hh:nn:ss")  ;
 
 if (check_exec>10)
  {
   if (!ModeApp)

   check_exec=0;
  }
 if (PageControl1->ActivePageIndex==1)
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
 else if (PageControl1->ActivePageIndex==2)
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
 else if ((PageControl1->ActivePageIndex>=0)&&(PageControl1->ActivePageIndex<=0)) // отображение активных данных
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
/*     if (!SpeedButton2->Down)
      {
         MyValTags = Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].Val;MyStatusTags =Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].Status;
         if (QListTagsIDTag->AsInteger==1001)
          {
           int l=0;
          }
         if (QListTagsIDTag->AsInteger<10000)   yes_data  = Arhiv->DataTag[DateArhiv][QListTagsIDTag->AsInteger].YesData;
         if (!yes_data)
          int l= QListTagsIDTag->AsInteger;
      } */
     if ((QListTagsNumEkran->AsInteger&NumAct)==NumAct)
      {
       TmpCont = (TControl *)FindComponent(QListTagsNameTag->AsString.Trim()+"_S"+IntToStr(PageControl1->ActivePageIndex+1));
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
           case 16: // режим работы
                    TmpStaticText = (TStaticText *)TmpCont;
                    if (MyStatusTags==1)
                     {
                      TmpStaticText->Caption     = "???";
                      TmpStaticText->Color       = clRed;
                      TmpStaticText->Font->Color = clWhite;
                     }
                    else
                     {
                      if (MyValTags==0)
                       {
                        TmpStaticText->Caption     = "АВТОМАТИЧЕСКИЙ";
                        TmpStaticText->Color       = clBlack;
                        TmpStaticText->Font->Color = clLime;
                       }
                      else if(MyValTags==1)
                       {
                        TmpStaticText->Caption     = "РУЧНОЙ";
                        TmpStaticText->Color       = clBlack;
                        TmpStaticText->Font->Color = clRed;
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
                      if (MyValTags == 0){
                        TmpStaticText->Visible=true;
                        }
                      else {
                        TmpStaticText->Visible=false;
                      }
                     }
                    break;
           case 25: //Режим работы
                    TmpLabel = (TLabel *)TmpCont;
                    if (MyValTags==0){
                        TmpLabel->Caption = "В НОРМЕ";
                        TmpLabel->Font->Color=clLime;
                    }
                    else if(MyValTags==1){
                        TmpLabel->Caption = "ОСТАНОВЛЕН";
                        TmpLabel->Font->Color=clRed;
                    }
                    else if(MyValTags==2){
                        TmpLabel->Caption = "НАРУШЕНИЕ";
                        TmpLabel->Font->Color=clYellow;
                    }
                    break;
           case 26: //Режим работы вибратора
                    TmpImage  = (TImage *)TmpCont;
                    TmpImage1 = (TImage *)FindComponent(QListTagsNameTag->AsString.Trim()+"Right_S"+IntToStr(PageControl1->ActivePageIndex+1));
                    if (MyStatusTags==1)
                     {
                      if (TmpImage->Visible) TmpImage->Visible=false;
                     }
                    if (MyValTags==0){
                        //Вибратор выключен
                        TmpImage->Visible=false;
                        if (TmpImage1!=NULL)  TmpImage1->Visible=false;
                    }
                    else if(MyValTags==1){
                        //Вибратор включен
                        TmpImage->Visible=true;
                        if (TmpImage1!=NULL) TmpImage1->Visible=true;
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
     case 0:
            // if (SpeedButton2->Down)
            // {
                 /*Time_E5->Color =  clSilver;
                 Time_E5->Font->Color = clBlack;
                 Time_E5->Caption =Now().FormatString("dd.mm.yyyy hh:mm:ss");StaticText50->Visible = false; */
            //  }
            /* else
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
              } */
             break;
    }
  }
 PageControl1->Refresh();
 //------------------------
 if(status_doz1_S1->Font->Color==clLime){
        work_doz1_S1->Visible=true;
        stop_doz1_S1->Visible=false;
 }
 else{
        work_doz1_S1->Visible=false;
        stop_doz1_S1->Visible=true;
 }
 //------------------------
 if(status_doz2_S1->Font->Color==clLime){
        work_doz2_S1->Visible=true;
        stop_doz2_S1->Visible=false;
 }
 else{
        work_doz2_S1->Visible=false;
        stop_doz2_S1->Visible=true;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_logClick(TObject *Sender)
{
 Application->MessageBoxA("Нажата кнопка 'Журнал'","Внимание",MB_OK+MB_ICONSTOP);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::BBBuilderTrendClick(TObject *Sender)
{
 double min_v,max_v;
 // формирование выбранного тренда
 if (FIDTrends>0)
  {
   int    CountSeries;
   int IDTrend=FIDTrends;
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

void __fastcall TForm1::SBPlusClick(TObject *Sender)
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

void __fastcall TForm1::SBMinusClick(TObject *Sender)
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

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
 if (SpeedButton3->Down) // наблюдение за текущими параметрами в реальном времени
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

void __fastcall TForm1::SBTagMinusClick(TObject *Sender)
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

void __fastcall TForm1::SBHourMinusClick(TObject *Sender)
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

void __fastcall TForm1::SBHourPlusClick(TObject *Sender)
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

void __fastcall TForm1::SBTagPlusClick(TObject *Sender)
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

void __fastcall TForm1::TrendsGetAxisLabel(TChartAxis *Sender,
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

void __fastcall TForm1::TrendsMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft) MoveVizir=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrendsMouseMove(TObject *Sender, TShiftState Shift,
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

void __fastcall TForm1::TrendsMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
 if (Button == mbLeft)  MoveVizir=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrendsResize(TObject *Sender)
{
 // изменение размера ведёт к изменению размера ползунка
 Vizir->Top    = Trends->Height*(Trends->MarginTop*0.01)+Trends->Top+13+(1600-NewSizeWidth)/45;
 Vizir->Height = Trends->Height - Vizir->Top - 50 - 30 - 3 - (1600-NewSizeWidth)/45;
/* Vizir->Top    = Trends->Height*(Trends->MarginTop*0.01)+Trends->Top+3;
 Vizir->Height = Trends->Height - Vizir->Top - 50 - 30 - 3; */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TBValueChange(TObject *Sender)
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

void __fastcall TForm1::DBGridEh6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if (Shift.Contains(ssDouble)) // двойное нахатие
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

void __fastcall TForm1::DBGridEh6DrawColumnCell(TObject *Sender,
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
int __fastcall TForm1::GetCountSeries(int IDTrends, double *Shkals_min, double *Shkals_max, double *min_insh, double *max_insh, int *IDTags, unsigned int *ColorTrend, double *tmp_min, double *tmp_max)
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
AnsiString __fastcall TForm1::GetNameEdIzm(int IDTag)
{
 Variant tmp;
 AnsiString Ret="";
 int type_visible=0;
 tmp = QListTags->Lookup("IDTag",IDTag,"TypeVisibleElement");
 if ((tmp.IsEmpty())||(tmp.IsNull()))  type_visible = 0 ;  else  type_visible = tmp;
 if ((type_visible==17)||(type_visible==18))
  { Ret="&Р."; } // ++? Единицы измерения регулятора в зависимости от режима
 else
  {
   tmp=QListTags->Lookup("IDTag",IDTag,"VisParam2");
   if ((!tmp.IsNull())&&(!tmp.IsEmpty())) Ret=tmp;
  }
 return Ret;
}
//---------------------------------------------------------------------------
int __fastcall TForm1::RecNo(int IDTag)
{
 for (int pc=0;pc<Trends->SeriesCount();pc++)
  if (IDTags_Trends[pc]==IDTag) return pc;
 return -1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
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

void __fastcall TForm1::QViewDataAfterScroll(TDataSet *DataSet)
{
 Trends->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QViewDataCalcFields(TDataSet *DataSet)
{
 int id = DataSet->FieldByName("IDTag")->AsInteger;
 id = RecNo(id);
 if (id>=0) QViewDataActive->AsBoolean = Trends->Series[id]->Active;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QViewDataIDTagGetText(TField *Sender,
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

void __fastcall TForm1::QViewDataTDTGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  {
   Text = STTimeTrend->Caption;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QViewDataValGetText(TField *Sender,
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

void __fastcall TForm1::QViewDataStatusGetText(TField *Sender,
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

void __fastcall TForm1::QViewDataValProcGetText(TField *Sender,
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

void __fastcall TForm1::QViewDataActiveGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (Sender->AsBoolean) Text=" + ";
 else Text = " - ";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn12Click(TObject *Sender)
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
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
 for (int i=0;i<CLBFS->Items->Count;i++) CLBFS->Checked[i]=false;
 BitBtn1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BBLastHourClick(TObject *Sender)
{
 DTPTime_begin->DateTime = (TTime)(Now() - (TTime)"01:00:00");
 DTPDate_begin->DateTime = (TDate)(Now() - (TTime)"01:00:00");
 DTPTime_end->DateTime   = (TTime)Now();
 DTPDate_end->DateTime   = (TDate)Now();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::QListSobValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText) Text = GetIDTagCaptionValue(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QListSobDlitGetText(TField *Sender,
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

void __fastcall TForm1::QActiveSobIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText) Text = GetIDTagCaption(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QActiveSobValGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)  { Text=GetIDTagCaptionValue(Sender);  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetIDTagCaptionValue(TField *Sender)
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
     case 17: switch (Sender->AsInteger)
              {
               case  0: Ret = "В норме";break;
               case  1: Ret = "Остановлен";break;
               default: Ret = "Ошибка";break;
              }
             break;
     case 18: switch (Sender->AsInteger)
              {
               case  0: Ret = "Вибратор выключен";break;
               case  1: Ret = "Вибратор включен";break;
               default: Ret = "Ошибка";break;
              }
             break;
    }
  }
 else Ret=Sender->AsString.Trim();
 return Ret;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TForm1::GetIDTagCaption(TField *Sender)
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

void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
 if (PageControl1->ActivePageIndex==2)//NumPageArhivSob) // страница архивов
  {
   if (QActiveSob->Active) QActiveSob->Requery(TExecuteOptions());
   else                    QActiveSob->Open();
   BitBtn12Click(this);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CLBFSClickCheck(TObject *Sender)
{
 int ret=0;
 for (int i=0;i<CLBFS->Items->Count;i++)
  if (CLBFS->Checked[i]) { ret=1;break; }
 if (ret) BitBtn1->Enabled=true;
 else     BitBtn1->Enabled=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn_setIzvestActivity1_S1Click(TObject *Sender)
{
union{//Объявление временной union
                long luni;
                float funi;
        }tmpuni;
float tmpcom = 20;
if(!izvActEdToggle){
        izvActivityEdit1->Visible = true;
        izvActivityEdit1->Text = izvestActivity1_S1->Caption;
        izvActivityEdit1->Text = StringReplace(izvActivityEdit1->Text,"%","",TReplaceFlags()<<rfReplaceAll).Trim();
        izvActEdToggle = true;
        }
else{
        izvActivityEdit1->Visible = false;
        izvActEdToggle = false;
        tmpuni.funi = StrToFloat(izvActivityEdit1->Text);
        PostMessage(FindWindow("TPACQuery","Модуль опроса"),WM_USER+1,tmpcom,tmpuni.luni);
        confirmArmed=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_setPerfomanceSummary1_S1Click(TObject *Sender)
{
union{//Объявление временной union
                long luni;
                float funi;
        }tmpuni;
float tmpcom = 22;

if(!neededPerfToggle){
        neededPerfEdit1->Visible = true;
        neededPerfEdit1->Text = neededPerfomanceSummary1_S1->Caption;
        neededPerfEdit1->Text = StringReplace(neededPerfEdit1->Text,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim();
        neededPerfToggle = true;
        }
else{
        neededPerfEdit1->Visible = false;
        neededPerfToggle = false;
        tmpuni.funi = StrToFloat(neededPerfEdit1->Text);
        PostMessage(FindWindow("TPACQuery","Модуль опроса"),WM_USER+1,tmpcom,tmpuni.luni);
        confirmArmed=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_setMV1_S1Click(TObject *Sender)
{
union{//Объявление временной union
                long luni;
                float funi;
        }tmpuni;
float tmpcom = 21;
if(!MVtoggle){
        MVEdit1->Visible = true;
        MVEdit1->Text = curent_MV1_S1->Caption;
        MVEdit1->Text = StringReplace(MVEdit1->Text,"%","",TReplaceFlags()<<rfReplaceAll).Trim();
        MVtoggle = true;
        }
else{
        MVEdit1->Visible = false;
        MVtoggle = false;
        tmpuni.funi = StrToFloat(MVEdit1->Text);
        PostMessage(FindWindow("TPACQuery","Модуль опроса"),WM_USER+1,tmpcom,tmpuni.luni);
        confirmArmed=true;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::QListSobIDTagGetText(TField *Sender,
      AnsiString &Text, bool DisplayText)
{
 if (DisplayText)
  Text=GetIDTagCaption(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
bool error=1;
if(curentPerfomanceIzvest1_S1->Caption!="---"){
        CalcPerfIzvest = StrToFloat(StringReplace(calcPerfomanceIzvest1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
else error=1;
if(calcPerfomanceIzvest1_S1->Caption!="---"){
        CurentPerfIzvest = StrToFloat(StringReplace(curentPerfomanceIzvest1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
//--
if(calcPerfomanceSand1_S1->Caption!="---"){
        CalcPerfSand = StrToFloat(StringReplace(calcPerfomanceSand1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
else error=1;
if(curentPerfomanceSand1_S1->Caption!="---"){
        CurentPerfSand = StrToFloat(StringReplace(curentPerfomanceSand1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
//---
else error=1;
if(curentPerfomanceSummary1_S1->Caption!="---"){
        CurPerfSummary = StrToFloat(StringReplace(curentPerfomanceSummary1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
else error=1;
if(neededPerfomanceSummary1_S1->Caption!="---"){
        NeededPerfSummary = StrToFloat(StringReplace(neededPerfomanceSummary1_S1->Caption,"Т.","",TReplaceFlags()<<rfReplaceAll).Trim());
        error=0;
        }
else error=1;
if(!error){
        if(CurentPerfIzvest<CalcPerfIzvest){
                curentIzvPerfArrowDown1->Visible=true;
                curentIzvPerfArrowUp1->Visible=false;
                }
        else{
                curentIzvPerfArrowDown1->Visible=false;
                curentIzvPerfArrowUp1->Visible=true;
                }
        if(CurPerfSummary<NeededPerfSummary){
                curentPerfSummArrowDown1->Visible=true;
                curentPerfSummArrowUp1->Visible=false;
                }
        else{
                curentPerfSummArrowDown1->Visible=false;
                curentPerfSummArrowUp1->Visible=true;
                }
        if(CurentPerfSand<CalcPerfSand){
                curentPerfSandArrowDown1->Visible=true;
                curentPerfSandArrowUp1->Visible=false;
                }
        else{
                curentPerfSandArrowDown1->Visible=false;
                curentPerfSandArrowUp1->Visible=true;
                }
        }
else;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_confirm1_S1Click(TObject *Sender)
{
confirmArmed=false;

float tmpcom = 10;

PostMessage(FindWindow("TPACQuery","Модуль опроса"),WM_USER+1,tmpcom,0);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_mainTabClick(TObject *Sender)
{
TabSheet1->TabVisible = true;
TabSheet2->TabVisible = false;
TabSheet3->TabVisible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_trendTabClick(TObject *Sender)
{
TabSheet1->TabVisible = false;
TabSheet2->TabVisible = true;
TabSheet3->TabVisible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_logTabClick(TObject *Sender)
{
TabSheet1->TabVisible = false;
TabSheet2->TabVisible = false;
TabSheet3->TabVisible = true;
}
//---------------------------------------------------------------------------

