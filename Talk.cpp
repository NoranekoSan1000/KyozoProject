#include "GameData.h"

bool TalkActive = false;
int PlayerTalk = 0;
int BossTalk = 0;

int TalkStep = 0;
string str = "";

int Font = CreateFontToHandle("�l�r �S�V�b�N", 50, 9, DX_FONTTYPE_ANTIALIASING);

struct TalkList
{
	char Conversation[50];
	int p; //0 <-Disable 1<-stand-by 2<-Enable
	int b;
};

TalkList talklist[4] = 
{ 
	{"�����̂��O�I�Ƃ܂�I\0",0,0},
	{"���O�A�m���w����z����Ă��������ȁI\0",1,2},
	{"����͎�����Ȃ���B�ʐl��B\0",2,1},
	{"\0",0,0}//�I��
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