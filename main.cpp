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

//게임 룰
//start칸에 들어가면 1000원 +
//상대방이 구매한 칸에 들어가면 1000원 -
//
//☆은 황금카드
//황금 카드 능력
//1. 무작위로 남의 하나 땅 빼앗기
//2. 출발 지점으로 이동
//3. 무인도로 이동
//
//승리 조건
//게임은 상대방이 파산하거나 100만원을 먼저 모으면 승리

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

	cout << "이름을 입력하세요 : ";
	cin >> tPlayer.strName;
	while (true) {
		system("cls");
		printf("==== 부유마불 ====\n\n");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int a = i * 7 + j;
				if (a == tPlayer.iPosition - 1)
					cout << "§";
				else if (a == tAI.iPosition - 1)
					cout << "＆";
				else if (a == DE_ISRAND)
					cout << "▤";
				else if (a == STAR_MAP1 ||a == STAR_MAP2 || a == STAR_MAP3)
					cout << "☆";
				else if (!i || i == 6 || !j || j == 6)
					cout << "□";
				else
					cout << "  ";
			}
			cout << endl;
		}

		cout << endl << tPlayer.strName << " 말 위치 : " << tPlayer.iPosition <<endl;
		cout << tAI.strName << " 말 위치 : " << tAI.iPosition << endl <<endl; 
		
		cout << "1. 주사위 굴리기" << endl;
		cout << "2. 게임 종료" << endl;
		int iMenu;
		cin >> iMenu;
		getchar();
		if (iMenu == MENU_EXIT) break;
		switch(iMenu) {
		case MENU_ROLL :
			// 플레이어 이동
			int iDice1 = rand() % 6 + 1;
			int iDice2 = rand() % 6 + 1;
			int sumDice = iDice1 + iDice2;
			cout << tPlayer.strName << "(이)가 주사위 " << iDice1 << ", " << iDice2 << "을 던졌습니다! " << sumDice << "칸을 이동합니다." << endl;
			tPlayer.iPosition += sumDice;

			// 컴퓨터 이동
			iDice1 = rand() % 6 + 1;
			iDice2 = rand() % 6 + 1;
			sumDice = iDice1 + iDice2;
			cout << tAI.strName << "(이)가 주사위 " << iDice1 << ", " << iDice2 << "을 던졌습니다! " << sumDice << "칸을 이동합니다." << endl;
			tAI.iPosition += sumDice;

			// 끝에 도달 시 다시 돌아감
			if (tPlayer.iPosition >= END_MAP) tPlayer.iPosition = 1;
			if (tAI.iPosition >= END_MAP) tAI.iPosition = 1;

			getchar();
			break;
		}

		
	}

	return 0;
}