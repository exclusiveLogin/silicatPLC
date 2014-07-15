//---------------------------------------------------------------------------

#ifndef FormEnterZadanH
#define FormEnterZadanH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFEnterZadan : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        float NewZad;
        __fastcall TFEnterZadan(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEnterZadan *FEnterZadan;
//---------------------------------------------------------------------------
#endif
