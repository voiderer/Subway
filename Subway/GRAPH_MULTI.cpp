// GRAPH_MULTI.h : CGRAPH_MULTI 类的实现



// CGRAPH_MULTI 实现

// 代码生成在 2016年1月17日, 23:22

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
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// CGRAPH_MULTI 诊断

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


