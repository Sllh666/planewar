#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>            //����������Ҫ��ͷ�ļ�
#pragma comment(lib,"winmm.lib") //�����ƶ��Ĳ������ֵĿ��ļ�

enum My
{
	WIDTH = 591, //���ڸ߶ȺͿ��
	HEIGHT = 864,
	BULLET_NUM = 15, //�ӵ��������
	ENEMY_NUM = 10, // �л��������
	BOSS, // ��л�
	SMALL // С�л�

};
struct plane {
	int x;
	int y;
	bool live;
	int speed;
	int width; //�л��߿�
	int height;
	int hp; //�л�Ѫ��
	int type;//�л�����
}player, bull[BULLET_NUM],enemy[ENEMY_NUM];
IMAGE bk; //����ͼƬ
IMAGE img_role[2]; //��ҷɻ�ͼƬ
IMAGE img_bull[2];
IMAGE img_enemy[2][2]; // �л�ͼƬ
void loadImg() { //����ͼƬ����
	loadimage(&bk, "./images/background.jpg");
	loadimage(&img_role[0], "./images/planeNormal_1.jpg"); //�������ͼ
	loadimage(&img_role[1], "./images/planeNormal_2.jpg"); //���ԭͼ

	loadimage(&img_bull[0], "./images/bullet1.jpg"); //�ӵ�����ͼ
	loadimage(&img_bull[1], "./images/bullet2.jpg"); //�ӵ�ԭͼ

	loadimage(&img_enemy[0][0], "./images/enemy_1.jpg"); //�л�����ͼ
	loadimage(&img_enemy[0][1], "./images/enemy_2.jpg"); //�л�ԭͼ
	loadimage(&img_enemy[1][0], "./images/enemyPlane1.jpg"); //
	loadimage(&img_enemy[1][1], "./images/enemyPlane2.jpg"); //
}
void enemyHp(int i) {
	if (rand()%10==0)
	{
		enemy[i].type = BOSS;
		enemy[i].hp = 3;
		enemy[i].width = 104;
		enemy[i].height = 148;
	}
	else
	{
		enemy[i].type = SMALL;
		enemy[i].hp = 1;
		enemy[i].width = 52;
		enemy[i].height = 39;
	}
}
void gameInit() { //��ʼ�����ݺ���
	loadImg();
	player.x = WIDTH / 2;//�ɻ�����������
	player.y = HEIGHT - 120;//�ɻ�����������
	player.speed = 1;//�ɻ��ƶ��ٶ�
	player.live = true;//��Ҵ��
	for (int  i = 0; i < BULLET_NUM; i++) // ��ʼ���л�
	{
		bull[i].live = false; // ��ʾ�ӵ�Ĭ�ϲ�����
	}
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].live = false;
		enemyHp(i);
	}
}
void gameDraw() { //����ͼƬ����
	putimage(0, 0, &bk);
	putimage(player.x, player.y,&img_role[0],NOTSRCERASE); //����ͼ
	putimage(player.x, player.y,&img_role[1],SRCINVERT); //ԭͼ
	
	for (int i = 0; i < BULLET_NUM; i++) // �����ӵ�
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE); //����ͼ
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT); //ԭͼ
		}
	}

	for (int i = 0; i < BULLET_NUM; i++) // ���Ƶл�
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BOSS) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE); //����ͼ
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT); //ԭͼ
			}
			else
			{
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE); //����ͼ
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT); //ԭͼ
			}
		}
	}
	

}

void creatrBullet() {//�ӵ���������
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (!bull[i].live)
		{	
			bull[i].x = player.x + 40;
			bull[i].y = player.y;
			bull[i].live = true;
			break;
		}
	}
}

void BulletMove() { // �ӵ��ƶ�����
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bull[i].live)
		{
			
			bull[i].y -= 1;
			if (bull[i].y<0)
			{
				bull[i].live = false;
			}
			
		}
	}
}
void playerMove() {// �ɻ��ƶ�����
	if (GetAsyncKeyState(VK_UP)|| GetAsyncKeyState('W')) {
		if (player.y > 0) {
			player.y -= player.speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN)|| GetAsyncKeyState('S')) {
		if (player.y+120<HEIGHT)
		{
			player.y += player.speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT)|| GetAsyncKeyState('A')) {
		if (player.x>0)
		{
			player.x -= player.speed;
		}
		
	}
	if (GetAsyncKeyState(VK_RIGHT)|| GetAsyncKeyState('D')) {
		if (player.x + 117 < WIDTH)
		{
			player.x += player.speed;
		}
	}
	static DWORD t1 = 0 ,t2 = 0;

	if (GetAsyncKeyState(VK_SPACE) && t2-t1>100)
	{	

		creatrBullet();
		t1 = t2;
		
	}
	t2 = GetTickCount();
}
// �����л�
void createEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].live)
		{
			enemy[i].live = true;
			enemy[i].x = rand() % (WIDTH - 60);
			enemy[i].y = 0;
			enemyHp(i);
			break;
		}
		
	}
}
// �л��ƶ�
void enemyMove() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live) {
			
			
			
				enemy[i].y += 1;
				
			}
			
			
			if (enemy[i].y>HEIGHT)
			{
				enemy[i].live = false;
			}
		}

	}
void playPlance() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (!enemy[i].live) {
			continue;
		}
		for (int  k = 0; k < BULLET_NUM; k++)
		{
			if (!bull[i].live)
			{
				continue;
			}
			if (bull[k].x>enemy[i].x && bull[k].x<enemy[i].x+enemy[i].width
			&& bull[k].y>enemy[i].y && bull[k].y < enemy[i].y + enemy[i].height)
			{
				bull[k].live = false;
				enemy[i].hp--;

			}
		}
		if (enemy[i].hp<=0)
		{
			enemy[i].live = false;
		}
		
	}

}
int boom() {
	for (int i = 0; i < ENEMY_NUM; i++) {
		if (enemy[i].live) {
			int playerRight = player.x + 117; // �޸���ҷɻ��ұ߽���㷽ʽ
			int playerBottom = player.y + 120; // �޸���ҷɻ��ײ��߽���㷽ʽ
			int enemyRight = enemy[i].x + enemy[i].width;
			int enemyBottom = enemy[i].y + enemy[i].height;
			if (player.x < enemyRight && playerRight > enemy[i].x && player.y < enemyBottom && playerBottom > enemy[i].y)
			{
				player.live = false;
				return 0;
			}
		}
	}
	return 1;
}
void music() {

}
int main() {
	mciSendString("./images/game_music.mp3 repeat", 0, 0, 0);
	initgraph(591, 864,SHOWCONSOLE);
	gameInit();
	BeginBatchDraw();//˫�����ͼ
	while (1)
	{
		gameDraw();
		FlushBatchDraw();
		playerMove();
		BulletMove();
		static DWORD t1 ,t2;
		if (t2 -t1 >500)
		{
			createEnemy();
			t1 = t2;

		}
		t2 = clock();
		static DWORD t3, t4;
		if (t4 - t3 > 10) {
			enemyMove();
			t3 = t4;
		}
		t4 = clock();
		int ret = boom();
		if (ret==0) {
			exit(1);
		}
		playPlance();
	}
	EndBatchDraw();
}