#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <random>
#include <stack>
#include <windows.h>
#include <time.h>
#include <queue>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;

#define Windows_x 1100
#define Windows_y 731
#define maze_x 180
#define maze_y 130

MOUSEMSG m;//������

struct  pos//�洢ÿ���������Ϻ����µ�����
{
	int x1, y1;
	int x2, y2;
} map[30][30];

int maze[30][30] = { 0 };//�����еĳ����ͼ

struct node
{
	int x, y, s;
} s, e;
int go[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
int pre[1000001] = { 0 };
int vis[25][25];
void init();//��ʼ������
void start();//��Ϸ�߼�����
int bfs(int x, int y);//���й���
void myprint(int n);//���д�ӡ·��

int bfs(int x, int y)
{
	node now, to;
	now.x = x, now.y = y, now.s = 0;
	queue <node>q;
	vis[x][y] = 1;
	q.push(now);
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now.x == e.x&&now.y == e.y)
			return now.s;
		for (int i = 0; i<4; i++)
		{
			int xx = now.x + go[i][0];
			int yy = now.y + go[i][1];
			if (xx >= 0 && xx<20 && yy >= 0 && yy<20 && maze[xx][yy] == 0 && !vis[xx][yy])
			{
				vis[xx][yy] = 1;
				to.x = xx, to.y = yy, to.s = now.s + 1;
				pre[xx * 20 + yy] = now.x * 20 + now.y;
				q.push(to);
			}
		}
	}
	return -1;
}

queue<node>stk;//�ö������洢·��
void myprint(int n)//����Ѱ��·��
{
	if (-1 == pre[n])return;
	myprint(pre[n]);
	node t;
	t.x = n / 20, t.y = n % 20;
	stk.push(t);
}

