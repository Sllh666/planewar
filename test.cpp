#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>            //播放音乐需要的头文件
#pragma comment(lib,"winmm.lib") //加载制定的播放音乐的库文件

enum My
{
	WIDTH = 591, //窗口高度和宽度
	HEIGHT = 864,
	BULLET_NUM = 15, //子弹最多数量
	ENEMY_NUM = 10, // 敌机最多数量
	BOSS, // 大敌机
	SMALL // 小敌机

};
struct plane {
	int x;
	int y;
	bool live;
	int speed;
	int width; //敌机高宽
	int height;
	int hp; //敌机血量
	int type;//敌机类型
}player, bull[BULLET_NUM],enemy[ENEMY_NUM];
IMAGE bk; //背景图片
IMAGE img_role[2]; //玩家飞机图片
IMAGE img_bull[2];
IMAGE img_enemy[2][2]; // 敌机图片
void loadImg() { //载入图片函数
	loadimage(&bk, "./images/background.jpg");
	loadimage(&img_role[0], "./images/planeNormal_1.jpg"); //玩家掩码图
	loadimage(&img_role[1], "./images/planeNormal_2.jpg"); //玩家原图

	loadimage(&img_bull[0], "./images/bullet1.jpg"); //子弹掩码图
	loadimage(&img_bull[1], "./images/bullet2.jpg"); //子弹原图

	loadimage(&img_enemy[0][0], "./images/enemy_1.jpg"); //敌机掩码图
	loadimage(&img_enemy[0][1], "./images/enemy_2.jpg"); //敌机原图
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
void gameInit() { //初始化数据函数
	loadImg();
	player.x = WIDTH / 2;//飞机出生横坐标
	player.y = HEIGHT - 120;//飞机出生纵坐标
	player.speed = 1;//飞机移动速度
	player.live = true;//玩家存活
	for (int  i = 0; i < BULLET_NUM; i++) // 初始化敌机
	{
		bull[i].live = false; // 表示子弹默认不发射
	}
	for (int  i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].live = false;
		enemyHp(i);
	}
}
void gameDraw() { //绘制图片函数
	putimage(0, 0, &bk);
	putimage(player.x, player.y,&img_role[0],NOTSRCERASE); //掩码图
	putimage(player.x, player.y,&img_role[1],SRCINVERT); //原图
	
	for (int i = 0; i < BULLET_NUM; i++) // 绘制子弹
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE); //掩码图
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT); //原图
		}
	}

	for (int i = 0; i < BULLET_NUM; i++) // 绘制敌机
	{
		if (enemy[i].live)
		{
			if (enemy[i].type == BOSS) {
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][0], NOTSRCERASE); //掩码图
				putimage(enemy[i].x, enemy[i].y, &img_enemy[1][1], SRCINVERT); //原图
			}
			else
			{
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][0], NOTSRCERASE); //掩码图
				putimage(enemy[i].x, enemy[i].y, &img_enemy[0][1], SRCINVERT); //原图
			}
		}
	}
	

}

void creatrBullet() {//子弹创建函数
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

void BulletMove() { // 子弹移动函数
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
void playerMove() {// 飞机移动函数
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
// 产生敌机
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
// 敌机移动
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
			int playerRight = player.x + 117; // 修改玩家飞机右边界计算方式
			int playerBottom = player.y + 120; // 修改玩家飞机底部边界计算方式
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
	BeginBatchDraw();//双缓冲绘图
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