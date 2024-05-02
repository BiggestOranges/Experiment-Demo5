#include "Graph.h"
#include "Tourism.h"

int main() {
	while (true)
	{
		//输出界面
		cout << COLOR_CYAN << "= = = = =景区信息管理系统 = = = = =" << COLOR_RESET << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "\n请输入操作编号" << COLOR_YELLOW << "(0~5)：" << COLOR_RESET;

		int option;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << endl;
			CreateGraph();
			cout << endl << "按任意键继续......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 2:
			cout << endl;
			GetSpotInfo();
			cout << endl << "按任意键继续......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 3:
			cout << endl;
			TravelPath();
			cout << endl << "按任意键继续......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 4:
			cout << endl;
			FindPath();
			cout << endl << "按任意键继续......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 5:
			cout << endl;
			DesignPath();
			cout << endl << "按任意键继续......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 0:
			cout << "\n正在退出系统......" << endl;
			exit(0);
			break;
		default:
			cout << "\n输入有误，请重新输入！\n" << endl;
			break;
		}
	}

	return 0;
}