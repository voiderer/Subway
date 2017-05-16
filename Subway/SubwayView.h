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

// SubwayView.h : CSubwayView 类的接口
//

#pragma once
#include <vector>

class CSubwayView : public CScrollView
{
protected: // 仅从序列化创建
	CSubwayView();
	DECLARE_DYNCREATE(CSubwayView)
	float m_fRa;             //图像的显示比例
	int m_nAlgorithm;        //使用的算法
	int m_nMode;             //导航的模式选择
	bool m_bDrag;            //鼠标点击是否是拖拽模式标志
	CSize m_ViewSize;        //整体显示大小
	CPoint m_LastPoint;      //拖拽时记录点击位置相对屏幕左上角的位置
	CPoint m_Lastscrollpos;  //拖拽是记录点击时客户区左上角相对整个视图左上角位置
	HCURSOR m_hCursor;       //拖拽时的光标资源
	HCURSOR m_hStdCur;       //选择站点时的手形光标
	CString m_strDescription;//对于模式的描述
	int m_nSerial;

	void OnRatioChange();    //处理显示比例发生变化时候需要干的事
	bool JudgePos(CPoint pot,bool flag=1);    //判断当前鼠标位置是不是在站点之上
	CPoint TranPos(CPoint orign);             //将原始比例的坐标点转化为比例变化后的坐标
	CFont font;
// 特性
public:
	CSubwayDoc* GetDocument() const;
	vector<CString> highlighted;              //用于记录鼠标选择的站点名
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSubwayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnZoomOut();       //显示比例放大事件
	afx_msg void OnZoomIn();        //显示比例缩小事件
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);  //用滚轮时间改变显示比例
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //左键点下时间，调用判断点击的位置分情况处理
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);   //如果是在拖拽状态，实现视图位置的改变
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);   //鼠标抬起时还原状态
	afx_msg void OnPathShort();      //切换成最短路径模式下的事件响应
	afx_msg void OnTransLeast();     //切换成最少换乘模式下的事件响应
	afx_msg void OnBothConsider();   //切换成综合考虑模式下的事件响应
	afx_msg void OnUpdatePathShort(CCmdUI *pCmdUI);    //功能区重绘时设置“最短路径”复选框状态
	afx_msg void OnUpdateTransLeast(CCmdUI *pCmdUI);   //功能区重绘时设置“最少换乘”复选框状态
	afx_msg void OnUpdateBothConsider(CCmdUI *pCmdUI); //功能区重绘时设置“综合考虑”复选框状态
	afx_msg void OnSingleTicket();
	afx_msg void OnUpdateSingleTicket(CCmdUI *pCmdUI);
	afx_msg void OnCheck3();
	afx_msg void OnUpdateCheck3(CCmdUI *pCmdUI);
	afx_msg void OnEdit2();
	afx_msg void OnUpdateEdit2(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SubwayView.cpp 中的调试版本
inline CSubwayDoc* CSubwayView::GetDocument() const
   { return reinterpret_cast<CSubwayDoc*>(m_pDocument); }
#endif

