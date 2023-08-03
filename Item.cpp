#include "GameData.h"
#include "Player.h"

//敵
bool Item_exist[ITEM_AMOUNT];
int Item_X[ITEM_AMOUNT];
int Item_Y[ITEM_AMOUNT];
int Item_HitBoxSize[ITEM_AMOUNT];
bool CollectTime[ITEM_AMOUNT];

void ItemGenerate(int num, int x, int y, int hitboxsize)
{
	Item_exist[num] = true;
	Item_X[num] = x;
	Item_Y[num] = y;
	Item_HitBoxSize[num] = hitboxsize;
	CollectTime[num] = false;
}

void ItemDestroy(int num)
{
	Item_exist[num] = false;
	Item_X[num] = NULL;
	Item_Y[num] = NULL;
	Item_HitBoxSize[num] = NULL;
	CollectTime[num] = false;
}

void ItemSpawn(int en_x,int en_y)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (Item_exist[i] == false)
		{
			ItemGenerate(i, en_x, en_y, 20);
			break;
		}
	}
}

void ItemMove(int num)
{
	if (!CollectTime[num]) Item_Y[num] += 1;
	else
	{
		if (px < Item_X[num] - 8) Item_X[num] -= 8;
		else if(px > Item_X[num] + 8) Item_X[num] += 8;
		else Item_X[num] += 0;
		if (py < Item_Y[num] - 10 ) Item_Y[num] -= 10;
		else if (py > Item_Y[num] +10) Item_Y[num] += 10;
		else Item_Y[num] += 0;
	}
}

void CollectItem(int num) 
{
	if (py <= 150) CollectTime[num] = true;
}

void ItemAction(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		//画像表示
		if (Item_exist[i] == true) DrawRotaGraph(Item_X[i], Item_Y[i], 1.0, 0, power_img, TRUE);//画像
		else continue;

		
		CollectItem(i);//プレイヤーが画面上部へ行った時
		ItemMove(i);

		//敵とプレイヤーが接触
		float dis = sqrt(pow((double)Item_X[i] - px, 2) + pow((double)Item_Y[i] - py, 2));

		//画面外で消滅
		if (Item_Y[i] > FRAME_HEIGHT || 0 > Item_X[i] || Item_X[i] > FRAME_WIDTH)
		{
			ItemDestroy(i);
			continue;
		}

		if (dis <= Item_HitBoxSize[i] + Player_HitBoxSize)
		{
			//接触判定
			Power += 1;
			Score += 2;
			PlaySE(SE_ItemGet);
			ItemDestroy(i);
			continue;
		}
	}
}

void ItemClear(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++) ItemDestroy(i);
}