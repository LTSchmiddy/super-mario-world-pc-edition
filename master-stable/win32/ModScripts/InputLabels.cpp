#include "InputLabels.h"

#include "wsnes9x.h"
#include "wlanguage.h"
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

#include <iostream>
//#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
#include <ctype.h>

#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

#include <commctrl.h>
#include <io.h>
#include <time.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

// Local Methods:
void SetLabelsToDefaults(HWND hDlg) {
	SetDlgItemText(hDlg, IDC_LABEL_UP, INPUTCONFIG_LABEL_UP);
	SetDlgItemText(hDlg, IDC_LABEL_DOWN, INPUTCONFIG_LABEL_DOWN);
	SetDlgItemText(hDlg, IDC_LABEL_LEFT, INPUTCONFIG_LABEL_LEFT);
	SetDlgItemText(hDlg, IDC_LABEL_RIGHT, INPUTCONFIG_LABEL_RIGHT);
	SetDlgItemText(hDlg, IDC_LABEL_A, INPUTCONFIG_LABEL_A);
	SetDlgItemText(hDlg, IDC_LABEL_B, INPUTCONFIG_LABEL_B);
	SetDlgItemText(hDlg, IDC_LABEL_X, INPUTCONFIG_LABEL_X);
	SetDlgItemText(hDlg, IDC_LABEL_Y, INPUTCONFIG_LABEL_Y);
	SetDlgItemText(hDlg, IDC_LABEL_L, INPUTCONFIG_LABEL_L);
	SetDlgItemText(hDlg, IDC_LABEL_R, INPUTCONFIG_LABEL_R);
	SetDlgItemText(hDlg, IDC_LABEL_START, INPUTCONFIG_LABEL_START);
	SetDlgItemText(hDlg, IDC_LABEL_SELECT, INPUTCONFIG_LABEL_SELECT);
	SetDlgItemText(hDlg, IDC_LABEL_UPRIGHT, INPUTCONFIG_LABEL_UPRIGHT);
	SetDlgItemText(hDlg, IDC_LABEL_UPLEFT, INPUTCONFIG_LABEL_UPLEFT);
	SetDlgItemText(hDlg, IDC_LABEL_DOWNRIGHT, INPUTCONFIG_LABEL_DOWNRIGHT);
	SetDlgItemText(hDlg, IDC_LABEL_DOWNLEFT, INPUTCONFIG_LABEL_DOWNLEFT);
}

void SetLabelsToUnused(HWND hDlg) {
	SetDlgItemText(hDlg, IDC_LABEL_UP, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_DOWN, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_LEFT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_RIGHT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_A, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_B, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_X, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_Y, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_L, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_R, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_START, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_SELECT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_UPRIGHT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_UPLEFT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_DOWNRIGHT, INPUTCONFIG_LABEL_UNUSED);
	SetDlgItemText(hDlg, IDC_LABEL_DOWNLEFT, INPUTCONFIG_LABEL_UNUSED);
}


// Global Methods:
void InputLabels_SetInputMenuLabels(HWND hDlg) {
	TCHAR temp[256];
	for (int i = 1; i < 6; i++)
	{
		if (i == 1) {
			_stprintf(temp, INPUTCONFIG_MENU_LABEL_1);
		}
		else if (i == 2) {
			_stprintf(temp, INPUTCONFIG_MENU_LABEL_2);
		}
		else if (i == 3) {
			_stprintf(temp, INPUTCONFIG_MENU_LABEL_3);
		}
		else if (i == 4) {
			_stprintf(temp, INPUTCONFIG_MENU_LABEL_4);
		}
		else {
			//_stprintf(temp, INPUTCONFIG_JPCOMBO, i);
			break;
		}

		SendDlgItemMessage(hDlg, IDC_JPCOMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)temp);
	}

	//for(i=6;i<11;i++)
	//{
	//	_stprintf(temp,INPUTCONFIG_JPCOMBO INPUTCONFIG_LABEL_CONTROLLER_TURBO_PANEL_MOD,i-5);
	//	SendDlgItemMessage(hDlg,IDC_JPCOMBO,CB_ADDSTRING,0,(LPARAM)(LPCTSTR)temp);
	//}
}

void InputLabels_SetInputLabels(HWND hDlg, int input) {

	if (input == 3) {
		SetLabelsToUnused(hDlg);
	}
	if (input == 2) {
		SetLabelsToUnused(hDlg);

	}
	else if (input == 0) {
		SetDlgItemText(hDlg, IDC_LABEL_UP, TEXT("Move Up"));
		SetDlgItemText(hDlg, IDC_LABEL_DOWN, TEXT("Move Down"));
		SetDlgItemText(hDlg, IDC_LABEL_LEFT, TEXT("Move Left"));
		SetDlgItemText(hDlg, IDC_LABEL_RIGHT, TEXT("Move Right"));
		SetDlgItemText(hDlg, IDC_LABEL_A, TEXT("Spin Jump"));
		SetDlgItemText(hDlg, IDC_LABEL_B, TEXT("Jump"));
		SetDlgItemText(hDlg, IDC_LABEL_X, TEXT("Run/Grab"));
		SetDlgItemText(hDlg, IDC_LABEL_Y, TEXT("Run/Grab"));
		SetDlgItemText(hDlg, IDC_LABEL_L, TEXT("Look Left"));
		SetDlgItemText(hDlg, IDC_LABEL_R, TEXT("Look Right"));
		SetDlgItemText(hDlg, IDC_LABEL_START, TEXT("Pause"));
		SetDlgItemText(hDlg, IDC_LABEL_SELECT, TEXT("Select"));
		SetDlgItemText(hDlg, IDC_LABEL_UPRIGHT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_UPLEFT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_DOWNRIGHT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_DOWNLEFT, INPUTCONFIG_LABEL_UNUSED);
	}

	else if (input == 1) {
		SetDlgItemText(hDlg, IDC_LABEL_UP, TEXT("Move Up"));
		SetDlgItemText(hDlg, IDC_LABEL_DOWN, TEXT("Move Down"));
		SetDlgItemText(hDlg, IDC_LABEL_LEFT, TEXT("Move Left"));
		SetDlgItemText(hDlg, IDC_LABEL_RIGHT, TEXT("Move Right"));
		SetDlgItemText(hDlg, IDC_LABEL_A, TEXT("Spin Jump"));
		SetDlgItemText(hDlg, IDC_LABEL_B, TEXT("Jump"));
		SetDlgItemText(hDlg, IDC_LABEL_X, TEXT("Run/Grab"));
		SetDlgItemText(hDlg, IDC_LABEL_Y, TEXT("Run/Grab"));
		SetDlgItemText(hDlg, IDC_LABEL_L, TEXT("L"));
		SetDlgItemText(hDlg, IDC_LABEL_R, TEXT("R"));
		SetDlgItemText(hDlg, IDC_LABEL_START, TEXT("Pause"));
		SetDlgItemText(hDlg, IDC_LABEL_SELECT, TEXT("Select"));
		SetDlgItemText(hDlg, IDC_LABEL_UPRIGHT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_UPLEFT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_DOWNRIGHT, INPUTCONFIG_LABEL_UNUSED);
		SetDlgItemText(hDlg, IDC_LABEL_DOWNLEFT, INPUTCONFIG_LABEL_UNUSED);
	}
	else {
		SetLabelsToDefaults(hDlg);
	}
}


