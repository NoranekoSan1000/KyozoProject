#pragma once

void PlayerBomb(int x, int y);
void PlayerShot(int px, int py, int type);
void PlayerBulletAction(void);
void PlayerBulletClear(void);

int GetP_BulletPosX(int num);
int GetP_BulletPosY(int num);
int GetP_BulletHitBoxSize(int num);
void DelP_Bullet(int num);