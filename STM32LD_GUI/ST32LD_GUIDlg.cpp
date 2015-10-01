// ST32LD_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ST32LD_GUI.h"
#include "ST32LD_GUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CST32LD_GUIDlg *pDlg;


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CST32LD_GUIDlg dialog

CST32LD_GUIDlg::CST32LD_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CST32LD_GUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CST32LD_GUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CST32LD_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CST32LD_GUIDlg)
	DDX_Control(pDX, IDC_COMBO_BOARD, m_ctrlBoard);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_comboCOM);
	DDX_Control(pDX, IDC_LIST_DEBUG, m_listLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CST32LD_GUIDlg, CDialog)
	//{{AFX_MSG_MAP(CST32LD_GUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DOWN_BOOT, OnButtonDownBoot)
	ON_BN_CLICKED(IDC_BUTTON_DOWN_FIRM, OnButtonDownFirm)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_WRITE_UNPROTECT, OnButtonWriteUnprotect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CST32LD_GUIDlg message handlers

BOOL CST32LD_GUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Print_LogTitle();

	fp = NULL;
	UART_Opened = FALSE;
	FILE_Opened = FALSE;

	
	m_ctrlBoard.SetCurSel(0);


	//m_comboCOM.GetCurSel();

	pDlg = this;

	((CButton *)GetDlgItem(IDC_CHECK_AUTO_BOOT))->SetCheck(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CST32LD_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CST32LD_GUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CST32LD_GUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CST32LD_GUIDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE)) 
	{ 
		return TRUE; 
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CST32LD_GUIDlg::Print_LogTitle(void)
{
	m_listLog.DeleteAllItems();

	m_listLog.InsertColumn( 0,"Log", 0,1000 );
}

void CST32LD_GUIDlg::Print_Log(CString str)
{
	int last_index = m_listLog.GetItemCount();

	m_listLog.InsertItem( last_index, str );

	m_listLog.EnsureVisible(m_listLog.GetItemCount()-1, FALSE);
}

void CST32LD_GUIDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	
}

void CST32LD_GUIDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if( fp != NULL ) 
	{
		fclose(fp);
	}
}

u32 CST32LD_GUIDlg::writeh_read_data( u8 *dst, u32 len )
{
  size_t readbytes = 0;

  if( !feof( pDlg->fp ) )
    readbytes = fread( dst, 1, len, pDlg->fp );
  return ( u32 )readbytes;
}

// Progress function
void CST32LD_GUIDlg::writeh_progress( u32 wrote )
{
  unsigned pwrite = ( wrote * 100 ) / pDlg->fpsize;

  if( pwrite >= pDlg->expected_next )
  {
    pDlg->dbg_printf( "%d%% ", pDlg->expected_next );
    pDlg->expected_next += 10;
  }
}

void CST32LD_GUIDlg::COM_Update( void )
{
	char port_name[100];
	int i;
	int list_cnt = 0;
	ser_handler hPort;
	CString str;


	stm32_close();


	//-- COM 리스트 Clear
	list_cnt = m_comboCOM.GetCount();

	for( i=0; i<list_cnt; i++ )
	{
		m_comboCOM.DeleteString(0);
	}

	UART_Opened = FALSE;


	list_cnt = 0;

	for( i=1; i<=32; i++ )
	{
		sprintf( port_name, "COM%d", i );

		hPort = ser_open( port_name );

		if( hPort == WIN_ERROR )
		{
			//-- COM 포트가 없으면 다음 포트로 이동 
			continue;
		}
		else
		{
			//-- COM 포트가 있으면 리스트에 추가 
			m_comboCOM.AddString(port_name);
			m_comboCOM.SetCurSel(0);

			dbg_printf("%s Found ", port_name);
			ser_close(hPort);

			list_cnt++;
		}
	}

	if( list_cnt > 0 )
	{
		UART_Opened = TRUE;
	}
		
}

void CST32LD_GUIDlg::dbg_printf( char *format, ... )
{
	char Str[200];
	va_list ap;
	CString str;

	va_start( ap, format );

	vsprintf( Str, format, ap );	

	va_end(ap);	

	str.Format("%s", Str);
	Print_Log(str);
}

