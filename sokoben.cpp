#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void put_out(int task[8][8]);  //刷新函数 刷新每一次按键的屏幕输出
void find_me(int task[8][8]);  //找到人的位置，并将坐标置于x,y中
void put_message(int p);//P传递输出哪个信息
void up(int task[8][8]);
void down(int task[8][8]);
void left(int task[8][8]);
void right(int task[8][8]);
void fun_task(int p);
int if_win(int task[8][8]);
int x = 0, y = 0;  //人的位置坐标
int task_one[8][8] = {   //推箱子第一关矩阵    0->空位置 1->墙  2->人 3->箱子 4->箱子位置 5->箱子成功到达位置
	{ 0, 0, 1, 1, 1, 0, 0, 0 },//x=0 y= 0->7
	{ 0, 0, 1, 4, 1, 0, 0, 0 },//x=1 y= 0->7
	{ 0, 0, 1, 3, 1, 1, 1, 1 },//x=2
	{ 1, 1, 1, 0, 0, 3, 4, 1 },//x=3
	{ 1, 4, 0, 3, 2, 1, 1, 1 },
	{ 1, 1, 1, 1, 3, 1, 0, 0 },
	{ 0, 0, 0, 1, 4, 1, 0, 0 },
	{ 0, 0, 0, 1, 1, 1, 0, 0 }
};
int task_two[8][8] = {   //推箱子第二关矩阵    0->空位置 1->墙  2->人 3->箱子 4->箱子位置 5->箱子成功到达位置
	{ 0, 1, 1, 1, 1, 1, 0, 0 },//x=0 y= 0->7
	{ 0, 1, 0, 0, 1, 1, 1, 0 },//x=1 y= 0->7
	{ 0, 1, 2, 3, 0, 0, 1, 0 },//x=2
	{ 1, 1, 1, 0, 1, 0, 1, 1 },//x=3
	{ 1, 4, 1, 0, 1, 0, 0, 1 },
	{ 1, 4, 3, 0, 0, 1, 0, 1 },
	{ 1, 4, 0, 0, 0, 3, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1 }
};
int task_two_box[8][8] = {    //为了存储箱子的位置
	{ 0, 0, 0, 0, 0, 0, 0, 0 },//x=0 y= 0->7
	{ 0, 0, 0, 0, 0, 0, 0, 0 },//x=1 y= 0->7
	{ 0, 0, 0, 0, 0, 0, 0, 0 },//x=2
	{ 0, 0, 0, 0, 0, 0, 0, 0 },//x=3
	{ 0, 4, 0, 0, 0, 0, 0, 0 },
	{ 0, 4, 0, 0, 0, 0, 0, 0 },
	{ 0, 4, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 }
};
int main()
{
A:	put_message(1);
	switch (_getch())
	{
	case 'q':
		break;
	case 'h':
		system("cls");
		put_message(2);
		switch (_getch())
		{
		case 'q':
			break;
		default:
			system("cls");
			goto A;
			break;
		}
		break;
	default:
		put_out(task_one);
		find_me(task_one);
		while (1)
		{
			find_me(task_one);
			fun_task(1);
			system("cls");
			put_message(1);
			if (if_win(task_one) == 1)
			{
				printf("胜利！进入第二关...\n");
				_getch();
				while (if_win(task_two) != 2)
				{
					system("cls");
					put_message(1);
					put_out(task_two);
					find_me(task_two);
					fun_task(2);
				}
				system("cls");
				put_message(1);
				printf("胜利\n");
				exit(0);
			}
			else
				put_out(task_one);
		}
		break;
	}

	return 0;
}
void find_me(int task[8][8])
{
	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (task[i][j] == 2)
			{
				x = i;
				y = j;
			}
		}
	}
}
void put_out(int task[8][8])
{
	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (task[i][j] == 0)
				printf("  ");
			if (task[i][j] == 1)
				printf("■");
			if (task[i][j] == 2)
				printf("⊙");
			if (task[i][j] == 3)
				printf("□");
			if (task[i][j] == 4)
				printf("☆");
			if (task[i][j] == 5)
				printf("★");
			if (j == 7)  //换行
				printf("\n");
		}
	}
}
void up(int task[8][8])    
{//一共五种情况
	if (task[x][y] == 2)
	{
		if (task[x - 1][y] == 0)  //判断上移是否为空格 走空
		{
			task[x - 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x - 1][y] == 4)//在点里不推箱子走
		{
			task[x - 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
			
		}
		if (task[x - 1][y] == 5 && task[x - 2][y] == 4) //在点里推箱子走
		{
			task[x - 1][y] = 2;
			task[x - 2][y] = 5;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x - 1][y] == 3 && task[x - 2][y] == 4)  //推箱子到点里
		{
			
			task[x - 2][y] = 5;
			task[x - 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x - 1][y] == 3 && task[x - 2][y] == 0) //推箱子在空白处走
		{
			task[x - 2][y] = 3;
			task[x - 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
	}
}
void left(int task[8][8])
{
	if (task[x][y] == 2)
	{
		if (task[x][y - 1] == 0)
		{
			task[x][y - 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y - 1] == 4)
		{
			task[x][y - 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y - 1] == 3 && task[x][y - 2] == 4)
		{
			task[x][y - 2] = 5;
			task[x][y - 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y - 1] == 3 && task[x][y - 2] == 0)
		{
			task[x][y - 2] = 3;
			task[x][y - 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
	}
}
void right(int task[8][8])
{
	if (task[x][y] == 2)
	{
		if (task[x][y + 1] == 0)
		{
			task[x][y + 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y + 1] == 4)
		{
			task[x][y + 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y + 1] == 3 && task[x][y + 2] == 4)
		{
			task[x][y + 2] = 5;
			task[x][y + 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x][y + 1] == 3 && task[x][y + 2] == 0)
		{
			task[x][y + 2] = 3;
			task[x][y + 1] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
	}
}
void down(int task[8][8])
{
	if (task[x][y] == 2)
	{
		if (task[x + 1][y] == 0)
		{
			task[x + 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x + 1][y] == 4)
		{
			task[x + 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x + 1][y] == 3 && task[x + 2][y] == 4)
		{
			task[x + 2][y] = 5;
			task[x + 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
		if (task[x + 1][y] == 3 && task[x + 2][y] == 0)
		{
			task[x + 2][y] = 3;
			task[x + 1][y] = 2;
			if (task_two_box[x][y] == 4)
				task[x][y] = 4;
			else
				task[x][y] = 0;
		}
	}
}
int if_win(int task[8][8])
{
	int count = 0;
	int i = 0, j = 0;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (task[i][j] == 5)
			{
				count++;
			}
		}
	}
	if (count == 4)
	{
		return 1;
	}
	else if(count == 3)
	{
		return 2;
	}
}
void put_message(int p)
{
	if (p == 1)
	{
		printf("********************************\n");
		printf("|                              |\n");
		printf("|                              |\n");
		printf("|       推箱子(一二关版)       |\n");
		printf("|                              |\n");
		printf("|       任意键开始 q退出       |\n");
		printf("|         w,a,s,d移动          |\n");
		printf("|                              |\n");
		printf("|               h键-关于本游戏 |\n");
		printf("********************************\n");
	}
	if (p == 2)
	{
		printf("********************************\n");
		printf("|                              |\n");
		printf("|                              |\n");
		printf("|       推箱子(一二关版)       |\n");
		printf("|                              |\n");
		printf("|       仅供娱乐学习之用       |\n");
		printf("|                              |\n");
		printf("|                              |\n");
		printf("|               作者：Tony     |\n");
		printf("********************************\n");
	}
}
void fun_task(int p)
{
	if (p == 1)
	{
		switch (_getch())
		{
		case 'w':
			up(task_one);
			break;
		case 'a':
			left(task_one);
			break;
		case 's':
			down(task_one);
			break;
		case 'd':
			right(task_one);
			break;
		default:
			break;
		}
	}
	else if (p == 2)
	{
		switch (_getch())
		{
		case 'w':
			up(task_two);
			break;
		case 'a':
			left(task_two);
			break;
		case 's':
			down(task_two);
			break;
		case 'd':
			right(task_two);
			break;
		default:
			break;
		}
	}
}