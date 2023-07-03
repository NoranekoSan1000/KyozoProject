#pragma once

extern bool E_Bullet_exist[];
extern double E_Bullet_PosX[];
extern double E_Bullet_PosY[];
extern int E_Bullet_HitBoxSize[];
extern int E_Bullet_MovePattern[];
extern double E_Bullet_Angle[];

void EnemyBulletGenerate(int num, double x, double y, int hitboxsize, int pattern, double angle);
void EnemyBulletDestroy(int num);
float EnemyAngleCalc(int en_x, int en_y);
void EnemyShot(int design, EnemyShotPattern type, int en_x, int en_y, int capacity, int arc);
void EnemyBulletMove(int num);
void EnemyBulletHit(int num);
void EnemyBulletAction(void);
void EnemyBulletClear(void);