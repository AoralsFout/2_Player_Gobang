#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 19
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

/*
* ����
*   0 1 ...
* 0
* 1
* ...
*/
int x;								// ѡ��λ��x����
int y;								// ѡ��λ��y����
int board[BOARD_SIZE][BOARD_SIZE];	// ������Ϣ
int flag;							// ���� ż����ʾ��������  ������ʾ��������

/*
* ��ʼ�����̺;���
*/
void init();

/*
* չʾ��Ϸ�淨
*/
void showHowToPlay();

/*
* ��ʾ�˵�
*/
void menuView();

/*
* ����������������ʾ�˵��е���
* ��ӡѡ�ͬ�Ĳ˵�
*/
void printMenuStart();
void printMenuSetting();
void printMenuExit();

/*
* ����������Ϣ�͵�ǰѡ��λ����Ⱦ����
*/
void printBoard();

/*
* ��ʼ��Ϸ
*/
void startGame();

/*
* �ж�ʤ��
*/
int isWin();

int main()
{
	init();
	showHowToPlay();
	menuView();
	return 0;
}

void init() {
	// ���þ���
	flag = 1;
	// ��������
	int* p = &board[0][0];
	for (int i = 0; i < (BOARD_SIZE + 1) * (BOARD_SIZE + 1); i++)
	{
		*p = 0;
		p++;
	}
	// ����ѡ��
	x = BOARD_SIZE / 2;
	y = BOARD_SIZE / 2;
}

void menuView() {
	/*
	* ��¼���ѡ��
	* 0	�˳���Ϸ
	* 1 ��Ϸ����
	* 2	��ʼ��Ϸ
	*/
	int selection = 2;
	while (1) {
		// ��ȾĿ¼ѡ��
		switch (selection) {
		case 0:
			printMenuExit();
			break;
		case 1:
			printMenuSetting();
			break;
		case 2:
			printMenuStart();
			break;
		}
		// ���������̣�ֱ����ָ���ļ�������
		int key;
		key = _getch();
		// �����û�����ѡ�����
		switch (key) {
			// �ϼ�
		case 72:
			if (selection == 2)
			{
				selection = 2;
			}
			else
			{
				selection++;
			}
			system("cls");	// ��տ���̨
			break;
			// �¼�
		case 80:
			if (selection == 0)
			{
				selection = 0;
			}
			else
			{
				selection--;
			}
			system("cls");	// ��տ���̨
			break;
			// ENTER
		case 13:
			switch (selection) {
			case 0:
				exit(0);
			case 1:
				break;
			case 2:
				startGame();
				break;
			}
			system("cls");	// ��տ���̨
			break;
		}
	}
}

void showHowToPlay() {
	printf("C����˫�������� by AoralsFout\n");
	printf("v1.0.0\n");
	printf("ʹ�� ��������  �����Ʋ˵�ѡ��\n");
	printf("ʹ�� ��������  ����������\n");
	printf("ʹ�� Enter ��ȷ��\n");
	printf("\n");
	printf("�밴���������...");
	int c = _getch();	// ���������̣�ֱ���а���������
	system("cls");		// ��տ���̨
}

void startGame() {
	while (1) {
		int check;
		system("cls");
		// ��ӡ������Ϣ
		printf("�� %d ��|��", flag);
		switch (flag % 2) {
		case 0:
			printf("  ���ӡ�   ����|");
			break;
		case 1:
			printf("  ���ӡ�   ����|");
			break;
		}
		printf("\n");
		check = isWin();
		printBoard();
		int key = _getch();
		if (check == 1)
		{
			init();
			break;
		}
		// �û���������
		//�� 72 ��80 �� 75 �� 77
		switch (key) {
		case 72:
			y == 0 ? y == 0 : y--;
			break;
		case 75:
			x == 0 ? x == 0 : x--;
			break;
		case 77:
			x == BOARD_SIZE - 1 ? x == BOARD_SIZE - 1 : x++;
			break;
		case 80:
			y == BOARD_SIZE - 1 ? y == BOARD_SIZE - 1 : y++;
			break;
		case 13: {
			// ֻ�пտ�������
			if (board[y][x] == 0)
			{
				int who = flag % 2;
				switch (who) {
				case 0:
					board[y][x] = 1;
					break;
				case 1:
					board[y][x] = 2;
					break;
				}
				flag++;
			}
		}
		}
	}
}

