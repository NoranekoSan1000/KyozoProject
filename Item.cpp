#include "GameData.h"
#include "Player.h"

class Item
{
private:	
	bool CollectTime;

public:
	int x;
	int y;
	int Item_HitBoxSize;
	bool Item_exist;

	void ItemGenerate(int ex, int ey, int hitboxsize) //コンストラクタ
	{
		Item_exist = true;
		x = ex;
		y = ey;
		Item_HitBoxSize = hitboxsize;
		CollectTime = false;
	}

	void ItemDestroy()
	{
		Item_exist = false;
		x = NULL;
		y = NULL;
		Item_HitBoxSize = NULL;
		CollectTime = false;
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

	void CollectItem()
	{
		if (py <= 150) CollectTime = true; //player.cpp
	}
};

Item item[ITEM_AMOUNT];

void ItemSpawn(int en_x, int en_y)
{
	for (int i = 0; i < ITEM_AMOUNT; i++)
	{
		if (item[i].Item_exist != true)
		{
			item[i].ItemGenerate(en_x, en_y, 40);
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
		if (!item[i].Item_exist) continue;

		item[i].CollectItem();//プレイヤーが画面上部へ行った時
		item[i].ItemMove();

		 DrawRotaGraph(item[i].x, item[i].y, 1.0, 0, power_img, TRUE);//画像
		
		//画面外で消滅
		if (item[i].y > FRAME_HEIGHT || 0 > item[i].x || item[i].x > FRAME_WIDTH)
		{
			item[i].ItemDestroy();
		}

		//プレイヤーが接触
		float dis = sqrt(pow((double)item[i].x - px, 2) + pow((double)item[i].y - py, 2)); //player.cpp
		if (dis <= item[i].Item_HitBoxSize + Player_HitBoxSize) //player.cpp
		{
			//接触判定
			Power += 1; //player.cpp
			Score += 2; //player.cpp
			PlaySE(SE_ItemGet);
			item[i].ItemDestroy();
		}
	}
}