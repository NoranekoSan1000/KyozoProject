#pragma once

extern bool BossActive;
extern int Boss;
extern int BossStock;

void EnemySpawn(int type, MoveList move, int x, int y);
void EnemyClear(void);
void EnemyAction(void);

int GetBossCurrentHP(void);
int GetBossMaxHP(void);
int GetCloseEnemy_X(void);
int GetCloseEnemy_Y(void);
int GetCloseEnemyNum(void);