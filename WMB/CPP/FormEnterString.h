//---------------------------------------------------------------------------

#ifndef FormEnterStringH
#define FormEnterStringH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFEnterString : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TFEnterString(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFEnterString *FEnterString;
//---------------------------------------------------------------------------
#endif
