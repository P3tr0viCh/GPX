object Main: TMain
  Left = 0
  Top = 0
  Caption = 'GPX'
  ClientHeight = 379
  ClientWidth = 576
  Color = clBtnFace
  Constraints.MinHeight = 418
  Constraints.MinWidth = 592
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 17
  object PanelTop: TPanel
    Left = 0
    Top = 0
    Width = 576
    Height = 48
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 635
    DesignSize = (
      576
      48)
    object btnClose: TButton
      Left = 488
      Top = 8
      Width = 80
      Height = 32
      Anchors = [akTop, akRight]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      TabOrder = 0
      OnClick = btnCloseClick
    end
    object btnOpen: TButton
      Left = 8
      Top = 8
      Width = 80
      Height = 32
      Caption = #1054#1090#1082#1088#1099#1090#1100
      TabOrder = 1
      OnClick = btnOpenClick
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 355
    Width = 576
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Panels = <>
    SimplePanel = True
    UseSystemFont = False
    ExplicitTop = 405
    ExplicitWidth = 695
  end
  object ListBox: TListBox
    Left = 0
    Top = 48
    Width = 576
    Height = 211
    Align = alClient
    ItemHeight = 17
    TabOrder = 2
    ExplicitLeft = 192
    ExplicitTop = 152
    ExplicitWidth = 121
    ExplicitHeight = 97
  end
  object PanelBottom: TPanel
    Left = 0
    Top = 259
    Width = 576
    Height = 96
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 297
    ExplicitWidth = 695
    object gbDistance: TGroupBox
      Left = 8
      Top = 8
      Width = 560
      Height = 80
      Caption = #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077
      TabOrder = 0
      object eHaversine: TLabeledEdit
        Left = 8
        Top = 40
        Width = 120
        Height = 25
        Color = clBtnFace
        EditLabel.Width = 67
        EditLabel.Height = 17
        EditLabel.Caption = #1043#1072#1074#1077#1088#1089#1080#1085#1091#1089
        ReadOnly = True
        TabOrder = 0
      end
      object eEquirectangular: TLabeledEdit
        Left = 136
        Top = 40
        Width = 200
        Height = 25
        Color = clBtnFace
        EditLabel.Width = 192
        EditLabel.Height = 17
        EditLabel.Caption = #1056#1072#1074#1085#1086#1087#1088#1086#1084#1077#1078#1091#1090#1086#1095#1085#1072#1103' '#1087#1088#1086#1077#1082#1094#1080#1103
        ReadOnly = True
        TabOrder = 1
      end
      object eSphericalLawOfCosines: TLabeledEdit
        Left = 344
        Top = 40
        Width = 208
        Height = 25
        Color = clBtnFace
        EditLabel.Width = 199
        EditLabel.Height = 17
        EditLabel.Caption = #1057#1092#1077#1088#1080#1095#1077#1089#1082#1072#1103' '#1090#1077#1086#1088#1077#1084#1072' '#1082#1086#1089#1080#1085#1091#1089#1086#1074
        ReadOnly = True
        TabOrder = 2
      end
    end
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'gpx'
    Filter = 'GPX|*.gpx|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 312
    Top = 144
  end
end
