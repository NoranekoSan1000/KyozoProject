#pragma once
enum SceneManager
{
	Title_Scene,
	DifficultyLvSelect_Scene,
	Stage1_Scene,
	Stage2_Scene,
	Stage3_Scene,
	Stage4_Scene,
	Stage5_Scene,
	MusicRoom_Scene,
	Setting_Scene,
};

extern bool FadeIn;
extern bool FadeOut;
extern int fadeALPHA;
extern bool ChangeSceneActive;
extern SceneManager nextScene;
extern SceneManager GameScene;

void ViewFadeWindow(void);
void ChangeScene(void);