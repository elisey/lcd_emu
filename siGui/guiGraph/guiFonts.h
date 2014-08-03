#ifndef __GUI_FONTS_H_
#define __GUI_FONTS_H_

#include <stdint.h>

/*
    A font may have all chars present, or only some subset of chars.
    If a font has contiguous set of chars, starting with some char code,
    it is indicated by setting charTable to 0 and defining firstCharCode value.
    Field charCount tells how many chars the font has.
    Accessing some char with char code c in this case is trivial and looks like this:
        c -= font.firstCharCode;
        char_data = font.data[c * font.bytesPerChar];
    If a font has non-contiguous set of chars, their char codes are specified in codeTable,
    and offset relative to font.data is specified in offsetTable.

    A font may be monospaced or variable-spaced.
    If a font is monospaced, widthTable must be set to 0. All chars will have the same width = font.width.
    If font is variable-spaced, widthTable is used - it contains width for every char.

    If font has non-contiguous set of chars, or font is variable-spaced, font processing routines need to know,
    where particular char image is located. This information provides offsetTable.

    So, a font can be one of the following:
        - monospaced, char subset is contiguous:
            codeTable:      -
            widthTable:     -
            offsetTable:    -
        - monospaced, char subset is non-contiguous:
            codeTable:      present
            widthTable:     -
            offsetTable:    present
        - variable-spaced, char subset is contiguous:
            codeTable:      -
            widthTable:     present
            offsetTable:    present
        - variable-spaced, char subset is non-contiguous:
            codeTable:      present
            widthTable:     present
            offsetTable:    present

        Font MUST have valid offsetTable when codeTable or widthTable are used.
*/


//---------------------------------------------//
// Fonts typedefs

typedef struct 
{
    uint8_t height;                     // font chars height
    uint8_t width;                      // actual for monospaced, ignored for variable-width fonts
    uint8_t charCount;                  // Total number of chars in the font
    uint8_t spacing;                    // Additional space between chars
    uint8_t bytesPerChar;               // Actual for monospaced, ignored for variable-length fonts
    uint8_t firstCharCode;              // Used if there is no charTable - specifies first avaliable char code in the font.
    const uint8_t *codeTable;           // Used if not all symbols are prensent in the font. Otherwise must be 0.
    const uint8_t *widthTable;          // Used if font is not monospaced. Otherwise must be 0.
    const uint16_t *offsetTable;        // Used with codeTable or widthTable
    const uint8_t *data;                // Font data - contiguous byte array
} tFont;


extern const tFont font_h12;
extern const tFont font_h32;
extern const tFont font_h10;
extern const tFont font_h10_bold;
extern const tFont font_6x8_mono;



#endif