int isWin() {
	int blackWin = 0;
	int whiteWin = 0;
	int isFull = 1; // ������������

	// ��������Ƿ�����
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == 0) {
				isFull = 0;
				break;
			}
		}
		if (!isFull) break;
	}

	/*
	* ����ÿһ�����ӣ���¼��ǰ��Ϣ
	* �ٴζ�ˮƽ����ֱ�����¶Խ��ߣ����¶Խ��߷��������Σ�����кͼ�¼��Ϣ��ͬ�ģ��������������
	* �����������Ƿ�Ϊ5
	*/

	// �������̼���������������
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			// ��¼��ǰ����״̬
			int current = board[i][j];
			// �����հ�
			if (current == 0) continue;

			// ���ˮƽ����
			// ��Խ��
			if (j <= BOARD_SIZE - 5) {
				int count = 1;
				for (int k = 1; k < 5; k++) {
					if (board[i][j + k] == current) {
						count++;
					}
					else {
						break;
					}
				}
				if (count == 5) {
					if (current == 1) blackWin = 1;
					else if (current == 2) whiteWin = 1;
				}
			}

			// ��鴹ֱ����
			if (i <= BOARD_SIZE - 5) {
				int count = 1;
				for (int k = 1; k < 5; k++) {
					if (board[i + k][j] == current) {
						count++;
					}
					else {
						break;
					}
				}
				if (count == 5) {
					if (current == 1) blackWin = 1;
					else if (current == 2) whiteWin = 1;
				}
			}

			// ������¶Խ���
			if (i <= BOARD_SIZE - 5 && j <= BOARD_SIZE - 5) {
				int count = 1;
				for (int k = 1; k < 5; k++) {
					if (board[i + k][j + k] == current) {
						count++;
					}
					else {
						break;
					}
				}
				if (count == 5) {
					if (current == 1) blackWin = 1;
					else if (current == 2) whiteWin = 1;
				}
			}

			// ������¶Խ���
			if (i <= BOARD_SIZE - 5 && j >= 4) {
				int count = 1;
				for (int k = 1; k < 5; k++) {
					if (board[i + k][j - k] == current) {
						count++;
					}
					else {
						break;
					}
				}
				if (count == 5) {
					if (current == 1) blackWin = 1;
					else if (current == 2) whiteWin = 1;
				}
			}
		}
	}

	// ������
	if (blackWin && whiteWin) {
		printf("�������밴���������...\n");
	}
	else if (blackWin) {
		printf("����ʤ�����밴���������...\n");
	}
	else if (whiteWin) {
		printf("����ʤ�����밴���������...\n");
	}
	else if (isFull) {
		printf("ƽ�֣��������������˻�ʤ���밴���������...\n");
	}
	else {
		printf("\n");
	}

	if (blackWin || whiteWin || isFull)
	{
		return 1;
	}
	else {
		return 0;
	}
}

