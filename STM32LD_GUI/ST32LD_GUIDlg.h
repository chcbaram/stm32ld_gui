// ST32LD_GUIDlg.h : header file
//

#if !defined(AFX_ST32LD_GUIDLG_H__8A73CAA6_45B8_4A36_82A9_CB4018C2BCC7__INCLUDED_)
#define AFX_ST32LD_GUIDLG_H__8A73CAA6_45B8_4A36_82A9_CB4018C2BCC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdarg.h>


#include "stm32ld.h"
#include "serial.h"
#include "OpenCM.h"


#define BL_VERSION_MAJOR  2
#define BL_VERSION_MINOR  1
#define BL_MKVER( major, minor )    ( ( major ) * 256 + ( minor ) ) 
#define BL_MINVERSION               BL_MKVER( BL_VERSION_MAJOR, BL_VERSION_MINOR )

#define CHIP_ID           0x0414
#define CHIP_ID_ALT       0x0413


#define BOOT_DOWNLOAD	0
#define FIRM_DOWNLOAD	1
#define WRITE_UNPROTECT 2


#define BOARD_SKYROVER	0
#define BOARD_CUPDRONE	1



/////////////////////////////////////////////////////////////////////////////
// CST32LD_GUIDlg dialog

class CST32LD_GUIDlg : public CDialog
{
// Construction
public:
	CST32LD_GUIDlg(CWnd* pParent = NULL);	// standard constructor


	BOOL	UART_Opened;
	BOOL	FILE_Opened;
	
	u32		Download_Mode;



	FILE *fp;
	u32   fpsize;
	int   expected_next;
	char  file_str[2048];

	static u32  writeh_read_data( u8 *dst, u32 len );
	static void writeh_progress( u32 wrote );


	void Print_LogTitle(void);
	void Print_Log(CString str);
	void Button_Status( BOOL Mode );
	void Download_Exe();
	void Download_Exe_OpenCM();
	void dbg_printf( char *format, ... );
	void COM_Update( void );
	BOOL GetFileName( void );
	u32  Get_BoardType();


	static UINT Download_Thread(LPVOID pParam);
	static UINT Download_Thread_OpenCM(LPVOID pParam);

// Dialog Data
	//{{AFX_DATA(CST32LD_GUIDlg)
	enum { IDD = IDD_ST32LD_GUI_DIALOG };
	CComboBox	m_ctrlBoard;
	CComboBox	m_comboCOM;
	CListCtrl	m_listLog;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CST32LD_GUIDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CST32LD_GUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	afx_msg void OnDestroy();
	afx_msg void OnButtonDownBoot();
	afx_msg void OnButtonDownFirm();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonWriteUnprotect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ST32LD_GUIDLG_H__8A73CAA6_45B8_4A36_82A9_CB4018C2BCC7__INCLUDED_)
