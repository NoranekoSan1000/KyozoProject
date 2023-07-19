#include "GameData.h"

bool TalkActive = false;
bool PlayerTalk = false;
bool BossTalk = false;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("ＭＳ ゴシック", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[50];
	bool p;
	bool b;
};

TalkList talklist[4] = 
{ 
	{"こんにちは\0",true,false},
	{"さようなら\0",false,true},
	{"なんですか\0",true,false},
	{"\0",false,false}//終了
};

void TalkProcess(void)
{
	int x = 115;
	int y = 630;
	if(talklist[TalkStep].Conversation[0] == '\0') TalkActive = false;

	DrawFormatString(x, y, GetColor(255, 255, 255), "%s", talklist[TalkStep].Conversation);
	PlayerTalk = talklist[TalkStep].p;
	BossTalk = talklist[TalkStep].b;
	
}