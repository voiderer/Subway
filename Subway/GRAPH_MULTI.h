// GRAPH_MULTI.h : CGRAPH_MULTI ������

#pragma once

// ���������� 2016��1��17��, 23:22

class CGRAPH_MULTI : public CRecordset
{
public:
	CGRAPH_MULTI(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGRAPH_MULTI)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	int	m_dboGRAPHINDX;
	CStringW	m_dboGRAPHLNAME;
	CStringW	m_dboGRAPHSNAME;
	int	m_dboGRAPHDisUp;
	int	m_dboGRAPHDisDown;
	CStringW	m_dboSTATIONSNAME;
	int	m_dboSTATIONNX;
	int	m_dboSTATIONNY;
	int	m_dboSTATIONOX;
	int	m_dboSTATIONOY;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


