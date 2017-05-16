#pragma once
#include <vector>
#include <list>
#include "stdafx.h"
using namespace std;

#define MY_INFINITE 99999999
#define STOP_DELAY 100
//////////////////////////////

struct Location         //վ��ӳ����վ������·��Ϣ���еĶ�λ
{
	int whichline;      //��ʾ��վ����ڵ���·�������е��±�
	int whichstop;      //��ʾ��վ������·���ڵ�վ��������±�
};
struct StaInfo
{
	CPoint pos;              //��ʾ��վ���ͼʱ�������
	list<Location> locate;   //��ʾ��վ���Ӧ����·��Ϣ���е�λ��
};
/////////////////////////////////////////////////////////////////
struct station          //��·��Ϣ����·�б��еĵ�Ԫ�ṹ
{
	int disup;          //��ǰվ�㵽ǰһ��վ�ľ���
	int disdown;        //��ǰվ�㵽��һ��վ��ľ���
	CString name;       //�δ�վ����
};

struct Relation                    //��·�ཻ��ϵ���ڽӱ�����ݳ�Ա
{
	int lineName;                  //��·�������ж�Ӧ���±�
	list<CString>* StopNames;      //������·�߽���վ�������ڽӱ�������Ӧ�Ľ�㹲��һ������
};

struct Route                       //��·��Ϣ��ĵ�Ԫ
{
	COLORREF m_color;              //��·����ɫ
	CString name;                  //��·������
	vector<station> stationlist;   //��·��Ӧ��վ������
	list<Relation> relatelist;     //��·֮����ཻ��ϵ�ڽӱ�
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
	CString stopname; //��վ����
	int lineID;       //�����վ�����·
	linkedNode* prior;//�����վ���ǰһ��վ���ָ��
	linkedNode* next; //�������һ������ָ��
	linkedNode(linkedNode* priornode = NULL,int ID =0,CString statID = _T(""), linkedNode* nextnode = NULL)//���캯��
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
	linkedNode* firstnode;  //ָ���һ�����
	linkedNode* layerfirst; //ָ��ǰ��ȵĵ�һ����㣬��ʾ�˶��еĿ�ͷ
	linkedNode* layerlast;  //ָ��ǰ��ȵ����һ����㣬��ʾ�˶��е����һ��Ԫ��
	linkedNode* lastnode;   //ָ�����һ�����
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
