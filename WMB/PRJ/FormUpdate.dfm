object FUpdate: TFUpdate
  Left = 2
  Top = 111
  Width = 1305
  Height = 675
  Caption = 'FUpdate'
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
    Left = 344
    Top = 72
    Width = 201
    Height = 25
    Caption = '�������� ����'
    TabOrder = 0
    OnClick = Button1Click
  end
  object DSListTags: TDataSource
    DataSet = QListTags
    Left = 56
    Top = 52
  end
  object QListTags: TADOQuery
    Connection = ConArhiv
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags')
    Left = 88
    Top = 52
    object QListTagsIDTag: TIntegerField
      FieldName = 'IDTag'
    end
    object QListTagsNameTag: TWideStringField
      FieldName = 'NameTag'
      Size = 50
    end
    object QListTagsCaptionTag: TWideStringField
      FieldName = 'CaptionTag'
      Size = 255
    end
    object QListTagsValueTag: TFloatField
      FieldName = 'ValueTag'
    end
    object QListTagsStatusTag: TIntegerField
      FieldName = 'StatusTag'
    end
    object QListTagsTypeOpros: TWideStringField
      FieldName = 'TypeOpros'
      Size = 255
    end
    object QListTagsParam1: TWideStringField
      FieldName = 'Param1'
      Size = 255
    end
    object QListTagsParam2: TWideStringField
      FieldName = 'Param2'
      Size = 255
    end
    object QListTagsParam3: TWideStringField
      FieldName = 'Param3'
      Size = 255
    end
    object QListTagsTypeValue: TIntegerField
      FieldName = 'TypeValue'
    end
    object QListTagsNumEkran: TIntegerField
      FieldName = 'NumEkran'
    end
    object QListTagsTypeVisibleElement: TIntegerField
      FieldName = 'TypeVisibleElement'
    end
    object QListTagsVisParam1: TWideStringField
      FieldName = 'VisParam1'
      Size = 30
    end
    object QListTagsVisParam2: TWideStringField
      FieldName = 'VisParam2'
      Size = 30
    end
    object QListTagsMinVal: TFloatField
      FieldName = 'MinVal'
    end
    object QListTagsMaxVal: TFloatField
      FieldName = 'MaxVal'
    end
    object QListTagsMinValIn: TFloatField
      FieldName = 'MinValIn'
    end
    object QListTagsMaxValIn: TFloatField
      FieldName = 'MaxValIn'
    end
    object QListTagsVisParam3: TIntegerField
      FieldName = 'VisParam3'
    end
    object QListTagsVisParam4: TIntegerField
      FieldName = 'VisParam4'
    end
    object QListTagsTypeVisibleArhiv: TIntegerField
      FieldName = 'TypeVisibleArhiv'
    end
    object QListTagsTypeArhiv: TIntegerField
      FieldName = 'TypeArhiv'
    end
    object QListTagsUslAvar: TIntegerField
      FieldName = 'UslAvar'
    end
  end
  object ConArhiv: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 120
    Top = 52
  end
end
