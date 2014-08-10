#include "guiButtonHAL.h"
#include "guiCore.h"
#include "guiEvent.h"
#include "guiKey.h"

void Buttons_onKeyPressed(int key)
{
	switch (key) {
	case KEY_ENTER:
		guiKey_ProcessKey(guiKey_Enter, guiPressType_Short);
		break;
	case KEY_ESC:
		guiKey_ProcessKey(guiKey_Esc, guiPressType_Short);
		break;
	case KEY_LEFT:
		guiKey_ProcessKey(guiKey_Left, guiPressType_Short);
		break;
	case KEY_RIGHT:
		guiKey_ProcessKey(guiKey_Right, guiPressType_Short);
		break;
	default:
		break;
	}
}
