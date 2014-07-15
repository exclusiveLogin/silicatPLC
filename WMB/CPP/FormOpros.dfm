object FOpros: TFOpros
  Left = 495
  Top = 210
  Width = 519
  Height = 252
  Caption = 'Опрос по протоколу Modbus'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object DSListTag: TDataSource
    DataSet = QListTags
    Left = 208
    Top = 56
  end
  object ConArhiv: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 240
    Top = 56
  end
  object QListTags: TADOQuery
    Connection = ConArhiv
    Parameters = <>
    SQL.Strings = (
      'select * from ListTags ORDER BY IDTag')
    Left = 272
    Top = 56
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
    Left = 208
    Top = 88
  end
  object ConArhivSob: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Arhiv.mdb;Persist S' +
      'ecurity Info=False;'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 240
    Top = 88
  end
  object QArhivSob: TADOQuery
    Connection = ConArhivSob
    Parameters = <>
    SQL.Strings = (
      'select * from ListSob ORDER BY DTSob DESC, IDSob')
    Left = 272
    Top = 88
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
  object Timer1: TTimer
    Interval = 150
    OnTimer = Timer1Timer
    Left = 208
    Top = 16
  end
  object ClientSocket1: TClientSocket
    Active = False
    Address = '192.168.201.111'
    ClientType = ctNonBlocking
    Port = 502
    OnLookup = ClientSocket1Lookup
    OnConnecting = ClientSocket1Connecting
    OnConnect = ClientSocket1Connect
    OnDisconnect = ClientSocket1Disconnect
    OnRead = ClientSocket1Read
    OnWrite = ClientSocket1Write
    OnError = ClientSocket1Error
    Left = 88
    Top = 24
  end
  object ClientSocket2: TClientSocket
    Active = False
    Address = '192.168.201.200'
    ClientType = ctNonBlocking
    Port = 502
    OnConnect = ClientSocket2Connect
    OnRead = ClientSocket2Read
    OnError = ClientSocket2Error
    Left = 88
    Top = 64
  end
  object ClientSocket3: TClientSocket
    Active = False
    Address = '192.168.201.113'
    ClientType = ctNonBlocking
    Port = 502
    OnConnect = ClientSocket3Connect
    OnRead = ClientSocket3Read
    OnError = ClientSocket3Error
    Left = 88
    Top = 100
  end
  object ClientSocket4: TClientSocket
    Active = False
    Address = '192.168.201.114'
    ClientType = ctNonBlocking
    Port = 502
    OnConnect = ClientSocket4Connect
    OnRead = ClientSocket4Read
    OnError = ClientSocket4Error
    Left = 88
    Top = 140
  end
end
