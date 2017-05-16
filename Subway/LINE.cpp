// LINE.h : CLINE 类的实现



// CLINE 实现

// 代码生成在 2016年1月17日, 22:55

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
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[LNAME]"), m_LNAME);
	RFX_Long(pFX, _T("[color]"), m_color);

}
/////////////////////////////////////////////////////////////////////////////
// CLINE 诊断

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


