#include "Graph.h"

Cgraph graph;

void Init()
{
	graph.m_nVexNum = 0;
	int i;
	for (i = 0; i < 20; i++)
	{
		graph.m_aVexs[i].num = -1;
		strcpy(graph.m_aVexs[i].name, "null");
		strcpy(graph.m_aVexs[i].desc, "null");
		//初始化邻接矩阵，两点间无单边连结的，或顶点与自身相连的，权重都置为0
		for (int j = 0; j < 20; j++)
			graph.m_aAdjMatrix[i][j] = 0;
	}
}

bool InsertVex(Vex sVex) {
	if (graph.m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return false;
	}
	//插入顶点信息
	graph.m_aVexs[graph.m_nVexNum++] = sVex;
	return true;
}

bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= graph.m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= graph.m_nVexNum)
	{
		//下标越界
		return false;
	}
	//插入边的信息
	graph.m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	graph.m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex GetVex(int nVex) {
	return graph.m_aVexs[nVex];
}

int FindEdge(int nVex, Edge aEdge[]) {
	int ct = 0;
	for (int i = 0; i < graph.m_nVexNum; i++)
	{
		if (graph.m_aAdjMatrix[nVex][i] != 0)
		{
			aEdge[ct].vex1 = nVex;
			aEdge[ct].vex2 = i;
			aEdge[ct].weight = graph.m_aAdjMatrix[nVex][i];
			ct++;
		}
	}
	return ct;
}

void DFSTraverse(int nVex, PathList& pList) {
	//初始化所有顶点，默认值为false
	int nIndex = 0;
	bool bVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, bVisited, nIndex, pList);
}

void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList) {
	bVisited[nVex] = true; //改为已访问
	pList->vexs[nIndex++] = nVex; //访问顶点nVex，记录在pList中
	int nVexNum = 0;

	//搜索
	for (int i = 0; i < graph.m_nVexNum; i++) {
		if (bVisited[i]) nVexNum++;
	}
	//判断是否所有顶点都访问过
	if (nVexNum == graph.m_nVexNum) {
		//保存一条路径
		pList->next = (PathList)malloc(sizeof(Path));
		for (int i = 0; i < graph.m_nVexNum; i++) {
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}

	else {
		for (int i = 0; i < graph.m_nVexNum; i++)
		{
			//判断i是否为nVex的邻接点
			if ((graph.m_aAdjMatrix[nVex][i] > 0) && !bVisited[i] && (graph.m_aAdjMatrix[nVex][i] != MAX_WEIGHT)) {
				//递归调用DFS得到一条路径
				DFS(i, bVisited, nIndex, pList);
				bVisited[i] = false;    //得到一条路径后将访问的i点改为未访问状态
				nIndex--;   //索引值减一，回溯到上一个节点，以便选择另一条路径进行深度遍历
				//nIndex作为引用传递给递归函数，使得在递归调用的过程中对 nIndex 的改变会影响到外层函数中的 nIndex 变量
			}
		}
	}
}

int Dijkstra(int nVexStart, int nVexEnd, Edge aPath[]) {
	bool aVisited[MAX_VERTEX_NUM];	//aVisited标记数组
	int prior[MAX_VERTEX_NUM], min_weight[MAX_VERTEX_NUM], newVex;    //prior前置顶点，min_weight两点之间最小权重，newVex记录加入路径的新顶点
	//初始化最短路径
	for (int i = 0; i < graph.m_nVexNum; i++) {
		aVisited[i] = false;
		prior[i] = -1;
		if (graph.m_aAdjMatrix[nVexStart][i] > 0 || i == nVexStart) {
			min_weight[i] = graph.m_aAdjMatrix[nVexStart][i];//两点距离
			prior[i] = nVexStart;   //当两个边直接相连时，prior初始化为起点
		}
		else {
			min_weight[i] = MAX_WEIGHT;//两点不相邻
		}
	}
	aVisited[nVexStart] = true; //第一个并入的应该是起点

	int min;
	//每次找出一个顶点的最短路径
	for (int i = 1; i < graph.m_nVexNum; i++) {
		//寻找当前总权重最小的路径，min为目前记录的起始点到各顶点的最短距离
		min = MAX_WEIGHT;
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == false && min_weight[j] < min) {
				min = min_weight[j];
				newVex = j; //记录当前最小权重的顶点
			}
		}
		aVisited[newVex] = true;   //将该顶点加入路径中

		//若newVex为终点，返回边的数目
		if (newVex == nVexEnd)
			break;

		//将newVex作为中间点计算nVexSart到所有顶点的最短路径，进行扩充集合
		for (int j = 0; j < graph.m_nVexNum; j++) {
			int temp;
			if (graph.m_aAdjMatrix[newVex][j] == 0) {
				temp = MAX_WEIGHT;
			}
			else {
				//更新的最短路径长度暂存到temp中
				//min起始点到新顶点的距离，m_aAdjMatrix[newVex][j]新顶点到各顶点的距离
				temp = min + graph.m_aAdjMatrix[newVex][j];
			}
			//若有新的最短距离，则更新最短路径
			if (aVisited[j] == false && (temp < min_weight[j])) {
				min_weight[j] = temp;
				prior[j] = newVex;
			}
		}
	}

	int Num = 0; //Num边的总数
	int i = nVexEnd;
	//从终点开始回溯
	while (i != nVexStart) {
		aPath[Num].vex2 = i;
		aPath[Num].vex1 = prior[i];
		aPath[Num].weight = graph.m_aAdjMatrix[prior[i]][i];
		i = prior[i];
		Num++;
	}
	return Num;
}

int Prim(int nStart, Edge aEdge[]) {
	int aVisited[20], prior[20];//aVisited标记数组，prior前驱顶点
	int min_weight[20];//两点之间最小权重

	//初始化数据
	for (int i = 0; i < graph.m_nVexNum; i++) {
		prior[i] = -1;
		aVisited[i] = 0;
		if (graph.m_aAdjMatrix[nStart][i] > 0 || i == nStart) {
			min_weight[i] = graph.m_aAdjMatrix[nStart][i];
			prior[i] = nStart;
		}
		else {
			min_weight[i] = MAX_WEIGHT;
		}
	}
	aVisited[nStart] = 1;

	int Num = 0;
	//找出除起点之外的其他边
	int min, index;  //min用来临时判断权重大小，index记录当前能选取到的最小权重边指向的顶点的索引
	for (int i = 1; i < graph.m_nVexNum; i++) {
		min = MAX_WEIGHT;
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == 0 && min_weight[j] < min) {
				min = min_weight[j];
				index = j;	//当前最小权重边指向的顶点的索引
			}
		}

		aVisited[index] = 1;    //记录该顶点已访问
		//刷新在index顶点加入后，各边权重变化
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == 0 && graph.m_aAdjMatrix[index][j] < min_weight[j] && graph.m_aAdjMatrix[index][j] != 0) {
				min_weight[j] = graph.m_aAdjMatrix[index][j];
				prior[j] = index;
			}
		}

		//存储加入新点后形成的新边信息至aEdge数组中
		aVisited[prior[index]] = 1;
		aEdge[Num].vex1 = prior[index];
		aEdge[Num].vex2 = index;
		aEdge[Num].weight = graph.m_aAdjMatrix[prior[index]][index];
		Num++;
	}
	return Num;
}