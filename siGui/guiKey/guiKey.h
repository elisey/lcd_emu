#ifndef GUI_KEY_H_
#define GUI_KEY_H_

typedef enum	{
	guiPressType_Short	= 1,
	guiPressType_Long	= 2,
} guiPressType_t;

typedef enum	{
	guiKey_Enter	= 0b0001,
	guiKey_Esc		= 0b0010,
	guiKey_Left		= 0b0100,
	guiKey_Right	= 0b1000
} guiKey_t;

void guiKey_ProcessKey(guiKey_t key, guiPressType_t pressType);

#endif
