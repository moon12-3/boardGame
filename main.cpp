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
	MSTAR_MAP1 = 5,		// 황금카드 1
	MDE_ISRAND,			// 무인도
	MBACK_MAP = 9,		// 걸리면 1~3칸 뒤로 감
	MSTAR_MAP2,			// 황금카드 2
	MGIVEMONEY_MAP = 14,// 걸리면 30000~100000원 추가, 또는 마이너스
	MGOFRONT_MAP = 18,	// 걸리면 1~3칸 앞으로 감
	MSTAR_MAP3 = 21,	// 황금카드 3
	MEND_MAP = 23		// 맵 끝


};

using namespace std;

class _tagPlayer {
public:

	char strName[NAME_SIZE] = "COMPUTER";
	int iPosition = 0;
	int iPos = 0;
	int money = 50000;
	bool ifTwoMoney = false;	//시작지점에서 돈을 받아야 하는지
	bool isInDeIsland = false;	//무인도
	int a = 0;	// 무인도에 갇힌 턴 수
	// 시작지점
	void start(void) {
		if (ifTwoMoney) {

			cout << "시작지점을 지났습니다! 10000원을 지급합니다." << endl;
			money += 10000;
			ifTwoMoney = false;
		}
	}
	// 무인도
	void deIsland(int dice) {

		if (!a) isInDeIsland = true;
		cout << "무인도에 갇혔습니다. " << 3 - a << "턴간 머무르게 됩니다." << endl;
		if (a) {
			if (dice == 6) {
				cout << "6이 나왔습니다. 무인도 탈출! 다음턴부터 무인도를 나가게 됩니다!" << endl;
				a = -1;
				isInDeIsland = false;
			}
			else cout << "주사위가 6이 나올 시 탈출할 수 있습니다." << endl;
		}
		if (a == 3) {
			cout << "3턴이 지났습니다. 다음턴부터 무인도를 나가게 됩니다." << endl;
			a = -1;
			isInDeIsland = false;
		}
		a++;

	}
	// 황금카드
	void pickgoldcard(string* goldcard, int iMenu) {
		string selectcard[3];
		for (int i = 0; i < 3; i++) {
			int random = rand() % 4 + 1;
			selectcard[i] = goldcard[random];
		}
		cout << "[ " << selectcard[iMenu] << " ] " << "에 당첨되셨습니다!" << endl;
		for (int i = 0; i < 5; i++) {
			if (selectcard[iMenu] == goldcard[i])
				switch (i) {
					// 시작지점으로 돌아가기
				case 0:
					cout << "시작지점으로 이동합니다!" << endl;
					iPos = 0;
					iPosition = 0;
					break;
					// 무작위 순간이동
				case 1:
					cout << "랜덤으로 다른 땅에 이동됩니다!" << endl;
					iPos = rand() % MEND_MAP;
					break;
					// 5만원 받기
				case 2:
					cout << "50000원을 획득합니다." << endl;
					money += 50000;
					break;
					// 5만원 내기
				case 3:
					cout << "50000원을 잃습니다." << endl;
					money -= 50000;
					break;
					// 무인도로 이동
				case 4:
					cout << "무인도로 이동합니다." << endl;
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
			cout << "깡패에게 시비가 걸렸습니다. 돈 "<<monrandom<<"원을 내야 합니다..." << endl;
			money -= monrandom;
		}
		else {
			cout << "버스킹을 했습니다. 엄청난 인기로 돈 "<<monrandom<<"원을 받습니다!" << endl;
			money += monrandom;
		}
	}

	void back(int* mapPosition) {
		if (iPos == MBACK_MAP) {
			int random = rand() % 3 + 1;
			cout << "트랩을 밟았습니다... " << random << "칸 뒤로 이동합니다!" << endl;
			iPos -= random;
			iPosition = *(mapPosition - random);
		}
	}

	void goFront(int* mapPosition) {
		if (iPos == MGOFRONT_MAP) {
			int random = rand() % 3 + 1;
			cout << "히치 하이킹 성공! " << random << "칸 앞으로 이동합니다!" << endl;
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

	// 칸 위치 집어넣기
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

	cout << "이름을 입력하세요 : ";
	cin >> tPlayer.strName;

	// 필요한 변수
	string goldcard[] = { "시작부분으로 돌아가기", "무작위 순간이동", "5만원 받기", "5만원 내기", "무인도 가기" };


	while (true) {
		char gamesize[WIDTH_SIZE][HEIGHT_SIZE] = {};
		system("cls");

		// 컴퓨터 승리 조건
		if (tPlayer.money < 0 || tAI.money >= 500000) {
			if (tPlayer.money < 0) cout << tPlayer.strName << "(은)는 파산했다.... 거지로 전락합니다!" << endl;
			else cout << tAI.strName << "(은)는 50만원을 모았다! 부자가 되었습니다!" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "THE WINNER IS...." << tAI.strName << "!!!" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

			system("pause");
			break;
		}

		// 플레이어 승리 조건
		else if (tAI.money < 0 || tPlayer.money >= 500000) {
			if (tPlayer.money < 0) cout << tAI.strName << "(은)는 파산했다.... 거지로 전락합니다!" << endl;
			else cout << tPlayer.strName << "(은)는 50만원을 모았다! 부자가 되었습니다!" << endl <<endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "THE WINNER IS...." << tPlayer.strName << "!!!" << endl;
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;

			system("pause");
			break;
		}

		cout << "~~~~ 부유마불 ~~~~" << endl << endl;
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
		cout << endl << tPlayer.strName << " 말 위치 : " << tPlayer.iPos << "\t돈 : " << tPlayer.money << endl;
		cout << tAI.strName << " 말 위치 : " << tAI.iPos << "\t돈 : " << tAI.money << endl << endl;

		cout << "1. 주사위 굴리기" << endl;
		cout << "2. 게임 종료" << endl;
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
			// 플레이어 이동
			cout << "==== PLAYER ====" << endl;
			int dice = rand() % 6 + 1;
			cout << tPlayer.strName << "(이)가 주사위 " << dice << "을 던졌습니다! " << dice << "칸을 이동합니다." << endl;
			if (!tPlayer.isInDeIsland) {
				tPlayer.iPos += dice;
				if (tPlayer.iPos > MEND_MAP) {
					tPlayer.iPos -= MEND_MAP + 1;
					tPlayer.ifTwoMoney = true;
				}
				tPlayer.iPosition = mapPosition[tPlayer.iPos];
			}
			// 특별한 위치의 이벤트 설정
			// 1. 걸리면 1~3칸 뒤로 이동
			tPlayer.back(&mapPosition[tPlayer.iPos]);

			// 2. 걸리면 1~3칸 앞으로 이동
			tPlayer.goFront(&mapPosition[tPlayer.iPos]);

			// 3. 시작지점 지나면
			tPlayer.start();

			// 4. 황금카드
			if (tPlayer.iPos == MSTAR_MAP1 || tPlayer.iPos == MSTAR_MAP2 || tPlayer.iPos == MSTAR_MAP3) {
				cout << "황금카드에 당첨되셨습니다. 원하는 카드를 뽑으세요!" << endl;
				cout << "1  2  3 : ";
				cin >> iMenu;
				getchar();
				while (iMenu < 1 || iMenu>3) {
					cout << "카드를 뽑으세요!" << endl;
					cin >> iMenu;
					getchar();
				}
				tPlayer.pickgoldcard(goldcard, iMenu - 1);
			}

			// 5. 무인도
			if (tPlayer.iPos == MDE_ISRAND)	tPlayer.deIsland(dice);

			// 6. + 또는 - 30000원
			if (tPlayer.iPos == MGIVEMONEY_MAP)	tPlayer.coin();

			cout << endl;

			// 컴퓨터 이동
			cout << "==== COMPUTER ====" << endl;
			dice = rand() % 6 + 1;
			cout << tAI.strName << "(이)가 주사위 " << dice << "을 던졌습니다! " << dice << "칸을 이동합니다." << endl;
			if (!tAI.isInDeIsland) {
				tAI.iPos += dice;
				if (tAI.iPos > MEND_MAP) {
					tAI.iPos -= MEND_MAP + 1;
					tAI.ifTwoMoney = true;
				}
				tAI.iPosition = mapPosition[tAI.iPos];
			}

			// 컴퓨터 걸리면 1~3칸 뒤로 이동
			tAI.back(&mapPosition[tAI.iPos]);

			// 컴퓨터 걸리면 1~3칸 앞으로 이동
			tAI.goFront(&mapPosition[tAI.iPos]);

			// 컴퓨터 시작지점
			tAI.start();

			// 컴퓨터 황금카드
			if (tAI.iPos == MSTAR_MAP1 || tAI.iPos == MSTAR_MAP2 || tAI.iPos == MSTAR_MAP3) {
				cout << "황금카드에 당첨되셨습니다." << endl;
				iMenu = rand() % 3;
				tAI.pickgoldcard(goldcard, iMenu);
			}

			// 컴퓨터 무인도
			if (tAI.iPos == MDE_ISRAND)	tAI.deIsland(dice);

			// 컴퓨터 + 또는 - 30000원
			if (tAI.iPos == MGIVEMONEY_MAP)	tAI.coin();

			getchar();
			break;
		}
	}
	return 0;
}