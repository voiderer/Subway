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

// SubwayDoc.cpp : CSubwayDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Subway.h"
#endif

#include "SubwayDoc.h"
#include "MainFrm.h"
#include <stack>
#include <propkey.h>
#include "Transcode.h"
#include "LINE.h"
#include "GRAPH_MULTI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSubwayDoc

IMPLEMENT_DYNCREATE(CSubwayDoc, CDocument)

BEGIN_MESSAGE_MAP(CSubwayDoc, CDocument)
END_MESSAGE_MAP()


// CSubwayDoc 构造/析构

CSubwayDoc::CSubwayDoc()
{
	// TODO:  在此添加一次性构造代码
	TRANSFER_DELAY = 0;
}

CSubwayDoc::~CSubwayDoc()
{
}

BOOL CSubwayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (m_linelist.size() > 0)
	{
		return TRUE;
	}
	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	CLINE line;
	try {
		if (line.IsOpen())
			line.Close();
		if (!line.Open(CRecordset::snapshot, _T("select * from LINE"))) {
			AfxMessageBox(_T("打开数据库失败"));
			return TRUE;
		}
	}
	catch (CDBException *e) {
		e->ReportError();
	}
	line.MoveFirst();
	while (!line.IsEOF())
	{
		Route temp;
		temp.name = line.m_LNAME;
		temp.m_color = ConvertToColor(line.m_color);//将字符串转化为数值后再转化为颜色
		m_linelist.push_back(temp);
		line.MoveNext();
	}
	CGRAPH_MULTI graph;
	try {
		if (graph.IsOpen())
			graph.Close();
		if (!graph.Open(CRecordset::snapshot, _T("select * from GRAPH,STATION where GRAPH.SNAME=STATION.SNAME"))) {
			AfxMessageBox(_T("打开数据库失败"));
			return TRUE;
		}
	}
	catch (CDBException *e) {
		e->ReportError();
	}
	station temp;
	CString qur;
	CPoint poitemp;
	Location temploc;
	map<CString, StaInfo>::iterator iter;
	for (UINT i = 0; i < m_linelist.size(); i++)
	{
		qur.Format(_T("select * from GRAPH,STATION where GRAPH.SNAME=STATION.SNAME and LNAME='%s' order by INDX"), m_linelist[i].name);
		try {
			if (graph.IsOpen())
				graph.Close();
			if (!graph.Open(CRecordset::snapshot, qur)) {
				AfxMessageBox(_T("打开数据库失败"));
				return TRUE;
			}
		}
		catch (CDBException *e) {
			e->ReportError();
		}
		graph.MoveFirst();
		while (!graph.IsEOF())
		{
			temp.name = graph.m_dboSTATIONSNAME;
			temp.disup = graph.m_dboGRAPHDisUp;
			temp.disdown = graph.m_dboGRAPHDisDown;
			m_linelist[i].stationlist.push_back(temp);
			temploc.whichline = i;
			temploc.whichstop = m_linelist[i].stationlist.size() - 1;
			iter = m_stationmap.find(temp.name);
			if (iter == m_stationmap.end())//在站点映射中没有找到此站点，则插入这一个站点
			{
				StaInfo tempinfo;
				tempinfo.pos.x = graph.m_dboSTATIONNX;
				tempinfo.pos.y = graph.m_dboSTATIONNY;

				tempinfo.locate.push_back(temploc);
				m_stationmap.insert(pair<CString, StaInfo>(temp.name, tempinfo));
			}
			else
			{
				iter->second.locate.push_back(temploc);
			}
			graph.MoveNext();
		}
	}

	list<Location>::iterator Siter1, Siter2;
	list<Relation>::iterator Liter;
	bool flag;
	for (iter = m_stationmap.begin(); iter != m_stationmap.end(); iter++)
		//对于每一个站点，如果经过的线路大于两条，就建立线路的相交关系
	{
		Siter1 = iter->second.locate.begin();
		while (Siter1 != iter->second.locate.end())//两重循环，使线路间两两都建立关系
		{
			Siter2 = Siter1;
			Siter2++;
			while (Siter2 != iter->second.locate.end())
			{
				flag = FALSE;
				for (Liter = m_linelist[Siter1->whichline].relatelist.begin(); Liter != m_linelist[Siter1->whichline].relatelist.end(); Liter++)
				{
					if (Liter->lineName == Siter2->whichline)
					{
						flag = TRUE;
						break;
					}
				}
				if (flag)
				{
					Liter->StopNames->push_back(iter->first);
				}
				else
				{
					Relation rela;

					rela.StopNames = new list<CString>;
					rela.StopNames->push_back(iter->first);
					rela.lineName = Siter1->whichline;
					m_linelist[Siter2->whichline].relatelist.push_back(rela);
					rela.lineName = Siter2->whichline;
					m_linelist[Siter1->whichline].relatelist.push_back(rela);
				}
				Siter2++;
			}
			Siter1++;
		}
	}
	
	/*CDataSource m_datasource;
	CSession m_dbsession;
	LPCOLESTR lpcOleConnect = L"Provider=sqloledb;Data Source=;Initial Catalog=yutao;User ID = sa; Password = yutao2011;";
	USES_CONVERSION;
//	Provider = Microsoft.ACE.OLEDB.12.0; Data Source = E:\database\地铁信息数据库.accdb
	CComVariant  var;
	HRESULT hr=m_datasource.OpenFromInitializationString(lpcOleConnect);//连接数据库
	if (FAILED(hr))
	{
		AfxMessageBox(_T("数据库连接失败"));
	}
	else
	{
		hr = m_dbsession.Open(m_datasource);
		hr = m_datasource.GetProperty(DBPROPSET_DATASOURCEINFO, DBPROP_DATASOURCENAME, &var);
		if (FAILED(hr) || (var.vt == VT_EMPTY))
		{
			AfxMessageBox(_T("未找到对应的文件名"));
		}
		else
		{
			LPCOLESTR query = L"SELECT * FROM 地铁线路表;";//读入地铁线路表的数据
			CCommand<CDynamicStringAccessor> cmd;
			hr = cmd.Open(m_dbsession, query);
			DBORDINAL colCount = cmd.GetColumnCount();
			if (SUCCEEDED(hr) && 0 < colCount)
			{				
				CRowset<CDynamicStringAccessor>* pRS = (CRowset<CDynamicStringAccessor>*)&cmd;
				while (pRS->MoveNext() == S_OK)
				{
					Route temp;
					temp.ID = atoi(&WCHAR2CHAR( cmd.GetString(1)).front());
					temp.name = cmd.GetString(2);
					temp.m_color = ConvertToColor(atoi(&WCHAR2CHAR(cmd.GetString(3)).front()));//将字符串转化为数值后再转化为颜色
					m_linelist.push_back(temp);
				}
			}
			station temp;
			CString qur;
			CPoint poitemp;
			Location temploc;
			map<CString, StaInfo>::iterator iter;
			for (UINT i = 0; i < m_linelist.size(); i++)
			{
				qur.Format( _T("SELECT * FROM 线路站点关系 WHERE 线路=%d") , m_linelist[i].ID);//对于每一条线路都把对应的线路信息读入
				CCommand<CDynamicStringAccessor> ncmd;
				ncmd.Open(m_dbsession, qur.GetBuffer());
				CRowset<CDynamicStringAccessor>* pRS = (CRowset<CDynamicStringAccessor>*)&ncmd;
				while (pRS->MoveNext() == S_OK)
				{					
					temp.name = ncmd.GetString(3);						
					temp.disup = atoi(&WCHAR2CHAR(ncmd.GetString(6)).front());
					temp.disdown = atoi(&WCHAR2CHAR(ncmd.GetString(7)).front());
					m_linelist[i].stationlist.push_back(temp);
					temploc.whichline = i;
					temploc.whichstop = m_linelist[i].stationlist.size() - 1;					
					iter= m_stationmap.find(temp.name);
					if (iter == m_stationmap.end())//在站点映射中没有找到此站点，则插入这一个站点
					{
						StaInfo tempinfo;
						tempinfo.pos.x = atoi(&WCHAR2CHAR(ncmd.GetString(4)).front());
						tempinfo.pos.y = atoi(&WCHAR2CHAR(ncmd.GetString(5)).front());
				
						tempinfo.locate.push_back(temploc);
						m_stationmap.insert(pair<CString, StaInfo>(temp.name, tempinfo));
					}
					else
					{
						iter->second.locate.push_back(temploc);
					}
				}
			}
		}
	}
	map<CString, StaInfo>::iterator iter;
	list<Location>::iterator Siter1, Siter2;
	list<Relation>::iterator Liter;
	bool flag;
	for (iter = m_stationmap.begin(); iter != m_stationmap.end(); iter++)
		//对于每一个站点，如果经过的线路大于两条，就建立线路的相交关系
	{
		Siter1 = iter->second.locate.begin();
		while (Siter1 != iter->second.locate.end())//两重循环，使线路间两两都建立关系
		{
			Siter2 = Siter1;
			Siter2++;
			while (Siter2 != iter->second.locate.end())
			{
				flag = FALSE;
				for (Liter = m_linelist[Siter1->whichline].relatelist.begin(); Liter != m_linelist[Siter1->whichline].relatelist.end(); Liter++)
				{
					if (Liter->lineName == Siter2->whichline)
					{
						flag = TRUE;
						break;
					}
				}
				if (flag)
				{
					Liter->StopNames->push_back(iter->first);
				}
				else
				{
					Relation rela;

					rela.StopNames = new list<CString>;
					rela.StopNames->push_back(iter->first);
					rela.lineName = Siter1->whichline;
					m_linelist[Siter2->whichline].relatelist.push_back(rela);
					rela.lineName = Siter2->whichline;
					m_linelist[Siter1->whichline].relatelist.push_back(rela);
				}
				Siter2++;
			}
			Siter1++;
		}
	}
	
	m_datasource.Close();
	m_dbsession.Close();*/
	return TRUE;
}




