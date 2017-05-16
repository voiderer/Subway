// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// SubwayView.cpp : CSubwayView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Subway.h"
#endif

#include "SubwayDoc.h"
#include "SubwayView.h"
#include "Structure.h"
#include "MainFrm.h"
#include "SINGLETICKET.h"
#include "CONSUME.h"
#include "Transcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSubwayView

IMPLEMENT_DYNCREATE(CSubwayView, CScrollView)

BEGIN_MESSAGE_MAP(CSubwayView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSubwayView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ZOOM_OUT, &CSubwayView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_IN, &CSubwayView::OnZoomIn)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
    ON_COMMAND(ID_PATH_SHORT, &CSubwayView::OnPathShort)
    ON_COMMAND(ID_TRANS_LEAST, &CSubwayView::OnTransLeast)
    ON_COMMAND(ID_BOTH_CONSIDER, &CSubwayView::OnBothConsider)
    ON_UPDATE_COMMAND_UI(ID_PATH_SHORT, &CSubwayView::OnUpdatePathShort)
    ON_UPDATE_COMMAND_UI(ID_TRANS_LEAST, &CSubwayView::OnUpdateTransLeast)
    ON_UPDATE_COMMAND_UI(ID_BOTH_CONSIDER, &CSubwayView::OnUpdateBothConsider)
	ON_COMMAND(ID_SINGLE_TICKET, &CSubwayView::OnSingleTicket)
	ON_UPDATE_COMMAND_UI(ID_SINGLE_TICKET, &CSubwayView::OnUpdateSingleTicket)
	ON_COMMAND(ID_CHECK3, &CSubwayView::OnCheck3)
	ON_UPDATE_COMMAND_UI(ID_CHECK3, &CSubwayView::OnUpdateCheck3)
	ON_COMMAND(ID_EDIT2, &CSubwayView::OnEdit2)
	ON_UPDATE_COMMAND_UI(ID_EDIT2, &CSubwayView::OnUpdateEdit2)
END_MESSAGE_MAP()

// CSubwayView 构造/析构

CSubwayView::CSubwayView()
{
	// TODO:  在此处添加构造代码
	m_fRa = 1.5;
	m_hCursor = AfxGetApp()->LoadCursor(IDC_DRAG);
	m_hStdCur = AfxGetApp()->LoadStandardCursor(IDC_HAND);
	m_bDrag = FALSE;
	m_nAlgorithm = 1;
	m_strDescription = "单程票购票：\n";
	m_nMode = 3;
	font.CreateFont(9 * m_fRa,                                          //   nHeight     
		5 * m_fRa,                                                   //   nWidth     
		0,                                                   //   nEscapement   
		0,                                                   //   nOrientation     
		FW_NORMAL,                                   //   nWeight     
		FALSE,                                           //   bItalic     
		FALSE,                                           //   bUnderline     
		0,                                                   //   cStrikeOut     
		ANSI_CHARSET,                             //   nCharSet     
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision     
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
		DEFAULT_QUALITY,                       //   nQuality     
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily       
		_T("楷体"));
}

CSubwayView::~CSubwayView()
{
}

BOOL CSubwayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.dwExStyle = WS_HSCROLL | WS_VSCROLL;
	return CScrollView::PreCreateWindow(cs);
}

// CSubwayView 绘制
CPoint CSubwayView::TranPos(CPoint orign)
{
	return CPoint((int)orign.x*m_fRa , (int)orign.y*m_fRa);
}

