//---------------------------------------------------------------------------

#ifndef FormRegH
#define FormRegH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <Chart.hpp>
#include <DBChart.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <IniFiles.hpp>
#include "DBGridEh.hpp"
#include "ClassArhiv.hpp"
#include <Grids.hpp>
#include <ADODB.hpp>
#include <Db.hpp>
//---------------------------------------------------------------------------
typedef void __fastcall (__closure *TGetParam)(System::TObject *Sender, int IDTag, double &ValParam, int &StatusParam);
class TFReg : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TPanel *Panel2;
        TSplitter *Splitter1;
        TPanel *Panel3;
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TTrackBar *TrackBar1;
        TStaticText *L11_Exit;
        TStaticText *L1_Exit;
        TStaticText *L10_Exit;
        TStaticText *L9_Exit;
        TStaticText *L8_Exit;
        TStaticText *L7_Exit;
        TStaticText *L6_Exit;
        TStaticText *L5_Exit;
        TStaticText *L4_Exit;
        TStaticText *L3_Exit;
        TStaticText *L2_Exit;
        TPanel *Panel7;
        TTrackBar *TrackBar2;
        TStaticText *L11_Zad;
        TStaticText *L1_Zad;
        TStaticText *L10_Zad;
        TStaticText *L9_Zad;
        TStaticText *L8_Zad;
        TStaticText *L7_Zad;
        TStaticText *L6_Zad;
        TStaticText *L5_Zad;
        TStaticText *L4_Zad;
        TStaticText *L3_Zad;
        TStaticText *L2_Zad;
        TPanel *Panel8;
        TTrackBar *TrackBar3;
        TStaticText *L11_Whod;
        TStaticText *L1_Whod;
        TStaticText *L10_Whod;
        TStaticText *L9_Whod;
        TStaticText *L8_Whod;
        TStaticText *L7_Whod;
        TStaticText *L6_Whod;
        TStaticText *L5_Whod;
        TStaticText *L4_Whod;
        TStaticText *L3_Whod;
        TStaticText *L2_Whod;
        TStaticText *StaticText34;
        TStaticText *StaticText35;
        TStaticText *StaticText36;
        TMaskEdit *MaskEdit1;
        TMaskEdit *MaskEdit2;
        TMaskEdit *MaskEdit3;
        TPanel *Panel9;
        TPanel *Panel10;
        TPanel *Panel11;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TTimer *Timer1;
        TPanel *PanelTrend;
        TSplitter *Splitter4;
        TPanel *PView;
        TDBGridEh *DBGridEh6;
        TTrackBar *TBValue;
        TChart *Trends;
        TPanel *Vizir;
        TLineSeries *Series1;
        TDataSource *DSViewData;
        TADOQuery *QViewData;
        TIntegerField *QViewDataIDInfo;
        TIntegerField *QViewDataIDTrend;
        TIntegerField *QViewDataIDTag;
        TIntegerField *QViewDataColorLine;
        TDateTimeField *QViewDataTDT;
        TFloatField *QViewDataVal;
        TIntegerField *QViewDataStatus;
        TFloatField *QViewDataValProc;
        TBooleanField *QViewDataActive;
        TADOConnection *ConViewData;
        TDataSource *DSConChecktrend;
        TADOQuery *QConCheckTrend;
        TIntegerField *QConCheckTrendIDInfo;
        TIntegerField *QConCheckTrendIDTrend;
        TIntegerField *QConCheckTrendIDTag;
        TIntegerField *QConCheckTrendColorLine;
        TDateTimeField *QConCheckTrendTDT;
        TFloatField *QConCheckTrendVal;
        TIntegerField *QConCheckTrendStatus;
        TFloatField *QConCheckTrendValProc;
        TADOConnection *ConCheckTrend;
        TDataSource *DSListTrend;
        TADOQuery *QListTrend;
        TIntegerField *QListTrendIDTrend;
        TWideStringField *QListTrendCaptionTrend;
        TADOConnection *ConListTrend;
        TPanel *Panel12;
        TPanel *Panel71;
        TSpeedButton *SBPlus;
        TSpeedButton *SBMinus;
        TSpeedButton *SpeedButton3;
        TSpeedButton *SBTagMinus;
        TSpeedButton *SBHourMinus;
        TSpeedButton *SBHourPlus;
        TSpeedButton *SBTagPlus;
        TStaticText *StaticText90;
        TDateTimePicker *DTPTime_beginTrend;
        TDateTimePicker *DTPDate_beginTrend;
        TStaticText *StaticText118;
        TDateTimePicker *DTPTime_endTrend;
        TDateTimePicker *DTPDate_endTrend;
        TBitBtn *BBBuilderTrend;
        TStaticText *STTimeTrend;
        void __fastcall TrackBar3Change(TObject *Sender);
        void __fastcall TrackBar3Enter(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall TrackBar2Change(TObject *Sender);
        void __fastcall TrackBar2Enter(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall TrackBar1Enter(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall MaskEdit2Exit(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BBBuilderTrendClick(TObject *Sender);
        void __fastcall SBPlusClick(TObject *Sender);
        void __fastcall SBMinusClick(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SBTagMinusClick(TObject *Sender);
        void __fastcall SBHourMinusClick(TObject *Sender);
        void __fastcall SBHourPlusClick(TObject *Sender);
        void __fastcall SBTagPlusClick(TObject *Sender);
        void __fastcall TBValueChange(TObject *Sender);
        void __fastcall TrendsGetAxisLabel(TChartAxis *Sender,
          TChartSeries *Series, int ValueIndex, AnsiString &LabelText);
        void __fastcall TrendsMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall TrendsMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall TrendsMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall TrendsResize(TObject *Sender);
        void __fastcall DBGridEh6DrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumnEh *Column,
          TGridDrawState State);
        void __fastcall DBGridEh6MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall QConCheckTrendTDTGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataIDTagGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataValGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataStatusGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataValProcGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataActiveGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataTDTGetText(TField *Sender,
          AnsiString &Text, bool DisplayText);
        void __fastcall QViewDataAfterScroll(TDataSet *DataSet);
        void __fastcall QViewDataCalcFields(TDataSet *DataSet);
private:	// User declarations
        bool       FModeReg; // 1 - автоматический режим, 0 - ручной
        AnsiString FEdIzm  ; // Единицы измерения
        int        NewSizeWidth;
        void __fastcall SetModeReg(bool Value)    ;
        void __fastcall SetZadAuto(double Value)  ;
        void __fastcall SetZadHand(double Value)  ;
        void __fastcall SetEnter(double Value)    ; // вход
        void __fastcall SetExit(double Value)     ; // выход
        double     KoefMas    ; // коэффициент масштабирования
        double     FHandZadReg; // Задание регулятора в ручном режиме
        double     FAutoZadReg; // Задание регулятора в автоматическом режиме
        double     FEnterReg  ; // Вход регулятора
        double     FExitReg   ; // Выход регулятора
        double     FMinValue,FMaxValue ; // шкала регулятора
        double     FMn                 ;
        double     SmFMn               ;
        int        FIDTrends  ;
        TGetParam  FOnGetParam;
        bool       MoveVizir;
        int __fastcall GetCountSeries(int IDTrends, double *Shkals_min, double *Shkals_max, double *min_insh, double *max_insh, int *IDTags, unsigned int *ColorTrend, double *tmp_min, double *tmp_max);
        AnsiString __fastcall GetNameEdIzm(int IDTag);
        int       __fastcall  RecNo(int IDTag)       ;
        double       Shkals_Min[200]   ;
        double       Shkals_Max[200]   ;
        double       Shkals_InMin[200] ;
        double       Shkals_InMax[200] ;
        unsigned int ColorTrend[200]   ;
        int          IDTags_Trends[200];
        double       Mashtab;
        AnsiString   FormatTrend[200]  ;

public:		// User declarations
        __fastcall TFReg(TComponent* Owner);
        __property bool        ModeReg     = { read = FModeReg,    write = SetModeReg  }; // Режим регулятора
        __property AnsiString  EdIzm       = { read = FEdIzm,      write = FEdIzm      }; // Единицы измерения задания в аытоматическом режиме
        __property double      ZadanieAuto = { read = FAutoZadReg, write = SetZadAuto  }; // Задание регулятора в автоматическом режиме
        __property double      ZadanieHand = { read = FHandZadReg, write = SetZadHand  }; // Задание регулятора в ручном режиме
        __property TGetParam   OnGetParam  = { read = FOnGetParam, write = FOnGetParam }; // Событие чтения параметра
        void __fastcall SetShkals(double MinValue, double MaxValue); // установка шкалы для регулятора
        int TypeReg    ; // Тип регулятора 0 - обычный, 1 - для КР-500
        int IDTAG_ENTER; // ID тэга для чтения значения входа
        int IDTAG_EXIT ; // ID тэга для чтения значения выхода
        int IDTAG_MODE ; // ID тэга для изменения режима
        int IDTAG_ZADHAND; // ID тэга для изменения задания в ручном режиме
        int IDTAG_ZADAUTO; // ID тэга для изменения задания в автоматическом режиме
        int ID_K1,ID_K2,ID_K3,ID_K4,ID_K5,ID_K6,ID_K7;
        AnsiString Password; // Пароль для изменения коэффициентов регулятора

        __property int         IDTrend_Reg = { read = FIDTrends, write = FIDTrends };
        TADOQuery *QListTags;
        MyArhiv   *Arhiv   ;
        __fastcall ~TFReg(void); 

};
//---------------------------------------------------------------------------
extern PACKAGE TFReg *FReg;
//---------------------------------------------------------------------------
#endif
