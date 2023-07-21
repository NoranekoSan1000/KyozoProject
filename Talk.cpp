#include "GameData.h"

bool TalkActive = false;
int PlayerTalk = 0;
int BossTalk = 0;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("ＭＳ ゴシック", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[50];
	int p; //0 <-Disable 1<-stand-by 2<-Enable
	int b;
};

TalkList talklist[4] = 
{ 
	{"そこのお前！とまれ！\0",0,0},
	{"お前、確か指名手配されていた女だな！\0",1,2},
	{"あれは私じゃないわ。別人よ。\0",2,1},
	{"\0",0,0}//終了
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