// CSubwayDoc 序列化

void CSubwayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSubwayDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSubwayDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSubwayDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSubwayDoc 诊断

#ifdef _DEBUG
void CSubwayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSubwayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSubwayDoc 命令
void CSubwayDoc::Pathsearching(CString startpoint, CString destination)
{
	list<Location>* location = &m_stationmap.find(startpoint)->second.locate;
	list<Location>::iterator iter;
	list<Relation>* theLine = &m_linelist[0].relatelist;
	list<Relation>::iterator Liter;

	bool visited[20]= { FALSE };
	iter = location->begin();
	visited[iter->whichline] = TRUE;
	mylinkedlist thelist(iter->whichline,startpoint);
	iter++;
	bool flagfound;
	bool flagend;
	while (iter != location->end())               ///将经过起点站的所有线路都进队列
	{
		thelist.addAtlast(NULL, iter->whichline, startpoint);
		visited[iter->whichline] = TRUE;
		iter++;
	}
	thelist.layerlast = thelist.lastnode;
	flagfound = FALSE;
	linkedNode* ptr,*pa,*theone=NULL;
	location=&m_stationmap.find(destination)->second.locate;
	while (TRUE)
	{
		ptr = thelist.layerfirst;
		while (ptr)                              //比较当前队列中是否存在经过终点的线路
		{
			iter = location->begin();
			while (iter != location->end())
			{
				if (iter->whichline == ptr->lineID)
				{
					flagfound = TRUE;           //找到了便可将标志设为真
					break;
				}
				iter++;
			}
			if (flagfound)
			{
				break;
			}
			ptr = ptr->next;
		}
		if (flagfound)                          //找到了线路，便可以结束循环
		{
			break;
		}
		ptr = thelist.layerfirst;	
		flagend = TRUE;
		while (flagend)                        //对与当前队列中每一条线路，找出所有可以换乘的线路
		{
			if (ptr == thelist.layerlast)
			{
				flagend = FALSE;
			}
			theLine = &m_linelist[ptr->lineID].relatelist;
			for each(Relation a in *theLine)         
			{
				if (!visited[a.lineName])
				{
					for each(CString s in *a.StopNames)
					{
						thelist.addAtlast(ptr, a.lineName, s);
					}
				}
			}
			ptr = ptr->next;
		} 
		thelist.tonextlayer();           //将上一层的线路都出队列，队列中为新找到的站点
		ptr = thelist.layerfirst;
		while (ptr )      //把找到的线路的访问标志都设为真
		{
			visited[ptr->lineID] = TRUE;
			ptr = ptr->next;
		}
	}
	ptr = thelist.layerfirst;
	CString  s2;
	int sum;
	int min=MY_INFINITE;
	while (ptr)            //找到所有换乘方案中距离最短的
	{
		for each(Location l in *location)
		{
			if (l.whichline == ptr->lineID)
			{
				pa = ptr;
				sum = 0;
				s2 = destination;
				
				while (pa)
				{
					sum += MesureDistance(pa->stopname, s2, pa->lineID);
					s2 = pa->stopname;
					pa = pa->prior;
				}
				if (min > sum)
				{
					min = sum;
					theone = ptr;
				}
			}
		}
		ptr = ptr->next;
	}
	s2 = destination;
	m_nTranstimes = 0;
	while (theone)   //将找到的换乘放案记录下来
	{
		GetStations(s2, theone->stopname, theone->lineID);
		s2 = theone->stopname;
		if (theone->prior&&theone->lineID != theone->prior->lineID)
		{
			m_nTranstimes++;
		}
		theone = theone->prior;	
	}
	m_Path.push_back(startpoint);
	m_nPathLength = min;
}

