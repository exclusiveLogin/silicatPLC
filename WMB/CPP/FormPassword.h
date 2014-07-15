//---------------------------------------------------------------------------

#ifndef FormPasswordH
#define FormPasswordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFPassword : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
private:	// User declarations
public:		// User declarations
        __fastcall TFPassword(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPassword *FPassword;
//---------------------------------------------------------------------------
#endif
