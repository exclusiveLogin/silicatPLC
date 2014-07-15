//---------------------------------------------------------------------------

#ifndef FormEnterShkalsH
#define FormEnterShkalsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFEnterShkal : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TStaticText *StaticText7;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText8;
        TEdit *Edit2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int id[2];
        __fastcall TFEnterShkal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEnterShkal *FEnterShkal;
//---------------------------------------------------------------------------
#endif
