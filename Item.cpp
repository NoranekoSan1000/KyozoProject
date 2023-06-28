#include "GameData.h"
#include "Player.h"

//“G
bool Item_exist[ITEM_AMOUNT];
int Item_X[ITEM_AMOUNT];
int Item_Y[ITEM_AMOUNT];
int Item_HitBoxSize[ITEM_AMOUNT];


void ItemGenerate(int num, int x, int y, int hitboxsize)
{
	Item_exist[num] = true;
	Item_X[num] = x;
	Item_Y[num] = y;
	Item_HitBoxSize[num] = hitboxsize;
}

void ItemDestroy(int num)
{
	Item_exist[num] = false;
	Item_X[num] = NULL;
	Item_Y[num] = NULL;
	Item_HitBoxSize[num] = NULL;
}

void ItemSpawn(int en_x,int en_y)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (Item_exist[i] == false)
		{
			ItemGenerate(i, en_x, en_y, 12);
			break;
		}
	}
}

void ItemMove(int num)
{
	Item_Y[num] += 2;
}

void ItemAction(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		//‰æ‘œ•\Ž¦
		if (Item_exist[i] == true) DrawCircle(Item_X[i], Item_Y[i], Item_HitBoxSize[i], GetColor(0, 0, 255), 1);
		else continue;

		DrawRotaGraph(Item_X[i], Item_Y[i], 1.0, 0, power_img, TRUE);//‰æ‘œ

		ItemMove(i);

		//“G‚ÆƒvƒŒƒCƒ„[‚ªÚG
		float dis = sqrt(pow((double)Item_X[i] - px, 2) + pow((double)Item_Y[i] - py, 2));

		//‰æ–ÊŠO‚ÅÁ–Å
		if (Item_Y[i] > FRAME_HEIGHT || 0 > Item_X[i] || Item_X[i] > FRAME_WIDTH)
		{
			ItemDestroy(i);
			continue;
		}

		if (dis <= Item_HitBoxSize[i] + Player_HitBoxSize)
		{
			//ÚG”»’è
			Power += 1;
			Score += 2;
			ItemDestroy(i);
			continue;
		}

		
	}
}

void ItemClear(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++) ItemDestroy(i);
}