void printBoard() {
	for (int i = 0; i <= BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			/*
			* ÿ����һ�����ӣ��ͼ�¼�ܱ߼�����9�����ӵ�״̬��ȷ�������Ⱦ����
			* ����ܱ����
			* ֵ
			* 0	������
			* 1 �����ڲ�
			* 2 ѡ��
			* ����
			* 0	����
			* 1	��
			* 2 ����
			* 3 ��
			* 4 ����
			* 5 ��
			* 6 ����
			* 7 ��
			* 8 ����
			*/
			int checkArr[9] = { 1,1,1,1,1,1,1,1,1 };
			// ����ܱ��Ƿ�Ϊ������
			if (i == 0)
			{
				checkArr[0] = 0;
				checkArr[1] = 0;
				checkArr[2] = 0;
			}
			if (i == BOARD_SIZE)
			{
				checkArr[6] = 0;
				checkArr[7] = 0;
				checkArr[8] = 0;
			}
			if (j == 0)
			{
				checkArr[0] = 0;
				checkArr[3] = 0;
				checkArr[6] = 0;
			}
			if (j == BOARD_SIZE)
			{
				checkArr[2] = 0;
				checkArr[5] = 0;
				checkArr[8] = 0;
			}
			// ����ܱ��Ƿ���ѡ������
			for (int k = 0; k < 9; k++)
			{
				if (checkArr[k] == 0) {
					continue;
				}
				switch (k) {
				case 0:
					if (i - 1 == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 1:
					if (i - 1 == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 2:
					if (i - 1 == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 3:
					if (i == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 4:
					if (i == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 5:
					if (i == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 6:
					if (i + 1 == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 7:
					if (i + 1 == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 8:
					if (i + 1 == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				}
				// �������Ͻ������Ⱦ
				// ȡ����    ���ϣ��ϣ���,��������״̬
				/* ����:		0  1  3  4
				* �� ����ʵ��	0  0  0  2
				* ��	�������	0  0  0  1
				* ��	���Ҷ���	0  1  0  1
				* ��	����ʵ�Ҷ���0  1  0  2
				* ��	����ʵ�Ҷ���0  2  0  1
				* �� ���¶���	0  0  1  1
				* ��	����ʵ����	0  0  1  2
				* ��	����ʵ����	0  0  1  1
				* ��	��ʮ��		1  1  1  1
				* ��	����ʵʮ��	2  1  1  1
				* ��	����ʵʮ��	1  2  1  1
				* ��	����ʵʮ��	1  1  2  1
				* �� ����ʵʮ��	1  1  1  2
				*/
			}
			// ��һ�У�����
			int a = checkArr[0], b = checkArr[1], c = checkArr[3], d = checkArr[4];

			// ��������һ��
			if (i == BOARD_SIZE)
			{
				if (b == 2) {
					// �Ϸ���ѡ��
					if (j == 0)
					{
						printf("���T�T�T�T");
					}
					else if (j == BOARD_SIZE - 1) {
						printf("�بT�T�T�T��");
					}
					else {
						printf("�بT�T�T�T");
					}
				}
				else {
					// �Ϸ�δѡ��
					if (j == 0)
					{
						printf("����������");
					}
					else if (j == BOARD_SIZE - 1) {
						printf("�ة���������");
					}
					else {
						printf("�ة�������");
					}
				}
				continue;
			}

			if (j != BOARD_SIZE - 1)
			{
				if (a == 0 && b == 0 && c == 0 && d == 2) {
					printf("���T�T�T�T�ѩ�������");	// ��ֵ�bug����һ�������ѡ�У���������Ⱦһ�����Ͻǣ����Ե�һ�еĶ����һ�Σ�����ͬ��
				}
				else if (a == 0 && b == 0 && c == 0 && d == 1) {
					printf("����������");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 1) {
					printf("����������");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 2) {
					printf("�ƨT�T�T�T");
				}
				else if (a == 0 && b == 2 && c == 0 && d == 1) {
					printf("�ŨT�T�T�T");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 1) {
					printf("�Щ�������");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 2) {
					// ��һ��δ����
					if (x != BOARD_SIZE - 2)
					{
						printf("�֨T�T�T�T�ѩ�������");
					}
					// ��һ���ѽ���
					else {
						printf("�֨T�T�T�T�ѩ���������");
					}
				}
				else if (a == 1 && b == 1 && c == 1 && d == 1) {
					printf("�੤������");
				}
				else if (a == 2 && b == 1 && c == 1 && d == 1) {
					printf("�穤������");
				}
				else if (a == 1 && b == 2 && c == 1 && d == 1) {
					printf("��T�T�T�T");
				}
				else if (a == 1 && b == 1 && c == 2 && d == 1) {
					printf("�驤������");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 2) {
					printf("��T�T�T�T");
				}
			}
			else {
				if (a == 0 && b == 0 && c == 0 && d == 2) {
					printf("���T�T�T�T��");
				}
				else if (a == 0 && b == 0 && c == 0 && d == 1) {
					printf("������������");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 1) {
					printf("������������");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 2) {
					printf("�ƨT�T�T�T��");
				}
				else if (a == 0 && b == 2 && c == 0 && d == 1) {
					printf("�ŨT�T�T�T��");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 1) {
					printf("�Щ���������");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 2) {
					printf("�֨T�T�T�T��");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 1) {
					printf("�੤��������");
				}
				else if (a == 2 && b == 1 && c == 1 && d == 1) {
					printf("�穤��������");
				}
				else if (a == 1 && b == 2 && c == 1 && d == 1) {
					printf("��T�T�T�T��");
				}
				else if (a == 1 && b == 1 && c == 2 && d == 1) {
					printf("�驤��������");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 2) {
					printf("��T�T�T�T��");
				}
			}
		}
		printf("\n");

		// �ڶ��У����߼�����
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			// ���Ϊ���һ�У��Ͳ����Ƶײ�������
			if (i == BOARD_SIZE)
			{
				continue;
			}
			int checkArr[9] = { 1,1,1,1,1,1,1,1,1 };
			// ����ܱ��Ƿ�Ϊ������
			if (i == 0)
			{
				checkArr[0] = 0;
				checkArr[1] = 0;
				checkArr[2] = 0;
			}
			if (i == BOARD_SIZE)
			{
				checkArr[6] = 0;
				checkArr[7] = 0;
				checkArr[8] = 0;
			}
			if (j == 0)
			{
				checkArr[0] = 0;
				checkArr[3] = 0;
				checkArr[6] = 0;
			}
			if (j == BOARD_SIZE)
			{
				checkArr[2] = 0;
				checkArr[5] = 0;
				checkArr[8] = 0;
			}
			for (int k = 0; k < 9; k++)
			{
				// ����ܱ��Ƿ���ѡ������
				if (checkArr[k] == 0) {
					continue;
				}
				switch (k) {
				case 0:
					if (i - 1 == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 1:
					if (i - 1 == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 2:
					if (i - 1 == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 3:
					if (i == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 4:
					if (i == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 5:
					if (i == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 6:
					if (i + 1 == y && j - 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 7:
					if (i + 1 == y && j == x)
					{
						checkArr[k] = 2;
					}
					break;
				case 8:
					if (i + 1 == y && j + 1 == x)
					{
						checkArr[k] = 2;
					}
					break;
				}
			}
			// �������
			// ���ֻ����������й�
			/*
			*	����û��һ��״̬��2
			*	������һ��״̬��2
			*/
			int a = checkArr[3], b = checkArr[4];
			if (a == 2 || b == 2)
			{
				printf("�U ");
			}
			else {
				printf("�� ");
			}
			// ������
			switch (board[i][j]) {
			case 0:
				printf("   ");
				break;
			case 1:
				printf("��  ");
				break;
			case 2:
				printf("��  ");
				break;
			}

			// ��β
			if (j == BOARD_SIZE - 1)
			{
				if (b == 2)
				{
					printf("�U ");
				}
				else {
					printf("�� ");
				}
			}
		}
		printf("\n");
	}
}

void printMenuStart() {
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("              ��                    C����������                    ��              \n");
	printf("              �ǩ�������������������������������������������������������������������������������������������������������              \n");
	printf("              �����X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[�� ��              \n");
	printf("              �����U                   ��ʼ��Ϸ                   �U�� ��              \n");
	printf("              �����^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a�� ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    ��Ϸ����                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    �˳���Ϸ                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

void printMenuSetting() {
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("              ��                    C����������                    ��              \n");
	printf("              �ǩ�������������������������������������������������������������������������������������������������������              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    ��ʼ��Ϸ                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              �����X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[�� ��              \n");
	printf("              �����U                   ��Ϸ����                   �U�� ��              \n");
	printf("              �����^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a�� ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    �˳���Ϸ                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

void printMenuExit() {
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("              ��                    C����������                    ��              \n");
	printf("              �ǩ�������������������������������������������������������������������������������������������������������              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    ��ʼ��Ϸ                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ����                    ��Ϸ����                    �� ��              \n");
	printf("              ������������������������������������������������������������������������������������������������������ ��              \n");
	printf("              ��                                                   ��              \n");
	printf("              �����X�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�[�� ��              \n");
	printf("              �����U                   �˳���Ϸ                   �U�� ��              \n");
	printf("              �����^�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�T�a�� ��              \n");
	printf("              ����������������������������������������������������������������������������������������������������������              \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
}