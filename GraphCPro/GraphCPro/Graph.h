#ifndef GRAPH_H
#define GRAPH_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define MAX_VERTEX_NUM 999	//��󶥵�����
#define MAX_WEIGHT 999999	//����Ȩֵ
using namespace std;

struct Vex
{
	int num;	//������
	char name[20];	//��������
	char desc[1024];	//�������
};

struct Edge
{
	int vex1;	//�ߵĵ�һ������
	int vex2;	//�ߵĵڶ�������
	int weight;	//Ȩֵ
};

struct Cgraph
{
	int m_aAdjMatrix[20][20];	//�ڽӾ���
	Vex m_aVexs[20];		//������Ϣ����
	int m_nVexNum;	//��ǰͼ�Ķ������
};

typedef struct Path
{
	int vexs[20];	//����һ��·��
	Path *next;	//������һ��·��
}*PathList;	//*PathList��ָ��ṹ���ָ��

void Init();	//��ʼ��ͼ
bool InsertVex(Vex sVex);	//���붥��
bool InsertEdge(Edge sEdge);	//�����
Vex GetVex(int nVex);	//���ض�����Ϣ
int FindEdge(int nVex, Edge aEdge[]);	//�����ڽӵı߲����رߵ�����
void DFSTraverse(int nVex, PathList& pList);	//DFS��ȱ����㷨��ͨ���ݹ����DFS������ʵ�֣�nVex�����ţ�pList�����õ��Ľ��
void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);	//����DFS������nVex�����ţ�bVisited��¼ĳ�������Ƿ񱻱�������nIndex��¼��������ȣ�pList�����õ��Ľ��
int Dijkstra(int nVexStart, int nVexEnd, Edge aPath[]);	//�Ͻ�˹�����㷨�������·��
int Prim(int nStart, Edge aEdge[]);	//Prim�㷨������С������

#endif // !GRAPH_H