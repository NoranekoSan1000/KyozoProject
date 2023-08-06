#include "GameData.h"
#include "Player.h"

class Item
{
private:	
	int ItemType;
	bool CollectTime;

public:
	bool State;
	int x;
	int y;
	int Item_HitBoxSize;

	void ItemGenerate(int itemtype, int ex, int ey, int hitboxsize)
	{
		State = true;
		ItemType = itemtype;
		x = ex;
		y = ey;
		Item_HitBoxSize = hitboxsize;
		CollectTime = false;
	}

	void ItemDestroy()
	{
		State = false;
		ItemType = NULL;
		x = NULL;
		y = NULL;
		Item_HitBoxSize = NULL;
		CollectTime = false;
	}

	void CollectItem()
	{
		if (py <= 150) CollectTime = true; //player.cpp
	}
	void ItemMove()
	{
		if (!CollectTime) y += 1;
		else
		{
			if (px < x - 8) x -= 8; //player.cpp
			else if (px > x + 8) x += 8;
			else x += 0;
			if (py < y - 10) y -= 10; //player.cpp
			else if (py > y + 10) y += 10;
			else y += 0;
		}
	}

	void HitPlayer(void)
	{
		if (ItemType == 0) //miniPower
		{
			Power += 1; //player.cpp
			Score += 2; //player.cpp
			PlaySE(SE_ItemGet);
		}
		if (ItemType == 1) //bigPower
		{
			Power += 5; //player.cpp
			Score += 10; //player.cpp
			PlaySE(SE_ItemGet);
		}
		if (ItemType == 2) //Life
		{
			Life += 1; //player.cpp
			Score += 10; //player.cpp
			PlaySE(SE_ItemGet);
		}
		if (ItemType == 3) //Bomb
		{
			Bomb += 1; //player.cpp
			Score += 10; //player.cpp
			PlaySE(SE_ItemGet);
		}
		ItemDestroy();
	}
};

Item item[ITEM_AMOUNT];

void ItemSpawn(int type, int en_x, int en_y)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (item[i].State != true)
		{
			item[i].ItemGenerate(type, en_x, en_y, 40);
			break;
		}
	}
}

void ItemClear(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++) item[i].ItemDestroy();
}

void ItemMovement(void)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (!item[i].State) continue; //生成されていなければ飛ばす

		item[i].CollectItem();//プレイヤーが画面上部へ行った時
		item[i].ItemMove();
		DrawRotaGraph(item[i].x, item[i].y, 1.0, 0, power_img, TRUE);//画像
		if (item[i].y > FRAME_HEIGHT || 0 > item[i].x || item[i].x > FRAME_WIDTH) item[i].ItemDestroy(); //画面外で消滅

		//プレイヤーが接触
		float dis = sqrt(pow((double)item[i].x - px, 2) + pow((double)item[i].y - py, 2)); //player.cpp
		if (dis <= item[i].Item_HitBoxSize + Player_HitBoxSize) item[i].HitPlayer();//player.cpp
	}
}