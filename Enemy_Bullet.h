#pragma once

void EnemyShot(int design, EnemyShotPattern type, int en_x, int en_y, int size, int capacity, int arc);
void EnemyBulletSpawn(int design, int en_x, int en_y, int size, int pattern, double angle);
void EnemyBulletClear(void);
void EnemyBulletAction(void);