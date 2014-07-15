//---------------------------------------------------------------------------

#ifndef FormEnterUstH
#define FormEnterUstH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TGetParam)(System::TObject *Sender, int IDTag, double &ValParam, int &StatusParam);
class TFEnterUst : public TForm
{
__published:	// IDE-managed Components
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TStaticText *StaticText6;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TStaticText *T5;
        TEdit *E5;
        TStaticText *T4;
        TEdit *E4;
        TStaticText *T3;
        TEdit *E3;
        TStaticText *T2;
        TEdit *E2;
        TStaticText *T1;
        TEdit *E1;
        TStaticText *StaticText5;
        TStaticText *StaticText12;
        TStaticText *StaticText13;
        TStaticText *StaticText14;
        TStaticText *StaticText15;
        TStaticText *T10;
        TEdit *E10;
        TStaticText *T9;
        TEdit *E9;
        TStaticText *T8;
        TEdit *E8;
        TStaticText *T7;
        TEdit *E7;
        TStaticText *T6;
        TEdit *E6;
        TStaticText *StaticText21;
        TStaticText *StaticText22;
        TStaticText *StaticText23;
        TStaticText *StaticText24;
        TStaticText *StaticText25;
        TStaticText *T15;
        TEdit *E15;
        TStaticText *T14;
        TEdit *E14;
        TStaticText *T13;
        TEdit *E13;
        TStaticText *T12;
        TEdit *E12;
        TStaticText *T11;
        TEdit *E11;
        TStaticText *StaticText31;
        TStaticText *StaticText32;
        TStaticText *StaticText33;
        TStaticText *StaticText34;
        TStaticText *StaticText35;
        TStaticText *T20;
        TEdit *E20;
        TStaticText *T19;
        TEdit *E19;
        TStaticText *T18;
        TEdit *E18;
        TStaticText *T17;
        TEdit *E17;
        TStaticText *T16;
        TEdit *E16;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TStaticText *StaticText9;
        TStaticText *StaticText10;
        TStaticText *StaticText11;
        TStaticText *T25;
        TEdit *E25;
        TStaticText *T24;
        TEdit *E24;
        TStaticText *T23;
        TEdit *E23;
        TStaticText *T22;
        TEdit *E22;
        TStaticText *T21;
        TEdit *E21;
        TStaticText *StaticText26;
        TStaticText *StaticText27;
        TStaticText *StaticText28;
        TStaticText *StaticText29;
        TStaticText *StaticText30;
        TStaticText *T30;
        TEdit *E30;
        TStaticText *T29;
        TEdit *E29;
        TStaticText *T28;
        TEdit *E28;
        TStaticText *T27;
        TEdit *E27;
        TStaticText *T26;
        TEdit *E26;
        TStaticText *StaticText17;
        TStaticText *T31;
        TEdit *E31;
        TTimer *Timer1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        TGetParam  FOnGetParam;
public:		// User declarations
        __fastcall TFEnterUst(TComponent* Owner);
        __property TGetParam   OnGetParam  = { read = FOnGetParam, write = FOnGetParam }; // Событие чтения параметра
        int  id[31]   ;
        bool first[31];

};
//---------------------------------------------------------------------------
extern PACKAGE TFEnterUst *FEnterUst;
//---------------------------------------------------------------------------
#endif
