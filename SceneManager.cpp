#include "GameData.h"
#include "Enemy.h"
#include "Player_Bullet.h"

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
	EnemyClear();
}

void ChangeScene(void)
{
	if (!ChangeSceneActive) return;
	FadeOut = true;
	if (fadeALPHA == 256) //ÉVÅ[ÉìÇ™ïœÇÌÇÈèuä‘
	{
		ObjectClear();
		GameScene = nextScene;
		FadeIn = true;
		ChangeSceneActive = false;
	}
}

