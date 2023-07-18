#include "GameData.h"

bool TalkActive = false;
bool PlayerTalk = false;
bool BossTalk = false;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("ＭＳ ゴシック", 50, 9, DX_FONTTYPE_ANTIALIASING);

void TalkProcess(void)
{
	switch (TalkStep)
	{
		case 0:
			DrawStringToHandle(315, 675, "Hello ワールド！", GetColor(255, 255, 255), Font);  
			PlayerTalk = true;
			BossTalk = false;
			break;
		case 1:
			DrawStringToHandle(315, 675, "Hello！", GetColor(255, 255, 255), Font);  
			PlayerTalk = false;
			BossTalk = true; 
			break;
		case 2:
			TalkActive = false;
		default: break;
	}
}