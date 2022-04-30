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
	MSTAR_MAP1 = 5,		// Ȳ��ī�� 1
	MDE_ISRAND,			// ���ε�
	MBACK_MAP = 9,		// �ɸ��� 1~3ĭ �ڷ� ��
	MSTAR_MAP2,			// Ȳ��ī�� 2
	MGIVEMONEY_MAP = 14,// �ɸ��� 30000~100000�� �߰�, �Ǵ� ���̳ʽ�
	MGOFRONT_MAP = 18,	// �ɸ��� 1~3ĭ ������ ��
	MSTAR_MAP3 = 21,	// Ȳ��ī�� 3
	MEND_MAP = 23		// �� ��


};

using namespace std;

class _tagPlayer {
public:

	char strName[NAME_SIZE] = "COMPUTER";
	int iPosition = 0;
	int iPos = 0;
	int money = 50000;
	bool ifTwoMoney = false;	//������������ ���� �޾ƾ� �ϴ���
	bool isInDeIsland = false;	//���ε�
	int a = 0;	// ���ε��� ���� �� ��
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

		if (!a) isInDeIsland = true;
		cout << "���ε��� �������ϴ�. " << 3 - a << "�ϰ� �ӹ����� �˴ϴ�." << endl;
		if (a) {
			if (dice == 6) {
				cout << "6�� ���Խ��ϴ�. ���ε� Ż��! �����Ϻ��� ���ε��� ������ �˴ϴ�!" << endl;
				a = -1;
				isInDeIsland = false;
			}
			else cout << "�ֻ����� 6�� ���� �� Ż���� �� �ֽ��ϴ�." << endl;
		}
		if (a == 3) {
			cout << "3���� �������ϴ�. �����Ϻ��� ���ε��� ������ �˴ϴ�." << endl;
			a = -1;
			isInDeIsland = false;
		}
		a++;

	}
	// Ȳ��ī��
	void pickgoldcard(string* goldcard, int iMenu) {
		string selectcard[3];
		for (int i = 0; i < 3; i++) {
			int random = rand() % 4 + 1;
			selectcard[i] = goldcard[random];
		}
		cout << "[ " << selectcard[iMenu] << " ] " << "�� ��÷�Ǽ̽��ϴ�!" << endl;
		for (int i = 0; i < 5; i++) {
			if (selectcard[iMenu] == goldcard[i])
				switch (i) {
					// ������������ ���ư���
				case 0:
					cout << "������������ �̵��մϴ�!" << endl;
					iPos = 0;
					iPosition = 0;
					break;
					// ������ �����̵�
				case 1:
					cout << "�������� �ٸ� ���� �̵��˴ϴ�!" << endl;
					iPos = rand() % MEND_MAP;
					break;
					// 5���� �ޱ�
				case 2:
					cout << "50000���� ȹ���մϴ�." << endl;
					money += 50000;
					break;
					// 5���� ����
				case 3:
					cout << "50000���� �ҽ��ϴ�." << endl;
					money -= 50000;
					break;
					// ���ε��� �̵�
				case 4:
					cout << "���ε��� �̵��մϴ�." << endl;
					iPos = MDE_ISRAND;
					iPosition = DE_ISRAND;
					break;
				}
		}
	}

	void coin() {

		int random = rand() % 2;
		int monrandom = (rand() % 70000 + 30000) / 100;
		monrandom *= 100;

		if (random) {
			cout << "���п��� �ú� �ɷȽ��ϴ�. �� "<<monrandom<<"���� ���� �մϴ�..." << endl;
			money -= monrandom;
		}
		else {
			cout << "����ŷ�� �߽��ϴ�. ��û�� �α�� �� "<<monrandom<<"���� �޽��ϴ�!" << endl;
			money += monrandom;
		}
	}

	void back(int* mapPosition) {
		if (iPos == MBACK_MAP) {
			int random = rand() % 3 + 1;
			cout << "Ʈ���� ��ҽ��ϴ�... " << random << "ĭ �ڷ� �̵��մϴ�!" << endl;
			iPos -= random;
			iPosition = *(mapPosition - random);
		}
	}

	void goFront(int* mapPosition) {
		if (iPos == MGOFRONT_MAP) {
			int random = rand() % 3 + 1;
			cout << "��ġ ����ŷ ����! " << random << "ĭ ������ �̵��մϴ�!" << endl;
			iPos += random;
			iPosition = *(mapPosition + random);
		}
	}
};

