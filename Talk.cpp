#include "GameData.h"

bool TalkActive = false;
bool PlayerTalk = false;
bool BossTalk = false;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("�l�r �S�V�b�N", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[50];
	bool p;
	bool b;
};

TalkList talklist[4] = 
{ 
	{"����ɂ���\0",true,false},
	{"���悤�Ȃ�\0",false,true},
	{"�Ȃ�ł���\0",true,false},
	{"\0",false,false}//�I��
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