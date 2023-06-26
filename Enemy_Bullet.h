#pragma once

extern bool E_Bullet_exist[];
extern int E_Bullet_PosX[];
extern int E_Bullet_PosY[];
extern int E_Bullet_HitBoxSize[];
extern int E_Bullet_MovePattern[];
extern float E_Bullet_Angle[];

void EnemyBulletGenerate(int num, int x, int y, int hitboxsize, int pattern, float angle);
void EnemyBulletDestroy(int num);
float EnemyAngleCalc(int en_x, int en_y);
void EnemyShot(int en_x, int en_y, int size, int type);
void EnemyBulletMove(int num);
void EnemyBulletHit(int num);
void EnemyBulletAction(void);
void EnemyBulletClear(void);