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
#include <ScktComp.hpp>
#include "ClassArhiv.hpp"
//---------------------------------------------------------------------------
class TPACQuery : public TForm
{
__published:	// IDE-managed Components
        TClientSocket *ClientSocket1;
        TTimer *Timer1;
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
        TFloatField *QListTagsMinVal;
        TFloatField *QListTagsMaxVal;
        TFloatField *QListTagsMinValIn;
        TFloatField *QListTagsMaxValIn;
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
        TLabel *statusDebug1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall ClientSocket1Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Lookup(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Write(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ClientSocket1Connecting(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
        void WriteData();
        void SendCommand(int num_zap,float value);
        int unsigned const_time_out;
        int unsigned const_time_out_query;
        void __fastcall  OnWriteValue(TMessage& Message); // запись значения в контроллер

        union{
        unsigned char buf[53];
        struct{
                unsigned char start[5];
                float data[12];//48 bytes

        }recvtmpstruct;
       }recvtmpbuf;


       union{
              unsigned char buf[10];
              struct{
                unsigned char start[5];//5 bytes
                unsigned char i_command;//1 byte
                float value;//4 bytes
              }st;
        }tmpbuf;


        MyArhiv      *Arhiv                     ;
        unsigned int TekIDSob                   ;
        unsigned int Lic                        ;  // ключ- количество тегов
        void __fastcall InitArhiv(TObject *Sender, bool &Active, int *IDTag, double *Val, int *Stat);
        void TPACQuery::analiz(int IDTag,double Value,int Status,int TypeArhiv,int Usl, int UslAvar);
public:		// User declarations
        __fastcall TPACQuery(TComponent* Owner);
        BEGIN_MESSAGE_MAP
         MESSAGE_HANDLER(WM_USER+1,TMessage, OnWriteValue)      // запись значения в контроллер
        END_MESSAGE_MAP(TComponent)
    __fastcall ~TPACQuery(void);
};
//---------------------------------------------------------------------------
MyArhiv                *ActiveArhiv;
extern PACKAGE TPACQuery *PACQuery;
//---------------------------------------------------------------------------
#endif
