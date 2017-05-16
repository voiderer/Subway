// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// SubwayView.h : CSubwayView ��Ľӿ�
//

#pragma once
#include <vector>

class CSubwayView : public CScrollView
{
protected: // �������л�����
	CSubwayView();
	DECLARE_DYNCREATE(CSubwayView)
	float m_fRa;             //ͼ�����ʾ����
	int m_nAlgorithm;        //ʹ�õ��㷨
	int m_nMode;             //������ģʽѡ��
	bool m_bDrag;            //������Ƿ�����קģʽ��־
	CSize m_ViewSize;        //������ʾ��С
	CPoint m_LastPoint;      //��קʱ��¼���λ�������Ļ���Ͻǵ�λ��
	CPoint m_Lastscrollpos;  //��ק�Ǽ�¼���ʱ�ͻ������Ͻ����������ͼ���Ͻ�λ��
	HCURSOR m_hCursor;       //��קʱ�Ĺ����Դ
	HCURSOR m_hStdCur;       //ѡ��վ��ʱ�����ι��
	CString m_strDescription;//����ģʽ������
	int m_nSerial;

	void OnRatioChange();    //������ʾ���������仯ʱ����Ҫ�ɵ���
	bool JudgePos(CPoint pot,bool flag=1);    //�жϵ�ǰ���λ���ǲ�����վ��֮��
	CPoint TranPos(CPoint orign);             //��ԭʼ�����������ת��Ϊ�����仯�������
	CFont font;
// ����
public:
	CSubwayDoc* GetDocument() const;
	vector<CString> highlighted;              //���ڼ�¼���ѡ���վ����
// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSubwayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnZoomOut();       //��ʾ�����Ŵ��¼�
	afx_msg void OnZoomIn();        //��ʾ������С�¼�
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);  //�ù���ʱ��ı���ʾ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  //�������ʱ�䣬�����жϵ����λ�÷��������
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);   //���������ק״̬��ʵ����ͼλ�õĸı�
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);   //���̧��ʱ��ԭ״̬
	afx_msg void OnPathShort();      //�л������·��ģʽ�µ��¼���Ӧ
	afx_msg void OnTransLeast();     //�л������ٻ���ģʽ�µ��¼���Ӧ
	afx_msg void OnBothConsider();   //�л����ۺϿ���ģʽ�µ��¼���Ӧ
	afx_msg void OnUpdatePathShort(CCmdUI *pCmdUI);    //�������ػ�ʱ���á����·������ѡ��״̬
	afx_msg void OnUpdateTransLeast(CCmdUI *pCmdUI);   //�������ػ�ʱ���á����ٻ��ˡ���ѡ��״̬
	afx_msg void OnUpdateBothConsider(CCmdUI *pCmdUI); //�������ػ�ʱ���á��ۺϿ��ǡ���ѡ��״̬
	afx_msg void OnSingleTicket();
	afx_msg void OnUpdateSingleTicket(CCmdUI *pCmdUI);
	afx_msg void OnCheck3();
	afx_msg void OnUpdateCheck3(CCmdUI *pCmdUI);
	afx_msg void OnEdit2();
	afx_msg void OnUpdateEdit2(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SubwayView.cpp �еĵ��԰汾
inline CSubwayDoc* CSubwayView::GetDocument() const
   { return reinterpret_cast<CSubwayDoc*>(m_pDocument); }
#endif

