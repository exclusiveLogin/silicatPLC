//---------------------------------------------------------------------------

#ifndef FormProgEchoH
#define FormProgEchoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ScktComp.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
#include "ClassArhiv.hpp"
MyArhiv *ActiveArhiv;
//---------------------------------------------------------------------------
class TFPEcho : public TForm
{
__published:	// IDE-managed Components
        TServerSocket *SSocket;
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
        void __fastcall SSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall SSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
private:	// User declarations
       MyArhiv    *Arhiv ; // Архив для хранения информации (сохранение раз в секунду неактивно)
public:		// User declarations
        __fastcall TFPEcho(TComponent* Owner);
        __fastcall ~TFPEcho(void)            ;
};
//---------------------------------------------------------------------------
extern PACKAGE TFPEcho *FPEcho;
//---------------------------------------------------------------------------
#endif
