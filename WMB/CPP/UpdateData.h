//---------------------------------------------------------------------------

#ifndef UpdateDataH
#define UpdateDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TDataSource *DS1;
        TADOConnection *Con1;
        TADOQuery *Q1;
        TDataSource *DSSource;
        TADOQuery *QSource;
        TADOConnection *ConSource;
        TIntegerField *QSourceIDTag;
        TWideStringField *QSourceNameTag;
        TWideStringField *QSourceCaptionTag;
        TFloatField *QSourceValueTag;
        TIntegerField *QSourceStatusTag;
        TWideStringField *QSourceTypeOpros;
        TWideStringField *QSourceParam1;
        TWideStringField *QSourceParam2;
        TWideStringField *QSourceParam3;
        TIntegerField *QSourceTypeValue;
        TIntegerField *QSourceNumEkran;
        TIntegerField *QSourceTypeVisibleElement;
        TWideStringField *QSourceVisParam1;
        TWideStringField *QSourceVisParam2;
        TFloatField *QSourceMinVal;
        TFloatField *QSourceMaxVal;
        TFloatField *QSourceMinValIn;
        TFloatField *QSourceMaxValIn;
        TIntegerField *QSourceExtParam3;
        TWideStringField *QSourceNameContr;
        TWideStringField *QSourceNameModul;
        TWideStringField *QSourceNumEnter;
        TIntegerField *QSourceTypeArhiv;
        TIntegerField *QSourceUslWrite;
        TIntegerField *QSourceUslAvar;
        TIntegerField *QSourceVisParam3;
        TIntegerField *QSourceVisParam4;
        TIntegerField *QSourceTypeVisibleArhiv;
        TIntegerField *Q1IDTag;
        TWideStringField *Q1NameTag;
        TWideStringField *Q1CaptionTag;
        TFloatField *Q1ValueTag;
        TIntegerField *Q1StatusTag;
        TWideStringField *Q1TypeOpros;
        TWideStringField *Q1Param1;
        TWideStringField *Q1Param2;
        TWideStringField *Q1Param3;
        TIntegerField *Q1TypeValue;
        TIntegerField *Q1NumEkran;
        TIntegerField *Q1TypeVisibleElement;
        TWideStringField *Q1VisParam1;
        TWideStringField *Q1VisParam2;
        TFloatField *Q1MinVal;
        TFloatField *Q1MaxVal;
        TFloatField *Q1MinValIn;
        TFloatField *Q1MaxValIn;
        TIntegerField *Q1ExtParam3;
        TWideStringField *Q1NameContr;
        TWideStringField *Q1NameModul;
        TWideStringField *Q1NumEnter;
        TIntegerField *Q1TypeArhiv;
        TIntegerField *Q1UslWrite;
        TIntegerField *Q1UslAvar;
        TIntegerField *Q1VisParam3;
        TIntegerField *Q1VisParam4;
        TIntegerField *Q1TypeVisibleArhiv;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
