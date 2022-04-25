#include<iostream>
#include<time.h>

#define NAME_SIZE	32

enum GAME_MENU {
	MENU_NONE,
	MENU_ROLL,
	MENU_EXIT
};

enum GAME_SIZE {
	WIDTH_SIZE = 7, 
	HEIGHT_SIZE = 7
};

enum SPECIAL_MAP {
	STAR_MAP1 = 5,
	DE_ISRAND,
	STAR_MAP2 = 21,
	STAR_MAP3 = 34,
	END_MAP = 7
};

using namespace std;

//���� ��
//startĭ�� ���� 1000�� +
//������ ������ ĭ�� ���� 1000�� -
//
//���� Ȳ��ī��
//Ȳ�� ī�� �ɷ�
//1. �������� ���� �ϳ� �� ���ѱ�
//2. ��� �������� �̵�
//3. ���ε��� �̵�
//
//�¸� ����
//������ ������ �Ļ��ϰų� 100������ ���� ������ �¸�

struct _tagPlayer {
	bool ifTwo = false; // �� �� �̻� ���������� ���Ҵ���
	char strName[NAME_SIZE];
	int iPosition = 0;
	int iPos = 0;
	string card;
	int money = 10000;
};

int main() {
	srand((unsigned int)time(0));

	_tagPlayer tPlayer = {};
	_tagPlayer tAI = {};
	strcpy(tAI.strName, "Computer");

	
	// ĭ ��ġ ����ֱ�
	int mapPosition[WIDTH_SIZE*HEIGHT_SIZE] = {};
	int po = 0;
	for (int i = 0; i <= WIDTH_SIZE - 1; i++)
		mapPosition[po++] = i;
	for (int i = 1; i <= HEIGHT_SIZE - 1; i++)
		mapPosition[po++] = i * HEIGHT_SIZE + (HEIGHT_SIZE-1);
	for (int i = (WIDTH_SIZE - 2); i >= 0; i--)
		mapPosition[po++] = (WIDTH_SIZE-1) * WIDTH_SIZE + i;
	for (int i = HEIGHT_SIZE - 2; i > 0; i--)
		mapPosition[po++] = i * HEIGHT_SIZE;

	cout << "�̸��� �Է��ϼ��� : ";
	cin >> tPlayer.strName;
	while (true) {
		char gamesize[WIDTH_SIZE][HEIGHT_SIZE] = {};
		system("cls");
		printf("==== �������� ====\n\n");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int a = i * 7 + j;
				if (a == tPlayer.iPosition)
					cout << "��";
				else if (a == tAI.iPosition)
					cout << "��";
				else if (a == DE_ISRAND)
					cout << "��";
				else if (a == STAR_MAP1 || a == STAR_MAP2 || a == STAR_MAP3)
					cout << "��";
				else if (!i || i == 6 || !j || j == 6)
					cout << "��";
				else
					cout << "  ";
			}
			cout << endl;
		}

		

		// �� ��ġ ���
		cout << endl << tPlayer.strName << " �� ��ġ : " << mapPosition[tPlayer.iPos] <<endl;
		cout << tAI.strName << " �� ��ġ : " << mapPosition[tAI.iPos] << endl <<endl;
		
		cout << "1. �ֻ��� ������" << endl;
		cout << "2. ���� ����" << endl;
		int iMenu;
		cin >> iMenu;
		getchar();
		if (iMenu == MENU_EXIT) break;
		switch(iMenu) {
		case MENU_ROLL :
			// �÷��̾� �̵�
			int dice = rand() % 6 + 1;
			cout << tPlayer.strName << "(��)�� �ֻ��� " << dice<< "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			tPlayer.iPos += dice;	// 9
			
			tPlayer.iPosition = mapPosition[tPlayer.iPos];

			// ��ǻ�� �̵�
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			tAI.iPos += dice;
			tAI.iPosition = mapPosition[tAI.iPos];

			// ���� ���� �����ϸ� �ٽ� ó������ ���ư���.
				/*if (END_MAP) tPlayer.iPosition = 0, tPlayer.iPos = 0;
				if (END_MAP) tAI.iPosition = 0, tAI.iPos = 0;*/
			getchar();
			break;
		}

		
	}

	return 0;
}