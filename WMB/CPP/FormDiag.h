//---------------------------------------------------------------------------

#ifndef FormDiagH
#define FormDiagH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TGetParam)(System::TObject *Sender, int IDTag, double &ValParam, int &StatusParam);
class TFDiag : public TForm
{
__published:	// IDE-managed Components
        TShape *Shape1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TStaticText *StaticText1;
        TShape *Shape2;
        TLabel *Label4;
        TStaticText *StaticText2;
        TLabel *Label5;
        TStaticText *StaticText3;
        TLabel *Label6;
        TStaticText *StaticText4;
        TLabel *Label7;
        TStaticText *StaticText5;
        TLabel *Label8;
        TStaticText *StaticText6;
        TLabel *Label9;
        TStaticText *StaticText7;
        TLabel *Label10;
        TStaticText *StaticText8;
        TShape *Shape3;
        TLabel *Label11;
        TStaticText *StaticText15;
        TShape *Shape4;
        TLabel *Label18;
        TStaticText *StaticText16;
        TLabel *Label19;
        TStaticText *StaticText17;
        TLabel *Label20;
        TStaticText *StaticText18;
        TLabel *Label21;
        TStaticText *StaticText19;
        TLabel *Label22;
        TStaticText *StaticText22;
        TShape *Shape5;
        TLabel *Label25;
        TStaticText *StaticText23;
        TLabel *Label26;
        TStaticText *StaticText24;
        TLabel *Label27;
        TStaticText *StaticText25;
        TLabel *Label28;
        TStaticText *StaticText29;
        TShape *Shape6;
        TLabel *Label32;
        TStaticText *StaticText36;
        TStaticText *StaticText43;
        TShape *Shape8;
        TLabel *Label46;
        TStaticText *StaticText50;
        TShape *Shape7;
        TLabel *Label39;
        TShape *Shape9;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *L_CRP0_0;
        TLabel *L_CRP0_3;
        TLabel *L_CRP0_3_0;
        TLabel *Label17;
        TLabel *L_CRP0_1;
        TLabel *L_CRP0_4;
        TLabel *L_CRP0_3_1;
        TLabel *Label30;
        TLabel *L_CRP0_2;
        TLabel *L_CRP0_5;
        TLabel *L_CRP0_3_2;
        TLabel *L_CRP0_4_0;
        TLabel *L_CRP0_4_1;
        TLabel *L_CRP0_4_2;
        TLabel *L_CRP0_4_3;
        TLabel *L_CRP0_4_4;
        TLabel *L_CRP0_4_5;
        TLabel *L_CRP0_4_6;
        TLabel *L_CRP0_4_7;
        TLabel *L_CRP0_4_8;
        TLabel *L_CRP0_4_9;
        TLabel *L_CRP0_4_10;
        TLabel *L_CRP0_4_11;
        TLabel *L_CRP0_5_0;
        TLabel *L_CRP0_5_1;
        TLabel *L_CRP0_5_2;
        TShape *Shape11;
        TLabel *Label52;
        TLabel *Label53;
        TLabel *L_CRP1_0;
        TLabel *L_CRP1_3;
        TLabel *L_CRP1_3_0;
        TLabel *Label57;
        TLabel *L_CRP1_1;
        TLabel *L_CRP1_4;
        TLabel *L_CRP1_3_1;
        TLabel *Label61;
        TLabel *L_CRP1_2;
        TLabel *L_CRP1_5;
        TLabel *L_CRP1_3_2;
        TLabel *L_CRP1_4_0;
        TLabel *L_CRP1_4_1;
        TLabel *L_CRP1_4_2;
        TLabel *L_CRP1_4_3;
        TLabel *L_CRP1_4_4;
        TLabel *L_CRP1_4_5;
        TLabel *L_CRP1_4_6;
        TLabel *L_CRP1_4_7;
        TLabel *L_CRP1_4_8;
        TLabel *L_CRP1_4_9;
        TLabel *L_CRP1_4_10;
        TLabel *L_CRP1_4_11;
        TLabel *L_CRP1_5_0;
        TLabel *L_CRP1_5_1;
        TLabel *L_CRP1_5_2;
        TShape *Shape10;
        TLabel *Label80;
        TLabel *Label81;
        TLabel *L_UPS_0;
        TLabel *Label83;
        TLabel *Label85;
        TLabel *L_UPS_1;
        TLabel *Label87;
        TLabel *Label89;
        TLabel *L_UPS_2;
        TLabel *Label91;
        TLabel *Label93;
        TLabel *Label94;
        TLabel *Label95;
        TLabel *Label96;
        TLabel *Label97;
        TLabel *Label98;
        TLabel *Label99;
        TLabel *Label100;
        TLabel *Label84;
        TLabel *L_UPS_3;
        TLabel *Label92;
        TLabel *Label108;
        TLabel *L_UPS_4;
        TLabel *Label110;
        TLabel *Label111;
        TLabel *L_UPS_5;
        TLabel *Label113;
        TLabel *Label114;
        TLabel *L_UPS_6;
        TLabel *Label116;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TTimer *Timer1;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
        TGetParam  FOnGetParam;
public:		// User declarations
        AnsiString Password;
        int IDTag_UPS[8]       ;
        int IDTag_CRP[2][6]    ;
        int IDDop    [2]       ;
        int IDOsn,IDRez        ;
        int IDTag_Time_Blok[36];
        int IDTag_On_Blok[36]  ;
        __property TGetParam   OnGetParam  = { read = FOnGetParam, write = FOnGetParam }; // Событие чтения параметра
        __fastcall TFDiag(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFDiag *FDiag;
//---------------------------------------------------------------------------
#endif
