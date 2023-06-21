#include <stdio.h>
#include "GameData.h"

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern, int hp)
{
	Enemy_exist[num] = true;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
	Enemy_HP[num] = hp;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveSpeed[num] = NULL;
	MovePattern[num] = NULL;
	Enemy_HP[num] = NULL;
}

void EnemyMove(int num)//ëﬁèÍ
{
	switch (MovePattern[num])
	{
		case 0://íºêi
			Enemy_Y[num] += Enemy_MoveSpeed[num];
			break;
		default:
			break;
	}
}

