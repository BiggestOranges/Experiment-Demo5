#include "Graph.h"
#include "Tourism.h"

int main() {
	while (true)
	{
		//�������
		cout << COLOR_CYAN << "= = = = =������Ϣ����ϵͳ = = = = =" << COLOR_RESET << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "\n������������" << COLOR_YELLOW << "(0~5)��" << COLOR_RESET;

		int option;
		cin >> option;
		switch (option)
		{
		case 1:
			cout << endl;
			CreateGraph();
			cout << endl << "�����������......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 2:
			cout << endl;
			GetSpotInfo();
			cout << endl << "�����������......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 3:
			cout << endl;
			TravelPath();
			cout << endl << "�����������......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 4:
			cout << endl;
			FindPath();
			cout << endl << "�����������......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 5:
			cout << endl;
			DesignPath();
			cout << endl << "�����������......";
			getchar();
			getchar();
			cout << endl << endl;
			break;
		case 0:
			cout << "\n�����˳�ϵͳ......" << endl;
			exit(0);
			break;
		default:
			cout << "\n�����������������룡\n" << endl;
			break;
		}
	}

	return 0;
}