int CSubwayDoc::MesureDistance(CString stop1, CString stop2, int line)//计算线路上两站点之间的距离
{
	vector<station>::iterator iter1, iter2;
	int i=0,j, size;
	int count1, count2;
	while (m_linelist[line].stationlist[i].name != stop1)
	{
		i++;
	}
	if (m_linelist[line].stationlist[0].disup > 0)
	{
		count1 = count2 = 0;
		size = m_linelist[line].stationlist.size();		
		j = i;

		while (m_linelist[line].stationlist[i].name != stop2)
		{
			count1 += m_linelist[line].stationlist[i].disdown;
			i=(i+1)%size;
		}
		i = j ;
		while (m_linelist[line].stationlist[i].name != stop2)
		{
			count2 += m_linelist[line].stationlist[i].disup;
			i = (i + size - 1) % size;
		}
		return count1 < count2 ? count1 : count2;
	}
	else
	{
		j = 0;
		count1 = 0;
		while (m_linelist[line].stationlist[j].name != stop2)
		{
			j++;
		}
		if (i>j)
		{
			while (i != j)
			{
				count1 += m_linelist[line].stationlist[i].disup;
				i--;
			}
		}
		else
		{
			while (i != j)
			{
				count1 += m_linelist[line].stationlist[i].disdown;
				i++;
			}
		}
		return count1;
	}
	return 0;
}

