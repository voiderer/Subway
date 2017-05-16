// GRAPH_MULTI.h : CGRAPH_MULTI ���ʵ��



// CGRAPH_MULTI ʵ��

// ���������� 2016��1��17��, 23:22

#include "stdafx.h"
#include "GRAPH_MULTI.h"
IMPLEMENT_DYNAMIC(CGRAPH_MULTI, CRecordset)

CGRAPH_MULTI::CGRAPH_MULTI(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_dboGRAPHINDX = 0;
	m_dboGRAPHLNAME = L"";
	m_dboGRAPHSNAME = L"";
	m_dboGRAPHDisUp = 0;
	m_dboGRAPHDisDown = 0;
	m_dboSTATIONSNAME = L"";
	m_dboSTATIONNX = 0;
	m_dboSTATIONNY = 0;
	m_dboSTATIONOX = 0;
	m_dboSTATIONOY = 0;
	m_nFields = 10;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CGRAPH_MULTI::GetDefaultConnect()
{
	return _T("DSN=sub;UID=sa;PWD=yutao2011;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=YUTAO-PC;DATABASE=yutao");
}

CString CGRAPH_MULTI::GetDefaultSQL()
{
	return _T("[dbo].[GRAPH],[dbo].[STATION]");
}

void CGRAPH_MULTI::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Int(pFX, _T("[dbo].[GRAPH].[INDX]"), m_dboGRAPHINDX);
	RFX_Text(pFX, _T("[dbo].[GRAPH].[LNAME]"), m_dboGRAPHLNAME);
	RFX_Text(pFX, _T("[dbo].[GRAPH].[SNAME]"), m_dboGRAPHSNAME);
	RFX_Int(pFX, _T("[dbo].[GRAPH].[DisUp]"), m_dboGRAPHDisUp);
	RFX_Int(pFX, _T("[dbo].[GRAPH].[DisDown]"), m_dboGRAPHDisDown);
	RFX_Text(pFX, _T("[dbo].[STATION].[SNAME]"), m_dboSTATIONSNAME);
	RFX_Int(pFX, _T("[dbo].[STATION].[NX]"), m_dboSTATIONNX);
	RFX_Int(pFX, _T("[dbo].[STATION].[NY]"), m_dboSTATIONNY);
	RFX_Int(pFX, _T("[dbo].[STATION].[OX]"), m_dboSTATIONOX);
	RFX_Int(pFX, _T("[dbo].[STATION].[OY]"), m_dboSTATIONOY);

}
/////////////////////////////////////////////////////////////////////////////
// CGRAPH_MULTI ���

#ifdef _DEBUG
void CGRAPH_MULTI::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGRAPH_MULTI::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


