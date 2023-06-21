#include "GameData.h"

//プレイヤー
int InitialPosX = 350;
int InitialPosY = 550;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Score = 0;
int Life = 10;
float DamagedCoolTime = 0;

//プレイヤーの弾
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
float P_ShotCoolTime = 0;

//敵
bool Enemy_exist[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];
int Enemy_HP[ENEMY_AMOUNT];