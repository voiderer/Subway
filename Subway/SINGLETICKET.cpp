// SINGLETICKET.h : CSINGLETICKET ���ʵ��



// CSINGLETICKET ʵ��

// ���������� 2016��1��18��, 11:59

#include "stdafx.h"
#include "SINGLETICKET.h"
IMPLEMENT_DYNAMIC(CSINGLETICKET, CRecordset)

CSINGLETICKET::CSINGLETICKET(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PRICE = 0.0;
	m_ETIME;
	m_XTIME;
	m_BTIME;
	m_SERIAL = 0;
	m_BSTAT = L"";
	m_ESTAT = L"";
	m_XSTAT = L"";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSINGLETICKET::GetDefaultConnect()
{
	return _T("DSN=sub;UID=sa;PWD=yutao2011;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=YUTAO-PC;DATABASE=yutao");
}

CString CSINGLETICKET::GetDefaultSQL()
{
	return _T("[dbo].[SINGLETICKET]");
}

void CSINGLETICKET::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Single(pFX, _T("[PRICE]"), m_PRICE);
	RFX_Date(pFX, _T("[ETIME]"), m_ETIME);
	RFX_Date(pFX, _T("[XTIME]"), m_XTIME);
	RFX_Date(pFX, _T("[BTIME]"), m_BTIME);
	RFX_Long(pFX, _T("[SERIAL]"), m_SERIAL);
	RFX_Text(pFX, _T("[BSTAT]"), m_BSTAT);
	RFX_Text(pFX, _T("[ESTAT]"), m_ESTAT);
	RFX_Text(pFX, _T("[XSTAT]"), m_XSTAT);

}
/////////////////////////////////////////////////////////////////////////////
// CSINGLETICKET ���

#ifdef _DEBUG
void CSINGLETICKET::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSINGLETICKET::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


