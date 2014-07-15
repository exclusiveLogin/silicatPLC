object Form1: TForm1
  Left = 817
  Top = 109
  Width = 166
  Height = 112
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
  object ClientSocket1: TClientSocket
    Active = False
    Address = '192.168.201.230'
    ClientType = ctNonBlocking
    Port = 10000
    OnLookup = ClientSocket1Lookup
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnWrite = ClientSocket1Write
  end
  object Timer1: TTimer
    Interval = 150
    OnTimer = Timer1Timer
    Top = 32
  end
  object DSListTag: TDataSource
    DataSet = QListTags
    Left = 40
  end
  object ConArhiv: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 72
  end
  object QListTags: TADOQuery
    Connection = ConArhiv
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags ORDER BY IDTag')
    Left = 104
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
    object QListTagsExtParam3: TIntegerField
      FieldName = 'ExtParam3'
    end
    object QListTagsNumEkran: TIntegerField
      FieldName = 'NumEkran'
    end
    object QListTagsTypeArhiv: TIntegerField
      FieldName = 'TypeArhiv'
    end
    object QListTagsUslWrite: TIntegerField
      FieldName = 'UslWrite'
    end
    object QListTagsUslAvar: TIntegerField
      FieldName = 'UslAvar'
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
  end
  object DSArhivSob: TDataSource
    DataSet = QArhivSob
    Left = 40
    Top = 32
  end
  object ConArhivSob: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 72
    Top = 32
  end
  object QArhivSob: TADOQuery
    Connection = ConArhivSob
    Parameters = <>
    SQL.Strings = (
      'select * from ListSob ORDER BY DTSob DESC, IDSob')
    Left = 104
    Top = 32
    object QArhivSobIDSob: TIntegerField
      FieldName = 'IDSob'
    end
    object QArhivSobDTSob: TDateTimeField
      FieldName = 'DTSob'
    end
    object QArhivSobIDTag: TIntegerField
      FieldName = 'IDTag'
    end
    object QArhivSobVal: TIntegerField
      FieldName = 'Val'
    end
    object QArhivSobActive: TBooleanField
      FieldName = 'Active'
    end
    object QArhivSobKvitirov: TBooleanField
      FieldName = 'Kvitirov'
    end
    object QArhivSobActive1: TBooleanField
      FieldName = 'Active1'
    end
    object QArhivSobDlit: TDateTimeField
      FieldName = 'Dlit'
    end
  end
end
