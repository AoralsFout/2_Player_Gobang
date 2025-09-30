#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 19
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

/*
* 数据
*   0 1 ...
* 0
* 1
* ...
*/
int x;								// 选中位置x坐标
int y;								// 选中位置y坐标
int board[BOARD_SIZE][BOARD_SIZE];	// 棋盘信息
int flag;							// 局数 偶数表示黑棋落子  奇数表示白棋落子

/*
* 初始化棋盘和局数
*/
void init();

/*
* 展示游戏玩法
*/
void showHowToPlay();

/*
* 显示菜单
*/
void menuView();

/*
* 以下三个函数在显示菜单中调用
* 打印选项不同的菜单
*/
void printMenuStart();
void printMenuSetting();
void printMenuExit();

/*
* 根据棋盘信息和当前选中位置渲染棋盘
*/
void printBoard();

/*
* 开始游戏
*/
void startGame();

/*
* 判断胜利
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
	// 重置局数
	flag = 1;
	// 重置棋盘
	int* p = &board[0][0];
	for (int i = 0; i < (BOARD_SIZE + 1) * (BOARD_SIZE + 1); i++)
	{
		*p = 0;
		p++;
	}
	// 重置选中
	x = BOARD_SIZE / 2;
	y = BOARD_SIZE / 2;
}

void menuView() {
	/*
	* 记录玩家选择
	* 0	退出游戏
	* 1 游戏设置
	* 2	开始游戏
	*/
	int selection = 2;
	while (1) {
		// 渲染目录选项
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
		// 阻塞主进程，直到有指定的键被按下
		int key;
		key = _getch();
		// 根据用户按键选择操作
		switch (key) {
			// 上键
		case 72:
			if (selection == 2)
			{
				selection = 2;
			}
			else
			{
				selection++;
			}
			system("cls");	// 清空控制台
			break;
			// 下键
		case 80:
			if (selection == 0)
			{
				selection = 0;
			}
			else
			{
				selection--;
			}
			system("cls");	// 清空控制台
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
			system("cls");	// 清空控制台
			break;
		}
	}
}

void showHowToPlay() {
	printf("C语言双人五子棋 by AoralsFout\n");
	printf("v1.0.0\n");
	printf("使用 ↑↓←→  键控制菜单选项\n");
	printf("使用 ↑↓←→  键控制棋盘\n");
	printf("使用 Enter 键确定\n");
	printf("\n");
	printf("请按任意键继续...");
	int c = _getch();	// 阻塞主进程，直到有按键被按下
	system("cls");		// 清空控制台
}

