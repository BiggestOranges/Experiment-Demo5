#ifndef TOURISM_H
#define TOURISM_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#define COLOR_CYAN    "\033[1m\033[3m\033[36m"
#define COLOR_YELLOW  "\033[1m\033[33m"
#define COLOR_RED     "\033[1m\033[31m"
#define COLOR_RESET "\033[0m"
using namespace std;

void CreateGraph();	//��������ͼ
bool PrintInfo(int num);	//��ӡ��������Ϣ
void GetSpotInfo();	//��ѯ������Ϣ
void PrintInfo(bool& retFlag);
void TravelPath();	//���ξ��㵼��
void FindPath();	//�������·��
void DesignPath();	//�����·�滮

#endif // !TOURISM_H