// CONSUME.h : CCONSUME 类的实现



// CCONSUME 实现

// 代码生成在 2016年1月20日, 13:02

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
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[SERIAL]"), m_SERIAL);
	RFX_Date(pFX, _T("[BTIME]"), m_BTIME);
	RFX_Date(pFX, _T("[DTIME]"), m_DTIME);
	RFX_Text(pFX, _T("[KIND]"), m_KIND);
	RFX_Single(pFX, _T("[CHANGE]"), m_CHANGE);
	RFX_Single(pFX, _T("[REST]"), m_REST);

}
/////////////////////////////////////////////////////////////////////////////
// CCONSUME 诊断

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


