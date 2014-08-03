#include "guiCore.h"
#include "guiLcdHAL.h"
#include "guiGraphPrimitives.h"

void prv_graphPrimitivesTest();

void guiCore_Init()
{
    prv_graphPrimitivesTest();

}


void prv_graphPrimitivesTest()
{


    guiGraph_SetPenColor(CL_WHITE);
    guiGraph_SetAltPenColor(CL_RED);
    guiGraph_SetFillColor(CL_GREEN);
    guiGraph_SetLineStyle(line_style_solid);

    guiGraph_SetFont(&font_h10_bold);
    guiGraph_PrintString("Hello font", 34, 12);

    guiGraph_DrawPackedImage(checkbox_10x10_checked, 40, 40, 10, 10);
    guiGraph_DrawPackedImage(checkbox_10x10_empty, 40, 60, 10, 10);

    guiGraph_DrawPackedImage(checkbox_10x10_checked_no_frame, 40, 80, 10, 10);
    guiGraph_DrawPackedImage(checkbox_10x10_empty_no_frame, 40, 100, 10, 10);

    guiGraph_DrawPackedImage(checkbox_8x8_checked_no_frame, 60, 40, 8, 8);
    guiGraph_DrawPackedImage(checkbox_8x8_empty_no_frame, 60, 60, 8, 8);

    guiGraph_DrawPackedImage(checkbox_9x9_checked_no_frame, 60, 80, 9, 9);
    guiGraph_DrawPackedImage(checkbox_9x9_empty_no_frame, 60, 100, 9, 9);


}
