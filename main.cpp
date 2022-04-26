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
	bool ifTwo = false; // 한 번 이상 시작지점을 돌았는지
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

	
	// 칸 위치 집어넣기
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

	cout << "이름을 입력하세요 : ";
	cin >> tPlayer.strName;
	while (true) {
		char gamesize[WIDTH_SIZE][HEIGHT_SIZE] = {};
		system("cls");
		printf("==== 부유마불 ====\n\n");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 7; j++) {
				int a = i * 7 + j;
				if (a == tPlayer.iPosition)
					cout << "§";
				else if (a == tAI.iPosition)
					cout << "＆";
				else if (a == DE_ISRAND)
					cout << "▤";
				else if (a == STAR_MAP1 || a == STAR_MAP2 || a == STAR_MAP3)
					cout << "☆";
				else if (!i || i == 6 || !j || j == 6)
					cout << "□";
				else
					cout << "  ";
			}
			cout << endl;
		}

		

		// 말 위치 출력
		cout << endl << tPlayer.strName << " 말 위치 : " << tPlayer.iPos <<endl;
		cout << tAI.strName << " 말 위치 : " << tAI.iPos << endl <<endl;
		
		cout << "1. 주사위 굴리기" << endl;
		cout << "2. 게임 종료" << endl;
		int iMenu;
		cin >> iMenu;
		getchar();
		if (iMenu == MENU_EXIT) break;
		switch(iMenu) {
		case MENU_ROLL :
			bool isInDeIsland = false;
			// 플레이어 이동
			int dice = rand() % 6 + 1;
			cout << tPlayer.strName << "(이)가 주사위 " << dice<< "을 던졌습니다! " << dice << "칸을 이동합니다." << endl;
			if (isInDeIsland) cout << "무인도에 있어 이동을 할 수가 없습니다.";
			else {
				tPlayer.iPos += dice;
				if (tPlayer.iPos > MEND_MAP) tPlayer.iPos -= MEND_MAP + 1;

				tPlayer.iPosition = mapPosition[tPlayer.iPos];
			}
			// 특별한 위치의 이벤트 설정
			// 황금카드
			string goldcard[] = { "시작부분으로 돌아가기", "무작위로 팔리지 않은 땅 하나 갖기", "5만원 받기", "5만원 내기", "무인도 가기" };
			if (tPlayer.iPos == MSTAR_MAP1 || tPlayer.iPos == MSTAR_MAP2 || tPlayer.iPos == MSTAR_MAP3) {
				cout << "황금카드에 당첨되셨습니다. 카드를 뽑으세요!" << endl;
			}

			//무인도
			/*if (tPlayer.iPos == MDE_ISRAND) {
				int a = 0;
					cout << "무인도에 갇혔습니다. %d턴간 머무르게 됩니다." << endl;
					if (a)
						if (dice == 6)

				}
			}*/

			// 컴퓨터 이동
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(이)가 주사위 " << dice << "을 던졌습니다! " << dice << "칸을 이동합니다." << endl;
			tAI.iPos += dice;
			if (tAI.iPos > MEND_MAP) tAI.iPos -= MEND_MAP+1;

			tAI.iPosition = mapPosition[tAI.iPos];

			

			


			getchar();
			break;
		}

		
	}

	return 0;
}