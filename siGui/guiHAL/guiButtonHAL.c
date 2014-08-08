#include "guiButtonHAL.h"
#include "guiCore.h"

void Buttons_onKeyPressed(int key)
{
	switch (key) {
	case KEY_ENTER:
		//guiCore_FocusNext(1);
		break;
	case KEY_ESC:
		guiCore_FocusFirst();
		break;
	case KEY_LEFT:
		guiCore_FocusNext(-1);
		break;
	case KEY_RIGHT:
		guiCore_FocusNext(1);
		break;
	default:
		break;
	}
}