void CSubwayDoc::GetStations(CString stop1, CString stop2, int line)//将选定线路的站点放入容器中
{
	vector<station>::iterator iter1, iter2;
	int i = 0, j, size;
	int count1, count2;
	while (m_linelist[line].stationlist[i].name != stop1)
	{
		i++;
	}
	if (m_linelist[line].stationlist[0].disup > 0)
	{
		count1 = count2 = 0;
		size = m_linelist[line].stationlist.size();
		j = i;
		while (m_linelist[line].stationlist[i].name != stop2)
		{
			count1 += m_linelist[line].stationlist[i].disdown;
			i = (i + 1) % size;
		}
		i = j;
		while (m_linelist[line].stationlist[i].name != stop2)
		{
			count2 += m_linelist[line].stationlist[i].disup;
			i = (i - 1 + size) % size;
		}
		i = j;
		if (count1 < count2)
		{
			
			while (m_linelist[line].stationlist[i].name != stop2)
			{
				m_Path.push_back(m_linelist[line].stationlist[i].name);
				i = (i + 1) % size;
			}
		}
		else
		{
			while (m_linelist[line].stationlist[i].name != stop2)
			{
				m_Path.push_back(m_linelist[line].stationlist[i].name);
				i = (i - 1 + size) % size;
			}
		}
	}
	else
	{
		j = 0;
		while (m_linelist[line].stationlist[j].name != stop2)
		{
			j++;
		}
		if (i>j)
		{
			while (i != j)
			{
				m_Path.push_back(m_linelist[line].stationlist[i].name);
				i--;
			}
		}
		else
		{
			while (i != j)
			{
				m_Path.push_back(m_linelist[line].stationlist[i].name);
				i++;
			}
		}
	}
}

