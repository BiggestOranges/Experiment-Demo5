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

void CreateGraph();	//创建景点图
bool PrintInfo(int num);	//打印各顶点信息
void GetSpotInfo();	//查询景点信息
void PrintInfo(bool& retFlag);
void TravelPath();	//旅游景点导航
void FindPath();	//搜索最短路径
void DesignPath();	//铺设电路规划

#endif // !TOURISM_H