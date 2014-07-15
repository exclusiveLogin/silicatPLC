//---------------------------------------------------------------------------

#ifndef FormPuskStopH
#define FormPuskStopH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFPuskStop : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel2;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        bool Click;
public:		// User declarations
        TDataSet *DataSet;  
        int ID_PUSK;
        int ID_STOP;
        int ID_STOPA;
        int ID_MODE ;
        __fastcall TFPuskStop(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPuskStop *FPuskStop;
//---------------------------------------------------------------------------
#endif
