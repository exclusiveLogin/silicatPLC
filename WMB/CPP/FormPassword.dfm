object FPassword: TFPassword
  Left = 565
  Top = 319
  BorderStyle = bsDialog
  Caption = '������� ������ �������'
  ClientHeight = 50
  ClientWidth = 273
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
    Left = 0
    Top = 0
    Width = 273
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object BitBtn1: TBitBtn
    Left = 1
    Top = 24
    Width = 75
    Height = 25
    Caption = '����'
    TabOrder = 1
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 197
    Top = 24
    Width = 75
    Height = 25
    Caption = '������'
    TabOrder = 2
    Kind = bkCancel
  end
end
