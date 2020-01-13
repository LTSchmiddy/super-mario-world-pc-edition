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

#define INPUTCONFIG_MENU_LABEL_1 TEXT("Game Controls - Player 1")
#define INPUTCONFIG_MENU_LABEL_2 TEXT("Game Controls - Player 2")
#define INPUTCONFIG_MENU_LABEL_3 TEXT("-- Not Used --")
#define INPUTCONFIG_MENU_LABEL_4 TEXT("Menu Controls")

void InputLabels_SetInputMenuLabels(HWND hDlg);
void InputLabels_SetInputLabels(HWND hDlg, int input);