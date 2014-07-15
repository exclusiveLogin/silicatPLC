//---------------------------------------------------------------------------

#include <vcl.h>
#include <mmsystem.hpp>
#pragma hdrstop

#include "FormOpros.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFOpros *FOpros;
//---------------------------------------------------------------------------
__fastcall TFOpros::TFOpros(TComponent* Owner)
        : TForm(Owner)
{
 AnsiString TmpFile      ;
 AnsiString TekDir       ;
 TIniFile   *Ini         ;
 char       NameFile[255];
 // чтение установочного файла
 for (int i=0;i<50;i++) StatusUstr[i]=1;
 GetCurrentDirectory(255,NameFile);
 TekDir    =NameFile;
 TmpFile = (String) NameFile + "\\wmb.ini";
 if (FileExists(TmpFile))
  {
   if ((Ini = new TIniFile(TmpFile))!=NULL)
    {
     const_tim_out_k3    = 60;
     const_tim_out_zk3   =  2;
     const_tim_out_obsk  = 60;
     const_tim_out_zobsk =  1;
     const_tim_out_kde_1 = 60;
     const_tim_out_kde_2 = 60;
     const_tim_out_zkde_1=  2;
     const_tim_out_zkde_2=  2;
//     NumPortModbus=Ini->ReadInteger("PORTS","ComPortModbus",3);
//     if ((NumPortModbus>0)&&(NumPortModbus<=CountMaxPorts))
//      {
//       BaundRate[NumPortModbus-1] = Ini->ReadInteger("PORTS","BaundRateModbus",0)          ;
//       ByteSize[NumPortModbus-1]  = Ini->ReadInteger("PORTS","ByteSizeModbus",0)              ;
//       Parity[NumPortModbus-1]    = Ini->ReadInteger("PORTS","ParityModbus",0)                ;
//       StopBits[NumPortModbus-1]  = Ini->ReadInteger("PORTS","StopBitsModbus",0)              ;
//       RInterval[NumPortModbus-1] = Ini->ReadInteger("PORTS","TimeOutModbus",0)               ;
//       RCInterval[NumPortModbus-1]= Ini->ReadInteger("PORTS","TimeOutConstantModbus",0)       ;
//       RMInterval[NumPortModbus-1]= Ini->ReadInteger("PORTS","TimeOutMultiplieModbus",0)     ;
//       WCInterval[NumPortModbus-1]= Ini->ReadInteger("PORTS","TimeOutConstantWriteModbus",0)  ;
//       WMInterval[NumPortModbus-1]= Ini->ReadInteger("PORTS","TimeOutMultiplierWriteModbus",0);
//       count_cikl_time_out_modbus = Ini->ReadInteger("TIMERS","TimeOutModbus",0)              ; // задержка на ожидание ответа по Modbus протоколу
       Lic                        = Ini->ReadInteger("USER","Lic",1000)                       ;
       ModeApp                    = Ini->ReadInteger("DISK","Mode",0)                         ;
//      }
//     else Application->MessageBoxA("Не правильно указан порт!","Внимание!",MB_OK+MB_ICONSTOP);
     delete Ini;
    }
   else throw Exception("Отсутствует установочный файл Opros.Ini");
  }
 else throw Exception("Отсутствует установочный файл Opros.Ini");
 if (!ModeApp)
  {
   FOpros->Visible=false;Application->ShowMainForm=false;
  }
 // Определить ID последней записи в архиве
 for (int i=0;i<CountTimers;i++)
  {
   TimersInfo[i].begin   = DateTimeToTimeStamp(Now());
   TimersInfo[i].end     = DateTimeToTimeStamp(Now());
   TimersInfo[i].OnTimer = true ;
   TimersInfo[i].dlit    = 10000;
  }
 TekIDSob = GetLastRecordArhivSob();
 QListTags->Open();
 int Count = 0;
 while (!QListTags->Eof)
  {
   if (QListTagsIDTag->AsInteger<10000) Count++;
   QListTags->Next();
  }
 if (!QListTags->Bof) QListTags->First();
 Arhiv                = new MyArhiv(this,Lic,1000);
 Arhiv->OnActiveArhiv = InitArhiv;
 Arhiv->ActiveWrite   = true     ;
// копирование шкал из БД
 if (!QListTags->Bof) QListTags->First();
 while (!QListTags->Eof)
  {
    switch (QListTagsIDTag->AsInteger)
     {
      case 101: RegFl[SH4ma_PT201]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT201]=QListTagsMaxVal->AsFloat;break;
      case 102: RegFl[SH4ma_PT202]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT202]=QListTagsMaxVal->AsFloat;break;
      case 103: RegFl[SH4ma_PT203]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT203]=QListTagsMaxVal->AsFloat;break;
      case 104: RegFl[SH4ma_PT204]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT204]=QListTagsMaxVal->AsFloat;break;
      case 105: RegFl[SH4ma_PT205]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT205]=QListTagsMaxVal->AsFloat;break;
      case 106: RegFl[SH4ma_LI401]=QListTagsMinVal->AsFloat;RegFl[SH20ma_LI401]=QListTagsMaxVal->AsFloat;break;
      case 107: RegFl[SH4ma_LI402]=QListTagsMinVal->AsFloat;RegFl[SH20ma_LI402]=QListTagsMaxVal->AsFloat;break;
      case 109: RegFl[SH4ma_LI403]=QListTagsMinVal->AsFloat;RegFl[SH20ma_LI403]=QListTagsMaxVal->AsFloat;break;
      case 110: RegFl[SH4ma_PT206]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT206]=QListTagsMaxVal->AsFloat;break;
      case 111: RegFl[SH4ma_LI404]=QListTagsMinVal->AsFloat;RegFl[SH20ma_LI404]=QListTagsMaxVal->AsFloat;break;
      case 112: RegFl[SH4ma_PT207]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT207]=QListTagsMaxVal->AsFloat;break;
      case 117: RegFl[SH4ma_PT210]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT210]=QListTagsMaxVal->AsFloat;break;
      case 118: RegFl[SH4ma_PT211]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT211]=QListTagsMaxVal->AsFloat;break;
      case 119: RegFl[SH4ma_PT212]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT212]=QListTagsMaxVal->AsFloat;break;
      case 120: RegFl[SH4ma_PT213]=QListTagsMinVal->AsFloat;RegFl[SH20ma_PT213]=QListTagsMaxVal->AsFloat;break;
     }
    QListTags->Next();
  }

