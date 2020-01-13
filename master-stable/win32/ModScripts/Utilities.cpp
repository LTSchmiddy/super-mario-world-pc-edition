#include "ModScripts\Utilities.h"

#include "SMMods.h"
#include "wsnes9x.h"
#include "win32_sound.h"
#include "win32_display.h"
#include "CCGShader.h"
#include "../shaders/glsl.h"
#include "CShaderParamDlg.h"
#include "../snes9x.h"
#include "../memmap.h"
#include "../cpuexec.h"
#include "../display.h"
#include "../cheats.h"
#include "../controls.h"
#include "../conffile.h"
#include "../statemanager.h"
#include "InputCustom.h"
#include "ModScripts\SMW_GameMemory.h"

#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

using namespace std;

#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

#include <commctrl.h>
#include <io.h>
#include <time.h>
#include <direct.h>

//#include <direct.h>
#include <stdlib.h>
#include <stdio.h>


// Game States Managements:
bool InOverworldMenu() {
	return (AlexGetByteFree(A_GameState) == SMW_GameStates::V_Overworld);
}

bool InLevel() {
	return (AlexGetByteFree(A_GameState) == SMW_GameStates::V_Level);
}

// Player Score:
unsigned GetPlayerScore() {
	return AlexGetMultiByteFree(A_MarioScore, 3);
}

void SetPlayerScore(unsigned val) {
	return AlexSetMultiByteFree(val, A_MarioScore, 3);
}

// Reserve Item:
SMW_ReserveItem GetCurrentReserveItem() {
	if (AlexGetByteFree(SMW_MemAddr::A_ReserveItem) > 0x04) {
		return V_NoItem;
	}

	return (SMW_ReserveItem)AlexGetByteFree(SMW_MemAddr::A_ReserveItem);
}

void SetCurrentReserveItem(SMW_ReserveItem item) {
	AlexSetByteFree(item, SMW_MemAddr::A_ReserveItem);
}

SMW_PlayerFacing GetPlayerFacing() {
	return (SMW_PlayerFacing)AlexGetByteFree(SMW_MemAddr::A_PlayerFacing);
}

void SetPlayerFacing(SMW_PlayerFacing direction) {
	AlexSetByteFree(direction, SMW_MemAddr::A_PlayerFacing);
}