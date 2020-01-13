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


//SMW_ReserveItem lastItem;
unsigned itemPriceList[] = { 0, 1000, 2000, 10000, 3000 };

bool AttemptPurchaseItem(SMW_ReserveItem item) {
	if (GetPlayerScore() >= itemPriceList[item] && GetCurrentReserveItem() != item) {
		//SetPlayerScore(400);
		//printf(std::to_string(GetPlayerScore()).c_str());
		//printf("\n");
		SetPlayerScore(GetPlayerScore() - itemPriceList[item]);
		


		//lastItem = GetCurrentReserveItem();
		//itemPurchaseState = 1;

		SetCurrentReserveItem(item);
		return true;
	}
	return false;
}

void ResetItemPurchase() {
	//SetCurrentReserveItem(lastItem);

}