object FBlok: TFBlok
  Left = 122
  Top = 236
  Width = 1348
  Height = 612
  Caption = '����������:'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object StaticText1: TStaticText
    Left = 0
    Top = 41
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ����� �  ���1          :'
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
    Top = 69
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� PI1             :'
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
    Top = 125
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� DPI3            :'
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
    Top = 97
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� PI2             :'
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
    Top = 153
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� LI2             :'
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
    Top = 555
    Width = 225
    Height = 25
    Caption = '���������'
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
    Left = 1018
    Top = 556
    Width = 225
    Height = 25
    Caption = '������� ���� '
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
    Top = 153
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
    Top = 153
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
    Top = 125
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
    Top = 125
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
    Top = 97
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
    Top = 97
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
    Top = 69
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
    Top = 69
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
    Top = 41
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
    Top = 41
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
    Top = 181
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ����� � ���4           :'
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
    Top = 209
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� DI6             :'
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
    Top = 265
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ����� � ���5           :'
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
    Top = 237
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����� ������� DI16            :'
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
    Top = 293
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ����� � ���6           : '
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
    Top = 293
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
    Top = 293
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
    Top = 265
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
    Top = 265
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
    Top = 237
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
    Top = 237
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
    Top = 209
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
    Top = 209
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
    Top = 181
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
    Top = 181
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
    Top = 321
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������� ���� ����� ���. ����. : '
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
    Top = 349
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������. ������� ������ AV1: '
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
    Top = 405
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������. ������� ������ AV3: '
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
    Top = 377
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������. ������� ������ AV2:'
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
    Top = 433
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������� ������� ��� ���. ����.:'
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
    Top = 433
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
    Top = 433
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
    Top = 405
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
    Top = 405
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
    Top = 377
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
    Top = 377
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
    Top = 349
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
    Top = 349
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
    Top = 321
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
    Top = 321
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
    Left = 0
    Top = 461
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '��� �������, �������� ������� :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 47
  end
  object StaticText32: TStaticText
    Left = 0
    Top = 489
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '��� �������,�������� ���������:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 48
  end
  object StaticText33: TStaticText
    Left = 679
    Top = 41
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������������ �������� ����    : '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 49
  end
  object StaticText34: TStaticText
    Left = 0
    Top = 517
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������� �������� ����     :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 50
  end
  object StaticText35: TStaticText
    Left = 679
    Top = 69
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '�������� ������., ����. �����.:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 51
  end
  object T20: TStaticText
    Left = 1053
    Top = 69
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
    Left = 1151
    Top = 69
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
    Left = 1053
    Top = 41
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
    Left = 1151
    Top = 41
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
    Left = 376
    Top = 517
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
    Left = 472
    Top = 517
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
    Left = 376
    Top = 489
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
    Left = 472
    Top = 489
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
    Left = 376
    Top = 461
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
    Left = 472
    Top = 461
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
    Left = 679
    Top = 97
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������� �������� �������  :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 62
  end
  object StaticText8: TStaticText
    Left = 679
    Top = 125
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '���. �������� ������� ��� ���.:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 63
  end
  object StaticText9: TStaticText
    Left = 679
    Top = 181
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������������ �������� ����    :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 64
  end
  object StaticText10: TStaticText
    Left = 679
    Top = 153
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '����������� ����������        :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 65
  end
  object StaticText11: TStaticText
    Left = 679
    Top = 209
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '���. ������� � �������� ����� :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 66
  end
  object T25: TStaticText
    Left = 1053
    Top = 209
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
    Left = 1150
    Top = 209
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
    Left = 1053
    Top = 181
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
    Left = 1150
    Top = 181
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
    Left = 1053
    Top = 153
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
    Left = 1150
    Top = 153
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
    Left = 1053
    Top = 125
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
    Left = 1150
    Top = 125
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
    Left = 1053
    Top = 97
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
    Left = 1150
    Top = 97
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
    Left = 679
    Top = 237
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '���. ������� � �������� ����� :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 77
  end
  object StaticText27: TStaticText
    Left = 679
    Top = 265
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '�������������� �� 2-�� �����  :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 78
  end
  object StaticText28: TStaticText
    Left = 679
    Top = 321
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '�������� � �����              :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 79
  end
  object StaticText29: TStaticText
    Left = 679
    Top = 293
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '���������� ����������������   :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 80
  end
  object StaticText30: TStaticText
    Left = 679
    Top = 349
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ������ ����            :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 81
  end
  object T30: TStaticText
    Left = 1053
    Top = 349
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
    Left = 1150
    Top = 349
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
    Left = 1053
    Top = 321
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
    Left = 1150
    Top = 321
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
    Left = 1053
    Top = 293
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
    Left = 1150
    Top = 293
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
    Left = 1053
    Top = 265
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
    Left = 1150
    Top = 265
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
    Left = 1053
    Top = 237
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
    Left = 1150
    Top = 237
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
    Left = 679
    Top = 377
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '���������� ������� ��������   :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 92
  end
  object T31: TStaticText
    Left = 1053
    Top = 377
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
    Left = 1150
    Top = 377
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
  object StaticText16: TStaticText
    Left = 677
    Top = 405
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ��� ����., ���������   :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 95
  end
  object StaticText18: TStaticText
    Left = 677
    Top = 433
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ��� ����., ����������  :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 96
  end
  object T33: TStaticText
    Left = 1053
    Top = 433
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
    TabOrder = 97
  end
  object E33: TEdit
    Left = 1149
    Top = 433
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 98
    Text = 'E33'
  end
  object T32: TStaticText
    Left = 1053
    Top = 405
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
    TabOrder = 99
  end
  object E32: TEdit
    Left = 1149
    Top = 405
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 100
  end
  object StaticText36: TStaticText
    Left = 677
    Top = 461
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ��� ���., ���������    :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 101
  end
  object StaticText37: TStaticText
    Left = 677
    Top = 489
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ��� ���., ����������   :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 102
  end
  object StaticText38: TStaticText
    Left = 677
    Top = 517
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '������ ��� ����., ����������. :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 103
  end
  object T36: TStaticText
    Left = 1053
    Top = 517
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
    TabOrder = 104
  end
  object E36: TEdit
    Left = 1149
    Top = 517
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 105
    Text = 'Edit1'
  end
  object T35: TStaticText
    Left = 1053
    Top = 489
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
    TabOrder = 106
  end
  object E35: TEdit
    Left = 1149
    Top = 489
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 107
    Text = 'Edit1'
  end
  object T34: TStaticText
    Left = 1053
    Top = 461
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
    TabOrder = 108
  end
  object E34: TEdit
    Left = 1149
    Top = 461
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 109
    Text = 'Edit1'
  end
  object StaticText42: TStaticText
    Left = 152
    Top = 8
    Width = 134
    Height = 27
    Caption = '����������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 110
  end
  object StaticText43: TStaticText
    Left = 400
    Top = 8
    Width = 108
    Height = 27
    Caption = '��������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 111
  end
  object StaticText44: TStaticText
    Left = 557
    Top = 8
    Width = 108
    Height = 27
    Caption = '���/����'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 112
  end
  object StaticText45: TStaticText
    Left = 812
    Top = 8
    Width = 134
    Height = 27
    Caption = '����������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 113
  end
  object StaticText46: TStaticText
    Left = 1060
    Top = 8
    Width = 108
    Height = 27
    Caption = '��������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 114
  end
  object StaticText47: TStaticText
    Left = 1229
    Top = 8
    Width = 108
    Height = 27
    Caption = '���/����'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 115
  end
  object Panel1: TPanel
    Left = 552
    Top = 41
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 116
    object SpeedButton1: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton2: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel2: TPanel
    Left = 552
    Top = 69
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 117
    object SpeedButton3: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton4: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel3: TPanel
    Left = 552
    Top = 97
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 118
    object SpeedButton5: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton6: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel4: TPanel
    Left = 551
    Top = 125
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 119
    object SpeedButton7: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton8: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel5: TPanel
    Left = 552
    Top = 153
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 120
    object SpeedButton9: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton10: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel6: TPanel
    Left = 552
    Top = 181
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 121
    object SpeedButton11: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton12: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel7: TPanel
    Left = 552
    Top = 209
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 122
    object SpeedButton13: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton14: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel8: TPanel
    Left = 551
    Top = 237
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 123
    object SpeedButton15: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton16: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel9: TPanel
    Left = 552
    Top = 265
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 124
    object SpeedButton17: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton18: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel10: TPanel
    Left = 552
    Top = 293
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 125
    object SpeedButton19: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton20: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel11: TPanel
    Left = 552
    Top = 321
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 126
    object SpeedButton21: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton22: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel12: TPanel
    Left = 551
    Top = 349
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 127
    object SpeedButton23: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton24: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel13: TPanel
    Left = 552
    Top = 377
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 128
    object SpeedButton25: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton26: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel14: TPanel
    Left = 552
    Top = 405
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 129
    object SpeedButton27: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton28: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel15: TPanel
    Left = 552
    Top = 433
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 130
    object SpeedButton29: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton30: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel16: TPanel
    Left = 551
    Top = 461
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 131
    object SpeedButton31: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton32: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel17: TPanel
    Left = 552
    Top = 489
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 132
    object SpeedButton33: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton34: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel18: TPanel
    Left = 552
    Top = 517
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 133
    object SpeedButton35: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton36: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel19: TPanel
    Left = 1232
    Top = 41
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 134
    object SpeedButton37: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton38: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel20: TPanel
    Left = 1232
    Top = 69
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 135
    object SpeedButton39: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton40: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel21: TPanel
    Left = 1232
    Top = 97
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 136
    object SpeedButton41: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton42: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel22: TPanel
    Left = 1231
    Top = 125
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 137
    object SpeedButton43: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton44: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel23: TPanel
    Left = 1232
    Top = 153
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 138
    object SpeedButton45: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton46: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel24: TPanel
    Left = 1232
    Top = 181
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 139
    object SpeedButton47: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton48: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel25: TPanel
    Left = 1232
    Top = 209
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 140
    object SpeedButton49: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton50: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel26: TPanel
    Left = 1231
    Top = 237
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 141
    object SpeedButton51: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton52: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel27: TPanel
    Left = 1232
    Top = 265
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 142
    object SpeedButton53: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton54: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel28: TPanel
    Left = 1232
    Top = 293
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 143
    object SpeedButton55: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton56: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel29: TPanel
    Left = 1232
    Top = 321
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 144
    object SpeedButton57: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton58: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel30: TPanel
    Left = 1231
    Top = 349
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 145
    object SpeedButton59: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton60: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel31: TPanel
    Left = 1232
    Top = 377
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 146
    object SpeedButton61: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton62: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel32: TPanel
    Left = 1232
    Top = 405
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 147
    object SpeedButton63: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton64: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel33: TPanel
    Left = 1232
    Top = 433
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 148
    object SpeedButton65: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton66: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel34: TPanel
    Left = 1231
    Top = 461
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 149
    object SpeedButton67: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton68: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel35: TPanel
    Left = 1232
    Top = 489
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 150
    object SpeedButton69: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton70: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Panel36: TPanel
    Left = 1232
    Top = 517
    Width = 105
    Height = 28
    BevelOuter = bvNone
    TabOrder = 151
    object SpeedButton71: TSpeedButton
      Left = 2
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Down = True
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton72: TSpeedButton
      Left = 53
      Top = 4
      Width = 50
      Height = 22
      GroupIndex = 1
      Caption = '���.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -20
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object L1: TStaticText
    Left = 231
    Top = 554
    Width = 28
    Height = 27
    BorderStyle = sbsSunken
    Caption = 'L1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 152
    Visible = False
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = Timer1Timer
    Left = 664
    Top = 165
  end
end