#include "typeepr.h"
#include "vare.h"


float Get_Float_FromEEPROM(int iBlock,int iNo)
{    
    float fValue;
    EE_MultiRead(iBlock,iNo*4,4,(char*)&fValue);
    return fValue;
}
int Write_Float_ToEEPROM(int iBlock,int iNo,float fValue)
{
    float fTemp;
    EE_WriteEnable();
    EE_MultiWrite(iBlock,iNo*4,4,(char*)&fValue);
    EE_WriteProtect();
    fTemp=Get_Float_FromEEPROM(iBlock,iNo);
    if((fTemp>fValue-0.001)&&(fTemp<fValue+0.001))      return NoError;
    else                                                return -1;
}

void ReadFromEEPROM(void)
{
 /* ������ �������� �� EEPROM */
 int adr =0;
 for(adr=0;adr<64;adr++)
    {
     VarEEPROM.r.data[adr]=Get_Float_FromEEPROM(2,adr);
    }  
 /* ����������� ��������� � ���������� */
 for (adr=0;adr<CountUstavok;adr++)
  {
   switch (adr)
    {
     case  0:workmode[0]               =VarEEPROM.r.data[adr];break;//workmode
     case  1:calcPerfIzvest[0]         =VarEEPROM.r.data[adr];break;//����������� ������������������ �������
     case  2:curentIzvestActivity[0]   =VarEEPROM.r.data[adr];break;//���������� �������
     case  3:calcPerfSand[0]           =VarEEPROM.r.data[adr];break;//����������� ������������������ �����
     case  4:curentMV[0]               =VarEEPROM.r.data[adr];break;//������ �������
     case  5:neededPerfomanceSummary[0]=VarEEPROM.r.data[adr];break;//������� ������������������
     case  6:workmode[1]               =VarEEPROM.r.data[adr];break;//workmode
     case  7:calcPerfIzvest[1]         =VarEEPROM.r.data[adr];break;//����������� ������������������ �������
     case  8:curentIzvestActivity[1]   =VarEEPROM.r.data[adr];break;//���������� �������
     case  9:calcPerfSand[1]           =VarEEPROM.r.data[adr];break;//����������� ������������������ �����
     case 10:curentMV[1]               =VarEEPROM.r.data[adr];break;//������ �������
     case 11:neededPerfomanceSummary[1]=VarEEPROM.r.data[adr];break;//������� ������������������
	}
  }
}
void WriteToEEPROM(void)
{
 /* ������ �������� � EEPROM */
 int adr=0  ;
 int izm=0  ;
 /* ����������� ��������� �� ��������� ���������� */
 for (adr=0;adr<CountUstavok;adr++)
  {
   switch (adr)
    {
     case  0:TmpEEPROM.r.data[adr]=workmode[0]               ;break;//workmode
     case  1:TmpEEPROM.r.data[adr]=calcPerfIzvest[0]         ;break;//����������� ������������������ �������
     case  2:TmpEEPROM.r.data[adr]=curentIzvestActivity[0]   ;break;//���������� �������
     case  3:TmpEEPROM.r.data[adr]=calcPerfSand[0]           ;break;//����������� ������������������ �����
     case  4:TmpEEPROM.r.data[adr]=curentMV[0]               ;break;//������ �������
     case  5:TmpEEPROM.r.data[adr]=neededPerfomanceSummary[0];break;//������� ������������������
     case  6:TmpEEPROM.r.data[adr]=workmode[1]               ;break;//workmode
     case  7:TmpEEPROM.r.data[adr]=calcPerfIzvest[1]         ;break;//����������� ������������������ �������
     case  8:TmpEEPROM.r.data[adr]=curentIzvestActivity[1]   ;break;//���������� �������
     case  9:TmpEEPROM.r.data[adr]=calcPerfSand[1]           ;break;//����������� ������������������ �����
     case 10:TmpEEPROM.r.data[adr]=curentMV[1]               ;break;//������ �������
     case 11:TmpEEPROM.r.data[adr]=neededPerfomanceSummary[1];break;//������� ������������������
	}
  }
 /* �������� �� ������� ��������� */
 for (adr=0;adr<256;adr++)
  if (TmpEEPROM.buffer[adr]!=VarEEPROM.buffer[adr])  { izm=1;break; }
 /* ���� ���� ���������, �� ������ � EEPROM */
 if (izm==1)
  {
    Print("\r\nWrite to EEPROM!");
   //++? MainVar.YesWriteToEEPROM=0;
    for(adr=0;adr<64;adr++)   
     Write_Float_ToEEPROM(2,adr,TmpEEPROM.r.data[adr]);
 
   /* ��������� ��������� � ���������� EEPROM ��� ������������ ������� ������� ��������� */
   for (adr=0;adr<256;adr++)
     VarEEPROM.buffer[adr]=TmpEEPROM.buffer[adr];
  }
}
