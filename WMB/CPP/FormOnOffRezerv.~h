//---------------------------------------------------------------------------

#ifndef FormOnOffRezervH
#define FormOnOffRezervH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFOnOffRezerv : public TForm
{
__published:	// IDE-managed Components
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TStaticText *StaticText4;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
       bool Click;
public:		// User declarations
        __fastcall TFOnOffRezerv(TComponent* Owner);
        TDataSet *DataSet;
        int ID_REZ1 ; // ID состояние резерва насоса №1
        int ID_REZ2 ; // ID состояние резерва насоса №2
        int ID_REZ3 ; // ID состояние резерва насоса №3
        int ID_WREZ1; // ID для записи состояния резерва насоса №1
        int ID_WREZ2; // ID для записи состояния резерва насоса №2
        int ID_WREZ3; // ID для записи состояния резерва насоса №3
};
//---------------------------------------------------------------------------
extern PACKAGE TFOnOffRezerv *FOnOffRezerv;
//---------------------------------------------------------------------------
#endif
