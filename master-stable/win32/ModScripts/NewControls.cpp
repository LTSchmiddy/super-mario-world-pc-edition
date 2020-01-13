#include "ModScripts\Utilities.h"
#include "ModScripts\NewControls.h"
#include "SMMods.h"

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


//New Controls:

const uint32 Menu_Up = 0x81100808;
const uint32 Menu_Down = 0x81100809;
const uint32 Menu_Left = 0x8110080a;
const uint32 Menu_Right = 0x8110080b;
const uint32 Menu_A = 0x81100801;
const uint32 Menu_B = 0x81100802;
const uint32 Menu_Y = 0x81100803;

const uint32 Control_Select = 0x81100106;
const uint32 Control_Up = 0x81100108;
const uint32 Control_Down = 0x81100109;
const uint32 Control_Left = 0x8110010a;
const uint32 Control_Right = 0x8110010b;
const uint32 Control_X = 0x81100100;
const uint32 Control_A = 0x81100101;
const uint32 Control_B = 0x81100102;
const uint32 Control_Y = 0x81100103;
const uint32 Control_L = 0x81100104;
const uint32 Control_R = 0x81100105;


const uint32 BuyMushroom = 0x81100400; // X
const uint32 BuyFlower = 0x81100401; // A
const uint32 BuyStar = 0x81100402; // B
const uint32 BuyFeather = 0x81100403; // Y

// Quick Buttons:



// Addresses:


// Active Variables:====================================================

bool MenuPressed_Up = false;
bool MenuPressed_Down = false;
bool MenuPressed_Left = false;
bool MenuPressed_Right = false;
bool MenuPressed_A = false;
bool MenuPressed_B = false;

bool reaccessCastlesPressed = false;

unsigned itemPurchaseState = 0;


bool lastBuyMushroomDown = false;
bool lastBuyFlowerDown = false;
bool lastBuyStarDown = false;
bool lastBuyFeatherDown = false;

bool flightTurnDown = false;


bool GetUseMenuControls() {
	return (AlexGetByteFree(A_GameState) != SMW_GameStates::V_Level);
}



bool SetMenuControls(bool pressedIn) {

	if (GetUseMenuControls()) {
		return pressedIn;
	}

	return false;

}

bool NewControlsInputUpdate(uint32 id, bool pressed) {

	// Checking to see if the menu controls are being pressed:
	if (id == Menu_Up) {
		//printf("\nPressing Up\n");
		MenuPressed_Up = SetMenuControls(pressed);
	}

	else if (id == Menu_Down) {
		MenuPressed_Down = SetMenuControls(pressed);
	}

	else if (id == Menu_Left) {
		MenuPressed_Left = SetMenuControls(pressed);
	}

	else if (id == Menu_Right) {
		MenuPressed_Right = SetMenuControls(pressed);
	}

	else if (id == Menu_A) {
		MenuPressed_A = SetMenuControls(pressed);
	}

	else if (id == Menu_B) {
		MenuPressed_B = SetMenuControls(pressed);
	}


	
	// Spoofing the Menu Controls if necessary:
	if (id == Control_Up && MenuPressed_Up) {
		pressed = true;
	}

	if (id == Control_Down && MenuPressed_Down) {
		pressed = true;
	}

	if (id == Control_Left && MenuPressed_Left) {
		pressed = true;
	}

	if (id == Control_Right && MenuPressed_Right) {
		pressed = true;
	}

	if (id == Control_A && MenuPressed_A) {
		pressed = true;
	}

	if (id == Control_B && MenuPressed_B) {
		pressed = true;
	}
	

	// There's a secret method to re-enter castles after they've been beaten.
	// Simply select the castle on the map and press L + R instead of A.
	// If the A button pressed L + R on the map screen, we can spoof the castles being  re-selectable.
	if (GameConfig[CFG_REACCESSCASTLES] && InOverworldMenu()) {
		if (id == Control_A) {
			reaccessCastlesPressed = pressed;
		}

		if (reaccessCastlesPressed) {
			if (id == Control_L || id == Control_R) {
				pressed = true;
			}
		}
	}

	//if (GameConfig[CFG_USESCORETOBUYITEMS]) {
	//	if (itemPurchaseState >= 40 && itemPurchaseState <= 75) {
	//		if (id == Control_Select) {
	//			pressed = true;
	//			printf("Should Have Dropped Purchased Item...");

	//		}
	//	} else if (itemPurchaseState > 100000) {
	//		ResetItemPurchase();
	//		itemPurchaseState = 0;
	//	}

	//	if (itemPurchaseState > 0) {
	//		itemPurchaseState++;
	//	}
	//}



	return pressed;
}


void NewControlsGameplayInputUpdate(uint32 id, bool pressed) {
	
	// Handling Opening the Save Menu when Select is pressed on the map screen:
	if (GameConfig[CFG_SELECTOPENSSAVEMENU]) {
		if (InOverworldMenu()) {

			if ((id == Control_Select || id == Menu_Y) && pressed && AlexGetByteFree(A_SaveMenu) < SMW_SaveMenuTrigger::V_InitSaveMenu && AlexGetByteFree(A_OverworldMapState) == SMW_OverworldMapStates::V_OnLevelTile) {
				AlexSetByteFree(0x05, A_SaveMenu);
				printf("Trying to load save menu...");

			}
		}
	}


	//Handling Score Buys Items
	if (GameConfig[CFG_USESCORETOBUYITEMS] && InLevel()) {
		if (id == BuyMushroom) {
			if (pressed) {

			}

			if (pressed && !lastBuyMushroomDown) {
				printf("Buying Mushroom\n");
				AttemptPurchaseItem(SMW_ReserveItem::V_Mushroom);
				
			}
			lastBuyMushroomDown = pressed;
		}

		if (id == BuyFlower) {

			if (pressed && !lastBuyFlowerDown) {
				printf("Buying Flower\n");
				AttemptPurchaseItem(SMW_ReserveItem::V_FireFlower);
				
			}
			lastBuyFlowerDown = pressed;
		}

		if (id == BuyStar) {
			if (pressed && !lastBuyStarDown) {
				printf("Buying Star\n");
				AttemptPurchaseItem(SMW_ReserveItem::V_InvincibilityStar);

			}
			lastBuyStarDown = pressed;
		}

		if (id == BuyFeather) {
			if (pressed && !lastBuyFeatherDown) {
				printf("Buying Feather\n");
				AttemptPurchaseItem(SMW_ReserveItem::V_CapeFeather);
				
			}
			lastBuyFeatherDown = pressed;
		}
	}

	if (GameConfig[CFG_TURNWHILEFLYING]) {
		if (id == Control_B) {
			if (AlexGetByteFree(SMW_MemAddr::A_FlightMode) != 0x00 && pressed && !flightTurnDown) {

				if (AlexGetByteFree(SMW_MemAddr::A_PlayerFacing) != 0x00) {
					AlexSetByteFree(0x00, SMW_MemAddr::A_PlayerFacing);

				}
				else {
					AlexSetByteFree(0x01, SMW_MemAddr::A_PlayerFacing);
				}
			}

			flightTurnDown = pressed;
		}
	}

	
}

void Input_OnUpdate() {

	

}
