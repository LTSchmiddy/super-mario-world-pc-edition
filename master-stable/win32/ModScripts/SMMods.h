//#pragma once


//#include <map>
//#include <set>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <assert.h>
//#include <ctype.h>


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
#include "ModScripts\PurchaseItems.h"

#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

#define NUMOFCFGS 6

#define CFG_NEWCONTROLS 0
#define CFG_REACCESSCASTLES 1
#define CFG_SELECTOPENSSAVEMENU 2
#define CFG_USESCORETOBUYITEMS 3
#define CFG_TURNWHILEFLYING 4
#define CFG_HEALTHMODE 5

//Config Variables:

//extern bool UseNewControls;
extern bool GameConfig[];


//extern bool SaveStationsHeal;
//extern bool XraySMRedesignMode;
//extern bool AllowChargeBeamToggling;
//extern bool QuitOnExit;


//Methods:


void HideMenu(void);
void SMOnLoadState(void);


void SMOnLoadRom(void);

bool ModInputUpdate(uint32 id, bool pressed);

void ModGameplayControl(uint32 id, bool pressed);


void SMMainLoop(void);


void SMMainLoop_Late(void);

void SMOnEndRom(void);