#include "GameData.h"

bool TalkActive = false;
bool PlayerTalk = false;
bool BossTalk = false;

int TalkStep = 0;
string str = "";

void TalkProcess(void)
{
	switch (TalkStep)
	{
		case 0: str = "‚â‚ "; break;
		case 1: str = "12345"; break;
		default: break;
	}
}