void CSubwayView::OnDraw(CDC* pDC)
{
	CSubwayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO:  在此处为本机数据添加绘制代码
	map<CString, StaInfo>::iterator iter;
	CPen myPen,*PenOld;
	vector<Route>& Lines = pDoc->m_linelist;
	PenOld = pDC->GetCurrentPen();
	CPoint tmpPoint;
	map<CString, StaInfo>& Station = pDoc->m_stationmap;
	for (UINT i = 0; i < Lines.size(); i++)
	{
		vector<station>& TempList = Lines[i].stationlist;
		myPen.CreatePen(PS_SOLID, (int)8 * m_fRa, Lines[i].m_color);
		pDC->SelectObject(&myPen);
		iter = Station.find(TempList[0].name);
		pDC->MoveTo(TranPos(iter->second.pos));
		
		for (UINT j = 1; j < TempList.size(); j++)
		{
			iter = Station.find(TempList[j].name);
			pDC->LineTo(TranPos(iter->second.pos));
		}
		if (TempList[TempList.size()-1].disdown>0&&i<17)
		{
			iter = Station.find(TempList[0].name);
			pDC->LineTo(TranPos(iter->second.pos));
		}
		myPen.DeleteObject();
	}
	pDC->SelectObject(PenOld);
	CPoint tem;
	

	pDC->SelectObject(&font);
	for (iter = Station.begin(); iter != Station.end(); iter++)
	{
		tem = iter->second.pos;
		if (iter->second.locate.size() == 1)
		{
			pDC->Ellipse((tem.x - 5)*m_fRa, (tem.y - 5)*m_fRa, (tem.x + 5)*m_fRa, (tem.y + 5)*m_fRa);
		}
		else
		{
			pDC->Ellipse((tem.x - 8)*m_fRa, (tem.y - 8)*m_fRa, (tem.x + 8)*m_fRa, (tem.y + 8)*m_fRa);
		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut((tem.x + 5)*m_fRa, (tem.y + 8)*m_fRa, iter->first);
	}
	CBrush BrushNew,*pOldBrush;
	BrushNew.CreateSolidBrush(RGB(255, 0, 0));
	pOldBrush=pDC->SelectObject(&BrushNew);
	for (UINT i = 0; i < highlighted.size(); i++)
	{
		
		tem = Station.find(highlighted[i])->second.pos;
		pDC->Ellipse((tem.x - 9)*m_fRa, (tem.y - 9)*m_fRa, (tem.x + 9)*m_fRa, (tem.y + 9)*m_fRa);
	}
	BrushNew.DeleteObject();
	
	if (pDoc->m_Path.size() > 0)
	{
		
		CPen APen, *oldpen;
		APen.CreatePen(PS_SOLID, (int)8 * m_fRa, RGB(0, 255, 0));
		oldpen = pDC->SelectObject(&APen);
		pDC->MoveTo(TranPos(Station.find((pDoc->m_Path[0]))->second.pos));
		for (UINT i = 1; i < pDoc->m_Path.size(); i++)
		{
			tem = Station.find(pDoc->m_Path[i])->second.pos;
			pDC->LineTo(TranPos(tem));
		}
		pDC->SelectObject(oldpen);
		BrushNew.CreateSolidBrush(RGB(0, 200, 0));
		pDC->SelectObject(&BrushNew);
		for each(CString a in pDoc->m_Path)
		{
			tem = Station.find(a)->second.pos;
			pDC->Ellipse((tem.x - 9)*m_fRa, (tem.y - 9)*m_fRa, (tem.x + 9)*m_fRa, (tem.y + 9)*m_fRa);
		}	
				
	}
	pDC->SelectObject(pOldBrush);
}

void CSubwayView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO:  计算此视图的合计大小
	m_ViewSize.cx = 2900;
	m_ViewSize.cy = 1950;
	SetScrollSizes(MM_TEXT, m_ViewSize);
	ScrollToPosition(CPoint(670, 750));
}


// CSubwayView 打印


void CSubwayView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSubwayView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSubwayView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CSubwayView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CSubwayView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSubwayView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSubwayView 诊断

#ifdef _DEBUG
void CSubwayView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSubwayView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSubwayDoc* CSubwayView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSubwayDoc)));
	return (CSubwayDoc*)m_pDocument;
}
#endif //_DEBUG


// CSubwayView 消息处理程序

