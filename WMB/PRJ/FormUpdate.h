//---------------------------------------------------------------------------

#ifndef FormUpdateH
#define FormUpdateH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
class TFUpdate : public TForm
{
__published:	// IDE-managed Components
        TDataSource *DSListTags;
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
        TIntegerField *QListTagsNumEkran;
        TIntegerField *QListTagsTypeVisibleElement;
        TWideStringField *QListTagsVisParam1;
        TWideStringField *QListTagsVisParam2;
        TFloatField *QListTagsMinVal;
        TFloatField *QListTagsMaxVal;
        TFloatField *QListTagsMinValIn;
        TFloatField *QListTagsMaxValIn;
        TIntegerField *QListTagsVisParam3;
        TIntegerField *QListTagsVisParam4;
        TIntegerField *QListTagsTypeVisibleArhiv;
        TIntegerField *QListTagsTypeArhiv;
        TIntegerField *QListTagsUslAvar;
        TADOConnection *ConArhiv;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFUpdate(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFUpdate *FUpdate;
//---------------------------------------------------------------------------
#endif