void start()//��ʼ��Ϸ
{
	srand(unsigned(time(0)));//��ʱ���������������
	loadimage(NULL, "welcome_0.jpg");
	setlinestyle(PS_SOLID, 2);//���û�����ʽ
	setlinecolor(BLACK);
	rectangle(maze_x, maze_y, maze_x + 500, maze_y + 500);//�Թ�������
														  //�����Թ���ͼ20*20
	for (int x = maze_x; x <= maze_x + 500; x += 25)
		line(x, maze_y, x, maze_y + 500);
	for (int y = maze_y; y <= maze_y + 500; y += 25)
		line(maze_x, y, maze_x + 500, y);
	//�洢ÿ�����ӵ�����
	for (int i = 0; i<20; i++)
		for (int j = 0; j < 20; j++)
		{
			map[i][j].x1 = maze_x + 25 * j;
			map[i][j].y1 = maze_y + 25 * i;
			map[i][j].x2 = map[i][j].x1 + 25;
			map[i][j].y2 = map[i][j].y1 + 25;
		}
	//����ť
	setfillcolor(RGB(131, 175, 155));
	fillrectangle(700, 130, 950, 634);
	rectangle(700, 130, 700 + 250, 130 + 84);//�������1
	rectangle(700, 130 + 84, 700 + 250, 130 + 84 * 2);//�����յ�2
	rectangle(700, 130 + 84 * 2, 700 + 250, 130 + 84 * 3);//�����ϰ�3
	rectangle(700, 130 + 84 * 3, 700 + 250, 130 + 84 * 4);//����ϰ�4
	rectangle(700, 130 + 84 * 4, 700 + 250, 130 + 84 * 5);//��ʼѰ·5
	rectangle(700, 130 + 84 * 5, 700 + 250, 130 + 84 * 6);//���õ�ͼ6
	RECT r1 = { 700, 130, 700 + 250, 130 + 84 };
	RECT r2 = { 700, 130 + 84, 700 + 250, 130 + 84 * 2 };
	RECT r3 = { 700, 130 + 84 * 2, 700 + 250, 130 + 84 * 3 };
	RECT r4 = { 700, 130 + 84 * 3, 700 + 250, 130 + 84 * 4 };
	RECT r5 = { 700, 130 + 84 * 4, 700 + 250, 130 + 84 * 5 };
	RECT r6 = { 700, 130 + 84 * 5, 700 + 250, 130 + 84 * 6 };
	settextcolor(BLUE);
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 60;                      // ��������߶�Ϊ 60
	_tcscpy(f.lfFaceName, "΢���ź�");
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����
	settextstyle(&f);                     // ����������ʽ
	drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	int MODE = 0;//��ǰ��ť����ʾ���¼�
				 //���������Ϣ
	while (true)
	{
		BeginBatchDraw();
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE://�������ƶ�
			EndBatchDraw();
			if (m.x >= 700 && m.x <= 950 && m.y >= 130 && m.y <= 634)//�ڰ�ť����
			{
				if (m.y >= 130 && m.y < 214)//�������
				{
					setfillcolor(RGB(254, 67, 101));
					fillrectangle(700, 130, 950, 214);//r1
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 214, 950, 298);//r2
					fillrectangle(700, 298, 950, 382);//r3
					fillrectangle(700, 382, 950, 466);//r4
					fillrectangle(700, 466, 950, 550);//r5
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (m.y >= 214 && m.y < 298)//�����յ�
				{
					setfillcolor(RGB(254, 67, 101));//r2
					fillrectangle(700, 214, 950, 298);
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 130, 950, 214);//r1
					fillrectangle(700, 298, 950, 382);//r3
					fillrectangle(700, 382, 950, 466);//r4
					fillrectangle(700, 466, 950, 550);//r5
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (m.y >= 298 && m.y < 382)//�����ϰ�
				{
					setfillcolor(RGB(254, 67, 101));
					fillrectangle(700, 298, 950, 382);//r3
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 130, 950, 214);//r1
					fillrectangle(700, 214, 950, 298);//r2
					fillrectangle(700, 382, 950, 466);//r4
					fillrectangle(700, 466, 950, 550);//r5
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (m.y >= 382 && m.y < 466)//����ϰ�
				{
					setfillcolor(RGB(254, 67, 101));
					fillrectangle(700, 382, 950, 466);//r4
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 130, 950, 214);//r1
					fillrectangle(700, 214, 950, 298);//r2
					fillrectangle(700, 298, 950, 382);//r3
					fillrectangle(700, 466, 950, 550);//r5
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (m.y >= 466 && m.y < 550)//��ʼѰ·
				{
					setfillcolor(RGB(254, 67, 101));
					fillrectangle(700, 466, 950, 550);//r5
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 130, 950, 214);//r1
					fillrectangle(700, 214, 950, 298);//r2
					fillrectangle(700, 298, 950, 382);//r3
					fillrectangle(700, 382, 950, 466);//r4
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (m.y >= 550 && m.y < 634)//������Ϸ
				{
					setfillcolor(RGB(254, 67, 101));
					fillrectangle(700, 550, 950, 634);//r6
					drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					setfillcolor(RGB(131, 175, 155));
					fillrectangle(700, 130, 950, 214);//r1
					fillrectangle(700, 214, 950, 298);//r2
					fillrectangle(700, 298, 950, 382);//r3
					fillrectangle(700, 382, 950, 466);//r4
					fillrectangle(700, 466, 950, 550);//r5
					drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			else
			{
				setfillcolor(RGB(131, 175, 155));
				fillrectangle(700, 130, 950, 214);//r1
				fillrectangle(700, 214, 950, 298);//r2
				fillrectangle(700, 298, 950, 382);//r3
				fillrectangle(700, 382, 950, 466);//r4
				fillrectangle(700, 466, 950, 550);//r5
				fillrectangle(700, 550, 950, 634);//r6
				drawtext("�������", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("�����յ�", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("�����ϰ�", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("����ϰ�", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("��ʼѰ·", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				drawtext("������Ϸ", &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			break;
		case WM_LBUTTONDOWN://����������
			EndBatchDraw();
			if (m.x >= 180 && m.x <= 680 && m.y >= 130 && m.y <= 630)//���Թ�����
			{
				int tx, ty;//�洢��������
						   //�ҵ���ǰ����ĵ���ͼ�ϵ���һ������
				int f = 1;
				pos ans;//�洢�ҵ��ĸ���
				for (int i = 0; i < 20 && f; i++)
				{
					for (int j = 0; j < 20 && f; j++)
					{
						if (m.x >= map[i][j].x1&&m.x <= map[i][j].x2&&m.y >= map[i][j].y1&&m.y <= map[i][j].y2)
						{
							f = 0;
							ans = map[i][j];
							tx = i, ty = j;
						}
					}
				}
				//���������ͼ
				if (MODE == 1)//���Ϊ��ɫ
				{
					setfillcolor(RED);
					fillrectangle(ans.x1, ans.y1, ans.x2, ans.y2);
					s.x = tx, s.y = ty;
					MODE = 0;
				}
				else if (MODE == 2)//�յ�Ϊ��ɫ
				{
					setfillcolor(BLUE);
					fillrectangle(ans.x1, ans.y1, ans.x2, ans.y2);
					e.x = tx, e.y = ty;
					MODE = 0;
				}
				else if (MODE == 3)//�ϰ�Ϊ��ɫ
				{
					setfillcolor(BLACK);
					fillrectangle(ans.x1, ans.y1, ans.x2, ans.y2);
					maze[tx][ty] = 1;
				}
			}
			else if (m.x >= 700 && m.x <= 950 && m.y >= 130 && m.y <= 630)//�ڰ�ť����
			{
				if (m.y >= 130 && m.y < 214)//�����������
				{
					MODE = 1;
				}
				else if (m.y >= 214 && m.y < 298)//�����յ�����
				{
					MODE = 2;
				}
				else if (m.y >= 298 && m.y < 382)//�����ϰ�����
				{
					MODE = 3;
				}
				else if (m.y >= 382 && m.y < 466)//����ϰ�����
				{
					int rad[30][30];
					mem(rad, 0);
					for (int cse = 0; cse < 100; cse++)
					{
						int random_x = rand() % 20;
						int random_y = rand() % 20;
						if (maze[random_x][random_y] == 0 && rad[random_x][random_y] == 0
							&&(random_x!=s.x||random_y!=s.y)&&(random_x!=e.x&&random_y!=e.y))
						{
							maze[random_x][random_y] = 1;
							setfillcolor(BLACK);
							pos ans = map[random_x][random_y];
							fillrectangle(ans.x1, ans.y1, ans.x2, ans.y2);
						}
					}
				}
				else if (m.y >= 466 && m.y < 550)//��ʼѰ·����BFS
				{
					mem(vis, 0);
					mem(pre, -1);
					int jieguo = bfs(s.x, s.y);
					if (jieguo == -1)
					{
						MessageBox(GetHWnd(), "���ź�,Ѱ·ʧ��", "��ʾ", 0);
					}
					else
					{
						char temp[30];
						sprintf(temp, "��ϲ��Ѱ·�ɹ���һ��%d��!", jieguo);
						myprint(e.x * 20 + e.y);
						setfillcolor(YELLOW);
						while (stk.size() != 1 && !stk.empty())
						{
							node fr = stk.front();
							stk.pop();
							Sleep(50);
							fillrectangle(map[fr.x][fr.y].x1, map[fr.x][fr.y].y1, map[fr.x][fr.y].x2, map[fr.x][fr.y].y2);
						}
						MessageBox(GetHWnd(), temp, "��ʾ", 0);
					}
				}
				else if (m.y >= 550 && m.y < 634)//������Ϸ����
				{
					loadimage(NULL, "welcome_0.jpg");
					setlinestyle(PS_SOLID, 2);//���û�����ʽ
					setlinecolor(BLACK);
					rectangle(maze_x, maze_y, maze_x + 500, maze_y + 500);//�Թ�������
																		  //�����Թ���ͼ20*20
					for (int x = maze_x; x <= maze_x + 500; x += 25)
						line(x, maze_y, x, maze_y + 500);
					for (int y = maze_y; y <= maze_y + 500; y += 25)
						line(maze_x, y, maze_x + 500, y);
					MODE = 0;
					mem(vis, 0);
					mem(maze, 0);
					mem(pre, -1);
					while (!stk.empty())
					{
						stk.pop();
					}
				}
			}
			break;
		}
	}
	_getch();              // �����������
	closegraph();          // �رջ�ͼ����
}
void init()//�Կ�ʼ���������Ⱦ
{
	initgraph(Windows_x, Windows_y);
	loadimage(NULL, "welcome.jpg");
	setbkmode(TRANSPARENT);//͸������
	HWND hwnd = GetHWnd();//��ȡ��ǰ���ھ��
	SetWindowText(hwnd, "�Թ��Զ�Ѱ·   --- By:������");//���ô��ڱ���
	settextcolor(RGB(77, 77, 77));
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 65;                      // ��������߶�Ϊ 48
	_tcscpy(f.lfFaceName, "΢���ź�");
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����
	settextstyle(&f);                     // ����������ʽ
	RECT BegingameText = { Windows_x / 4 + 100, Windows_y / 2, Windows_x / 4 + 450, Windows_y / 2 + 110 };//"��ʼ��Ϸ"��λ��
	drawtext("���� ʼ �� Ϸ��", &BegingameText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	bool flag = true;
	while (flag)
	{
		BeginBatchDraw();
		m = GetMouseMsg();//��ȡ�����Ϣ
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN://������������
			EndBatchDraw();
			if (m.x >= Windows_x / 4 + 100 && m.x <= Windows_x / 4 + 450 && m.y >= Windows_y / 2 && m.y <= Windows_y / 2 + 110)//�����ʼ��Ϸ
			{
				flag = false;
				start();
			}
		case WM_MOUSEMOVE://�������ƶ�
			EndBatchDraw();
			if (m.x >= Windows_x / 4 + 100 && m.x <= Windows_x / 4 + 450 && m.y >= Windows_y / 2 && m.y <= Windows_y / 2 + 110)
			{
				settextcolor(RGB(69, 137, 148));
				drawtext("���� ʼ �� Ϸ��", &BegingameText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
			else
			{
				settextcolor(RGB(77, 77, 77));
				drawtext("���� ʼ �� Ϸ��", &BegingameText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}
int main()
{
	init();
	return 0;
}
