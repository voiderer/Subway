#include "stdafx.h"
#include "InfoView.h"
#include "resource.h"

CInfoView::CInfoView()
{
}


CInfoView::~CInfoView()
{
}


void CInfoView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);
	m_wndOutPut.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}BEGIN_MESSAGE_MAP(CInfoView, CDockablePane)
ON_WM_CREATE()
ON_WM_SIZE()
END_MESSAGE_MAP()


int CInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  在此添加您专用的创建代码
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// 创建组合: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_READONLY | ES_WANTRETURN | ES_MULTILINE;
	if (!m_wndOutPut.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建输出窗口 \n");
		return -1;      // 未能创建
	}
	return 0;
}


void CInfoView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	AdjustLayout();
	// TODO:  在此处添加消息处理程序代码
}

void CInfoView::AppendString(CString str)
{
	m_wndOutPut.SetSel(-1, -1);
	m_wndOutPut.ReplaceSel(str);
	m_wndOutPut.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}