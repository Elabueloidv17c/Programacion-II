#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"

class CBreakoutfinalApp : public CWinApp
{
public:
	CBreakoutfinalApp();
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CBreakoutfinalApp theApp;
