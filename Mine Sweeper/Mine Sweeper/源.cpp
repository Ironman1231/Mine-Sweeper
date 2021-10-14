#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <ctime>

using namespace std;

#define ROW 10     //����
#define COL 10     //����
#define Mine 3    //����
#define SIZE 30    //ͼƬ��С

int map[ROW + 1][COL + 1];       //��һ��/��Ϊ������/��
IMAGE img[12];
bool visited[ROW + 1][COL + 1];   //��¼�÷����Ƿ񷭹�

//����ͼƬ
void LoadImg()
{
	loadimage(&img[0], L"0.jpg", SIZE, SIZE);
	loadimage(&img[1], L"1.jpg", SIZE, SIZE);
	loadimage(&img[2], L"2.jpg", SIZE, SIZE);
	loadimage(&img[3], L"3.jpg", SIZE, SIZE);
	loadimage(&img[4], L"4.jpg", SIZE, SIZE);
	loadimage(&img[5], L"5.jpg", SIZE, SIZE);
	loadimage(&img[6], L"6.jpg", SIZE, SIZE);
	loadimage(&img[7], L"7.jpg", SIZE, SIZE);
	loadimage(&img[8], L"8.jpg", SIZE, SIZE);
	loadimage(&img[9], L"9.jpg", SIZE, SIZE);     //��
	loadimage(&img[10], L"10.jpg", SIZE, SIZE);   //����
	loadimage(&img[11], L"11.jpg", SIZE, SIZE);   //����
}

//��ʾ��Χ�׵ĸ���
void ShowMine()
{
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			if (map[i][j] != -1)
			{//ɨ�������׵ĸ���
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if (map[m][n] == -1) map[i][j]++;
					}
				}
			}
		}
	}
}
void initial()       //��Ϸ��ʼ��
{
	//���������ʼ��
	for (int i = 0; i <= ROW; i++)
	{
		for (int j = 0; j <= COL; j++)
		{
			map[i][j] = 0;
		}
	}

	//�����׵�λ��
	int num = 0;   //����
	srand((int)(time(NULL)));
	while (num != Mine)
	{
		int x = (rand() % (COL)) + 1;     //x����
		int y = (rand() % (ROW)) + 1;
		if (map[y][x] == 0)
		{
			map[y][x] = -1;
			num++;
		}
	}

	ShowMine();    //��ʾ��Χ�׵ĸ���

	//��������м���
	for (int i = 1; i <= ROW; i++)
	{
		for (int j = 1; j <= COL; j++)
		{
			map[i][j] += 20;
		}
	}
}

void initial_map()     //�Ե�ͼ�ĳ�ʼ�����������ͼ
{
	for (int i = 1; i <= ROW; i++)      //������飨ͼƬ��
	{
		for (int j = 1; j <= COL; j++)
		{
			//��ȫ�ķ���
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);
			}
			//�ȵ���
			if (map[i][j] == -1)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[9]);
			}
			//�����
			if (map[i][j] >= 39 && map[i][j] <= 48)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);
			}
			//���ܵķ���
			if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);
			}
		}
		cout << endl;
	}
}

//void check_out(int(*map)[11], int x, int y)
void check_out(int x, int y)    //����㿪����0������Χ�Ƿ�Ҳ��0���������һ�𷭿�
{
	if (map[x][y] >= 20 && map[x][y] <= 28)
	{
		map[x][y] -= 20;
		visited[x][y] = true;
	}
	if (map[x][y] != 0)
	{
		return;
	}
	else if (map[x][y] == 0)
	{
		/*check_out(x - 1, y);       ������������д��������д�ᳬ�����ĵݹ����
		check_out(x + 1, y);
		check_out(x, y - 1);
		check_out(x, y + 1);*/
		if (!visited[x - 1][y] && x - 1 > 0) check_out(x - 1, y);
		if (!visited[x + 1][y] && x + 1 <= ROW) check_out(x + 1, y);
		if (!visited[x][y + 1] && y + 1 <= COL) check_out(x, y + 1);
		if (!visited[x][y - 1] && y - 1 > 0) check_out(x, y - 1);
	}
}

bool game_rule()
{
	ExMessage msg;
	getmessage(&msg, EM_MOUSE);
	if (msg.lbutton)        //������
	{
		int y = msg.x / SIZE + 1;
		int x = msg.y / SIZE + 1;
		if (map[x][y] >= 20 && map[x][y] <= 28)
		{
			//check_out(map, x, y);
			check_out(x, y);
		}
		else if (map[x][y] == 19)
		{
			map[x][y] -= 20;
			return true;
		}
	}
	else if (msg.rbutton)     //�Ҽ����
	{
		int y = msg.x / SIZE + 1;
		int x = msg.y / SIZE + 1;
		if (map[x][y] >= 19 && map[x][y] <= 28)
		{
			map[x][y] += 20;
		}
		else if (map[x][y] >= 39 && map[x][y] <= 48)
		{
			map[x][y] -= 20;
		}
	}
	return false;
}

int main()
{
	initgraph(SIZE * COL, SIZE * ROW);    //����x������y
	LoadImg();
	initial();
	initial_map();
	while (true)
	{
		initial_map();
		if (game_rule())
		{
			initial_map();
			break;
		}
	}
	system("pause");
	return 0;
}