// Send_Modbus(1,6);Sleep(100);
// Send_Modbus(1,5);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::InitArhiv(TObject *Sender, bool &Active, int *IDTag, double *Val, int *Stat)
{
 if (!QListTags->Active) Active=false;
 else
  {
   if (!QListTags->Bof) QListTags->First();
   int sm =0;
   while (!QListTags->Eof)
    {
     if (QListTagsIDTag->AsInteger<Lic) // CountActiveTags)
      {
       IDTag[sm]=QListTagsIDTag->AsInteger    ;
       Val[sm]  =QListTagsValueTag->AsFloat   ;
       Stat[sm] =QListTagsStatusTag->AsInteger;
       sm++;
       if (sm>Arhiv->CountTags) break;
      }
     QListTags->Next();
    }
   Active=true;
  }
}
//---------------------------------------------------------------------------
/*int __fastcall TFOpros::ReadDataCom(HANDLE ComPort, unsigned char *buffer, unsigned int MaxLenBuffer)
{
 unsigned long BytesRead=0;
 unsigned int  Index    =0;
 if (ComPort==NULL) return 0;
 do
  {
   if (!ReadFile(ComPort, (buffer+Index), 1, &BytesRead, NULL)) // возникла ошибка
    {
     GetLastError(); return 0;
    }
   else if (BytesRead==1) Index++;
  }
 while ((BytesRead!=0)&&(Index<MaxLenBuffer));
 return Index;
} */
//---------------------------------------------------------------------------
/*bool __fastcall TFOpros::WriteDataCom(HANDLE ComPort, unsigned char *buffer, unsigned long CountBytes)
{
 // передача данных в порт
 unsigned long BytesWrite;
 if (ComPort==NULL) return false;
 if (CountBytes==0)  return false;
 if (!WriteFile(ComPort, buffer, CountBytes, &BytesWrite, NULL))
  {
   GetLastError();
   return false  ;
  }
 if (BytesWrite==0)          return false;
 if (CountBytes!=BytesWrite) return false;
 return true;
} */
//---------------------------------------------------------------------------
/*bool TFOpros::Send_Modbus(int AdressUstr, int NumParam)
{
 // отсылка команды по MODBUS протоколу
 unsigned char command[80]; // команда по Modbus
 unsigned char ansver[255]; // ответ   по Modbus
 int           bytz = 6   ; // количество байт в запросе
 union
  {
   unsigned char c[2];
   short int     val ;
  } tmpint;
 if (Port_Modbus==NULL) Port_Modbus = OpenPort(NumPortModbus,NULL); // открытие порта
 if (Port_Modbus!=NULL)
  {
   command[ 0] = AdressUstr; // адрес устройства
   command[ 1] = 0x03      ; // команда чтения
   switch (NumParam)
    {
     case 0:  // опрос первых 10-ти регистров - 20 байт 0..9
              command[2] = 0x00;
              command[3] = 0x00; // начиная с нулевого адреса
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 1:  // опрос первых 10-ти регистров - 20 байт
              command[2] = 0x00;
              command[3] = 0x0A; // начиная с 10 адреса
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 2:  // опрос первых 10-ти регистров - 20 байт
              command[2] = 0x00;
              command[3] = 0x14; // начиная с 20 адреса
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 3:  // опрос первых 10-ти регистров - 20 байт
              command[2] = 0x00;
              command[3] = 0x1E; // начиная с 30 адреса
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 4:  // опрос первых 10-ти регистров - 20 байт
              command[2] = 0x00;
              command[3] = 0x28; // начиная с 40 адреса
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 5: // запись задания
              command[1] = 0x06;
              command[2] = 0x00;
              command[3] = 0x2F; // адрес уставки регулятора 2C 2F 30
              tmpint.val =  102;
              command[4] = tmpint.c[1];
              command[5] = tmpint.c[0];
              break;
     case 6: // переключение в режим удаленной установки задания
              command[1] = 0x06;
              command[2] = 0x00;
              command[3] = 0x2B; // адрес уставки регулятора
              tmpint.val =    1;
              command[4] = tmpint.c[1];
              command[5] = tmpint.c[0];
              break;
     default: return false;
    }
   WORD tt=Crc16(command,bytz);
   command[bytz]  = (BYTE) tt    ;
   command[bytz+1]= (BYTE)(tt>>8);
   if (!WriteDataCom(Port_Modbus, command, bytz+2)) // отослать команду
    { Port_Modbus = OpenPort(NumPortModbus,Port_Modbus);return false; } // закрыть порт в случае ошибки
   else return true;
  }
 else   return false;
} */
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForK3(int NumCom)
{
 unsigned char buf[1024];
 buf[0]=0;
 buf[1]=0;
 buf[2]=0;
 buf[3]=0;
 buf[4]=0;
 buf[5]=6;
 buf[6]=1;
 switch (NumCom)
  {
   case 0: buf[7]=3;break;
   case 1: buf[7]=1;break;
  }
 buf[8] = 0;
 buf[9] = 0; // адрес == 0
 buf[10]= 0;
 buf[11]=50; // количество переменных для указанного адреса
 ClientSocket1->Socket->SendBuf(buf,12);
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetFloatIndex(int Index)
{
 int ret=Index/2;
 return ret;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForDE_1(int NumCom)
{
 // команды опроса для ДЕ-1 (котёл №3)
 // - значение 03
 // 0 - опрос MW0   .. MW103     0.. 51
 // 1 - опрос WM104 .. MW207    52..103
 // 2 - опрос MW208 .. MW311   104..155
 // 3 - опрос MW312 .. MW415   156..207
 // - статус значения 04
 // 4 - опрос MW0   .. MW103     0.. 103
 // 5 - опрос WM104 .. MW207   104.. 207
 unsigned char buf[1024];
 union
  {
   unsigned char c[4];
   unsigned short int i[2];
   float   f;
  } tmp;
 union
  {
   unsigned char      c[2];
   unsigned short int i   ;
  } tmp1;
 int           len_com = 12 ;
 AnsiString tmp_str;
 switch (NumCom)
  {
   case 0: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0x68; // смещение адрес == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0xD0; // смещение адрес == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    =104 ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x01;buf[9] =0x38; // смещение адрес == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    =156 ;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    =   0;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x68; // смещение адрес == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_1    = 104;
           break;
   case 101:
   case 100: // запись вещественного значения
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// команда записи
             tmp1.i = WriteAdress_DE1[WrIndexBuf_DE1];
             buf[8] = tmp1.c[1];     // смещение адрес == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 слова == 0x68
             buf[12]=0x04; // количество байт
             // значение
             tmp.f   = WriteVal_DE1[WrIndexBuf_DE1];
             buf[13] = tmp.c[1];
             buf[14] = tmp.c[0];
             buf[15] = tmp.c[3];
             buf[16] = tmp.c[2];
            // tmp_str = "Передача параметра по адресу " + IntToStr(tmp1.i) + " значение = " + FloatToStr(tmp.f);
            // Application->MessageBoxA(tmp_str.c_str(),"Внимание!",MB_OK+MB_ICONSTOP);
             len_com=17;
             break;
   default : len_com=17;NumParam_ForDE_1=-1;break;
  }
 ClientSocket3->Socket->SendBuf(buf,len_com);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForDE_2(int NumCom)
{
 // команды опроса для ДЕ-2 (котёл №4)
 // - значение 03
 // 0 - опрос MW0   .. MW103     0.. 51
 // 1 - опрос WM104 .. MW207    52..103
 // 2 - опрос MW208 .. MW311   104..155
 // 3 - опрос MW312 .. MW415   156..207
 // - статус значения 04
 // 4 - опрос MW0   .. MW103     0.. 103
 // 5 - опрос WM104 .. MW207   104.. 207
 unsigned char buf[1024];
 union
  {
   unsigned char c[4];
   unsigned short int i[2];
   float   f;
  } tmp;
 union
  {
   unsigned char      c[2];
   unsigned short int i   ;
  } tmp1;
 int           len_com = 12 ;
 AnsiString tmp_str;
 switch (NumCom)
  {
   case 0: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0x68; // смещение адрес == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x00;buf[9] =0xD0; // смещение адрес == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    =104 ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // команда чтения
           buf[8] =0x01;buf[9] =0x38; // смещение адрес == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    =156 ;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    =   0;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x68; // смещение адрес == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForDE_2    = 104;
           break;
   case 101:
   case 100: // запись вещественного значения
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// команда записи
             tmp1.i = WriteAdress_DE2[WrIndexBuf_DE2];
             buf[8] = tmp1.c[1];     // смещение адрес == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 слова == 0x68
             buf[12]=0x04; // количество байт
             // значение
             tmp.f   = WriteVal_DE2[WrIndexBuf_DE2];
             buf[13] = tmp.c[1];
             buf[14] = tmp.c[0];
             buf[15] = tmp.c[3];
             buf[16] = tmp.c[2];
            // tmp_str = "Передача параметра по адресу " + IntToStr(tmp1.i) + " значение = " + FloatToStr(tmp.f);
            // Application->MessageBoxA(tmp_str.c_str(),"Внимание!",MB_OK+MB_ICONSTOP);
             len_com=17;
             break;
   default : len_com=17;NumParam_ForDE_2=-1;break;
  }
 ClientSocket4->Socket->SendBuf(buf,len_com);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForObsK(int NumCom)
{
 // команды опроса
 // 0 - опрос MW0  .. MW103                         +0     0.. 103   0
 // 1 - опрос MW104.. MW207                         +1   104.. 207   52
 // 2 - опрос MW416.. MW519                         +8   208.. 311   104
 // 3 - опрос MW520.. MW523                         +9   312.. 415   156
 // 4 - опрос MW832.. MW935                         +2   416.. 519   208
 // 5 - опрос M0   ..                               +3   520.. 523   260
 //                                                 +10  624.. 727   312
 // 6 - опрос MW936.. MW1039                        +7   728.. 831   364
 // 7 - опрос MW728.. MW831                         +4   832.. 935   416
 // 8 - опрос MW208.. MW311                         +6   936..1039   468
 // 9 - опрос MW312.. MW415
 // 10- опрос MW624.. MW727
 unsigned char buf[1024];
 union
  {
   unsigned char c[4];
   unsigned short int i[2];
   float   f;
  } tmp;
 union
  {
   unsigned char      c[2];
   unsigned short int i   ;
  } tmp1;
 int len_com=12;
 switch (NumCom)
  {
   case 0: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0x68; // смещение адрес == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x01;buf[9] =0xA0; // смещение адрес == 416 ~ 0x01A0
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    = 208; // 52  ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x02;buf[9] =0x08; // смещение адрес == 208 ~ 0x0208
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    = 260;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x03;buf[9] =0x40; // смещение адрес == 832 ~ 0x0340
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    = 416;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x01; // команда чтения
           buf[8] =0x00;buf[9] =0x00; // смещение адрес == 0 ~ 0x0000
           buf[10]=0x02;buf[11]=0x00; // число бит 1024 0x400  1024/8 = 128 байт = 64 слова
           NumParam_ForOBSK    =  -2;
           break;
   case 6: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x03;buf[9] =0xA8; // смещение адрес == 936 ~ 0x03A8
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =468 ;
           break;
   case 7: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x02;buf[9] =0xD8; // смещение адрес == 728 ~ 0x02D8
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =364 ;
           break;
   case 8: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x00;buf[9] =0xD0; // смещение адрес == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =104 ;
           break;
   case 9: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x01;buf[9] =0x38; // смещение адрес == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =156 ;
           break;
   case 10: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // команда чтения
           buf[8] =0x02;buf[9] =0x70; // смещение адрес == 624 ~ 0x0270
           buf[10]=0x00;buf[11]=0x68; // 104 слова == 0x68
           NumParam_ForOBSK    =312 ;
           break;
   case 101: // запись одного бита
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
             buf[7] =0x05;// команда записи одного бита
             tmp1.i = WriteAdress[WrIndexBuf];
             buf[8] = tmp1.c[1];     // смещение адрес
             buf[9] = tmp1.c[0];
             if (WriteVal[WrIndexBuf]==1) buf[10]=0xFF;
             else                         buf[10]=0x00;
             buf[11]=0x00;
             len_com=12;
             break;
   case 100: // запись вещественного значения
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// команда записи
             tmp1.i = WriteAdress[WrIndexBuf];
             buf[8] = tmp1.c[1];     // смещение адрес == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 слова == 0x68
             buf[12]=0x04; // количество байт
             // значение
             tmp.f   = WriteVal[WrIndexBuf];
             buf[13] = tmp.c[1];
             buf[14] = tmp.c[0];
             buf[15] = tmp.c[3];
             buf[16] = tmp.c[2];
             len_com=17;
             break;
   default : len_com=17;NumParam_ForOBSK=-1;break;


  }
/* buf[0]=0;
 buf[1]=0;
 buf[2]=0;
 buf[3]=0;
 buf[4]=0;
 buf[5]=11; //6
 buf[6]=1;
 switch (NumCom)
  {
   case 0: buf[7] =0x10; // команда записи
           buf[8] =0x00;
           buf[9] =0x02; // смещение, адрес == 1
           buf[10]=0x00;
           buf[11]=0x02; // количество слов
           buf[12]=0x04; // количество байт
           tmp.f = 2500;
           buf[13]=tmp.c[1];
           buf[14]=tmp.c[0]; // количество переменных для указанного адреса
           buf[15]=tmp.c[3];
           buf[16]=tmp.c[2]; // количество слов
           break;
//   case 1: buf[7]=1;break;
  } */
 ClientSocket2->Socket->SendBuf(buf,len_com);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::Timer1Timer(TObject *Sender)
{
 static unsigned int tim_out_k3=0 ;
 static unsigned int tim_out_zk3=0;
 static unsigned int num_zap_k3=0 ;
 static unsigned int tim_out_obsk=0 ; // тайм-аут для общекотельной автоматики. Время прошедшее с момента отсутствия соединения
 static unsigned int tim_out_zobsk=0; // тайм-аут для общекотельной автоматики. Время прошедшее с момента последнего запроса
 static unsigned int num_zap_obsk=0 ; // номер запроса для общекотельой автоматики
 static unsigned int tim_out_kde_1 = 0;
 static unsigned int tim_out_zkde_1= 0;
 static unsigned int num_zap_kde_1 = 0;
 static unsigned int tim_out_kde_2 = 0;
 static unsigned int tim_out_zkde_2= 0;
 static unsigned int num_zap_kde_2 = 0;
 static int cc=0;
 unsigned int count_zap_obsk  = 11   ; // количество (видов) запросов к общекотельной автоматике
 unsigned int count_zap_kde_1 =  6   ; // количество (видов  запросов к котлу ДЕ - №1 (котёл №3)
 unsigned int count_zap_kde_2 =  6   ; // количество (видов  запросов к котлу ДЕ - №2 (котёл №4)
  // Опрос переменных
 Timer1->Enabled=false;
 // Опрос раз в секунду
 try
  {
   // опрос параметров общекотельной автоматики
   if (ClientSocket2->Socket!=NULL)
    if (ClientSocket2->Socket->Connected) // соединение установлено
     {
      tim_out_zobsk++;
      if ((tim_out_obsk%const_tim_out_obsk)==1) // периодический запрос
       {
        bool byl=false;
        if (WrVal[WrIndexBuf]) // необходимость записи значения
         SendCommandForObsK(WrNumZap[WrIndexBuf]);
        else
         SendCommandForObsK(num_zap_obsk);
        num_zap_obsk++;
        if (num_zap_obsk==count_zap_obsk) num_zap_obsk=0;
       }
      if (tim_out_zobsk==const_tim_out_obsk) { tim_out_zobsk=0;WrVal[WrIndexBuf]=false;WrIndexBuf--;if (WrIndexBuf<0) WrIndexBuf=0; } // сброс тайм-аута при превышении порога
     }
    else // нет соединения
     {
      tim_out_obsk++;                             // тайм-аут отсутствия соединения
      if ((tim_out_obsk%const_tim_out_obsk)==1)   // истёк тайм-аут ожидания соединения
       {
        ClientSocket2->Open();                   // попытка открыть соединение
       }
      if (tim_out_obsk==const_tim_out_obsk) tim_out_obsk=0; // сброс тайм-аута при превышении порога
     }
    else
     int pc=0;

   if (ClientSocket1->Socket!=NULL)
    if (ClientSocket1->Socket->Connected) // соединение установлено
     {
      tim_out_zk3++;
      if ((tim_out_zk3%const_tim_out_zk3)==1)
       {
        SendCommandForK3(num_zap_k3);
        num_zap_k3++;
        if (num_zap_k3==2) num_zap_k3=0;
       }
      if (tim_out_zk3==const_tim_out_zk3) tim_out_zk3=0;
     }
    else // нет соединения
     {
      tim_out_k3++;
      if ((tim_out_k3%const_tim_out_k3)==1)
       {
        ClientSocket1->Open();
       }
      if (tim_out_k3==const_tim_out_k3) tim_out_k3=0;
     }
    else
     int pc=0;
   if (ClientSocket3->Socket!=NULL)
    if (ClientSocket3->Socket->Connected) // соединение установлено
     {
      tim_out_zkde_1++;
      if ((tim_out_zkde_1%const_tim_out_zkde_1)==1)
       {
        bool byl=false;
        if (WrVal_DE1[WrIndexBuf_DE1])
         SendCommandForDE_1(WrNumZap_DE1[WrIndexBuf_DE1]);
        else
         SendCommandForDE_1(num_zap_kde_1);
        num_zap_kde_1++;
        if (num_zap_kde_1==count_zap_kde_1) num_zap_kde_1=0;
       }
      if (tim_out_zkde_1==const_tim_out_zkde_1) tim_out_zkde_1=0;
     }
    else // нет соединения
     {
      tim_out_kde_1++;
      if ((tim_out_kde_1%const_tim_out_kde_1)==1)
       {
        ClientSocket3->Open();
       }
      if (tim_out_kde_1==const_tim_out_kde_1) tim_out_kde_1=0;
     }
    else
     int pc=0;
   if (ClientSocket4->Socket!=NULL)
    if (ClientSocket4->Socket->Connected) // соединение установлено
     {
      tim_out_zkde_2++;
      if ((tim_out_zkde_2%const_tim_out_zkde_2)==1)
       {
        bool byl=false;
        if (WrVal_DE2[WrIndexBuf_DE2])
         SendCommandForDE_2(WrNumZap_DE2[WrIndexBuf_DE2]);
        else
         SendCommandForDE_2(num_zap_kde_2);
        num_zap_kde_2++;
        if (num_zap_kde_2==count_zap_kde_2) num_zap_kde_2=0;
       }
      if (tim_out_zkde_2==const_tim_out_zkde_2) tim_out_zkde_2=0;
     }
    else // нет соединения
     {
      tim_out_kde_2++;
      if ((tim_out_kde_2%const_tim_out_kde_2)==1)
       {
        ClientSocket4->Open();
       }
      if (tim_out_kde_2==const_tim_out_kde_2) tim_out_kde_2=0;
     }
    else
     int pc=0;
   WriteData();

   if (Reg[223]==1)
    {
     if ((cc%3)==0) { sndPlaySound("td.wav",SND_SYNC);cc++; }
     else cc++;
    }
   else cc=0;
  }
 catch (...) { }
 Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
WORD TFOpros::Crc16(BYTE *Data, ULONG size)
{
 union
  {
   BYTE b[2];
   unsigned short w;
  } Sum;
 char shift_cnt;
 BYTE  *ptrByte;
 ULONG byte_cnt = size;

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
/*HANDLE __fastcall TFOpros::OpenPort(int NumCom1, HANDLE ComPort)
{
 static int sav[CountMaxPorts]={0,0,0,0,0,0,0,0,0,0} ;
 int NumCom=NumCom1;
 AnsiString NameCOM="COM"+IntToStr(NumCom1);
 HANDLE     Ret;
 if ((NumCom<=0)||(NumCom>CountMaxPorts)) return NULL;
 if (ComPort==NULL)
  {

   Ret=(unsigned int*)CreateFile(NameCOM.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL );
   if (Ret == INVALID_HANDLE_VALUE)
    {
     dwError[NumCom-1] = GetLastError();
     return Ret;
    }
   fSuccess[NumCom-1] = GetCommState(Ret, &dcb[NumCom-1]);
   if (!fSuccess)
    {
     CloseHandle(Ret);
     Ret=NULL;
     return Ret;
    }
   if (dcb[NumCom-1].BaudRate != BaundRate[NumCom-1]) sav[NumCom-1]=1;
   dcb[NumCom-1].BaudRate = BaundRate[NumCom-1];
   if (dcb[NumCom-1].ByteSize != ByteSize[NumCom-1] ) sav[NumCom-1]=1;
   dcb[NumCom-1].ByteSize = ByteSize[NumCom-1] ;
   if (dcb[NumCom-1].Parity != Parity[NumCom-1])      sav[NumCom-1]=1;
   switch (Parity[NumCom-1])
    {
     case 0 : dcb[NumCom-1].Parity=EVENPARITY	;break;
     case 1 : dcb[NumCom-1].Parity=MARKPARITY	;break;
     case 2 : dcb[NumCom-1].Parity=NOPARITY	;break;
     case 3 : dcb[NumCom-1].Parity=ODDPARITY	;break;
     default: dcb[NumCom-1].Parity=Parity[NumCom-1];break;
    }
   if (dcb[NumCom-1].StopBits!=StopBits[NumCom-1]) sav[NumCom-1]=1;
   switch (StopBits[NumCom-1])
    {
     case 0 : dcb[NumCom-1].StopBits=ONESTOPBIT  ;break;
     case 1 : dcb[NumCom-1].StopBits=ONE5STOPBITS;break;
     case 2 : dcb[NumCom-1].StopBits=TWOSTOPBITS ;break;
     default: dcb[NumCom-1].StopBits=StopBits[NumCom-1];break;
    }
   if (sav[NumCom-1]==1)
    {
     fSuccess[NumCom-1] = SetCommState(Ret, &dcb[NumCom-1]);
     fSuccess[NumCom-1] = GetCommState(Ret, &dcb[NumCom-1]);
    }
   if (!fSuccess[NumCom-1]) { CloseHandle(Ret);Ret=NULL; return Ret; }
   GetCommTimeouts(Ret,&TimeOutInfo[NumCom-1]);
   TimeOutInfo[NumCom-1].ReadIntervalTimeout        =RInterval[NumCom-1] ;
   TimeOutInfo[NumCom-1].ReadTotalTimeoutConstant   =RCInterval[NumCom-1];
   TimeOutInfo[NumCom-1].ReadTotalTimeoutMultiplier =RMInterval[NumCom-1];
   TimeOutInfo[NumCom-1].WriteTotalTimeoutConstant  =WCInterval[NumCom-1];
   TimeOutInfo[NumCom-1].WriteTotalTimeoutMultiplier=WMInterval[NumCom-1];
   SetCommTimeouts(Ret,&TimeOutInfo[NumCom-1]);
  }
 else    // Com1!=NULL
  {
   CloseHandle(ComPort);
   Ret=NULL;
  }
 return Ret;
} */
//---------------------------------------------------------------------------
/*bool TFOpros::Read_Modbus(int AdrUstr, int NumParamCRP, int *Error, unsigned short int *res, unsigned short int *stat)
{
 // чтение данных по Modbus протоколу
 unsigned char ansver[255]; // ответ по Modbus
 unsigned int  len_ansv=0 ; // длина ответа
 union
  {
   unsigned char c[2];
   short int     val ;
  } tmpint;
 union
  {
   unsigned long val;
   float sf;
   unsigned char byte[4];
  } ddata1,ddata2;
 union
  {
   unsigned char c[4];
   unsigned long val ;
   float         valf;
  } tmplong;
 if (Port_Modbus!=NULL)
  {
   if ((len_ansv=ReadDataCom(Port_Modbus,ansver,255))>0) // пришёл ответ
    {
     if (len_ansv==45) // это ответ по modbus протоколу 10 параметров 20 байт
      {
       if (ansver[0]==AdrUstr) // вернулись данные параметра 2 -байта
        {
         for (int pc=0;pc<10;pc++)
          {
           tmpint.c[1] = ansver[3+pc*2];
           tmpint.c[0] = ansver[4+pc*2];
           res[pc+NumParamCRP*10]     = tmpint.val    ;
           if (((pc+NumParamCRP*10)==0)||
               ((pc+NumParamCRP*10)==25)||
               ((pc+NumParamCRP*10)==26)||
               ((pc+NumParamCRP*10)==27)||
               ((pc+NumParamCRP*10)==28))
                                        stat[pc+NumParamCRP*10]    = tmpint.val    ;
           else                         stat[pc+NumParamCRP*10]    = 0             ;
          }
         *Error=0;
         return true;
        }
       else { *Error=4;return true; }
      }
     else { *Error=3; return true; } // по порту пришёл мусор
    }
   else { *Error=2; return false; }
  }
 else { *Error=1; return false;}
} */
//---------------------------------------------------------------------------
unsigned int TFOpros::GetLastRecordArhivSob(void)
{
 int ret=1;
 if (!QArhivSob->Active) QArhivSob->Open();
 else                    QArhivSob->Requery(TExecuteOptions());
 if (!QArhivSob->Eof) ret=QArhivSobIDSob->AsInteger+1;
 return ret;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::FSetRegFl_DE1(int Index, float Value)
{
 DataFlUstr[Index+1000-1]=Value;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::FSetRegFl_DE2(int Index, float Value)
{
 DataFlUstr[Index+1300-1]=Value;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::FSetRegFl(int Index, float Value)
{
 DataFlUstr[IndexFloat[Index]]=Value;
}
//---------------------------------------------------------------------------
float  __fastcall TFOpros::FGetBits(int Index, int Bit)
{
 int tmp;
 tmp = RegFl[Index];
 switch (Bit)
  {
   case  0: if ((tmp&    1)==    1) return 1; else return 0;
   case  1: if ((tmp&    2)==    2) return 1; else return 0;
   case  2: if ((tmp&    4)==    4) return 1; else return 0;
   case  3: if ((tmp&    8)==    8) return 1; else return 0;
   case  4: if ((tmp&   16)==   16) return 1; else return 0;
   case  5: if ((tmp&   32)==   32) return 1; else return 0;
   case  6: if ((tmp&   64)==   64) return 1; else return 0;
   case  7: if ((tmp&  128)==  128) return 1; else return 0;
   case  8: if ((tmp&  256)==  256) return 1; else return 0;
   case  9: if ((tmp&  512)==  512) return 1; else return 0;
   case 10: if ((tmp& 1024)== 1024) return 1; else return 0;
   case 11: if ((tmp& 2048)== 2048) return 1; else return 0;
   case 12: if ((tmp& 4096)== 4096) return 1; else return 0;
   case 13: if ((tmp& 8192)== 8192) return 1; else return 0;
   case 14: if ((tmp&16384)==16384) return 1; else return 0;
   case 15: if ((tmp&32768)==32768) return 1; else return 0;
  }
 return 0;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetRegFlEx(int Index)
{
 union
  {
   unsigned int i;
   float        f;
  } tmp;
 tmp.f = RegFl[Index];
 return tmp.i;
}
//---------------------------------------------------------------------------
float __fastcall TFOpros::FGetRegFl_DE1(int Index)
{
 return DataFlUstr[Index];
}
//---------------------------------------------------------------------------
float __fastcall TFOpros::FGetRegFl_DE2(int Index)
{
 return DataFlUstr[Index];
}
//---------------------------------------------------------------------------
float __fastcall TFOpros::FGetRegFl(int Index)
{
 if ((Index%2)==0)
  {
   return DataFlUstr[IndexFloat[Index]];
  }
 else
  {
   return DataFlUstr[IndexFloat[Index+1]];
/*   union
    {
     float f[3];
     struct
      {
       short int i1;
       float     f1;
       float     f2;
       short int i2;
      } s;
    } tmp;
   switch (Index%10)
    {
     case 1:  tmp.f[0]= DataFlUstr[IndexFloat[Index]];
              tmp.f[1]= DataFlUstr[IndexFloat[Index]+1];
              tmp.f[2]= DataFlUstr[IndexFloat[Index]+2];
              return tmp.s.f1;
     case 3:  tmp.f[0]= DataFlUstr[IndexFloat[Index]-1];
              tmp.f[1]= DataFlUstr[IndexFloat[Index]  ];
              tmp.f[2]= DataFlUstr[IndexFloat[Index]+1];
              return tmp.s.f2;
     default: return 0;
    } */
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::FSetReg(int index, int Value)
{
 int NumRing=index/8;
 int Numbits=index%8;
 switch (Numbits)
  {
   case 0:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]|  1; else if ((DataBitUstr[NumRing]&  1)==  1) DataBitUstr[NumRing]= DataBitUstr[NumRing] -    1;break;
   case 1:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]|  2; else if ((DataBitUstr[NumRing]&  2)==  2) DataBitUstr[NumRing]= DataBitUstr[NumRing] -    2;break;
   case 2:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]|  4; else if ((DataBitUstr[NumRing]&  4)==  4) DataBitUstr[NumRing]= DataBitUstr[NumRing] -    4;break;
   case 3:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]|  8; else if ((DataBitUstr[NumRing]&  8)==  8) DataBitUstr[NumRing]= DataBitUstr[NumRing] -    8;break;
   case 4:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]| 16; else if ((DataBitUstr[NumRing]& 16)== 16) DataBitUstr[NumRing]= DataBitUstr[NumRing] -   16;break;
   case 5:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]| 32; else if ((DataBitUstr[NumRing]& 32)== 32) DataBitUstr[NumRing]= DataBitUstr[NumRing] -   32;break;
   case 6:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]| 64; else if ((DataBitUstr[NumRing]& 64)== 64) DataBitUstr[NumRing]= DataBitUstr[NumRing] -   64;break;
   case 7:  if (Value==1) DataBitUstr[NumRing]=DataBitUstr[NumRing]|128; else if ((DataBitUstr[NumRing]&128)==128) DataBitUstr[NumRing]= DataBitUstr[NumRing] -  128;break;
  }
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetReg(int index)
{
 int NumRing=index/8;
 int Numbits=index%8;
 int ret=0;
 switch (Numbits)
  {
   case 0: if ((DataBitUstr[NumRing]&  1)==  1) ret=1; break;
   case 1: if ((DataBitUstr[NumRing]&  2)==  2) ret=1; break;
   case 2: if ((DataBitUstr[NumRing]&  4)==  4) ret=1; break;
   case 3: if ((DataBitUstr[NumRing]&  8)==  8) ret=1; break;
   case 4: if ((DataBitUstr[NumRing]& 16)== 16) ret=1; break;
   case 5: if ((DataBitUstr[NumRing]& 32)== 32) ret=1; break;
   case 6: if ((DataBitUstr[NumRing]& 64)== 64) ret=1; break;
   case 7: if ((DataBitUstr[NumRing]&128)==128) ret=1; break;
  }
 return ret;
}
//---------------------------------------------------------------------------
void TFOpros::WriteData(void)
{
 // Запись текущих данных в архив
 unsigned int CodeError;
 for (int i=0;i<Lic/*CountActiveTags*/;i++)
  {
   int   IDTag = i+1;
   float Val=0;
   float Val1=0,Val2=0;
   int   Status1=1, Status2=1;
   bool  sh=false;
   int Status=1;
   TTime      sm      ;
   TDateTime  td=Now();
   TDateTime  fd,ld   ;
   int        tz = StrToInt(td.FormatString("hh"));
   td.Val = (int)td.Val;
   fd = td; ld = td;
   if (QListTags->Locate("IDTag",IDTag,TLocateOptions()))
    {
     switch (IDTag)
      {
       case 1 : // положение заслонки газа
                Val = (float)DataUstr[2]/10;  Status=StatusUstr[2]; break;
       case 2 : // положение заслонки воздуха
                Val = (float)DataUstr[4]/10; Status=StatusUstr[4]; break;
       case 3 : // давление пара
                Val = (float)DataUstr[12]/10; Status=StatusUstr[12]; break;
       case 4 : // задание давления пара
                Val = (float)DataUstr[11]/10; Status=StatusUstr[11]; break;
       case 5 : // наличие пламени
                Val = (float)DataUstr[13]/10; Status=StatusUstr[13]; break;
       case 6 : // контроллер включен
                Val = (DataUstr[35]&1)==1; Status=StatusUstr[35]; break;
       case 7 : // вентилятор включен
                Val = (DataUstr[35]&2)==1; Status=StatusUstr[35]; break;
       case 8 : // вид топлива мазут
                Val = (DataUstr[35]&4)==4; Status=StatusUstr[35]; break;
       case 9 : // вид топлива газ
                Val = (DataUstr[35]&8)==8; Status=StatusUstr[35]; break;
       case 10: // резерв
                Val = (DataUstr[35]&16)==16; Status=StatusUstr[35]; break;
       case 11: // давление топлива высоко
                Val = (DataUstr[35]&32)==32; Status=StatusUstr[35]; break;
       case 12: // давление топлива низко
                Val = (DataUstr[35]&64)==64; Status=StatusUstr[35]; break;
       case 13: // давление герметичности
                Val = (DataUstr[35]&128)==128; Status=StatusUstr[35]; break;
       case 14: // контур безопасности
                Val = (DataUstr[35]&256)==256; Status=StatusUstr[35]; break;
       case 15: // резерв
                Val = (DataUstr[35]&512)==512; Status=StatusUstr[35]; break;
       case 16: // давление газа низко
                Val = (DataUstr[35]&1024)==1024; Status=StatusUstr[35]; break;
       case 17: // давление газа высоко
                Val = (DataUstr[35]&2048)==2048; Status=StatusUstr[35]; break;
       case 18: // резерв
                Val = (DataUstr[35]&4096)==4096; Status=StatusUstr[35]; break;
       case 19: // LP
                Val = (DataUstr[35]&8192)==8192; Status=StatusUstr[35]; break;
       case 20: // Запуск топлива
                Val = (DataUstr[35]&16384)==16384; Status=StatusUstr[35]; break;
       case 21: // Мгновенный запуск топлива
                Val = (DataUstr[35]&32768)==32768; Status=StatusUstr[35]; break;
       case 22: // Сигнал тревоги
                Val = (DataUstr[37]&1)==1; Status=StatusUstr[37]; break;
       case 23: // резерв
                Val = (DataUstr[37]&2)==2; Status=StatusUstr[37]; break;
       case 24: // резерв
                Val = (DataUstr[37]&4)==4; Status=StatusUstr[37]; break;
       case 25: // резерв
                Val = (DataUstr[37]&8)==8; Status=StatusUstr[37]; break;
       case 26: // розжиг
                Val = (DataUstr[37]&16)==16; Status=StatusUstr[37]; break;
       case 27: // открыть клапан DW
                Val = (DataUstr[37]&32)==32; Status=StatusUstr[37]; break;
       case 28: // включить вентилятор
                Val = (DataUstr[37]&64)==64; Status=StatusUstr[37]; break;
       case 29: // включить топливный насос
                Val = (DataUstr[37]&128)==128; Status=StatusUstr[37]; break;
       case 30: // мазутный клапан SV
                Val = (DataUstr[37]&256)==256; Status=StatusUstr[37]; break;
       case 31: // мазутный клапан V1
                Val = (DataUstr[37]&512)==512; Status=StatusUstr[37]; break;
       case 32: // мазутный клапан V2
                Val = (DataUstr[37]&1024)==1024; Status=StatusUstr[37]; break;
       case 33: // мазутный клапан V3
                Val = (DataUstr[37]&2048)==2048; Status=StatusUstr[37]; break;
       case 34: // газовый клапан SV
                Val = (DataUstr[37]&4096)==4096; Status=StatusUstr[37]; break;
       case 35: // газовый клапан V1
                Val = (DataUstr[37]&8192)==8192; Status=StatusUstr[37]; break;
       case 36: // газовый клапан V2
                Val = (DataUstr[37]&16384)==16384; Status=StatusUstr[37]; break;
       case 37: // газовый клапан V3
                Val = (DataUstr[37]&32768)==32768; Status=StatusUstr[37]; break;
       case 38: // код ошибки
                Val = DataUstr[25]; Status=StatusUstr[25]; break;
       case 39: // диагностический код ошибки
                Val = DataUstr[26]; Status=StatusUstr[26]; break;
       case 40: // класс ошибки
                Val = DataUstr[27]; Status=StatusUstr[27]; break;
       case 41: // этап возникновения ошибки
                Val = DataUstr[28]; Status=StatusUstr[28]; break;
       case 42: // этап
                Val = DataUstr[0]; Status=StatusUstr[0]; break;
       case 43: // уставка №1
                Val = DataUstr[44]; Status=StatusUstr[44]; break;
       case 44:  // уставка №3
                Val = DataUstr[48]; Status=StatusUstr[48]; break;
       case 45: // наличие пламени
                if (((float)DataUstr[13]/10)<35.0) Val=0; else Val=1;
                Status=StatusUstr[13]; break;
       case 46: Val = DataUstr[43]; Status=StatusUstr[43]; break;
       case 47: if (Link_Kotel3)  Val = 1; else Val=0;
                Status=0;
                break;
       case 101: // Давление в питательной линии №1
                 Val  = RegFl[900]; if (Link_OBSK) Status=0;  else Status=1;
                 Val1 = RegFl[SH4ma_PT201] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT201];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 102: // Давление в питательной линии №2
                 Val  = RegFl[902]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT202] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT202];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 103: // Давление прямой воды в системе отопления
                 Val =  RegFl[904]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT203] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT203];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 104: // Давление обратной воды в системе отопления
                 Val =  RegFl[906]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT204] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT204];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 105: // Давление подачи ГВС
                 Val  = RegFl[908]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT205] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT205];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 106: // Уровень в баке аккумуляторе №1
                 Val  = RegFl[910]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI401] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI401];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 107: // Уровень в баке аккумуляторе №2
                 Val  = RegFl[912]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI402] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI402];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 108: // Резерв #1
                 Val = RegFl[914]; if (Link_OBSK) Status=0; else Status=1;
                 break;
       case 109: // Уровень в сетевом деаэраторе
                 Val  = RegFl[916]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI403] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI403];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 110: // Давление в сетевом деаэраторе
                 Val  = RegFl[918]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT206] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT206];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 111: // Уровень в питательном деаэраторе
                 Val  = RegFl[920]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI404] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI404];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 112: // Давление в питательном деаэраторе
                 Val  = RegFl[922]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT207] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT207];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 113: // Резерв #2
                 Val = RegFl[924]; if (Link_OBSK) Status=0; else Status=1; break;
       case 114: // Резерв #3
                 Val = RegFl[926]; if (Link_OBSK) Status=0; else Status=1; break;
       case 115: // Резерв #4
                 Val = RegFl[928]; if (Link_OBSK) Status=0; else Status=1; break;
       case 116: // Резерв #5
                 Val = RegFl[930]; if (Link_OBSK) Status=0; else Status=1; break;
       case 117: // Давление пара в сепараторе
                 Val  = RegFl[932]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT210] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT210];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 118: // Давление пара на гребёнке
                 Val  = RegFl[934]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT211] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT211];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 119: // Давление пара на выходе РУ №1
                 Val  = RegFl[936]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT212] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT212];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 120: // Давление пара на выходе РУ №2
                 Val  = RegFl[938]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT213] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT213];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 121: // Резерв #6
                 Val = RegFl[940]; if (Link_OBSK) Status=0; else Status=1; break;
       case 122: // Резерв #7
                 Val = RegFl[942]; if (Link_OBSK) Status=0; else Status=1; break;
       case 123: // Резерв #8
                 Val = RegFl[944]; if (Link_OBSK) Status=0; else Status=1; break;
       case 124: // Резерв #9
                 Val = RegFl[946]; if (Link_OBSK) Status=0; else Status=1; break;
       case 133: // Температура обратной воды №1
                 Val = RegFl[948]; if (Link_OBSK) Status=0; else Status=1; break;
       case 134: // Температура обратной воды №2
                 Val = RegFl[950]; if (Link_OBSK) Status=0; else Status=1; break;
       case 135: // Температура обратной воды №3
                 Val = RegFl[952]; if (Link_OBSK) Status=0; else Status=1; break;
       case 136: // Температура прямой воды
                 Val = RegFl[954]; if (Link_OBSK) Status=0; else Status=1; break;
       case 137: // Температура воды после сетевого деаэратора
                 Val = RegFl[956]; if (Link_OBSK) Status=0; else Status=1; break;
       case 138: // Температура воды после питательного деаэратора
                 Val = RegFl[958]; if (Link_OBSK) Status=0; else Status=1; break;
       case 139: // Температура подачи ГВС
                 Val = RegFl[960]; if (Link_OBSK) Status=0; else Status=1; break;
       case 140: // Температура воздуха на улице
                 Val = RegFl[962]; if (Link_OBSK) Status=0; else Status=1; break;
       case 201: // Питательный насос №1 включён
                 Val = RegBits[800][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 202: // Питательный насос №2 включён
                 Val = RegBits[800][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 203: // Питательный насос №3 включён
                 Val = RegBits[800][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 204: // Подпиточный насос теплосети №1 включён
                 Val = RegBits[800][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 205: // Подпиточный насос теплосети №2 включён
                 Val = RegBits[800][10];if (Link_OBSK) Status=0; else Status=1; break;
       case 206: // Сетевой насос №1 включён
                 Val = RegBits[800][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 207: // Сетевой насос №2 включён
                 Val = RegBits[800][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 208: // Сетевой насос №3 включён
                 Val = RegBits[800][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 209: // Насос ГВС №1 включён
                 Val = RegBits[800][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 210: // Резерв 13
                 Val = RegBits[804][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 211: // Насос ГВС №2 включён
                 Val = RegBits[804][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 212: // Насос ГВС №2 авария
                 Val = RegBits[804][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 213: // Насос ГВС №3 включён
                 Val = RegBits[804][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 214: // Насос ГВС №3 авария
                 Val = RegBits[804][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 215: // Насос ГВС №4 включён
                 Val = RegBits[804][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 216: // Насос ГВС №4 авария
                 Val = RegBits[804][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 217: // Насос конденсатный Н-10 включен
                 Val = RegBits[800][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 218: // Повысительный насос №1 включён
                 Val = RegBits[800][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 219: // Повысительный насос №2 включён
                 Val = RegBits[800][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 220: // Повысительный насос №3 включён
                 Val = RegBits[800][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 221: // Дренажный насос Н-11 включен
                 Val = RegBits[800][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 222: // Подмешивающий насос включен
                 Val = RegBits[800][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 223: // Резерв 1
                 Val = RegBits[800][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 224: // Кнопка открыть задвижку Z-3
                 Val = RegBits[802][0];  if (Link_OBSK) Status=0; else Status=1; break;
       case 225: // Кнопка закрыть задвижку Z-3
                 Val = RegBits[802][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 226: // Кнопка стоп задвижки Z-3
                 Val = RegBits[802][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 227: // Резерв 2
                 Val = RegBits[802][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 228: // Резерв 3
                 Val = RegBits[802][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 229: // Резерв 4
                 Val = RegBits[802][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 230: // Резерв 5
                 Val = RegBits[802][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 231: // Резерв 6
                 Val = RegBits[802][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 232: // Резерв 7
                 Val = RegBits[802][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 233: // Уровень в дренажном приямке нижний
                 Val = RegBits[802][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 234: // Уровень в дренажном приямке средний
                 Val = RegBits[802][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 235: // Уровень в дренажном приямке верхний
                 Val = RegBits[802][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 236: // Резерв 8
                 Val = RegBits[802][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 237: // Уровень в конденсатном баке нижний
                 Val = RegBits[802][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 238: // Уровень в конденсатном баке средний
                 Val = RegBits[802][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 239: // Уровень в конденсатном баке верхний
                 Val = RegBits[802][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 240: // Резерв 14
                 Val = RegBits[804][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 241: // Уровень в соляной ёмкости №1 верхний
                 Val = RegBits[804][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 242: // Уровень в соляной ёмкости №2 верхний
                 Val = RegBits[804][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 243: // Давление на вводе в котельную минимально (скважина)
                 Val = RegBits[804][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 244: // Давление на вводе в котельную минимально (город)
                 Val = RegBits[804][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 245: // Резерв 9
                 Val = RegBits[804][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 246: // Резерв 10
                 Val = RegBits[804][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 247: // Резерв 11
                 Val = RegBits[804][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 248: // Резерв 12
                 Val = RegBits[804][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 249: // Клапан подпиточной воды открыт
                 Val = RegBits[806][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 250: // Клапан подпиточной воды закрыт
                 Val = RegBits[806][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 251: // Клапан воды в сетевой деаэратор открыт
                 Val = RegBits[806][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 252: // Клапан воды в сетевой деаэратор закрыт
                 Val = RegBits[806][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 253: // Клапан воды в питательный деаэратор открыт
                 Val = RegBits[806][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 254: // Клапан воды в питательный деаэратор закрыт
                 Val = RegBits[806][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 255: // Клапан пара в сетевой деаэратор открыт
                 Val = RegBits[806][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 256: // Клапан пара в сетевой деаэратор закрыт
                 Val = RegBits[806][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 257: // Клапан пара в питательный деаэратор открыт
                 Val = RegBits[806][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 258: // Клапан пара в питательный деаэратор закрыт
                 Val = RegBits[806][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 259: // Клапан пара в РУ 6/10  открыт
                 Val = RegBits[806][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 260: // Клапан пара в РУ 6/10 закрыт
                 Val = RegBits[806][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 261: // Клапан пара в РУ 6/20  открыт
                 Val = RegBits[806][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 262: // Клапан пара в РУ 6/20 закрыт
                 Val = RegBits[806][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 263: // Задвижка №3 открыта
                 Val = RegBits[806][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 264: // Задвижка №3 закрыта
                 Val = RegBits[806][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 265: // Задвижка LV-721 открывается
                 Val = Reg[300]; if (Link_OBSK) Status=0; else Status=1; break;
       case 266: // Задвижка LV-721 закрывается
                 Val = Reg[301]; if (Link_OBSK) Status=0; else Status=1; break;
       case 267: // Клапан LV-731 открывается
                 Val = Reg[302]; if (Link_OBSK) Status=0; else Status=1; break;
       case 268: // Клапан LV-731 закрывается
                 Val = Reg[303]; if (Link_OBSK) Status=0; else Status=1; break;
       case 269: // Клапан PV-711 открывается
                 Val = Reg[304]; if (Link_OBSK) Status=0; else Status=1; break;
       case 270: // Клапан PV-711 закрывается
                 Val = Reg[305]; if (Link_OBSK) Status=0; else Status=1; break;
       case 271: // Клапан PV-741 открывается
                 Val = Reg[306]; if (Link_OBSK) Status=0; else Status=1; break;
       case 272: // Клапан PV-741 закрывается
                 Val = Reg[307]; if (Link_OBSK) Status=0; else Status=1; break;
       case 273: // Клапан PV-751 открывается
                 Val = Reg[308]; if (Link_OBSK) Status=0; else Status=1; break;
       case 274: // Клапан PV-751 закрывается
                 Val = Reg[309]; if (Link_OBSK) Status=0; else Status=1; break;
       case 275: // Клапан PV-761 открывается
                 Val = Reg[310]; if (Link_OBSK) Status=0; else Status=1; break;
       case 276: // Клапан PV-761 закрывается
                 Val = Reg[311]; if (Link_OBSK) Status=0; else Status=1; break;
       case 277: // Клапан PV-771 открывается
                 Val = Reg[312]; if (Link_OBSK) Status=0; else Status=1; break;
       case 278: // Клапан PV-771 закрывается
                 Val = Reg[313]; if (Link_OBSK) Status=0; else Status=1; break;
       case 301: // Команда Пуск питательного насоса №1 c ПК
                 Val = Reg[140]; if (Link_OBSK) Status=0; else Status=1; break;
       case 302: // Команда Стоп питательного насоса №1 с ПК
                 Val = Reg[141]; if (Link_OBSK) Status=0; else Status=1; break;
       case 303: // Команда Пуск питательного насоса №2 c ПК
                 Val = Reg[144]; if (Link_OBSK) Status=0; else Status=1; break;
       case 304: // Команда Стоп питательного насоса №2 с ПК
                 Val = Reg[145]; if (Link_OBSK) Status=0; else Status=1; break;
       case 305: // Команда Пуск питательного насоса №3 c ПК
                 Val = Reg[148]; if (Link_OBSK) Status=0; else Status=1; break;
       case 306: // Команда Стоп питательного насоса №3 с ПК
                 Val = Reg[149]; if (Link_OBSK) Status=0; else Status=1; break;
       case 307: // Команда Пуск подпиточного насоса №1 c ПК
                 Val = Reg[160]; if (Link_OBSK) Status=0; else Status=1; break;
       case 308: // Команда Стоп подпиточного насоса №1 с ПК
                 Val = Reg[161]; if (Link_OBSK) Status=0; else Status=1; break;
       case 309: // Команда Пуск подпиточного насоса №2 c ПК
                 Val = Reg[162]; if (Link_OBSK) Status=0; else Status=1; break;
       case 310: // Команда Стоп подпиточного насоса №2 с ПК
                 Val = Reg[163]; if (Link_OBSK) Status=0; else Status=1; break;
       case 311: // Команда Пуск сетевого насоса №1 c ПК
                 Val = Reg[164]; if (Link_OBSK) Status=0; else Status=1; break;
       case 312: // Команда Стоп сетевого насоса №1 с ПК
                 Val = Reg[165]; if (Link_OBSK) Status=0; else Status=1; break;
       case 313: // Команда Пуск сетевого насоса №2 c ПК
                 Val = Reg[168]; if (Link_OBSK) Status=0; else Status=1; break;
       case 314: // Команда Стоп сетевого насоса №2 с ПК
                 Val = Reg[169]; if (Link_OBSK) Status=0; else Status=1; break;
       case 315: // Команда Пуск сетевого насоса №3 c ПК
                 Val = Reg[172]; if (Link_OBSK) Status=0; else Status=1; break;
       case 316: // Команда Стоп сетевого насоса №3 с ПК
                 Val = Reg[173]; if (Link_OBSK) Status=0; else Status=1; break;
       case 317: // Команда Пуск конденсатного насоса №10 c ПК
                 Val = Reg[176]; if (Link_OBSK) Status=0; else Status=1; break;
       case 318: // Команда Стоп конденсатного насоса №10 с ПК
                 Val = Reg[177]; if (Link_OBSK) Status=0; else Status=1; break;
       case 319: // Команда Пуск повысительного насоса №1 c ПК
                 Val = Reg[190]; if (Link_OBSK) Status=0; else Status=1; break;
       case 320: // Команда Стоп повысительного насоса №1 с ПК
                 Val = Reg[191]; if (Link_OBSK) Status=0; else Status=1; break;
       case 321: // Команда Пуск повысительного насоса №2 c ПК
                 Val = Reg[192]; if (Link_OBSK) Status=0; else Status=1; break;
       case 322: // Команда Стоп повысительного насоса №2 с ПК
                 Val = Reg[193]; if (Link_OBSK) Status=0; else Status=1; break;
       case 323: // Команда Пуск повысительного насоса №3 c ПК
                 Val = Reg[194]; if (Link_OBSK) Status=0; else Status=1; break;
       case 324: // Команда Стоп повысительного насоса №3 с ПК
                 Val = Reg[195]; if (Link_OBSK) Status=0; else Status=1; break;
       case 325: // Команда Пуск дренажного насоса c ПК
                 Val = Reg[196]; if (Link_OBSK) Status=0; else Status=1; break;
       case 326: // Команда Стоп дренажного насоса с ПК
                 Val = Reg[197]; if (Link_OBSK) Status=0; else Status=1; break;
       case 327: // Команда "Пуск" насоса ГВС №1 с ПК
                 Val = Reg[199]; if (Link_OBSK) Status=0; else Status=1; break;
       case 328: // Команда "Стоп" насоса ГВС №1 с ПК
                 Val = Reg[200]; if (Link_OBSK) Status=0; else Status=1; break;
       case 329: // Команда "Пуск" насоса ГВС №2 с ПК
                 Val = Reg[201]; if (Link_OBSK) Status=0; else Status=1; break;
       case 330: // Команда "Стоп" насоса ГВС №2 с ПК
                 Val = Reg[202]; if (Link_OBSK) Status=0; else Status=1; break;
       case 331: // Команда "Пуск" насоса ГВС №3 с ПК
                 Val = Reg[205]; if (Link_OBSK) Status=0; else Status=1; break;
       case 332: // Команда "Стоп" насоса ГВС №3 с ПК
                 Val = Reg[206]; if (Link_OBSK) Status=0; else Status=1; break;
       case 333: // Команда "Пуск" насоса ГВС №4 с ПК
                 Val = Reg[209]; if (Link_OBSK) Status=0; else Status=1; break;
       case 334: // Команда "Стоп" насоса ГВС №4 с ПК
                 Val = Reg[210]; if (Link_OBSK) Status=0; else Status=1; break;
       case 335: // Питательный насос №1 в резерве
                 Val = Reg[143]; if (Link_OBSK) Status=0; else Status=1; break;
       case 336: // Питательный насос №2 в резерве
                 Val = Reg[147]; if (Link_OBSK) Status=0; else Status=1; break;
       case 337: // Питательный насос №3 в резерве
                 Val = Reg[151]; if (Link_OBSK) Status=0; else Status=1; break;
       case 338: // Сетевой насос №1 в резерве
                 Val = Reg[167]; if (Link_OBSK) Status=0; else Status=1; break;
       case 339: // Сетевой насос №2 в резерве
                 Val = Reg[171]; if (Link_OBSK) Status=0; else Status=1; break;
       case 340: // Сетевой насос №3 в резерве
                 Val = Reg[175]; if (Link_OBSK) Status=0; else Status=1; break;
       case 341: // Насос ГВС №2 в резерве
                 Val = Reg[204]; if (Link_OBSK) Status=0; else Status=1; break;
       case 342: // Насос ГВС №3 в резерве
                 Val = Reg[208]; if (Link_OBSK) Status=0; else Status=1; break;
       case 343: // Насос ГВС №4 в резерве
                 Val = Reg[212]; if (Link_OBSK) Status=0; else Status=1; break;
       case 344: // Автоматический режим конденсатного насоса
                 Val = Reg[178]; if (Link_OBSK) Status=0; else Status=1; break;
       case 345: // Автоматический режим дренажного насоса
                 Val = Reg[198]; if (Link_OBSK) Status=0; else Status=1; break;
       case 346: // Команда включения/отключения резерва для питательного насоса №1 с ПК
                 Val = Reg[142]; if (Link_OBSK) Status=0; else Status=1; break;
       case 347: // Команда включения/отключения резерва для питательного насоса №2 с ПК
                 Val = Reg[146]; if (Link_OBSK) Status=0; else Status=1; break;
       case 348: // Команда включения/отключения резерва для питательного насоса №3 с ПК
                 Val = Reg[150]; if (Link_OBSK) Status=0; else Status=1; break;
       case 349: // Команда включения/отключения резерва для сетевого насоса №1 с ПК
                 Val = Reg[166]; if (Link_OBSK) Status=0; else Status=1; break;
       case 350: // Команда включения/отключения резерва для сетевого насоса №2 с ПК
                 Val = Reg[170]; if (Link_OBSK) Status=0; else Status=1; break;
       case 351: // Команда включения/отключения резерва для сетевого насоса №3 с ПК
                 Val = Reg[174]; if (Link_OBSK) Status=0; else Status=1; break;
       case 352: // Команда включения/отключения резерва для насоса ГВС №2 с ПК
                 Val = Reg[203]; if (Link_OBSK) Status=0; else Status=1; break;
       case 353: // Команда включения/отключения резерва для насоса ГВС №3 с ПК
                 Val = Reg[207]; if (Link_OBSK) Status=0; else Status=1; break;
       case 354: // Команда включения/отключения резерва для насоса ГВС №4 с ПК
                 Val = Reg[211]; if (Link_OBSK) Status=0; else Status=1; break;
       case 355: // Команда открыть задвижку Z-3 с ПК
                 Val = Reg[38]; if (Link_OBSK) Status=0; else Status=1; break;
       case 356: // Команда закрыть задвижку Z-3 с ПК
                 Val = Reg[39]; if (Link_OBSK) Status=0; else Status=1; break;
       case 357: // Команда остановить задвижку Z-3 с ПК
                 Val = Reg[40]; if (Link_OBSK) Status=0; else Status=1; break;
       case 358: // Авария задвижки Z-3
                 Val = Reg[41]; if (Link_OBSK) Status=0; else Status=1; break;
       case 359: // Давление в питательной линии №1 вне рабочего диапазона
                 if ((RegBits[970][0]==1)||(RegBits[970][1]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][0]==1)||(RegBits[820][1]==1)) Status=1; else Status=0;
                 break;
       case 360: // Давление в питательной линии №2 вне рабочего диапазона
                 if ((RegBits[970][2]==1)||(RegBits[970][3]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][2]==1)||(RegBits[820][3]==1)) Status=1; else Status=0;
                 break;
       case 361: // Давление прямой воды в системе отопления вне рабочего диапазона
                 if ((RegBits[970][4]==1)||(RegBits[970][5]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][4]==1)||(RegBits[820][5]==1)) Status=1; else Status=0;
                 break;
       case 362: // Давление подачи ГВС вне рабочего диапазона
                 if (RegBits[970][6]==1) Val=1;
                 else Val=0;
                 if (RegBits[820][6]==1) Status=1; else Status=0;
                 break;
       case 363: // Давление пара в сепараторе вне рабочего диапазона
                 if (RegBits[970][7]==1) Val=1;
                 else Val=0;
                 if (RegBits[820][7]==1) Status=1; else Status=0;
                 break;
       case 364: // Давление пара на гребёнке вне рабочего диапазона
                 if ((RegBits[970][8]==1)||(RegBits[970][9]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][8]==1)||(RegBits[820][9]==1)) Status=1; else Status=0;
                 break;
       case 365: // Уровень в баке аккумулятора №1 вне рабочего диапазона
                 if ((RegBits[970][10]==1)||(RegBits[970][11]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][10]==1)||(RegBits[820][11]==1)) Status=1; else Status=0;
                 break;
       case 366: // Уровень в баке аккумулятора №2 вне рабочего диапазона
                 if ((RegBits[970][12]==1)||(RegBits[970][13]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][12]==1)||(RegBits[820][13]==1)) Status=1; else Status=0;
                 break;
       case 367: // Уровень в сетевом деаэраторе вне рабочего диапазона
                 if ((RegBits[970][14]==1)||(RegBits[970][15]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][14]==1)||(RegBits[820][15]==1)) Status=1; else Status=0;
                 break;
       case 368: // Уровень в питательном диаэраторе вне рабочего диапазона
                 if ((RegBits[972][0]==1)||(RegBits[972][1]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[822][0]==1)||(RegBits[822][1]==1)) Status=1; else Status=0;
                 break;
       case 369: // Верхний уровень в соленной ёмкости №1
                 if (RegBits[972][2]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][2]==1) Status=1; else Status=0;
                 break;
       case 370: // Верхний уровень в соленной ёмкости №2
                 if (RegBits[972][3]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][3]==1) Status=1; else Status=0;
                 break;
       case 371: // Минимальное давление на вводе в котельную (скважина)
                 if (RegBits[972][4]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][4]==1) Status=1; else Status=0;
                 break;
       case 372: // Минимальное давление на вводе в котельную (город)
                 if (RegBits[972][5]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][5]==1) Status=1; else Status=0;
                 break;
       case 373: // Неисправность оборудования
                 CodeError=0;
                 if (RegBits[812][ 8]==1) CodeError=CodeError|  1;
                 if (RegBits[812][ 9]==1) CodeError=CodeError|  2;
                 if (RegBits[812][10]==1) CodeError=CodeError|  4;
                 if (RegBits[812][11]==1) CodeError=CodeError|  8;
                 if (RegBits[812][12]==1) CodeError=CodeError| 16;
                 if (RegBits[812][13]==1) CodeError=CodeError| 32;
                 if (RegBits[812][14]==1) CodeError=CodeError| 64;
                 if (RegBits[812][15]==1) CodeError=CodeError|128;
                 Val=CodeError;CodeError=0;
                 if (RegBits[822][ 8]==1) CodeError=CodeError|  1;
                 if (RegBits[822][ 9]==1) CodeError=CodeError|  2;
                 if (RegBits[822][10]==1) CodeError=CodeError|  4;
                 if (RegBits[822][11]==1) CodeError=CodeError|  8;
                 if (RegBits[822][12]==1) CodeError=CodeError| 16;
                 if (RegBits[822][13]==1) CodeError=CodeError| 32;
                 if (RegBits[822][14]==1) CodeError=CodeError| 64;
                 if (RegBits[822][15]==1) CodeError=CodeError|128;
                 if (CodeError!=0) Status=CodeError; else Status=0;
                 break;
       case 374: // Обрыв каналов 1-ой группы
                 CodeError=0;
                 if (RegBits[810][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[810][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[810][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[810][ 3]==1) CodeError=CodeError|   8;
                 if (RegBits[810][ 4]==1) CodeError=CodeError|  16;
                 if (RegBits[810][ 5]==1) CodeError=CodeError|  32;
                 if (RegBits[810][ 6]==1) CodeError=CodeError|  64;
//                 if (RegBits[810][ 7]==1) CodeError=CodeError| 128;
                 if (RegBits[810][ 8]==1) CodeError=CodeError| 256;
                 if (RegBits[810][ 9]==1) CodeError=CodeError| 512;
                 if (RegBits[810][10]==1) CodeError=CodeError|1024;
                 if (RegBits[810][11]==1) CodeError=CodeError|2048;
                 Val=CodeError;CodeError=0;
                 if (RegBits[824][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[824][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[824][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[824][ 3]==1) CodeError=CodeError|   8;
                 if (RegBits[824][ 4]==1) CodeError=CodeError|  16;
                 if (RegBits[824][ 5]==1) CodeError=CodeError|  32;
                 if (RegBits[824][ 6]==1) CodeError=CodeError|  64;
//                 if (RegBits[824][ 7]==1) CodeError=CodeError| 128;
                 if (RegBits[824][ 8]==1) CodeError=CodeError| 256;
                 if (RegBits[824][ 9]==1) CodeError=CodeError| 512;
                 if (RegBits[824][10]==1) CodeError=CodeError|1024;
                 if (RegBits[824][11]==1) CodeError=CodeError|2048;
                 if (CodeError!=0) Status=CodeError; else Status=0;
                 break;
       case 375: // Обрыв каналов 2-ой группы
                 CodeError=0;
                 if (RegBits[812][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[812][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[812][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[812][ 3]==1) CodeError=CodeError|   8;
                 Val=CodeError;CodeError=0;
                 if (RegBits[826][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[826][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[826][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[826][ 3]==1) CodeError=CodeError|   8;
                 if (CodeError!=0) Status=CodeError; else Status=0;
                 break;
       case 376: // Обрыв каналов 3-ей группы
                 CodeError=0;
                 if (RegBits[814][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[814][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[814][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[814][ 3]==1) CodeError=CodeError|   8;
                 if (RegBits[814][ 4]==1) CodeError=CodeError|  16;
                 if (RegBits[814][ 5]==1) CodeError=CodeError|  32;
                 if (RegBits[814][ 6]==1) CodeError=CodeError|  64;
                 if (RegBits[814][ 7]==1) CodeError=CodeError| 128;
                 Val=CodeError;CodeError=0;
                 if (RegBits[828][ 0]==1) CodeError=CodeError|   1;
                 if (RegBits[828][ 1]==1) CodeError=CodeError|   2;
                 if (RegBits[828][ 2]==1) CodeError=CodeError|   4;
                 if (RegBits[828][ 3]==1) CodeError=CodeError|   8;
                 if (RegBits[828][ 4]==1) CodeError=CodeError|  16;
                 if (RegBits[828][ 5]==1) CodeError=CodeError|  32;
                 if (RegBits[828][ 6]==1) CodeError=CodeError|  64;
                 if (RegBits[828][ 7]==1) CodeError=CodeError| 128;
                 if (CodeError!=0) Status=CodeError; else Status=0;
                 break;
       case 377: // Команда "Пуск" подмешивающего насоса с ПК
                 Val = Reg[213]; if (Link_OBSK) Status=0; else Status=1; break;
       case 378: // Команда "Стоп" подмешивающего насоса с ПК
                 Val = Reg[214]; if (Link_OBSK) Status=0; else Status=1; break;
       case 501: // Регулятор №1. Режим регулятора.  Давление обратной воды в системе отопления
                 Val = Reg[18]; if (Link_OBSK) Status=0; else Status=1; break;
       case 502: // Регулятор №1. Задание.  Давление обратной воды в системе отопления
                 Val = RegFl[508]; if (Link_OBSK) Status=0; else Status=1; break;
       case 503: // Регулятор №1. Коэффициент пропорциональности. Давление обратной воды в системе отопления
                 Val = RegFl[290]; if (Link_OBSK) Status=0; else Status=1; break;
       case 504: // Регулятор №1. Время интегрирования. Давление обратной воды в системе отопления
                 Val = RegFlEx[292]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 505: // Регулятор №1. Зона нечувствительности. Давление обратной воды в системе отопления
                 Val = RegFl[294]; if (Link_OBSK) Status=0; else Status=1; break;
       case 506: // Регулятор №1. Время хода. Давление обратной воды в системе отопления
                 Val = RegFlEx[561]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 507: // Регулятор №1. Минимальный импульс. Давление обратной воды в системе отопления
                 Val = RegFlEx[563]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 508: // Регулятор №1. Выход. Давление обратной воды в системе отопления
                 Val = RegFl[510]; if (Link_OBSK) Status=0; else Status=1; break;
       case 509: // Клапан PV-711. Команда "открыть" с ПК
                 Val = Reg[19]; if (Link_OBSK) Status=0; else Status=1; break;
       case 510: // Клапан PV-711. Команда "закрыть" с ПК
                 Val = Reg[20]; if (Link_OBSK) Status=0; else Status=1; break;
       case 511: // Клапан PV-711. Команда "стоп" с ПК
                 Val = Reg[21]; if (Link_OBSK) Status=0; else Status=1; break;

       case 521: // Регулятор №2. Режим регулятора. Давление в сетевом деаэраторе
                 Val = Reg[22]; if (Link_OBSK) Status=0; else Status=1; break;
       case 522: // Регулятор №2. Задание. Давление в сетевом деаэраторе
                 Val = RegFl[512]; if (Link_OBSK) Status=0; else Status=1; break;
       case 523: // Регулятор №2. Коэффициент пропорциональности.  Давление в сетевом деаэраторе
                 Val = RegFl[330]; if (Link_OBSK) Status=0; else Status=1; break;
       case 524: // Регулятор №2. Время интегрирования. Давление в сетевом деаэраторе
                 Val = RegFlEx[332]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 525: // Регулятор №2. Зона нечувствительности. Давление в сетевом деаэраторе
                 Val = RegFl[334]; if (Link_OBSK) Status=0; else Status=1; break;
       case 526: // Регулятор №2. Время хода. Давление в сетевом деаэраторе
                 Val = RegFlEx[571]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 527: // Регулятор №2. Минимальный импульс. Давление в сетевом деаэраторе
                 Val = RegFlEx[573]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 528: // Регулятор №2. Выход. Давление в сетевом деаэраторе
                 Val = RegFl[514]; if (Link_OBSK) Status=0; else Status=1; break;
       case 529: // Клапан PV-741. Команда "открыть" с ПК
                 Val = Reg[23]; if (Link_OBSK) Status=0; else Status=1; break;
       case 530: // Клапан PV-741. Команда "закрыть" с ПК
                 Val = Reg[24]; if (Link_OBSK) Status=0; else Status=1; break;
       case 531: // Клапан PV-741. Команда "стоп" с ПК
                 Val = Reg[25]; if (Link_OBSK) Status=0; else Status=1; break;

       case 541: // Регулятор №3. Режим регулятора. Давление в питательном деаэраторе.
                 Val = Reg[26]; if (Link_OBSK) Status=0; else Status=1; break;
       case 542: // Регулятор №3. Задание. Давление в питательном деаэраторе
                 Val = RegFl[516]; if (Link_OBSK) Status=0; else Status=1; break;
       case 543: // Регулятор №3. Коэффициент пропорциональности. Давление в питательном деаэраторе
                 Val = RegFl[370]; if (Link_OBSK) Status=0; else Status=1; break;
       case 544: // Регулятор №3. Время интегрирования. Давление в питательном деаэраторе
                 Val = RegFlEx[372]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 545: // Регулятор №3. Зона нечувствительности. Давление в питательном деаэраторе
                 Val = RegFl[374]; if (Link_OBSK) Status=0; else Status=1; break;
       case 546: // Регулятор №3. Время хода. Давление в питательном деаэраторе
                 Val = RegFlEx[581]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 547: // Регулятор №3. Минимальный импульс. Давление в питательном деаэраторе
                 Val = RegFlEx[583]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 548: // Регулятор №3. Выход. Давление в питательном деаэраторе
                 Val = RegFl[518]; if (Link_OBSK) Status=0; else Status=1; break;
       case 549: // Клапан PV-751. Команда "открыть" с ПК
                 Val = Reg[27]; if (Link_OBSK) Status=0; else Status=1; break;
       case 550: // Клапан PV-751. Команда "закрыть" с ПК
                 Val = Reg[28]; if (Link_OBSK) Status=0; else Status=1; break;
       case 551: // Клапан PV-751. Команда "стоп" с ПК
                 Val = Reg[29]; if (Link_OBSK) Status=0; else Status=1; break;

       case 561: // Регулятор №4. Режим регулятора. Давление пара на выходе РУ №1.
                 Val = Reg[30]; if (Link_OBSK) Status=0; else Status=1; break;
       case 562: // Регулятор №4. Задание. Давление пара на выходе РУ №1.
                 Val = RegFl[520]; if (Link_OBSK) Status=0; else Status=1; break;
       case 563: // Регулятор №4. Коэффициент пропорциональности. Давление пара на выходе РУ №1.
                 Val = RegFl[410]; if (Link_OBSK) Status=0; else Status=1; break;
       case 564: // Регулятор №4. Время интегрирования. Давление пара на выходе РУ №1.
                 Val = RegFlEx[412]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 565: // Регулятор №4. Зона нечувствительности. Давление пара на выходе РУ №1.
                 Val = RegFl[414]; if (Link_OBSK) Status=0; else Status=1; break;
       case 566: // Регулятор №4. Время хода. Давление пара на выходе РУ №1.
                 Val = RegFlEx[591]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 567: // Регулятор №4. Минимальный импульс. Давление пара на выходе РУ №1.
                 Val = RegFlEx[593]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 568: // Регулятор №4. Выход. Давление пара на выходе РУ №1.
                 Val = RegFl[522]; if (Link_OBSK) Status=0; else Status=1; break;
       case 569: // Клапан PV-761. Команда "открыть" с ПК
                 Val = Reg[31]; if (Link_OBSK) Status=0; else Status=1; break;
       case 570: // Клапан PV-761. Команда "закрыть" с ПК
                 Val = Reg[32]; if (Link_OBSK) Status=0; else Status=1; break;
       case 571: // Клапан PV-761. Команда "стоп" с ПК
                 Val = Reg[33]; if (Link_OBSK) Status=0; else Status=1; break;

       case 581: // Регулятор №5. Режим регулятора. Давление пара на выходе РУ №2.
                 Val = Reg[34]; if (Link_OBSK) Status=0; else Status=1; break;
       case 582: // Регулятор №5. Задание. Давление пара на выходе РУ №2.
                 Val = RegFl[524]; if (Link_OBSK) Status=0; else Status=1; break;
       case 583: // Регулятор №5. Коэффициент пропорциональности. Давление пара на выходе РУ №2.
                 Val = RegFl[450]; if (Link_OBSK) Status=0; else Status=1; break;
       case 584: // Регулятор №5. Время интегрирования. Давление пара на выходе РУ №2.
                 Val = RegFlEx[452]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 585: // Регулятор №5. Зона нечувствительности. Давление пара на выходе РУ №2.
                 Val = RegFl[454]; if (Link_OBSK) Status=0; else Status=1; break;
       case 586: // Регулятор №5. Время хода. Давление пара на выходе РУ №2.
                 Val = RegFlEx[601]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 587: // Регулятор №5. Минимальный импульс. Давление пара на выходе РУ №2.
                 Val = RegFlEx[603]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 588: // Регулятор №5. Выход. Давление пара на выходе РУ №2.
                 Val = RegFl[526]; if (Link_OBSK) Status=0; else Status=1; break;
       case 589: // Клапан PV-771. Команда "открыть" с ПК
                 Val = Reg[35]; if (Link_OBSK) Status=0; else Status=1; break;
       case 590: // Клапан PV-771. Команда "закрыть" с ПК
                 Val = Reg[36]; if (Link_OBSK) Status=0; else Status=1; break;
       case 591: // Клапан PV-771. Команда "стоп" с ПК
                 Val = Reg[37]; if (Link_OBSK) Status=0; else Status=1; break;

       case 601: // Регулятор №6. Режим регулятора. Уровень в сетевом деаэраторе.
                 Val = Reg[10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 602: // Регулятор №6. Задание. Уровень в сетевом деаэраторе.
                 Val = RegFl[500]; if (Link_OBSK) Status=0; else Status=1; break;
       case 603: // Регулятор №6. Коэффициент пропорциональности. Уровень в сетевом деаэраторе.
                 Val = RegFl[210]; if (Link_OBSK) Status=0; else Status=1; break;
       case 604: // Регулятор №6. Время интегрирования. Уровень в сетевом деаэраторе.
                 Val = RegFlEx[212]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 605: // Регулятор №6. Зона нечувствительности. Уровень в сетевом деаэраторе.
                 Val = RegFl[214]; if (Link_OBSK) Status=0; else Status=1; break;
       case 606: // Регулятор №6. Время хода. Уровень в сетевом деаэраторе.
                 Val = RegFlEx[541]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 607: // Регулятор №6. Минимальный импульс. Уровень в сетевом деаэраторе.
                 Val = RegFlEx[543]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 608: // Регулятор №6. Выход. Уровень в сетевом деаэраторе.
                 Val = RegFl[502]; if (Link_OBSK) Status=0; else Status=1; break;
       case 609: // Клапан PV-721. Команда "открыть" с ПК
                 Val = Reg[11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 610: // Клапан PV-721. Команда "закрыть" с ПК
                 Val = Reg[12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 611: // Клапан PV-721. Команда "стоп" с ПК
                 Val = Reg[13]; if (Link_OBSK) Status=0; else Status=1; break;

       case 621: // Регулятор №7. Режим регулятора. Уровень в питательном деаэраторе.
                 Val = Reg[14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 622: // Регулятор №7. Задание. Уровень в питательном деаэраторе.
                 Val = RegFl[504]; if (Link_OBSK) Status=0; else Status=1; break;
       case 623: // Регулятор №7. Коэффициент пропорциональности. Уровень в питательном деаэраторе.
                 Val = RegFl[250]; if (Link_OBSK) Status=0; else Status=1; break;
       case 624: // Регулятор №7. Время интегрирования. Уровень в питательном деаэраторе.
                 Val = RegFlEx[252]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 625: // Регулятор №7. Зона нечувствительности. Уровень в питательном деаэраторе.
                 Val = RegFl[254]; if (Link_OBSK) Status=0; else Status=1; break;
       case 626: // Регулятор №7. Время хода. Уровень в питательном деаэраторе.
                 Val = RegFlEx[551]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 627: // Регулятор №7. Минимальный импульс. Уровень в питательном деаэраторе.
                 Val = RegFlEx[553]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 628: // Регулятор №7. Выход. Уровень в питательном деаэраторе.
                 Val = RegFl[506]; if (Link_OBSK) Status=0; else Status=1; break;
       case 629: // Клапан PV-731. Команда "открыть" с ПК
                 Val = Reg[15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 630: // Клапан PV-731. Команда "закрыть" с ПК
                 Val = Reg[16]; if (Link_OBSK) Status=0; else Status=1; break;
       case 631: // Клапан PV-731. Команда "стоп" с ПК
                 Val = Reg[17]; if (Link_OBSK) Status=0; else Status=1; break;

       case 800: // Уставка минимального давления питательной линии №1
                 Val = RegFl[424]; if (Link_OBSK) Status=0; else Status=1; break;
       case 801: // Уставка минимального давления питательной линии №2
                 Val = RegFl[426]; if (Link_OBSK) Status=0; else Status=1; break;
       case 802: // Уставка разницы давлений питательных линий
                 Val = RegFl[428]; if (Link_OBSK) Status=0; else Status=1; break;
       case 803: // Давление в питательной линии №1. Максимум .
                 Val = RegFl[640]; if (Link_OBSK) Status=0; else Status=1; break;
       case 804: // Давление в питательной линии №1. Минимум.
                 Val = RegFl[642]; if (Link_OBSK) Status=0; else Status=1; break;
       case 805: // Давление в питательной линии №1. Гистерезис.
                 Val = RegFl[644]; if (Link_OBSK) Status=0; else Status=1; break;
       case 806: // Давление в питательной линии №2. Максимум.
                 Val = RegFl[646]; if (Link_OBSK) Status=0; else Status=1; break;
       case 807: // Давление в питательной линии №2. Минимум.
                 Val = RegFl[648]; if (Link_OBSK) Status=0; else Status=1; break;
       case 808: // Давление в питательной линии №2. Гистерезис.
                 Val = RegFl[650]; if (Link_OBSK) Status=0; else Status=1; break;
       case 809: // Давление прямой воды в системе отопления. Максимум.
                 Val = RegFl[652]; if (Link_OBSK) Status=0; else Status=1; break;
       case 810: // Давление прямой воды в системе отопления. Минимум.
                 Val = RegFl[654]; if (Link_OBSK) Status=0; else Status=1; break;
       case 811: // Давление прямой воды в системе отопления. Гистерезис.
                 Val = RegFl[656]; if (Link_OBSK) Status=0; else Status=1; break;
       case 812: // Давление подачи ГВС. Максимум.
                 Val = RegFl[658]; if (Link_OBSK) Status=0; else Status=1; break;
       case 813: // Давление подачи ГВС. Гистирезис.
                 Val = RegFl[660]; if (Link_OBSK) Status=0; else Status=1; break;
       case 814: // Давление пара в сепараторе. Максимум.
                 Val = RegFl[662]; if (Link_OBSK) Status=0; else Status=1; break;
       case 815: // Давление пара в сепараторе. Гистерезис.
                 Val = RegFl[664]; if (Link_OBSK) Status=0; else Status=1; break;
       case 816: // Давление пара на гребёнке. Максимум.
                 Val = RegFl[666]; if (Link_OBSK) Status=0; else Status=1; break;
       case 817: // Давление пара на гребёнке. Минимум.
                 Val = RegFl[668]; if (Link_OBSK) Status=0; else Status=1; break;
       case 818: // Давление пара на гребёнке. Гистерезис.
                 Val = RegFl[670]; if (Link_OBSK) Status=0; else Status=1; break;
       case 819: // Уровень в баке аккумулятора №1. Максимум.
                 Val = RegFl[672]; if (Link_OBSK) Status=0; else Status=1; break;
       case 820: // Уровень в баке аккумулятора №1. Минимум.
                 Val = RegFl[674]; if (Link_OBSK) Status=0; else Status=1; break;
       case 821: // Уровень в баке аккумулятора №1. Гистерезис.
                 Val = RegFl[676]; if (Link_OBSK) Status=0; else Status=1; break;
       case 822: // Уровень в баке аккумулятора №2. Максимум.
                 Val = RegFl[678]; if (Link_OBSK) Status=0; else Status=1; break;
       case 823: // Уровень в баке аккумулятора №2. Минимум.
                 Val = RegFl[680]; if (Link_OBSK) Status=0; else Status=1; break;
       case 824: // Уровень в баке аккумулятора №2. Гистерезис.
                 Val = RegFl[682]; if (Link_OBSK) Status=0; else Status=1; break;
       case 825: // Уровень в сетевом деаэраторе. Максимум.
                 Val = RegFl[684]; if (Link_OBSK) Status=0; else Status=1; break;
       case 826: // Уровень в сетевом деаэраторе. Минимум.
                 Val = RegFl[686]; if (Link_OBSK) Status=0; else Status=1; break;
       case 827: // Уровень в сетевом деаэраторе. Гистерезис.
                 Val = RegFl[688]; if (Link_OBSK) Status=0; else Status=1; break;
       case 828: // Уровень в питательном деаэраторе. Максимум.
                 Val = RegFl[690]; if (Link_OBSK) Status=0; else Status=1; break;
       case 829: // Уровень в питательном деаэраторе. Минимум.
                 Val = RegFl[692]; if (Link_OBSK) Status=0; else Status=1; break;
       case 830: // Уровень в питательном деаэраторе. Гистерезис.
                 Val = RegFl[694]; if (Link_OBSK) Status=0; else Status=1; break;
       case 831: // квитирование
                 Val = Reg[222]; if (Link_OBSK) Status=0; else Status=1; break;
       case 1001: // К3. Давление газа перед горелкой.
       case 1002: // К3. Давление воздуха перед горелкой
       case 1003: // К3. Разрежение в топке котла
       case 1004: // К3. Давление пара на выходе котла
       case 1005: // K3. Уровень(1) в барабане котла
       case 1006: // К3. Уровень(2) в барабане котла
       case 1007: // K3. Положение регулирующего клапана питательной воды
       case 1008: // K3. Положение газовой заслонки
       case 1009: // K3. Температура дыма до экономайзера
       case 1010: // К3. Температура дыма после экономайзера
       case 1011: // К3. Температура воды после экономайзера
       case 1012: // К3. Температура воды до экономайзера
       case 1013: // K3. Мгновенный расход воды
       case 1014: // K3. Расход воды текущий час
       case 1015: // K3. Расход воды предыдущий час
       case 1016: // К3. Расход воды текущий день
       case 1017: // K3. Расход воды предыдущий день
       case 1018: // К3. Клапан запальника открыт
       case 1019: // К3. Отсечной клапан №1 открыт
       case 1020: // К3. Отсечной клапан №2 открыт
       case 1021: // К3. Клапан свечи безопасности открыт
       case 1022: // К3. Наличие пламени
       case 1023: // К3. Режим управления задвижкой газа
       case 1024: // К3. Режим управления воздуходувом
       case 1025: // К3. Режим управления дымососом
       case 1026: // К3. Режим управления задвижкой воды
       case 1027: // К3. ЧРП воздуходува. Частота вращения
       case 1028: // К3. ЧРП воздуходува. Выходной ток
       case 1029: // К3. ЧРП воздуходува. Выходное напряжение
       case 1030: // К3. ЧРП воздуходува. Состояние
       case 1031: // К3. ЧРП воздуходува. Неисправности
       case 1032: // К3. ЧРП воздуходува. Ошибки обмена
       case 1033: // К3. ЧРП дымососа. Частота вращения
       case 1034: // К3. ЧРП дымососа. Выходной ток
       case 1035: // К3. ЧРП дымососа. Выходное напряжение
       case 1036: // К3. ЧРП дымососа. Состояние
       case 1037: // К3. ЧРП дымососа. Неисправности
       case 1038: // К3. ЧРП дымососа. Ошибки обмена
       case 1039: // К3. Сигнализация. Ошибка связи с модулем
       case 1040: // К3. Сигнализация. Обрыв линии связи
       case 1041: // К3. Сигнализация. Загазованность 1-ый порог
       case 1042: // К3. Сигнализация. Низкий уровень в барабане котла
       case 1043: // К3. Сигнализация. Высокий уровень в барабане котла
       case 1044: // К3. Сигнализация. Максимальное давление пара
       case 1045: // К3. Сигнализация. Высокая температура дымовых газов до экономайзера
       case 1046: // К3. Сигнализация. Высокая температура дымовых газов после экономайзера
       case 1047: // К3. Сигнализация. Высокая температура воды до экономайзера
       case 1048: // К3. Сигнализация. Высокая температура воды после экономайзера
       case 1049: // К3. Сигнализация. Расход воды мал.
       case 1050: // К3. Сигнализация. Загазованность по СН4
       case 1051: // К3. Сигнализация. Рассогласование регулятора воздуха
       case 1052: // К3. Сигнализация. Рассогласование регулятора разрежения
       case 1053: // К3. Котел готов к пуску
       case 1054: // К3. Вентиляция топки котла
       case 1055: // К3. Опрессовка
       case 1056: // К3. Котел готов к розжигу
       case 1057: // К3. Розжиг
       case 1058: // К3. Прогрев котла
       case 1059: // К3. Котел в работе
       case 1060: // К3. Авария котла
       case 1061: // К3. Сигнализация
       case 1062: // К3. Наличие газа при закрытых отсекателях
       case 1063: // К3. Давление газа перед горелкой меньше допустимого
       case 1064: // К3. Давление газа перед горелкой больше допустимого
       case 1065: // К3. Загазованность по СО
       case 1066: // К3. Отсутствует электроснабжение
       case 1067: // К3. Давление воздуха перед горелкой меньше допустимого
       case 1068: // К3. Разрежение в топке мало
       case 1069: // К3. Уровень в барабане котла мал
       case 1070: // К3. Уровень в барабане котла велик
       case 1071: // К3. Давление пара больше допустимого
       case 1072: // К3. Нет пламени
       case 1073: // К3. Наличие пламени при закрытых отсечных клапанах
       case 1074: // К3. Неисправность ЧРП вентилятора
       case 1075: // К3. Неисправность ЧРП дымососа
       case 1076: // К3. Обрыв линии связи с датчиком
       case 1077: // К3. Ошибка связи с модулем
       case 1078: // К3. Негерметичен газовый клапан
       case 1079: // К3. Нажата кнопка СТОП
       case 1080: // К3. Высокое давление в топке котла
       case 1081: // К3. Неисправна газовая заслонка
       case 1082: // К3. Неисправность модуля вывода
       case 1083: // К3. Авария ЧРП вентилятора. Большое рассогласование.
       case 1084: // К3. Включена блокировка ошибка связи с ВАМ1
       case 1085: // К3. Включена блокировка обрыв датчика PI1
       case 1086: // K3. Включена блокировка обрыв датчика PI2
       case 1087: // К3. Включена блокировка обрыв датчика DPI3
       case 1088: // К3. Включена блокировка обрыв датчика LI2
       case 1089: // K3. Включена блокировка ошибка связи с ВДМ4
       case 1090: // К3. Включена блокировка обрыв датчика DI6
       case 1091: // К3. Включена блокировка обрыв датчика DI16
       case 1092: // К3. Включена блокировка ошибка связи с ВДМ5
       case 1093: // К3. Включена блокировка ошибка связи с МДВ6
       case 1094: // К3. Включена блокировка наличие газа между отсечными клапанами
       case 1095: // К3. Включена блокировка негерметичный газовый клапан AV1
       case 1096: // К3. Включена блокировка негерметичный газовый клапан AV2
       case 1097: // K3. Включена блокировка негерметичный газовый клапан AV3
       case 1098: // К3. Включена блокировка наличие пламени при закрытых отсечных клапанах
       case 1099: // К3. Включена блокировка нет пламени, контроль розжига
       case 1100: // К3. Включена блокировка нет пламени, контроль  потухания
       case 1101: // К3. Включена блокировка минимальное давление газа
       case 1102: // К3. Включена блокировка максимальное давление газа
       case 1103: // К3. Включена блокировка контроль герметичности, верхняя уставка
       case 1104: // К3. Включена блокировка минимальное давление воздуха
       case 1105: // К3. Включена блокировка минимальное давление воздуха при включенной вентиляции
       case 1106: // К3. Включена блокировка минимальное разрежение
       case 1107: // К3. Включена блокировка максимальное давление пара
       case 1108: // К3. Включена блокировка минимальный уровень в барабане котла
       case 1109: // К3. Включена блокировка максимальный уровень в барабане котла
       case 1110: // К3. Включена блокировка загазованность СО 2-ой порог
       case 1111: // К3. Включена блокировка отсутствие электроснабжения
       case 1112: // К3. Включена блокировка давление в топке
       case 1113: // К3. Включена блокировка нажата кнопка СТОП
       case 1114: // К3. Включена блокировка неисправна газовая заслонка
       case 1115: // К3. Включена блокировка авария ЧРП вентилятора, контроль включения
       case 1116: // К3. Включена блокировка авария ЧРП вентилятора, контроль выключения
       case 1117: // К3. Включена блокировка авария ЧРП дымососа, контроль включения
       case 1118: // К3. Включена блокировка авария ЧРП дымососа, контроль выключения
       case 1119: // К3. Включена блокировка авария ЧРП вентилятора, большое рассогласование
       case 1120: // К3. Задержка блокировки. Ошибка связи с ВАМ1
       case 1121: // К3. Задержка блокировки. Обрыв датчика PI1
       case 1122: // К3. Задержка блокировки. Обрыв датчика PI2
       case 1123: // К3. Задержка блокировки. Обрыв датчика DIP3
       case 1124: // К3. Задержка блокировки. Обрыв датчика LI2
       case 1125: // К3. Задержка блокировки. Ошибка связи с ВДМ4
       case 1126: // К3. Задержка блокировки. Обрыв датчика DI6
       case 1127: // К3. Задержка блокировки. Обрыв датчика  DI16
       case 1128: // К3. Задержка блокировки. Ошибка связи с ВДМ5
       case 1129: // К3. Задержка блокировки. Ошибка связи с МДВ6
       case 1130: // К3. Задержка блокировки. Наличие газа между отсечными клапанами
       case 1131: // К3. Задержка блокировки. Негерметичный газовый клапан AV1
       case 1132: // К3. Задержка блокировки. Негерметичный газовый клапан AV2
       case 1133: // К3. Задержка блокировки. Негерметичный газовый клапан AV3
       case 1134: // К3. Задержка блокировки. Наличие пламени при закрытых отсекателях
       case 1135: // К3. Задержка блокировки. Нет пламени, контроль розжига
       case 1136: // К3. Задержки блокировки. Нет пламени, контроль потухания
       case 1137: // К3. Задержки блокировки. Минимальное давление газа
       case 1138: // К3. Задержки блокировки. Максимальное давление газа
       case 1139: // К3. Задержки блокировки. Контроль герметичности, верхняя уставка
       case 1140: // К3. Задержки блокировки. Минимальное давление воздуха
       case 1141: // К3. Задержки блокировки. Минимальное давление воздуха при включенной вентиляции
       case 1142: // К3. Задержки блокировки. Минимальное разрежение
       case 1143: // К3. Задержки блокировки. Максимальное давление пара
       case 1144: // К3. Задержки блокировки. Минимальный уровень в барабане котла
       case 1145: // К3. Задержки блокировки. Максимальный уровень в барабане котла
       case 1146: // К3. Задержки блокировки. Загазованность CO 2-ой порог
       case 1147: // К3. Задержки блокировки. Отсутствие электроснабжения
       case 1148: // К3. Задержки блокировки. Давление в топке
       case 1149: // К3. Задержки блокировки. Нажата кнопка СТОП
       case 1150: // К3. Задержки блокировки. Неисправна газовая заслонка
       case 1151: // К3. Задержки блокировки. Авария ЧРП вентилятора, контроль включения
       case 1152: // К3. Задержки блокировки. Авария ЧРП вентилятора, контроль выключения
       case 1153: // К3. Задержки блокировки. Авария ЧРП дымососа, контроль включения
       case 1154: // К3. Задержки блокировки. Авария ЧРП дымососа, контроль выключения
       case 1155: // К3. Задержки блокировки. Авария ЧРП вентилятора, большое рассогласование
       case 1156: // К3. Регулятор пара. Задание
       case 1157: // К3. Регулятор пара. Время фильтра (тф)
       case 1158: // К3. Регулятор пара. Коэффициент дх
       case 1159: // К3. Регулятор пара. Коэффициент пропорциональности (Кп)
       case 1160: // К3. Регулятор пара. Коэффициент интегрирования (Ки)
       case 1161: // К3. Регулятор пара. Коэффициент дифференцирования (Кд)
       case 1162: // К3. Регулятор пара. Коэффициент тм
       case 1163: // К3. Регулятор пара. Время импульса (Тимп)
       case 1164: // К3. Регулятор воздуха. Задание
       case 1165: // К3. Регулятор воздуха. Время фильтра (тф)
       case 1166: // К3. Регулятор воздуха. Коэффициент дх
       case 1167: // К3. Регулятор воздуха. Коэффициент пропорциональности (Кп)
       case 1168: // К3. Регулятор воздуха. Коэффициент интегрирования (Ки)
       case 1169: // К3. Регулятор воздуха. Коэффициент дифференцирования (Кд)
       case 1170: // К3. Регулятор воздуха. Коэффициент тм
       case 1171: // К3. Регулятор воздуха. Время импульса (Тимп)
       case 1172: // К3. Регулятор разрежение. Задание
       case 1173: // К3. Регулятор разрежение. Время фильтра (тф)
       case 1174: // К3. Регулятор разрежение. Коэффициент дх
       case 1175: // К3. Регулятор разрежение. Коэффициент пропорциональности (Кп)
       case 1176: // К3. Регулятор разрежение. Коэффициент интерирования (Ки)
       case 1177: // К3. Регулятор разрежение. Коэффициент дифференцирования (Кд)
       case 1178: // К3. Регулятор разрежение. Коэффициент тм
       case 1179: // К3. Регулятор разрежение. Время импульса (Тим)
       case 1180: // К3. Регулятор вода. Задание
       case 1181: // К3. Регулятор вода. Время фильтра (тф)
       case 1182: // К3. Регулятор вода. Коэффицент дх
       case 1183: // К3. Регулятор вода. Коэффициент пропорцимональности (Кп)
       case 1184: // К3. Регулятор вода. Коэффициент интегрирования (Ки)
       case 1185: // К3. Регулятор вода. Коэффициент дифференцирования (Кд)
       case 1186: // К3. Регулятор вода. Коэффициент тм
       case 1187: // К3. Регулятор вода. Время импульса (Тим)
       case 1188: // К3. UPS. Входное напряжение
       case 1189: // K3. UPS. Входное напряжение (fault)
       case 1190: // K3. UPS. Выходное напряжение
       case 1191: // K3. UPS. Нагрузка в процентах
       case 1192: // K3. UPS. Частота
       case 1193: // K3. UPS. Температура
       case 1194: // K3. UPS. Заряд батареи
       case 1195: // K3. UPS. Состояние
       case 1196: // К3. Диагностика обрывов
       case 1197: // К3. Диагностика связи с модулями
       case 1198: // K3. В работе основной контроллер
       case 1199: // K3. В работе резервный контроллер
                  Val  = DataFlUstr[IDTag-1];
                  if (Link_Kotel_DE1) Status = 1 - StatFlUstr[IDTag-1];
                  else                Status = 1;
                  break;
       case 1200: // К3. Вентилятор воздуха включен
                  if (DataFlUstr[1026]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1026];
                  break;
       case 1201: // К3. Дымосос включен
                  if (DataFlUstr[1032]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1032];
                  break;
       case 1301: // К4. Давление газа перед горелкой.
       case 1302: // К4. Давление воздуха перед горелкой
       case 1303: // К4. Разрежение в топке котла
       case 1304: // К4. Давление пара на выходе котла
       case 1305: // K4. Уровень(1) в барабане котла
       case 1306: // К4. Уровень(2) в барабане котла
       case 1307: // K4. Положение регулирующего клапана питательной воды
       case 1308: // K4. Положение газовой заслонки
       case 1309: // K4. Температура дыма до экономайзера
       case 1310: // К4. Температура дыма после экономайзера
       case 1311: // К4. Температура воды после экономайзера
       case 1312: // К4. Температура воды до экономайзера
       case 1313: // K4. Мгновенный расход воды
       case 1314: // K4. Расход воды текущий час
       case 1315: // K4. Расход воды предыдущий час
       case 1316: // К4. Расход воды текущий день
       case 1317: // K4. Расход воды предыдущий день
       case 1318: // К4. Клапан запальника открыт
       case 1319: // К4. Отсечной клапан №1 открыт
       case 1320: // К4. Отсечной клапан №2 открыт
       case 1321: // К4. Клапан свечи безопасности открыт
       case 1322: // К4. Наличие пламени
       case 1323: // К4. Режим управления задвижкой газа
       case 1324: // К4. Режим управления воздуходувом
       case 1325: // К4. Режим управления дымососом
       case 1326: // К4. Режим управления задвижкой воды
       case 1327: // К4. ЧРП воздуходува. Частота вращения
       case 1328: // К4. ЧРП воздуходува. Выходной ток
       case 1329: // К4. ЧРП воздуходува. Выходное напряжение
       case 1330: // К4. ЧРП воздуходува. Состояние
       case 1331: // К4. ЧРП воздуходува. Неисправности
       case 1332: // К4. ЧРП воздуходува. Ошибки обмена
       case 1333: // К4. ЧРП дымососа. Частота вращения
       case 1334: // К4. ЧРП дымососа. Выходной ток
       case 1335: // К4. ЧРП дымососа. Выходное напряжение
       case 1336: // К4. ЧРП дымососа. Состояние
       case 1337: // К4. ЧРП дымососа. Неисправности
       case 1338: // К4. ЧРП дымососа. Ошибки обмена
       case 1339: // К4. Сигнализация. Ошибка связи с модулем
       case 1340: // К4. Сигнализация. Обрыв линии связи
       case 1341: // К4. Сигнализация. Загазованность 1-ый порог
       case 1342: // К4. Сигнализация. Низкий уровень в барабане котла
       case 1343: // К4. Сигнализация. Высокий уровень в барабане котла
       case 1344: // К4. Сигнализация. Максимальное давление пара
       case 1345: // К4. Сигнализация. Высокая температура дымовых газов до экономайзера
       case 1346: // К4. Сигнализация. Высокая температура дымовых газов после экономайзера
       case 1347: // К4. Сигнализация. Высокая температура воды до экономайзера
       case 1348: // К4. Сигнализация. Высокая температура воды после экономайзера
       case 1349: // К4. Сигнализация. Расход воды мал.
       case 1350: // К4. Сигнализация. Загазованность по СН4
       case 1351: // К4. Сигнализация. Рассогласование регулятора воздуха
       case 1352: // К4. Сигнализация. Рассогласование регулятора разрежения
       case 1353: // К4. Котел готов к пуску
       case 1354: // К4. Вентиляция топки котла
       case 1355: // К4. Опрессовка
       case 1356: // К4. Котел готов к розжигу
       case 1357: // К4. Розжиг
       case 1358: // К4. Прогрев котла
       case 1359: // К4. Котел в работе
       case 1360: // К4. Авария котла
       case 1361: // К4. Сигнализация
       case 1362: // К4. Наличие газа при закрытых отсекателях
       case 1363: // К4. Давление газа перед горелкой меньше допустимого
       case 1364: // К4. Давление газа перед горелкой больше допустимого
       case 1365: // К4. Загазованность по СО
       case 1366: // К4. Отсутствует электроснабжение
       case 1367: // К4. Давление воздуха перед горелкой меньше допустимого
       case 1368: // К4. Разрежение в топке мало
       case 1369: // К4. Уровень в барабане котла мал
       case 1370: // К4. Уровень в барабане котла велик
       case 1371: // К4. Давление пара больше допустимого
       case 1372: // К4. Нет пламени
       case 1373: // К4. Наличие пламени при закрытых отсечных клапанах
       case 1374: // К4. Неисправность ЧРП вентилятора
       case 1375: // К4. Неисправность ЧРП дымососа
       case 1376: // К4. Обрыв линии связи с датчиком
       case 1377: // К4. Ошибка связи с модулем
       case 1378: // К4. Негерметичен газовый клапан
       case 1379: // К4. Нажата кнопка СТОП
       case 1380: // К4. Высокое давление в топке котла
       case 1381: // К4. Неисправна газовая заслонка
       case 1382: // К4. Неисправность модуля вывода
       case 1383: // К4. Авария ЧРП вентилятора. Большое рассогласование.
       case 1384: // К4. Включена блокировка ошибка связи с ВАМ1
       case 1385: // К4. Включена блокировка обрыв датчика PI1
       case 1386: // K4. Включена блокировка обрыв датчика PI2
       case 1387: // К4. Включена блокировка обрыв датчика DPI3
       case 1388: // К4. Включена блокировка обрыв датчика LI2
       case 1389: // K4. Включена блокировка ошибка связи с ВДМ4
       case 1390: // К4. Включена блокировка обрыв датчика DI6
       case 1391: // К4. Включена блокировка обрыв датчика DI16
       case 1392: // К4. Включена блокировка ошибка связи с ВДМ5
       case 1393: // К4. Включена блокировка ошибка связи с МДВ6
       case 1394: // К4. Включена блокировка наличие газа между отсечными клапанами
       case 1395: // К4. Включена блокировка негерметичный газовый клапан AV1
       case 1396: // К4. Включена блокировка негерметичный газовый клапан AV2
       case 1397: // K4. Включена блокировка негерметичный газовый клапан AV3
       case 1398: // К4. Включена блокировка наличие пламени при закрытых отсечных клапанах
       case 1399: // К4. Включена блокировка нет пламени, контроль розжига
       case 1400: // К4. Включена блокировка нет пламени, контроль  потухания
       case 1401: // К4. Включена блокировка минимальное давление газа
       case 1402: // К4. Включена блокировка максимальное давление газа
       case 1403: // К4. Включена блокировка контроль герметичности, верхняя уставка
       case 1404: // К4. Включена блокировка минимальное давление воздуха
       case 1405: // К4. Включена блокировка минимальное давление воздуха при включенной вентиляции
       case 1406: // К4. Включена блокировка минимальное разрежение
       case 1407: // К4. Включена блокировка максимальное давление пара
       case 1408: // К4. Включена блокировка минимальный уровень в барабане котла
       case 1409: // К4. Включена блокировка максимальный уровень в барабане котла
       case 1410: // К4. Включена блокировка загазованность СО 2-ой порог
       case 1411: // К4. Включена блокировка отсутствие электроснабжения
       case 1412: // К4. Включена блокировка давление в топке
       case 1413: // К4. Включена блокировка нажата кнопка СТОП
       case 1414: // К4. Включена блокировка неисправна газовая заслонка
       case 1415: // К4. Включена блокировка авария ЧРП вентилятора, контроль включения
       case 1416: // К4. Включена блокировка авария ЧРП вентилятора, контроль выключения
       case 1417: // К4. Включена блокировка авария ЧРП дымососа, контроль включения
       case 1418: // К4. Включена блокировка авария ЧРП дымососа, контроль выключения
       case 1419: // К4. Включена блокировка авария ЧРП вентилятора, большое рассогласование
       case 1420: // К4. Задержка блокировки. Ошибка связи с ВАМ1
       case 1421: // К4. Задержка блокировки. Обрыв датчика PI1
       case 1422: // К4. Задержка блокировки. Обрыв датчика PI2
       case 1423: // К4. Задержка блокировки. Обрыв датчика DIP3
       case 1424: // К4. Задержка блокировки. Обрыв датчика LI2
       case 1425: // К4. Задержка блокировки. Ошибка связи с ВДМ4
       case 1426: // К4. Задержка блокировки. Обрыв датчика DI6
       case 1427: // К4. Задержка блокировки. Обрыв датчика  DI16
       case 1428: // К4. Задержка блокировки. Ошибка связи с ВДМ5
       case 1429: // К4. Задержка блокировки. Ошибка связи с МДВ6
       case 1430: // К4. Задержка блокировки. Наличие газа между отсечными клапанами
       case 1431: // К4. Задержка блокировки. Негерметичный газовый клапан AV1
       case 1432: // К4. Задержка блокировки. Негерметичный газовый клапан AV2
       case 1433: // К4. Задержка блокировки. Негерметичный газовый клапан AV3
       case 1434: // К4. Задержка блокировки. Наличие пламени при закрытых отсекателях
       case 1435: // К4. Задержка блокировки. Нет пламени, контроль розжига
       case 1436: // К4. Задержки блокировки. Нет пламени, контроль потухания
       case 1437: // К4. Задержки блокировки. Минимальное давление газа
       case 1438: // К4. Задержки блокировки. Максимальное давление газа
       case 1439: // К4. Задержки блокировки. Контроль герметичности, верхняя уставка
       case 1440: // К4. Задержки блокировки. Минимальное давление воздуха
       case 1441: // К4. Задержки блокировки. Минимальное давление воздуха при включенной вентиляции
       case 1442: // К4. Задержки блокировки. Минимальное разрежение
       case 1443: // К4. Задержки блокировки. Максимальное давление пара
       case 1444: // К4. Задержки блокировки. Минимальный уровень в барабане котла
       case 1445: // К4. Задержки блокировки. Максимальный уровень в барабане котла
       case 1446: // К4. Задержки блокировки. Загазованность CO 2-ой порог
       case 1447: // К4. Задержки блокировки. Отсутствие электроснабжения
       case 1448: // К4. Задержки блокировки. Давление в топке
       case 1449: // К4. Задержки блокировки. Нажата кнопка СТОП
       case 1450: // К4. Задержки блокировки. Неисправна газовая заслонка
       case 1451: // К4. Задержки блокировки. Авария ЧРП вентилятора, контроль включения
       case 1452: // К4. Задержки блокировки. Авария ЧРП вентилятора, контроль выключения
       case 1453: // К4. Задержки блокировки. Авария ЧРП дымососа, контроль включения
       case 1454: // К4. Задержки блокировки. Авария ЧРП дымососа, контроль выключения
       case 1455: // К4. Задержки блокировки. Авария ЧРП вентилятора, большое рассогласование
       case 1456: // К4. Регулятор пара. Задание
       case 1457: // К4. Регулятор пара. Время фильтра (тф)
       case 1458: // К4. Регулятор пара. Коэффициент дх
       case 1459: // К4. Регулятор пара. Коэффициент пропорциональности (Кп)
       case 1460: // К4. Регулятор пара. Коэффициент интегрирования (Ки)
       case 1461: // К4. Регулятор пара. Коэффициент дифференцирования (Кд)
       case 1462: // К4. Регулятор пара. Коэффициент тм
       case 1463: // К4. Регулятор пара. Время импульса (Тимп)
       case 1464: // К4. Регулятор воздуха. Задание
       case 1465: // К4. Регулятор воздуха. Время фильтра (тф)
       case 1466: // К4. Регулятор воздуха. Коэффициент дх
       case 1467: // К4. Регулятор воздуха. Коэффициент пропорциональности (Кп)
       case 1468: // К4. Регулятор воздуха. Коэффициент интегрирования (Ки)
       case 1469: // К4. Регулятор воздуха. Коэффициент дифференцирования (Кд)
       case 1470: // К4. Регулятор воздуха. Коэффициент тм
       case 1471: // К4. Регулятор воздуха. Время импульса (Тимп)
       case 1472: // К4. Регулятор разрежение. Задание
       case 1473: // К4. Регулятор разрежение. Время фильтра (тф)
       case 1474: // К4. Регулятор разрежение. Коэффициент дх
       case 1475: // К4. Регулятор разрежение. Коэффициент пропорциональности (Кп)
       case 1476: // К4. Регулятор разрежение. Коэффициент интерирования (Ки)
       case 1477: // К4. Регулятор разрежение. Коэффициент дифференцирования (Кд)
       case 1478: // К4. Регулятор разрежение. Коэффициент тм
       case 1479: // К4. Регулятор разрежение. Время импульса (Тим)
       case 1480: // К4. Регулятор вода. Задание
       case 1481: // К4. Регулятор вода. Время фильтра (тф)
       case 1482: // К4. Регулятор вода. Коэффицент дх
       case 1483: // К4. Регулятор вода. Коэффициент пропорцимональности (Кп)
       case 1484: // К4. Регулятор вода. Коэффициент интегрирования (Ки)
       case 1485: // К4. Регулятор вода. Коэффициент дифференцирования (Кд)
       case 1486: // К4. Регулятор вода. Коэффициент тм
       case 1487: // К4. Регулятор вода. Время импульса (Тим)
       case 1488: // К4. UPS. Входное напряжение
       case 1489: // K4. UPS. Входное напряжение (fault)
       case 1490: // K4. UPS. Выходное напряжение
       case 1491: // K4. UPS. Нагрузка в процентах
       case 1492: // K4. UPS. Частота
       case 1493: // K4. UPS. Температура
       case 1494: // K4. UPS. Заряд батареи
       case 1495: // K4. UPS. Состояние
       case 1496: // К4. Диагностика обрывов
       case 1497: // К4. Диагностика связи с модулями
       case 1498: // K4. В работе основной контроллер
       case 1499: // K4. В работе резервный контроллер
                  Val  = DataFlUstr[IDTag-1];
                  if (Link_Kotel_DE1) Status = 1 - StatFlUstr[IDTag-1];
                  else                Status = 1;
                  break;
       case 1500: // К4. Вентилятор воздуха включен
                  if (DataFlUstr[1026]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1026];
                  break;
       case 1501: // К4. Дымосос включен
                  if (DataFlUstr[1032]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1032];
                  break;
      }
     if ((QListTagsValueTag->AsFloat!=Val)||(QListTagsStatusTag->AsInteger!=Status)||
         ((sh)&&(Status1==0)&&(Status2==0)&&((QListTagsMinValIn->AsFloat!=Val1)||(QListTagsMinValIn->AsFloat!=Val2)))
        )
      {
       QListTags->Edit();
       QListTagsValueTag->AsFloat    = Val;
       QListTagsStatusTag->AsInteger = Status;
       if ((sh)&&(Status1==0)&&(Status2==0))
        {
         QListTagsMinVal->AsFloat = Val1;
         QListTagsMaxVal->AsFloat = Val2;
        }
       QListTags->Post();
       analiz(QListTagsIDTag->AsInteger,Val,Status,QListTagsTypeArhiv->AsInteger,QListTagsUslWrite->AsInteger,QListTagsUslAvar->AsInteger);

      }
     Arhiv->SetData(QListTagsIDTag->AsInteger,Val,Status);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::analiz(int IDTag,double Value,int Status,int TypeArhiv,int Usl, int UslAvar)
{
 // анализ необходимости записи в архив
 // IDTag     - ID тэга
 // Value     - значение
 // Status    - статус
 // TypeArhiv - тип архива
 // Usl       - условия записи в архив 0 - по изменению, 1 по достижению значения
 bool wr=false;
 bool av=false;
 double FaktVal;
 TDateTime tmp = Now();
 switch (TypeArhiv)
  {
   case 1 : // Архив событий
            switch (Usl)
             {
              case 0: // запись по изменению
                      switch (UslAvar)
                       {
                        case  2: // значение 0 - является аварийным
                                 av = Value==0;
                                 break;
                        case  3: // значение 0 - является аварийным или отсутствие связи (Status) является аварийным
                                 av = (Value==0); /* || (Status==0); */ wr=true;
                                 break;
                        case  4: // значение 1 - является аварийным
                                 av = Value==1;
                                 break;
                        case  5: // значение не является аварийным
                        case  7:
                        case 10:
                                 av=false;
                                 break;
                        case  6: // значение аварийное, если == 1 или 2
                                 av = (Value==1) || (Value==2); wr=true;
                                 break;
                        case  8: // значение аварийное, если != 0
                                 av = (Value!=0);
                                 break;
                        case  9: av = (Value==1) || (Value==2) || (Value==5) || (Value==10) || (Value==14) || (Value==15) || (Value>=16);
                                 break;
                       }
                      if (!Status) wr=true;
                      FaktVal = Value;
                      break;
              case 3: // контроль загрузки
                      if (!Status) Value=2;
                      switch (UslAvar)
                       {
                        case  2: // значение 0 - является аварийным
                                 av = Value==0;
                                 break;
                        case  3: // значение 0 - является аварийным или отсутствие связи (Status) является аварийным
                                 av = (Value==0) || (Status==0); wr=true;
                                 break;
                        case  4: // значение 1 - является аварийным
                                 av = Value==1;
                                 break;
                        case  5: // значение не является аварийным
                        case  7:
                        case 10:
                                 av=false;
                                 break;
                        case  6: // значение аварийное, если == 1 или 2
                                 av = (Value==1) || (Value==2); wr=true;
                                 break;
                        case  8: // значение аварийное, если != 0
                                 av = (Value!=0);
                                 break;
                        case  9: av = (Value==1) ||(Value==2) || (Value==10) || (Value==5) || (Value==14) || (Value==15) || (Value>=16);
                                 break;
                       }
                      if (!Status) wr=true;
                      FaktVal = Value;
                      break;
             }
            if (wr)
             {
              // снять значек активности с предыдущего значения
              TLocateOptions SearchOptions;
              Variant locval[] = { IDTag, true };
              bool stop=false;
              if (QArhivSob->Locate("IDTag;Active",VarArrayOf(locval,1),SearchOptions<<loPartialKey<<loCaseInsensitive))
               {
                if (QArhivSobVal->AsInteger!=FaktVal)
                 {
                  QArhivSob->Edit();
                  QArhivSobActive->AsBoolean   = false;
                  QArhivSobKvitirov->AsBoolean = false;
                  QArhivSobActive1->AsBoolean  = false;
                  try
                   {
                    QArhivSobDlit->AsDateTime = Now() - QArhivSobDTSob->AsDateTime;
                   }
                  catch (...) { QArhivSobDlit->AsString=""; }
                  QArhivSob->Post()                   ;
                 }
                else stop=true;
               }
              else
               {
                if (QArhivSob->Locate("IDTag;Active1",VarArrayOf(locval,1),SearchOptions<<loPartialKey<<loCaseInsensitive))
                 {
                  if (QArhivSobVal->AsInteger!=FaktVal)
                   {
                    QArhivSob->Edit();
                    QArhivSobActive->AsBoolean   = false;
                    QArhivSobKvitirov->AsBoolean = false;
                    QArhivSobActive1->AsBoolean  = false;
                    try
                     {
                      QArhivSobDlit->AsDateTime = Now() - QArhivSobDTSob->AsDateTime;
                     }
                    catch (...) { QArhivSobDlit->AsString=""; }
                    QArhivSob->Post()                   ;
                   }
                  else stop=true;
                 }
               }
              if (!stop)
               {
                if (QArhivSob->Locate("IDSob",TekIDSob,TLocateOptions())) QArhivSob->Edit();
                else                                                      QArhivSob->Insert();
                QArhivSobIDSob->AsInteger    = TekIDSob;
                QArhivSobDTSob->AsDateTime   = tmp     ;
                QArhivSobIDTag->AsInteger    = IDTag   ;
                QArhivSobVal->AsInteger      = FaktVal ;
                QArhivSobActive->AsBoolean   = av      ;
                QArhivSobKvitirov->AsBoolean = av      ;
                QArhivSobActive1->AsBoolean  = true    ;
                QArhivSobDlit->AsString      = ""      ;
                if (av) // сигнал является аварийным, посылка сообщения
                 PostMessage(FindWindow("TFMainForm","ОАО \"ВИММ-БИЛЬ-ДАНН\". Программа диспетчерезации котла."),WM_USER+4,1,1);
                QArhivSob->Post();
                TekIDSob++;
               }
             }
            break;
  }

}
//---------------------------------------------------------------------------
void __fastcall TFOpros::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
 unsigned char Buf2[1024];
 int           i=0;
 i=Socket->ReceiveBuf(&Buf2[0],256);
 if (i==109)
  {
   if ((Buf2[6]==0x01)&&(Buf2[7]==0x03))
    {
     union
      {
       char c[2];
       short int i;
      } v;
     for (int i=0;i<50;i++)
      {
       v.c[0]=Buf2[10+i*2];
       v.c[1]=Buf2[9 +i*2];
       DataUstr[i] = v.i  ;
      }
    }
  }
 else if (i==15) // не пять 5, а 7 + переделать в программе опроса
  {
    if ((Buf2[6]==0x01)&&(Buf2[7]==0x01))
     {
      for (int pc=0;pc<7;pc++)
       {
        int k=1;
        for (int pc1=0;pc1<8;pc1++)
         {
          if (((pc*8+pc1)>=0)&&((pc*8+pc1)<50))
           if ((Buf2[9+pc]&k)==k) StatusUstr[pc*8+pc1]=1; else StatusUstr[pc*8+pc1]=0;
          k=k*2;
         }
       }
     }
  }
  i=0;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 Link_Kotel3 = true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Connecting(TObject *Sender,
      TCustomWinSocket *Socket)
{
  int i=0;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Disconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 int i=0;        
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 int i=0;
 switch (ErrorEvent)
  {
   case eeGeneral    : // неизвестная ошибка
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeSend       : // произошла ошибка при попытки записи в сокет-соединение
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeReceive    : // ошибка при попытки чтения из сокет-соединения
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeConnect    : // запрос на соединение не может быть завершён
                       Link_Kotel3 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // произошла ошибка при попытке закрыть соединение
                       Link_Kotel3 = false;ErrorCode=0;
                       break;
   case eeAccept     : // произошла ошибка при попытке принять подключение клиента
                       Link_Kotel3 = false;ErrorCode=0;break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Lookup(TObject *Sender,
      TCustomWinSocket *Socket)
{
 int i=0;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket1Write(TObject *Sender,
      TCustomWinSocket *Socket)
{
 int i=0;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket2Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 Link_OBSK = true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket2Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 switch (ErrorEvent)
  {
   case eeGeneral    : // неизвестная ошибка
                       Link_OBSK = false;ErrorCode=0;break;
   case eeSend       : // произошла ошибка при попытки записи в сокет-соединение
                       Link_OBSK = false;ErrorCode=0;break;
   case eeReceive    : // ошибка при попытки чтения из сокет-соединения
                       Link_OBSK = false;ErrorCode=0;break;
   case eeConnect    : // запрос на соединение не может быть завершён
                       Link_OBSK = false;ErrorCode=0;
                       break;
   case eeDisconnect : // произошла ошибка при попытке закрыть соединение
                       Link_OBSK = false;ErrorCode=0;
                       break;
   case eeAccept     : // произошла ошибка при попытке принять подключение клиента
                       Link_OBSK = false;ErrorCode=0;break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::ClientSocket2Read(TObject *Sender,   TCustomWinSocket *Socket)
{
 unsigned char Buf2[1024];
 int           i=0;
 union
  {
   unsigned long l;
   float         f;
  } tmp;
 i=Socket->ReceiveBuf(&Buf2[0],256);
 if (i>0)
  {
   if ((Buf2[6]==0x01)&&(Buf2[7]==0x03))
    {
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForOBSK>=0)) // чтение 104 регистра
      {
       union
        {
         char c[4];
         float f;
        } v;
       int sm=NumParam_ForOBSK;
       for (int i=0;i<52;i++)
        {
         if ((sm+i)==160)
          {
           int k=0;
          }
         v.c[1]= Buf2[ 9+i*4];
         v.c[0]= Buf2[10+i*4];
         v.c[3]= Buf2[11+i*4];
         v.c[2]= Buf2[12+i*4];
         DataFlUstr[sm+i]=v.f;
        }
       // заполнение структуры регулятора
/*       RegInfo[0].Val[0]=RegFl[320];
       RegInfo[0].Val[1]=RegFl[322];
       RegInfo[0].Val[2]=RegFl[324];
       RegInfo[0].Val[3]=RegFl[326];
       RegInfo[0].Val[4]=RegFl[328];
       RegInfo[0].Val[5]=RegFl[330];
       RegInfo[0].Val[6]=RegFl[332];
       RegInfo[0].Val[7]=RegFl[334];
       RegInfo[0].Val[8]=RegFl[336]; */
      }
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x01))
    {
      {
       union
        {
         char c[2];
         short int i;
        } v;
       if ((i==73) &&(NumParam_ForOBSK==-2))
        {
         for (int i=0;i<64;i++)  DataBitUstr[i] = Buf2[9 +i];
        }
      }
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x10))
    {
     WrVal[WrIndexBuf]=false;WrIndexBuf--;if (WrIndexBuf<0) WrIndexBuf=0;
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x05))
    {
     WrVal[WrIndexBuf]=false;WrIndexBuf--;if (WrIndexBuf<0) WrIndexBuf=0;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteTag_DE1(int Adress, int TypeValue, double value)
{
 // Передать по TCP/IP  (sizeof int)4 байта + (sizeof int)4 байта + (sizeof double)8 байт
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // передача вещественного значения
                    if (Adress>=0)
                     {
                      if (WrVal_DE1[WrIndexBuf_DE1]) { WrIndexBuf_DE1++;if (WrIndexBuf_DE1>=50) WrIndexBuf_DE1=49; }
                      WrVal_DE1[WrIndexBuf_DE1]       = true;
                      WriteAdress_DE1[WrIndexBuf_DE1] = Adress;
                      WriteVal_DE1[WrIndexBuf_DE1]    = (float)tmp.f/100.0;
                      RegFl_DE1[Adress]               = (float)tmp.f/100.0;
                      WrNumZap_DE1[WrIndexBuf_DE1]    = 100   ;
                     }
                    break;
    case TYPEBIT:   // запись одного бита
                    if (Adress>=0)
                     {
                      if (WrVal_DE1[WrIndexBuf_DE1]) { WrIndexBuf_DE1++;if (WrIndexBuf_DE1>=50) WrIndexBuf_DE1=49; }
                      WrVal_DE1[WrIndexBuf_DE1]       = true;
                      RegFl_DE1[Adress]               = value ;
                      WriteAdress_DE1[WrIndexBuf_DE1] = Adress;
                      WriteVal_DE1[WrIndexBuf_DE1]    = value ;
                      WrNumZap_DE1[WrIndexBuf_DE1]    = 101   ;
                     }
                    break;
   }
/* if (ClientXP->Active)
  {
   switch (TypeValue)
    {
     case TYPEFLOAT: //
                     break;
    } */
//   if (debug_message==1)
/*    {
     AnsiString Text="Передача значения для тэга + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"Отладка!",MB_OK);
    } */
//  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteTag_DE2(int Adress, int TypeValue, double value)
{
 // Передать по TCP/IP  (sizeof int)4 байта + (sizeof int)4 байта + (sizeof double)8 байт
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // передача вещественного значения
                    if (Adress>=0)
                     {
                      if (WrVal_DE2[WrIndexBuf_DE2]) { WrIndexBuf_DE2++;if (WrIndexBuf_DE2>=50) WrIndexBuf_DE2=49; }
                      WrVal_DE2[WrIndexBuf_DE2]       = true;
                      WriteAdress_DE2[WrIndexBuf_DE2] = Adress;
                      WriteVal_DE2[WrIndexBuf_DE2]    = (float)tmp.f/100.0;
                      RegFl_DE2[Adress]               = (float)tmp.f/100.0;
                      WrNumZap_DE2[WrIndexBuf_DE2]    = 100   ;
                     }
                    break;
    case TYPEBIT:   // запись одного бита
                    if (Adress>=0)
                     {
                      if (WrVal_DE2[WrIndexBuf_DE2]) { WrIndexBuf_DE2++;if (WrIndexBuf_DE2>=50) WrIndexBuf_DE2=49; }
                      WrVal_DE2[WrIndexBuf_DE2]       = true;
                      RegFl_DE2[Adress]               = value ;
                      WriteAdress_DE2[WrIndexBuf_DE2] = Adress;
                      WriteVal_DE2[WrIndexBuf_DE2]    = value ;
                      WrNumZap_DE2[WrIndexBuf_DE2]    = 101   ;
                     }
                    break;
   }
/* if (ClientXP->Active)
  {
   switch (TypeValue)
    {
     case TYPEFLOAT: //
                     break;
    } */
//   if (debug_message==1)
/*    {
     AnsiString Text="Передача значения для тэга + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"Отладка!",MB_OK);
    } */
//  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteTag(int Adress, int TypeValue, double value)
{
 // Передать по TCP/IP  (sizeof int)4 байта + (sizeof int)4 байта + (sizeof double)8 байт
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // передача вещественного значения
                    if (Adress>=0)
                     {
                      if (WrVal[WrIndexBuf]) { WrIndexBuf++;if (WrIndexBuf>=50) WrIndexBuf=49; }
                      WrVal[WrIndexBuf]       = true;
                      WriteAdress[WrIndexBuf] = Adress;
                      WriteVal[WrIndexBuf]    = tmp.f ;
                      RegFl[Adress]           = tmp.f ;
                      WrNumZap[WrIndexBuf]    = 100   ;
                     }
                    break;
    case TYPEBIT:   // запись одного бита
                    if (Adress>=0)
                     {
                      if (WrVal[WrIndexBuf]) { WrIndexBuf++;if (WrIndexBuf>=50) WrIndexBuf=49; }
                      WrVal[WrIndexBuf]       = true;
                      Reg[Adress]             = value ;
                      WriteAdress[WrIndexBuf] = Adress;
                      WriteVal[WrIndexBuf]    = value ;
                      WrNumZap[WrIndexBuf]    = 101   ;
                     }
                    break;
   }
/* if (ClientXP->Active)
  {
   switch (TypeValue)
    {
     case TYPEFLOAT: //
                     break;
    } */
//   if (debug_message==1)
/*    {
     AnsiString Text="Передача значения для тэга + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"Отладка!",MB_OK);
    } */
//  }
 return;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetAdress_DE1(int IDTag)
{
 int NumBit=-1;
 return FFullGetAdress_DE1(IDTag,&NumBit);
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetAdress_DE2(int IDTag)
{
 int NumBit=-1;
 return FFullGetAdress_DE2(IDTag,&NumBit);
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FFullGetAdress_DE1(int IDTag,int *NumBit)
{
 // адрес по ID тэга
 int ret=0;
 TmpWrFun = 0;
 *NumBit=0;
 switch (IDTag)
  {
   case 1023:  // Режим управления задвижкой газа
   case 1024:  // Режим управления задвижкой воздуходувки
   case 1025:  // Режим управления задвижкой дымососом
   case 1026:  // Режим управления задвижкой воды
   case 1084:  // включение/отключение блокировок
   case 1085:  // включение/отключение блокировок
   case 1086:  // включение/отключение блокировок
   case 1087:  // включение/отключение блокировок
   case 1088:  // включение/отключение блокировок
   case 1089:  // включение/отключение блокировок
   case 1090:  // включение/отключение блокировок
   case 1091:  // включение/отключение блокировок
   case 1092:  // включение/отключение блокировок
   case 1093:  // включение/отключение блокировок
   case 1094:  // включение/отключение блокировок
   case 1095:  // включение/отключение блокировок
   case 1096:  // включение/отключение блокировок
   case 1097:  // включение/отключение блокировок
   case 1098:  // включение/отключение блокировок
   case 1099:  // включение/отключение блокировок
   case 1100:  // включение/отключение блокировок
   case 1101:  // включение/отключение блокировок
   case 1102:  // включение/отключение блокировок
   case 1103:  // включение/отключение блокировок
   case 1104:  // включение/отключение блокировок
   case 1105:  // включение/отключение блокировок
   case 1106:  // включение/отключение блокировок
   case 1107:  // включение/отключение блокировок
   case 1108:  // включение/отключение блокировок
   case 1109:  // включение/отключение блокировок
   case 1110:  // включение/отключение блокировок
   case 1111:  // включение/отключение блокировок
   case 1112:  // включение/отключение блокировок
   case 1113:  // включение/отключение блокировок
   case 1114:  // включение/отключение блокировок
   case 1115:  // включение/отключение блокировок
   case 1116:  // включение/отключение блокировок
   case 1117:  // включение/отключение блокировок
   case 1118:  // включение/отключение блокировок
   case 1119:  // включение/отключение блокировок
   case 1120:  // Задержки блокировки
   case 1121:  // Задержки блокировки
   case 1122:  // Задержки блокировки
   case 1123:  // Задержки блокировки
   case 1124:  // Задержки блокировки
   case 1125:  // Задержки блокировки
   case 1126:  // Задержки блокировки
   case 1127:  // Задержки блокировки
   case 1128:  // Задержки блокировки
   case 1129:  // Задержки блокировки
   case 1130:  // Задержки блокировки
   case 1131:  // Задержки блокировки
   case 1132:  // Задержки блокировки
   case 1133:  // Задержки блокировки
   case 1134:  // Задержки блокировки
   case 1135:  // Задержки блокировки
   case 1136:  // Задержки блокировки
   case 1137:  // Задержки блокировки
   case 1138:  // Задержки блокировки
   case 1139:  // Задержки блокировки
   case 1140:  // Задержки блокировки
   case 1141:  // Задержки блокировки
   case 1142:  // Задержки блокировки
   case 1143:  // Задержки блокировки
   case 1144:  // Задержки блокировки
   case 1145:  // Задержки блокировки
   case 1146:  // Задержки блокировки
   case 1147:  // Задержки блокировки
   case 1148:  // Задержки блокировки
   case 1149:  // Задержки блокировки
   case 1150:  // Задержки блокировки
   case 1151:  // Задержки блокировки
   case 1152:  // Задержки блокировки
   case 1153:  // Задержки блокировки
   case 1154:  // Задержки блокировки
   case 1155:  // Задержки блокировки
   case 1156:  // Задание пара
   case 1157:  // Время фильтра
   case 1158:  // дх
   case 1159:  // кп
   case 1160:  // ки
   case 1161:  // кд
   case 1162:  // тм
   case 1163:  // тимп
   case 1164:  // Задание воздуха
   case 1165:  // Время фильтра
   case 1166:  // дх
   case 1167:  // кп
   case 1168:  // ки
   case 1169:  // кд
   case 1170:  // тм
   case 1171:  // тимп
   case 1172:  // Задание разрежение
   case 1173:  // Время фильтра
   case 1174:  // дх
   case 1175:  // кп
   case 1176:  // ки
   case 1177:  // кд
   case 1178:  // тм
   case 1179:  // тимп
   case 1180:  // Задание уровня воды
   case 1181:  // Время фильтра
   case 1182:  // дх
   case 1183:  // кп
   case 1184:  // ки
   case 1185:  // кд
   case 1186:  // тм
   case 1187:  // тимп
               ret = IDTag - 1000;
               break;
  }
 return ret;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FFullGetAdress_DE2(int IDTag,int *NumBit)
{
 // адрес по ID тэга
 int ret=0;
 TmpWrFun = 0;
 *NumBit=0;
 switch (IDTag)
  {
   case 1323:  // Режим управления задвижкой газа
   case 1324:  // Режим управления задвижкой воздуходувки
   case 1325:  // Режим управления задвижкой дымососом
   case 1326:  // Режим управления задвижкой воды
   case 1384:  // включение/отключение блокировок
   case 1385:  // включение/отключение блокировок
   case 1386:  // включение/отключение блокировок
   case 1387:  // включение/отключение блокировок
   case 1388:  // включение/отключение блокировок
   case 1389:  // включение/отключение блокировок
   case 1390:  // включение/отключение блокировок
   case 1391:  // включение/отключение блокировок
   case 1392:  // включение/отключение блокировок
   case 1393:  // включение/отключение блокировок
   case 1394:  // включение/отключение блокировок
   case 1395:  // включение/отключение блокировок
   case 1396:  // включение/отключение блокировок
   case 1397:  // включение/отключение блокировок
   case 1398:  // включение/отключение блокировок
   case 1399:  // включение/отключение блокировок
   case 1400:  // включение/отключение блокировок
   case 1401:  // включение/отключение блокировок
   case 1402:  // включение/отключение блокировок
   case 1403:  // включение/отключение блокировок
   case 1404:  // включение/отключение блокировок
   case 1405:  // включение/отключение блокировок
   case 1406:  // включение/отключение блокировок
   case 1407:  // включение/отключение блокировок
   case 1408:  // включение/отключение блокировок
   case 1409:  // включение/отключение блокировок
   case 1410:  // включение/отключение блокировок
   case 1411:  // включение/отключение блокировок
   case 1412:  // включение/отключение блокировок
   case 1413:  // включение/отключение блокировок
   case 1414:  // включение/отключение блокировок
   case 1415:  // включение/отключение блокировок
   case 1416:  // включение/отключение блокировок
   case 1417:  // включение/отключение блокировок
   case 1418:  // включение/отключение блокировок
   case 1419:  // включение/отключение блокировок
   case 1420:  // Задержки блокировки
   case 1421:  // Задержки блокировки
   case 1422:  // Задержки блокировки
   case 1423:  // Задержки блокировки
   case 1424:  // Задержки блокировки
   case 1425:  // Задержки блокировки
   case 1426:  // Задержки блокировки
   case 1427:  // Задержки блокировки
   case 1428:  // Задержки блокировки
   case 1429:  // Задержки блокировки
   case 1430:  // Задержки блокировки
   case 1431:  // Задержки блокировки
   case 1432:  // Задержки блокировки
   case 1433:  // Задержки блокировки
   case 1434:  // Задержки блокировки
   case 1435:  // Задержки блокировки
   case 1436:  // Задержки блокировки
   case 1437:  // Задержки блокировки
   case 1438:  // Задержки блокировки
   case 1439:  // Задержки блокировки
   case 1440:  // Задержки блокировки
   case 1441:  // Задержки блокировки
   case 1442:  // Задержки блокировки
   case 1443:  // Задержки блокировки
   case 1444:  // Задержки блокировки
   case 1445:  // Задержки блокировки
   case 1446:  // Задержки блокировки
   case 1447:  // Задержки блокировки
   case 1448:  // Задержки блокировки
   case 1449:  // Задержки блокировки
   case 1450:  // Задержки блокировки
   case 1451:  // Задержки блокировки
   case 1452:  // Задержки блокировки
   case 1453:  // Задержки блокировки
   case 1454:  // Задержки блокировки
   case 1455:  // Задержки блокировки
   case 1456:  // Задание пара
   case 1457:  // Время фильтра
   case 1458:  // дх
   case 1459:  // кп
   case 1460:  // ки
   case 1461:  // кд
   case 1462:  // тм
   case 1463:  // тимп
   case 1464:  // Задание воздуха
   case 1465:  // Время фильтра
   case 1466:  // дх
   case 1467:  // кп
   case 1468:  // ки
   case 1469:  // кд
   case 1470:  // тм
   case 1471:  // тимп
   case 1472:  // Задание разрежение
   case 1473:  // Время фильтра
   case 1474:  // дх
   case 1475:  // кп
   case 1476:  // ки
   case 1477:  // кд
   case 1478:  // тм
   case 1479:  // тимп
   case 1480:  // Задание уровня воды
   case 1481:  // Время фильтра
   case 1482:  // дх
   case 1483:  // кп
   case 1484:  // ки
   case 1485:  // кд
   case 1486:  // тм
   case 1487:  // тимп
               ret = IDTag - 1300;
               break;
  }
 return ret;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FGetAdress(int IDTag)
{
 int NumBit=-1;
 return FFullGetAdress(IDTag,&NumBit);
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FFullGetAdress(int IDTag, int *NumBit)
{
 // адрес тэга по ID
 int ret=-1;
 *NumBit=-1;
 TmpWrFun = 0;
 switch (IDTag)
  {
   case 100101: ret=  4;*NumBit=-1;break;
   case 200101: ret=  6;*NumBit=-1;break;
   case 100102: ret= 14;*NumBit=-1;break;
   case 200102: ret= 16;*NumBit=-1;break;
   case 100103: ret= 24;*NumBit=-1;break;
   case 200103: ret= 26;*NumBit=-1;break;
   case 100104: ret= 34;*NumBit=-1;break;
   case 200104: ret= 36;*NumBit=-1;break;
   case 100105: ret= 44;*NumBit=-1;break;
   case 200105: ret= 46;*NumBit=-1;break;
   case 100106: ret=114;*NumBit=-1;break;
   case 200106: ret=116;*NumBit=-1;break;
   case 100107: ret=124;*NumBit=-1;break;
   case 200107: ret=126;*NumBit=-1;break;
   case 100109: ret=134;*NumBit=-1;break;
   case 200109: ret=136;*NumBit=-1;break;
   case 100110: ret= 54;*NumBit=-1;break;
   case 200110: ret= 56;*NumBit=-1;break;
   case 100111: ret=144;*NumBit=-1;break;
   case 200111: ret=146;*NumBit=-1;break;
   case 100112: ret= 64;*NumBit=-1;break;
   case 200112: ret= 66;*NumBit=-1;break;
   case 100117: ret= 74;*NumBit=-1;break;
   case 200117: ret= 76;*NumBit=-1;break;
   case 100118: ret= 84;*NumBit=-1;break;
   case 200118: ret= 86;*NumBit=-1;break;
   case 100119: ret= 94;*NumBit=-1;break;
   case 200119: ret= 96;*NumBit=-1;break;
   case 100120: ret=104;*NumBit=-1;break;
   case 200120: ret=106;*NumBit=-1;break;

   case    301: ret=140;*NumBit= 0;break;
   case    302: ret=141;*NumBit= 0;break;
   case    303: ret=144;*NumBit= 0;break;
   case    304: ret=145;*NumBit= 0;break;
   case    305: ret=148;*NumBit= 0;break;
   case    306: ret=149;*NumBit= 0;break;
   case    307: ret=160;*NumBit= 0;break;
   case    308: ret=161;*NumBit= 0;break;
   case    309: ret=162;*NumBit= 0;break;
   case    310: ret=163;*NumBit= 0;break;
   case    311: ret=164;*NumBit= 0;break;
   case    312: ret=165;*NumBit= 0;break;
   case    313: ret=168;*NumBit= 0;break;
   case    314: ret=169;*NumBit= 0;break;
   case    315: ret=172;*NumBit= 0;break;
   case    316: ret=173;*NumBit= 0;break;
   case    317: ret=176;*NumBit= 0;break;
   case    318: ret=177;*NumBit= 0;break;
   case    319: ret=190;*NumBit= 0;break;
   case    320: ret=191;*NumBit= 0;break;
   case    321: ret=192;*NumBit= 0;break;
   case    322: ret=193;*NumBit= 0;break;
   case    323: ret=194;*NumBit= 0;break;
   case    324: ret=195;*NumBit= 0;break;
   case    325: ret=196;*NumBit= 0;break;
   case    326: ret=197;*NumBit= 0;break;
   case    327: ret=199;*NumBit= 0;break;
   case    328: ret=200;*NumBit= 0;break;
   case    329: ret=201;*NumBit= 0;break;
   case    330: ret=202;*NumBit= 0;break;
   case    331: ret=205;*NumBit= 0;break;
   case    332: ret=206;*NumBit= 0;break;
   case    333: ret=209;*NumBit= 0;break;
   case    334: ret=210;*NumBit= 0;break;

   case    344: ret=178;*NumBit= 0;break;
   case    345: ret=198;*NumBit= 0;break;
   case    346: ret=142;*NumBit= 0;break;
   case    347: ret=146;*NumBit= 0;break;
   case    348: ret=150;*NumBit= 0;break;
   case    349: ret=166;*NumBit= 0;break;
   case    350: ret=170;*NumBit= 0;break;
   case    351: ret=174;*NumBit= 0;break;
   case    352: ret=203;*NumBit= 0;break;
   case    353: ret=207;*NumBit= 0;break;
   case    354: ret=211;*NumBit= 0;break;
   case    355: ret= 38;*NumBit= 0;break;
   case    356: ret= 39;*NumBit= 0;break;
   case    357: ret= 40;*NumBit= 0;break;

   case    377: ret=213;*NumBit= 0;break;
   case    378: ret=214;*NumBit= 0;break;

   case    501: ret= 18;*NumBit= 0;break;
   case    502: ret=508;*NumBit=-1;break;
   case    503: ret=290;*NumBit=-1;break;
   case    504: TmpWrFun=1;ret=292;*NumBit=-1;break;
   case    505: ret=294;*NumBit=-1;break;
   case    506: TmpWrFun=1;ret=561;*NumBit=-1;break;
   case    507: TmpWrFun=1;ret=563;*NumBit=-1;break;
   case    508: ret=510;*NumBit=-1;break;
   case    509: ret= 19;*NumBit= 0;break;
   case    510: ret= 20;*NumBit= 0;break;
   case    511: ret= 21;*NumBit= 0;break;

   case    521: ret= 22;*NumBit= 0;break;
   case    522: ret=512;*NumBit=-1;break;
   case    523: ret=330;*NumBit=-1;break;
   case    524: TmpWrFun=1;ret=332;*NumBit=-1;break;
   case    525: ret=334;*NumBit=-1;break;
   case    526: TmpWrFun=1;ret=571;*NumBit=-1;break;
   case    527: TmpWrFun=1;ret=573;*NumBit=-1;break;
   case    528: ret=514;*NumBit=-1;break;
   case    529: ret= 23;*NumBit= 0;break;
   case    530: ret= 24;*NumBit= 0;break;
   case    531: ret= 25;*NumBit= 0;break;

   case    541: ret= 26;*NumBit= 0;break;
   case    542: ret=516;*NumBit=-1;break;
   case    543: ret=370;*NumBit=-1;break;
   case    544: TmpWrFun=1;ret=372;*NumBit=-1;break;
   case    545: ret=374;*NumBit=-1;break;
   case    546: TmpWrFun=1;ret=581;*NumBit=-1;break;
   case    547: TmpWrFun=1;ret=583;*NumBit=-1;break;
   case    548: ret=518;*NumBit=-1;break;
   case    549: ret= 27;*NumBit= 0;break;
   case    550: ret= 28;*NumBit= 0;break;
   case    551: ret= 29;*NumBit= 0;break;

   case    561: ret= 30;*NumBit= 0;break;
   case    562: ret=520;*NumBit=-1;break;
   case    563: ret=410;*NumBit=-1;break;
   case    564: TmpWrFun=1;ret=412;*NumBit=-1;break;
   case    565: ret=414;*NumBit=-1;break;
   case    566: TmpWrFun=1;ret=591;*NumBit=-1;break;
   case    567: TmpWrFun=1;ret=593;*NumBit=-1;break;
   case    568: ret=522;*NumBit=-1;break;
   case    569: ret= 31;*NumBit= 0;break;
   case    570: ret= 32;*NumBit= 0;break;
   case    571: ret= 33;*NumBit= 0;break;

   case    581: ret= 34;*NumBit= 0;break;
   case    582: ret=524;*NumBit=-1;break;
   case    583: ret=450;*NumBit=-1;break;
   case    584: TmpWrFun=1;ret=452;*NumBit=-1;break;
   case    585: ret=454;*NumBit=-1;break;
   case    586: TmpWrFun=1;ret=601;*NumBit=-1;break;
   case    587: TmpWrFun=1;ret=603;*NumBit=-1;break;
   case    588: ret=526;*NumBit=-1;break;
   case    589: ret= 35;*NumBit= 0;break;
   case    590: ret= 36;*NumBit= 0;break;
   case    591: ret= 37;*NumBit= 0;break;

   case    601: ret= 10;*NumBit= 0;break;
   case    602: ret=500;*NumBit=-1;break;
   case    603: ret=210;*NumBit=-1;break;
   case    604: TmpWrFun=1;ret=212;*NumBit=-1;break;
   case    605: ret=214;*NumBit=-1;break;
   case    606: TmpWrFun=1;ret=541;*NumBit=-1;break;
   case    607: TmpWrFun=1;ret=543;*NumBit=-1;break;
   case    608: ret=502;*NumBit=-1;break;
   case    609: ret= 11;*NumBit= 0;break;
   case    610: ret= 12;*NumBit= 0;break;
   case    611: ret= 13;*NumBit= 0;break;

   case    621: ret= 14;*NumBit= 0;break;
   case    622: ret=504;*NumBit=-1;break;
   case    623: ret=250;*NumBit=-1;break;
   case    624: TmpWrFun=1;ret=252;*NumBit=-1;break;
   case    625: ret=254;*NumBit=-1;break;
   case    626: TmpWrFun=1;ret=551;*NumBit=-1;break;
   case    627: TmpWrFun=1;ret=553;*NumBit=-1;break;
   case    628: ret=506;*NumBit=-1;break;
   case    629: ret= 15;*NumBit= 0;break;
   case    630: ret= 16;*NumBit= 0;break;
   case    631: ret= 17;*NumBit= 0;break;

   case    800: ret=424;*NumBit=-1;break;
   case    801: ret=426;*NumBit=-1;break;
   case    802: ret=428;*NumBit=-1;break;
   case    803: ret=640;*NumBit=-1;break;
   case    804: ret=642;*NumBit=-1;break;
   case    805: ret=644;*NumBit=-1;break;
   case    806: ret=646;*NumBit=-1;break;
   case    807: ret=648;*NumBit=-1;break;
   case    808: ret=650;*NumBit=-1;break;
   case    809: ret=652;*NumBit=-1;break;
   case    810: ret=654;*NumBit=-1;break;
   case    811: ret=656;*NumBit=-1;break;
   case    812: ret=658;*NumBit=-1;break;
   case    813: ret=660;*NumBit=-1;break;
   case    814: ret=662;*NumBit=-1;break;
   case    815: ret=664;*NumBit=-1;break;
   case    816: ret=666;*NumBit=-1;break;
   case    817: ret=668;*NumBit=-1;break;
   case    818: ret=670;*NumBit=-1;break;
   case    819: ret=672;*NumBit=-1;break;
   case    820: ret=674;*NumBit=-1;break;
   case    821: ret=676;*NumBit=-1;break;
   case    822: ret=678;*NumBit=-1;break;
   case    823: ret=680;*NumBit=-1;break;
   case    824: ret=682;*NumBit=-1;break;
   case    825: ret=684;*NumBit=-1;break;
   case    826: ret=686;*NumBit=-1;break;
   case    827: ret=688;*NumBit=-1;break;
   case    828: ret=690;*NumBit=-1;break;
   case    829: ret=692;*NumBit=-1;break;
   case    830: ret=694;*NumBit=-1;break;

   case    831: ret=222;*NumBit= 0;break;

  }
 if ((ret%2)!=0) { if (TmpWrFun==1) ret++; }
 return ret;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::OnWriteValue(TMessage& Message)
{
 // запись значения в контроллер
 if (Message.WParam<=1000)
  {
   WriteTag(Adress[Message.WParam],TYPEBIT,Message.LParam);
   WrIDTag[WrIndexBuf] = Message.WParam;
  }
 else if (Message.WParam<=1300)
  {
   WriteTag_DE1(Adress_DE1[Message.WParam],TYPEBIT,StrToFloat(IntToStr(Message.LParam)));
   WrIDTag_DE1[WrIndexBuf] = Message.WParam;
  }
 else if (Message.WParam<=1600)
  {
   WriteTag_DE2(Adress_DE2[Message.WParam],TYPEBIT,StrToFloat(IntToStr(Message.LParam)));
   WrIDTag_DE2[WrIndexBuf] = Message.WParam;
  }
 WriteData();
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::OnWriteFloatValue(TMessage& Message)
{
 // запись вещественного значения в контроллер
 double tmp = (double)Message.LParam/100;
 if (Message.WParam<=1000)
  {
   WriteTag(Adress[Message.WParam],TYPEFLOAT,tmp);
   WrIDTag[WrIndexBuf] = Message.WParam;
  }
 else if (Message.WParam<=1300)
  {
   WriteTag_DE1(Adress_DE1[Message.WParam],TYPEFLOAT,Message.LParam);
   WrIDTag_DE1[WrIndexBuf] = Message.WParam;
  }
 else
  {
   WriteTag_DE2(Adress_DE2[Message.WParam],TYPEFLOAT,StrToFloat(IntToStr(Message.LParam)));
   WrIDTag_DE2[WrIndexBuf] = Message.WParam;
  }
 WriteData();
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket3Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 switch (ErrorEvent)
  {
   case eeGeneral    : // неизвестная ошибка
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeSend       : // произошла ошибка при попытки записи в сокет-соединение
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeReceive    : // ошибка при попытки чтения из сокет-соединения
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeConnect    : // запрос на соединение не может быть завершён
                       Link_Kotel_DE1 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // произошла ошибка при попытке закрыть соединение
                       Link_Kotel_DE1 = false;ErrorCode=0;
                       break;
   case eeAccept     : // произошла ошибка при попытке принять подключение клиента
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::ClientSocket3Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 Link_Kotel_DE1 = true;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::ClientSocket3Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
 unsigned char Buf2[1024];
 int           i=0;
 union
  {
   unsigned long l;
   float         f;
  } tmp;

 i=Socket->ReceiveBuf(&Buf2[0],512);
 if (i>0) // пришли данные
  {

   if (((Buf2[6]==0x01)&&(Buf2[7]==0x03))||
       ((Buf2[6]==0x01)&&(Buf2[7]==0x04)))
    {
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForDE_1>=0)) // чтение 104 регистра
      {
       union
        {
         char c[4];
         float f;
        } v;
       int sm=NumParam_ForDE_1;
       for (int i=0;i<52;i++)
        {
         if ((sm+i)==198)
          {
           int k=0;
          }
         if (Buf2[7]==0x04)
          {
           v.c[1]= Buf2[ 9+i*4];
           v.c[0]= Buf2[10+i*4];
           v.c[3]= Buf2[11+i*4];
           v.c[2]= Buf2[12+i*4];
           DataFlUstr[sm+i+1000]=v.f;
          }
         else
          {
           union
           {
            char c[2];
            short int i;
           } v1;
           v1.c[1]= Buf2[ 9+i*4];
           v1.c[0]= Buf2[10+i*4];
           StatFlUstr[sm+i*2+1000]=v1.i;
           v1.c[1]= Buf2[11+i*4];
           v1.c[0]= Buf2[12+i*4];
           StatFlUstr[sm+i*2+1001]=v1.i;
          }
        }
       // заполнение структуры регулятора
      }
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x01))
    {
/*      {
       union
        {
         char c[2];
         short int i;
        } v;
       if ((i==73) &&(NumParam_ForOBSK==-2))
        {
         for (int i=0;i<64;i++)  DataBitUstr[i] = Buf2[9 +i];
        }
      } */
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x10))
    {
      WrVal_DE1[WrIndexBuf_DE1]=false;WrIndexBuf_DE1--;if (WrIndexBuf_DE1<0) WrIndexBuf_DE1=0;
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x05))
    {
     WrVal_DE1[WrIndexBuf_DE1]=false;WrIndexBuf_DE1--;if (WrIndexBuf_DE1<0) WrIndexBuf_DE1=0;
    }
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket4Connect(TObject *Sender,
      TCustomWinSocket *Socket)
{
 Link_Kotel_DE2 = true;
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket4Error(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
 switch (ErrorEvent)
  {
   case eeGeneral    : // неизвестная ошибка
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeSend       : // произошла ошибка при попытки записи в сокет-соединение
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeReceive    : // ошибка при попытки чтения из сокет-соединения
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeConnect    : // запрос на соединение не может быть завершён
                       Link_Kotel_DE2 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // произошла ошибка при попытке закрыть соединение
                       Link_Kotel_DE2 = false;ErrorCode=0;
                       break;
   case eeAccept     : // произошла ошибка при попытке принять подключение клиента
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TFOpros::ClientSocket4Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
 unsigned char Buf2[1024];
 int           i=0;
 union
  {
   unsigned long l;
   float         f;
  } tmp;

 i=Socket->ReceiveBuf(&Buf2[0],512);
 if (i>0) // пришли данные
  {

   if (((Buf2[6]==0x01)&&(Buf2[7]==0x03))||
       ((Buf2[6]==0x01)&&(Buf2[7]==0x04)))
    {
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForDE_2>=0)) // чтение 104 регистра
      {
       union
        {
         char c[4];
         float f;
        } v;
       int sm=NumParam_ForDE_1;
       for (int i=0;i<52;i++)
        {
         if ((sm+i)==198)
          {
           int k=0;
          }
         if (Buf2[7]==0x04)
          {
           v.c[1]= Buf2[ 9+i*4];
           v.c[0]= Buf2[10+i*4];
           v.c[3]= Buf2[11+i*4];
           v.c[2]= Buf2[12+i*4];
           DataFlUstr[sm+i+1300]=v.f;
          }
         else
          {
           union
           {
            char c[2];
            short int i;
           } v1;
           v1.c[1]= Buf2[ 9+i*4];
           v1.c[0]= Buf2[10+i*4];
           StatFlUstr[sm+i*2+1300]=v1.i;
           v1.c[1]= Buf2[11+i*4];
           v1.c[0]= Buf2[12+i*4];
           StatFlUstr[sm+i*2+1301]=v1.i;
          }
        }
       // заполнение структуры регулятора
      }
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x01))
    {
/*      {
       union
        {
         char c[2];
         short int i;
        } v;
       if ((i==73) &&(NumParam_ForOBSK==-2))
        {
         for (int i=0;i<64;i++)  DataBitUstr[i] = Buf2[9 +i];
        }
      } */
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x10))
    {
      WrVal_DE2[WrIndexBuf_DE2]=false;WrIndexBuf_DE2--;if (WrIndexBuf_DE2<0) WrIndexBuf_DE2=0;
    }
   else if ((Buf2[6]==0x01)&&(Buf2[7]==0x05))
    {
     WrVal_DE2[WrIndexBuf_DE2]=false;WrIndexBuf_DE2--;if (WrIndexBuf_DE2<0) WrIndexBuf_DE2=0;
    }
  }
}
//---------------------------------------------------------------------------

