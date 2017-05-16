// CONSUME.h : CCONSUME ���ʵ��



// CCONSUME ʵ��

// ���������� 2016��1��20��, 13:02

#include "stdafx.h"
#include "CONSUME.h"
IMPLEMENT_DYNAMIC(CCONSUME, CRecordset)

CCONSUME::CCONSUME(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SERIAL = 0;
	m_BTIME;
	m_DTIME;
	m_KIND = L"";
	m_CHANGE = 0.0;
	m_REST = 0.0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CCONSUME::GetDefaultConnect()
{
	return _T("DSN=sub;UID=sa;PWD=yutao2011;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=YUTAO-PC;DATABASE=yutao");
}

CString CCONSUME::GetDefaultSQL()
{
	return _T("[dbo].[CONSUME]");
}

void CCONSUME::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[SERIAL]"), m_SERIAL);
	RFX_Date(pFX, _T("[BTIME]"), m_BTIME);
	RFX_Date(pFX, _T("[DTIME]"), m_DTIME);
	RFX_Text(pFX, _T("[KIND]"), m_KIND);
	RFX_Single(pFX, _T("[CHANGE]"), m_CHANGE);
	RFX_Single(pFX, _T("[REST]"), m_REST);

}
/////////////////////////////////////////////////////////////////////////////
// CCONSUME ���

#ifdef _DEBUG
void CCONSUME::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCONSUME::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


