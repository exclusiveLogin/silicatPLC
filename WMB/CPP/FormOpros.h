//---------------------------------------------------------------------------

#ifndef FormOprosH
#define FormOprosH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
#include <ExtCtrls.hpp>
#include <IniFiles.hpp>
#include "ClassArhiv.hpp"
#include <ScktComp.hpp>
#define CountTimers   5   // Количество внутренних таймеров
#define CountMaxPorts 10
#define CountActiveTags 2000
#define TYPEFLOAT    0           // запись вещественного значения
#define TYPEBIT      1           // запись одного бита
#define SH4ma_PT201  4           //  смещение = X/2 + 52  адрес = (смещение-52)*2
#define SH20ma_PT201 6
#define SH4ma_PT202  14
#define SH20ma_PT202 16
#define SH4ma_PT203  24
#define SH20ma_PT203 26
#define SH4ma_PT204  34
#define SH20ma_PT204 36
#define SH4ma_PT205  44
#define SH20ma_PT205 46
#define SH4ma_PT206  54
#define SH20ma_PT206 56
#define SH4ma_PT207  64
#define SH20ma_PT207 66
#define SH4ma_PT210  74
#define SH20ma_PT210 76
#define SH4ma_PT211  84
#define SH20ma_PT211 86
#define SH4ma_PT212  94
#define SH20ma_PT212 96
#define SH4ma_PT213  104
#define SH20ma_PT213 106
#define SH4ma_LI401  114
#define SH20ma_LI401 116
#define SH4ma_LI402  124
#define SH20ma_LI402 126
#define SH4ma_LI403  134
#define SH20ma_LI403 136
#define SH4ma_LI404  144
#define SH20ma_LI404 146
//---------------------------------------------------------------------------
DWORD           dwError[CountMaxPorts]     ;
BOOL            fSuccess[CountMaxPorts]    ;
DCB             dcb[CountMaxPorts]         ;
COMMTIMEOUTS    TimeOutInfo[CountMaxPorts] ;
typedef struct
{
 TTimeStamp    begin  ; // Время начала таймера
 TTimeStamp    end    ; // Текущее время
 bool          OnTimer; // Таймер включен
 unsigned long dlit   ; // Длительность
} TTimersInfo;
typedef union
{
 float Val[9];
 struct
  {
   short int     id    ;
   float         tmp[4];
   short int     ds    ;
   float         kp    ;
   unsigned long ti    ;
   float         zn    ;
   float         tmp2  ;
  } contex;
} TTypeReg;
class TFOpros : public TForm
{
__published:	// IDE-managed Components
        TDataSource *DSListTag;
        TADOConnection *ConArhiv;
        TADOQuery *QListTags;
        TIntegerField *QListTagsIDTag;
        TWideStringField *QListTagsNameTag;
        TWideStringField *QListTagsCaptionTag;
        TFloatField *QListTagsValueTag;
        TIntegerField *QListTagsStatusTag;
        TWideStringField *QListTagsTypeOpros;
        TWideStringField *QListTagsParam1;
        TWideStringField *QListTagsParam2;
        TWideStringField *QListTagsParam3;
        TIntegerField *QListTagsTypeValue;
        TIntegerField *QListTagsExtParam3;
        TIntegerField *QListTagsNumEkran;
        TIntegerField *QListTagsTypeArhiv;
        TIntegerField *QListTagsUslWrite;
        TIntegerField *QListTagsUslAvar;
        TDataSource *DSArhivSob;
        TADOConnection *ConArhivSob;
        TADOQuery *QArhivSob;
        TIntegerField *QArhivSobIDSob;
        TDateTimeField *QArhivSobDTSob;
        TIntegerField *QArhivSobIDTag;
        TIntegerField *QArhivSobVal;
        TBooleanField *QArhivSobActive;
        TBooleanField *QArhivSobKvitirov;
        TBooleanField *QArhivSobActive1;
        TDateTimeField *QArhivSobDlit;
        TTimer *Timer1;
        TClientSocket *ClientSocket1;
        TClientSocket *ClientSocket2;
        TFloatField *QListTagsMinVal;
        TFloatField *QListTagsMaxVal;
        TFloatField *QListTagsMinValIn;
        TFloatField *QListTagsMaxValIn;
        TClientSocket *ClientSocket3;
        TClientSocket *ClientSocket4;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket1Lookup(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Write(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket2Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket2Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket2Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket3Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket3Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket3Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket4Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket4Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ClientSocket4Read(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
        void WriteData(void);
        HANDLE __fastcall  OpenPort(int NumCom, HANDLE ComPort); // открытие COM порта
        WORD Crc16(BYTE *Data, ULONG size)                               ;
        TTimersInfo      TimersInfo[CountTimers]; // Таймеры ожидания ответа, внутренние таймеры
//        bool           Read_Modbus(int AdrUstr, int NumGroup, int *Error, unsigned short int *res,unsigned short int *stat);
//        unsigned int   BaundRate[CountMaxPorts]   ;
//        int            ByteSize[CountMaxPorts]    ;
//        int            Parity[CountMaxPorts]      ;
//        int            StopBits[CountMaxPorts]    ;
//        int            RInterval[CountMaxPorts]   ;
//        int            RCInterval[CountMaxPorts]  ;
//        int            RMInterval[CountMaxPorts]  ;
//        int            WCInterval[CountMaxPorts]  ;
//        int            WMInterval[CountMaxPorts]  ;
        unsigned short int DataUstr[50]             ;
        float              DataFlUstr[2000]         ;
        unsigned short int StatFlUstr[2000]         ;
//        unsigned short int DataDIUstr[1000]       ;
        unsigned char      DataBitUstr[1000]      ;
        unsigned short int StatusUstr[50]         ;
        bool               Link_Kotel3            ; // связь с котлом №3. Американец
        bool               Link_Kotel_DE1         ; // связь с котлом №1. ДЕ-1
        bool               Link_Kotel_DE2         ; // связь с котлом №2. ДЕ-2
        unsigned int       const_tim_out_k3       ; // тайм-аут на восстановление соединения в циклах программы цикл==1сек. для котла №3 (американец)
        unsigned int       const_tim_out_zk3      ; // тайм-аут на подачу запроса к котлу №3
        unsigned int       const_tim_out_kde_1    ; // тайм-аут на подачу запроса к котлу ДЕ - №1
        unsigned int       const_tim_out_kde_2    ;
        unsigned int       const_tim_out_obsk     ; // тайм-аут на восстановление соединения в циклах программы для общекотельной автоматики
        unsigned int       const_tim_out_zobsk    ; // тайм-аут на подачу запроса к общекотельной автоматики
        unsigned int       const_tim_out_zkde_1   ; // тайм-аут на восстановление соединения в циклах программы для котла ДЕ - №1
        unsigned int       const_tim_out_zkde_2   ; // тайм-аут на восстановление соединения в циклах программы для котла ДЕ - №2
//        bool         Link_modbus                ;
//        HANDLE       Port_Modbus                ;
//        bool         rez_opr_modbus             ;  // режим опроса включен (отправка запроса) / выключен (ожидание ответа)
//        unsigned int count_cikl_time_out_modbus ;  // количество циклов на ожидание ответа по MODBUS протоколу
//        int          NumPortModbus              ;
        unsigned int Lic                          ;  // ключ - количество тэгов
//        unsigned int tim_out_modbus             ;
        bool         ModeApp                    ;
        bool         Link_OBSK                  ;
        unsigned int TekIDSob                   ;
        MyArhiv      *Arhiv                     ;
        int          NumParam_ForOBSK           ;
        int          NumParam_ForDE_1           ;
        int          NumParam_ForDE_2           ;

        unsigned int    GetLastRecordArhivSob(void)                      ;
        void __fastcall  OnWriteValue(TMessage& Message)                 ; // запись значения в контроллер
        void __fastcall  OnWriteFloatValue(TMessage& Message)            ; // запись вещественного значения в контроллер
        void __fastcall SendCommandForK3(int NumCom)                     ; // посылка команды к котлу №1 (американец)
        void __fastcall SendCommandForObsK(int NumCom)                   ; // посылка команды к общекотловой автоматике
        void __fastcall SendCommandForDE_1(int NumCom)                   ; // посылка команды к котлу №3 (ДЕ-№3)
        void __fastcall SendCommandForDE_2(int NumCom)                   ; // посылка команды к котлу №4 (ДЕ-№4)
//        bool __fastcall ReadModbus(int AdrUstr,     int  NumCom,  float *data                       );
//        bool            Send_Modbus(int AdressUstr, int NumParam)                                    ;
//        int  __fastcall ReadDataCom(HANDLE ComPort, unsigned char *buffer, unsigned int MaxLenBuffer);
//        bool __fastcall WriteDataCom(HANDLE ComPort, unsigned char *buffer, unsigned long CountBytes);
        void  __fastcall InitArhiv (TObject *Sender, bool &Active, int *IDTag, double *Val, int *Stat);
        void  __fastcall analiz(int IDTag,double Value,int Status,int TypeArhiv,int Usl, int UslAvar) ;
        int   __fastcall FGetReg(int index)                ;
        int   __fastcall FGetFloatIndex(int Index)         ;
        float __fastcall FGetRegFl(int Index)              ;
        float __fastcall FGetRegFl_DE1(int Index)          ;
        float __fastcall FGetRegFl_DE2(int Index)          ;
        int   __fastcall FGetRegFlEx(int Index)            ;
        void  __fastcall FSetRegFl(int Index, float Value)    ;
        float __fastcall FGetBits(int Index, int Bit)         ;
        void  __fastcall FSetReg(int index, int Value)        ;
        void  __fastcall FSetRegFl_DE1(int index, float Value);
        void  __fastcall FSetRegFl_DE2(int index, float Value);
        float __property RegFl[int index]         =    { read = FGetRegFl, write =FSetRegFl };
        int   __property RegFlEx[int index]       =    { read = FGetRegFlEx                 };
        int   __property Reg[int index]           =    { read = FGetReg,   write =FSetReg   };
        float __property RegFl_DE1[int index]     =    { read = FGetRegFl_DE1, write = FSetRegFl_DE1 };
        float __property RegFl_DE2[int index]     =    { read = FGetRegFl_DE2, write = FSetRegFl_DE2 };

        int   __property IndexFloat[int index]    =    { read = FGetFloatIndex };
        float __property RegBits[int Index][int Bit] = { read = FGetBits       };
        void __fastcall WriteTag(int IDTag, int TypeValue, double value)        ;
        void __fastcall WriteTag_DE1(int Adress, int TypeValue, double value)   ;
        void __fastcall WriteTag_DE2(int Adress, int TypeValue, double value)   ;
        int __fastcall  FFullGetAdress(int IDTag, int *NumBit)                  ;
        int __fastcall  FFullGetAdress_DE1(int IDTag, int *NumBit)              ;
        int __fastcall  FFullGetAdress_DE2(int IDTag, int *NumBit)              ;
        int __fastcall  FGetAdress(int IDTag)                                   ;
        int __fastcall  FGetAdress_DE1(int IDTag)                               ;
        int __fastcall  FGetAdress_DE2(int IDTag)                               ;
        int   __property Adress[int IDTag]     = { read = FGetAdress }          ;
        int   __property Adress_DE1[int IDTag] = { read = FGetAdress_DE1 }      ;
        int   __property Adress_DE2[int IDTag] = { read = FGetAdress_DE2 }      ;
        float       WriteVal[50]       ; // записываемое значение
        float       WriteVal_DE1[50]   ; // записываемое значение
        float       WriteVal_DE2[50]   ; // записываемое значение
        short int   WriteAdress[50]    ; // адрес для записи значения
        short int   WriteAdress_DE1[50]; // адрес для записи значения
        short int   WriteAdress_DE2[50]; // адрес для записи значения
        bool        WrVal[50]       ; // необходимость записи значения
        bool        WrVal_DE1[50]   ;
        bool        WrVal_DE2[50]   ;
        int         WrIDTag[50]     ; // ID тэга для записи значения
        int         WrIDTag_DE1[50] ;
        int         WrIDTag_DE2[50] ;
        int         WrNumZap[50]    ;
        int         WrNumZap_DE1[50];
        int         WrNumZap_DE2[50];
        int         WrFunWr[50]     ; // функция записи 0 - обычно, 1 - время * 1000 как long
        int         TmpWrFun        ;
        int         WrIndexBuf      ;
        int         WrIndexBuf_DE1  ;
        int         WrIndexBuf_DE2  ;
        TTypeReg    RegInfo[7]      ;
public:		// User declarations
        __fastcall TFOpros(TComponent* Owner);
        BEGIN_MESSAGE_MAP
         MESSAGE_HANDLER(WM_USER+1,TMessage, OnWriteValue)      // запись значения в контроллер
         MESSAGE_HANDLER(WM_USER+2,TMessage, OnWriteFloatValue) // запись вещественного значения в контроллер
        END_MESSAGE_MAP(TComponent)
};
//---------------------------------------------------------------------------
MyArhiv                *ActiveArhiv;
extern PACKAGE TFOpros *FOpros     ;
//---------------------------------------------------------------------------
#endif
