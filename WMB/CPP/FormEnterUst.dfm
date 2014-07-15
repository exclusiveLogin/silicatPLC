object FEnterUst: TFEnterUst
  Left = 216
  Top = 194
  Width = 1115
  Height = 476
  Caption = 'УСТАВКИ:'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object StaticText1: TStaticText
    Left = 0
    Top = 0
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'АВР. Мин.давл.в пит. линии №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object StaticText2: TStaticText
    Left = 0
    Top = 28
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'АВР. Мин.давл.в пит. линии №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object StaticText3: TStaticText
    Left = 0
    Top = 84
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. давление в пит. линии №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object StaticText4: TStaticText
    Left = 0
    Top = 56
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'АВР. Разница давл. сист. отоп.:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object StaticText6: TStaticText
    Left = 0
    Top = 112
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. давление в пит. линии №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
  object BitBtn1: TBitBtn
    Left = 0
    Top = 422
    Width = 225
    Height = 25
    Caption = 'Сохранить'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = BitBtn1Click
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
  object BitBtn2: TBitBtn
    Left = 322
    Top = 423
    Width = 225
    Height = 25
    Caption = 'Закрыть окно '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    Kind = bkCancel
  end
  object T5: TStaticText
    Left = 376
    Top = 112
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 7
  end
  object E5: TEdit
    Left = 472
    Top = 112
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 8
    Text = 'Edit1'
  end
  object T4: TStaticText
    Left = 376
    Top = 84
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 9
  end
  object E4: TEdit
    Left = 472
    Top = 84
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
    Text = 'Edit1'
  end
  object T3: TStaticText
    Left = 376
    Top = 56
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 11
  end
  object E3: TEdit
    Left = 472
    Top = 56
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
    Text = 'Edit1'
  end
  object T2: TStaticText
    Left = 376
    Top = 28
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 13
  end
  object E2: TEdit
    Left = 472
    Top = 28
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 14
    Text = 'Edit1'
  end
  object T1: TStaticText
    Left = 376
    Top = 0
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 15
  end
  object E1: TEdit
    Left = 472
    Top = 0
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 16
    Text = 'E1'
  end
  object StaticText5: TStaticText
    Left = 0
    Top = 140
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис для  пит. линии №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 17
  end
  object StaticText12: TStaticText
    Left = 0
    Top = 168
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. давление в пит. линии №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 18
  end
  object StaticText13: TStaticText
    Left = 0
    Top = 224
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис для  пит. линии №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 19
  end
  object StaticText14: TStaticText
    Left = 0
    Top = 196
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. давление в пит. линии №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 20
  end
  object StaticText15: TStaticText
    Left = 0
    Top = 252
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. давление пр.вода отоплен.: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 21
  end
  object T10: TStaticText
    Left = 376
    Top = 252
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 22
  end
  object E10: TEdit
    Left = 472
    Top = 252
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 23
    Text = 'Edit1'
  end
  object T9: TStaticText
    Left = 376
    Top = 224
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 24
  end
  object E9: TEdit
    Left = 472
    Top = 224
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 25
    Text = 'Edit1'
  end
  object T8: TStaticText
    Left = 376
    Top = 196
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 26
  end
  object E8: TEdit
    Left = 472
    Top = 196
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 27
    Text = 'Edit1'
  end
  object T7: TStaticText
    Left = 376
    Top = 168
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 28
  end
  object E7: TEdit
    Left = 472
    Top = 168
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 29
    Text = 'Edit1'
  end
  object T6: TStaticText
    Left = 376
    Top = 140
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 30
  end
  object E6: TEdit
    Left = 472
    Top = 140
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 31
  end
  object StaticText21: TStaticText
    Left = 0
    Top = 280
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. давление пр.вода отоплен.: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 32
  end
  object StaticText22: TStaticText
    Left = 0
    Top = 308
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис пр. воды отопления : '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 33
  end
  object StaticText23: TStaticText
    Left = 0
    Top = 364
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис давления подачи ГВС: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 34
  end
  object StaticText24: TStaticText
    Left = 0
    Top = 336
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Максималь. давление подачи ГВС:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 35
  end
  object StaticText25: TStaticText
    Left = 0
    Top = 392
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. давление пара в сепарат. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 36
  end
  object T15: TStaticText
    Left = 376
    Top = 392
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 37
  end
  object E15: TEdit
    Left = 472
    Top = 392
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 38
    Text = 'Edit1'
  end
  object T14: TStaticText
    Left = 376
    Top = 364
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 39
  end
  object E14: TEdit
    Left = 472
    Top = 364
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 40
    Text = 'Edit1'
  end
  object T13: TStaticText
    Left = 376
    Top = 336
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 41
  end
  object E13: TEdit
    Left = 472
    Top = 336
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 42
    Text = 'Edit1'
  end
  object T12: TStaticText
    Left = 376
    Top = 308
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 43
  end
  object E12: TEdit
    Left = 472
    Top = 308
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 44
    Text = 'Edit1'
  end
  object T11: TStaticText
    Left = 376
    Top = 280
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 45
  end
  object E11: TEdit
    Left = 472
    Top = 280
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 46
    Text = 'Edit1'
  end
  object StaticText31: TStaticText
    Left = 552
    Top = 0
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис дав. пара в сепар. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 47
  end
  object StaticText32: TStaticText
    Left = 552
    Top = 28
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. давление пара на гребенке:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 48
  end
  object StaticText33: TStaticText
    Left = 552
    Top = 84
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис дав. пара на греб. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 49
  end
  object StaticText34: TStaticText
    Left = 552
    Top = 56
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. давление пара на гребенке:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 50
  end
  object StaticText35: TStaticText
    Left = 552
    Top = 112
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. уровень в баке аккум. №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 51
  end
  object T20: TStaticText
    Left = 928
    Top = 112
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 52
  end
  object E20: TEdit
    Left = 1024
    Top = 112
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 53
    Text = 'Edit1'
  end
  object T19: TStaticText
    Left = 928
    Top = 84
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 54
  end
  object E19: TEdit
    Left = 1024
    Top = 84
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 55
    Text = 'Edit1'
  end
  object T18: TStaticText
    Left = 928
    Top = 56
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 56
  end
  object E18: TEdit
    Left = 1024
    Top = 56
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 57
    Text = 'Edit1'
  end
  object T17: TStaticText
    Left = 928
    Top = 28
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 58
  end
  object E17: TEdit
    Left = 1024
    Top = 28
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 59
    Text = 'Edit1'
  end
  object T16: TStaticText
    Left = 928
    Top = 0
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 60
  end
  object E16: TEdit
    Left = 1024
    Top = 0
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 61
    Text = 'Edit1'
  end
  object StaticText7: TStaticText
    Left = 552
    Top = 140
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. уровень в баке аккум. №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 62
  end
  object StaticText8: TStaticText
    Left = 552
    Top = 168
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис уровня в аккум. №1 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 63
  end
  object StaticText9: TStaticText
    Left = 552
    Top = 224
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. уровень в баке аккум. №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 64
  end
  object StaticText10: TStaticText
    Left = 552
    Top = 196
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. уровень в баке аккум. №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 65
  end
  object StaticText11: TStaticText
    Left = 552
    Top = 252
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис уровня в аккум. №2 :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 66
  end
  object T25: TStaticText
    Left = 928
    Top = 252
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 67
  end
  object E25: TEdit
    Left = 1023
    Top = 252
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 68
    Text = 'E25'
  end
  object T24: TStaticText
    Left = 928
    Top = 224
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 69
  end
  object E24: TEdit
    Left = 1023
    Top = 224
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 70
    Text = 'Edit1'
  end
  object T23: TStaticText
    Left = 928
    Top = 196
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 71
  end
  object E23: TEdit
    Left = 1023
    Top = 196
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 72
    Text = 'Edit1'
  end
  object T22: TStaticText
    Left = 928
    Top = 168
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 73
  end
  object E22: TEdit
    Left = 1023
    Top = 168
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 74
    Text = 'Edit1'
  end
  object T21: TStaticText
    Left = 928
    Top = 140
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 75
  end
  object E21: TEdit
    Left = 1023
    Top = 140
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 76
    Text = 'Edit1'
  end
  object StaticText26: TStaticText
    Left = 552
    Top = 280
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. уровень в сетевом деаэр. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 77
  end
  object StaticText27: TStaticText
    Left = 552
    Top = 308
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. уровень в сетевом деаэр. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 78
  end
  object StaticText28: TStaticText
    Left = 552
    Top = 364
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мак. уровень в питат.  деаэр. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 79
  end
  object StaticText29: TStaticText
    Left = 552
    Top = 336
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис уровня в сет.деаэр.:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 80
  end
  object StaticText30: TStaticText
    Left = 552
    Top = 392
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Мин. уровень в питат.  деаэр. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 81
  end
  object T30: TStaticText
    Left = 928
    Top = 392
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 82
  end
  object E30: TEdit
    Left = 1023
    Top = 392
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 83
    Text = 'Edit1'
  end
  object T29: TStaticText
    Left = 928
    Top = 364
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 84
  end
  object E29: TEdit
    Left = 1023
    Top = 364
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 85
    Text = 'Edit1'
  end
  object T28: TStaticText
    Left = 928
    Top = 336
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 86
  end
  object E28: TEdit
    Left = 1023
    Top = 336
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 87
    Text = 'Edit1'
  end
  object T27: TStaticText
    Left = 928
    Top = 308
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 88
  end
  object E27: TEdit
    Left = 1023
    Top = 308
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 89
    Text = 'Edit1'
  end
  object T26: TStaticText
    Left = 928
    Top = 280
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 90
  end
  object E26: TEdit
    Left = 1023
    Top = 280
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 91
    Text = 'Edit1'
  end
  object StaticText17: TStaticText
    Left = 552
    Top = 420
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = 'Гистерезис уровня в пит.деаэр.:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 92
  end
  object T31: TStaticText
    Left = 928
    Top = 420
    Width = 97
    Height = 28
    Alignment = taCenter
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '0.0'
    Color = clBlack
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clLime
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 93
  end
  object E31: TEdit
    Left = 1023
    Top = 420
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 94
    Text = 'Edit1'
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 664
    Top = 208
  end
end