int main() {
	srand((unsigned int)time(0));

	_tagPlayer tPlayer = {};
	_tagPlayer tAI = {};
	strcpy(tAI.strName, "Computer");

	// ĭ ��ġ ����ֱ�
	int mapPosition[WIDTH_SIZE * HEIGHT_SIZE] = {};
	int po = 0;
	for (int i = 0; i <= WIDTH_SIZE - 1; i++)
		mapPosition[po++] = i;
	for (int i = 1; i <= HEIGHT_SIZE - 1; i++)
		mapPosition[po++] = i * HEIGHT_SIZE + (HEIGHT_SIZE - 1);
	for (int i = (WIDTH_SIZE - 2); i >= 0; i--)
		mapPosition[po++] = (WIDTH_SIZE - 1) * WIDTH_SIZE + i;
	for (int i = HEIGHT_SIZE - 2; i > 0; i--)
		mapPosition[po++] = i * HEIGHT_SIZE;

	cout << "�̸��� �Է��ϼ��� : ";
	cin >> tPlayer.strName;

	// �ʿ��� ����
	string goldcard[] = { "���ۺκ����� ���ư���", "������ �����̵�", "5���� �ޱ�", "5���� ����", "���ε� ����" };


	while (true) {
		char gamesize[WIDTH_SIZE][HEIGHT_SIZE] = {};
		system("cls");

		// ��ǻ�� �¸� ����
		if (tPlayer.money < 0 || tAI.money >= 500000) {
			if (tPlayer.money < 0) cout << tPlayer.strName << "(��)�� �Ļ��ߴ�.... ������ �����մϴ�!" << endl;
			else cout << tAI.strName << "(��)�� 50������ ��Ҵ�! ���ڰ� �Ǿ����ϴ�!" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "THE WINNER IS...." << tAI.strName << "!!!" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

			system("pause");
			break;
		}

		// �÷��̾� �¸� ����
		else if (tAI.money < 0 || tPlayer.money >= 500000) {
			if (tPlayer.money < 0) cout << tAI.strName << "(��)�� �Ļ��ߴ�.... ������ �����մϴ�!" << endl;
			else cout << tPlayer.strName << "(��)�� 50������ ��Ҵ�! ���ڰ� �Ǿ����ϴ�!" << endl <<endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "THE WINNER IS...." << tPlayer.strName << "!!!" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

			system("pause");
			break;
		}

		cout << "~~~~ �������� ~~~~" << endl << endl;
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
		cout << endl << tPlayer.strName << " �� ��ġ : " << tPlayer.iPos << "\t�� : " << tPlayer.money << endl;
		cout << tAI.strName << " �� ��ġ : " << tAI.iPos << "\t�� : " << tAI.money << endl << endl;

		cout << "1. �ֻ��� ������" << endl;
		cout << "2. ���� ����" << endl;
		int iMenu;
		cin >> iMenu;
		getchar();
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (iMenu == MENU_EXIT) break;
		switch (iMenu) {
		case MENU_ROLL:
			// �÷��̾� �̵�
			cout << "==== PLAYER ====" << endl;
			int dice = rand() % 6 + 1;
			cout << tPlayer.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			if (!tPlayer.isInDeIsland) {
				tPlayer.iPos += dice;
				if (tPlayer.iPos > MEND_MAP) {
					tPlayer.iPos -= MEND_MAP + 1;
					tPlayer.ifTwoMoney = true;
				}
				tPlayer.iPosition = mapPosition[tPlayer.iPos];
			}
			// Ư���� ��ġ�� �̺�Ʈ ����
			// 1. �ɸ��� 1~3ĭ �ڷ� �̵�
			tPlayer.back(&mapPosition[tPlayer.iPos]);

			// 2. �ɸ��� 1~3ĭ ������ �̵�
			tPlayer.goFront(&mapPosition[tPlayer.iPos]);

			// 3. �������� ������
			tPlayer.start();

			// 4. Ȳ��ī��
			if (tPlayer.iPos == MSTAR_MAP1 || tPlayer.iPos == MSTAR_MAP2 || tPlayer.iPos == MSTAR_MAP3) {
				cout << "Ȳ��ī�忡 ��÷�Ǽ̽��ϴ�. ���ϴ� ī�带 ��������!" << endl;
				cout << "1  2  3 : ";
				cin >> iMenu;
				getchar();
				while (iMenu < 1 || iMenu>3) {
					cout << "ī�带 ��������!" << endl;
					cin >> iMenu;
					getchar();
				}
				tPlayer.pickgoldcard(goldcard, iMenu - 1);
			}

			// 5. ���ε�
			if (tPlayer.iPos == MDE_ISRAND)	tPlayer.deIsland(dice);

			// 6. + �Ǵ� - 30000��
			if (tPlayer.iPos == MGIVEMONEY_MAP)	tPlayer.coin();

			cout << endl;

			// ��ǻ�� �̵�
			cout << "==== COMPUTER ====" << endl;
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(��)�� �ֻ��� " << dice << "�� �������ϴ�! " << dice << "ĭ�� �̵��մϴ�." << endl;
			if (!tAI.isInDeIsland) {
				tAI.iPos += dice;
				if (tAI.iPos > MEND_MAP) {
					tAI.iPos -= MEND_MAP + 1;
					tAI.ifTwoMoney = true;
				}
				tAI.iPosition = mapPosition[tAI.iPos];
			}

			// ��ǻ�� �ɸ��� 1~3ĭ �ڷ� �̵�
			tAI.back(&mapPosition[tAI.iPos]);

			// ��ǻ�� �ɸ��� 1~3ĭ ������ �̵�
			tAI.goFront(&mapPosition[tAI.iPos]);

			// ��ǻ�� ��������
			tAI.start();

			// ��ǻ�� Ȳ��ī��
			if (tAI.iPos == MSTAR_MAP1 || tAI.iPos == MSTAR_MAP2 || tAI.iPos == MSTAR_MAP3) {
				cout << "Ȳ��ī�忡 ��÷�Ǽ̽��ϴ�." << endl;
				iMenu = rand() % 3;
				tAI.pickgoldcard(goldcard, iMenu);
			}

			// ��ǻ�� ���ε�
			if (tAI.iPos == MDE_ISRAND)	tAI.deIsland(dice);

			// ��ǻ�� + �Ǵ� - 30000��
			if (tAI.iPos == MGIVEMONEY_MAP)	tAI.coin();

			getchar();
			break;
		}
	}
	return 0;
}