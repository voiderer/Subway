#pragma once
#include <vector>
#include <list>
#include "stdafx.h"
using namespace std;

#define MY_INFINITE 99999999
#define STOP_DELAY 100
//////////////////////////////

struct Location         //站点映射中站点在线路信息表中的定位
{
	int whichline;      //表示此站点存在的线路在容器中的下标
	int whichstop;      //表示此站点在线路对于的站点数组的下标
};
struct StaInfo
{
	CPoint pos;              //表示该站点绘图时候的坐标
	list<Location> locate;   //表示该站点对应的线路信息表中的位置
};
/////////////////////////////////////////////////////////////////
struct station          //线路信息中线路列表中的单元结构
{
	int disup;          //当前站点到前一个站的距离
	int disdown;        //当前站点到后一个站点的距离
	CString name;       //次此站点名
};

struct Relation                    //线路相交关系的邻接表的数据成员
{
	int lineName;                  //线路在数组中对应的下标
	list<CString>* StopNames;      //两个线路线交的站点链表（邻接表两个对应的结点共享一个链表）
};

struct Route                       //线路信息表的单元
{
	COLORREF m_color;              //线路的颜色
	CString name;                  //线路的名称
	vector<station> stationlist;   //线路对应的站点数组
	list<Relation> relatelist;     //线路之间的相交关系邻接表
};

struct Low
{
	CString prior;
	int lineID;
	int weight;
	int factor;
};

///////////////////////////////////////

class linkedNode
{
public:
	CString stopname; //此站点名
	int lineID;       //到达此站点的线路
	linkedNode* prior;//到达此站点的前一个站点的指针
	linkedNode* next; //链表的下一个结点的指针
	linkedNode(linkedNode* priornode = NULL,int ID =0,CString statID = _T(""), linkedNode* nextnode = NULL)//构造函数
	{
		this->lineID = ID;
		this->prior = priornode;
		this->next = nextnode;
		this->stopname = statID;
	}
};


class mylinkedlist
{
public:
	linkedNode* firstnode;  //指向第一个结点
	linkedNode* layerfirst; //指向当前深度的第一个结点，表示此队列的开头
	linkedNode* layerlast;  //指向当前深度的最后一个结点，表示此队列的最后一个元素
	linkedNode* lastnode;   //指向最后一个结点
	mylinkedlist(int ID,CString name = _T(""))
	{
		firstnode = lastnode = layerfirst = layerlast = new linkedNode(NULL, ID, name, NULL);
	}
	~mylinkedlist()
	{
		linkedNode* p, *q;
		p = firstnode;
		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}
	void addAtlast(linkedNode* priornode,int ID, CString nodeID)
	{
		lastnode->next = new linkedNode(priornode, ID,nodeID, NULL);
		lastnode = lastnode->next;
	}
	void tonextlayer()
	{
		layerfirst = layerlast->next;
		layerlast = lastnode;
	}
};

COLORREF ConvertToColor(long num);