void startGame() {
	while (1) {
		int check;
		system("cls");
		// 打印棋盘信息
		printf("第 %d 局|由", flag);
		switch (flag % 2) {
		case 0:
			printf("  黑子○   出手|");
			break;
		case 1:
			printf("  白子●   出手|");
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
		// 用户操作棋盘
		//↑ 72 ↓80 ← 75 → 77
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
			// 只有空可以下棋
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
	int isFull = 1; // 假设棋盘已满

	// 检查棋盘是否已满
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
	* 遍历每一个格子，记录当前信息
	* 再次对水平，垂直，右下对角线，左下对角线方向遍历五次，如果有和记录信息相同的，则计数器自增。
	* 最后检查计数器是否为5
	*/

	// 遍历棋盘检查连续的五个棋子
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			// 记录当前棋子状态
			int current = board[i][j];
			// 跳过空白
			if (current == 0) continue;

			// 检查水平方向
			// 防越界
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

			// 检查垂直方向
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

			// 检查右下对角线
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

			// 检查左下对角线
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

	// 输出结果
	if (blackWin && whiteWin) {
		printf("啊？！请按任意键继续...\n");
	}
	else if (blackWin) {
		printf("黑子胜利！请按任意键继续...\n");
	}
	else if (whiteWin) {
		printf("白子胜利！请按任意键继续...\n");
	}
	else if (isFull) {
		printf("平局！棋盘已满，无人获胜。请按任意键继续...\n");
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
			* 每遍历一个格子，就记录周边及自身9个格子的状态，确定如何渲染棋盘
			* 检查周边情况
			* 值
			* 0	棋盘外
			* 1 棋盘内部
			* 2 选中
			* 索引
			* 0	左上
			* 1	上
			* 2 右上
			* 3 左
			* 4 自身
			* 5 右
			* 6 左下
			* 7 下
			* 8 右下
			*/
			int checkArr[9] = { 1,1,1,1,1,1,1,1,1 };
			// 检查周边是否为棋盘外
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
			// 检查周边是否有选中棋盘
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
				// 处理左上角如何渲染
				// 取决于    左上，上，左,自身三个状态
				/* 索引:		0  1  3  4
				* ┏ 右下实角	0  0  0  2
				* ┌	右下虚角	0  0  0  1
				* ├	虚右丁角	0  1  0  1
				* ┢	右下实右丁角0  1  0  2
				* ┡	右上实右丁角0  2  0  1
				* ┬ 虚下丁角	0  0  1  1
				* ┲	右下实丁角	0  0  1  2
				* ┱	左下实丁角	0  0  1  1
				* ┼	虚十角		1  1  1  1
				* ╃	左上实十角	2  1  1  1
				* ╄	右上实十角	1  2  1  1
				* ╅	左下实十角	1  1  2  1
				* ╆ 右下实十角	1  1  1  2
				*/
			}
			// 第一行，顶线
			int a = checkArr[0], b = checkArr[1], c = checkArr[3], d = checkArr[4];

			// 如果是最后一行
			if (i == BOARD_SIZE)
			{
				if (b == 2) {
					// 上方被选中
					if (j == 0)
					{
						printf("└════");
					}
					else if (j == BOARD_SIZE - 1) {
						printf("┴════┘");
					}
					else {
						printf("┴════");
					}
				}
				else {
					// 上方未选中
					if (j == 0)
					{
						printf("└────");
					}
					else if (j == BOARD_SIZE - 1) {
						printf("┴────┘");
					}
					else {
						printf("┴────");
					}
				}
				continue;
			}

			if (j != BOARD_SIZE - 1)
			{
				if (a == 0 && b == 0 && c == 0 && d == 2) {
					printf("┏════┭────");	// 奇怪的bug：第一行如果被选中，总是少渲染一次左上角，所以第一行的多加了一段，以下同理
				}
				else if (a == 0 && b == 0 && c == 0 && d == 1) {
					printf("┌────");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 1) {
					printf("├────");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 2) {
					printf("┢════");
				}
				else if (a == 0 && b == 2 && c == 0 && d == 1) {
					printf("┡════");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 1) {
					printf("┬────");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 2) {
					// 第一行未结束
					if (x != BOARD_SIZE - 2)
					{
						printf("┲════┭────");
					}
					// 第一行已结束
					else {
						printf("┲════┭────┐");
					}
				}
				else if (a == 1 && b == 1 && c == 1 && d == 1) {
					printf("┼────");
				}
				else if (a == 2 && b == 1 && c == 1 && d == 1) {
					printf("╃────");
				}
				else if (a == 1 && b == 2 && c == 1 && d == 1) {
					printf("╄════");
				}
				else if (a == 1 && b == 1 && c == 2 && d == 1) {
					printf("╅────");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 2) {
					printf("╆════");
				}
			}
			else {
				if (a == 0 && b == 0 && c == 0 && d == 2) {
					printf("┏════┓");
				}
				else if (a == 0 && b == 0 && c == 0 && d == 1) {
					printf("┌────┐");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 1) {
					printf("├────┤");
				}
				else if (a == 0 && b == 1 && c == 0 && d == 2) {
					printf("┢════┪");
				}
				else if (a == 0 && b == 2 && c == 0 && d == 1) {
					printf("┡════┦");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 1) {
					printf("┬────┐");
				}
				else if (a == 0 && b == 0 && c == 1 && d == 2) {
					printf("┲════┓");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 1) {
					printf("┼────┤");
				}
				else if (a == 2 && b == 1 && c == 1 && d == 1) {
					printf("╃────┤");
				}
				else if (a == 1 && b == 2 && c == 1 && d == 1) {
					printf("╄════┦");
				}
				else if (a == 1 && b == 1 && c == 2 && d == 1) {
					printf("╅────┤");
				}
				else if (a == 1 && b == 1 && c == 1 && d == 2) {
					printf("╆════┪");
				}
			}
		}
		printf("\n");

		// 第二行，竖线及棋子
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			// 如果为最后一行，就不绘制底部的竖条
			if (i == BOARD_SIZE)
			{
				continue;
			}
			int checkArr[9] = { 1,1,1,1,1,1,1,1,1 };
			// 检查周边是否为棋盘外
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
				// 检查周边是否有选中棋盘
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
			// 处理左侧
			// 左侧只与左和自身有关
			/*
			*	│：没有一个状态是2
			*	┃：有一个状态是2
			*/
			int a = checkArr[3], b = checkArr[4];
			if (a == 2 || b == 2)
			{
				printf("║ ");
			}
			else {
				printf("│ ");
			}
			// 处理棋
			switch (board[i][j]) {
			case 0:
				printf("   ");
				break;
			case 1:
				printf("○  ");
				break;
			case 2:
				printf("●  ");
				break;
			}

			// 封尾
			if (j == BOARD_SIZE - 1)
			{
				if (b == 2)
				{
					printf("║ ");
				}
				else {
					printf("│ ");
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
	printf("              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓              \n");
	printf("              ┃                    C语言五子棋                    ┃              \n");
	printf("              ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫              \n");
	printf("              ┃┌╔══════════════════════════════════════════════╗┐ ┃              \n");
	printf("              ┃│║                   开始游戏                   ║│ ┃              \n");
	printf("              ┃└╚══════════════════════════════════════════════╝┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    游戏设置                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    退出游戏                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛              \n");
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
	printf("              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓              \n");
	printf("              ┃                    C语言五子棋                    ┃              \n");
	printf("              ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    开始游戏                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌╔══════════════════════════════════════════════╗┐ ┃              \n");
	printf("              ┃│║                   游戏设置                   ║│ ┃              \n");
	printf("              ┃└╚══════════════════════════════════════════════╝┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    退出游戏                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛              \n");
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
	printf("              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓              \n");
	printf("              ┃                    C语言五子棋                    ┃              \n");
	printf("              ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    开始游戏                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌────────────────────────────────────────────────┐ ┃              \n");
	printf("              ┃│                    游戏设置                    │ ┃              \n");
	printf("              ┃└────────────────────────────────────────────────┘ ┃              \n");
	printf("              ┃                                                   ┃              \n");
	printf("              ┃┌╔══════════════════════════════════════════════╗┐ ┃              \n");
	printf("              ┃│║                   退出游戏                   ║│ ┃              \n");
	printf("              ┃└╚══════════════════════════════════════════════╝┘ ┃              \n");
	printf("              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛              \n");
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