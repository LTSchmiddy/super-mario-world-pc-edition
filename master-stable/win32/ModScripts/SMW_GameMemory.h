#pragma once

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


#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>


//#define SMW_GAMESTATE 0x7e0100
//#define SMW_RESERVEITEM 0x7e0dc2



enum SMW_MemAddr {
	A_GameState = 0x7e0100,
	A_OverworldMapState = 0x7E13D9,
	A_ReserveItem = 0x7E0DC2,
	A_PlayerFacing = 0x7e0076,
	A_2PlayerMode = 0x7E0DB2,
	A_CurrentLives = 0x7E0DBE,
	A_SaveMenu = 0x7e1b87,
	A_MarioScore = 0x7E0F34,
	A_FlightMode = 0x7E1407
};


enum SMW_GameStates {
	V_Overworld = 0x0e,
	V_Level = 0x14
	// Add the others as needed...
};

enum SMW_OverworldMapStates {
	V_OnLevelTile = 0x03
};

enum SMW_ReserveItem {
	V_NoItem = 0x00,
	V_Mushroom = 0x01,
	V_FireFlower = 0x02,
	V_InvincibilityStar = 0x03,
	V_CapeFeather = 0x04
};

enum SMW_SaveMenuTrigger {
	V_InitSaveMenu = 0x05
};



enum SMW_PlayerFacing {
	V_Left = 0x00,
	V_Right = 0x01
};