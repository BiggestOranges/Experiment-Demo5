#include "Tourism.h"
#include "Graph.h"

extern Cgraph graph;	//访问Graph.cpp中定义的变量
void CreateGraph() {
	cout << COLOR_CYAN << "= = = = = 创建景区景点图 = = = = =" << COLOR_RESET << endl;
	//初始化图
	Init();

	//设置图的顶点
	int num;
	FILE* InVex = fopen("Vex.txt", "r");
	fscanf(InVex, "%d", &num);
	cout << "顶点数目：" << num << endl;
	cout << "\n= = = = =顶点= = = = =" << endl;
	for (int i = 0; i < num; i++)
	{
		Vex vex;
		fscanf(InVex, "%d", &(vex.num));
		fscanf(InVex, "%s", vex.name);
		fscanf(InVex, "%s", vex.desc);
		cout << vex.num << "-" << vex.name << endl;
		InsertVex(vex);
	}
	fclose(InVex);

	//设置图的边
	FILE* InEdge = fopen("Edge.txt", "r");
	cout << "\n= = = = =边= = = = =" << endl;
	while (!feof(InEdge))
	{
		Edge edge;
		fscanf(InEdge, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);
		cout << "<v" << edge.vex1 << ",v" << edge.vex2 << "> " << edge.weight << endl;
		InsertEdge(edge);
	}
	fclose(InEdge);
}

bool PrintInfo(int num)
{
	if (graph.m_nVexNum == 0) {
		cout << COLOR_YELLOW << "景区景点暂未设立，请下次再来！" << COLOR_RESET << endl;
		return false;
	}
	switch (num)
	{
	case 2:
		cout << COLOR_CYAN << "= = = = = 查询景点信息 = = = = =" << COLOR_RESET << endl;
		break;
	case 3:
		cout << COLOR_CYAN << "= = = = = 旅游景点导航 = = = = =" << COLOR_RESET << endl;
		break;
	case 4:
		cout << COLOR_CYAN << "= = = = = 搜索最短路径 = = = = =" << COLOR_RESET << endl;
		break;
	case 5:
		cout << COLOR_CYAN << "= = = = = 铺设电路规划 = = = = =" << COLOR_RESET << endl;
		break;
	default:
		return false;
	}
	for (int i = 0; i < graph.m_nVexNum; i++)
		cout << graph.m_aVexs[i].num << " - " << graph.m_aVexs[i].name << endl;
	cout << endl;

	return true;
}

void GetSpotInfo() {
	//判断图是否存在，打印顶点信息
	bool flag = PrintInfo(2);
	if (!flag) return;

	//读取输入
	int Num;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "请输入想要查询的景点编号" << COLOR_YELLOW << "(0 ~" << n << ")：" << COLOR_RESET;
		cin >> Num;
		if (Num < 0 || Num >= graph.m_nVexNum) {
			cout << "\n没有找到对应编号的景区，请" << COLOR_RED << "重新输入！" << COLOR_RESET << endl;
		}
		else break;
	}

	Vex vex = GetVex(Num);
	cout << "\n景区特点：" << vex.desc << endl << endl;
	cout << "= = = = = 周围景区 = = = = =" << endl;
	Edge aEdge[100];
	int sum_Edge = FindEdge(Num, aEdge);
	for (int i = 0; i < sum_Edge; i++) {
		if (aEdge[i].weight != MAX_WEIGHT) {
			cout << graph.m_aVexs[aEdge[i].vex1].name << " -> " <<
				graph.m_aVexs[aEdge[i].vex2].name << " 距离 " << aEdge[i].weight << "m" << endl;
		}
	}
}

void TravelPath() {
	//判断图是否存在，打印顶点信息
	bool flag = PrintInfo(3);
	if (!flag) return;

	//读取输入
	int Num;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "请输入" << COLOR_YELLOW << "起始点" << COLOR_RESET << "编号" << COLOR_YELLOW << "(0 ~" << n << ")：" << COLOR_RESET;
		cin >> Num;
		if (Num < 0 || Num >= graph.m_nVexNum) {
			cout << "\n没有找到对应编号的景区，请" << COLOR_RED << "重新输入！" << COLOR_RESET << endl;
		}
		else break;
	}

	cout << "导游路线为：" << endl;
	PathList pList = (PathList)malloc(sizeof(Path));
	PathList Head = pList;
	//深度遍历景区图，规划出所有可用路线
	DFSTraverse(Num, pList);
	pList = Head;

	//输出遍历结果
	int ct = 1;
	while (pList->next != NULL) {
		cout << "路线" << ct << "：";
		for (int i = 0; i < graph.m_nVexNum; i++) {
			cout << graph.m_aVexs[pList->vexs[i]].name;
			if (i != graph.m_nVexNum - 1) cout << " -> ";
		}
		cout << endl;
		pList = pList->next;
		ct++;
	}
	free(pList);
	pList = NULL;
	Head = NULL;
}

void FindPath() {
	//判断图是否存在，打印顶点信息
	bool flag = PrintInfo(4);
	if (!flag) return;

	//读取输入
	int nStart, nEnd;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "请输入" << COLOR_YELLOW << "起点" << COLOR_RESET << "编号" << COLOR_YELLOW << "(0 ~" << n << ")：" << COLOR_RESET;
		cin >> nStart;
		cout << "请输入" << COLOR_YELLOW << "终点" << COLOR_RESET << "编号" << COLOR_YELLOW << "(0 ~" << n << ")：" << COLOR_RESET;
		cin >> nEnd;
		if (nEnd >= graph.m_nVexNum || nStart >= graph.m_nVexNum || nEnd < 0 || nStart < 0) {
			cout << "\n没有找到对应编号的景区，请" << COLOR_RED << "重新输入！" << COLOR_RESET << endl;
		}
		else if (nStart == nEnd) {
			cout << "\n起点不能与终点相同，请" << COLOR_RED << "重新输入！" << COLOR_RESET << endl;
		}
		else break;
	}

	//开始搜索最短路径
	Edge aPath[MAX_VERTEX_NUM];
	int Num = Dijkstra(nStart, nEnd, aPath);
	cout << "最短路径为：" << endl;
	int Path = 0;
	for (int i = Num - 1; i >= 0; i--) {
		cout << graph.m_aVexs[aPath[i].vex1].name << " -> ";
		cout << graph.m_aVexs[aPath[i].vex2].name << endl;
		Path += aPath[i].weight;
	}
	cout << "最短距离为：" << Path << "m" << endl;
}

void DesignPath() {
	//判断图是否存在，打印顶点信息
	bool flag = PrintInfo(5);
	if (!flag) return;

	//读取输入
	int nStart;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "请输入您要铺设电路的" << COLOR_YELLOW << "起始顶点(0 ~" << n << ")：" << COLOR_RESET;
		cin >> nStart;
		if (nStart < 0 || nStart >= graph.m_nVexNum) {
			cout << "\n没有找到对应编号的景区，请" << COLOR_RED << "重新输入！" << COLOR_RESET << endl;
		}
		else break;
	}

	//开始规划电路
	Edge aEdge[20];
	int Num = Prim(nStart, aEdge), Path = 0;
	//输出
	cout << "电路规划如下：" << endl;
	for (int i = 0; i < Num; i++) {
		cout << graph.m_aVexs[aEdge[i].vex1].name << " -> "
			<< graph.m_aVexs[aEdge[i].vex2].name << "\t长度："
			<< aEdge[i].weight << "m" << endl;
		Path += aEdge[i].weight;
	}
	cout << "铺设电路的总长度为：" << Path << "m" << endl;
}