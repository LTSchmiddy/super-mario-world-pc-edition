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
#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "ModScripts\NewGamePlus.h"
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




// Constant Variables: ===============================================


string TrueString = "true";
string FalseString = "false";

//File Config:

//bool UseNewControls = false;
//bool ReAccessCastles = false;
//bool UseScoreToBuyItems = false;
//bool SelectOpensSaveMenu = false;

const char * DefaultConfigPathBase = "Default_GameConfig.txt";


//const string UseNewControlsStr = "UseNewControls";
//const string ReAccessCastlesStr = "ReAccessCastles";
//const string UseScoreToBuyItemsStr = "UseScoreToBuyItems";

bool GameConfig[NUMOFCFGS];
string GameConfigNames[NUMOFCFGS] = { "UseNewControls" , "ReAccessCastles" , "SelectOpensSaveMenu", "UseScoreToBuyItems", "TurnWhileFlying", "HealthMode" };




//Function Declairations: ================================================================================================
void ModGameplayControl(uint32, bool);
void LoadSMGameConfig();


// Runtime Variables:====================================================


// Function Methods: ================================================================================================
//Tools:


//Utilities: **********************************************************************


//External Calls:
void HideMenu() {
	SetMenu(GUI.hWnd, NULL);
}

// Main Loop Function:

void SMOnLoadRom() {
	LoadSMGameConfig();
}

void ReadGameConfigFromFile(const char * path) {
	std::ifstream infile;

	infile.open(path, ios::in);

	if (infile.is_open()) {
		printf("Opened GameConfig File '");
		printf(path);
		printf("'\n");
	}
	else {

		printf("GameConfig File '");
		printf(path);
		printf("' not found. Continuing without...\n");

		return;
	}

	printf("Reading Config\n");
	std::string line;

	//while (infile >> line)
	while (std::getline(infile, line))
	{


		if (line.find("#") != std::string::npos) {
			continue;
		}

		for (int i = 0; i < NUMOFCFGS; i++) {
			if (line.find(GameConfigNames[i]) != std::string::npos) {
				std::getline(infile, line);
				if (line.find(TrueString) != std::string::npos) {
					GameConfig[i] = true;
					printf("Enabling ");
					printf(GameConfigNames[i].c_str());
					printf("\n");
					//printf("Enabling New Controls\n");
				}
				else if (line.find(FalseString) != std::string::npos) {
					GameConfig[i] = false;
					printf("Disabling ");
					printf(GameConfigNames[i].c_str());
					printf("\n");
				}
			}
		}

		//// Use New Controls:
		//if (line.find(UseNewControlsStr) != std::string::npos) {
		//	std::getline(infile, line);
		//	if (line.find(TrueString) != std::string::npos) {
		//		UseNewControls = true;
		//		printf("Enabling New Controls\n");
		//	}
		//	else if (line.find(FalseString) != std::string::npos) {
		//		UseNewControls = false;
		//		printf("Disabling New Controls\n");
		//	}
		//}

		//if (line.find(ReAccessCastlesStr) != std::string::npos) {
		//	std::getline(infile, line);
		//	if (line.find(TrueString) != std::string::npos) {
		//		ReAccessCastles = true;
		//		printf("Enabling Re-Access Castles\n");
		//	}
		//	else if (line.find(FalseString) != std::string::npos) {
		//		ReAccessCastles = false;
		//		printf("Disabling Re-Access Castles\n");
		//	}
		//}

		//if (line.find(UseScoreToBuyItemsStr) != std::string::npos) {
		//	std::getline(infile, line);
		//	if (line.find(TrueString) != std::string::npos) {
		//		UseScoreToBuyItems = true;
		//		printf("Enabling Use Score To Buy Items\n");
		//	}
		//	else if (line.find(FalseString) != std::string::npos) {
		//		UseScoreToBuyItems = false;
		//		printf("Disabling Use Score To Buy Items\n");
		//	}
		//}

	}


}

void LoadSMGameConfig() {

	const char * DefaultConfigPath = S9xGetFileInDirectory(DefaultConfigPathBase, HOME_DIR);
	printf("\nDefault GameConfig Path: ");
	//strcat(DefaultConfigPath, DefaultConfigPathBase);
	printf(DefaultConfigPath);
	printf("\n");

	ReadGameConfigFromFile(DefaultConfigPath);

	const char * ROMConfigPath = S9xGetFilename("_GameConfig.txt", PATCH_DIR);
	printf("ROM GameConfig Path: ");
	printf(ROMConfigPath);
	printf("\n");
	ReadGameConfigFromFile(ROMConfigPath);
}

//And this is where the extra controls are applied:
bool ModInputUpdate(uint32 id, bool pressed) {

	if (GameConfig[CFG_NEWCONTROLS]) {
		pressed = NewControlsInputUpdate(id, pressed);
	}

	return pressed;
}


void ModGameplayControl(uint32 id, bool pressed) {
	if (GameConfig[CFG_NEWCONTROLS]) {
		NewControlsGameplayInputUpdate(id, pressed);
	}
}



void SMMainLoop() {


}


void SMMainLoop_Late() {


}




void SMOnEndRom() {



}

void SMOnLoadState() {


}

