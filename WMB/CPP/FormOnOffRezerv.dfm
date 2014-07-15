object FOnOffRezerv: TFOnOffRezerv
  Left = 235
  Top = 311
  Width = 492
  Height = 105
  Caption = 'FOnOffRezerv'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clGreen
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 213
    Top = 0
    Width = 173
    Height = 24
    Cursor = crHandPoint
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Включить резерв'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 213
    Top = 24
    Width = 173
    Height = 24
    Cursor = crHandPoint
    AllowAllUp = True
    GroupIndex = 1
    Caption = 'Включить резерв'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object SpeedButton3: TSpeedButton
    Left = 213
    Top = 48
    Width = 173
    Height = 24
    Cursor = crHandPoint
    AllowAllUp = True
    GroupIndex = 1
    Down = True
    Caption = 'Отключить резерв'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton3Click
  end
  object StaticText1: TStaticText
    Left = -1
    Top = 0
    Width = 213
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Питательный насос №1:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object StaticText2: TStaticText
    Left = -1
    Top = 24
    Width = 213
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Питательный насос №2:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object StaticText3: TStaticText
    Left = -1
    Top = 48
    Width = 213
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Питательный насос №3:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object StaticText4: TStaticText
    Left = 387
    Top = 0
    Width = 95
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object StaticText5: TStaticText
    Left = 387
    Top = 24
    Width = 95
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
  object StaticText6: TStaticText
    Left = 387
    Top = 48
    Width = 95
    Height = 24
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'В резерве'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
  end
end
