#pragma once
#include <stdio.h>
#include <algorithm>
#include <DxLib.h>
#include <math.h>
#include <string>
#include "KeyManager.h"
#include "Image.h"
#include "Audio.h"
#include "SceneManager.h"

using namespace std;
#define PI 3.14159265f

#define ENEMY_AMOUNT 20
#define PLAYER_BULLET_AMOUNT 80
#define ENEMY_BULLET_AMOUNT 700
#define ITEM_AMOUNT 40

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 800
#define FRAME_WIDTH 600
#define FRAME_HEIGHT 775

extern float StageTitleFadeTime;
extern bool BossBGM;

enum Difficulty { Easy, Normal, Hard, HellDiva };

enum EnemyShotPattern
{
	ShotWait,
	OneShot,
	AimingOneShot,
	Explosion,
	AimingExplosion,
	Diffusion,
	AimingDiffusion,
	ShotEnd,
};

enum MoveList
{
	MOVE_A,
	MOVE_B,
	MOVE_C,
	MOVE_D,
	MOVE_E,
	MOVE_BOSS
};
