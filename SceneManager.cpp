#include "GameData.h"
#include "Enemy.h"
#include "Player_Bullet.h"
#include "Enemy_Bullet.h"
#include "Item.h"
#include "Player.h"

void StatusReset(void);

float StageTitleFadeTime = 0;

bool FadeIn = false;
bool FadeOut = false;
int fadeALPHA = 256;

bool ChangeSceneActive = false;
SceneManager nextScene;
SceneManager GameScene = Title_Scene;

void ViewFadeWindow(void)
{
	if (FadeIn) {
		if (FadeOut) FadeOut = false;
		if (fadeALPHA <= 0)
		{
			fadeALPHA = 0;
			FadeIn = false;
		}
		else fadeALPHA -= 2;
	}
	if (FadeOut) {
		if (FadeIn) FadeIn = false;
		if (fadeALPHA >= 256)
		{
			fadeALPHA = 256;
			FadeOut = false;
		}
		else fadeALPHA += 2;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeALPHA);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor(0, 0, 0), 1);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
}

void ObjectClear(void)
{
	PlayerBulletClear();
	EnemyBulletClear();
	EnemyClear();
	ItemClear();
}

void ChangeScene(void)
{
	if (!ChangeSceneActive) return;
	FadeOut = true;
	if (fadeALPHA == 256) //ÉVÅ[ÉìÇ™ïœÇÌÇÈèuä‘
	{
		ObjectClear();
		StageTitleFadeTime = 0;
		px = InitialPosX;
		py = InitialPosY;
		if (nextScene == Title_Scene) StatusReset();
		GameScene = nextScene;
		FadeIn = true;
		ChangeSceneActive = false;
	}
}

void StatusReset(void)
{
	Power = 0;
	Level = 0;
	Score = 0;
	Life = 3;
	Bomb = 2;
	BombTime = 0;
	DamagedCoolTime = 0;
	P_ShotCoolTime = 0;
}

