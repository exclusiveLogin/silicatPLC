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
 // ������ ������������� �����
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
//       count_cikl_time_out_modbus = Ini->ReadInteger("TIMERS","TimeOutModbus",0)              ; // �������� �� �������� ������ �� Modbus ���������
       Lic                        = Ini->ReadInteger("USER","Lic",1000)                       ;
       ModeApp                    = Ini->ReadInteger("DISK","Mode",0)                         ;
//      }
//     else Application->MessageBoxA("�� ��������� ������ ����!","��������!",MB_OK+MB_ICONSTOP);
     delete Ini;
    }
   else throw Exception("����������� ������������ ���� Opros.Ini");
  }
 else throw Exception("����������� ������������ ���� Opros.Ini");
 if (!ModeApp)
  {
   FOpros->Visible=false;Application->ShowMainForm=false;
  }
 // ���������� ID ��������� ������ � ������
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
// ����������� ���� �� ��
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
   if (!ReadFile(ComPort, (buffer+Index), 1, &BytesRead, NULL)) // �������� ������
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
 // �������� ������ � ����
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
 // ������� ������� �� MODBUS ���������
 unsigned char command[80]; // ������� �� Modbus
 unsigned char ansver[255]; // �����   �� Modbus
 int           bytz = 6   ; // ���������� ���� � �������
 union
  {
   unsigned char c[2];
   short int     val ;
  } tmpint;
 if (Port_Modbus==NULL) Port_Modbus = OpenPort(NumPortModbus,NULL); // �������� �����
 if (Port_Modbus!=NULL)
  {
   command[ 0] = AdressUstr; // ����� ����������
   command[ 1] = 0x03      ; // ������� ������
   switch (NumParam)
    {
     case 0:  // ����� ������ 10-�� ��������� - 20 ���� 0..9
              command[2] = 0x00;
              command[3] = 0x00; // ������� � �������� ������
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 1:  // ����� ������ 10-�� ��������� - 20 ����
              command[2] = 0x00;
              command[3] = 0x0A; // ������� � 10 ������
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 2:  // ����� ������ 10-�� ��������� - 20 ����
              command[2] = 0x00;
              command[3] = 0x14; // ������� � 20 ������
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 3:  // ����� ������ 10-�� ��������� - 20 ����
              command[2] = 0x00;
              command[3] = 0x1E; // ������� � 30 ������
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 4:  // ����� ������ 10-�� ��������� - 20 ����
              command[2] = 0x00;
              command[3] = 0x28; // ������� � 40 ������
              command[4] = 0x00;
              command[5] = 0x14;
              break;
     case 5: // ������ �������
              command[1] = 0x06;
              command[2] = 0x00;
              command[3] = 0x2F; // ����� ������� ���������� 2C 2F 30
              tmpint.val =  102;
              command[4] = tmpint.c[1];
              command[5] = tmpint.c[0];
              break;
     case 6: // ������������ � ����� ��������� ��������� �������
              command[1] = 0x06;
              command[2] = 0x00;
              command[3] = 0x2B; // ����� ������� ����������
              tmpint.val =    1;
              command[4] = tmpint.c[1];
              command[5] = tmpint.c[0];
              break;
     default: return false;
    }
   WORD tt=Crc16(command,bytz);
   command[bytz]  = (BYTE) tt    ;
   command[bytz+1]= (BYTE)(tt>>8);
   if (!WriteDataCom(Port_Modbus, command, bytz+2)) // �������� �������
    { Port_Modbus = OpenPort(NumPortModbus,Port_Modbus);return false; } // ������� ���� � ������ ������
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
 buf[9] = 0; // ����� == 0
 buf[10]= 0;
 buf[11]=50; // ���������� ���������� ��� ���������� ������
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
 // ������� ������ ��� ��-1 (���� �3)
 // - �������� 03
 // 0 - ����� MW0   .. MW103     0.. 51
 // 1 - ����� WM104 .. MW207    52..103
 // 2 - ����� MW208 .. MW311   104..155
 // 3 - ����� MW312 .. MW415   156..207
 // - ������ �������� 04
 // 4 - ����� MW0   .. MW103     0.. 103
 // 5 - ����� WM104 .. MW207   104.. 207
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
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0x68; // �������� ����� == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0xD0; // �������� ����� == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    =104 ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x01;buf[9] =0x38; // �������� ����� == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    =156 ;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    =   0;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x68; // �������� ����� == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_1    = 104;
           break;
   case 101:
   case 100: // ������ ������������� ��������
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// ������� ������
             tmp1.i = WriteAdress_DE1[WrIndexBuf_DE1];
             buf[8] = tmp1.c[1];     // �������� ����� == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 ����� == 0x68
             buf[12]=0x04; // ���������� ����
             // ��������
             tmp.f   = WriteVal_DE1[WrIndexBuf_DE1];
             buf[13] = tmp.c[1];
             buf[14] = tmp.c[0];
             buf[15] = tmp.c[3];
             buf[16] = tmp.c[2];
            // tmp_str = "�������� ��������� �� ������ " + IntToStr(tmp1.i) + " �������� = " + FloatToStr(tmp.f);
            // Application->MessageBoxA(tmp_str.c_str(),"��������!",MB_OK+MB_ICONSTOP);
             len_com=17;
             break;
   default : len_com=17;NumParam_ForDE_1=-1;break;
  }
 ClientSocket3->Socket->SendBuf(buf,len_com);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForDE_2(int NumCom)
{
 // ������� ������ ��� ��-2 (���� �4)
 // - �������� 03
 // 0 - ����� MW0   .. MW103     0.. 51
 // 1 - ����� WM104 .. MW207    52..103
 // 2 - ����� MW208 .. MW311   104..155
 // 3 - ����� MW312 .. MW415   156..207
 // - ������ �������� 04
 // 4 - ����� MW0   .. MW103     0.. 103
 // 5 - ����� WM104 .. MW207   104.. 207
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
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0x68; // �������� ����� == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x00;buf[9] =0xD0; // �������� ����� == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    =104 ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x04; // ������� ������
           buf[8] =0x01;buf[9] =0x38; // �������� ����� == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    =156 ;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    =   0;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x68; // �������� ����� == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForDE_2    = 104;
           break;
   case 101:
   case 100: // ������ ������������� ��������
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// ������� ������
             tmp1.i = WriteAdress_DE2[WrIndexBuf_DE2];
             buf[8] = tmp1.c[1];     // �������� ����� == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 ����� == 0x68
             buf[12]=0x04; // ���������� ����
             // ��������
             tmp.f   = WriteVal_DE2[WrIndexBuf_DE2];
             buf[13] = tmp.c[1];
             buf[14] = tmp.c[0];
             buf[15] = tmp.c[3];
             buf[16] = tmp.c[2];
            // tmp_str = "�������� ��������� �� ������ " + IntToStr(tmp1.i) + " �������� = " + FloatToStr(tmp.f);
            // Application->MessageBoxA(tmp_str.c_str(),"��������!",MB_OK+MB_ICONSTOP);
             len_com=17;
             break;
   default : len_com=17;NumParam_ForDE_2=-1;break;
  }
 ClientSocket4->Socket->SendBuf(buf,len_com);
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::SendCommandForObsK(int NumCom)
{
 // ������� ������
 // 0 - ����� MW0  .. MW103                         +0     0.. 103   0
 // 1 - ����� MW104.. MW207                         +1   104.. 207   52
 // 2 - ����� MW416.. MW519                         +8   208.. 311   104
 // 3 - ����� MW520.. MW523                         +9   312.. 415   156
 // 4 - ����� MW832.. MW935                         +2   416.. 519   208
 // 5 - ����� M0   ..                               +3   520.. 523   260
 //                                                 +10  624.. 727   312
 // 6 - ����� MW936.. MW1039                        +7   728.. 831   364
 // 7 - ����� MW728.. MW831                         +4   832.. 935   416
 // 8 - ����� MW208.. MW311                         +6   936..1039   468
 // 9 - ����� MW312.. MW415
 // 10- ����� MW624.. MW727
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
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 00 ~ 0x0000
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =   0;
           break;
   case 1: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0x68; // �������� ����� == 104 ~ 0x0064
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =  52;
           break;
   case 2: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x01;buf[9] =0xA0; // �������� ����� == 416 ~ 0x01A0
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    = 208; // 52  ;
           break;
   case 3: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x02;buf[9] =0x08; // �������� ����� == 208 ~ 0x0208
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    = 260;
           break;
   case 4: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x03;buf[9] =0x40; // �������� ����� == 832 ~ 0x0340
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    = 416;
           break;
   case 5: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x01; // ������� ������
           buf[8] =0x00;buf[9] =0x00; // �������� ����� == 0 ~ 0x0000
           buf[10]=0x02;buf[11]=0x00; // ����� ��� 1024 0x400  1024/8 = 128 ���� = 64 �����
           NumParam_ForOBSK    =  -2;
           break;
   case 6: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x03;buf[9] =0xA8; // �������� ����� == 936 ~ 0x03A8
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =468 ;
           break;
   case 7: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x02;buf[9] =0xD8; // �������� ����� == 728 ~ 0x02D8
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =364 ;
           break;
   case 8: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x00;buf[9] =0xD0; // �������� ����� == 208 ~ 0x00D0
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =104 ;
           break;
   case 9: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x01;buf[9] =0x38; // �������� ����� == 312 ~ 0x0138
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =156 ;
           break;
   case 10: buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
           buf[7] =0x03; // ������� ������
           buf[8] =0x02;buf[9] =0x70; // �������� ����� == 624 ~ 0x0270
           buf[10]=0x00;buf[11]=0x68; // 104 ����� == 0x68
           NumParam_ForOBSK    =312 ;
           break;
   case 101: // ������ ������ ����
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x06;buf[6]=0x01;
             buf[7] =0x05;// ������� ������ ������ ����
             tmp1.i = WriteAdress[WrIndexBuf];
             buf[8] = tmp1.c[1];     // �������� �����
             buf[9] = tmp1.c[0];
             if (WriteVal[WrIndexBuf]==1) buf[10]=0xFF;
             else                         buf[10]=0x00;
             buf[11]=0x00;
             len_com=12;
             break;
   case 100: // ������ ������������� ��������
             buf[0] =0x00;buf[1]=0x00;buf[2]=0x00;buf[3]=0x00;buf[4]=0x00;buf[5]=0x0B;buf[6]=0x01;
             buf[7] =0x10;// ������� ������
             tmp1.i = WriteAdress[WrIndexBuf];
             buf[8] = tmp1.c[1];     // �������� ����� == 312 ~ 0x0138
             buf[9] = tmp1.c[0];
             buf[10]=0x00;buf[11]=0x02; // 2 ����� == 0x68
             buf[12]=0x04; // ���������� ����
             // ��������
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
   case 0: buf[7] =0x10; // ������� ������
           buf[8] =0x00;
           buf[9] =0x02; // ��������, ����� == 1
           buf[10]=0x00;
           buf[11]=0x02; // ���������� ����
           buf[12]=0x04; // ���������� ����
           tmp.f = 2500;
           buf[13]=tmp.c[1];
           buf[14]=tmp.c[0]; // ���������� ���������� ��� ���������� ������
           buf[15]=tmp.c[3];
           buf[16]=tmp.c[2]; // ���������� ����
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
 static unsigned int tim_out_obsk=0 ; // ����-��� ��� ������������� ����������. ����� ��������� � ������� ���������� ����������
 static unsigned int tim_out_zobsk=0; // ����-��� ��� ������������� ����������. ����� ��������� � ������� ���������� �������
 static unsigned int num_zap_obsk=0 ; // ����� ������� ��� ������������ ����������
 static unsigned int tim_out_kde_1 = 0;
 static unsigned int tim_out_zkde_1= 0;
 static unsigned int num_zap_kde_1 = 0;
 static unsigned int tim_out_kde_2 = 0;
 static unsigned int tim_out_zkde_2= 0;
 static unsigned int num_zap_kde_2 = 0;
 static int cc=0;
 unsigned int count_zap_obsk  = 11   ; // ���������� (�����) �������� � ������������� ����������
 unsigned int count_zap_kde_1 =  6   ; // ���������� (�����  �������� � ����� �� - �1 (���� �3)
 unsigned int count_zap_kde_2 =  6   ; // ���������� (�����  �������� � ����� �� - �2 (���� �4)
  // ����� ����������
 Timer1->Enabled=false;
 // ����� ��� � �������
 try
  {
   // ����� ���������� ������������� ����������
   if (ClientSocket2->Socket!=NULL)
    if (ClientSocket2->Socket->Connected) // ���������� �����������
     {
      tim_out_zobsk++;
      if ((tim_out_obsk%const_tim_out_obsk)==1) // ������������� ������
       {
        bool byl=false;
        if (WrVal[WrIndexBuf]) // ������������� ������ ��������
         SendCommandForObsK(WrNumZap[WrIndexBuf]);
        else
         SendCommandForObsK(num_zap_obsk);
        num_zap_obsk++;
        if (num_zap_obsk==count_zap_obsk) num_zap_obsk=0;
       }
      if (tim_out_zobsk==const_tim_out_obsk) { tim_out_zobsk=0;WrVal[WrIndexBuf]=false;WrIndexBuf--;if (WrIndexBuf<0) WrIndexBuf=0; } // ����� ����-���� ��� ���������� ������
     }
    else // ��� ����������
     {
      tim_out_obsk++;                             // ����-��� ���������� ����������
      if ((tim_out_obsk%const_tim_out_obsk)==1)   // ���� ����-��� �������� ����������
       {
        ClientSocket2->Open();                   // ������� ������� ����������
       }
      if (tim_out_obsk==const_tim_out_obsk) tim_out_obsk=0; // ����� ����-���� ��� ���������� ������
     }
    else
     int pc=0;

   if (ClientSocket1->Socket!=NULL)
    if (ClientSocket1->Socket->Connected) // ���������� �����������
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
    else // ��� ����������
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
    if (ClientSocket3->Socket->Connected) // ���������� �����������
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
    else // ��� ����������
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
    if (ClientSocket4->Socket->Connected) // ���������� �����������
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
    else // ��� ����������
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
 // ������ ������ �� Modbus ���������
 unsigned char ansver[255]; // ����� �� Modbus
 unsigned int  len_ansv=0 ; // ����� ������
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
   if ((len_ansv=ReadDataCom(Port_Modbus,ansver,255))>0) // ������ �����
    {
     if (len_ansv==45) // ��� ����� �� modbus ��������� 10 ���������� 20 ����
      {
       if (ansver[0]==AdrUstr) // ��������� ������ ��������� 2 -�����
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
     else { *Error=3; return true; } // �� ����� ������ �����
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
 // ������ ������� ������ � �����
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
       case 1 : // ��������� �������� ����
                Val = (float)DataUstr[2]/10;  Status=StatusUstr[2]; break;
       case 2 : // ��������� �������� �������
                Val = (float)DataUstr[4]/10; Status=StatusUstr[4]; break;
       case 3 : // �������� ����
                Val = (float)DataUstr[12]/10; Status=StatusUstr[12]; break;
       case 4 : // ������� �������� ����
                Val = (float)DataUstr[11]/10; Status=StatusUstr[11]; break;
       case 5 : // ������� �������
                Val = (float)DataUstr[13]/10; Status=StatusUstr[13]; break;
       case 6 : // ���������� �������
                Val = (DataUstr[35]&1)==1; Status=StatusUstr[35]; break;
       case 7 : // ���������� �������
                Val = (DataUstr[35]&2)==1; Status=StatusUstr[35]; break;
       case 8 : // ��� ������� �����
                Val = (DataUstr[35]&4)==4; Status=StatusUstr[35]; break;
       case 9 : // ��� ������� ���
                Val = (DataUstr[35]&8)==8; Status=StatusUstr[35]; break;
       case 10: // ������
                Val = (DataUstr[35]&16)==16; Status=StatusUstr[35]; break;
       case 11: // �������� ������� ������
                Val = (DataUstr[35]&32)==32; Status=StatusUstr[35]; break;
       case 12: // �������� ������� �����
                Val = (DataUstr[35]&64)==64; Status=StatusUstr[35]; break;
       case 13: // �������� �������������
                Val = (DataUstr[35]&128)==128; Status=StatusUstr[35]; break;
       case 14: // ������ ������������
                Val = (DataUstr[35]&256)==256; Status=StatusUstr[35]; break;
       case 15: // ������
                Val = (DataUstr[35]&512)==512; Status=StatusUstr[35]; break;
       case 16: // �������� ���� �����
                Val = (DataUstr[35]&1024)==1024; Status=StatusUstr[35]; break;
       case 17: // �������� ���� ������
                Val = (DataUstr[35]&2048)==2048; Status=StatusUstr[35]; break;
       case 18: // ������
                Val = (DataUstr[35]&4096)==4096; Status=StatusUstr[35]; break;
       case 19: // LP
                Val = (DataUstr[35]&8192)==8192; Status=StatusUstr[35]; break;
       case 20: // ������ �������
                Val = (DataUstr[35]&16384)==16384; Status=StatusUstr[35]; break;
       case 21: // ���������� ������ �������
                Val = (DataUstr[35]&32768)==32768; Status=StatusUstr[35]; break;
       case 22: // ������ �������
                Val = (DataUstr[37]&1)==1; Status=StatusUstr[37]; break;
       case 23: // ������
                Val = (DataUstr[37]&2)==2; Status=StatusUstr[37]; break;
       case 24: // ������
                Val = (DataUstr[37]&4)==4; Status=StatusUstr[37]; break;
       case 25: // ������
                Val = (DataUstr[37]&8)==8; Status=StatusUstr[37]; break;
       case 26: // ������
                Val = (DataUstr[37]&16)==16; Status=StatusUstr[37]; break;
       case 27: // ������� ������ DW
                Val = (DataUstr[37]&32)==32; Status=StatusUstr[37]; break;
       case 28: // �������� ����������
                Val = (DataUstr[37]&64)==64; Status=StatusUstr[37]; break;
       case 29: // �������� ��������� �����
                Val = (DataUstr[37]&128)==128; Status=StatusUstr[37]; break;
       case 30: // �������� ������ SV
                Val = (DataUstr[37]&256)==256; Status=StatusUstr[37]; break;
       case 31: // �������� ������ V1
                Val = (DataUstr[37]&512)==512; Status=StatusUstr[37]; break;
       case 32: // �������� ������ V2
                Val = (DataUstr[37]&1024)==1024; Status=StatusUstr[37]; break;
       case 33: // �������� ������ V3
                Val = (DataUstr[37]&2048)==2048; Status=StatusUstr[37]; break;
       case 34: // ������� ������ SV
                Val = (DataUstr[37]&4096)==4096; Status=StatusUstr[37]; break;
       case 35: // ������� ������ V1
                Val = (DataUstr[37]&8192)==8192; Status=StatusUstr[37]; break;
       case 36: // ������� ������ V2
                Val = (DataUstr[37]&16384)==16384; Status=StatusUstr[37]; break;
       case 37: // ������� ������ V3
                Val = (DataUstr[37]&32768)==32768; Status=StatusUstr[37]; break;
       case 38: // ��� ������
                Val = DataUstr[25]; Status=StatusUstr[25]; break;
       case 39: // ��������������� ��� ������
                Val = DataUstr[26]; Status=StatusUstr[26]; break;
       case 40: // ����� ������
                Val = DataUstr[27]; Status=StatusUstr[27]; break;
       case 41: // ���� ������������� ������
                Val = DataUstr[28]; Status=StatusUstr[28]; break;
       case 42: // ����
                Val = DataUstr[0]; Status=StatusUstr[0]; break;
       case 43: // ������� �1
                Val = DataUstr[44]; Status=StatusUstr[44]; break;
       case 44:  // ������� �3
                Val = DataUstr[48]; Status=StatusUstr[48]; break;
       case 45: // ������� �������
                if (((float)DataUstr[13]/10)<35.0) Val=0; else Val=1;
                Status=StatusUstr[13]; break;
       case 46: Val = DataUstr[43]; Status=StatusUstr[43]; break;
       case 47: if (Link_Kotel3)  Val = 1; else Val=0;
                Status=0;
                break;
       case 101: // �������� � ����������� ����� �1
                 Val  = RegFl[900]; if (Link_OBSK) Status=0;  else Status=1;
                 Val1 = RegFl[SH4ma_PT201] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT201];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 102: // �������� � ����������� ����� �2
                 Val  = RegFl[902]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT202] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT202];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 103: // �������� ������ ���� � ������� ���������
                 Val =  RegFl[904]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT203] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT203];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 104: // �������� �������� ���� � ������� ���������
                 Val =  RegFl[906]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT204] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT204];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 105: // �������� ������ ���
                 Val  = RegFl[908]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT205] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT205];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 106: // ������� � ���� ������������ �1
                 Val  = RegFl[910]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI401] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI401];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 107: // ������� � ���� ������������ �2
                 Val  = RegFl[912]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI402] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI402];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 108: // ������ #1
                 Val = RegFl[914]; if (Link_OBSK) Status=0; else Status=1;
                 break;
       case 109: // ������� � ������� ����������
                 Val  = RegFl[916]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI403] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI403];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 110: // �������� � ������� ����������
                 Val  = RegFl[918]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT206] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT206];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 111: // ������� � ����������� ����������
                 Val  = RegFl[920]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_LI404] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_LI404];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 112: // �������� � ����������� ����������
                 Val  = RegFl[922]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT207] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT207];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 113: // ������ #2
                 Val = RegFl[924]; if (Link_OBSK) Status=0; else Status=1; break;
       case 114: // ������ #3
                 Val = RegFl[926]; if (Link_OBSK) Status=0; else Status=1; break;
       case 115: // ������ #4
                 Val = RegFl[928]; if (Link_OBSK) Status=0; else Status=1; break;
       case 116: // ������ #5
                 Val = RegFl[930]; if (Link_OBSK) Status=0; else Status=1; break;
       case 117: // �������� ���� � ����������
                 Val  = RegFl[932]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT210] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT210];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 118: // �������� ���� �� �������
                 Val  = RegFl[934]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT211] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT211];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 119: // �������� ���� �� ������ �� �1
                 Val  = RegFl[936]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT212] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT212];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 120: // �������� ���� �� ������ �� �2
                 Val  = RegFl[938]; if (Link_OBSK) Status=0; else Status=1;
                 Val1 = RegFl[SH4ma_PT213] ;  if (Link_OBSK) Status1=0; else Status1=1;
                 Val2 = RegFl[SH20ma_PT213];  if (Link_OBSK) Status2=0; else Status2=1;
                 sh=true;
                 break;
       case 121: // ������ #6
                 Val = RegFl[940]; if (Link_OBSK) Status=0; else Status=1; break;
       case 122: // ������ #7
                 Val = RegFl[942]; if (Link_OBSK) Status=0; else Status=1; break;
       case 123: // ������ #8
                 Val = RegFl[944]; if (Link_OBSK) Status=0; else Status=1; break;
       case 124: // ������ #9
                 Val = RegFl[946]; if (Link_OBSK) Status=0; else Status=1; break;
       case 133: // ����������� �������� ���� �1
                 Val = RegFl[948]; if (Link_OBSK) Status=0; else Status=1; break;
       case 134: // ����������� �������� ���� �2
                 Val = RegFl[950]; if (Link_OBSK) Status=0; else Status=1; break;
       case 135: // ����������� �������� ���� �3
                 Val = RegFl[952]; if (Link_OBSK) Status=0; else Status=1; break;
       case 136: // ����������� ������ ����
                 Val = RegFl[954]; if (Link_OBSK) Status=0; else Status=1; break;
       case 137: // ����������� ���� ����� �������� ����������
                 Val = RegFl[956]; if (Link_OBSK) Status=0; else Status=1; break;
       case 138: // ����������� ���� ����� ������������ ����������
                 Val = RegFl[958]; if (Link_OBSK) Status=0; else Status=1; break;
       case 139: // ����������� ������ ���
                 Val = RegFl[960]; if (Link_OBSK) Status=0; else Status=1; break;
       case 140: // ����������� ������� �� �����
                 Val = RegFl[962]; if (Link_OBSK) Status=0; else Status=1; break;
       case 201: // ����������� ����� �1 �������
                 Val = RegBits[800][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 202: // ����������� ����� �2 �������
                 Val = RegBits[800][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 203: // ����������� ����� �3 �������
                 Val = RegBits[800][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 204: // ����������� ����� ��������� �1 �������
                 Val = RegBits[800][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 205: // ����������� ����� ��������� �2 �������
                 Val = RegBits[800][10];if (Link_OBSK) Status=0; else Status=1; break;
       case 206: // ������� ����� �1 �������
                 Val = RegBits[800][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 207: // ������� ����� �2 �������
                 Val = RegBits[800][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 208: // ������� ����� �3 �������
                 Val = RegBits[800][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 209: // ����� ��� �1 �������
                 Val = RegBits[800][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 210: // ������ 13
                 Val = RegBits[804][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 211: // ����� ��� �2 �������
                 Val = RegBits[804][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 212: // ����� ��� �2 ������
                 Val = RegBits[804][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 213: // ����� ��� �3 �������
                 Val = RegBits[804][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 214: // ����� ��� �3 ������
                 Val = RegBits[804][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 215: // ����� ��� �4 �������
                 Val = RegBits[804][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 216: // ����� ��� �4 ������
                 Val = RegBits[804][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 217: // ����� ������������ �-10 �������
                 Val = RegBits[800][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 218: // ������������� ����� �1 �������
                 Val = RegBits[800][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 219: // ������������� ����� �2 �������
                 Val = RegBits[800][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 220: // ������������� ����� �3 �������
                 Val = RegBits[800][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 221: // ��������� ����� �-11 �������
                 Val = RegBits[800][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 222: // ������������� ����� �������
                 Val = RegBits[800][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 223: // ������ 1
                 Val = RegBits[800][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 224: // ������ ������� �������� Z-3
                 Val = RegBits[802][0];  if (Link_OBSK) Status=0; else Status=1; break;
       case 225: // ������ ������� �������� Z-3
                 Val = RegBits[802][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 226: // ������ ���� �������� Z-3
                 Val = RegBits[802][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 227: // ������ 2
                 Val = RegBits[802][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 228: // ������ 3
                 Val = RegBits[802][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 229: // ������ 4
                 Val = RegBits[802][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 230: // ������ 5
                 Val = RegBits[802][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 231: // ������ 6
                 Val = RegBits[802][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 232: // ������ 7
                 Val = RegBits[802][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 233: // ������� � ��������� ������� ������
                 Val = RegBits[802][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 234: // ������� � ��������� ������� �������
                 Val = RegBits[802][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 235: // ������� � ��������� ������� �������
                 Val = RegBits[802][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 236: // ������ 8
                 Val = RegBits[802][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 237: // ������� � ������������ ���� ������
                 Val = RegBits[802][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 238: // ������� � ������������ ���� �������
                 Val = RegBits[802][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 239: // ������� � ������������ ���� �������
                 Val = RegBits[802][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 240: // ������ 14
                 Val = RegBits[804][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 241: // ������� � ������� ������� �1 �������
                 Val = RegBits[804][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 242: // ������� � ������� ������� �2 �������
                 Val = RegBits[804][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 243: // �������� �� ����� � ��������� ���������� (��������)
                 Val = RegBits[804][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 244: // �������� �� ����� � ��������� ���������� (�����)
                 Val = RegBits[804][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 245: // ������ 9
                 Val = RegBits[804][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 246: // ������ 10
                 Val = RegBits[804][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 247: // ������ 11
                 Val = RegBits[804][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 248: // ������ 12
                 Val = RegBits[804][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 249: // ������ ����������� ���� ������
                 Val = RegBits[806][0]; if (Link_OBSK) Status=0; else Status=1; break;
       case 250: // ������ ����������� ���� ������
                 Val = RegBits[806][1]; if (Link_OBSK) Status=0; else Status=1; break;
       case 251: // ������ ���� � ������� ��������� ������
                 Val = RegBits[806][2]; if (Link_OBSK) Status=0; else Status=1; break;
       case 252: // ������ ���� � ������� ��������� ������
                 Val = RegBits[806][3]; if (Link_OBSK) Status=0; else Status=1; break;
       case 253: // ������ ���� � ����������� ��������� ������
                 Val = RegBits[806][4]; if (Link_OBSK) Status=0; else Status=1; break;
       case 254: // ������ ���� � ����������� ��������� ������
                 Val = RegBits[806][5]; if (Link_OBSK) Status=0; else Status=1; break;
       case 255: // ������ ���� � ������� ��������� ������
                 Val = RegBits[806][6]; if (Link_OBSK) Status=0; else Status=1; break;
       case 256: // ������ ���� � ������� ��������� ������
                 Val = RegBits[806][7]; if (Link_OBSK) Status=0; else Status=1; break;
       case 257: // ������ ���� � ����������� ��������� ������
                 Val = RegBits[806][8]; if (Link_OBSK) Status=0; else Status=1; break;
       case 258: // ������ ���� � ����������� ��������� ������
                 Val = RegBits[806][9]; if (Link_OBSK) Status=0; else Status=1; break;
       case 259: // ������ ���� � �� 6/10  ������
                 Val = RegBits[806][10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 260: // ������ ���� � �� 6/10 ������
                 Val = RegBits[806][11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 261: // ������ ���� � �� 6/20  ������
                 Val = RegBits[806][12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 262: // ������ ���� � �� 6/20 ������
                 Val = RegBits[806][13]; if (Link_OBSK) Status=0; else Status=1; break;
       case 263: // �������� �3 �������
                 Val = RegBits[806][14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 264: // �������� �3 �������
                 Val = RegBits[806][15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 265: // �������� LV-721 �����������
                 Val = Reg[300]; if (Link_OBSK) Status=0; else Status=1; break;
       case 266: // �������� LV-721 �����������
                 Val = Reg[301]; if (Link_OBSK) Status=0; else Status=1; break;
       case 267: // ������ LV-731 �����������
                 Val = Reg[302]; if (Link_OBSK) Status=0; else Status=1; break;
       case 268: // ������ LV-731 �����������
                 Val = Reg[303]; if (Link_OBSK) Status=0; else Status=1; break;
       case 269: // ������ PV-711 �����������
                 Val = Reg[304]; if (Link_OBSK) Status=0; else Status=1; break;
       case 270: // ������ PV-711 �����������
                 Val = Reg[305]; if (Link_OBSK) Status=0; else Status=1; break;
       case 271: // ������ PV-741 �����������
                 Val = Reg[306]; if (Link_OBSK) Status=0; else Status=1; break;
       case 272: // ������ PV-741 �����������
                 Val = Reg[307]; if (Link_OBSK) Status=0; else Status=1; break;
       case 273: // ������ PV-751 �����������
                 Val = Reg[308]; if (Link_OBSK) Status=0; else Status=1; break;
       case 274: // ������ PV-751 �����������
                 Val = Reg[309]; if (Link_OBSK) Status=0; else Status=1; break;
       case 275: // ������ PV-761 �����������
                 Val = Reg[310]; if (Link_OBSK) Status=0; else Status=1; break;
       case 276: // ������ PV-761 �����������
                 Val = Reg[311]; if (Link_OBSK) Status=0; else Status=1; break;
       case 277: // ������ PV-771 �����������
                 Val = Reg[312]; if (Link_OBSK) Status=0; else Status=1; break;
       case 278: // ������ PV-771 �����������
                 Val = Reg[313]; if (Link_OBSK) Status=0; else Status=1; break;
       case 301: // ������� ���� ������������ ������ �1 c ��
                 Val = Reg[140]; if (Link_OBSK) Status=0; else Status=1; break;
       case 302: // ������� ���� ������������ ������ �1 � ��
                 Val = Reg[141]; if (Link_OBSK) Status=0; else Status=1; break;
       case 303: // ������� ���� ������������ ������ �2 c ��
                 Val = Reg[144]; if (Link_OBSK) Status=0; else Status=1; break;
       case 304: // ������� ���� ������������ ������ �2 � ��
                 Val = Reg[145]; if (Link_OBSK) Status=0; else Status=1; break;
       case 305: // ������� ���� ������������ ������ �3 c ��
                 Val = Reg[148]; if (Link_OBSK) Status=0; else Status=1; break;
       case 306: // ������� ���� ������������ ������ �3 � ��
                 Val = Reg[149]; if (Link_OBSK) Status=0; else Status=1; break;
       case 307: // ������� ���� ������������ ������ �1 c ��
                 Val = Reg[160]; if (Link_OBSK) Status=0; else Status=1; break;
       case 308: // ������� ���� ������������ ������ �1 � ��
                 Val = Reg[161]; if (Link_OBSK) Status=0; else Status=1; break;
       case 309: // ������� ���� ������������ ������ �2 c ��
                 Val = Reg[162]; if (Link_OBSK) Status=0; else Status=1; break;
       case 310: // ������� ���� ������������ ������ �2 � ��
                 Val = Reg[163]; if (Link_OBSK) Status=0; else Status=1; break;
       case 311: // ������� ���� �������� ������ �1 c ��
                 Val = Reg[164]; if (Link_OBSK) Status=0; else Status=1; break;
       case 312: // ������� ���� �������� ������ �1 � ��
                 Val = Reg[165]; if (Link_OBSK) Status=0; else Status=1; break;
       case 313: // ������� ���� �������� ������ �2 c ��
                 Val = Reg[168]; if (Link_OBSK) Status=0; else Status=1; break;
       case 314: // ������� ���� �������� ������ �2 � ��
                 Val = Reg[169]; if (Link_OBSK) Status=0; else Status=1; break;
       case 315: // ������� ���� �������� ������ �3 c ��
                 Val = Reg[172]; if (Link_OBSK) Status=0; else Status=1; break;
       case 316: // ������� ���� �������� ������ �3 � ��
                 Val = Reg[173]; if (Link_OBSK) Status=0; else Status=1; break;
       case 317: // ������� ���� ������������� ������ �10 c ��
                 Val = Reg[176]; if (Link_OBSK) Status=0; else Status=1; break;
       case 318: // ������� ���� ������������� ������ �10 � ��
                 Val = Reg[177]; if (Link_OBSK) Status=0; else Status=1; break;
       case 319: // ������� ���� �������������� ������ �1 c ��
                 Val = Reg[190]; if (Link_OBSK) Status=0; else Status=1; break;
       case 320: // ������� ���� �������������� ������ �1 � ��
                 Val = Reg[191]; if (Link_OBSK) Status=0; else Status=1; break;
       case 321: // ������� ���� �������������� ������ �2 c ��
                 Val = Reg[192]; if (Link_OBSK) Status=0; else Status=1; break;
       case 322: // ������� ���� �������������� ������ �2 � ��
                 Val = Reg[193]; if (Link_OBSK) Status=0; else Status=1; break;
       case 323: // ������� ���� �������������� ������ �3 c ��
                 Val = Reg[194]; if (Link_OBSK) Status=0; else Status=1; break;
       case 324: // ������� ���� �������������� ������ �3 � ��
                 Val = Reg[195]; if (Link_OBSK) Status=0; else Status=1; break;
       case 325: // ������� ���� ���������� ������ c ��
                 Val = Reg[196]; if (Link_OBSK) Status=0; else Status=1; break;
       case 326: // ������� ���� ���������� ������ � ��
                 Val = Reg[197]; if (Link_OBSK) Status=0; else Status=1; break;
       case 327: // ������� "����" ������ ��� �1 � ��
                 Val = Reg[199]; if (Link_OBSK) Status=0; else Status=1; break;
       case 328: // ������� "����" ������ ��� �1 � ��
                 Val = Reg[200]; if (Link_OBSK) Status=0; else Status=1; break;
       case 329: // ������� "����" ������ ��� �2 � ��
                 Val = Reg[201]; if (Link_OBSK) Status=0; else Status=1; break;
       case 330: // ������� "����" ������ ��� �2 � ��
                 Val = Reg[202]; if (Link_OBSK) Status=0; else Status=1; break;
       case 331: // ������� "����" ������ ��� �3 � ��
                 Val = Reg[205]; if (Link_OBSK) Status=0; else Status=1; break;
       case 332: // ������� "����" ������ ��� �3 � ��
                 Val = Reg[206]; if (Link_OBSK) Status=0; else Status=1; break;
       case 333: // ������� "����" ������ ��� �4 � ��
                 Val = Reg[209]; if (Link_OBSK) Status=0; else Status=1; break;
       case 334: // ������� "����" ������ ��� �4 � ��
                 Val = Reg[210]; if (Link_OBSK) Status=0; else Status=1; break;
       case 335: // ����������� ����� �1 � �������
                 Val = Reg[143]; if (Link_OBSK) Status=0; else Status=1; break;
       case 336: // ����������� ����� �2 � �������
                 Val = Reg[147]; if (Link_OBSK) Status=0; else Status=1; break;
       case 337: // ����������� ����� �3 � �������
                 Val = Reg[151]; if (Link_OBSK) Status=0; else Status=1; break;
       case 338: // ������� ����� �1 � �������
                 Val = Reg[167]; if (Link_OBSK) Status=0; else Status=1; break;
       case 339: // ������� ����� �2 � �������
                 Val = Reg[171]; if (Link_OBSK) Status=0; else Status=1; break;
       case 340: // ������� ����� �3 � �������
                 Val = Reg[175]; if (Link_OBSK) Status=0; else Status=1; break;
       case 341: // ����� ��� �2 � �������
                 Val = Reg[204]; if (Link_OBSK) Status=0; else Status=1; break;
       case 342: // ����� ��� �3 � �������
                 Val = Reg[208]; if (Link_OBSK) Status=0; else Status=1; break;
       case 343: // ����� ��� �4 � �������
                 Val = Reg[212]; if (Link_OBSK) Status=0; else Status=1; break;
       case 344: // �������������� ����� ������������� ������
                 Val = Reg[178]; if (Link_OBSK) Status=0; else Status=1; break;
       case 345: // �������������� ����� ���������� ������
                 Val = Reg[198]; if (Link_OBSK) Status=0; else Status=1; break;
       case 346: // ������� ���������/���������� ������� ��� ������������ ������ �1 � ��
                 Val = Reg[142]; if (Link_OBSK) Status=0; else Status=1; break;
       case 347: // ������� ���������/���������� ������� ��� ������������ ������ �2 � ��
                 Val = Reg[146]; if (Link_OBSK) Status=0; else Status=1; break;
       case 348: // ������� ���������/���������� ������� ��� ������������ ������ �3 � ��
                 Val = Reg[150]; if (Link_OBSK) Status=0; else Status=1; break;
       case 349: // ������� ���������/���������� ������� ��� �������� ������ �1 � ��
                 Val = Reg[166]; if (Link_OBSK) Status=0; else Status=1; break;
       case 350: // ������� ���������/���������� ������� ��� �������� ������ �2 � ��
                 Val = Reg[170]; if (Link_OBSK) Status=0; else Status=1; break;
       case 351: // ������� ���������/���������� ������� ��� �������� ������ �3 � ��
                 Val = Reg[174]; if (Link_OBSK) Status=0; else Status=1; break;
       case 352: // ������� ���������/���������� ������� ��� ������ ��� �2 � ��
                 Val = Reg[203]; if (Link_OBSK) Status=0; else Status=1; break;
       case 353: // ������� ���������/���������� ������� ��� ������ ��� �3 � ��
                 Val = Reg[207]; if (Link_OBSK) Status=0; else Status=1; break;
       case 354: // ������� ���������/���������� ������� ��� ������ ��� �4 � ��
                 Val = Reg[211]; if (Link_OBSK) Status=0; else Status=1; break;
       case 355: // ������� ������� �������� Z-3 � ��
                 Val = Reg[38]; if (Link_OBSK) Status=0; else Status=1; break;
       case 356: // ������� ������� �������� Z-3 � ��
                 Val = Reg[39]; if (Link_OBSK) Status=0; else Status=1; break;
       case 357: // ������� ���������� �������� Z-3 � ��
                 Val = Reg[40]; if (Link_OBSK) Status=0; else Status=1; break;
       case 358: // ������ �������� Z-3
                 Val = Reg[41]; if (Link_OBSK) Status=0; else Status=1; break;
       case 359: // �������� � ����������� ����� �1 ��� �������� ���������
                 if ((RegBits[970][0]==1)||(RegBits[970][1]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][0]==1)||(RegBits[820][1]==1)) Status=1; else Status=0;
                 break;
       case 360: // �������� � ����������� ����� �2 ��� �������� ���������
                 if ((RegBits[970][2]==1)||(RegBits[970][3]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][2]==1)||(RegBits[820][3]==1)) Status=1; else Status=0;
                 break;
       case 361: // �������� ������ ���� � ������� ��������� ��� �������� ���������
                 if ((RegBits[970][4]==1)||(RegBits[970][5]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][4]==1)||(RegBits[820][5]==1)) Status=1; else Status=0;
                 break;
       case 362: // �������� ������ ��� ��� �������� ���������
                 if (RegBits[970][6]==1) Val=1;
                 else Val=0;
                 if (RegBits[820][6]==1) Status=1; else Status=0;
                 break;
       case 363: // �������� ���� � ���������� ��� �������� ���������
                 if (RegBits[970][7]==1) Val=1;
                 else Val=0;
                 if (RegBits[820][7]==1) Status=1; else Status=0;
                 break;
       case 364: // �������� ���� �� ������� ��� �������� ���������
                 if ((RegBits[970][8]==1)||(RegBits[970][9]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][8]==1)||(RegBits[820][9]==1)) Status=1; else Status=0;
                 break;
       case 365: // ������� � ���� ������������ �1 ��� �������� ���������
                 if ((RegBits[970][10]==1)||(RegBits[970][11]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][10]==1)||(RegBits[820][11]==1)) Status=1; else Status=0;
                 break;
       case 366: // ������� � ���� ������������ �2 ��� �������� ���������
                 if ((RegBits[970][12]==1)||(RegBits[970][13]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][12]==1)||(RegBits[820][13]==1)) Status=1; else Status=0;
                 break;
       case 367: // ������� � ������� ���������� ��� �������� ���������
                 if ((RegBits[970][14]==1)||(RegBits[970][15]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[820][14]==1)||(RegBits[820][15]==1)) Status=1; else Status=0;
                 break;
       case 368: // ������� � ����������� ���������� ��� �������� ���������
                 if ((RegBits[972][0]==1)||(RegBits[972][1]==1)) Val=1;
                 else Val=0;
                 if ((RegBits[822][0]==1)||(RegBits[822][1]==1)) Status=1; else Status=0;
                 break;
       case 369: // ������� ������� � �������� ������� �1
                 if (RegBits[972][2]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][2]==1) Status=1; else Status=0;
                 break;
       case 370: // ������� ������� � �������� ������� �2
                 if (RegBits[972][3]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][3]==1) Status=1; else Status=0;
                 break;
       case 371: // ����������� �������� �� ����� � ��������� (��������)
                 if (RegBits[972][4]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][4]==1) Status=1; else Status=0;
                 break;
       case 372: // ����������� �������� �� ����� � ��������� (�����)
                 if (RegBits[972][5]==1) Val=1;
                 else Val=0;
                 if (RegBits[822][5]==1) Status=1; else Status=0;
                 break;
       case 373: // ������������� ������������
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
       case 374: // ����� ������� 1-�� ������
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
       case 375: // ����� ������� 2-�� ������
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
       case 376: // ����� ������� 3-�� ������
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
       case 377: // ������� "����" �������������� ������ � ��
                 Val = Reg[213]; if (Link_OBSK) Status=0; else Status=1; break;
       case 378: // ������� "����" �������������� ������ � ��
                 Val = Reg[214]; if (Link_OBSK) Status=0; else Status=1; break;
       case 501: // ��������� �1. ����� ����������.  �������� �������� ���� � ������� ���������
                 Val = Reg[18]; if (Link_OBSK) Status=0; else Status=1; break;
       case 502: // ��������� �1. �������.  �������� �������� ���� � ������� ���������
                 Val = RegFl[508]; if (Link_OBSK) Status=0; else Status=1; break;
       case 503: // ��������� �1. ����������� ������������������. �������� �������� ���� � ������� ���������
                 Val = RegFl[290]; if (Link_OBSK) Status=0; else Status=1; break;
       case 504: // ��������� �1. ����� ��������������. �������� �������� ���� � ������� ���������
                 Val = RegFlEx[292]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 505: // ��������� �1. ���� ������������������. �������� �������� ���� � ������� ���������
                 Val = RegFl[294]; if (Link_OBSK) Status=0; else Status=1; break;
       case 506: // ��������� �1. ����� ����. �������� �������� ���� � ������� ���������
                 Val = RegFlEx[561]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 507: // ��������� �1. ����������� �������. �������� �������� ���� � ������� ���������
                 Val = RegFlEx[563]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 508: // ��������� �1. �����. �������� �������� ���� � ������� ���������
                 Val = RegFl[510]; if (Link_OBSK) Status=0; else Status=1; break;
       case 509: // ������ PV-711. ������� "�������" � ��
                 Val = Reg[19]; if (Link_OBSK) Status=0; else Status=1; break;
       case 510: // ������ PV-711. ������� "�������" � ��
                 Val = Reg[20]; if (Link_OBSK) Status=0; else Status=1; break;
       case 511: // ������ PV-711. ������� "����" � ��
                 Val = Reg[21]; if (Link_OBSK) Status=0; else Status=1; break;

       case 521: // ��������� �2. ����� ����������. �������� � ������� ����������
                 Val = Reg[22]; if (Link_OBSK) Status=0; else Status=1; break;
       case 522: // ��������� �2. �������. �������� � ������� ����������
                 Val = RegFl[512]; if (Link_OBSK) Status=0; else Status=1; break;
       case 523: // ��������� �2. ����������� ������������������.  �������� � ������� ����������
                 Val = RegFl[330]; if (Link_OBSK) Status=0; else Status=1; break;
       case 524: // ��������� �2. ����� ��������������. �������� � ������� ����������
                 Val = RegFlEx[332]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 525: // ��������� �2. ���� ������������������. �������� � ������� ����������
                 Val = RegFl[334]; if (Link_OBSK) Status=0; else Status=1; break;
       case 526: // ��������� �2. ����� ����. �������� � ������� ����������
                 Val = RegFlEx[571]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 527: // ��������� �2. ����������� �������. �������� � ������� ����������
                 Val = RegFlEx[573]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 528: // ��������� �2. �����. �������� � ������� ����������
                 Val = RegFl[514]; if (Link_OBSK) Status=0; else Status=1; break;
       case 529: // ������ PV-741. ������� "�������" � ��
                 Val = Reg[23]; if (Link_OBSK) Status=0; else Status=1; break;
       case 530: // ������ PV-741. ������� "�������" � ��
                 Val = Reg[24]; if (Link_OBSK) Status=0; else Status=1; break;
       case 531: // ������ PV-741. ������� "����" � ��
                 Val = Reg[25]; if (Link_OBSK) Status=0; else Status=1; break;

       case 541: // ��������� �3. ����� ����������. �������� � ����������� ����������.
                 Val = Reg[26]; if (Link_OBSK) Status=0; else Status=1; break;
       case 542: // ��������� �3. �������. �������� � ����������� ����������
                 Val = RegFl[516]; if (Link_OBSK) Status=0; else Status=1; break;
       case 543: // ��������� �3. ����������� ������������������. �������� � ����������� ����������
                 Val = RegFl[370]; if (Link_OBSK) Status=0; else Status=1; break;
       case 544: // ��������� �3. ����� ��������������. �������� � ����������� ����������
                 Val = RegFlEx[372]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 545: // ��������� �3. ���� ������������������. �������� � ����������� ����������
                 Val = RegFl[374]; if (Link_OBSK) Status=0; else Status=1; break;
       case 546: // ��������� �3. ����� ����. �������� � ����������� ����������
                 Val = RegFlEx[581]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 547: // ��������� �3. ����������� �������. �������� � ����������� ����������
                 Val = RegFlEx[583]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 548: // ��������� �3. �����. �������� � ����������� ����������
                 Val = RegFl[518]; if (Link_OBSK) Status=0; else Status=1; break;
       case 549: // ������ PV-751. ������� "�������" � ��
                 Val = Reg[27]; if (Link_OBSK) Status=0; else Status=1; break;
       case 550: // ������ PV-751. ������� "�������" � ��
                 Val = Reg[28]; if (Link_OBSK) Status=0; else Status=1; break;
       case 551: // ������ PV-751. ������� "����" � ��
                 Val = Reg[29]; if (Link_OBSK) Status=0; else Status=1; break;

       case 561: // ��������� �4. ����� ����������. �������� ���� �� ������ �� �1.
                 Val = Reg[30]; if (Link_OBSK) Status=0; else Status=1; break;
       case 562: // ��������� �4. �������. �������� ���� �� ������ �� �1.
                 Val = RegFl[520]; if (Link_OBSK) Status=0; else Status=1; break;
       case 563: // ��������� �4. ����������� ������������������. �������� ���� �� ������ �� �1.
                 Val = RegFl[410]; if (Link_OBSK) Status=0; else Status=1; break;
       case 564: // ��������� �4. ����� ��������������. �������� ���� �� ������ �� �1.
                 Val = RegFlEx[412]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 565: // ��������� �4. ���� ������������������. �������� ���� �� ������ �� �1.
                 Val = RegFl[414]; if (Link_OBSK) Status=0; else Status=1; break;
       case 566: // ��������� �4. ����� ����. �������� ���� �� ������ �� �1.
                 Val = RegFlEx[591]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 567: // ��������� �4. ����������� �������. �������� ���� �� ������ �� �1.
                 Val = RegFlEx[593]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 568: // ��������� �4. �����. �������� ���� �� ������ �� �1.
                 Val = RegFl[522]; if (Link_OBSK) Status=0; else Status=1; break;
       case 569: // ������ PV-761. ������� "�������" � ��
                 Val = Reg[31]; if (Link_OBSK) Status=0; else Status=1; break;
       case 570: // ������ PV-761. ������� "�������" � ��
                 Val = Reg[32]; if (Link_OBSK) Status=0; else Status=1; break;
       case 571: // ������ PV-761. ������� "����" � ��
                 Val = Reg[33]; if (Link_OBSK) Status=0; else Status=1; break;

       case 581: // ��������� �5. ����� ����������. �������� ���� �� ������ �� �2.
                 Val = Reg[34]; if (Link_OBSK) Status=0; else Status=1; break;
       case 582: // ��������� �5. �������. �������� ���� �� ������ �� �2.
                 Val = RegFl[524]; if (Link_OBSK) Status=0; else Status=1; break;
       case 583: // ��������� �5. ����������� ������������������. �������� ���� �� ������ �� �2.
                 Val = RegFl[450]; if (Link_OBSK) Status=0; else Status=1; break;
       case 584: // ��������� �5. ����� ��������������. �������� ���� �� ������ �� �2.
                 Val = RegFlEx[452]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 585: // ��������� �5. ���� ������������������. �������� ���� �� ������ �� �2.
                 Val = RegFl[454]; if (Link_OBSK) Status=0; else Status=1; break;
       case 586: // ��������� �5. ����� ����. �������� ���� �� ������ �� �2.
                 Val = RegFlEx[601]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 587: // ��������� �5. ����������� �������. �������� ���� �� ������ �� �2.
                 Val = RegFlEx[603]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 588: // ��������� �5. �����. �������� ���� �� ������ �� �2.
                 Val = RegFl[526]; if (Link_OBSK) Status=0; else Status=1; break;
       case 589: // ������ PV-771. ������� "�������" � ��
                 Val = Reg[35]; if (Link_OBSK) Status=0; else Status=1; break;
       case 590: // ������ PV-771. ������� "�������" � ��
                 Val = Reg[36]; if (Link_OBSK) Status=0; else Status=1; break;
       case 591: // ������ PV-771. ������� "����" � ��
                 Val = Reg[37]; if (Link_OBSK) Status=0; else Status=1; break;

       case 601: // ��������� �6. ����� ����������. ������� � ������� ����������.
                 Val = Reg[10]; if (Link_OBSK) Status=0; else Status=1; break;
       case 602: // ��������� �6. �������. ������� � ������� ����������.
                 Val = RegFl[500]; if (Link_OBSK) Status=0; else Status=1; break;
       case 603: // ��������� �6. ����������� ������������������. ������� � ������� ����������.
                 Val = RegFl[210]; if (Link_OBSK) Status=0; else Status=1; break;
       case 604: // ��������� �6. ����� ��������������. ������� � ������� ����������.
                 Val = RegFlEx[212]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 605: // ��������� �6. ���� ������������������. ������� � ������� ����������.
                 Val = RegFl[214]; if (Link_OBSK) Status=0; else Status=1; break;
       case 606: // ��������� �6. ����� ����. ������� � ������� ����������.
                 Val = RegFlEx[541]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 607: // ��������� �6. ����������� �������. ������� � ������� ����������.
                 Val = RegFlEx[543]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 608: // ��������� �6. �����. ������� � ������� ����������.
                 Val = RegFl[502]; if (Link_OBSK) Status=0; else Status=1; break;
       case 609: // ������ PV-721. ������� "�������" � ��
                 Val = Reg[11]; if (Link_OBSK) Status=0; else Status=1; break;
       case 610: // ������ PV-721. ������� "�������" � ��
                 Val = Reg[12]; if (Link_OBSK) Status=0; else Status=1; break;
       case 611: // ������ PV-721. ������� "����" � ��
                 Val = Reg[13]; if (Link_OBSK) Status=0; else Status=1; break;

       case 621: // ��������� �7. ����� ����������. ������� � ����������� ����������.
                 Val = Reg[14]; if (Link_OBSK) Status=0; else Status=1; break;
       case 622: // ��������� �7. �������. ������� � ����������� ����������.
                 Val = RegFl[504]; if (Link_OBSK) Status=0; else Status=1; break;
       case 623: // ��������� �7. ����������� ������������������. ������� � ����������� ����������.
                 Val = RegFl[250]; if (Link_OBSK) Status=0; else Status=1; break;
       case 624: // ��������� �7. ����� ��������������. ������� � ����������� ����������.
                 Val = RegFlEx[252]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 625: // ��������� �7. ���� ������������������. ������� � ����������� ����������.
                 Val = RegFl[254]; if (Link_OBSK) Status=0; else Status=1; break;
       case 626: // ��������� �7. ����� ����. ������� � ����������� ����������.
                 Val = RegFlEx[551]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 627: // ��������� �7. ����������� �������. ������� � ����������� ����������.
                 Val = RegFlEx[553]/1000.0; if (Link_OBSK) Status=0; else Status=1; break;
       case 628: // ��������� �7. �����. ������� � ����������� ����������.
                 Val = RegFl[506]; if (Link_OBSK) Status=0; else Status=1; break;
       case 629: // ������ PV-731. ������� "�������" � ��
                 Val = Reg[15]; if (Link_OBSK) Status=0; else Status=1; break;
       case 630: // ������ PV-731. ������� "�������" � ��
                 Val = Reg[16]; if (Link_OBSK) Status=0; else Status=1; break;
       case 631: // ������ PV-731. ������� "����" � ��
                 Val = Reg[17]; if (Link_OBSK) Status=0; else Status=1; break;

       case 800: // ������� ������������ �������� ����������� ����� �1
                 Val = RegFl[424]; if (Link_OBSK) Status=0; else Status=1; break;
       case 801: // ������� ������������ �������� ����������� ����� �2
                 Val = RegFl[426]; if (Link_OBSK) Status=0; else Status=1; break;
       case 802: // ������� ������� �������� ����������� �����
                 Val = RegFl[428]; if (Link_OBSK) Status=0; else Status=1; break;
       case 803: // �������� � ����������� ����� �1. �������� .
                 Val = RegFl[640]; if (Link_OBSK) Status=0; else Status=1; break;
       case 804: // �������� � ����������� ����� �1. �������.
                 Val = RegFl[642]; if (Link_OBSK) Status=0; else Status=1; break;
       case 805: // �������� � ����������� ����� �1. ����������.
                 Val = RegFl[644]; if (Link_OBSK) Status=0; else Status=1; break;
       case 806: // �������� � ����������� ����� �2. ��������.
                 Val = RegFl[646]; if (Link_OBSK) Status=0; else Status=1; break;
       case 807: // �������� � ����������� ����� �2. �������.
                 Val = RegFl[648]; if (Link_OBSK) Status=0; else Status=1; break;
       case 808: // �������� � ����������� ����� �2. ����������.
                 Val = RegFl[650]; if (Link_OBSK) Status=0; else Status=1; break;
       case 809: // �������� ������ ���� � ������� ���������. ��������.
                 Val = RegFl[652]; if (Link_OBSK) Status=0; else Status=1; break;
       case 810: // �������� ������ ���� � ������� ���������. �������.
                 Val = RegFl[654]; if (Link_OBSK) Status=0; else Status=1; break;
       case 811: // �������� ������ ���� � ������� ���������. ����������.
                 Val = RegFl[656]; if (Link_OBSK) Status=0; else Status=1; break;
       case 812: // �������� ������ ���. ��������.
                 Val = RegFl[658]; if (Link_OBSK) Status=0; else Status=1; break;
       case 813: // �������� ������ ���. ����������.
                 Val = RegFl[660]; if (Link_OBSK) Status=0; else Status=1; break;
       case 814: // �������� ���� � ����������. ��������.
                 Val = RegFl[662]; if (Link_OBSK) Status=0; else Status=1; break;
       case 815: // �������� ���� � ����������. ����������.
                 Val = RegFl[664]; if (Link_OBSK) Status=0; else Status=1; break;
       case 816: // �������� ���� �� �������. ��������.
                 Val = RegFl[666]; if (Link_OBSK) Status=0; else Status=1; break;
       case 817: // �������� ���� �� �������. �������.
                 Val = RegFl[668]; if (Link_OBSK) Status=0; else Status=1; break;
       case 818: // �������� ���� �� �������. ����������.
                 Val = RegFl[670]; if (Link_OBSK) Status=0; else Status=1; break;
       case 819: // ������� � ���� ������������ �1. ��������.
                 Val = RegFl[672]; if (Link_OBSK) Status=0; else Status=1; break;
       case 820: // ������� � ���� ������������ �1. �������.
                 Val = RegFl[674]; if (Link_OBSK) Status=0; else Status=1; break;
       case 821: // ������� � ���� ������������ �1. ����������.
                 Val = RegFl[676]; if (Link_OBSK) Status=0; else Status=1; break;
       case 822: // ������� � ���� ������������ �2. ��������.
                 Val = RegFl[678]; if (Link_OBSK) Status=0; else Status=1; break;
       case 823: // ������� � ���� ������������ �2. �������.
                 Val = RegFl[680]; if (Link_OBSK) Status=0; else Status=1; break;
       case 824: // ������� � ���� ������������ �2. ����������.
                 Val = RegFl[682]; if (Link_OBSK) Status=0; else Status=1; break;
       case 825: // ������� � ������� ����������. ��������.
                 Val = RegFl[684]; if (Link_OBSK) Status=0; else Status=1; break;
       case 826: // ������� � ������� ����������. �������.
                 Val = RegFl[686]; if (Link_OBSK) Status=0; else Status=1; break;
       case 827: // ������� � ������� ����������. ����������.
                 Val = RegFl[688]; if (Link_OBSK) Status=0; else Status=1; break;
       case 828: // ������� � ����������� ����������. ��������.
                 Val = RegFl[690]; if (Link_OBSK) Status=0; else Status=1; break;
       case 829: // ������� � ����������� ����������. �������.
                 Val = RegFl[692]; if (Link_OBSK) Status=0; else Status=1; break;
       case 830: // ������� � ����������� ����������. ����������.
                 Val = RegFl[694]; if (Link_OBSK) Status=0; else Status=1; break;
       case 831: // ������������
                 Val = Reg[222]; if (Link_OBSK) Status=0; else Status=1; break;
       case 1001: // �3. �������� ���� ����� ��������.
       case 1002: // �3. �������� ������� ����� ��������
       case 1003: // �3. ���������� � ����� �����
       case 1004: // �3. �������� ���� �� ������ �����
       case 1005: // K3. �������(1) � �������� �����
       case 1006: // �3. �������(2) � �������� �����
       case 1007: // K3. ��������� ������������� ������� ����������� ����
       case 1008: // K3. ��������� ������� ��������
       case 1009: // K3. ����������� ���� �� ������������
       case 1010: // �3. ����������� ���� ����� ������������
       case 1011: // �3. ����������� ���� ����� ������������
       case 1012: // �3. ����������� ���� �� ������������
       case 1013: // K3. ���������� ������ ����
       case 1014: // K3. ������ ���� ������� ���
       case 1015: // K3. ������ ���� ���������� ���
       case 1016: // �3. ������ ���� ������� ����
       case 1017: // K3. ������ ���� ���������� ����
       case 1018: // �3. ������ ���������� ������
       case 1019: // �3. �������� ������ �1 ������
       case 1020: // �3. �������� ������ �2 ������
       case 1021: // �3. ������ ����� ������������ ������
       case 1022: // �3. ������� �������
       case 1023: // �3. ����� ���������� ��������� ����
       case 1024: // �3. ����� ���������� ������������
       case 1025: // �3. ����� ���������� ���������
       case 1026: // �3. ����� ���������� ��������� ����
       case 1027: // �3. ��� �����������. ������� ��������
       case 1028: // �3. ��� �����������. �������� ���
       case 1029: // �3. ��� �����������. �������� ����������
       case 1030: // �3. ��� �����������. ���������
       case 1031: // �3. ��� �����������. �������������
       case 1032: // �3. ��� �����������. ������ ������
       case 1033: // �3. ��� ��������. ������� ��������
       case 1034: // �3. ��� ��������. �������� ���
       case 1035: // �3. ��� ��������. �������� ����������
       case 1036: // �3. ��� ��������. ���������
       case 1037: // �3. ��� ��������. �������������
       case 1038: // �3. ��� ��������. ������ ������
       case 1039: // �3. ������������. ������ ����� � �������
       case 1040: // �3. ������������. ����� ����� �����
       case 1041: // �3. ������������. �������������� 1-�� �����
       case 1042: // �3. ������������. ������ ������� � �������� �����
       case 1043: // �3. ������������. ������� ������� � �������� �����
       case 1044: // �3. ������������. ������������ �������� ����
       case 1045: // �3. ������������. ������� ����������� ������� ����� �� ������������
       case 1046: // �3. ������������. ������� ����������� ������� ����� ����� ������������
       case 1047: // �3. ������������. ������� ����������� ���� �� ������������
       case 1048: // �3. ������������. ������� ����������� ���� ����� ������������
       case 1049: // �3. ������������. ������ ���� ���.
       case 1050: // �3. ������������. �������������� �� ��4
       case 1051: // �3. ������������. ��������������� ���������� �������
       case 1052: // �3. ������������. ��������������� ���������� ����������
       case 1053: // �3. ����� ����� � �����
       case 1054: // �3. ���������� ����� �����
       case 1055: // �3. ����������
       case 1056: // �3. ����� ����� � �������
       case 1057: // �3. ������
       case 1058: // �3. ������� �����
       case 1059: // �3. ����� � ������
       case 1060: // �3. ������ �����
       case 1061: // �3. ������������
       case 1062: // �3. ������� ���� ��� �������� �����������
       case 1063: // �3. �������� ���� ����� �������� ������ �����������
       case 1064: // �3. �������� ���� ����� �������� ������ �����������
       case 1065: // �3. �������������� �� ��
       case 1066: // �3. ����������� ����������������
       case 1067: // �3. �������� ������� ����� �������� ������ �����������
       case 1068: // �3. ���������� � ����� ����
       case 1069: // �3. ������� � �������� ����� ���
       case 1070: // �3. ������� � �������� ����� �����
       case 1071: // �3. �������� ���� ������ �����������
       case 1072: // �3. ��� �������
       case 1073: // �3. ������� ������� ��� �������� �������� ��������
       case 1074: // �3. ������������� ��� �����������
       case 1075: // �3. ������������� ��� ��������
       case 1076: // �3. ����� ����� ����� � ��������
       case 1077: // �3. ������ ����� � �������
       case 1078: // �3. ������������ ������� ������
       case 1079: // �3. ������ ������ ����
       case 1080: // �3. ������� �������� � ����� �����
       case 1081: // �3. ���������� ������� ��������
       case 1082: // �3. ������������� ������ ������
       case 1083: // �3. ������ ��� �����������. ������� ���������������.
       case 1084: // �3. �������� ���������� ������ ����� � ���1
       case 1085: // �3. �������� ���������� ����� ������� PI1
       case 1086: // K3. �������� ���������� ����� ������� PI2
       case 1087: // �3. �������� ���������� ����� ������� DPI3
       case 1088: // �3. �������� ���������� ����� ������� LI2
       case 1089: // K3. �������� ���������� ������ ����� � ���4
       case 1090: // �3. �������� ���������� ����� ������� DI6
       case 1091: // �3. �������� ���������� ����� ������� DI16
       case 1092: // �3. �������� ���������� ������ ����� � ���5
       case 1093: // �3. �������� ���������� ������ ����� � ���6
       case 1094: // �3. �������� ���������� ������� ���� ����� ��������� ���������
       case 1095: // �3. �������� ���������� ������������� ������� ������ AV1
       case 1096: // �3. �������� ���������� ������������� ������� ������ AV2
       case 1097: // K3. �������� ���������� ������������� ������� ������ AV3
       case 1098: // �3. �������� ���������� ������� ������� ��� �������� �������� ��������
       case 1099: // �3. �������� ���������� ��� �������, �������� �������
       case 1100: // �3. �������� ���������� ��� �������, ��������  ���������
       case 1101: // �3. �������� ���������� ����������� �������� ����
       case 1102: // �3. �������� ���������� ������������ �������� ����
       case 1103: // �3. �������� ���������� �������� �������������, ������� �������
       case 1104: // �3. �������� ���������� ����������� �������� �������
       case 1105: // �3. �������� ���������� ����������� �������� ������� ��� ���������� ����������
       case 1106: // �3. �������� ���������� ����������� ����������
       case 1107: // �3. �������� ���������� ������������ �������� ����
       case 1108: // �3. �������� ���������� ����������� ������� � �������� �����
       case 1109: // �3. �������� ���������� ������������ ������� � �������� �����
       case 1110: // �3. �������� ���������� �������������� �� 2-�� �����
       case 1111: // �3. �������� ���������� ���������� ����������������
       case 1112: // �3. �������� ���������� �������� � �����
       case 1113: // �3. �������� ���������� ������ ������ ����
       case 1114: // �3. �������� ���������� ���������� ������� ��������
       case 1115: // �3. �������� ���������� ������ ��� �����������, �������� ���������
       case 1116: // �3. �������� ���������� ������ ��� �����������, �������� ����������
       case 1117: // �3. �������� ���������� ������ ��� ��������, �������� ���������
       case 1118: // �3. �������� ���������� ������ ��� ��������, �������� ����������
       case 1119: // �3. �������� ���������� ������ ��� �����������, ������� ���������������
       case 1120: // �3. �������� ����������. ������ ����� � ���1
       case 1121: // �3. �������� ����������. ����� ������� PI1
       case 1122: // �3. �������� ����������. ����� ������� PI2
       case 1123: // �3. �������� ����������. ����� ������� DIP3
       case 1124: // �3. �������� ����������. ����� ������� LI2
       case 1125: // �3. �������� ����������. ������ ����� � ���4
       case 1126: // �3. �������� ����������. ����� ������� DI6
       case 1127: // �3. �������� ����������. ����� �������  DI16
       case 1128: // �3. �������� ����������. ������ ����� � ���5
       case 1129: // �3. �������� ����������. ������ ����� � ���6
       case 1130: // �3. �������� ����������. ������� ���� ����� ��������� ���������
       case 1131: // �3. �������� ����������. ������������� ������� ������ AV1
       case 1132: // �3. �������� ����������. ������������� ������� ������ AV2
       case 1133: // �3. �������� ����������. ������������� ������� ������ AV3
       case 1134: // �3. �������� ����������. ������� ������� ��� �������� �����������
       case 1135: // �3. �������� ����������. ��� �������, �������� �������
       case 1136: // �3. �������� ����������. ��� �������, �������� ���������
       case 1137: // �3. �������� ����������. ����������� �������� ����
       case 1138: // �3. �������� ����������. ������������ �������� ����
       case 1139: // �3. �������� ����������. �������� �������������, ������� �������
       case 1140: // �3. �������� ����������. ����������� �������� �������
       case 1141: // �3. �������� ����������. ����������� �������� ������� ��� ���������� ����������
       case 1142: // �3. �������� ����������. ����������� ����������
       case 1143: // �3. �������� ����������. ������������ �������� ����
       case 1144: // �3. �������� ����������. ����������� ������� � �������� �����
       case 1145: // �3. �������� ����������. ������������ ������� � �������� �����
       case 1146: // �3. �������� ����������. �������������� CO 2-�� �����
       case 1147: // �3. �������� ����������. ���������� ����������������
       case 1148: // �3. �������� ����������. �������� � �����
       case 1149: // �3. �������� ����������. ������ ������ ����
       case 1150: // �3. �������� ����������. ���������� ������� ��������
       case 1151: // �3. �������� ����������. ������ ��� �����������, �������� ���������
       case 1152: // �3. �������� ����������. ������ ��� �����������, �������� ����������
       case 1153: // �3. �������� ����������. ������ ��� ��������, �������� ���������
       case 1154: // �3. �������� ����������. ������ ��� ��������, �������� ����������
       case 1155: // �3. �������� ����������. ������ ��� �����������, ������� ���������������
       case 1156: // �3. ��������� ����. �������
       case 1157: // �3. ��������� ����. ����� ������� (��)
       case 1158: // �3. ��������� ����. ����������� ��
       case 1159: // �3. ��������� ����. ����������� ������������������ (��)
       case 1160: // �3. ��������� ����. ����������� �������������� (��)
       case 1161: // �3. ��������� ����. ����������� ����������������� (��)
       case 1162: // �3. ��������� ����. ����������� ��
       case 1163: // �3. ��������� ����. ����� �������� (����)
       case 1164: // �3. ��������� �������. �������
       case 1165: // �3. ��������� �������. ����� ������� (��)
       case 1166: // �3. ��������� �������. ����������� ��
       case 1167: // �3. ��������� �������. ����������� ������������������ (��)
       case 1168: // �3. ��������� �������. ����������� �������������� (��)
       case 1169: // �3. ��������� �������. ����������� ����������������� (��)
       case 1170: // �3. ��������� �������. ����������� ��
       case 1171: // �3. ��������� �������. ����� �������� (����)
       case 1172: // �3. ��������� ����������. �������
       case 1173: // �3. ��������� ����������. ����� ������� (��)
       case 1174: // �3. ��������� ����������. ����������� ��
       case 1175: // �3. ��������� ����������. ����������� ������������������ (��)
       case 1176: // �3. ��������� ����������. ����������� ������������� (��)
       case 1177: // �3. ��������� ����������. ����������� ����������������� (��)
       case 1178: // �3. ��������� ����������. ����������� ��
       case 1179: // �3. ��������� ����������. ����� �������� (���)
       case 1180: // �3. ��������� ����. �������
       case 1181: // �3. ��������� ����. ����� ������� (��)
       case 1182: // �3. ��������� ����. ���������� ��
       case 1183: // �3. ��������� ����. ����������� ������������������� (��)
       case 1184: // �3. ��������� ����. ����������� �������������� (��)
       case 1185: // �3. ��������� ����. ����������� ����������������� (��)
       case 1186: // �3. ��������� ����. ����������� ��
       case 1187: // �3. ��������� ����. ����� �������� (���)
       case 1188: // �3. UPS. ������� ����������
       case 1189: // K3. UPS. ������� ���������� (fault)
       case 1190: // K3. UPS. �������� ����������
       case 1191: // K3. UPS. �������� � ���������
       case 1192: // K3. UPS. �������
       case 1193: // K3. UPS. �����������
       case 1194: // K3. UPS. ����� �������
       case 1195: // K3. UPS. ���������
       case 1196: // �3. ����������� �������
       case 1197: // �3. ����������� ����� � ��������
       case 1198: // K3. � ������ �������� ����������
       case 1199: // K3. � ������ ��������� ����������
                  Val  = DataFlUstr[IDTag-1];
                  if (Link_Kotel_DE1) Status = 1 - StatFlUstr[IDTag-1];
                  else                Status = 1;
                  break;
       case 1200: // �3. ���������� ������� �������
                  if (DataFlUstr[1026]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1026];
                  break;
       case 1201: // �3. ������� �������
                  if (DataFlUstr[1032]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1032];
                  break;
       case 1301: // �4. �������� ���� ����� ��������.
       case 1302: // �4. �������� ������� ����� ��������
       case 1303: // �4. ���������� � ����� �����
       case 1304: // �4. �������� ���� �� ������ �����
       case 1305: // K4. �������(1) � �������� �����
       case 1306: // �4. �������(2) � �������� �����
       case 1307: // K4. ��������� ������������� ������� ����������� ����
       case 1308: // K4. ��������� ������� ��������
       case 1309: // K4. ����������� ���� �� ������������
       case 1310: // �4. ����������� ���� ����� ������������
       case 1311: // �4. ����������� ���� ����� ������������
       case 1312: // �4. ����������� ���� �� ������������
       case 1313: // K4. ���������� ������ ����
       case 1314: // K4. ������ ���� ������� ���
       case 1315: // K4. ������ ���� ���������� ���
       case 1316: // �4. ������ ���� ������� ����
       case 1317: // K4. ������ ���� ���������� ����
       case 1318: // �4. ������ ���������� ������
       case 1319: // �4. �������� ������ �1 ������
       case 1320: // �4. �������� ������ �2 ������
       case 1321: // �4. ������ ����� ������������ ������
       case 1322: // �4. ������� �������
       case 1323: // �4. ����� ���������� ��������� ����
       case 1324: // �4. ����� ���������� ������������
       case 1325: // �4. ����� ���������� ���������
       case 1326: // �4. ����� ���������� ��������� ����
       case 1327: // �4. ��� �����������. ������� ��������
       case 1328: // �4. ��� �����������. �������� ���
       case 1329: // �4. ��� �����������. �������� ����������
       case 1330: // �4. ��� �����������. ���������
       case 1331: // �4. ��� �����������. �������������
       case 1332: // �4. ��� �����������. ������ ������
       case 1333: // �4. ��� ��������. ������� ��������
       case 1334: // �4. ��� ��������. �������� ���
       case 1335: // �4. ��� ��������. �������� ����������
       case 1336: // �4. ��� ��������. ���������
       case 1337: // �4. ��� ��������. �������������
       case 1338: // �4. ��� ��������. ������ ������
       case 1339: // �4. ������������. ������ ����� � �������
       case 1340: // �4. ������������. ����� ����� �����
       case 1341: // �4. ������������. �������������� 1-�� �����
       case 1342: // �4. ������������. ������ ������� � �������� �����
       case 1343: // �4. ������������. ������� ������� � �������� �����
       case 1344: // �4. ������������. ������������ �������� ����
       case 1345: // �4. ������������. ������� ����������� ������� ����� �� ������������
       case 1346: // �4. ������������. ������� ����������� ������� ����� ����� ������������
       case 1347: // �4. ������������. ������� ����������� ���� �� ������������
       case 1348: // �4. ������������. ������� ����������� ���� ����� ������������
       case 1349: // �4. ������������. ������ ���� ���.
       case 1350: // �4. ������������. �������������� �� ��4
       case 1351: // �4. ������������. ��������������� ���������� �������
       case 1352: // �4. ������������. ��������������� ���������� ����������
       case 1353: // �4. ����� ����� � �����
       case 1354: // �4. ���������� ����� �����
       case 1355: // �4. ����������
       case 1356: // �4. ����� ����� � �������
       case 1357: // �4. ������
       case 1358: // �4. ������� �����
       case 1359: // �4. ����� � ������
       case 1360: // �4. ������ �����
       case 1361: // �4. ������������
       case 1362: // �4. ������� ���� ��� �������� �����������
       case 1363: // �4. �������� ���� ����� �������� ������ �����������
       case 1364: // �4. �������� ���� ����� �������� ������ �����������
       case 1365: // �4. �������������� �� ��
       case 1366: // �4. ����������� ����������������
       case 1367: // �4. �������� ������� ����� �������� ������ �����������
       case 1368: // �4. ���������� � ����� ����
       case 1369: // �4. ������� � �������� ����� ���
       case 1370: // �4. ������� � �������� ����� �����
       case 1371: // �4. �������� ���� ������ �����������
       case 1372: // �4. ��� �������
       case 1373: // �4. ������� ������� ��� �������� �������� ��������
       case 1374: // �4. ������������� ��� �����������
       case 1375: // �4. ������������� ��� ��������
       case 1376: // �4. ����� ����� ����� � ��������
       case 1377: // �4. ������ ����� � �������
       case 1378: // �4. ������������ ������� ������
       case 1379: // �4. ������ ������ ����
       case 1380: // �4. ������� �������� � ����� �����
       case 1381: // �4. ���������� ������� ��������
       case 1382: // �4. ������������� ������ ������
       case 1383: // �4. ������ ��� �����������. ������� ���������������.
       case 1384: // �4. �������� ���������� ������ ����� � ���1
       case 1385: // �4. �������� ���������� ����� ������� PI1
       case 1386: // K4. �������� ���������� ����� ������� PI2
       case 1387: // �4. �������� ���������� ����� ������� DPI3
       case 1388: // �4. �������� ���������� ����� ������� LI2
       case 1389: // K4. �������� ���������� ������ ����� � ���4
       case 1390: // �4. �������� ���������� ����� ������� DI6
       case 1391: // �4. �������� ���������� ����� ������� DI16
       case 1392: // �4. �������� ���������� ������ ����� � ���5
       case 1393: // �4. �������� ���������� ������ ����� � ���6
       case 1394: // �4. �������� ���������� ������� ���� ����� ��������� ���������
       case 1395: // �4. �������� ���������� ������������� ������� ������ AV1
       case 1396: // �4. �������� ���������� ������������� ������� ������ AV2
       case 1397: // K4. �������� ���������� ������������� ������� ������ AV3
       case 1398: // �4. �������� ���������� ������� ������� ��� �������� �������� ��������
       case 1399: // �4. �������� ���������� ��� �������, �������� �������
       case 1400: // �4. �������� ���������� ��� �������, ��������  ���������
       case 1401: // �4. �������� ���������� ����������� �������� ����
       case 1402: // �4. �������� ���������� ������������ �������� ����
       case 1403: // �4. �������� ���������� �������� �������������, ������� �������
       case 1404: // �4. �������� ���������� ����������� �������� �������
       case 1405: // �4. �������� ���������� ����������� �������� ������� ��� ���������� ����������
       case 1406: // �4. �������� ���������� ����������� ����������
       case 1407: // �4. �������� ���������� ������������ �������� ����
       case 1408: // �4. �������� ���������� ����������� ������� � �������� �����
       case 1409: // �4. �������� ���������� ������������ ������� � �������� �����
       case 1410: // �4. �������� ���������� �������������� �� 2-�� �����
       case 1411: // �4. �������� ���������� ���������� ����������������
       case 1412: // �4. �������� ���������� �������� � �����
       case 1413: // �4. �������� ���������� ������ ������ ����
       case 1414: // �4. �������� ���������� ���������� ������� ��������
       case 1415: // �4. �������� ���������� ������ ��� �����������, �������� ���������
       case 1416: // �4. �������� ���������� ������ ��� �����������, �������� ����������
       case 1417: // �4. �������� ���������� ������ ��� ��������, �������� ���������
       case 1418: // �4. �������� ���������� ������ ��� ��������, �������� ����������
       case 1419: // �4. �������� ���������� ������ ��� �����������, ������� ���������������
       case 1420: // �4. �������� ����������. ������ ����� � ���1
       case 1421: // �4. �������� ����������. ����� ������� PI1
       case 1422: // �4. �������� ����������. ����� ������� PI2
       case 1423: // �4. �������� ����������. ����� ������� DIP3
       case 1424: // �4. �������� ����������. ����� ������� LI2
       case 1425: // �4. �������� ����������. ������ ����� � ���4
       case 1426: // �4. �������� ����������. ����� ������� DI6
       case 1427: // �4. �������� ����������. ����� �������  DI16
       case 1428: // �4. �������� ����������. ������ ����� � ���5
       case 1429: // �4. �������� ����������. ������ ����� � ���6
       case 1430: // �4. �������� ����������. ������� ���� ����� ��������� ���������
       case 1431: // �4. �������� ����������. ������������� ������� ������ AV1
       case 1432: // �4. �������� ����������. ������������� ������� ������ AV2
       case 1433: // �4. �������� ����������. ������������� ������� ������ AV3
       case 1434: // �4. �������� ����������. ������� ������� ��� �������� �����������
       case 1435: // �4. �������� ����������. ��� �������, �������� �������
       case 1436: // �4. �������� ����������. ��� �������, �������� ���������
       case 1437: // �4. �������� ����������. ����������� �������� ����
       case 1438: // �4. �������� ����������. ������������ �������� ����
       case 1439: // �4. �������� ����������. �������� �������������, ������� �������
       case 1440: // �4. �������� ����������. ����������� �������� �������
       case 1441: // �4. �������� ����������. ����������� �������� ������� ��� ���������� ����������
       case 1442: // �4. �������� ����������. ����������� ����������
       case 1443: // �4. �������� ����������. ������������ �������� ����
       case 1444: // �4. �������� ����������. ����������� ������� � �������� �����
       case 1445: // �4. �������� ����������. ������������ ������� � �������� �����
       case 1446: // �4. �������� ����������. �������������� CO 2-�� �����
       case 1447: // �4. �������� ����������. ���������� ����������������
       case 1448: // �4. �������� ����������. �������� � �����
       case 1449: // �4. �������� ����������. ������ ������ ����
       case 1450: // �4. �������� ����������. ���������� ������� ��������
       case 1451: // �4. �������� ����������. ������ ��� �����������, �������� ���������
       case 1452: // �4. �������� ����������. ������ ��� �����������, �������� ����������
       case 1453: // �4. �������� ����������. ������ ��� ��������, �������� ���������
       case 1454: // �4. �������� ����������. ������ ��� ��������, �������� ����������
       case 1455: // �4. �������� ����������. ������ ��� �����������, ������� ���������������
       case 1456: // �4. ��������� ����. �������
       case 1457: // �4. ��������� ����. ����� ������� (��)
       case 1458: // �4. ��������� ����. ����������� ��
       case 1459: // �4. ��������� ����. ����������� ������������������ (��)
       case 1460: // �4. ��������� ����. ����������� �������������� (��)
       case 1461: // �4. ��������� ����. ����������� ����������������� (��)
       case 1462: // �4. ��������� ����. ����������� ��
       case 1463: // �4. ��������� ����. ����� �������� (����)
       case 1464: // �4. ��������� �������. �������
       case 1465: // �4. ��������� �������. ����� ������� (��)
       case 1466: // �4. ��������� �������. ����������� ��
       case 1467: // �4. ��������� �������. ����������� ������������������ (��)
       case 1468: // �4. ��������� �������. ����������� �������������� (��)
       case 1469: // �4. ��������� �������. ����������� ����������������� (��)
       case 1470: // �4. ��������� �������. ����������� ��
       case 1471: // �4. ��������� �������. ����� �������� (����)
       case 1472: // �4. ��������� ����������. �������
       case 1473: // �4. ��������� ����������. ����� ������� (��)
       case 1474: // �4. ��������� ����������. ����������� ��
       case 1475: // �4. ��������� ����������. ����������� ������������������ (��)
       case 1476: // �4. ��������� ����������. ����������� ������������� (��)
       case 1477: // �4. ��������� ����������. ����������� ����������������� (��)
       case 1478: // �4. ��������� ����������. ����������� ��
       case 1479: // �4. ��������� ����������. ����� �������� (���)
       case 1480: // �4. ��������� ����. �������
       case 1481: // �4. ��������� ����. ����� ������� (��)
       case 1482: // �4. ��������� ����. ���������� ��
       case 1483: // �4. ��������� ����. ����������� ������������������� (��)
       case 1484: // �4. ��������� ����. ����������� �������������� (��)
       case 1485: // �4. ��������� ����. ����������� ����������������� (��)
       case 1486: // �4. ��������� ����. ����������� ��
       case 1487: // �4. ��������� ����. ����� �������� (���)
       case 1488: // �4. UPS. ������� ����������
       case 1489: // K4. UPS. ������� ���������� (fault)
       case 1490: // K4. UPS. �������� ����������
       case 1491: // K4. UPS. �������� � ���������
       case 1492: // K4. UPS. �������
       case 1493: // K4. UPS. �����������
       case 1494: // K4. UPS. ����� �������
       case 1495: // K4. UPS. ���������
       case 1496: // �4. ����������� �������
       case 1497: // �4. ����������� ����� � ��������
       case 1498: // K4. � ������ �������� ����������
       case 1499: // K4. � ������ ��������� ����������
                  Val  = DataFlUstr[IDTag-1];
                  if (Link_Kotel_DE1) Status = 1 - StatFlUstr[IDTag-1];
                  else                Status = 1;
                  break;
       case 1500: // �4. ���������� ������� �������
                  if (DataFlUstr[1026]>0) Val=1; else Val=0; Status = 1-StatFlUstr[1026];
                  break;
       case 1501: // �4. ������� �������
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
 // ������ ������������� ������ � �����
 // IDTag     - ID ����
 // Value     - ��������
 // Status    - ������
 // TypeArhiv - ��� ������
 // Usl       - ������� ������ � ����� 0 - �� ���������, 1 �� ���������� ��������
 bool wr=false;
 bool av=false;
 double FaktVal;
 TDateTime tmp = Now();
 switch (TypeArhiv)
  {
   case 1 : // ����� �������
            switch (Usl)
             {
              case 0: // ������ �� ���������
                      switch (UslAvar)
                       {
                        case  2: // �������� 0 - �������� ���������
                                 av = Value==0;
                                 break;
                        case  3: // �������� 0 - �������� ��������� ��� ���������� ����� (Status) �������� ���������
                                 av = (Value==0); /* || (Status==0); */ wr=true;
                                 break;
                        case  4: // �������� 1 - �������� ���������
                                 av = Value==1;
                                 break;
                        case  5: // �������� �� �������� ���������
                        case  7:
                        case 10:
                                 av=false;
                                 break;
                        case  6: // �������� ���������, ���� == 1 ��� 2
                                 av = (Value==1) || (Value==2); wr=true;
                                 break;
                        case  8: // �������� ���������, ���� != 0
                                 av = (Value!=0);
                                 break;
                        case  9: av = (Value==1) || (Value==2) || (Value==5) || (Value==10) || (Value==14) || (Value==15) || (Value>=16);
                                 break;
                       }
                      if (!Status) wr=true;
                      FaktVal = Value;
                      break;
              case 3: // �������� ��������
                      if (!Status) Value=2;
                      switch (UslAvar)
                       {
                        case  2: // �������� 0 - �������� ���������
                                 av = Value==0;
                                 break;
                        case  3: // �������� 0 - �������� ��������� ��� ���������� ����� (Status) �������� ���������
                                 av = (Value==0) || (Status==0); wr=true;
                                 break;
                        case  4: // �������� 1 - �������� ���������
                                 av = Value==1;
                                 break;
                        case  5: // �������� �� �������� ���������
                        case  7:
                        case 10:
                                 av=false;
                                 break;
                        case  6: // �������� ���������, ���� == 1 ��� 2
                                 av = (Value==1) || (Value==2); wr=true;
                                 break;
                        case  8: // �������� ���������, ���� != 0
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
              // ����� ������ ���������� � ����������� ��������
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
                if (av) // ������ �������� ���������, ������� ���������
                 PostMessage(FindWindow("TFMainForm","��� \"����-����-����\". ��������� ��������������� �����."),WM_USER+4,1,1);
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
 else if (i==15) // �� ���� 5, � 7 + ���������� � ��������� ������
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
   case eeGeneral    : // ����������� ������
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeSend       : // ��������� ������ ��� ������� ������ � �����-����������
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeReceive    : // ������ ��� ������� ������ �� �����-����������
                       Link_Kotel3 = false;ErrorCode=0;break;
   case eeConnect    : // ������ �� ���������� �� ����� ���� ��������
                       Link_Kotel3 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // ��������� ������ ��� ������� ������� ����������
                       Link_Kotel3 = false;ErrorCode=0;
                       break;
   case eeAccept     : // ��������� ������ ��� ������� ������� ����������� �������
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
   case eeGeneral    : // ����������� ������
                       Link_OBSK = false;ErrorCode=0;break;
   case eeSend       : // ��������� ������ ��� ������� ������ � �����-����������
                       Link_OBSK = false;ErrorCode=0;break;
   case eeReceive    : // ������ ��� ������� ������ �� �����-����������
                       Link_OBSK = false;ErrorCode=0;break;
   case eeConnect    : // ������ �� ���������� �� ����� ���� ��������
                       Link_OBSK = false;ErrorCode=0;
                       break;
   case eeDisconnect : // ��������� ������ ��� ������� ������� ����������
                       Link_OBSK = false;ErrorCode=0;
                       break;
   case eeAccept     : // ��������� ������ ��� ������� ������� ����������� �������
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
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForOBSK>=0)) // ������ 104 ��������
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
       // ���������� ��������� ����������
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
 // �������� �� TCP/IP  (sizeof int)4 ����� + (sizeof int)4 ����� + (sizeof double)8 ����
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // �������� ������������� ��������
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
    case TYPEBIT:   // ������ ������ ����
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
     AnsiString Text="�������� �������� ��� ���� + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"�������!",MB_OK);
    } */
//  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteTag_DE2(int Adress, int TypeValue, double value)
{
 // �������� �� TCP/IP  (sizeof int)4 ����� + (sizeof int)4 ����� + (sizeof double)8 ����
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // �������� ������������� ��������
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
    case TYPEBIT:   // ������ ������ ����
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
     AnsiString Text="�������� �������� ��� ���� + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"�������!",MB_OK);
    } */
//  }
 return;
}
//---------------------------------------------------------------------------
void __fastcall TFOpros::WriteTag(int Adress, int TypeValue, double value)
{
 // �������� �� TCP/IP  (sizeof int)4 ����� + (sizeof int)4 ����� + (sizeof double)8 ����
  union
   {
    unsigned int i;
    float        f;
   } tmp;
  if (TmpWrFun==1)  tmp.i = (int)((float)value*1000.0);
  else              tmp.f = value;

  switch (TypeValue)
   {
    case TYPEFLOAT: // �������� ������������� ��������
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
    case TYPEBIT:   // ������ ������ ����
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
     AnsiString Text="�������� �������� ��� ���� + " + IntToStr(IDTag) + " = " + FloatToStr(value);
     Application->MessageBoxA(Text.c_str(),"�������!",MB_OK);
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
 // ����� �� ID ����
 int ret=0;
 TmpWrFun = 0;
 *NumBit=0;
 switch (IDTag)
  {
   case 1023:  // ����� ���������� ��������� ����
   case 1024:  // ����� ���������� ��������� ������������
   case 1025:  // ����� ���������� ��������� ���������
   case 1026:  // ����� ���������� ��������� ����
   case 1084:  // ���������/���������� ����������
   case 1085:  // ���������/���������� ����������
   case 1086:  // ���������/���������� ����������
   case 1087:  // ���������/���������� ����������
   case 1088:  // ���������/���������� ����������
   case 1089:  // ���������/���������� ����������
   case 1090:  // ���������/���������� ����������
   case 1091:  // ���������/���������� ����������
   case 1092:  // ���������/���������� ����������
   case 1093:  // ���������/���������� ����������
   case 1094:  // ���������/���������� ����������
   case 1095:  // ���������/���������� ����������
   case 1096:  // ���������/���������� ����������
   case 1097:  // ���������/���������� ����������
   case 1098:  // ���������/���������� ����������
   case 1099:  // ���������/���������� ����������
   case 1100:  // ���������/���������� ����������
   case 1101:  // ���������/���������� ����������
   case 1102:  // ���������/���������� ����������
   case 1103:  // ���������/���������� ����������
   case 1104:  // ���������/���������� ����������
   case 1105:  // ���������/���������� ����������
   case 1106:  // ���������/���������� ����������
   case 1107:  // ���������/���������� ����������
   case 1108:  // ���������/���������� ����������
   case 1109:  // ���������/���������� ����������
   case 1110:  // ���������/���������� ����������
   case 1111:  // ���������/���������� ����������
   case 1112:  // ���������/���������� ����������
   case 1113:  // ���������/���������� ����������
   case 1114:  // ���������/���������� ����������
   case 1115:  // ���������/���������� ����������
   case 1116:  // ���������/���������� ����������
   case 1117:  // ���������/���������� ����������
   case 1118:  // ���������/���������� ����������
   case 1119:  // ���������/���������� ����������
   case 1120:  // �������� ����������
   case 1121:  // �������� ����������
   case 1122:  // �������� ����������
   case 1123:  // �������� ����������
   case 1124:  // �������� ����������
   case 1125:  // �������� ����������
   case 1126:  // �������� ����������
   case 1127:  // �������� ����������
   case 1128:  // �������� ����������
   case 1129:  // �������� ����������
   case 1130:  // �������� ����������
   case 1131:  // �������� ����������
   case 1132:  // �������� ����������
   case 1133:  // �������� ����������
   case 1134:  // �������� ����������
   case 1135:  // �������� ����������
   case 1136:  // �������� ����������
   case 1137:  // �������� ����������
   case 1138:  // �������� ����������
   case 1139:  // �������� ����������
   case 1140:  // �������� ����������
   case 1141:  // �������� ����������
   case 1142:  // �������� ����������
   case 1143:  // �������� ����������
   case 1144:  // �������� ����������
   case 1145:  // �������� ����������
   case 1146:  // �������� ����������
   case 1147:  // �������� ����������
   case 1148:  // �������� ����������
   case 1149:  // �������� ����������
   case 1150:  // �������� ����������
   case 1151:  // �������� ����������
   case 1152:  // �������� ����������
   case 1153:  // �������� ����������
   case 1154:  // �������� ����������
   case 1155:  // �������� ����������
   case 1156:  // ������� ����
   case 1157:  // ����� �������
   case 1158:  // ��
   case 1159:  // ��
   case 1160:  // ��
   case 1161:  // ��
   case 1162:  // ��
   case 1163:  // ����
   case 1164:  // ������� �������
   case 1165:  // ����� �������
   case 1166:  // ��
   case 1167:  // ��
   case 1168:  // ��
   case 1169:  // ��
   case 1170:  // ��
   case 1171:  // ����
   case 1172:  // ������� ����������
   case 1173:  // ����� �������
   case 1174:  // ��
   case 1175:  // ��
   case 1176:  // ��
   case 1177:  // ��
   case 1178:  // ��
   case 1179:  // ����
   case 1180:  // ������� ������ ����
   case 1181:  // ����� �������
   case 1182:  // ��
   case 1183:  // ��
   case 1184:  // ��
   case 1185:  // ��
   case 1186:  // ��
   case 1187:  // ����
               ret = IDTag - 1000;
               break;
  }
 return ret;
}
//---------------------------------------------------------------------------
int __fastcall TFOpros::FFullGetAdress_DE2(int IDTag,int *NumBit)
{
 // ����� �� ID ����
 int ret=0;
 TmpWrFun = 0;
 *NumBit=0;
 switch (IDTag)
  {
   case 1323:  // ����� ���������� ��������� ����
   case 1324:  // ����� ���������� ��������� ������������
   case 1325:  // ����� ���������� ��������� ���������
   case 1326:  // ����� ���������� ��������� ����
   case 1384:  // ���������/���������� ����������
   case 1385:  // ���������/���������� ����������
   case 1386:  // ���������/���������� ����������
   case 1387:  // ���������/���������� ����������
   case 1388:  // ���������/���������� ����������
   case 1389:  // ���������/���������� ����������
   case 1390:  // ���������/���������� ����������
   case 1391:  // ���������/���������� ����������
   case 1392:  // ���������/���������� ����������
   case 1393:  // ���������/���������� ����������
   case 1394:  // ���������/���������� ����������
   case 1395:  // ���������/���������� ����������
   case 1396:  // ���������/���������� ����������
   case 1397:  // ���������/���������� ����������
   case 1398:  // ���������/���������� ����������
   case 1399:  // ���������/���������� ����������
   case 1400:  // ���������/���������� ����������
   case 1401:  // ���������/���������� ����������
   case 1402:  // ���������/���������� ����������
   case 1403:  // ���������/���������� ����������
   case 1404:  // ���������/���������� ����������
   case 1405:  // ���������/���������� ����������
   case 1406:  // ���������/���������� ����������
   case 1407:  // ���������/���������� ����������
   case 1408:  // ���������/���������� ����������
   case 1409:  // ���������/���������� ����������
   case 1410:  // ���������/���������� ����������
   case 1411:  // ���������/���������� ����������
   case 1412:  // ���������/���������� ����������
   case 1413:  // ���������/���������� ����������
   case 1414:  // ���������/���������� ����������
   case 1415:  // ���������/���������� ����������
   case 1416:  // ���������/���������� ����������
   case 1417:  // ���������/���������� ����������
   case 1418:  // ���������/���������� ����������
   case 1419:  // ���������/���������� ����������
   case 1420:  // �������� ����������
   case 1421:  // �������� ����������
   case 1422:  // �������� ����������
   case 1423:  // �������� ����������
   case 1424:  // �������� ����������
   case 1425:  // �������� ����������
   case 1426:  // �������� ����������
   case 1427:  // �������� ����������
   case 1428:  // �������� ����������
   case 1429:  // �������� ����������
   case 1430:  // �������� ����������
   case 1431:  // �������� ����������
   case 1432:  // �������� ����������
   case 1433:  // �������� ����������
   case 1434:  // �������� ����������
   case 1435:  // �������� ����������
   case 1436:  // �������� ����������
   case 1437:  // �������� ����������
   case 1438:  // �������� ����������
   case 1439:  // �������� ����������
   case 1440:  // �������� ����������
   case 1441:  // �������� ����������
   case 1442:  // �������� ����������
   case 1443:  // �������� ����������
   case 1444:  // �������� ����������
   case 1445:  // �������� ����������
   case 1446:  // �������� ����������
   case 1447:  // �������� ����������
   case 1448:  // �������� ����������
   case 1449:  // �������� ����������
   case 1450:  // �������� ����������
   case 1451:  // �������� ����������
   case 1452:  // �������� ����������
   case 1453:  // �������� ����������
   case 1454:  // �������� ����������
   case 1455:  // �������� ����������
   case 1456:  // ������� ����
   case 1457:  // ����� �������
   case 1458:  // ��
   case 1459:  // ��
   case 1460:  // ��
   case 1461:  // ��
   case 1462:  // ��
   case 1463:  // ����
   case 1464:  // ������� �������
   case 1465:  // ����� �������
   case 1466:  // ��
   case 1467:  // ��
   case 1468:  // ��
   case 1469:  // ��
   case 1470:  // ��
   case 1471:  // ����
   case 1472:  // ������� ����������
   case 1473:  // ����� �������
   case 1474:  // ��
   case 1475:  // ��
   case 1476:  // ��
   case 1477:  // ��
   case 1478:  // ��
   case 1479:  // ����
   case 1480:  // ������� ������ ����
   case 1481:  // ����� �������
   case 1482:  // ��
   case 1483:  // ��
   case 1484:  // ��
   case 1485:  // ��
   case 1486:  // ��
   case 1487:  // ����
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
 // ����� ���� �� ID
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
 // ������ �������� � ����������
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
 // ������ ������������� �������� � ����������
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
   case eeGeneral    : // ����������� ������
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeSend       : // ��������� ������ ��� ������� ������ � �����-����������
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeReceive    : // ������ ��� ������� ������ �� �����-����������
                       Link_Kotel_DE1 = false;ErrorCode=0;break;
   case eeConnect    : // ������ �� ���������� �� ����� ���� ��������
                       Link_Kotel_DE1 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // ��������� ������ ��� ������� ������� ����������
                       Link_Kotel_DE1 = false;ErrorCode=0;
                       break;
   case eeAccept     : // ��������� ������ ��� ������� ������� ����������� �������
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
 if (i>0) // ������ ������
  {

   if (((Buf2[6]==0x01)&&(Buf2[7]==0x03))||
       ((Buf2[6]==0x01)&&(Buf2[7]==0x04)))
    {
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForDE_1>=0)) // ������ 104 ��������
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
       // ���������� ��������� ����������
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
   case eeGeneral    : // ����������� ������
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeSend       : // ��������� ������ ��� ������� ������ � �����-����������
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeReceive    : // ������ ��� ������� ������ �� �����-����������
                       Link_Kotel_DE2 = false;ErrorCode=0;break;
   case eeConnect    : // ������ �� ���������� �� ����� ���� ��������
                       Link_Kotel_DE2 = false;ErrorCode=0;
                       break;
   case eeDisconnect : // ��������� ������ ��� ������� ������� ����������
                       Link_Kotel_DE2 = false;ErrorCode=0;
                       break;
   case eeAccept     : // ��������� ������ ��� ������� ������� ����������� �������
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
 if (i>0) // ������ ������
  {

   if (((Buf2[6]==0x01)&&(Buf2[7]==0x03))||
       ((Buf2[6]==0x01)&&(Buf2[7]==0x04)))
    {
     if ((Buf2[8]==0xD0)&&(i==217)&&(NumParam_ForDE_2>=0)) // ������ 104 ��������
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
       // ���������� ��������� ����������
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

