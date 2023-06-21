#pragma once
extern int Enemy_Amount;
extern bool exist[];
extern int enX[];
extern int enY[];
extern int enHitBoxSize[];
extern int moveSpeed[];

void EnemyGenerate(int num, int x, int y, int hitboxsize, int movespeed);
void EnemyDestroy(int num);