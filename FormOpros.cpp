//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormOpros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFOpros *FOpros;
int DIPV;
//---------------------------------------------------------------------------
__fastcall TFOpros::TFOpros(TComponent* Owner)
        : TForm(Owner)
{
 Debug_prog    =false;
 write_to_memo1= false;
 Timer1->Enabled=false;
/* int val;
 union
  {
   unsigned char s[2];
   unsigned short i  ;
  } l;
  l.s[1]=   2;
  l.s[0]=0x20;
  val=l.i;
  rashod_gaza=(unsigned long)val*4; */
 StepProg=0;
 Inicializace()      ;
 try
  {
   QData->Open()                 ; if (write_to_memo1) Memo1->Lines->Add("Подключение к БД");
   QCountRecords->Open()         ;
   QArhivSob->Open()             ;

/*   if (QData->Locate("IDTag",99,TLocateOptions()))
    {
     QData->Edit();
     QData->FieldByName("TekValue")->AsFloat=1;
     QData->FieldByName("TekStatus")->AsInteger=0;
     QData->Post();
     QData->First();
    } */
  }
 catch (...) { throw Exception("Ошибка подключения к базе данных!"); }
 port0=uart_Open("")           ; if (write_to_memo1) Memo1->Lines->Add("Открытие COM0")   ;
 port4=uart_Open("COM4,9600"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM4")   ;
 port3=uart_Open("COM3,9600"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM3")   ;
 port5=uart_Open("COM5,2400"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM5")   ;
 port26=uart_Open("COM26,9600");
 port27=uart_Open("COM27,9600");
 uart_SetTimeOut(port26,80,CTO_TIMEOUT_ALL);
 uart_SetTimeOut(port27,80,CTO_TIMEOUT_ALL);
 RezWork=0;
 CONSTKLAP=4;
 CONSTCONTROL=6;
 CONSTSTABPLZAP=26;
 InitConsts();
 InitTableZadan();
 Timer1->Enabled=true;
 Application->ShowMainForm=false;


}
//---------------------------------------------------------------------------
void __fastcall TFOpros::Inicializace(void)
{
 char       NameFile[255] ;
 AnsiString TmpFile       ;
 TIniFile   *Ini          ;
 int        Dp,Wtm,Sp     ;
 GetCurrentDirectory(255,NameFile);
 TmpFile = (String) NameFile + "\\silikat.ini";
/* for (int pc=0;pc<MaxCountTags;pc++)
  {
   PredSignal[pc]    =false;
   KvitirovSignal[pc]=false;
  } */
 if (FileExists(TmpFile))
  {
   if ((Ini = new TIniFile(TmpFile))!=NULL)
    {
     Dp    =Ini->ReadInteger("USER","Debug_prog",    0);
     Wtm   =Ini->ReadInteger("USER","Write_to_memo1",0);
     Sp    =Ini->ReadInteger("USER","Show_Panel",    0);
    }
   else
    {
     Dp    =0;
     Wtm   =0;
     Sp    =0;
    }
  }
 else
  {
   Dp    =0;
   Wtm   =0;
   Sp    =0;
  }
 if (Dp==0)  Debug_prog    =false; else Debug_prog    =true;
 if (Wtm==0) write_to_memo1=false; else write_to_memo1=true;
 if (Sp==0)
  {
   Application->ShowMainForm=false;
   Timer1->Enabled=true;
  // Timer2->Enabled=true;
  }
}
//---------------------------------------------------------------------------
__fastcall TFOpros::~TFOpros(void)
{
 if (ConData->Connected) ConData->Connected=false;
 uart_Close(port0)  ;
 uart_Close(port4)  ;
 uart_Close(port3)  ;
 uart_Close(port5)  ;
 uart_Close(port26) ;
 uart_Close(port27) ;
}
//---------------------------------------------------------------------------
bool __fastcall TFOpros::ReadPC(void)
{
 BOOL          bResult;
 unsigned long fakt   ;
 unsigned char result[80];
 union
  {
   float          ValueTags[160];
   unsigned char  buffer[640]   ;
  } drpc;
 bResult=ReadFile(port4,result,9,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 if (fakt==8)
  {
   if ((result[0]=='[')&&
       (result[1]=='R')&&
       (result[2]=='E')&&
       (result[3]=='A')&&
       (result[4]=='D')&&
       (result[5]==']')&&
       (result[6]==0x0D)&&
       (result[7]==0x0A))
    {
     // передача данных
     for (int k=0;k<40;k++)
      {
       try
        {
         double shkala  = FakMax[k]-FakMin[k]        ;
         double ishkala = InMax[k] -InMin[k]         ;
         if ((shkala>0)&&(ishkala>0))
          {
           drpc.ValueTags[k]=(ValueTag[k]-InMin[k])*(double)(shkala/ishkala);
          }
         else
          {
           drpc.ValueTags[k]=ValueTag[k];
          }
         if (StatusTag[k]!=0)  drpc.ValueTags[k]=-9999;
        }
       catch  (...)
        {
         drpc.ValueTags[k]=-9999;
        }
      }
     bResult=WriteFile(port4,drpc.buffer,160,&fakt,NULL);
     if (!bResult)
      {
       GetLastError();
       return false;
      }
     if (fakt==160) return true;
    }
  }
 else if (fakt==9)
  {
   if ((result[0]=='[')&&
       (result[1]=='R')&&
       (result[2]=='E')&&
       (result[3]=='A')&&
       (result[4]=='D')&&
       ((result[5]=='1')||(result[5]=='2')||(result[5]=='3'))&&
       (result[6]==']')&&
       (result[7]==0x0D)&&
       (result[8]==0x0A))
    {
     // передача данных              480/4 = 120/3= 40
     if (result[5]=='1')
      {
       for (int k=40;k<80;k++)
        {
               try
               {
                double shkala  = FakMax[k]-FakMin[k]        ;
                double ishkala = InMax[k] -InMin[k]         ;
                if ((shkala>0)&&(ishkala>0))
                 {
                  drpc.ValueTags[k]=(ValueTag[k]-InMin[k])*(double)(shkala/ishkala);
                  }
                else
                 {
                  drpc.ValueTags[k]=ValueTag[k];
                 }
                if (StatusTag[k]!=0)  drpc.ValueTags[k]=-9999;
               }
              catch (...)
                {
                 drpc.ValueTags[k]=-9999;
                 }
        }
       bResult=WriteFile(port4,&drpc.buffer[160],160,&fakt,NULL);
      }
     else if (result[5]=='2')
      {
       for (int k=80;k<120;k++)
        {
               try
               {
                double shkala  = FakMax[k]-FakMin[k]        ;
                double ishkala = InMax[k] -InMin[k]         ;
                if ((shkala>0)&&(ishkala>0))
                 {
                  drpc.ValueTags[k]=(ValueTag[k]-InMin[k])*(double)(shkala/ishkala);
                  }
                else
                 {
                  drpc.ValueTags[k]=ValueTag[k];
                 }
                if (StatusTag[k]!=0)  drpc.ValueTags[k]=-9999;
               }
              catch (...)
                {
                 drpc.ValueTags[k]=-9999;
                 }
        }
       bResult=WriteFile(port4,&drpc.buffer[320],160,&fakt,NULL);
      }
     else
      {
       for (int k=120;k<160;k++)
        {
               try
               {
                double shkala  = FakMax[k]-FakMin[k]        ;
                double ishkala = InMax[k] -InMin[k]         ;
                if ((shkala>0)&&(ishkala>0))
                 {
                  drpc.ValueTags[k]=(ValueTag[k]-InMin[k])*(double)(shkala/ishkala);
                  }
                else
                 {
                  drpc.ValueTags[k]=ValueTag[k];
                 }
                if (StatusTag[k]!=0)  drpc.ValueTags[k]=-9999;
               }
              catch (...)
                {
                 drpc.ValueTags[k]=-9999;
                 }
        }
       bResult=WriteFile(port4,&drpc.buffer[480],160,&fakt,NULL);
      }
     if (!bResult)
      {
       GetLastError();
       return false;
      }
     if (fakt==160) return true;
    }
  }
 return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFOpros::ReadCounter(unsigned char BaseAdr)
{
 unsigned char com[80];
 BOOL bResult;
 int CountBytes=0;
 unsigned long fakt=0;
 union
  {
   unsigned char s[2];
   unsigned short i  ;
  } l;
 unsigned char result[80];
 com[0]=BaseAdr;
 // Накопденное значение счётчика с момента последнего включения прибора
 com[1]=0x03; // комнада чтения
 com[2]=0x00;
 com[3]=0x50;
 com[4]=0x00; // количество считываемых регистров
 com[5]=0x03;
 CountBytes=6;
 WORD tt=Crc16(com,CountBytes) ;
 com[CountBytes]= (BYTE) tt    ;CountBytes++;
 com[CountBytes]= (BYTE)(tt>>8);CountBytes++;
 if (port27==NULL) { return false; }
 bResult=WriteFile(port27,com,CountBytes,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 bResult=ReadFile(port27,result,11,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 if (fakt!=11) { return false; }
 else  // ответ на команду
      {
       if ((result[0]==BaseAdr)&&(result[1]==0x03))
        {
         unsigned int val;
         l.s[1]=result[3];
         l.s[0]=result[4];
         val=l.i;
         rashod_gaza=val*4; //1000+val[1]+(double)(val[2]/65536);
         return true;
        }
       else return false;
      }
}
//---------------------------------------------------------------------------
bool __fastcall TFOpros::ReadVesper(unsigned char BaseAdr, int NumCom, Word Registr)
{
 unsigned char com[80];
 BOOL bResult;
 int CountBytes=0;
 unsigned long fakt=0;
 union
  {
   unsigned char s[2];
   unsigned short i  ;
  } l;
 int AnswerByte;
 unsigned char result[80];
 com[0]=BaseAdr;
 switch (NumCom)
  {
   case   1: // Выходная частота
             com[1]=0x03; // комнада чтения
             com[2]=0x00;
             com[3]=0x21;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   2: // Выходное напряжение
             com[1]=0x03; // комнада чтения
             com[2]=0x00;
             com[3]=0x25;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   3: // Выходной ток
             com[1]=0x03; // комнада чтения
             com[2]=0x00;
             com[3]=0x22;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   4: // Состояние частотника
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x10;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   5: // Код ошибки ЧРП
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x14;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   6: // Сигналы управления
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x10;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   7: // выходная мощность
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x27;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   8: // опорная частота
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x20;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case   9: // состояние входных клем
             com[1]=0x03; // комнада чтения
             com[2]=0x00; // команда
             com[3]=0x29;
             com[4]=0x00; // количество считываемых регистров
             com[5]=0x01;
             CountBytes=6;
             break;
   case 101: // Пуск/Стоп
             com[1]=0x10; // команда записи
             com[2]=0x00; // АДРЕС КОМАНДЫ
             com[3]=0x00;
             com[4]=0x00; // количество записываемых регистров
             com[5]=0x01;
             com[6]=0x02; // количество записываемых байт
             CountBytes=7;
             break;
   case 102: // задание опорной частоты
             com[1]=0x10; // команда записи
             com[2]=0x00; // АДРЕС КОМАНДЫ
             com[3]=0x01;
             com[4]=0x00; // количество записываемых регистров
             com[5]=0x01;
             com[6]=0x02; // количество записываемых байт
             CountBytes=7;
             break;
   default : return false;
  }
 AnswerByte=7;
 if (CountBytes==7)
  {
   AnswerByte=11;
   l.i         = Registr;
   com[7] = l.s[1] ;
   com[8] = l.s[0] ;
   CountBytes=9;
  }
 WORD tt=Crc16(com,CountBytes) ;
 com[CountBytes]= (BYTE) tt    ;CountBytes++;
 com[CountBytes]= (BYTE)(tt>>8);CountBytes++;
 if (port26==NULL) { return false; }
 bResult=WriteFile(port26,com,CountBytes,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 bResult=ReadFile(port26,result,AnswerByte,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 if (fakt!=AnswerByte) { return false; }
 else if (fakt==11) // ответ на команду записи
      {
       if ((result[0]==BaseAdr)&&(result[1]==0x10))    return true;
       else       return false;
      }
     else // ответ на запрос
      {
       if ((result[0]==BaseAdr)&&(result[1]==0x03)&&(result[2]==0x02))
        {
         l.s[1]=result[3];
         l.s[0]=result[4];
         ValueI7011=l.i;
         return true;
        }
       else return false;
      }

}
//---------------------------------------------------------------------------
bool __fastcall TFOpros::ReadDVL(int NumDVL, int NumCom, Word Registr)
{
 // чтение информации с ДВЛ - дозиметра
 unsigned short int ks=0;
 union
  {
   unsigned long val;
   float sf;
   unsigned char byte[4];
  } ddata;
 union
  {
   unsigned char s[2];
   unsigned short i  ;
  } l;
 unsigned char com[29];
 unsigned char result[80];
 unsigned long fakt;
 int  CountBytes=0;
 BOOL bResult;
 switch (NumDVL)
  {
   case 1: com[0]=0x01;
           com[1]=0x03;
           com[2]=0x00;
           com[3]=0x2E; //46;
           com[4]=0x00;
           com[5]=0x02;
           CountBytes=6;
           break;
  }
 AnswerByte=7;
 if (CountBytes==7)
  {
   AnswerByte=11;
   l.i         = Registr;
   com[7] = l.s[1] ;
   com[8] = l.s[0] ;
   CountBytes=9;
  }
 ks=Crc16(com,CountBytes);
 com[CountBytes]  =(unsigned char)ks;
 com[CountBytes+1]=(unsigned char)(ks>>8);
// uart_SetTimeOut(port3,100,CTO_TIMEOUT_ALL)   ;
 bResult=WriteFile(port3,com,CountBytes+2,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 if (fakt!=CountBytes+2) return false;
 bResult=ReadFile(port3,result,9,&fakt,NULL);
 if (!bResult)
  {
   GetLastError();
   return false;
  }
 //fakt=uart_Read(port3,result);
 //if (write_to_memo1) Memo1->Lines->Add("Чтение = fakt="+IntToStr(fakt));
 if (fakt==9)
  {
   ddata.byte[3]=result[3];
   ddata.byte[2]=result[4];
   ddata.byte[1]=result[5];
   ddata.byte[0]=result[6];
   Proiz = ddata.val * 0.01;
   return true;
  }
 return false;
}
/*======================================================================*/
/*                     Расчёт контрольной суммы                         */
/*======================================================================*/
unsigned short int TFOpros::Crc16(unsigned char *Data, unsigned int size)
{
 union
  {
   unsigned char  b[2];
   unsigned short w   ;
  } Sum;
 unsigned char  shift_cnt;
 unsigned char  *ptrByte;
 unsigned long  byte_cnt = size;
 ptrByte = Data;
 Sum.w   = 0xffffU;
 for (;byte_cnt>0;byte_cnt--)
  {
   Sum.w=(unsigned short)((Sum.w/256U)*256U+((Sum.w%256U)^(*ptrByte++)));
   for (shift_cnt=0;shift_cnt<8;shift_cnt++)
    {
     if ((Sum.w&0x1)==1)
      Sum.w=(unsigned short)((Sum.w>>1)^0xa001U);
     else Sum.w>>=1;
    }
  }
 return Sum.w;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::CheckSignal(int TekRezWork, int NumCheckSignal, int IDTAG, unsigned long OTK_MOD, unsigned long NOT_SIGNAL, unsigned long YES_SIGNAL)
{
 int ret=TekRezWork;
 if (StatusTag[IDTAG]==1) { CodeError=(CodeError|OTK_MOD);TmpCodeError=(TmpCodeError|OTK_MOD);return ret; }
 if (check_sost[NumCheckSignal]%2==0) // не должно быть
  {   if (ValueTag[IDTAG]==1)
       {
         CodeError=(CodeError|NOT_SIGNAL);
         if ((check_sost[NumCheckSignal]>1)&&(NOT_SIGNAL!=0)) { TmpCodeError=(TmpCodeError|NOT_SIGNAL); ret=9; }
       }
      else if ((CodeError&NOT_SIGNAL)==NOT_SIGNAL) CodeError=CodeError-(CodeError&NOT_SIGNAL);
  }
 else // должно быть
  {
     if (ValueTag[IDTAG]==0)
      {
        CodeError=(CodeError|YES_SIGNAL);
        if ((check_sost[NumCheckSignal]>1)&&(YES_SIGNAL!=0)) { TmpCodeError=(TmpCodeError|YES_SIGNAL); ret=9; }
      }
     else if ((CodeError&YES_SIGNAL)==YES_SIGNAL) CodeError=CodeError-(CodeError&YES_SIGNAL);
  }
 return ret;
}
//---------------------------------------------------------------------------
static bool check_sig=true;
static int  zad=0;
static int  LogWklDym =0;
static int  stab_plamz=0;
void __fastcall TFOpros::Logika(void)
{
 // Логика работы
 TDateTime   Delta,C2S,C3S,C5S;
 static bool per_raz=true;
 static int startblok=0;
 static int startblokmax=0;
 C3S=(TTime)"00:00:03";
 C5S=(TTime)"00:00:35";
 C2S=(TTime)"00:00:02";
 C3S.Val=C3S.Val-(int)C3S.Val;
 C5S.Val=C5S.Val-(int)C5S.Val;
 C2S.Val=C2S.Val-(int)C2S.Val;
 if (!check_sig)
 {
  zad++;if (zad>CONSTKLAP) { zad=0;check_sig=true; }
  //if (write_to_memo1) Memo1->Lines->Add("TIME-OUT"+IntToStr(zad));
 }
 else zad=0;
 if (LogWklDym==0)   ValueTag[IDTAG_UPR_DYM]=0;
 switch (RezWork)
  {
   case 0: // Подготовка печи
           check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
           check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
           check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
           check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
           check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
           check_sost[5] =0;// 5 - закрыт клапан №1                     (0,2 закрыт)
           check_sost[6] =0;// 6 - закрыт клапан №2                     (0,2 закрыт)
           check_sost[7] =0;// 7 - закрыт клапан запальника             (0,2 закрыт)
           check_sost[8] =1;// 8 - открыта свеча безопасности           (0,2 открыт)
           check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
           check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
           check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
           if (((ValueTag[IDTAG_PUSK_ON]==1)&&(StatusTag[IDTAG_PUSK_ON]==0))||(TTimZakZas->Enabled)) // запуск таймера вентиляции
            {
             // закрытие газовой заслонки
             if (ValueTag[IDTAG_GAZ_OFF]==0)
              {
               StepProg=1;
               TTimZakZas->Enabled=true;
               TDym->Enabled=false;
               if (!TTimZakZas->Enabled) CodeError=CodeError|16777216;
               ValueTag[IDTAG_UPR_CLOSE]= 1;
              }
             else
              {
               StepProg=2;
               ValueTag[IDTAG_UPR_CLOSE]= 0;
               if ((CodeError&16777216)==16777216) CodeError=CodeError-16777216;
               LogWklDym=1;
               ValueTag[IDTAG_UPR_DYM]=1;
               TDym->Enabled=true;
               TimV=TDym->Interval/1000;///Timer1->Interval;
               TObrOts->Enabled=true;
               RezWork      =1;
               check_sig=false;
               //ValueTag[IDTAG_UPR_CLOSE]=1 ;
              }
            }
           else  { StepProg=0;TDym->Enabled=false;  }
           break;
   case  1: // Вентиляция топки печи
           check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
           check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
           check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
           check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
           check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
           check_sost[5] =0;// 5 - закрыт клапан №1                     (0,2 закрыт)
           check_sost[6] =0;// 6 - закрыт клапан №2                     (0,2 закрыт)
           check_sost[7] =0;// 7 - закрыт клапан запальника             (0,2 закрыт)
           check_sost[8] =1;// 8 - открыта свеча безопасности           (0,2 открыт)
           check_sost[9] =3;// 9 - дымосос выключен                     (0,2 выключен)
           check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
           check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
           if (check_sig)
            {
             if ((ValueTag[IDTAG_DYM_OFF]==0)&&(StatusTag[IDTAG_DYM_OFF]==0)) // остановить таймер вентиляции
              {
               StepProg     =    3;
               TDym->Enabled=false;
               RezWork      =    0;
              }
             else if ((ValueTag[IDTAG_PUSK_ON]==0)&&(StatusTag[IDTAG_PUSK_ON]==0)) // Нажата кнопка пуск - старт опрессовки
              {
               // закрытие клапана свечи безопасности
               ValueTag[IDTAG_UPR_KLAPSB]=1;
               StepProg = 4;
               // запуск 10 сек. таймера
               TCSB->Enabled=true;
               RezWork      =3;
               check_sig=false;
              }
            }
           break;
 /* case  2: // Вентиляция завершена. Требуется опрессовка
            check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
            check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
            check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
            check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =0;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =0;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =0;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =1;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
            //if ((ValueTag[IDTAG_DYM_OFF]==0)&&(StatusTag[IDTAG_DYM_OFF]==0)) //  дымосос выключили
            // RezWork = 0; // старт по новой
            //else
            if ((ValueTag[IDTAG_PUSK_ON]==0)&&(StatusTag[IDTAG_PUSK_ON]==0)) // Нажата кнопка пуск - старт опрессовки
             {
              // закрытие клапана свечи безопасности
              ValueTag[IDTAG_UPR_KLAPSB]=1;
              // запуск 10 сек. таймера
              TCSB->Enabled= true;
              RezWork      =    3;
              check_sig=false;

             }
            break; */
   case  3: // Контроль герметичности клапанов. Проверка клапана №1 "включён таймер TCSB"
            check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
            check_sost[1] =2;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
            check_sost[2] =2;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
            check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =2;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =2;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
            if (check_sig) StepProg=5;
            break;
   case  4: // Контроль герметичности клапанов. Проверка клапана №2, свечи безопасности
            Delta.Val=SDT.CurrentDateTime().Val-SDT.Val;
            if (Delta.Val<C3S.Val)  // дельта времени с момента переключения в режим < 3 сек
             {
            //  if (write_to_memo1) Memo1->Add("GERM-"
              if ((ValueTag[IDTAG_GERM2_OFF]==1)&&(StatusTag[IDTAG_GERM1_OFF]==0)) // если давление достигнуто
               {
                if (write_to_memo1) Memo1->Lines->Add("Меньше 3 сек. давление набрано!");
                 StepProg=8;
                 ValueTag[IDTAG_UPR_KLAP1]=0;// закрыть газовый клапан
                 check_sost[5]            =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
                 check_sost[1]            =1;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
                 check_sost[2]            =1;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
                 check_sig =false;
                 if (per_raz)
                  {
                    // Запуск 30 секундного таймера
                    TClaps->Enabled=true;
                    per_raz=false;
                    if (write_to_memo1) Memo1->Lines->Add("Запуск 30 сек.таймера");
                    return;
                  }
                 else  if (write_to_memo1) Memo1->Lines->Add("Меньше 3 секунд  давление набрано");
               }
              else
               {
                 if (check_sig) StepProg=7;
                 if (write_to_memo1) Memo1->Lines->Add("Меньше 3 сек. давление не набрано!");
                 check_sost[5] =3;per_raz=true;
                 check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
                 check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
               }
              check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
              check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
              check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
              check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
              check_sost[7] =2;// 7 - закрыт клапан запальника             (0,2 закрыт)
              check_sost[8] =2;// 8 - открыта свеча безопасности           (0,2 открыт)
              check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
              check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
              check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
             }
            else
             {
              if (check_sig) StepProg=9;
              if (write_to_memo1) Memo1->Lines->Add("Больше 3 секунд  авария если давление не набрано");
              check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
              check_sost[1] =3;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
              check_sost[2] =3;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
              check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
              check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
              check_sost[5] =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
              check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
              check_sost[7] =2;// 7 - закрыт клапан запальника             (0,2 закрыт)
              check_sost[8] =2;// 8 - открыта свеча безопасности           (0,2 открыт)
              check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
              check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
              check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
             }
            break;
   case  5: // Контроль герметичности клапанов. Подготовка к розжигу
            if (check_sig) StepProg=11;
            check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
            check_sost[1] =2;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
            check_sost[2] =2;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
            check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =2;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =3;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
            break;
   case  6: // Вентиляция завершена. Готов к розжигу
            check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
            check_sost[1] =2;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
            check_sost[2] =2;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
            check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =2;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =3;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
            if (check_sig) StepProg=14;
            if ((ValueTag[IDTAG_GAZ_OFF]==1)&&(StatusTag[IDTAG_GAZ_OFF]==0))
             {
              if (16777216==(CodeError&16777216)) CodeError=CodeError-16777216;
              if ((ValueTag[IDTAG_PUSK_ON]  ==1) && (StatusTag[IDTAG_PUSK_ON]  ==0)&&
                  (ValueTag[IDTAG_PLAM_OFF] ==0) && (StatusTag[IDTAG_PLAM_OFF] ==0)&&
                  (ValueTag[IDTAG_PLAMZ_OFF]==0) && (StatusTag[IDTAG_PLAMZ_OFF]==0)&&
                  (!TDym->Enabled)
                 )
               {
                StepProg=15;
                TOzPusk->Enabled=false;
                // Включить трансформатор
                ValueTag[IDTAG_UPR_ISKRA]  = 1;
                // Открыть клапан запальника
                ValueTag[IDTAG_UPR_KLAPZ]  = 1;
                // Запустить 3 секундный таймер
                TZap->Enabled=true;
                check_sig=false;
                RezWork=7;
                stab_plamz=0;
                SDT = SDT.CurrentDateTime() ;
               }
             }
            else
             {
              CodeError=CodeError|16777216;
             }
            break;
   case  7: // Розжиг. Открыт клапан запальника и включен трансформатор запальника
            Delta.Val=SDT.CurrentDateTime().Val-SDT.Val;
            if (Delta.Val<C5S.Val)  // дельта времени с момента переключения в режим < 5 сек
             {
              check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
              check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
              check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
              check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
              check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
              check_sost[5] =2;// 5 - закрыт клапан №1                     (0,2 закрыт)
              check_sost[6] =2;// 6 - закрыт клапан №2                     (0,2 закрыт)
              check_sost[7] =3;// 7 - закрыт клапан запальника             (0,2 закрыт)
              check_sost[8] =3;// 8 - открыта свеча безопасности           (0,2 открыт)
              check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
              check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
              if (stab_plamz<CONSTCONTROL)
               {
                check_sost[11]=1;
                if (!TZap->Enabled) check_sost[11]=3;
                else { if (check_sig) StepProg=16; }
               }// 11- пламя запальника                     (0,2 не должно быть)
              else
               {
                check_sost[11]=3;ValueTag[IDTAG_UPR_ISKRA]=0;StepProg=17;
               }
              if ((ValueTag[IDTAG_PLAMZ_OFF]==1)&&(StatusTag[IDTAG_PLAMZ_OFF]==0)) stab_plamz++;
              else if (stab_plamz<CONSTCONTROL) stab_plamz=0;
             }
            if (stab_plamz>=CONSTSTABPLZAP)
             {
              // открыть газовые клапана
              ValueTag[IDTAG_UPR_KLAP1]  = 1;
              ValueTag[IDTAG_UPR_KLAP2]  = 1;
              StepProg = 18;
              // Запустить 3 секундный таймер
              TStabFak->Enabled=true;
              check_sig=false;
              RezWork=8;
              SDT = SDT.CurrentDateTime() ;
             }
            break;
   case  8: // Розжиг. Контроль стабилизации пламени
            Delta.Val=SDT.CurrentDateTime().Val-SDT.Val;
            if (check_sig) StepProg=19;
            if (Delta.Val<C2S.Val)  // дельта времени с момента переключения в режим < 5 сек
             {
              check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
              check_sost[1] =1;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
              check_sost[2] =1;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
              check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
              check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
              check_sost[5] =3;// 5 - закрыт клапан №1                     (0,2 закрыт)
              check_sost[6] =3;// 6 - закрыт клапан №2                     (0,2 закрыт)
              check_sost[7] =3;// 7 - закрыт клапан запальника             (0,2 закрыт)
              check_sost[8] =3;// 8 - открыта свеча безопасности           (0,2 открыт)
              check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
              check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
              check_sost[11]=3;// 11- пламя запальника                     (0,2 не должно быть)
             }
            else
             {
              check_sost[0] =1;// 0 - наличие пламени                      (0,2 не должно быть)
              check_sost[1] =1;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
              check_sost[2] =1;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
              check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
              check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
              check_sost[5] =3;// 5 - закрыт клапан №1                     (0,2 закрыт)
              check_sost[6] =3;// 6 - закрыт клапан №2                     (0,2 закрыт)
              check_sost[7] =3;// 7 - закрыт клапан запальника             (0,2 закрыт)
              check_sost[8] =3;// 8 - открыта свеча безопасности           (0,2 открыт)
              check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
              check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
              check_sost[11]=3;// 11- пламя запальника                     (0,2 не должно быть)
             }
            WklBlok=0;
            break;
   case  9: // Авария
            // Выключение таймеров
            TDym->Enabled      =false;
            TCSB->Enabled      =false;
            TClaps->Enabled    =false;
            TZap->Enabled      =false;
            TStabFak->Enabled  =false;
            TTimZakZas->Enabled=false;
            TOzPusk->Enabled   =false;
             if (ValueTag[IDTAG_GAZ_OFF]==0) // закрытие газовой заслонки
              {
               //++? запустить таймер - только один раз
               ValueTag[IDTAG_UPR_CLOSE]= 1;
               ValueTag[IDTAG_UPR_OPEN] = 0;
              }

            // вернуть клапана в исходные состояния
            check_sost[0] =0;// 0 - наличие пламени                      (0,2 не должно быть)
            check_sost[1] =0;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)
            check_sost[2] =0;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)
            check_sost[3] =0;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =0;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =0;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =0;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =0;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =1;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =LogWklDym;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=0;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=0;// 11- пламя запальника                     (0,2 не должно быть)
            ValueTag[IDTAG_UPR_KLAP1]  = 0;
            ValueTag[IDTAG_UPR_KLAP2]  = 0;
            ValueTag[IDTAG_UPR_KLAPZ]  = 0;
            ValueTag[IDTAG_UPR_KLAPSB] = 0;
            ValueTag[IDTAG_UPR_ISKRA]  = 0;
            if ((ValueTag[IDTAG_KNOP_KVIT]==1)&&
                (StatusTag[IDTAG_KNOP_KVIT]==0))
             {
              ValueTag[IDTAG_UPR_SOUND]=0;
              wkl_sound=2;
              if (countknopkvit>CONSTCOUNTFORKVIT)
               {
                StepProg=23;
                CodeError=0;
                TmpCodeError=0;
                RezWork=0  ;
               }
              else { StepProg=22;countknopkvit++; }
             }
            else countknopkvit=0;
            break;
   case 10: // В работе.
            check_sost[0] =3;// 0 - наличие пламени                    (0,2 не должно быть)
            if (check_sig) StepProg=21;
            if ((CodeError&8192)==8192)  CodeError=CodeError-8192;

            check_sost[1] =1;// 1 - отсутствие сигнала герметичности №1  (0,2 не должно быть)

            check_sost[2] =1;// 2 - отсутствие сигнала герметичности №2  (0,2 не должно быть)

            check_sost[3] =2;// 3 - загазованность по метану             (0,2 не должно быть)
            check_sost[4] =2;// 4 - загазованность по СО                 (0,2 не должно быть)
            check_sost[5] =3;// 5 - закрыт клапан №1                     (0,2 закрыт)
            check_sost[6] =3;// 6 - закрыт клапан №2                     (0,2 закрыт)
            check_sost[7] =0;// 7 - закрыт клапан запальника             (0,2 закрыт)
            check_sost[8] =0;// 8 - открыта свеча безопасности           (0,2 открыт)
            check_sost[9] =1;// 9 - дымосос выключен                     (0,2 выключен)
            check_sost[10]=2;// 10- нет авария дымосоа                   (0,2 авария дымососа)
            check_sost[11]=ValueTag[IDTAG_PLAMZ_OFF];// 11- пламя запальника                     (0,2 не должно быть)
            if (ValueTag[IDTAG_ADYM_OFF]==1) counterr_for_dym++;
            else                             counterr_for_dym=0;
            if (counterr_for_dym>2) check_sost[10]=2;
            else                    check_sost[10]=0;
            if (ValueTag[IDTAG_PGAZA]>UST_PMIN+0.5)
             {
              // if (write_to_memo1) Memo1->Lines->Add("Авария="+FloatToStr(ValueTag[IDTAG_PGAZA])+FloatToStr(UST_PMIN));
              check_sost[9]=3;
             }
            if (ValueTag[IDTAG_PGAZA]>UST_PMIN) WklBlok=1;
            if (WklBlok==1)
             {
              if (ValueTag[IDTAG_PGAZA]<BLOK_PMIN)
               {
                if (startblok>((double)CONSTTIMESTOPPMIN/((double)Timer1->Interval/1000))) { TmpCodeError=TmpCodeError|2; CodeError=CodeError|2;RezWork=9; }
                else startblok++;
               }
              else startblok=0;
             }
            break;
   case 11: // послеаварийная вентиляция.
            if (!TimerPosAvar->Enabled)   if (bylpusk) RezWork=6; else RezWork=0;
            break;


  }

 if ((RezWork!=9)&&(RezWork!=11)&&(RezWork!=0))
  {
   if (ValueTag[IDTAG_PGAZA]>BLOK_PMAX)
    {
     startblokmax++;
     if (startblokmax>((double)CONSTTIMESTOPPMAX/((double)Timer1->Interval/1000)))
      { CodeError=CodeError|4;TmpCodeError=TmpCodeError|4;RezWork=9; }
    }
   else startblokmax=0;

   if ((ValueTag[IDTAG_KNOP_STOP]==1)&(StatusTag[IDTAG_KNOP_STOP]==0))
    { CodeError=CodeError|33554432;TmpCodeError=TmpCodeError|33554432;RezWork=9; }
  }
 if ((ValueTag[IDTAG_POWER]==0)&&(StatusTag[IDTAG_POWER]==0))
  {
   if (!TNoNapr->Enabled) TNoNapr->Enabled=true;
  }
 else TNoNapr->Enabled=false;
 if (RezWork!=9)
  {
   if ((ValueTag[IDTAG_KNOP_KVIT]==0)||(StatusTag[IDTAG_KNOP_KVIT]==1))
    CountForKvit=0;
   else  { CountForKvit++;wkl_sound=2; } //+++//
   if (CountForKvit>CONSTCOUNTFORKVIT)
    ValueTag[IDTAG_UPR_SOUND]=1;
   else  ValueTag[IDTAG_UPR_SOUND]=0;
  }
 if ((ValueTag[IDTAG_REZZ_HAND]==0)&&(StatusTag[IDTAG_REZZ_HAND]==0)) // ручное управление заслонкой
  {
   if ((ValueTag[IDTAG_KNOP_OPEN]==1)&&(StatusTag[IDTAG_KNOP_OPEN]==0))   { if (TTimZakZas->Enabled) TTimZakZas->Enabled=false; ValueTag[IDTAG_UPR_OPEN] =1;    }
   else                                                                   ValueTag[IDTAG_UPR_OPEN] =0;
   if ((ValueTag[IDTAG_KNOP_CLOSE]==1)&&(StatusTag[IDTAG_KNOP_CLOSE]==0)) ValueTag[IDTAG_UPR_CLOSE]=1;
   else                                                                   { if (!TTimZakZas->Enabled) ValueTag[IDTAG_UPR_CLOSE]=0;  }
   if ((ValueTag[IDTAG_UPR_OPEN]==1)&&(ValueTag[IDTAG_UPR_CLOSE]==1))
    { ValueTag[IDTAG_UPR_OPEN]=0;ValueTag[IDTAG_UPR_CLOSE]=0; }
  }
 else // автоматичекое управление заслонкой
  {
   ValueTag[IDTAG_UPR_OPEN] =0;
   ValueTag[IDTAG_UPR_CLOSE]=0;
  }
 if (RezWork==10)
  {
   if (ValueTag[IDTAG_PGAZA]<UST_PMIN) ValueTag[IDTAG_UPR_CLOSE]=0;
   if (ValueTag[IDTAG_PGAZA]>UST_PMAX) ValueTag[IDTAG_UPR_OPEN]=0;
  }
 if ((ValueTag[IDTAG_DYM_PUSK]==1)&&(StatusTag[IDTAG_DYM_PUSK]==0))
  { ValueTag[IDTAG_UPR_DYM]=1;LogWklDym=1;if ((CodeError&8388608)==8388608) CodeError=CodeError-8388608; }
 if ((ValueTag[IDTAG_DYM_STOP]==1)&&(StatusTag[IDTAG_DYM_STOP]==0)&&
     (ValueTag[IDTAG_PGAZA]<=UST_PMIN+0.5)
    )
     { ValueTag[IDTAG_UPR_DYM]=0;LogWklDym=0;if ((CodeError&1048576)==1048576) CodeError=CodeError-1048576; }
 Reguls_run();
 if ((RezWork!=9)&&((DIPV&8)!=8))
  {
   if (check_sig)
    {
     for (int k=0;k<12;k++) SaveAvar_sost[k]=check_sost[k];
     int TmpRezWork=RezWork;
     TmpRezWork=CheckSignal(TmpRezWork, 0,IDTAG_PLAM_OFF,     1024,   8192,     16);  // проверка датчика пламени                       нет есть
     TmpRezWork=CheckSignal(TmpRezWork, 1,IDTAG_GERM1_OFF,    1024,  16384,  16384);  // проверка датчика герметичности нижней уставки  нет есть
     TmpRezWork=CheckSignal(TmpRezWork, 2,IDTAG_GERM2_OFF,    1024,  32768,  32768);  // проверка датчика герметичности верхней уставки нет есть
     TmpRezWork=CheckSignal(TmpRezWork, 3,IDTAG_GAZCH4_OFF,   1024,     32,     32);  // проверка датчика загазованности по CH4         --- есть
     TmpRezWork=CheckSignal(TmpRezWork, 4,IDTAG_GAZCO_OFF,    1024,      8,      8);  // проверка датчика загазованности по CO          --- есть
     TmpRezWork=CheckSignal(TmpRezWork, 5,IDTAG_KLAP1_CLOSE,  1024,  65536,  65536);  // проверка датчика закрытия клапана №1           закрыт открыт
     TmpRezWork=CheckSignal(TmpRezWork, 6,IDTAG_KLAP2_CLOSE,  1024, 131072, 131072);  // проверка датчика закрытия клапана №2           закрыт открыт
     TmpRezWork=CheckSignal(TmpRezWork, 7,IDTAG_KLAPZ_CLOSE,  1024, 262144, 262144);  // проверка датчика закрытия клапана запальника   закрыт открыт
     TmpRezWork=CheckSignal(TmpRezWork, 8,IDTAG_SWBEZ_OPEN,   1024, 524288, 524288);  // проверка датчика свечи безопасности            открыт закрыт
     TmpRezWork=CheckSignal(TmpRezWork, 9,IDTAG_DYM_OFF,      1024,8388608,1048576);  // проверка включения дымососа                    выключен включен
     TmpRezWork=CheckSignal(TmpRezWork,10,IDTAG_ADYM_OFF,     1024,      1,      1);  // аварийный сигнал с дымососа                    --- есть
     TmpRezWork=CheckSignal(TmpRezWork,11,IDTAG_PLAMZ_OFF,    1024,4194304,2097152);  // проверка датчика пламени запалника             нет есть
     RezWork=TmpRezWork;
     if (RezWork==5) { RezWork=6;StepProg=12;check_sig=false; }
    }
  }
 if (RezWork==10) // убрать сигналы датчиков герметичности
  {
   if ((CodeError&32768)==32768) CodeError=CodeError-32768;
   if ((CodeError&16384)==16384) CodeError=CodeError-16384;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteData(void)
{
 static unsigned char result[80];
 if (!Debug_prog)
  {
   // запись данных
   // установка аналоговых выходов
   // сброс watchdog таймера
   // установка дискретных выходов
   // сброс watchdog таймера
   unsigned long Val=0;
   pac_ChangeSlot(5);
   uart_SetTimeOut(port5,10,CTO_TIMEOUT_ALL)   ;
   uart_SendCmd(port0,"~000",result)           ;
   if (result[4]=='4') // сработал WatchDogTimer
    {
     uart_SendCmd(port0,"~001",result)           ;
     uart_SendCmd(port0,"~00311E",result)        ;
    }
   else  uart_SendCmd(port0,"~**",result);
   //if (write_to_memo1) Memo1->Lines->Add((AnsiString)((char *)result));
   if (ValueTag[IDTAG_GAZ_OFF]==1) { ValueTag[IDTAG_UPR_CLOSE]=0;  TTimZakZas->Enabled=false; }
   int sswkl=0;
   static int cik=0;
   cik++;
   if (cik>7) cik=0;
   if (ValueTag[IDTAG_UPR_SOUND]) sswkl=1;
   else
    {
     if (wkl_sound==1)
      if (cik<3) sswkl=1;
      else       sswkl=0;
    }

   Val=ValueTag[IDTAG_UPR_OPEN]        +
       ValueTag[IDTAG_UPR_CLOSE] *   2 +
       ValueTag[IDTAG_UPR_KLAP1] *   8 +
       ValueTag[IDTAG_UPR_KLAP2] *   4 +
       ValueTag[IDTAG_UPR_KLAPZ] *  16 +
       ValueTag[IDTAG_UPR_KLAPSB]*  32 +
       ValueTag[IDTAG_UPR_ISKRA] *  64 +
       sswkl * 128 +
       ValueTag[IDTAG_UPR_DYM]   * 256;
   if (test_mod>10) Val=Val+512;
   pac_WriteDO(port0,5,32,Val);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteSobyt(void)
{
 // Запись события в базу данных
 static unsigned long old_code= 0;
 static int           old_rez =-1;
 try  // архив событий
  {
 //  if ((old_code!=CodeError)||(old_rez!=RezWork)) // возникло событие
    {
     TDateTime tdt;
     if (!QCountRecords->Active) QCountRecords->Open();
     if (!QArhivSob->Active) QArhivSob->Open();
     int tz=QCountRecordsNumTekRec->AsInteger;
     tdt=tdt.CurrentDateTime();
     if (!QArhivSob->Bof) QArhivSob->First();
     if (QArhivSob->Locate("IDRec",tz,TLocateOptions()))
      QArhivSob->Edit();
     else
      QArhivSob->Insert();
     QArhivSobIDRec->AsInteger    = QCountRecordsNumTekRec->AsInteger;
     QArhivSobDTSob->AsDateTime   =                               tdt;
     QArhivSobNumRez->AsInteger   =                           RezWork;
     QArhivSobStepProg->AsInteger    = StepProg;
 //    TmpCodeError = CodeError;
/*     for (int k=0;k<12;k++)
      {
       if (SaveAvar_sost[k]<2)
        {
         switch (k)
          {
           case  0: if ((TmpCodeError&   8192)==   8192) TmpCodeError=TmpCodeError-   8192;
                    if ((TmpCodeError&     16)==     16) TmpCodeError=TmpCodeError-     16;
                    break;
           case  1: if ((TmpCodeError&  16384)==  16384) TmpCodeError=TmpCodeError-  16384;
                    break;
           case  2: if ((TmpCodeError&  32768)==  32768) TmpCodeError=TmpCodeError-  32768;
                    break;
           case  3: if ((TmpCodeError&     32)==     32) TmpCodeError=TmpCodeError-     32;
                    break;
           case  4: if ((TmpCodeError&      8)==      8) TmpCodeError=TmpCodeError-      8;
                    break;
           case  5: if ((TmpCodeError&  65536)==  65536) TmpCodeError=TmpCodeError-  65536;
                    break;
           case  6: if ((TmpCodeError& 131072)== 131072) TmpCodeError=TmpCodeError- 131072;
                    break;
           case  7: if ((TmpCodeError& 262144)== 262144) TmpCodeError=TmpCodeError- 262144;
                    break;
           case  8: if ((TmpCodeError& 524288)== 524288) TmpCodeError=TmpCodeError- 524288;
                    break;
           case  9: if ((TmpCodeError&8388608)==8388608) TmpCodeError=TmpCodeError-8388608;
                    if ((TmpCodeError&1048576)==1048576) TmpCodeError=TmpCodeError-1048576;
                    break;
           case 10: if ((TmpCodeError&      1)==      1) TmpCodeError=TmpCodeError-      1;
                    break;
           case 11: if ((TmpCodeError&4194304)==4194304) TmpCodeError=TmpCodeError-4194304;
                    if ((TmpCodeError&2097152)==2097152) TmpCodeError=TmpCodeError-2097152;
                    break;

          }
        }
      } */
     QArhivSobCodeError->AsInteger=TmpCodeError;
     QArhivSob->Post();
     int newrec=QCountRecordsNumTekRec->AsInteger+1;
     if (newrec>QCountRecordsCountRecords->AsInteger) newrec=1;
     QCountRecords->Edit();
     QCountRecordsNumTekRec->AsInteger=newrec;
     QCountRecords->Post();
     old_code=CodeError;
     old_rez =RezWork  ;
    }
  }
 catch (...)
  {
  }

}
//---------------------------------------------------------------------------
void __fastcall TFOpros::Timer1Timer(TObject *Sender)
{
 // Логика работы
 TDateTime start,end;
 static int  filtr_ind =    0;

 start=start.CurrentDateTime();
// if (TimV>0) TimV--;
 test_mod++;
 if (test_mod>=20) test_mod=0;
// Timer1->Enabled=false;
 ReadData()  ; // чтение данных                                               TDateTime
 if (StatusTag[IDTAG_PGAZA]==0)
  {
   if ((filtr_ind>=0)&&(filtr_ind<100))
   massiv_p_gaza[filtr_ind]=ValueTag[IDTAG_PGAZA];
   filtr_ind++;
   if (filtr_ind>=CONSTCOUNTPOINT) filtr_ind=0;
  }
 Logika()    ; // логика
 WriteData() ; // запись данных
 end=end.CurrentDateTime();
 try
  {
   TDateTime tt;
   tt=end.Val-start.Val;
     //Memo1->Lines->Add(tt.FormatString("hh:nn:ss")+"===="+FloatToStr(tt.Val));
  }
 catch (...)
  {
  }
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::ReadData(void)
{
 // чтение данных
 float         AI[16]  ;
 static float  zd=0;
 static bool   first_rash    =true;
 static double old_value_rash=   0;
 bool          tim8,tim20;
 int           ST[16]  ;
 int           STDI[32];
 int           STDO[32];
 static float         CRP[20]  ;
 static int           STCRP[20];
 static int num_cikl=1;
 unsigned long DI,DO   ;
// static int OldSig[3]={0,0,0}  ;
// static int ind      =0        ;
// static int ps       =0        ;
 static unsigned char cmd[80]   ;
 static unsigned char result[80];
 TTime gtr;
 gtr=gtr.CurrentTime();
 if ((StrToInt(gtr.FormatString("hh"))==8)&&(StrToInt(gtr.FormatString("nn"))==0)&&(StrToInt(gtr.FormatString("ss"))<5))
  tim8=true;
 else tim8=false;
 if ((StrToInt(gtr.FormatString("hh"))==20)&&(StrToInt(gtr.FormatString("nn"))==0)&&(StrToInt(gtr.FormatString("ss"))<5))
  tim20=true;
 else tim20=false;
 if (Debug_prog==0)
  {
   DIPV=pac_GetDIPSwitch();
   if ((DIPV&8)==8)
   { IZMREZREG=true;StepProg=21;RezWork=10;ValueTag[IDTAG_UPR_KLAPSB]=1;ValueTag[IDTAG_UPR_KLAP1]=1;ValueTag[IDTAG_UPR_KLAP2]=1;}
   // 1-ый слот 8-и канальный модуль I-87017RW  (аналоговых входов)
   for (int pc=0;pc<8;pc++)
    if (pac_ReadAI(port0,1,pc,8,&AI[pc])) ST[pc]=0; else ST[pc]=1;
   // 2-ой слот 4-ех канальный модуль I-87018RW (температурных входов)
   for (int pc=0;pc<4;pc++)
    if (pc==0)
     if (pac_ReadAI(port0,7,pc,4,&AI[pc+8])) ST[pc+8]=0; else ST[pc+8]=1;
    else
     if (pac_ReadAI(port0,2,pc,4,&AI[pc+8])) ST[pc+8]=0; else ST[pc+8]=1;
   // 3-ий слот 4-ех канальный модуль I-87024W (аналоговых выходов)
   for (int pc=0;pc<4;pc++)
    if (pac_ReadAO(port0,3,pc,4,&AI[pc+12])) ST[pc+12]=0; else ST[pc+12]=1;
   // 4-ый слот 32-ух канальный модуль дискретных входов

   if (pac_ReadDI(port0,4,32,&DI)) for (int pc=0;pc<32;pc++) STDI[pc]=0;
   else                            for (int pc=0;pc<32;pc++) STDI[pc]=1;
   // фильтр по сигналу наличия пламени

   if (pac_ReadDO(port0,5,32,&DO)) for (int pc=0;pc<32;pc++) STDO[pc]=0;
   else                            for (int pc=0;pc<32;pc++) STDO[pc]=1;
  }
 // опрос БИРП
 cmd[0]='Q' ;
 cmd[1]='1' ;
 cmd[2]=0x0D;
 uart_SetTimeOut(port5,50,CTO_TIMEOUT_ALL);
 uart_SendCmd(port5,cmd,result)           ;
 AnsiString ttt=(AnsiString)((char *)result);
 bool read_data_ups=0;
 if ((strlen(result)>=46)&&(result[0]=='('))
  {
   UPS_DATA.IPV =(result[1] -'0')*1000+(result[2] -'0')*100+(result[3] -'0')*10+(result[5] -'0');
   UPS_DATA.IPFV=(result[7] -'0')*1000+(result[8] -'0')*100+(result[9] -'0')*10+(result[11]-'0');
   UPS_DATA.OPV =(result[13]-'0')*1000+(result[14]-'0')*100+(result[15]-'0')*10+(result[17]-'0');
   UPS_DATA.NAGR=(result[19]-'0')* 100+(result[20]-'0')* 10+(result[21]-'0')                    ;
   UPS_DATA.FREQ=(result[23]-'0')* 100+(result[24]-'0')* 10+(result[26]-'0')                    ;
   UPS_DATA.BAT =(result[28]-'0')* 100+(result[29]-'0')* 10+(result[31]-'0')                    ;
   UPS_DATA.TEMP=(result[33]-'0')* 100+(result[34]-'0')* 10+(result[36]-'0')                    ;
   UPS_DATA.FLAG=0;
   if (result[38]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG +128;
   if (result[39]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG + 64;
   if (result[40]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG + 32;
   if (result[41]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG + 16;
   if (result[42]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG +  8;
   if (result[43]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG +  4;
   if (result[44]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG +  2;
   if (result[45]=='1') UPS_DATA.FLAG=UPS_DATA.FLAG +  1;
  }
 else read_data_ups=1;
  // опрос веспера
 switch (num_cikl)
 {
  case 1: if (ReadVesper(1,1,0)){CRP[0]=(float)ValueI7011/10; STCRP[0]=0;}   else STCRP[0]=1;   break;
  case 2: if (ReadVesper(1,2,0)){CRP[1]=(float)ValueI7011/10; STCRP[1]=0;}   else STCRP[1]=1;   break;
  case 3: if (ReadVesper(1,3,0)){CRP[2]=(float)ValueI7011/100; STCRP[2]=0;}   else STCRP[2]=1;  break;
  case 4: if (ReadVesper(1,4,0)){CRP[3]=ValueI7011; STCRP[3]=0;}   else STCRP[3]=1;             break;
  case 5: if (ReadVesper(1,5,0)){CRP[10]=ValueI7011; STCRP[10]=0;} else STCRP[10]=1;            break;
  case 6: if (ReadVesper(1,7,0)){CRP[4]=(float)ValueI7011/10; STCRP[4]=0;}   else STCRP[4]=1;   break;
  case 7: if (ReadVesper(1,8,0)){CRP[6]=(float)ValueI7011/10; STCRP[6]=0;}   else STCRP[6]=1;   break;
  case 8: if (ReadVesper(1,9,0)){CRP[9]=ValueI7011; STCRP[9]=0;}   else STCRP[9]=1;             break;
 }
num_cikl++;
if (num_cikl>8) num_cikl=1;
 // опрос дозиметра
 if (ReadDVL())  StatProiz=0;
 else            StatProiz=1;
 // опрос расходомера газа
 readdat= ReadCounter(36);
 ReadPC();
// DI=32;
 try
  {
   if (QData->Active) QData->Requery(TExecuteOptions());
   else QData->Open();
   if (!QData->Bof)   QData->First();
   float tekval, oldval ;
   int   tekstat,oldstat,k;
   unsigned long     tmp;
   while (!QData->Eof)
    {
     oldval =StrToFloat(QData->FieldByName(FieldNameTekValue)->AsString.Trim());
     oldstat=StrToInt(QData->FieldByName(FieldNameTekStatus)->AsString.Trim()) ;
     if ((QData->FieldByName(FieldNameIDTag)->AsInteger>=0)&&(QData->FieldByName(FieldNameIDTag)->AsInteger<MaxCountTags))
      {
       InMin [QData->FieldByName(FieldNameIDTag)->AsInteger]=QData->FieldByName(FieldNameMinIngenering)->AsFloat;
       InMax [QData->FieldByName(FieldNameIDTag)->AsInteger]=QData->FieldByName(FieldNameMaxIngenering)->AsFloat;
       FakMin[QData->FieldByName(FieldNameIDTag)->AsInteger]=QData->FieldByName(FieldNameMinValue)->AsFloat;
       FakMax[QData->FieldByName(FieldNameIDTag)->AsInteger]=QData->FieldByName(FieldNameMaxValue)->AsFloat;
      }
     switch (QData->FieldByName(FieldNameIDTag)->AsInteger)
      {
       case  1: case  2: case  3: case  4:  case  5: // Содержание кислорода
       case  6: case  7: case  8: case  9:  case 10: // Температура в пылевой камере
       case 11: case 12: case 13: case 14:  case 15: case 16: // Резерв 5
                tekval =AI[QData->FieldByName(FieldNameIDTag)->AsInteger-1];
                tekstat=ST[QData->FieldByName(FieldNameIDTag)->AsInteger-1];
                break;
       case 17: case 18: case 19: case 20: case 21: case 22: case 23: case 24: case 25: case 26:
       case 27: case 28: case 29: case 30: case 31: case 32: case 33: case 34:
       case 35: case 36: case 37: case 38: case 39: case 40: case 41: case 42:
       case 43: case 44: case 45: case 46: case 47:
       case 48:

                tmp= QData->FieldByName(FieldNameIDTag)->AsInteger-17;
                tekval  = (DI & (unsigned long)(1<<tmp))==((unsigned long)(1<<tmp));
                if ((QData->FieldByName(FieldNameIDTag)->AsInteger==32)||// отсечной клапан свечи безопасности
                    (QData->FieldByName(FieldNameIDTag)->AsInteger==39)||
                    (QData->FieldByName(FieldNameIDTag)->AsInteger==27)||
                    (QData->FieldByName(FieldNameIDTag)->AsInteger==18) // верхняя уставка
                   ) // температура ЧРП в норме
                 {
                  tekval=1-tekval;
                 }
                tekstat = STDI[QData->FieldByName(FieldNameIDTag)->AsInteger-17 ];
                break;
       case 81: tekval  = Proiz  ;
                tekstat = StatProiz;
                if (!tekstat)
                 {
                  if ((CodeError&2048)==2048)  CodeError=CodeError-2048;
                  counterr_for_dvl=0;
                 }
                else
                 {
                  if (counterr_for_dvl>4)  CodeError=(2048|CodeError);
                  else                     counterr_for_dvl++;
                 }
                if (Proiz>=QData->FieldByName(FieldNameMinValue)->AsFloat) { wkl_sound=0; }
                else                                    { if (wkl_sound==0) wkl_sound=1; }
                break;
       case 82: tekval  = RezWork;
                if ((RezWork==6)&&(TDym->Enabled)) tekval=1;
                tekstat = 0      ;
                break;
       case 83: tekval  = CodeError;
                tekstat = 0        ;
                break;
       case 84: // Входное напряжение
                tekval  = (float)UPS_DATA.IPV/10 ;
                tekstat = read_data_ups          ;
                break;
       case 85: // Входное напряжение (fault)
                tekval  = (float)UPS_DATA.IPFV/10;
                tekstat = read_data_ups          ;
                break;
       case 86: // Выходное напряжение
                tekval  = (float)UPS_DATA.OPV/10 ;
                tekstat = read_data_ups          ;
                break;
       case 87: // Нагрузка в процентах
                tekval  = (float)UPS_DATA.NAGR   ;
                tekstat = read_data_ups          ;
                break;
       case 88: // Частота
                tekval  = (float)UPS_DATA.FREQ/10;
                tekstat = read_data_ups          ;
                break;
       case 89: // Заряд батареи в процентах
                tekval  = (float)UPS_DATA.BAT/10 ;
                tekstat = read_data_ups          ;
                break;
       case 90: // Температура
                tekval  = (float)UPS_DATA.TEMP/10;
                tekstat = read_data_ups          ;
                break;
       case 91: // нет питания
                tekval  = ((UPS_DATA.FLAG&128)==128);
                tekstat = read_data_ups             ;
                break;
       case 92: // батарея разряжена
                tekval  = ((UPS_DATA.FLAG& 64)== 64);
                tekstat = read_data_ups             ;
                break;
       case 93: // сигнал AVR
                tekval  = ((UPS_DATA.FLAG& 32)== 32);
                tekstat = read_data_ups             ;
                break;
       case 94: // недостаточно питания
                tekval  = ((UPS_DATA.FLAG& 16)== 16);
                tekstat = read_data_ups             ;
                break;
       case 95: // нет связи с UPS
                tekval  = ((UPS_DATA.FLAG&  8)==  0);
                tekstat = read_data_ups             ;
                break;
       case 96: // тестирование
                tekval  = ((UPS_DATA.FLAG&  4)==  4);
                tekstat = read_data_ups             ;
                break;
       case 97: // UPS - выключен
                tekval  = ((UPS_DATA.FLAG&  2)==  2);
                tekstat = read_data_ups             ;
                break;
       case 98: // Звуковое устройство неисправно
                tekval  = ((UPS_DATA.FLAG&  1)==  0);
                tekstat = read_data_ups             ;
                break;
       /*case  99: if ((tekval==0)&&(RezWork!=10))
                  {
                   tekval=1;
                   tekstat=0;
                  }
                 break;  */
       case  99:
       case 100:
       case 101:
       case 102:
       case 103:
       case 104:
       case 105:
       case 106:
       case 107:
       case 108:
       case 109:
       case 110:
       case 111:
       case 112:
       case 113:
       case 114:
                 tekval =StrToFloat(QData->FieldByName(FieldNameTekValue)->AsString.Trim());
                 tekstat=0 ;
                 break;
       case 115: if ((DIPV&2)==2) tekval=1;
                 else tekval=0;
                 break;
       case 116: tekval=TableZadan;
                 tekstat=0;
                 break;
       case 117: tekval=TimV; //*((double)Timer1->Interval/1000);
                 tekstat=0;
                 break;
       case 118: tekval=StepProg;
                 tekstat=0;
                 break;
       case 119:
                 tekval=CRP[0];
                 tekstat=STCRP[0];
                 break;
       case 120:
                 tekval=CRP[1];
                 tekstat=STCRP[1];
                 break;
       case 121:
                 tekval=CRP[2];
                 tekstat=STCRP[2];
                 break;
       case 122:
                 tekval=CRP[3];
                 tekstat=STCRP[3];
                 break;
       case 123:
                 tekval=CRP[4];
                 tekstat=STCRP[4];
                 break;
       case 124:  zd = oldval;
                  tekval=oldval;
                  tekstat=oldstat;

                 break;
       case 125: if (zd*10!=CRP[6])
                  ReadVesper(1,102,(WORD)zd*100);

                 tekval=CRP[6];
                 tekstat=STCRP[6];
                 // установить задание опорной частоты
                 break;
       case 126:
       case 127:
                 tekval=oldval;
                 tekstat=0;
                 break;
       case 128:

                 tekval=CRP[9];
                 tekstat=STCRP[9];
                 break;
       case 129:
                 tekval=CRP[10];
                 tekstat=STCRP[10];
                 break;
       case 133: // РАСХОД ГАЗА ПО СЧЁТЧИКУ
                 tekval=rashod_gaza;
                 if (readdat)
                 tekstat=0;
                 else tekstat=1;
                 break;
       case 131: // показания счётчика на 08:00
                  if (tim8)
                   {
                    tekval=all_rashod_gaz;
                    tekstat=0;
                   }
                  else
                   {
                    tekval=oldval;
                    tekstat=0;
                   }
                  break;
       case 132: // показания счётчика на 20:00
                  if (tim20)
                   {
                    tekval=all_rashod_gaz;
                    tekstat=0;
                   }
                  else
                   {
                    tekval=oldval;
                    tekstat=0;
                   }
                  break;
       case 130: // накопленное значение расходчика газа
                 if (readdat)
                  {
                   if (first_rash) // первый раз
                    {
                     if (oldval==0) tekval = rashod_gaza;
                     else
                     tekval        =     oldval;
                     old_value_rash=rashod_gaza;
                     first_rash    =      false;
                     tekstat       =          0;
                    }
                   else
                    {
                      if (rashod_gaza>=old_value_rash)
                       tekval=oldval+(rashod_gaza-old_value_rash);
                      else tekval=oldval; 
                      old_value_rash=rashod_gaza;
                      tekstat=0;
                    }
                  }
                 else
                  {
                   tekval=oldval;
                   tekstat=1;
                  }
                 all_rashod_gaz=tekval;
                 break;

      }
     if ((QData->FieldByName(FieldNameIDTag)->AsInteger>=49)&&
          (QData->FieldByName(FieldNameIDTag)->AsInteger<=80)
        )
     {
     }
    else
     {
      if ((QData->FieldByName(FieldNameIDTag)->AsInteger==126)&&(tekval==1))
       { ReadVesper(1,101,1);tekval=0; }
      if ((QData->FieldByName(FieldNameIDTag)->AsInteger==127)&&(tekval==1))
       {  ReadVesper(1,101,0);tekval=0; }
      if (!Debug_prog)
       {
        ValueTag[QData->FieldByName(FieldNameIDTag)->AsInteger] =tekval ;
        StatusTag[QData->FieldByName(FieldNameIDTag)->AsInteger]=tekstat;
       }
      else
       {
        ValueTag[QData->FieldByName(FieldNameIDTag)->AsInteger] =oldval ;
        StatusTag[QData->FieldByName(FieldNameIDTag)->AsInteger]=oldstat;
       }
     }
     if (!Debug_prog)
      {
       try
        {
         if ((QData->FieldByName(FieldNameIDTag)->AsInteger==99)&&
             (RezWork!=10)) tekval=1;
         else
          {
           if  ((QData->FieldByName(FieldNameIDTag)->AsInteger==99)||  // Изменение режима регулятора дымососа при входе в работу
                (QData->FieldByName(FieldNameIDTag)->AsInteger==100))  // установка задания регулятора
            {
             if (IZMREZREG)
              {
               if (QData->FieldByName(FieldNameIDTag)->AsInteger==99)       tekval =  0;
               else if (QData->FieldByName(FieldNameIDTag)->AsInteger==100) tekval = minQ*0.16+4;
               if (QData->FieldByName(FieldNameIDTag)->AsInteger==100) IZMREZREG=false;
               ValueTag[QData->FieldByName(FieldNameIDTag)->AsInteger] =tekval ;
               StatusTag[QData->FieldByName(FieldNameIDTag)->AsInteger]=tekstat;
              }
            }
          }
         if ((oldval!=tekval)||(oldstat!=tekstat))
          {
           QData->Edit();
           QData->FieldByName(FieldNameTekStatus)->AsString=IntToStr(tekstat) ;
           QData->FieldByName(FieldNameTekValue)->AsString =FloatToStr(tekval);
           QData->Post();
          }
        }
       catch (...)
        {
         if (write_to_memo1) Memo1->Lines->Add("Ошибка записи данных!");
         if (QData->State==dsEdit) { QData->CancelUpdates();ConData->Connected=false;return; }
        }
      }
     QData->Next();
    }
   if ((DIPV&2)==2)
    {
     InitConsts();
     InitTableZadan();
     }
   if (Debug_prog)
    {
     RezWork=10;
     StepProg=21;
     if (CheckBox1->Checked) ValueTag[99]=1;
     else ValueTag[99]=0;
    }
  }
 catch (...)
  {
   ConData->Connected=false;
   uart_Close(port0)  ;
   uart_Close(port4)  ;
   uart_Close(port3)  ;
   uart_Close(port5)  ;
   port0=uart_Open("")         ; if (write_to_memo1) Memo1->Lines->Add("Открытие COM0")   ;
   port4=uart_Open("COM4,9600"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM4")   ;
   port3=uart_Open("COM3,9600"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM3")   ;
   port5=uart_Open("COM5,2400"); if (write_to_memo1) Memo1->Lines->Add("Открытие COM5")   ;
  }
}
//---------------------------------------------------------------------------
void TFOpros::InitTableZadan(void)
{
 try
  {
   if (QConstReg->Active)  QConstReg->Requery(TExecuteOptions());
   else                    QConstReg->Open();
   if (!QConstReg->Bof)  QConstReg->First();
   while (!QConstReg->Eof)
    {
     if ((QConstRegIDRec->AsInteger>=1)&&(QConstRegIDRec->AsInteger<=8))
      {
       pointsr[QConstRegIDRec->AsInteger-1][0]=QConstRegInputR->AsFloat ;
       pointsr[QConstRegIDRec->AsInteger-1][1]=QConstRegOutputR->AsFloat;
      }
     QConstReg->Next();
    }
  }
 catch (...)
  {
  }
}
//---------------------------------------------------------------------------
void TFOpros::InitConsts(void)
{
 // инициализация констант
 try
  {
   //if (write_to_memo1) Memo1->Lines->Add("Инициализация констант");
   if (QListConst->Active) QListConst->Requery(TExecuteOptions());
   else QListConst->Open();
   if (!QListConst->Bof) QListConst->First();
   while (!QListConst->Eof)
    {
     switch (QListConstIDConst->AsInteger)
      {
       case 1: // Время цикла программы в мс.
               Timer1->Interval    =QListConstValueConst->AsFloat;
               break;
       case 2: // Время вентиляции пред розжигом - время включения дымососа в сек
               TDym->Interval      = 1000*QListConstValueConst->AsFloat;
               break;
       case 3: // Время закрытия клапана свечи безопасности во время первого этапа опрессовкм
               TCSB->Interval      = 1000*QListConstValueConst->AsFloat;
               break;
       case 4: // Время удержания давления газа во время второго этапа опрессовки
               TClaps->Interval    = 1000*QListConstValueConst->AsFloat;
               break;
       case 5: // Время подачи искры во время розжига
               TZap->Interval      = 1000*QListConstValueConst->AsFloat;
               break;
       case 6: // Время стабилизации факела после розжига
               TStabFak->Interval  = 1000*QListConstValueConst->AsFloat;
               break;
       case 7: // Допустимое время ожидания розжига после завершения процесса вентиляции.
               TOzPusk->Interval   = 1000*QListConstValueConst->AsFloat;
               break;
       case 8: // Время закрытия заслонки газа в сек
               TTimZakZas->Interval= 1000*QListConstValueConst->AsFloat;
               break;
       case 9: // Время срабатывания клапанов в циклах программы
               CONSTKLAP = QListConstValueConst->AsFloat;
               break;
       case 10:// Время утойчивого сигнала пламени запальника для выключения трансорматора
               CONSTCONTROL= QListConstValueConst->AsFloat;
               break;
       case 11:// время стабилизации пламени запальника в секундах
               CONSTSTABPLZAP=QListConstValueConst->AsFloat;
               break;
       case 12:// время вентиляции после аварийной ситуации
               TimerPosAvar->Interval= 1000*QListConstValueConst->AsFloat;
               break;
       case 13: // частота вентиляции.
               minQ = QListConstValueConst->AsFloat;
               break;
       case 14: //  Защита PMIN
                BLOK_PMIN = QListConstValueConst->AsFloat*(double)16/40+4;
                break;
       case 15: // Защита PMAX
                BLOK_PMAX = QListConstValueConst->AsFloat*(double)16/40+4;
       case 16: // Время пропажи напряжения
                TNoNapr->Interval  = 1000*QListConstValueConst->AsFloat;
                break;
       case 17: // Время останова при низком давлении газа
                CONSTTIMESTOPPMIN =  QListConstValueConst->AsFloat;
                break;
       case 18: // Время останова при высоком давлении газа
                CONSTTIMESTOPPMAX =  QListConstValueConst->AsFloat;
                break;
       case 19: // Время удержания кнопки квитирования в циклах программы
                CONSTCOUNTFORKVIT=QListConstValueConst->AsFloat;
                break;
       case 20: // движение МЭО P_MIN
                UST_PMIN = QListConstValueConst->AsFloat*(double)16/40+4;
                break;
       case 21: // движение МЭО P_MAX
                UST_PMAX = QListConstValueConst->AsFloat*(double)16/40+4;
                break;
       case 22: // минимальная температура выше которой начинается регулирование заслонкой
                CONSTMINTWKLREG = QListConstValueConst->AsFloat;
                break;
       case 23: // константа количество точек для усреднения
                CONSTCOUNTPOINT = QListConstValueConst->AsFloat;
                if (CONSTCOUNTPOINT<=0) CONSTCOUNTPOINT=1;
                else if (CONSTCOUNTPOINT>100) CONSTCOUNTPOINT=100;
                break;
      }
     QListConst->Next();
    }
  }
 catch (...)
  {
  }
}

//---------------------------------------------------------------------------
void __fastcall TFOpros::TDymTimer(TObject *Sender)
{
 TDym->Enabled   =false;
 LogWklDym              =0;
 ValueTag[IDTAG_UPR_DYM]=0;
 StepProg               =13;
 RezWork                =6; // Вентиляция завершена - ожидание повторного нажатия кнопки пуск
 check_sig=false;
 TOzPusk->Enabled= true;

}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TCSBTimer(TObject *Sender)
{
 // таймер закрытия свечи безопасности
 TCSB->Enabled=false;
 // открыть первый газовый клапан
 ValueTag[IDTAG_UPR_KLAP1]=     1;
 check_sig                = false;
 RezWork                  =     4; // переключение в режим ожидания давления
 StepProg                 =     6;
 SDT = SDT.CurrentDateTime() ;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TClapsTimer(TObject *Sender)
{
 // истек таймер закрытия  клапанов, после набора давления
 TClaps->Enabled=false;
 // открыть клапан свечи безопасности
 ValueTag[IDTAG_UPR_KLAPSB]= 0;
 check_sig=false;
 RezWork                   = 5;
 StepProg = 10;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TZapTimer(TObject *Sender)
{
 TZap->Enabled=false;
 StepProg = 17;
 ValueTag[IDTAG_UPR_ISKRA]  = 0; // выключить трансформатор запальника
 //RezWork=7;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TStabFakTimer(TObject *Sender)
{
 ValueTag[IDTAG_UPR_KLAPZ] =0;
 ValueTag[IDTAG_UPR_KLAPSB]=1;
 TStabFak->Enabled=false;
 RezWork=10;
 StepProg=20;
 IZMREZREG=true;
 check_sig=false;
}
//---------------------------------------------------------------------------
/*======================================================================*/
double TFOpros::PVj(int NumReg, int Razr, double Sig, int *wyh, int upr)
{
 /* Регулирование */
 int pc;
 double ret;
 if ((NumReg<0)||(NumReg>MaxCountReguls-1)) { *wyh=0;return 0.0;     }
 if (Razr==0) { Reguls.TmpVar.NumPoint[NumReg]=0;*wyh=0;return 0.0; }
 if (Reguls.TmpVar.NumPoint[NumReg]<5)
  {
   Reguls.TmpVar.PV[NumReg][Reguls.TmpVar.NumPoint[NumReg]]=Sig;
   Reguls.TmpVar.NumPoint[NumReg]++;
   *wyh=0;return 0.0;
  }
 else
  {
   /*   for (pc=0;pc<5;pc++)  Print("%f;",PV[NumReg][pc]);  Print("\r\n"); */
   if (upr==0)
    {
     for (pc=0;pc<4;pc++)
      { Reguls.TmpVar.PV[NumReg][pc]=Reguls.TmpVar.PV[NumReg][pc+1]; }
     Reguls.TmpVar.PV[NumReg][4]=Sig;
    }
   if (upr==0)
    ret=0.5*Reguls.TmpVar.PV[NumReg][4]+0.25*Reguls.TmpVar.PV[NumReg][3]+0.175*Reguls.TmpVar.PV[NumReg][2]+0.075*Reguls.TmpVar.PV[NumReg][1];
   else
    ret=0.5*Reguls.TmpVar.PV[NumReg][3]+0.25*Reguls.TmpVar.PV[NumReg][2]+0.175*Reguls.TmpVar.PV[NumReg][1]+0.075*Reguls.TmpVar.PV[NumReg][0];
   *wyh=1;
   return ret;
  }
}
/*======================================================================*/
double TFOpros::ek(double Zad, double PVj, double L, double SPrng)
{
 double ret;
 if (SPrng!=0)
  ret=(Zad-PVj)*(L+(1-L)*fabs(Zad-PVj)/SPrng);
 else
  ret=0.0;
 return ret;
}
/*======================================================================*/
double TFOpros::ebk(double Zad, double PVj, double L, double SPrng, double Betta)
{
 double ret;
 if (SPrng!=0)
  ret=(Betta*Zad-PVj)*(L+(1-L)*fabs(Betta*Zad-PVj)/SPrng);
 else
  ret=0.0;
 return ret;
}
/*======================================================================*/
double TFOpros::upk(double Zad, double PVj, double L, double SPrng, double Betta, double Kprop)
{
 /* рассчёт пропорционалльной составляющей */
 double ret;
 ret=Kprop*ebk(Zad,PVj,L,SPrng,Betta);
 return ret;
}
/*======================================================================*/
double TFOpros::udk(double PVj, double PVjm1, double Kprop, double Tdif)
{
 /* расчёт дифференциальной составляющей */
 double ret;
 ret=(-1.0*Kprop)*Tdif*(PVj-PVjm1);
/* Print("udk=%f %f %f %f %f \r\n",Kprop,Tdif,PVj,PVjm1,ret); */
 return ret;
}
/*======================================================================*/
double TFOpros::ulk(double ei, double eim1, double Kprop, double Tinteg, double SPrng, double *sum)
{
 /* расчёт интегральной составляющей */
 double ret;
 double tmp;
 if ((tmp=SPrng*SPrng)!=0.0)
  {
   tmp=1+(10*ei*ei)/tmp;
   if (tmp!=0.0)
    {
     if (Tinteg!=0)
      {
       // ret=Kprop/Tinteg*((*sum)+(ei+eim1)/2)*(1/tmp);
       // *sum=*sum+(ei+eim1)/2;
       *sum=*sum+(ei+eim1)/2*Kprop/Tinteg*(1/tmp);
       ret =*sum;
       return ret;
      }
     else return 0.0;
    }
   else return 0.0;
  }
 else return 0.0;
}
/*======================================================================*/
double TFOpros::PIDRegul(int    NumReg,  /* номер регулятора                     */
                int    Razr,    /* разрешение для регулирования         */
                int    Avt,     /* автоматическое/ручное регулирование  */
                double Zad,     /* задание                              */
                double Sig,     /* входной сигнал                       */
                double L,       /* степень линейности                   */
                double SPrng,   /* диапазон изменения задания           */
                double Betta,   /* фактор задания                       */
                double Kprop,   /* коэффициент пропорциональности       */
                double Tdif,    /* время дифференцирования              */
                double Tinteg,  /* время интегрирования                 */
                double umin,    /* минимальное управляющее воздействие  */
                double umax,    /* максимальное управляющее воздействие */
                int *upr)
{
 double vPVj,vPVjm1;
 double vei,veim1  ;
 double vupk       ;
 double vudk       ;
 double vulk       ;
 double oldval     ;
 double ret        ;
 int    wyh,wyh1   ;
 if (Razr==0)  Reguls.TmpVar.summa[NumReg]=0;
 if (Avt==0)
  {
    *upr=1;
   // if (Kprop!=0)
   //  if (NumReg==0)
     // Reguls.TmpVar.summa[NumReg]=((Zad-4)*6.25*(umax-umin)/100+umin);/**Tinteg/Kprop;*/Memo1->Lines->Add("Интеграл="+FloatToStr(Reguls.TmpVar.summa[NumReg]));
    //save_info_reg();
    return Sig;
  }
 vPVj  =PVj(NumReg,Razr,Sig,&wyh,0) ;
 vPVjm1=PVj(NumReg,Razr,Sig,&wyh1,1);
 if ((wyh==1)&&(wyh1==1))
  {
   vei   =ek(Zad,vPVj,L,SPrng)             ;
   veim1 =ek(Zad,vPVjm1,L,SPrng)           ;
   vupk  =upk(Zad,vPVj,L,SPrng,Betta,Kprop);
   vudk  =udk(vPVj,vPVjm1,Kprop,Tdif)      ;
   oldval=Reguls.TmpVar.summa[NumReg]      ;
   vulk  =ulk(vei,veim1,Kprop,Tinteg,SPrng,&Reguls.TmpVar.summa[NumReg]);
   ret=vupk+vudk+vulk;
   if (NumReg==0)
    {
     if (write_to_memo1) Memo1->Lines->Add("kp="+FloatToStr(Reguls.KRegul[0].KProp)+";Zad="+FloatToStr(Reguls.KRegul[0].Zadan)+";Wyhod="+FloatToStr(ret)+";vulk="+FloatToStr(vulk));
    }
   if (Reguls.TmpVar.pri==1)
    {
     //Print("%f;%f;%f\r\n",vupk,vudk,vulk);
     Reguls.TmpVar.pri=0;
    }
/*   Print("ret=%f\r\n",ret);*/
   if (ret>umax) {/* Print("Save=%f\r\n",oldval);*/ Reguls.TmpVar.summa[NumReg]=oldval;ret=umax; }
   if (ret<umin) {/* Print("Save=%f\r\n",oldval);*/ Reguls.TmpVar.summa[NumReg]=oldval;ret=umin; }
   *upr=1;
   //save_info_reg();
   return ret;
  }
 else
  {
   //Reguls.TmpVar.summa[NumReg]=0;
   *upr  =0;
   //save_info_reg();
   return 0;
  }
}
/*======================================================================*/
bool __fastcall TFOpros::InitReguls(int num_reg)
{
 bool ret=true;
 double tmp=0;
 switch (num_reg) // аналоговые регуляторы
  {

   case 0:  // регулятор разряжения
            Reguls.KRegul[num_reg].Auto    = ValueTag[ 99+num_reg*8];if (StatusTag[ 99+num_reg*8]!=0) ret=false;
            for (int k=0;k<CONSTCOUNTPOINT;k++)
             { tmp=tmp+massiv_p_gaza[k]; }
            /*if (CONSTCOUNTPOINT==0)*/ tmp=ValueTag[IDTAG_RASHOD];//rashod_gaza; //ValueTag[IDTAG_PGAZA];
            //else tmp=tmp/CONSTCOUNTPOINT;
            TableZadan =  GetValueFromTable(tmp);
            if ((RezWork!=10)||(Reguls.KRegul[num_reg].Auto==0))
             {
              Reguls.KRegul[num_reg].Zadan   = ValueTag[100+num_reg*8];if (StatusTag[100+num_reg*8]!=0) ret=false;
              Reguls.TmpVar.summa[num_reg]   = ((ValueTag[13]-4)*6.25)*2-100;
             }
            else
             {
              Reguls.KRegul[num_reg].Zadan   = TableZadan; //++? Задание для регулятора
             }
            Reguls.KRegul[num_reg].StepLin = ValueTag[101+num_reg*8];if (StatusTag[101+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].DiapIzm = ValueTag[102+num_reg*8];if (StatusTag[102+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].FaktZad = ValueTag[103+num_reg*8];if (StatusTag[103+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].KProp   = ValueTag[104+num_reg*8];if (StatusTag[104+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].TimInt  = ValueTag[105+num_reg*8];if (StatusTag[105+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].TimDif  = ValueTag[106+num_reg*8];if (StatusTag[106+num_reg*8]!=0) ret=false;
            if (Reguls.KRegul[num_reg].Auto==0) // ручное управление
             {
              Reguls.KRegul[num_reg].Whod   = Reguls.KRegul[num_reg].Zadan;
              Reguls.KRegul[num_reg].MaxVal = 100 ;
              Reguls.KRegul[num_reg].MinVal = 0   ;
             }
            else // Автоматическое управление
             {
              Reguls.KRegul[num_reg].Whod   =  (ValueTag [1]-4) * 6.25  ;if (StatusTag[1]!=0) ret=false;
              Reguls.KRegul[num_reg].MaxVal = 100;
              Reguls.KRegul[num_reg].MinVal = 0  ;
             }
            break;
   case 1:  // регулятор тепературы топки
            Reguls.KRegul[num_reg].Auto   = ValueTag[ 99+num_reg*8];if (StatusTag[ 99+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].Zadan  = ValueTag[100+num_reg*8];if (StatusTag[100+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].StepLin= ValueTag[101+num_reg*8];if (StatusTag[101+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].DiapIzm= ValueTag[102+num_reg*8];if (StatusTag[102+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].FaktZad= ValueTag[103+num_reg*8];if (StatusTag[103+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].KProp  = ValueTag[104+num_reg*8];if (StatusTag[104+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].TimInt = ValueTag[105+num_reg*8];if (StatusTag[105+num_reg*8]!=0) ret=false;
            Reguls.KRegul[num_reg].TimDif = ValueTag[106+num_reg*8];if (StatusTag[106+num_reg*8]!=0) ret=false;
            if (Reguls.KRegul[num_reg].Auto==0) // ручное управление
             {
              Reguls.KRegul[num_reg].Whod   = Reguls.KRegul[num_reg].Zadan;
              Reguls.KRegul[num_reg].MaxVal = 100  ;
              Reguls.KRegul[num_reg].MinVal = 0    ;
             }
            else // Автоматическое управление
             {
              Reguls.KRegul[num_reg].Whod   = ValueTag[10];if (StatusTag[10]!=0) ret=false;
              Reguls.KRegul[num_reg].MaxVal = 100 ;
              Reguls.KRegul[num_reg].MinVal = 0   ;
             }
            break;
   default: ret=false;
  }
 return ret;
}
//---------------------------------------------------------------------------
double TFOpros::GetValueFromTable(double val1)
{
 // Задание регулятора в % от шкалы 0..360
 int diap=-1;
 double faktv;
 double shkalp;
 double shkalr;
 double k;
 double value=(val1-4)*((double)9500/16.0);// val1*2.5-10;/*((double)40.0/16.0); */
 for (int i=0;i<7;i++)
  {
   if ((value>=pointsr[i][0])&&(value<=pointsr[i+1][0])) { diap=i;break; }
  }
 if (diap==-1)
  {
   if (value<pointsr[0][0]) faktv=pointsr[0][1];
   else                     faktv=pointsr[7][1];
  }
 else
  {
   shkalp=pointsr[diap+1][0]-pointsr[diap][0];
   shkalr=pointsr[diap+1][1]-pointsr[diap][1];
   k=shkalr/shkalp;
   faktv=k*(value-pointsr[diap][0])+pointsr[diap][1];
  }
 //if (write_to_memo1) Memo1->Lines->Add(FloatToStr(faktv)+";"+FloatToStr(value)+";"+FloatToStr(diap));
 return faktv*((double)10/63);
}
//---------------------------------------------------------------
void TFOpros::SetCodeError(unsigned long value)
{
 if (FCodeError!=value)
  {

   FCodeError=value;
   //bool wr_sob=true;
   //switch (RezWork)
  // if (wr_sob)   WriteSobyt();
  }
}
//---------------------------------------------------------------
void TFOpros::SetRezWork(int value)
{
 if (FRezWork!=value)
  {
   if (value==9)
    {
     if (FRezWork==10) bylpusk=true; else bylpusk=false;
     ValueTag[IDTAG_UPR_SOUND]=1;
     TOzPusk->Enabled= true;
     //LogWklDym              =1;
     if (write_to_memo1) Memo1->Lines->Add("Авария");
     //ValueTag[IDTAG_UPR_DYM]=1;
    }
   FRezWork=value;
   if ((value==0)||(value==9)||(value==10)||(value==1))
    WriteSobyt()  ;// изменение режима
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::Reguls_run(void)
{
 // алгоритмы регулирования
 for (int nreg=0;nreg<MaxCountReguls;nreg++)
  {
   if (InitReguls(nreg)) // инициализация структуры для конкретного регулятора
    {
     if ((nreg==0)&&(RezWork!=10)) // не вошёл в режим работы - запрет изменения выхода дымасоса, установка заранее заданного значения
      {
       float new_out;
       new_out=minQ*0.16+4;
       if (!Debug_prog)  pac_WriteAO(port0,3,0,4,new_out);
      }
     else if (nreg==0)// вошёл в режим работы
      {
         if ((ValueTag[IDTAG_DYM_OFF]==1)||(Reguls.KRegul[nreg].Auto==0)) // дымосос включён или регулятор в ручном режиме
          {
           double Wyhod = PIDRegul(nreg,
                                      1,
                                   Reguls.KRegul[nreg].Auto,
                                   Reguls.KRegul[nreg].Zadan,
                                   Reguls.KRegul[nreg].Whod,
                                   Reguls.KRegul[nreg].StepLin,
                                   Reguls.KRegul[nreg].DiapIzm,
                                   Reguls.KRegul[nreg].FaktZad,
                                   Reguls.KRegul[nreg].KProp,
                                   Reguls.KRegul[nreg].TimDif,
                                   Reguls.KRegul[nreg].TimInt, -100, 100,
                                   &Reguls.TmpVar.razr[nreg]);
           if (Reguls.TmpVar.razr[nreg]) Reguls.KRegul[nreg].Wyhod=Wyhod;
           float new_out;
           if (Reguls.KRegul[nreg].Auto==0) // ручное управление - выход 0..100  в БД 4-20 мA
            {
             new_out=Reguls.KRegul[nreg].Wyhod;
             if (RezWork!=10) new_out=minQ*0.16+4;
            }
           else
            {
             if (Reguls.TmpVar.razr[nreg])   // выход -100..100
              {
               new_out=Reguls.KRegul[nreg].Zadan*0.16+4; // отключить пид регулятор задание в % на выход
               //++? включить пид регулятор new_out=(Wyhod+100)*0.5*0.16+4;
              // if (write_to_memo1) Memo1->Lines->Add(FloatToStr(new_out));
              }
             else new_out=minQ*0.16+4;
            }
           if (new_out<4)   new_out=4;
           if (new_out>20) new_out=20;
           if (!Debug_prog) pac_WriteAO(port0,3,0,4,new_out);
         }
        else  { /* заморозить выход */ } // дымосос выключен и регулятор в автоматическом режиме
      } // закончена обработка вошёл в основной режим работы
    } // закончена обработка регулятора по разрежению
   if (nreg==1) // регулятор температуры в пылевой камере
    {
    }
  }

}


void __fastcall TFOpros::TOzPuskTimer(TObject *Sender)
{
 // таймер ожидания нажатия пуска вентиляции
 RezWork=0;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TimerPosAvarTimer(TObject *Sender)
{
 TimerPosAvar->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::TNoNaprTimer(TObject *Sender)
{
 TNoNapr->Enabled=false;
 if ((RezWork!=0)&&(RezWork!=9)&&(RezWork!=11))
  {
   RezWork=9;
   CodeError=CodeError|67108864;
  }

}
//---------------------------------------------------------------------------

void __fastcall TFOpros::TObrOtsTimer(TObject *Sender)
{
 if (TimV>0) TimV--;
 else TObrOts->Enabled=false;
}
//---------------------------------------------------------------------------