void CST32LD_GUIDlg::Button_Status( BOOL Mode )
{
	if( Mode == TRUE )
	{
		((CButton *)GetDlgItem(IDC_BUTTON_DOWN_BOOT))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BUTTON_DOWN_FIRM))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BUTTON_WRITE_UNPROTECT))->EnableWindow(TRUE);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_BUTTON_DOWN_BOOT))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_BUTTON_DOWN_FIRM))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_BUTTON_WRITE_UNPROTECT))->EnableWindow(FALSE);
	}
}

BOOL CST32LD_GUIDlg::GetFileName( void )
{
	BOOL Ret = FALSE;

	OPENFILENAME OFN;
	char str[300];
	char lpstrFile[MAX_PATH]="";

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner= this->GetSafeHwnd();
	OFN.lpstrFilter="BIN File(*.bin)\0*.bin\0BIN File\0*.bin;*.bin\0";
	OFN.lpstrFile=lpstrFile;
	OFN.nMaxFile=256;
	OFN.lpstrInitialDir="c:\\";

	
    CString filename;


	if( GetOpenFileName(&OFN) != 0 )
    {		
		strcpy(file_str, OFN.lpstrFile );
		Ret = TRUE;
    }
	

	return Ret;
	
}

void CST32LD_GUIDlg::Download_Exe() 
{

	u8 not_flashing    = 0;
	u8 send_go_command = 0;
	u8 boot_mode       = 0;
	u8 load_bin		   = 1;
	u8 minor, major;
	u16 version;
	long baud = 115200;
	
	char com_str[1024];
	CString str;
	int ErrCode;

	dbg_printf("stm32ld ver 1.0.1\n");


	if( UART_Opened != TRUE )
	{
		dbg_printf("ERROR : COM Port is not selected\n");
		MessageBox("Please Update COM and Select COM Port");
		return;
	}


	dbg_printf(" ");

	if( Download_Mode == BOOT_DOWNLOAD )
	{

		send_go_command = 1;
		dbg_printf("--- Bootloader Download Mode --- ");
	}
	else
	if( Download_Mode == FIRM_DOWNLOAD )
	{
		boot_mode       = 1;
		send_go_command = 1;
		dbg_printf("--- Firmware Download Mode --- ");
	}
	else
	{
		load_bin        = 0;
		boot_mode       = 0;
		send_go_command = 0;
		dbg_printf("--- Write Unprotect Mode --- ");
	}

	if( load_bin == 1 )
	{
		//-- Bin 파일 이름 읽기 
		//
		if( GetFileName() == FALSE )
		{
			dbg_printf("ERROR : GetFileName Failed");
		}
		else
		{
			dbg_printf("Download File : %s",file_str);
		}


		//-- Bin 파일 Open
		//
		if( fp != NULL ) 
		{
			fclose(fp);
		}

		if( ( fp = fopen( file_str, "rb" ) ) == NULL )
		{
			dbg_printf( "Unable to open %s\n", file_str );
			return;
		}
		else
		{
			fseek( fp, 0, SEEK_END );
			fpsize = ftell( fp );
			fseek( fp, 0, SEEK_SET );
		}

		dbg_printf( "File Size : %d KB\n", fpsize/1024 );
	}


	//-- Connect to bootloader
	//
	stm32_close();

	m_comboCOM.GetWindowText(str);
	sscanf( str, "%s", com_str );
	
	//dbg_printf("port : %s\n", com_str);


	if( ((CButton *)GetDlgItem(IDC_CHECK_AUTO_BOOT))->GetCheck() == TRUE )
	{
		dbg_printf( "Go to bootloader\n" );
		//-- 부트로더 실행 
		//
		stm32_go_boot( com_str, baud );
	}


	if( stm32_init( com_str, baud ) != STM32_OK )
	{
		dbg_printf( "ERROR :Unable to connect to bootloader\n" );
		if( load_bin == 1 )
		{
			fclose(fp);
		}
		return;
	}


	if( boot_mode == 1 )
	{
		if( stm32_boot_command() != STM32_OK )
		{
			dbg_printf( "ERROR : not baram bootloader\n" );
			return;
		}     
	}



	// Get version
	if( stm32_get_version( &major, &minor ) != STM32_OK )
	{
		dbg_printf( "ERROR :Unable to get bootloader version\n" );
		return;
	}
	else
	{

		if( boot_mode == 1)
		{
			dbg_printf( "Found baram bootloader version: %d.%d\n", major, minor );
		}
		else
		{  
			dbg_printf( "Found bootloader version: %d.%d\n", major, minor );
		}

		if( BL_MKVER( major, minor ) < BL_MINVERSION )
		{
			dbg_printf( "ERROR : Unsupported bootloader version" );
			return;
		}
	}
  
	// Get chip ID
	if( stm32_get_chip_id( &version ) != STM32_OK )
	{
		dbg_printf( "ERROR : Unable to get chip ID\n" );
		return;
	}
	else
	{
		dbg_printf( "Chip ID: %04X\n", version );
		if( version != CHIP_ID && version != CHIP_ID_ALT && version != 0x410 )
		{
			dbg_printf( "ERROR : Unsupported chip ID" );
			return;
		}
	}
  

  
	// Write unprotect
	//
	
	if( Download_Mode == WRITE_UNPROTECT )
	{
		if( stm32_write_unprotect() != STM32_OK )
		{
		  dbg_printf( "Unable to execute write unprotect\n" );
		  return;
		}
		else
		{
		  dbg_printf( "Cleared write protection.\n" );
		  dbg_printf( "Reset and Run BootLoader.\n" );
		}

		return;
    }
    


    // Erase flash
    //
	if( major == 3 )
    {
      dbg_printf( "Starting Extended Erase of FLASH memory. This will take some time ... Please be patient ...\n" );
      if( stm32_extended_erase_flash() != STM32_OK )
      {
        dbg_printf( "ERROR : Unable to extended erase chip\n" );
        return;
      }
      else
        dbg_printf( "Extended Erased FLASH memory.\n" );
    }
    else
    {
		ErrCode = stm32_erase_flash();
		if( ErrCode != STM32_OK )
		{
			str.Format("ERROR :Unable to erase chip : %d\n", ErrCode );
			dbg_printf((char *)str.GetBuffer(0));
			return;
		}
		else
			dbg_printf( "Erased FLASH memory.\n" );
    }


    // Program flash
	//
    //setbuf( stdout, NULL );
	expected_next = 10;
    dbg_printf( "Programming flash ... ");
    if( stm32_write_flash( writeh_read_data, writeh_progress ) != STM32_OK )
    {
      dbg_printf( "ERROR : Unable to program FLASH memory.\n" );
      return;
    }
    else
      dbg_printf( "\nDone.\n" );



	//-- Go
	//
	if( send_go_command == 1 )
	{
		// Run GO
		dbg_printf( "Sending Go command ... \n" );
		if( stm32_go_command( ) != STM32_OK )
		{
		  dbg_printf( "ERROR : Unable to run Go command.\n" );
		  return;
		}
	}


	Print_Log("다운로드 성공");
}


