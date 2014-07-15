object FPEcho: TFPEcho
  Left = 540
  Top = 383
  Width = 343
  Height = 199
  Caption = 'FPEcho'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object SSocket: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnClientConnect = SSocketClientConnect
    OnClientRead = SSocketClientRead
  end
  object DSListTags: TDataSource
    DataSet = QListTags
    Left = 64
  end
  object QListTags: TADOQuery
    Connection = ConArhiv
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags'
      'ORDER BY IDTag')
    Left = 96
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
      'Provider=Microsoft.Jet.OLEDB.4.0;User ID=Admin;Data Source=Arhiv' +
      '.mdb;Mode=Read;Jet OLEDB:System database="";Jet OLEDB:Registry P' +
      'ath="";Jet OLEDB:Database Password="";Jet OLEDB:Engine Type=5;Je' +
      't OLEDB:Database Locking Mode=0;Jet OLEDB:Global Partial Bulk Op' +
      's=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database ' +
      'Password="";Jet OLEDB:Create System Database=False;Jet OLEDB:Enc' +
      'rypt Database=False;Jet OLEDB:Don'#39't Copy Locale on Compact=False' +
      ';Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=Fa' +
      'lse;'
    LoginPrompt = False
    Mode = cmRead
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 128
  end
end
