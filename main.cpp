#include<iostream>
#include<time.h>

#define NAME_SIZE	32

enum GAME_MENU {
	MENU_NONE,
	MENU_ROLL,
	MENU_EXIT
};

enum SPECIAL_MAP {
	STAR_MAP1 = 5,
	DE_ISRAND,
	STAR_MAP2 = 21,
	STAR_MAP3 = 34,
	END_MAP = 48
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
	char strName[NAME_SIZE];
	int iPosition = 1;
	string card;
	int money = 10000;
};

int main() {

	srand((unsigned int)time(0));

	_tagPlayer tPlayer = {};
	_tagPlayer tAI = {};
	strcpy(tAI.strName, "Computer");

	cout << "�̸��� �Է��ϼ��� : ";
	cin >> tPlayer.strName;
	while (true) {
		system("cls");
		printf("==== �������� ====\n\n");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int a = i * 7 + j;
				if (a == tPlayer.iPosition - 1)
					cout << "��";
				else if (a == tAI.iPosition - 1)
					cout << "��";
				else if (a == DE_ISRAND)
					cout << "��";
				else if (a == STAR_MAP1 ||a == STAR_MAP2 || a == STAR_MAP3)
					cout << "��";
				else if (!i || i == 6 || !j || j == 6)
					cout << "��";
				else
					cout << "  ";
			}
			cout << endl;
		}

		cout << endl << tPlayer.strName << " �� ��ġ : " << tPlayer.iPosition <<endl;
		cout << tAI.strName << " �� ��ġ : " << tAI.iPosition << endl <<endl; 
		
		cout << "1. �ֻ��� ������" << endl;
		cout << "2. ���� ����" << endl;
		int iMenu;
		cin >> iMenu;
		getchar();
		if (iMenu == MENU_EXIT) break;
		switch(iMenu) {
		case MENU_ROLL :
			// �÷��̾� �̵�
			int iDice1 = rand() % 6 + 1;
			int iDice2 = rand() % 6 + 1;
			int sumDice = iDice1 + iDice2;
			cout << tPlayer.strName << "(��)�� �ֻ��� " << iDice1 << ", " << iDice2 << "�� �������ϴ�! " << sumDice << "ĭ�� �̵��մϴ�." << endl;
			tPlayer.iPosition += sumDice;

			// ��ǻ�� �̵�
			iDice1 = rand() % 6 + 1;
			iDice2 = rand() % 6 + 1;
			sumDice = iDice1 + iDice2;
			cout << tAI.strName << "(��)�� �ֻ��� " << iDice1 << ", " << iDice2 << "�� �������ϴ�! " << sumDice << "ĭ�� �̵��մϴ�." << endl;
			tAI.iPosition += sumDice;

			// ���� ���� �� �ٽ� ���ư�
			if (tPlayer.iPosition >= END_MAP) tPlayer.iPosition = 1;
			if (tAI.iPosition >= END_MAP) tAI.iPosition = 1;

			getchar();
			break;
		}

		
	}

	return 0;
}