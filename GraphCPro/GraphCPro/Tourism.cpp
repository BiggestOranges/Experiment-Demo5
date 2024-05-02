#include "Tourism.h"
#include "Graph.h"

extern Cgraph graph;	//����Graph.cpp�ж���ı���
void CreateGraph() {
	cout << COLOR_CYAN << "= = = = = ������������ͼ = = = = =" << COLOR_RESET << endl;
	//��ʼ��ͼ
	Init();

	//����ͼ�Ķ���
	int num;
	FILE* InVex = fopen("Vex.txt", "r");
	fscanf(InVex, "%d", &num);
	cout << "������Ŀ��" << num << endl;
	cout << "\n= = = = =����= = = = =" << endl;
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

	//����ͼ�ı�
	FILE* InEdge = fopen("Edge.txt", "r");
	cout << "\n= = = = =��= = = = =" << endl;
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
		cout << COLOR_YELLOW << "����������δ���������´�������" << COLOR_RESET << endl;
		return false;
	}
	switch (num)
	{
	case 2:
		cout << COLOR_CYAN << "= = = = = ��ѯ������Ϣ = = = = =" << COLOR_RESET << endl;
		break;
	case 3:
		cout << COLOR_CYAN << "= = = = = ���ξ��㵼�� = = = = =" << COLOR_RESET << endl;
		break;
	case 4:
		cout << COLOR_CYAN << "= = = = = �������·�� = = = = =" << COLOR_RESET << endl;
		break;
	case 5:
		cout << COLOR_CYAN << "= = = = = �����·�滮 = = = = =" << COLOR_RESET << endl;
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
	//�ж�ͼ�Ƿ���ڣ���ӡ������Ϣ
	bool flag = PrintInfo(2);
	if (!flag) return;

	//��ȡ����
	int Num;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "��������Ҫ��ѯ�ľ�����" << COLOR_YELLOW << "(0 ~" << n << ")��" << COLOR_RESET;
		cin >> Num;
		if (Num < 0 || Num >= graph.m_nVexNum) {
			cout << "\nû���ҵ���Ӧ��ŵľ�������" << COLOR_RED << "�������룡" << COLOR_RESET << endl;
		}
		else break;
	}

	Vex vex = GetVex(Num);
	cout << "\n�����ص㣺" << vex.desc << endl << endl;
	cout << "= = = = = ��Χ���� = = = = =" << endl;
	Edge aEdge[100];
	int sum_Edge = FindEdge(Num, aEdge);
	for (int i = 0; i < sum_Edge; i++) {
		if (aEdge[i].weight != MAX_WEIGHT) {
			cout << graph.m_aVexs[aEdge[i].vex1].name << " -> " <<
				graph.m_aVexs[aEdge[i].vex2].name << " ���� " << aEdge[i].weight << "m" << endl;
		}
	}
}

void TravelPath() {
	//�ж�ͼ�Ƿ���ڣ���ӡ������Ϣ
	bool flag = PrintInfo(3);
	if (!flag) return;

	//��ȡ����
	int Num;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "������" << COLOR_YELLOW << "��ʼ��" << COLOR_RESET << "���" << COLOR_YELLOW << "(0 ~" << n << ")��" << COLOR_RESET;
		cin >> Num;
		if (Num < 0 || Num >= graph.m_nVexNum) {
			cout << "\nû���ҵ���Ӧ��ŵľ�������" << COLOR_RED << "�������룡" << COLOR_RESET << endl;
		}
		else break;
	}

	cout << "����·��Ϊ��" << endl;
	PathList pList = (PathList)malloc(sizeof(Path));
	PathList Head = pList;
	//��ȱ�������ͼ���滮�����п���·��
	DFSTraverse(Num, pList);
	pList = Head;

	//����������
	int ct = 1;
	while (pList->next != NULL) {
		cout << "·��" << ct << "��";
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
	//�ж�ͼ�Ƿ���ڣ���ӡ������Ϣ
	bool flag = PrintInfo(4);
	if (!flag) return;

	//��ȡ����
	int nStart, nEnd;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "������" << COLOR_YELLOW << "���" << COLOR_RESET << "���" << COLOR_YELLOW << "(0 ~" << n << ")��" << COLOR_RESET;
		cin >> nStart;
		cout << "������" << COLOR_YELLOW << "�յ�" << COLOR_RESET << "���" << COLOR_YELLOW << "(0 ~" << n << ")��" << COLOR_RESET;
		cin >> nEnd;
		if (nEnd >= graph.m_nVexNum || nStart >= graph.m_nVexNum || nEnd < 0 || nStart < 0) {
			cout << "\nû���ҵ���Ӧ��ŵľ�������" << COLOR_RED << "�������룡" << COLOR_RESET << endl;
		}
		else if (nStart == nEnd) {
			cout << "\n��㲻�����յ���ͬ����" << COLOR_RED << "�������룡" << COLOR_RESET << endl;
		}
		else break;
	}

	//��ʼ�������·��
	Edge aPath[MAX_VERTEX_NUM];
	int Num = Dijkstra(nStart, nEnd, aPath);
	cout << "���·��Ϊ��" << endl;
	int Path = 0;
	for (int i = Num - 1; i >= 0; i--) {
		cout << graph.m_aVexs[aPath[i].vex1].name << " -> ";
		cout << graph.m_aVexs[aPath[i].vex2].name << endl;
		Path += aPath[i].weight;
	}
	cout << "��̾���Ϊ��" << Path << "m" << endl;
}

void DesignPath() {
	//�ж�ͼ�Ƿ���ڣ���ӡ������Ϣ
	bool flag = PrintInfo(5);
	if (!flag) return;

	//��ȡ����
	int nStart;
	while (true)
	{
		int n = graph.m_nVexNum - 1;
		cout << "��������Ҫ�����·��" << COLOR_YELLOW << "��ʼ����(0 ~" << n << ")��" << COLOR_RESET;
		cin >> nStart;
		if (nStart < 0 || nStart >= graph.m_nVexNum) {
			cout << "\nû���ҵ���Ӧ��ŵľ�������" << COLOR_RED << "�������룡" << COLOR_RESET << endl;
		}
		else break;
	}

	//��ʼ�滮��·
	Edge aEdge[20];
	int Num = Prim(nStart, aEdge), Path = 0;
	//���
	cout << "��·�滮���£�" << endl;
	for (int i = 0; i < Num; i++) {
		cout << graph.m_aVexs[aEdge[i].vex1].name << " -> "
			<< graph.m_aVexs[aEdge[i].vex2].name << "\t���ȣ�"
			<< aEdge[i].weight << "m" << endl;
		Path += aEdge[i].weight;
	}
	cout << "�����·���ܳ���Ϊ��" << Path << "m" << endl;
}