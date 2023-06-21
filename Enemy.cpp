#include <stdio.h>
#include "GameData.h"

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed, int movepattern)
{
	Enemy_exist[num] = true;
	Enemy_X[num] = x;
	Enemy_Y[num] = y;
	Enemy_HitBoxSize[num] = hitboxsize;
	Enemy_MoveSpeed[num] = movespeed;
	MovePattern[num] = movepattern;
}

void EnemyDestroy(int num)
{
	Enemy_exist[num] = false;
	Enemy_X[num] = NULL;
	Enemy_Y[num] = NULL;
	Enemy_HitBoxSize[num] = NULL;
	Enemy_MoveSpeed[num] = NULL;
	MovePattern[num] = NULL;
}

void EnemyMove(int num)//�ޏ�
{
	switch (MovePattern[num])
	{
	case 0://���i
		Enemy_Y[num] += Enemy_MoveSpeed[num];
		break;
	default:
		break;
	}
	
}