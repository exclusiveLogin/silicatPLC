object Form1: TForm1
  Left = 120
  Top = 117
  Width = 1088
  Height = 563
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 296
    Top = 184
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object DS1: TDataSource
    DataSet = Q1
    Left = 216
    Top = 32
  end
  object Con1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 336
    Top = 32
  end
  object Q1: TADOQuery
    Connection = Con1
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags')
    Left = 264
    Top = 32
    object Q1IDTag: TIntegerField
      FieldName = 'IDTag'
    end
    object Q1NameTag: TWideStringField
      FieldName = 'NameTag'
      Size = 50
    end
    object Q1CaptionTag: TWideStringField
      FieldName = 'CaptionTag'
      Size = 255
    end
    object Q1ValueTag: TFloatField
      FieldName = 'ValueTag'
    end
    object Q1StatusTag: TIntegerField
      FieldName = 'StatusTag'
    end
    object Q1TypeOpros: TWideStringField
      FieldName = 'TypeOpros'
      Size = 255
    end
    object Q1Param1: TWideStringField
      FieldName = 'Param1'
      Size = 255
    end
    object Q1Param2: TWideStringField
      FieldName = 'Param2'
      Size = 255
    end
    object Q1Param3: TWideStringField
      FieldName = 'Param3'
      Size = 255
    end
    object Q1TypeValue: TIntegerField
      FieldName = 'TypeValue'
    end
    object Q1NumEkran: TIntegerField
      FieldName = 'NumEkran'
    end
    object Q1TypeVisibleElement: TIntegerField
      FieldName = 'TypeVisibleElement'
    end
    object Q1VisParam1: TWideStringField
      FieldName = 'VisParam1'
      Size = 30
    end
    object Q1VisParam2: TWideStringField
      FieldName = 'VisParam2'
      Size = 30
    end
    object Q1MinVal: TFloatField
      FieldName = 'MinVal'
    end
    object Q1MaxVal: TFloatField
      FieldName = 'MaxVal'
    end
    object Q1MinValIn: TFloatField
      FieldName = 'MinValIn'
    end
    object Q1MaxValIn: TFloatField
      FieldName = 'MaxValIn'
    end
    object Q1ExtParam3: TIntegerField
      FieldName = 'ExtParam3'
    end
    object Q1NameContr: TWideStringField
      FieldName = 'NameContr'
      Size = 50
    end
    object Q1NameModul: TWideStringField
      FieldName = 'NameModul'
      Size = 50
    end
    object Q1NumEnter: TWideStringField
      FieldName = 'NumEnter'
      Size = 50
    end
    object Q1TypeArhiv: TIntegerField
      FieldName = 'TypeArhiv'
    end
    object Q1UslWrite: TIntegerField
      FieldName = 'UslWrite'
    end
    object Q1UslAvar: TIntegerField
      FieldName = 'UslAvar'
    end
    object Q1VisParam3: TIntegerField
      FieldName = 'VisParam3'
    end
    object Q1VisParam4: TIntegerField
      FieldName = 'VisParam4'
    end
    object Q1TypeVisibleArhiv: TIntegerField
      FieldName = 'TypeVisibleArhiv'
    end
  end
  object DSSource: TDataSource
    DataSet = QSource
    Left = 416
    Top = 40
  end
  object QSource: TADOQuery
    Connection = ConSource
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags where IDTag>1000')
    Left = 464
    Top = 40
    object QSourceIDTag: TIntegerField
      FieldName = 'IDTag'
    end
    object QSourceNameTag: TWideStringField
      FieldName = 'NameTag'
      Size = 50
    end
    object QSourceCaptionTag: TWideStringField
      FieldName = 'CaptionTag'
      Size = 255
    end
    object QSourceValueTag: TFloatField
      FieldName = 'ValueTag'
    end
    object QSourceStatusTag: TIntegerField
      FieldName = 'StatusTag'
    end
    object QSourceTypeOpros: TWideStringField
      FieldName = 'TypeOpros'
      Size = 255
    end
    object QSourceParam1: TWideStringField
      FieldName = 'Param1'
      Size = 255
    end
    object QSourceParam2: TWideStringField
      FieldName = 'Param2'
      Size = 255
    end
    object QSourceParam3: TWideStringField
      FieldName = 'Param3'
      Size = 255
    end
    object QSourceTypeValue: TIntegerField
      FieldName = 'TypeValue'
    end
    object QSourceNumEkran: TIntegerField
      FieldName = 'NumEkran'
    end
    object QSourceTypeVisibleElement: TIntegerField
      FieldName = 'TypeVisibleElement'
    end
    object QSourceVisParam1: TWideStringField
      FieldName = 'VisParam1'
      Size = 30
    end
    object QSourceVisParam2: TWideStringField
      FieldName = 'VisParam2'
      Size = 30
    end
    object QSourceMinVal: TFloatField
      FieldName = 'MinVal'
    end
    object QSourceMaxVal: TFloatField
      FieldName = 'MaxVal'
    end
    object QSourceMinValIn: TFloatField
      FieldName = 'MinValIn'
    end
    object QSourceMaxValIn: TFloatField
      FieldName = 'MaxValIn'
    end
    object QSourceExtParam3: TIntegerField
      FieldName = 'ExtParam3'
    end
    object QSourceNameContr: TWideStringField
      FieldName = 'NameContr'
      Size = 50
    end
    object QSourceNameModul: TWideStringField
      FieldName = 'NameModul'
      Size = 50
    end
    object QSourceNumEnter: TWideStringField
      FieldName = 'NumEnter'
      Size = 50
    end
    object QSourceTypeArhiv: TIntegerField
      FieldName = 'TypeArhiv'
    end
    object QSourceUslWrite: TIntegerField
      FieldName = 'UslWrite'
    end
    object QSourceUslAvar: TIntegerField
      FieldName = 'UslAvar'
    end
    object QSourceVisParam3: TIntegerField
      FieldName = 'VisParam3'
    end
    object QSourceVisParam4: TIntegerField
      FieldName = 'VisParam4'
    end
    object QSourceTypeVisibleArhiv: TIntegerField
      FieldName = 'TypeVisibleArhiv'
    end
  end
  object ConSource: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\MyProjects\WMB\P' +
      'RJ\Arhiv1.mdb;Persist Security Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 536
    Top = 40
  end
end
