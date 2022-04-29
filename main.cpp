#include<iostream>
#include<time.h>
#include<conio.h>

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

class _tagPlayer {
public:
	bool ifTwoMoney = false;	//������������ ���� �޾ƾ� �ϴ���
	bool isInDeIsland = false;	//���ε�
	int a = 0;
	char strName[NAME_SIZE];
	int iPosition = 0;
	int iPos = 0;
	int money = 10000;

	// ��������
	void start(void) {
		if (ifTwoMoney) {
			cout << "���������� �������ϴ�! 10000���� �����մϴ�." << endl;
			money += 10000;
			ifTwoMoney = false;
		}
	}
	// ���ε�
	void deIsland(int dice) {
		if (this->iPos == MDE_ISRAND) {
			if (!a) isInDeIsland = true;
			cout << "���ε��� �������ϴ�. " << 3 - a << "�ϰ� �ӹ����� �˴ϴ�." << endl;
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
	}
	// Ȳ��ī��
	void pickgoldcard(string* goldcard) {
		if (iPos == MSTAR_MAP1 || iPos == MSTAR_MAP2 || iPos == MSTAR_MAP3) {
			string selectcard[3];
			for (int i = 0; i < 3; i++) {
				int random = rand() % 4 + 1;
				selectcard[i] = goldcard[random];
			}
			cout << "Ȳ��ī�忡 ��÷�Ǽ̽��ϴ�. ���ϴ� ī�带 ��������!" << endl;
			cout << "1  2  3 : ";
			int iMenu;
			cin >> iMenu;
			while (iMenu < 1 || iMenu>3) {
				cout << "���ϴ� ī�带 ��������!" << endl;
				cin >> iMenu;
			}
			getchar();
			cout << "[ " << selectcard[iMenu] << " ] " << "�� ��÷�Ǽ̽��ϴ�!" << endl;
		}
	}

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
	string goldcard[] = { "���ۺκ����� ���ư���", "�������� �ȸ��� ���� �� �ϳ� ����", "5���� �ޱ�", "5���� ����", "���ε� ����" };
	

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
		switch (iMenu) {
		case MENU_ROLL:
			// �÷��̾� �̵�
			int dice = rand() % 6 + 1;
			cout << tPlayer.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			if(!tPlayer.isInDeIsland) {
				tPlayer.iPos += dice;
				if (tPlayer.iPos > MEND_MAP) {
					tPlayer.iPos -= MEND_MAP + 1;
					tPlayer.ifTwoMoney = true;
				}
				tPlayer.iPosition = mapPosition[tPlayer.iPos];
			}
			// Ư���� ��ġ�� �̺�Ʈ ����
			// 1. �������� ������
			tPlayer.start();

			// 2.Ȳ��ī��
			tPlayer.pickgoldcard(goldcard);

			//3. ���ε�
			tPlayer.deIsland(dice);

			cout << endl;

			// ��ǻ�� �̵�
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			if(!tAI.isInDeIsland) {
				tAI.iPos += dice;
				if (tAI.iPos > MEND_MAP) {
					tAI.iPos -= MEND_MAP + 1;
					tAI.ifTwoMoney = true;
				}
				tAI.iPosition = mapPosition[tAI.iPos];
			}
			// ��ǻ�� ��������
			tAI.start();
			
			// ��ǻ�� ���ε�
			if(tAI.iPos==MDE_ISRAND)
				tAI.deIsland(dice);

			// ��ǻ�� Ȳ��ī��
			tAI.pickgoldcard(goldcard);

			getchar();
			break;
		}
	}
	return 0;
}