#ifndef GRAPH_H
#define GRAPH_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define MAX_VERTEX_NUM 999	//最大顶点数量
#define MAX_WEIGHT 999999	//最大边权值
using namespace std;

struct Vex
{
	int num;	//景点编号
	char name[20];	//景点名字
	char desc[1024];	//景点介绍
};

struct Edge
{
	int vex1;	//边的第一个顶点
	int vex2;	//边的第二个顶点
	int weight;	//权值
};

struct Cgraph
{
	int m_aAdjMatrix[20][20];	//邻接矩阵
	Vex m_aVexs[20];		//顶点信息数组
	int m_nVexNum;	//当前图的顶点个数
};

typedef struct Path
{
	int vexs[20];	//保存一条路径
	Path *next;	//保存下一条路径
}*PathList;	//*PathList是指向结构体的指针

void Init();	//初始化图
bool InsertVex(Vex sVex);	//插入顶点
bool InsertEdge(Edge sEdge);	//插入边
Vex GetVex(int nVex);	//返回顶点信息
int FindEdge(int nVex, Edge aEdge[]);	//导入邻接的边并返回边的总数
void DFSTraverse(int nVex, PathList& pList);	//DFS深度遍历算法，通过递归调用DFS函数来实现，nVex顶点编号，pList遍历得到的结果
void DFS(int nVex, bool bVisited[], int &nIndex, PathList &pList);	//单次DFS遍历，nVex顶点编号，bVisited记录某个顶点是否被遍历过，nIndex记录遍历的深度，pList遍历得到的结果
int Dijkstra(int nVexStart, int nVexEnd, Edge aPath[]);	//迪杰斯特拉算法，求最短路径
int Prim(int nStart, Edge aEdge[]);	//Prim算法，求最小生成树

#endif // !GRAPH_H