// LINE.h : CLINE ���ʵ��



// CLINE ʵ��

// ���������� 2016��1��17��, 22:55

#include "stdafx.h"
#include "LINE.h"
IMPLEMENT_DYNAMIC(CLINE, CRecordset)

CLINE::CLINE(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_LNAME = L"";
	m_color = 0;
	m_nFields = 2;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CLINE::GetDefaultConnect()
{
	return _T("DSN=sub;UID=sa;PWD=yutao2011;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=YUTAO-PC;DATABASE=yutao");
}

CString CLINE::GetDefaultSQL()
{
	return _T("[dbo].[LINE]");
}

void CLINE::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[LNAME]"), m_LNAME);
	RFX_Long(pFX, _T("[color]"), m_color);

}
/////////////////////////////////////////////////////////////////////////////
// CLINE ���

#ifdef _DEBUG
void CLINE::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLINE::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


