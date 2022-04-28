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

enum MAPPOS_SPECIAL {
	MSTAR_MAP1 = 5,
	MDE_ISRAND,
	MSTAR_MAP2 = 10,
	MSTAR_MAP3 = 21,
	MEND_MAP = 23
};

using namespace std;

// ** ���� �� **
// ������ ������ ĭ�� ���� 2000�� -
// �� ���ſ� ��� �� 1000��
// �������� ���� ������ 1000�� ����
//���� Ȳ��ī��
// * �¸� ����
//������ ������ �Ļ��ϰų� 100������ ���� ������ �¸�!

struct _tagPlayer {
	bool ifTwoMoney = false;
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

	// �ʿ��� ����
	// * ���ε�
	bool isInDeIsland = false;
	int a = 0;

	while (true) {
		char gamesize[WIDTH_SIZE][HEIGHT_SIZE] = {};
		system("cls");
		cout << "==== �������� ===="<<endl <<endl;
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
		cout << endl << tPlayer.strName << " �� ��ġ : " << tPlayer.iPos << "\t�� : " <<tPlayer.money << endl;
		cout << tAI.strName << " �� ��ġ : " << tAI.iPos << "\t�� : " << tAI.money << endl <<endl;
		
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
			if (isInDeIsland)
				cout << "�̵��� �� ���� �����ϴ�.";
			else {
				tPlayer.iPos += dice;
				if (tPlayer.iPos > MEND_MAP) { 
					tPlayer.iPos -= MEND_MAP + 1; 
					tPlayer.ifTwoMoney = true;
				}
				tPlayer.iPosition = mapPosition[tPlayer.iPos];
			}
			// Ư���� ��ġ�� �̺�Ʈ ����
			 
			// �������� ������
			if (tPlayer.ifTwoMoney) {
				cout << "���������� �������ϴ�! 1000���� �����մϴ�." <<endl;
				tPlayer.money += 1000;
				tPlayer.ifTwoMoney = false;
			}
			 
			// Ȳ��ī��
			string goldcard[] = { "���ۺκ����� ���ư���", "�������� �ȸ��� ���� �� �ϳ� ����", "5���� �ޱ�", "5���� ����", "���ε� ����" };
			if (tPlayer.iPos == MSTAR_MAP1 || tPlayer.iPos == MSTAR_MAP2 || tPlayer.iPos == MSTAR_MAP3) {
				cout << "Ȳ��ī�忡 ��÷�Ǽ̽��ϴ�. ī�带 ��������!" << endl;
			}

			//���ε�
			
			if (tPlayer.iPos == MDE_ISRAND) {
				if(!a) isInDeIsland = true;
					cout << "���ε��� �������ϴ�. "<<3-a<<"�ϰ� �ӹ����� �˴ϴ�." << endl;
					if (a) {
						cout << "�ֻ����� 6�� ���� �� Ż���� �� �ֽ��ϴ�." << endl;
						if (dice == 6) {
							cout << "���ε� Ż��! �����Ϻ��� ���ε��� ������ �˴ϴ�!" << endl;
							isInDeIsland = false;
							a = -1;
						}
					}
					if (a == 3) {
						cout << "3���� �������ϴ�. �����Ϻ��� ���ε��� ������ �˴ϴ�." << endl;
						isInDeIsland = false;
						a = -1;
					}
					a++;
			}

			cout << endl;

			// ��ǻ�� �̵�
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			tAI.iPos += dice;
			if (tAI.iPos > MEND_MAP) tAI.iPos -= MEND_MAP+1;

			tAI.iPosition = mapPosition[tAI.iPos];

			getchar();
			break;
		}
	}
	return 0;
}