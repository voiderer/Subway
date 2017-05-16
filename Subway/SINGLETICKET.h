// SINGLETICKET.h : CSINGLETICKET ������

#pragma once

// ���������� 2016��1��18��, 11:59

class CSINGLETICKET : public CRecordset
{
public:
	CSINGLETICKET(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSINGLETICKET)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	float	m_PRICE;
	CTime	m_ETIME;
	CTime	m_XTIME;
	CTime	m_BTIME;
	long	m_SERIAL;
	CStringW	m_BSTAT;
	CStringW	m_ESTAT;
	CStringW	m_XSTAT;

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


