#pragma once
#include "afxdockablepane.h"
#include "Structure.h"


class CInfoView :
	public CDockablePane
{
public:
	void AdjustLayout();
	void AppendString(CString str);
protected:
	CRichEditCtrl m_wndOutPut;
public:
	CInfoView();
	~CInfoView();
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