void CST32LD_GUIDlg::Download_Exe_OpenCM() 
{

	u8 not_flashing    = 0;
	u8 send_go_command = 0;
	u8 boot_mode       = 0;
	u8 load_bin		   = 1;
	u8 minor, major;
	u16 version;
	u16 i;
	int Ret;
	char RecvStr[100];	

	long baud = 115200;
	
	char com_str[1024];
	CString str;
	int ErrCode;

	dbg_printf("stm32ld ver 1.0.1 for CupDrone\n");


	if( UART_Opened != TRUE )
	{
		dbg_printf("ERROR : COM Port is not selected\n");
		MessageBox("Please Update COM and Select COM Port");
		return;
	}


	dbg_printf(" ");

	if( Download_Mode == FIRM_DOWNLOAD )
	{
		boot_mode       = 1;
		send_go_command = 1;
		dbg_printf("--- CupDrone Firmware Download Mode --- ");
	}
	else
	{
		load_bin        = 0;
		boot_mode       = 0;
		send_go_command = 0;
		dbg_printf("--- Mode Error --- ");
		return;
	}

	if( load_bin == 1 )
	{
		//-- Bin 파일 이름 읽기 
		//
		if( GetFileName() == FALSE )
		{
			dbg_printf("ERROR : GetFileName Failed");
		}
		else
		{
			dbg_printf("Download File : %s",file_str);
		}


		//-- Bin 파일 Open
		//
		if( fp != NULL ) 
		{
			fclose(fp);
		}

		if( ( fp = fopen( file_str, "rb" ) ) == NULL )
		{
			dbg_printf( "Unable to open %s\n", file_str );
			return;
		}
		else
		{
			fseek( fp, 0, SEEK_END );
			fpsize = ftell( fp );
			fseek( fp, 0, SEEK_SET );
		}

		dbg_printf( "File Size : %d KB\n", fpsize/1024 );
	}


	//-- Connect to bootloader
	//
	stm32_close();

	m_comboCOM.GetWindowText(str);
	sscanf( str, "%s", com_str );
	
	dbg_printf("port : %s\n", com_str);


	Ret = OpenCM_Cmd_Init( com_str, baud );
	if( Ret != STM32_OK )
	{
		str.Format("ERROR :Unable to connect to bootloader : %d\n", Ret );
		dbg_printf( str.GetBuffer(0) );
		if( load_bin == 1 )
		{
			fclose(fp);
		}
		return;
	}

	dbg_printf( "OpenCM_Cmd_Init : OK\n" );


		for( i=0; i<5; i++ )
		{
	  		if( OpenCM_Cmd_SendCmdRecvResponse("AT&LD", RecvStr, 5000 ) == TRUE )
	  		{
	  			dbg_printf("Ready To download \n");
	  			OpenCM_Wait_ms(5);
	
	  			if( OpenCM_WriteFlash( writeh_read_data, writeh_progress ) != TRUE )
	    		{
					fprintf( stderr, "Unable to program FLASH memory.\n" );
					exit( 1 );
				}
				else
				{
					//printf("\nFlash OK\n");
					OpenCM_Wait_ms(50);
	
					RecvStr[0] = 0;
					OpenCM_Cmd_ReadResponse( RecvStr, 500 );
					dbg_printf("CheckSum : %s\n", RecvStr);
	
					if( strncmp(RecvStr, "Success", 7) == 0 )
					{
						if( send_go_command == 1 )
						{
							OpenCM_Wait_ms(200);
							dbg_printf("Go Application\n");
							OpenCM_Cmd_SendCommand("AT&GO");
						}
						
						break;
					}
					else
					{
						OpenCM_Wait_ms(200);
						fseek( fp, 0, SEEK_SET );
						expected_next = 10;
					}
	
				}
	
	  		}
	  		else
	  		{
	  			fprintf( stderr, "Fail to be ready.\n" );
	  			break;
	  		}
		}

	if( load_bin == 1 )
	{
		fclose(fp);
	}
	Print_Log("다운로드 성공");
}

