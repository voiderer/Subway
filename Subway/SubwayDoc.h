// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// SubwayDoc.h : CSubwayDoc 类的接口
//


#pragma once
#include "Structure.h"
#include <map>

class CSubwayDoc : public CDocument
{
protected: // 仅从序列化创建
	CSubwayDoc();
	DECLARE_DYNCREATE(CSubwayDoc)

// 特性
public:
	map<CString, StaInfo> m_stationmap;         //从站点名到站点信息的映射
	vector<Route> m_linelist;                   //存储线路信息的容器
	vector<CString> m_Path;                     //存储算法生成路径的容器
	void Pathsearching(CString startpoint, CString destination); //最少换乘算法
	int MesureDistance(CString stop1, CString stop2, int line);  //最少换乘算法中调用的测量两换乘站之间距离函数
	void GetStations(CString stop1, CString stop2, int line);//最少换乘算法中将两换乘点间的站点加入容器的函数
	void Dijkstra(CString startpoint, CString destination);//最短路径函数，使用的是基于邻接表的迪杰克斯拉算法
	void UpdateWeight(map<CString, Low>& lowcost,CString name);//迪杰克斯拉算法中更新权重的函数
	int m_nPathLength;      //记录路径的长度
	int TRANSFER_DELAY;     //换乘的权重
	int m_nTranstimes;      //记录换乘的次数
// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CSubwayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
