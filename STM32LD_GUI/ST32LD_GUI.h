// ST32LD_GUI.h : main header file for the ST32LD_GUI application
//

#if !defined(AFX_ST32LD_GUI_H__70D6F563_99C3_4F66_9E0F_B0D357C6D0AE__INCLUDED_)
#define AFX_ST32LD_GUI_H__70D6F563_99C3_4F66_9E0F_B0D357C6D0AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CST32LD_GUIApp:
// See ST32LD_GUI.cpp for the implementation of this class
//

class CST32LD_GUIApp : public CWinApp
{
public:
	CST32LD_GUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CST32LD_GUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CST32LD_GUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ST32LD_GUI_H__70D6F563_99C3_4F66_9E0F_B0D357C6D0AE__INCLUDED_)
