// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// SubwayDoc.h : CSubwayDoc ��Ľӿ�
//


#pragma once
#include "Structure.h"
#include <map>

class CSubwayDoc : public CDocument
{
protected: // �������л�����
	CSubwayDoc();
	DECLARE_DYNCREATE(CSubwayDoc)

// ����
public:
	map<CString, StaInfo> m_stationmap;         //��վ������վ����Ϣ��ӳ��
	vector<Route> m_linelist;                   //�洢��·��Ϣ������
	vector<CString> m_Path;                     //�洢�㷨����·��������
	void Pathsearching(CString startpoint, CString destination); //���ٻ����㷨
	int MesureDistance(CString stop1, CString stop2, int line);  //���ٻ����㷨�е��õĲ���������վ֮����뺯��
	void GetStations(CString stop1, CString stop2, int line);//���ٻ����㷨�н������˵���վ����������ĺ���
	void Dijkstra(CString startpoint, CString destination);//���·��������ʹ�õ��ǻ����ڽӱ�ĵϽܿ�˹���㷨
	void UpdateWeight(map<CString, Low>& lowcost,CString name);//�Ͻܿ�˹���㷨�и���Ȩ�صĺ���
	int m_nPathLength;      //��¼·���ĳ���
	int TRANSFER_DELAY;     //���˵�Ȩ��
	int m_nTranstimes;      //��¼���˵Ĵ���
// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CSubwayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