UINT CST32LD_GUIDlg::Download_Thread(LPVOID pParam)
{
        CST32LD_GUIDlg *Dlg = (CST32LD_GUIDlg*)pParam;
 
		Dlg->Download_Exe();
       
		stm32_close();

		Dlg->Button_Status(TRUE);

        return 0;
}


UINT CST32LD_GUIDlg::Download_Thread_OpenCM(LPVOID pParam)
{
        CST32LD_GUIDlg *Dlg = (CST32LD_GUIDlg*)pParam;
 
		Dlg->Download_Exe_OpenCM();      

		Dlg->Button_Status(TRUE);

        return 0;
}

void CST32LD_GUIDlg::OnButtonDownBoot() 
{
	// TODO: Add your control notification handler code here

	Download_Mode = BOOT_DOWNLOAD;

	Button_Status(FALSE);

	AfxBeginThread(Download_Thread,this);

}

void CST32LD_GUIDlg::OnButtonDownFirm() 
{
	// TODO: Add your control notification handler code here

	Download_Mode = FIRM_DOWNLOAD;

	Button_Status(FALSE);

	if( Get_BoardType() == BOARD_SKYROVER )
	{
		AfxBeginThread(Download_Thread,this);	
	}
	else if( Get_BoardType() == BOARD_CUPDRONE )
	{
		AfxBeginThread(Download_Thread_OpenCM,this);	
	}
	else
	{
		MessageBox("Wrong BoardType");
	}
}

void CST32LD_GUIDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here

	COM_Update();
}

void CST32LD_GUIDlg::OnButtonWriteUnprotect() 
{
	// TODO: Add your control notification handler code here
	Download_Mode = WRITE_UNPROTECT;

	Button_Status(FALSE);

	AfxBeginThread(Download_Thread,this);	
}

u32 CST32LD_GUIDlg::Get_BoardType() 
{
	int BoardType;
	CString str;

	BoardType = m_ctrlBoard.GetCurSel();

	//str.Format("%d", BoardType );
	//MessageBox( str );

	if( BoardType > 1 ) BoardType = 0;

	return BoardType;
}