void CSubwayDoc::Dijkstra(CString startpoint, CString destination)
{
	int i,  min,size;
	size = m_stationmap.size();
	map<CString, StaInfo>::iterator Miter;
	map<CString, Low> lowcost;     //动态规划的容器
	map<CString, Low>::iterator Liter1;
	Low elem;
	CString name;
	elem.weight = 0;
	elem.prior = startpoint;
	elem.lineID = -1;
	elem.factor = 0;
	lowcost.insert(pair<CString, Low>(startpoint, elem));//一开始lowcost中只有起点
	UpdateWeight(lowcost, startpoint);                   //跟新权重，并将未包含进来的站点加入容器
	for (i = 1; i < size; i++)     //开始循环，在size次之内必定能找到终点
	{
		min = MY_INFINITE;
		for (Liter1 = lowcost.begin(); Liter1 != lowcost.end(); Liter1++)//找出权重最小的站点
		{
			if (Liter1->second.factor != 0 && Liter1->second.factor<min)
			{
				min = Liter1->second.factor;
				name = Liter1->first;
			}
		}
		if (name == destination)   //找到终点，结束循环
		{
			break;
		}
		UpdateWeight(lowcost, name);  //用权重最小的点更新权重，并将没有包含的站点包含进来
	}
	Liter1 = lowcost.find(destination);//开始将线路上的站点加入容器
	m_nTranstimes = -1;
	int ID;
	while (Liter1->second.lineID != -1)
	{
		m_Path.push_back(Liter1->first);
		ID = Liter1->second.lineID;
		Liter1 = lowcost.find(Liter1->second.prior);
		if (Liter1->second.lineID != ID)
		{
			m_nTranstimes++;
		}
	}	
	m_Path.push_back(startpoint);
	m_nPathLength = lowcost.find(destination)->second.weight;
	return;
}

void CSubwayDoc::UpdateWeight(map<CString, Low>& lowcost, CString name)
{
	int size;
	int temp;
	int transfer=0;
	CString nametemp;
	map<CString, Low>::iterator Liter,Liter2;
	Liter = lowcost.find(name);
	for each(Location iter in m_stationmap.find(name)->second.locate)//对于每个站点对应的每条线路上的位置都进行操作
	{
		if (Liter->second.lineID!=-1&&Liter->second.lineID != iter.whichline)
		{
			transfer = TRANSFER_DELAY;
		}
		size = m_linelist[iter.whichline].stationlist.size();
		temp = m_linelist[iter.whichline].stationlist[iter.whichstop].disup;
		nametemp = m_linelist[iter.whichline].stationlist[(iter.whichstop - 1 + size) % size].name;
		
		if (lowcost.find(nametemp) == lowcost.end())//站点没有找到，将站点插入容器
		{
			Low elem;
			elem.factor = MY_INFINITE;
			lowcost.insert(pair<CString, Low>(nametemp, elem));
		}
		Liter2 = lowcost.find(nametemp);
		if (temp >0 && temp +transfer+ Liter->second.factor<Liter2->second.factor)//如果通过当前站点去下个站点
		{
			Liter2->second.factor = temp + transfer + Liter->second.factor;
			Liter2->second.weight = temp + Liter->second.weight;
			Liter2->second.prior = name;
			Liter2->second.lineID = iter.whichline;
		}
		temp = m_linelist[iter.whichline].stationlist[iter.whichstop].disdown;
		nametemp = m_linelist[iter.whichline].stationlist[(iter.whichstop + 1) % size].name;
		if (lowcost.find(nametemp) == lowcost.end())
		{
			Low elem;
			elem.factor = MY_INFINITE;
			lowcost.insert(pair<CString, Low>(nametemp, elem));
		}
		Liter2 = lowcost.find(nametemp);
		if (temp >0 && temp + transfer + Liter->second.factor<Liter2->second.factor)
		{
			Liter2->second.factor = temp + transfer + Liter->second.factor;
			Liter2->second.weight = temp + Liter->second.weight;
			Liter2->second.prior = name;
			Liter2->second.lineID = iter.whichline;
		}
	}
	Liter->second.factor = 0;//权重置零
}