void CSubwayView::OnRatioChange()
{
	CSize NewSize((int)m_ViewSize.cx*m_fRa, (int)m_ViewSize.cy*m_fRa);
	SetScrollSizes(MM_TEXT, NewSize);
	font.CreateFont(9 * m_fRa,                                          //   nHeight     
		5 * m_fRa,                                                   //   nWidth     
		0,                                                   //   nEscapement   
		0,                                                   //   nOrientation     
		FW_NORMAL,                                   //   nWeight     
		FALSE,                                           //   bItalic     
		FALSE,                                           //   bUnderline     
		0,                                                   //   cStrikeOut     
		ANSI_CHARSET,                             //   nCharSet     
		OUT_DEFAULT_PRECIS,                 //   nOutPrecision     
		CLIP_DEFAULT_PRECIS,               //   nClipPrecision     
		DEFAULT_QUALITY,                       //   nQuality     
		DEFAULT_PITCH | FF_SWISS,     //   nPitchAndFamily       
		_T("楷体"));
	CDC* pDC = GetDC();
}


void CSubwayView::OnZoomOut()
{
	// TODO:  在此添加命令处理程序代码
	if (m_fRa < 10)
	{
		m_fRa *= 1.25;
	}
	OnRatioChange();
	Invalidate();
}


void CSubwayView::OnZoomIn()
{
	// TODO:  在此添加命令处理程序代码
	if (m_fRa>1)
	{
		m_fRa *= 0.8;
	}
	OnRatioChange();
	Invalidate();
}


BOOL CSubwayView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags&MK_CONTROL)
	{
		if (zDelta < 0 && m_fRa > 0.5)
		{
			m_fRa *= 0.8;
		}
		else if (zDelta > 0 && m_fRa < 10)
		{
			m_fRa *= 1.25;
		}
		OnRatioChange();
		Invalidate();
	}
	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


void CSubwayView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (JudgePos(point))
	{
		CSubwayDoc* pDoc = GetDocument();
		CMFCRibbonBaseElement* elemPtr=((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetStatusbar()->GetElement(0);
		if (highlighted.size() == 1)
		{
			pDoc->m_Path.clear();
			elemPtr->SetText(_T("请使用鼠标左键单击选择终点"));
			elemPtr->Redraw();
		}
		else if (highlighted.size() == 2)
		{		
			if (highlighted[1] != highlighted[0])
			{
				if (m_nAlgorithm == 0)
				{
					pDoc->Pathsearching(highlighted[0], highlighted[1]);
				}
				else
				{
					pDoc->Dijkstra(highlighted[0], highlighted[1]);
				}
				CString temp;
				int price=0,a= pDoc->m_nPathLength,b;
				if (a < 6001)
				{
					price = 3;
				}
				else if(a<12001){
					price = 4;
				}
				else if (a<22001) {
					price = 5;
				}
				else if (a<32001) {
					price = 6;
				}
				else {
					b = a - 3200;
					b = (int)((float)b / 20000.0)+1;
					price = 6+b;
				}
				temp.Format(_T("%s%s-->%s\n距离=%d米\n票价=%d元\n\n"), m_strDescription, highlighted[0], highlighted[1], pDoc->m_nPathLength,price);
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndInfo.AppendString(temp);			
				elemPtr->SetText(_T("请使用鼠标左键单击选择起点"));
				elemPtr->Redraw();
				if (m_nMode == 3)
				{
					CSINGLETICKET ticket;
					ticket.Open();
					ticket.AddNew();
					ticket.m_BTIME = CTime::GetCurrentTime();
					ticket.m_ETIME = CTime::GetCurrentTime();
					ticket.m_XTIME = CTime::GetCurrentTime();
					ticket.m_PRICE = price;
					ticket.m_BSTAT = highlighted[0];
					ticket.m_ESTAT = highlighted[0];
					ticket.m_XSTAT = highlighted[1];
					ticket.m_SERIAL = rand();
					ticket.Update();
					ticket.Close();
				}
				else if (m_nMode == 4)
				{
					CString string;
					CMFCRibbonEdit* pEdit = ((CMainFrame*)AfxGetMainWnd())->GetEdit();
					CCONSUME consume;
					consume.Open();
					consume.AddNew();
					consume.m_BTIME= CTime::GetCurrentTime();
					consume.m_DTIME= CTime::GetCurrentTime();
					string = pEdit->GetEditText();
					consume.m_SERIAL = atoi(&WCHAR2CHAR( string).front());
				
					consume.m_KIND = _T("地铁");
					consume.m_CHANGE = price;
					consume.m_REST = 0;
					consume.Update();
					consume.Close();
				}
				
			}
			highlighted.clear();
		}
		Invalidate();
	}
	else
	{
		m_Lastscrollpos = GetScrollPosition();
		m_LastPoint = point;
		SetCapture();
		SetCursor(m_hCursor);
		m_bDrag = TRUE;
		
	}
	CScrollView::OnLButtonDown(nFlags, point);
}


void CSubwayView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bDrag)
	{
		ScrollToPosition(m_LastPoint - point + m_Lastscrollpos);
	}
	else
	{
		if (JudgePos(point,FALSE))
		{
			SetCursor(m_hStdCur);
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}


bool CSubwayView::JudgePos(CPoint pot,bool flag)
{
	CPoint Ctemp=GetScrollPosition();
	CPoint tem;
	CSubwayDoc* pDoc = GetDocument();
	map<CString, StaInfo>& Station = pDoc->m_stationmap;
	map<CString, StaInfo>::iterator iter;	
	for (iter = Station.begin(); iter != Station.end(); iter++)
	{
		tem = iter->second.pos;
		tem = TranPos(tem);
		if ((pot.x + Ctemp.x - tem.x)*(pot.x + Ctemp.x - tem.x) + (pot.y + Ctemp.y - tem.y)*(pot.y + Ctemp.y - tem.y) < 64 * m_fRa*m_fRa)
		{
			if (flag)
				highlighted.push_back(iter->first);
			return TRUE;
		}
	}
	return FALSE;
}


void CSubwayView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_bDrag)
	{
		m_bDrag = FALSE;
		ReleaseCapture();
	}
	CScrollView::OnLButtonUp(nFlags, point);
}


