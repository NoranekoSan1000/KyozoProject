#pragma once
extern int Enemy_Amount;
extern bool Enemy_exist[];
extern int Enemy_X[];
extern int Enemy_Y[];
extern int Enemy_HitBoxSize[];
extern int Enemy_MoveSpeed[];

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed);
void EnemyDestroy(int num);