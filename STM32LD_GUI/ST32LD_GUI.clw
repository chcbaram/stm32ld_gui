; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CST32LD_GUIDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ST32LD_GUI.h"

ClassCount=3
Class1=CST32LD_GUIApp
Class2=CST32LD_GUIDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ST32LD_GUI_DIALOG

[CLS:CST32LD_GUIApp]
Type=0
HeaderFile=ST32LD_GUI.h
ImplementationFile=ST32LD_GUI.cpp
Filter=N

[CLS:CST32LD_GUIDlg]
Type=0
HeaderFile=ST32LD_GUIDlg.h
ImplementationFile=ST32LD_GUIDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_COMBO_BOARD

[CLS:CAboutDlg]
Type=0
HeaderFile=ST32LD_GUIDlg.h
ImplementationFile=ST32LD_GUIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ST32LD_GUI_DIALOG]
Type=1
Class=CST32LD_GUIDlg
ControlCount=13
Control1=IDC_LIST_DEBUG,SysListView32,1350631425
Control2=IDC_STATIC,button,1342177287
Control3=IDC_COMBO_COMPORT,combobox,1344339970
Control4=IDC_BUTTON_OPEN,button,1073807360
Control5=IDC_STATIC,button,1342177287
Control6=IDC_BUTTON_UPDATE,button,1342242816
Control7=IDC_BUTTON_DOWN_BOOT,button,1342242816
Control8=IDC_BUTTON_DOWN_FIRM,button,1342242816
Control9=IDC_CHECK_AUTO_BOOT,button,1073807363
Control10=IDC_STATIC,button,1342177287
Control11=IDC_BUTTON_WRITE_UNPROTECT,button,1073807360
Control12=IDC_STATIC,button,1342177287
Control13=IDC_COMBO_BOARD,combobox,1344339970