void CSubwayView::OnPathShort()
{
	// TODO:  在此添加命令处理程序代码
	m_nAlgorithm = 1;
	m_strDescription = "最短路径算法：\n";
	GetDocument()->TRANSFER_DELAY = 0;
	m_nMode = 0;
}


void CSubwayView::OnTransLeast()
{
	// TODO:  在此添加命令处理程序代码
	m_nAlgorithm = 0;
	m_strDescription = "最少换乘算法：\n";
	m_nMode = 1;
}


void CSubwayView::OnBothConsider()
{
	// TODO:  在此添加命令处理程序代码
	m_nAlgorithm = 1;
	m_strDescription = "综合考虑算法：\n";
	GetDocument()->TRANSFER_DELAY = 4000;
	m_nMode = 2;
}

void CSubwayView::OnSingleTicket()
{
	// TODO: 在此添加命令处理程序代码
	m_nAlgorithm = 1;
	m_strDescription = "购票出行：\n";
	GetDocument()->TRANSFER_DELAY = 0;
	m_nMode = 3;
}

void CSubwayView::OnCheck3()
{
	// TODO: 在此添加命令处理程序代码
	m_nAlgorithm = 1;
	m_strDescription = "一卡通出行：\n";
	GetDocument()->TRANSFER_DELAY = 0;
	m_nMode = 4;

}

void CSubwayView::OnUpdatePathShort(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
		pCmdUI->SetCheck(m_nMode == 0);
}


void CSubwayView::OnUpdateTransLeast(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
		pCmdUI->SetCheck(m_nMode == 1);
}

void CSubwayView::OnUpdateBothConsider(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
		pCmdUI->SetCheck(m_nMode == 2);
}

void CSubwayView::OnUpdateSingleTicket(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nMode == 3);
}

void CSubwayView::OnUpdateCheck3(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_nMode == 4);
}


void CSubwayView::OnEdit2()
{
	// TODO: 在此添加命令处理程序代码
}


void CSubwayView::OnUpdateEdit2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(m_nMode == 4);
}
