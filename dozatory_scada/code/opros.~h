//---------------------------------------------------------------------------

#ifndef oprosH
#define oprosH
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
class TForm1 : public TForm
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
private:	// User declarations
        void WriteData();
        void SendCommand(int num_zap,float value);
        int unsigned const_time_out;
        int unsigned const_time_out_query;

        union{
        unsigned char buf[49];
        struct{
                unsigned char start[5];
                float data[11];//44 bytes

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
        void TForm1::analiz(int IDTag,double Value,int Status,int TypeArhiv,int Usl, int UslAvar);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
    __fastcall ~TForm1(void);
};
//---------------------------------------------------------------------------
MyArhiv                *ActiveArhiv;
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
