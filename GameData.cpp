
#define ENEMY_AMOUNT 20
#define PLAYER_BULLET_AMOUNT 50

//プレイヤー
int InitialPosX = 350;
int InitialPosY = 550;
int Player_HitBoxSize = 4;
int px = InitialPosX;
int py = InitialPosY;
int Score = 0;
int Life = 10;

//プレイヤーの弾
int P_Bullet_Amount = PLAYER_BULLET_AMOUNT;
bool P_Bullet_exist[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosX[PLAYER_BULLET_AMOUNT];
int P_Bullet_PosY[PLAYER_BULLET_AMOUNT];
int P_Bullet_HitBoxSize[PLAYER_BULLET_AMOUNT];
float P_ShotCoolTime = 0;

//敵
int Enemy_Amount = ENEMY_AMOUNT;
bool Enemy_exist[ENEMY_AMOUNT];
int Enemy_X[ENEMY_AMOUNT];
int Enemy_Y[ENEMY_AMOUNT];
int Enemy_HitBoxSize[ENEMY_AMOUNT];
int Enemy_MoveSpeed[ENEMY_AMOUNT];
int MovePattern[ENEMY_AMOUNT];