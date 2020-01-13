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
#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "ModScripts\NewGamePlus.h"
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


extern SMW_ReserveItem lastItem;
extern unsigned itemPriceList[];

bool AttemptPurchaseItem(SMW_ReserveItem itemIndex);
void ResetItemPurchase();
