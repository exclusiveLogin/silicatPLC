object FEnterShkal: TFEnterShkal
  Left = 131
  Top = 159
  Width = 556
  Height = 110
  Caption = '������� ____. ����� ����������� �������.'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
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
    TabOrder = 0
    Text = 'Edit1'
  end
  object StaticText7: TStaticText
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
    TabOrder = 1
  end
  object StaticText1: TStaticText
    Left = 0
    Top = 0
    Width = 376
    Height = 28
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '�������� ����� - 4 ��         :'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object StaticText2: TStaticText
    Left = 0
    Top = 28
    Width = 376
    Height = 27
    AutoSize = False
    BorderStyle = sbsSunken
    Caption = '�������� ����� - 20 ��        : '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
  end
  object StaticText8: TStaticText
    Left = 376
    Top = 28
    Width = 97
    Height = 27
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
    TabOrder = 4
  end
  object Edit2: TEdit
    Left = 472
    Top = 27
    Width = 76
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -17
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    Text = 'Edit1'
  end
  object BitBtn1: TBitBtn
    Left = 0
    Top = 56
    Width = 225
    Height = 25
    Caption = '���������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 320
    Top = 56
    Width = 225
    Height = 25
    Caption = '������'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    Kind = bkCancel
  end
end