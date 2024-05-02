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
		//��ʼ���ڽӾ���������޵�������ģ��򶥵������������ģ�Ȩ�ض���Ϊ0
		for (int j = 0; j < 20; j++)
			graph.m_aAdjMatrix[i][j] = 0;
	}
}

bool InsertVex(Vex sVex) {
	if (graph.m_nVexNum == MAX_VERTEX_NUM)
	{
		//��������
		return false;
	}
	//���붥����Ϣ
	graph.m_aVexs[graph.m_nVexNum++] = sVex;
	return true;
}

bool InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= graph.m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= graph.m_nVexNum)
	{
		//�±�Խ��
		return false;
	}
	//����ߵ���Ϣ
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
	//��ʼ�����ж��㣬Ĭ��ֵΪfalse
	int nIndex = 0;
	bool bVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, bVisited, nIndex, pList);
}

void DFS(int nVex, bool bVisited[], int& nIndex, PathList& pList) {
	bVisited[nVex] = true; //��Ϊ�ѷ���
	pList->vexs[nIndex++] = nVex; //���ʶ���nVex����¼��pList��
	int nVexNum = 0;

	//����
	for (int i = 0; i < graph.m_nVexNum; i++) {
		if (bVisited[i]) nVexNum++;
	}
	//�ж��Ƿ����ж��㶼���ʹ�
	if (nVexNum == graph.m_nVexNum) {
		//����һ��·��
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
			//�ж�i�Ƿ�ΪnVex���ڽӵ�
			if ((graph.m_aAdjMatrix[nVex][i] > 0) && !bVisited[i] && (graph.m_aAdjMatrix[nVex][i] != MAX_WEIGHT)) {
				//�ݹ����DFS�õ�һ��·��
				DFS(i, bVisited, nIndex, pList);
				bVisited[i] = false;    //�õ�һ��·���󽫷��ʵ�i���Ϊδ����״̬
				nIndex--;   //����ֵ��һ�����ݵ���һ���ڵ㣬�Ա�ѡ����һ��·��������ȱ���
				//nIndex��Ϊ���ô��ݸ��ݹ麯����ʹ���ڵݹ���õĹ����ж� nIndex �ĸı��Ӱ�쵽��㺯���е� nIndex ����
			}
		}
	}
}

int Dijkstra(int nVexStart, int nVexEnd, Edge aPath[]) {
	bool aVisited[MAX_VERTEX_NUM];	//aVisited�������
	int prior[MAX_VERTEX_NUM], min_weight[MAX_VERTEX_NUM], newVex;    //priorǰ�ö��㣬min_weight����֮����СȨ�أ�newVex��¼����·�����¶���
	//��ʼ�����·��
	for (int i = 0; i < graph.m_nVexNum; i++) {
		aVisited[i] = false;
		prior[i] = -1;
		if (graph.m_aAdjMatrix[nVexStart][i] > 0 || i == nVexStart) {
			min_weight[i] = graph.m_aAdjMatrix[nVexStart][i];//�������
			prior[i] = nVexStart;   //��������ֱ������ʱ��prior��ʼ��Ϊ���
		}
		else {
			min_weight[i] = MAX_WEIGHT;//���㲻����
		}
	}
	aVisited[nVexStart] = true; //��һ�������Ӧ�������

	int min;
	//ÿ���ҳ�һ����������·��
	for (int i = 1; i < graph.m_nVexNum; i++) {
		//Ѱ�ҵ�ǰ��Ȩ����С��·����minΪĿǰ��¼����ʼ�㵽���������̾���
		min = MAX_WEIGHT;
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == false && min_weight[j] < min) {
				min = min_weight[j];
				newVex = j; //��¼��ǰ��СȨ�صĶ���
			}
		}
		aVisited[newVex] = true;   //���ö������·����

		//��newVexΪ�յ㣬���رߵ���Ŀ
		if (newVex == nVexEnd)
			break;

		//��newVex��Ϊ�м�����nVexSart�����ж�������·�����������伯��
		for (int j = 0; j < graph.m_nVexNum; j++) {
			int temp;
			if (graph.m_aAdjMatrix[newVex][j] == 0) {
				temp = MAX_WEIGHT;
			}
			else {
				//���µ����·�������ݴ浽temp��
				//min��ʼ�㵽�¶���ľ��룬m_aAdjMatrix[newVex][j]�¶��㵽������ľ���
				temp = min + graph.m_aAdjMatrix[newVex][j];
			}
			//�����µ���̾��룬��������·��
			if (aVisited[j] == false && (temp < min_weight[j])) {
				min_weight[j] = temp;
				prior[j] = newVex;
			}
		}
	}

	int Num = 0; //Num�ߵ�����
	int i = nVexEnd;
	//���յ㿪ʼ����
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
	int aVisited[20], prior[20];//aVisited������飬priorǰ������
	int min_weight[20];//����֮����СȨ��

	//��ʼ������
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
	//�ҳ������֮���������
	int min, index;  //min������ʱ�ж�Ȩ�ش�С��index��¼��ǰ��ѡȡ������СȨ�ر�ָ��Ķ��������
	for (int i = 1; i < graph.m_nVexNum; i++) {
		min = MAX_WEIGHT;
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == 0 && min_weight[j] < min) {
				min = min_weight[j];
				index = j;	//��ǰ��СȨ�ر�ָ��Ķ��������
			}
		}

		aVisited[index] = 1;    //��¼�ö����ѷ���
		//ˢ����index�������󣬸���Ȩ�ر仯
		for (int j = 0; j < graph.m_nVexNum; j++) {
			if (aVisited[j] == 0 && graph.m_aAdjMatrix[index][j] < min_weight[j] && graph.m_aAdjMatrix[index][j] != 0) {
				min_weight[j] = graph.m_aAdjMatrix[index][j];
				prior[j] = index;
			}
		}

		//�洢�����µ���γɵ��±���Ϣ��aEdge������
		aVisited[prior[index]] = 1;
		aEdge[Num].vex1 = prior[index];
		aEdge[Num].vex2 = index;
		aEdge[Num].weight = graph.m_aAdjMatrix[prior[index]][index];
		Num++;
	}
	return Num;
}