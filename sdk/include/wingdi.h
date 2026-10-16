/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name: wingdi.h

--*/
#ifndef _WINGDI_H_
#define _WINGDI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <windef.h>


/**
 * This structure specifies the color and usage of a logical palette entry. A logical palette is
 * defined by a LOGPALETTE structure.
 *
 * Window CE ignores the peFlags member. It should be initialized to 0.
 */
typedef struct tagPALETTEENTRY {
    /**
     * Specifies a red intensity value for the palette entry.
     */
    BYTE        peRed;
    /**
     * Specifies a green intensity value for the palette entry.
     */
    BYTE        peGreen;
    /**
     * Specifies a blue intensity value for the palette entry.
     */
    BYTE        peBlue;
    /**
     * Specifies how the palette entry is to be used. The peFlags member may be set to NULL or one of
     * the following values: Value Description PC_EXPLICIT Specifies that the low-order word of the
     * logical palette entry designates a hardware palette index. This flag allows the application to
     * show the contents of the display device palette. PC_NOCOLLAPSE Specifies that the color be placed
     * in an unused entry in the system palette instead of being matched to an existing color in the
     * system palette. If there are no unused entries in the system palette, the color is matched
     * normally. Once this color is in the system palette, colors in other logical palettes can be
     * matched to this color. PC_RESERVED Specifies that the logical palette entry be used for palette
     * animation. This flag prevents other windows from matching colors to the palette entry since the
     * color frequently changes. If an unused system-palette entry is available, the color is placed in
     * that entry. Otherwise, the color is not available for animation.
     */
    BYTE        peFlags;
} PALETTEENTRY, *PPALETTEENTRY, FAR *LPPALETTEENTRY;

/* Logical Palette */
/**
 * This structure defines a logical color palette.
 *
 * The colors in the palette-entry table should appear in order of importance because entries
 * earlier in the logical palette are most likely to be placed in the system palette.
 */
typedef struct tagLOGPALETTE {
    /**
     * Specifies the version number of the system.
     */
    WORD        palVersion;
    /**
     * Specifies the number of entries in the logical color palette.
     */
    WORD        palNumEntries;
    /**
     * Specifies an array of PALETTEENTRY structures that define the color and usage of each entry in
     * the logical palette.
     */
    PALETTEENTRY        palPalEntry[1];
} LOGPALETTE, *PLOGPALETTE, NEAR *NPLOGPALETTE, FAR *LPLOGPALETTE;


#define TRUETYPE_FONTTYPE       0x0004  
#define LF_FACESIZE				32

/**
 * This structure defines the attributes of a font.
 *
 * Windows CE version 1.0 does not support the following values for lfClipPrecision:
 *
 * CLIP_MASK
 *
 * CLIP_EMBEDDED
 *
 * CLIP_LH_ANGLES
 *
 * CLIP_TT_ALWAYS
 *
 * Windows CE version 1.0 does not support the PROOF_QUALITY value for the lfQuality member.
 *
 * Windows CE version 2.0 ignores the lfClipPrecision and lfQuality members with one important
 * exception. If the raster font engine is installed, a IfClipPrecision value of
 * CLIP_CHARACTER_PRECIS will cause functions that create and select fonts to fail.
 */
typedef struct tagLOGFONTA
{
    /**
     * Specifies the height, in logical units, of the font's character cell or character. The character
     * height value (also known as the em height) is the character cell height value minus the
     * internal-leading value. The font mapper interprets the value specified in lfHeight in the
     * following manner: Value Description > 0 The font mapper transforms this value into device units
     * and matches it against the cell height of the available fonts. 0 The font mapper uses a default
     * height value when it searches for a match. < 0 The font mapper transforms this value into device
     * units and matches its absolute value against the character height of the available fonts.
     *
     * For all height comparisons, the font mapper looks for the largest font that does not exceed the
     * requested size.
     *
     * This mapping occurs when the font is used for the first time.
     *
     * For the MM_TEXT mapping mode, you can use the following formula to specify a height for a font
     * with a given point size:
     *
     *     lfHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
     */
    LONG      lfHeight;
    /**
     * Specifies the average width, in logical units, of characters in the font. If lfWidth is zero, the
     * aspect ratio of the device is matched against the digitization aspect ratio of the available
     * fonts to find the closest match, determined by the absolute value of the difference.
     */
    LONG      lfWidth;
    /**
     * Specifies the angle, in tenths of degrees, between the escapement vector and the x-axis of the
     * device. The escapement vector is parallel to the base line of a row of text.
     *
     * Windows NT: When the graphics mode is set to GM_ADVANCED, you can specify the escapement angle of
     * the string independently of the orientation angle of the string's characters.
     *
     * When the graphics mode is set to GM_COMPATIBLE, lfEscapement specifies both the escapement and
     * orientation. You should set lfEscapement and lfOrientation to the same value.
     *
     * Windows 95: The lfEscapement member specifies both the escapement and orientation. You should set
     * lfEscapement and lfOrientation to the same value.
     */
    LONG      lfEscapement;
    /**
     * Specifies the angle, in tenths of degrees, between each character's base line and the x-axis of
     * the device.
     */
    LONG      lfOrientation;
    /**
     * Specifies the weight of the font in the range 0 through 1000. For example, 400 is normal and 700
     * is bold. If this value is zero, a default weight is used.
     *
     * The following values are defined: Value Weight FW_DONTCARE 0 FW_THIN 100 FW_EXTRALIGHT 200
     * FW_ULTRALIGHT 200 FW_LIGHT 300 FW_NORMAL 400 FW_REGULAR 400 FW_MEDIUM 500 FW_SEMIBOLD 600
     * FW_DEMIBOLD 600 FW_BOLD 700 FW_EXTRABOLD 800 FW_ULTRABOLD 800 FW_HEAVY 900 FW_BLACK 900
     */
    LONG      lfWeight;
    /**
     * Specifies an italic font if set to TRUE.
     */
    BYTE      lfItalic;
    /**
     * Specifies an underlined font if set to TRUE.
     */
    BYTE      lfUnderline;
    /**
     * Specifies a strikeout font if set to TRUE.
     */
    BYTE      lfStrikeOut;
    /**
     * Specifies the character set. The following values are predefined: ANSI_CHARSET BALTIC_CHARSET
     * CHINESEBIG5_CHARSET DEFAULT_CHARSET EASTEUROPE_CHARSET GB2312_CHARSET GREEK_CHARSET
     * HANGUL_CHARSET MAC_CHARSET OEM_CHARSET RUSSIAN_CHARSET SHIFTJIS_CHARSET SYMBOL_CHARSET
     * TURKISH_CHARSET
     *
     * Korean Windows: JOHAB_CHARSET
     *
     * Middle-Eastern Windows: HEBREW_CHARSET ARABIC_CHARSET
     *
     * Thai Windows: THAI_CHARSET
     *
     * The OEM_CHARSET value specifies a character set that is operating-system dependent.
     *
     * You can use the DEFAULT_CHARSET value to allow the name and size of a font to fully describe the
     * logical font. If the specified font name does not exist, a font from any character set can be
     * substituted for the specified font, so you should use DEFAULT_CHARSET sparingly to avoid
     * unexpected results.
     *
     * Fonts with other character sets may exist in the operating system. If an application uses a font
     * with an unknown character set, it should not attempt to translate or interpret strings that are
     * rendered with that font.
     *
     * This member is important in the font mapping process. To ensure consistent results, specify a
     * specific character set. If you specify a typeface name in the lfFaceName member, make sure that
     * the lfCharSet value matches the character set of the typeface specified in lfFaceName.
     */
    BYTE      lfCharSet;
    /**
     * Specifies the output precision. The output precision defines how closely the output must match
     * the requested font's height, width, character orientation, escapement, pitch, and font type. It
     * can be one of the following values: Value Description OUT_CHARACTER_PRECIS Not used.
     * OUT_DEFAULT_PRECIS Specifies the default font mapper behavior. OUT_DEVICE_PRECIS Instructs the
     * font mapper to choose a Device font when the system contains multiple fonts with the same name.
     * OUT_OUTLINE_PRECIS Windows NT: This value instructs the font mapper to choose from TrueType and
     * other outline-based fonts. OUT_RASTER_PRECIS Instructs the font mapper to choose a raster font
     * when the system contains multiple fonts with the same name. OUT_STRING_PRECIS This value is not
     * used by the font mapper, but it is returned when raster fonts are enumerated. OUT_STROKE_PRECIS
     * Windows NT: This value is not used by the font mapper, but it is returned when TrueType, other
     * outline-based fonts, and vector fonts are enumerated. Windows 95: This value is used to map
     * vector fonts, and is returned when TrueType or vector fonts are enumerated. OUT_TT_ONLY_PRECIS
     * Instructs the font mapper to choose from only TrueType fonts. If there are no TrueType fonts
     * installed in the system, the font mapper returns to default behavior. OUT_TT_PRECIS Instructs the
     * font mapper to choose a TrueType font when the system contains multiple fonts with the same name.
     *
     * Applications can use the OUT_DEVICE_PRECIS, OUT_RASTER_PRECIS, and OUT_TT_PRECIS values to
     * control how the font mapper chooses a font when the operating system contains more than one font
     * with a given name. For example, if an operating system contains a font named Symbol in raster and
     * TrueType form, specifying OUT_TT_PRECIS forces the font mapper to choose the TrueType version.
     * Specifying OUT_TT_ONLY_PRECIS forces the font mapper to choose a TrueType font, even if it must
     * substitute a TrueType font of another name.
     */
    BYTE      lfOutPrecision;
    /**
     * Specifies the clipping precision. The clipping precision defines how to clip characters that are
     * partially outside the clipping region. It can be one or more of the following values: Value
     * Description CLIP_DEFAULT_PRECIS Specifies default clipping behavior. CLIP_CHARACTER_PRECIS Not
     * used. CLIP_STROKE_PRECIS Not used by the font mapper, but is returned when raster, vector, or
     * TrueType fonts are enumerated. Windows NT: For compatibility, this value is always returned when
     * enumerating fonts. CLIP_MASK Not used. CLIP_EMBEDDED You must specify this flag to use an
     * embedded read-only font. CLIP_LH_ANGLES When this value is used, the rotation for all fonts
     * depends on whether the orientation of the coordinate system is left-handed or right-handed. If
     * not used, device fonts always rotate counterclockwise, but the rotation of other fonts is
     * dependent on the orientation of the coordinate system. For more information about the orientation
     * of coordinate systems, see the description of the nOrientation parameter CLIP_TT_ALWAYS Not used.
     */
    BYTE      lfClipPrecision;
    /**
     * Specifies the output quality. The output quality defines how carefully the graphics device
     * interface (GDI) must attempt to match the logical-font attributes to those of an actual physical
     * font. It can be one of the following values: Value Description DEFAULT_QUALITY Appearance of the
     * font does not matter. DRAFT_QUALITY Appearance of the font is less important than when
     * PROOF_QUALITY is used. For GDI raster fonts, scaling is enabled, which means that more font sizes
     * are available, but the quality may be lower. Bold, italic, underline, and strikeout fonts are
     * synthesized if necessary. PROOF_QUALITY Character quality of the font is more important than
     * exact matching of the logical-font attributes. For GDI raster fonts, scaling is disabled and the
     * font closest in size is chosen. Although the chosen font size may not be mapped exactly when
     * PROOF_QUALITY is used, the quality of the font is high and there is no distortion of appearance.
     * Bold, italic, underline, and strikeout fonts are synthesized if necessary.
     */
    BYTE      lfQuality;
    /**
     * Specifies the pitch and family of the font. The two low-order bits specify the pitch of the font
     * and can be one of the following values:
     *
     * DEFAULT_PITCH
     *
     * FIXED_PITCH
     *
     * VARIABLE_PITCH
     *
     * Bits 4 through 7 of the member specify the font family and can be one of the following values:
     *
     * FF_DECORATIVE
     *
     * FF_DONTCARE
     *
     * FF_MODERN
     *
     * FF_ROMAN
     *
     * FF_SCRIPT
     *
     * FF_SWISS
     *
     * The proper value can be obtained by using the Boolean OR operator to join one pitch constant with
     * one family constant.
     *
     * Font families describe the look of a font in a general way. They are intended for specifying
     * fonts when the exact typeface desired is not available. The values for font families are as
     * follows: Value Description FF_DECORATIVE Novelty fonts, for example, Old English. FF_DONTCARE
     * Don't care or don't know. FF_MODERN Fonts with constant stroke width (monospace), with or without
     * serifs. Monospace fonts are usually modern, for example, Pica, Elite, and CourierNew(R). FF_ROMAN
     * Fonts with variable stroke width (proportional) and with serifs, for example, MS(R) Serif.
     * FF_SCRIPT Fonts designed to look like handwriting, for example, Script and Cursive. FF_SWISS
     * Fonts with variable stroke width (proportional) and without serifs, for example, MS(R) Sans
     * Serif.
     */
    BYTE      lfPitchAndFamily;
    /**
     * Specifies a null-terminated string that specifies the typeface name of the font. The length of
     * this string must not exceed 32 characters, including the terminating null character. The
     * EnumFontFamilies function can be used to enumerate the typeface names of all currently available
     * fonts. If lfFaceName is an empty string, GDI uses the first font that matches the other specified
     * attributes.
     */
    CHAR      lfFaceName[LF_FACESIZE];
} LOGFONTA, *PLOGFONTA, NEAR *NPLOGFONTA, FAR *LPLOGFONTA;

/**
 * This structure defines the attributes of a font.
 *
 * Windows CE version 1.0 does not support the following values for lfClipPrecision:
 *
 * CLIP_MASK
 *
 * CLIP_EMBEDDED
 *
 * CLIP_LH_ANGLES
 *
 * CLIP_TT_ALWAYS
 *
 * Windows CE version 1.0 does not support the PROOF_QUALITY value for the lfQuality member.
 *
 * Windows CE version 2.0 ignores the lfClipPrecision and lfQuality members with one important
 * exception. If the raster font engine is installed, a IfClipPrecision value of
 * CLIP_CHARACTER_PRECIS will cause functions that create and select fonts to fail.
 */
typedef struct tagLOGFONTW
{
    /**
     * Specifies the height, in logical units, of the font's character cell or character. The character
     * height value (also known as the em height) is the character cell height value minus the
     * internal-leading value. The font mapper interprets the value specified in lfHeight in the
     * following manner: Value Description > 0 The font mapper transforms this value into device units
     * and matches it against the cell height of the available fonts. 0 The font mapper uses a default
     * height value when it searches for a match. < 0 The font mapper transforms this value into device
     * units and matches its absolute value against the character height of the available fonts.
     *
     * For all height comparisons, the font mapper looks for the largest font that does not exceed the
     * requested size.
     *
     * This mapping occurs when the font is used for the first time.
     *
     * For the MM_TEXT mapping mode, you can use the following formula to specify a height for a font
     * with a given point size:
     *
     *     lfHeight = -MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
     */
    LONG      lfHeight;
    /**
     * Specifies the average width, in logical units, of characters in the font. If lfWidth is zero, the
     * aspect ratio of the device is matched against the digitization aspect ratio of the available
     * fonts to find the closest match, determined by the absolute value of the difference.
     */
    LONG      lfWidth;
    /**
     * Specifies the angle, in tenths of degrees, between the escapement vector and the x-axis of the
     * device. The escapement vector is parallel to the base line of a row of text.
     *
     * Windows NT: When the graphics mode is set to GM_ADVANCED, you can specify the escapement angle of
     * the string independently of the orientation angle of the string's characters.
     *
     * When the graphics mode is set to GM_COMPATIBLE, lfEscapement specifies both the escapement and
     * orientation. You should set lfEscapement and lfOrientation to the same value.
     *
     * Windows 95: The lfEscapement member specifies both the escapement and orientation. You should set
     * lfEscapement and lfOrientation to the same value.
     */
    LONG      lfEscapement;
    /**
     * Specifies the angle, in tenths of degrees, between each character's base line and the x-axis of
     * the device.
     */
    LONG      lfOrientation;
    /**
     * Specifies the weight of the font in the range 0 through 1000. For example, 400 is normal and 700
     * is bold. If this value is zero, a default weight is used.
     *
     * The following values are defined: Value Weight FW_DONTCARE 0 FW_THIN 100 FW_EXTRALIGHT 200
     * FW_ULTRALIGHT 200 FW_LIGHT 300 FW_NORMAL 400 FW_REGULAR 400 FW_MEDIUM 500 FW_SEMIBOLD 600
     * FW_DEMIBOLD 600 FW_BOLD 700 FW_EXTRABOLD 800 FW_ULTRABOLD 800 FW_HEAVY 900 FW_BLACK 900
     */
    LONG      lfWeight;
    /**
     * Specifies an italic font if set to TRUE.
     */
    BYTE      lfItalic;
    /**
     * Specifies an underlined font if set to TRUE.
     */
    BYTE      lfUnderline;
    /**
     * Specifies a strikeout font if set to TRUE.
     */
    BYTE      lfStrikeOut;
    /**
     * Specifies the character set. The following values are predefined: ANSI_CHARSET BALTIC_CHARSET
     * CHINESEBIG5_CHARSET DEFAULT_CHARSET EASTEUROPE_CHARSET GB2312_CHARSET GREEK_CHARSET
     * HANGUL_CHARSET MAC_CHARSET OEM_CHARSET RUSSIAN_CHARSET SHIFTJIS_CHARSET SYMBOL_CHARSET
     * TURKISH_CHARSET
     *
     * Korean Windows: JOHAB_CHARSET
     *
     * Middle-Eastern Windows: HEBREW_CHARSET ARABIC_CHARSET
     *
     * Thai Windows: THAI_CHARSET
     *
     * The OEM_CHARSET value specifies a character set that is operating-system dependent.
     *
     * You can use the DEFAULT_CHARSET value to allow the name and size of a font to fully describe the
     * logical font. If the specified font name does not exist, a font from any character set can be
     * substituted for the specified font, so you should use DEFAULT_CHARSET sparingly to avoid
     * unexpected results.
     *
     * Fonts with other character sets may exist in the operating system. If an application uses a font
     * with an unknown character set, it should not attempt to translate or interpret strings that are
     * rendered with that font.
     *
     * This member is important in the font mapping process. To ensure consistent results, specify a
     * specific character set. If you specify a typeface name in the lfFaceName member, make sure that
     * the lfCharSet value matches the character set of the typeface specified in lfFaceName.
     */
    BYTE      lfCharSet;
    /**
     * Specifies the output precision. The output precision defines how closely the output must match
     * the requested font's height, width, character orientation, escapement, pitch, and font type. It
     * can be one of the following values: Value Description OUT_CHARACTER_PRECIS Not used.
     * OUT_DEFAULT_PRECIS Specifies the default font mapper behavior. OUT_DEVICE_PRECIS Instructs the
     * font mapper to choose a Device font when the system contains multiple fonts with the same name.
     * OUT_OUTLINE_PRECIS Windows NT: This value instructs the font mapper to choose from TrueType and
     * other outline-based fonts. OUT_RASTER_PRECIS Instructs the font mapper to choose a raster font
     * when the system contains multiple fonts with the same name. OUT_STRING_PRECIS This value is not
     * used by the font mapper, but it is returned when raster fonts are enumerated. OUT_STROKE_PRECIS
     * Windows NT: This value is not used by the font mapper, but it is returned when TrueType, other
     * outline-based fonts, and vector fonts are enumerated. Windows 95: This value is used to map
     * vector fonts, and is returned when TrueType or vector fonts are enumerated. OUT_TT_ONLY_PRECIS
     * Instructs the font mapper to choose from only TrueType fonts. If there are no TrueType fonts
     * installed in the system, the font mapper returns to default behavior. OUT_TT_PRECIS Instructs the
     * font mapper to choose a TrueType font when the system contains multiple fonts with the same name.
     *
     * Applications can use the OUT_DEVICE_PRECIS, OUT_RASTER_PRECIS, and OUT_TT_PRECIS values to
     * control how the font mapper chooses a font when the operating system contains more than one font
     * with a given name. For example, if an operating system contains a font named Symbol in raster and
     * TrueType form, specifying OUT_TT_PRECIS forces the font mapper to choose the TrueType version.
     * Specifying OUT_TT_ONLY_PRECIS forces the font mapper to choose a TrueType font, even if it must
     * substitute a TrueType font of another name.
     */
    BYTE      lfOutPrecision;
    /**
     * Specifies the clipping precision. The clipping precision defines how to clip characters that are
     * partially outside the clipping region. It can be one or more of the following values: Value
     * Description CLIP_DEFAULT_PRECIS Specifies default clipping behavior. CLIP_CHARACTER_PRECIS Not
     * used. CLIP_STROKE_PRECIS Not used by the font mapper, but is returned when raster, vector, or
     * TrueType fonts are enumerated. Windows NT: For compatibility, this value is always returned when
     * enumerating fonts. CLIP_MASK Not used. CLIP_EMBEDDED You must specify this flag to use an
     * embedded read-only font. CLIP_LH_ANGLES When this value is used, the rotation for all fonts
     * depends on whether the orientation of the coordinate system is left-handed or right-handed. If
     * not used, device fonts always rotate counterclockwise, but the rotation of other fonts is
     * dependent on the orientation of the coordinate system. For more information about the orientation
     * of coordinate systems, see the description of the nOrientation parameter CLIP_TT_ALWAYS Not used.
     */
    BYTE      lfClipPrecision;
    /**
     * Specifies the output quality. The output quality defines how carefully the graphics device
     * interface (GDI) must attempt to match the logical-font attributes to those of an actual physical
     * font. It can be one of the following values: Value Description DEFAULT_QUALITY Appearance of the
     * font does not matter. DRAFT_QUALITY Appearance of the font is less important than when
     * PROOF_QUALITY is used. For GDI raster fonts, scaling is enabled, which means that more font sizes
     * are available, but the quality may be lower. Bold, italic, underline, and strikeout fonts are
     * synthesized if necessary. PROOF_QUALITY Character quality of the font is more important than
     * exact matching of the logical-font attributes. For GDI raster fonts, scaling is disabled and the
     * font closest in size is chosen. Although the chosen font size may not be mapped exactly when
     * PROOF_QUALITY is used, the quality of the font is high and there is no distortion of appearance.
     * Bold, italic, underline, and strikeout fonts are synthesized if necessary.
     */
    BYTE      lfQuality;
    /**
     * Specifies the pitch and family of the font. The two low-order bits specify the pitch of the font
     * and can be one of the following values:
     *
     * DEFAULT_PITCH
     *
     * FIXED_PITCH
     *
     * VARIABLE_PITCH
     *
     * Bits 4 through 7 of the member specify the font family and can be one of the following values:
     *
     * FF_DECORATIVE
     *
     * FF_DONTCARE
     *
     * FF_MODERN
     *
     * FF_ROMAN
     *
     * FF_SCRIPT
     *
     * FF_SWISS
     *
     * The proper value can be obtained by using the Boolean OR operator to join one pitch constant with
     * one family constant.
     *
     * Font families describe the look of a font in a general way. They are intended for specifying
     * fonts when the exact typeface desired is not available. The values for font families are as
     * follows: Value Description FF_DECORATIVE Novelty fonts, for example, Old English. FF_DONTCARE
     * Don't care or don't know. FF_MODERN Fonts with constant stroke width (monospace), with or without
     * serifs. Monospace fonts are usually modern, for example, Pica, Elite, and CourierNew(R). FF_ROMAN
     * Fonts with variable stroke width (proportional) and with serifs, for example, MS(R) Serif.
     * FF_SCRIPT Fonts designed to look like handwriting, for example, Script and Cursive. FF_SWISS
     * Fonts with variable stroke width (proportional) and without serifs, for example, MS(R) Sans
     * Serif.
     */
    BYTE      lfPitchAndFamily;
    /**
     * Specifies a null-terminated string that specifies the typeface name of the font. The length of
     * this string must not exceed 32 characters, including the terminating null character. The
     * EnumFontFamilies function can be used to enumerate the typeface names of all currently available
     * fonts. If lfFaceName is an empty string, GDI uses the first font that matches the other specified
     * attributes.
     */
    WCHAR     lfFaceName[LF_FACESIZE];
} LOGFONTW, *PLOGFONTW, NEAR *NPLOGFONTW, FAR *LPLOGFONTW;


#define WINUSERAPI


// @CESYSGEN IF GWES_PGDI || GWES_MGBASE
#define WINGDIAPI

#define GDI_ERROR			(0xFFFFFFFFL)
#define ERROR               0

#define OBJ_PEN             1
#define OBJ_BRUSH           2
#define OBJ_DC              3
#define OBJ_PAL             5
#define OBJ_FONT            6
#define OBJ_BITMAP          7
#define OBJ_REGION          8
#define OBJ_MEMDC           10
#define OBJ_ENHMETADC       12
#define OBJ_ENHMETAFILE     13

#define MIN_OBJ_TYPE        OBJ_PEN
#define MAX_OBJ_TYPE        OBJ_ENHMETAFILE

#define CLR_INVALID			0xFFFFFFFF
#define BI_RGB				0

/* Parameters for GetStockObject */
#define WHITE_BRUSH         0
#define LTGRAY_BRUSH        1
#define GRAY_BRUSH          2
#define DKGRAY_BRUSH        3
#define BLACK_BRUSH         4
#define NULL_BRUSH          5
#define HOLLOW_BRUSH        NULL_BRUSH
#define WHITE_PEN           6
#define BLACK_PEN           7
#define NULL_PEN            8
#define SYSTEM_FONT         13
#define DEFAULT_PALETTE     15

/* Device Parameters for GetDeviceCaps() */
#define DRIVERVERSION 0     /* Device driver version                    */
#define TECHNOLOGY    2     /* Device classification                    */
#define HORZSIZE      4     /* Horizontal size in millimeters           */
#define VERTSIZE      6     /* Vertical size in millimeters             */
#define HORZRES       8     /* Horizontal width in pixels               */
#define VERTRES       10    /* Vertical height in pixels                */
#define BITSPIXEL     12    /* Number of bits per pixel                 */
#define PLANES        14    /* Number of planes                         */
#define NUMBRUSHES    16    /* Number of brushes the device has         */
#define NUMPENS       18    /* Number of pens the device has            */
#define NUMMARKERS    20    /* Number of markers the device has         */
#define NUMFONTS      22    /* Number of fonts the device has           */
#define NUMCOLORS     24    /* Number of colors the device supports     */
#define PDEVICESIZE   26    /* Size required for device descriptor      */
#define CURVECAPS     28    /* Curve capabilities                       */
#define LINECAPS      30    /* Line capabilities                        */
#define POLYGONALCAPS 32    /* Polygonal capabilities                   */
#define TEXTCAPS      34    /* Text capabilities                        */
#define CLIPCAPS      36    /* Clipping capabilities                    */
#define RASTERCAPS    38    /* Bitblt capabilities                      */
#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

// Printing related DeviceCaps.

#define PHYSICALWIDTH   110 /* Physical Width in device units           */
#define PHYSICALHEIGHT  111 /* Physical Height in device units          */
#define PHYSICALOFFSETX 112 /* Physical Printable Area x margin         */
#define PHYSICALOFFSETY 113 /* Physical Printable Area y margin         */


#ifndef NOGDICAPMASKS

/* Device Capability Masks: */

/* Device Technologies */
#define DT_PLOTTER          0   /* Vector plotter                   */
#define DT_RASDISPLAY       1   /* Raster display                   */
#define DT_RASPRINTER       2   /* Raster printer                   */
#define DT_RASCAMERA        3   /* Raster camera                    */
#define DT_CHARSTREAM       4   /* Character-stream, PLP            */
#define DT_DISPFILE         6   /* Display-file                     */

/* Curve Capabilities */
#define CC_NONE             0   /* Curves not supported             */
#define CC_CIRCLES          1   /* Can do circles                   */
#define CC_PIE              2   /* Can do pie wedges                */
#define CC_CHORD            4   /* Can do chord arcs                */
#define CC_ELLIPSES         8   /* Can do ellipese                  */
#define CC_WIDE             16  /* Can do wide lines                */
#define CC_STYLED           32  /* Can do styled lines              */
#define CC_WIDESTYLED       64  /* Can do wide styled lines         */
#define CC_INTERIORS        128 /* Can do interiors                 */
#define CC_ROUNDRECT        256 /*                                  */

/* Line Capabilities */
#define LC_NONE             0   /* Lines not supported              */
#define LC_POLYLINE         2   /* Can do polylines                 */
#define LC_MARKER           4   /* Can do markers                   */
#define LC_POLYMARKER       8   /* Can do polymarkers               */
#define LC_WIDE             16  /* Can do wide lines                */
#define LC_STYLED           32  /* Can do styled lines              */
#define LC_WIDESTYLED       64  /* Can do wide styled lines         */
#define LC_INTERIORS        128 /* Can do interiors                 */

/* Polygonal Capabilities */
#define PC_NONE             0   /* Polygonals not supported         */
#define PC_POLYGON          1   /* Can do polygons                  */
#define PC_RECTANGLE        2   /* Can do rectangles                */
#define PC_WINDPOLYGON      4   /* Can do winding polygons          */
#define PC_TRAPEZOID        4   /* Can do trapezoids                */
#define PC_SCANLINE         8   /* Can do scanlines                 */
#define PC_WIDE             16  /* Can do wide borders              */
#define PC_STYLED           32  /* Can do styled borders            */
#define PC_WIDESTYLED       64  /* Can do wide styled borders       */
#define PC_INTERIORS        128 /* Can do interiors                 */

/* Clipping Capabilities */
#define CP_NONE             0   /* No clipping of output            */
#define CP_RECTANGLE        1   /* Output clipped to rects          */
#define CP_REGION           2   /* obsolete                         */

/* Text Capabilities */
#define TC_OP_CHARACTER     0x00000001  /* Can do OutputPrecision   CHARACTER      */
#define TC_OP_STROKE        0x00000002  /* Can do OutputPrecision   STROKE         */
#define TC_CP_STROKE        0x00000004  /* Can do ClipPrecision     STROKE         */
#define TC_CR_90            0x00000008  /* Can do CharRotAbility    90             */
#define TC_CR_ANY           0x00000010  /* Can do CharRotAbility    ANY            */
#define TC_SF_X_YINDEP      0x00000020  /* Can do ScaleFreedom      X_YINDEPENDENT */
#define TC_SA_DOUBLE        0x00000040  /* Can do ScaleAbility      DOUBLE         */
#define TC_SA_INTEGER       0x00000080  /* Can do ScaleAbility      INTEGER        */
#define TC_SA_CONTIN        0x00000100  /* Can do ScaleAbility      CONTINUOUS     */
#define TC_EA_DOUBLE        0x00000200  /* Can do EmboldenAbility   DOUBLE         */
#define TC_IA_ABLE          0x00000400  /* Can do ItalisizeAbility  ABLE           */
#define TC_UA_ABLE          0x00000800  /* Can do UnderlineAbility  ABLE           */
#define TC_SO_ABLE          0x00001000  /* Can do StrikeOutAbility  ABLE           */
#define TC_RA_ABLE          0x00002000  /* Can do RasterFontAble    ABLE           */
#define TC_VA_ABLE          0x00004000  /* Can do VectorFontAble    ABLE           */
#define TC_RESERVED         0x00008000
#define TC_SCROLLBLT        0x00010000  /* Don't do text scroll with blt           */

#endif /* NOGDICAPMASKS */

/* Raster Capabilities */
#define RC_NONE
#define RC_BITBLT           1       /* Can do standard BLT.             */
#define RC_BANDING          2       /* Device requires banding support  */
#define RC_SCALING          4       /* Device requires scaling support  */
#define RC_BITMAP64         8       /* Device can support >64K bitmap   */
#define RC_GDI20_OUTPUT     0x0010      /* has 2.0 output calls         */
#define RC_GDI20_STATE      0x0020
#define RC_SAVEBITMAP       0x0040
#define RC_DI_BITMAP        0x0080      /* supports DIB to memory       */
#define RC_PALETTE          0x0100      /* supports a palette           */
#define RC_DIBTODEV         0x0200      /* supports DIBitsToDevice      */
#define RC_BIGFONT          0x0400      /* supports >64K fonts          */
#define RC_STRETCHBLT       0x0800      /* supports StretchBlt          */
#define RC_STRETCHDIB       0x2000      /* supports StretchDIBits       */
#define RC_OP_DX_OUTPUT     0x4000
#define RC_DEVBITS          0x8000

#define LOGPIXELSX    88    /* Logical pixels/inch in X                 */
#define LOGPIXELSY    90    /* Logical pixels/inch in Y                 */

#define SIZEPALETTE  104    /* Number of entries in physical palette    */
#define NUMRESERVED  106    /* Number of reserved entries in palette    */
#define COLORRES     108    /* Actual color resolution                  */

/* Device Capability Masks: */

/* Device Technologies */
#define DT_RASDISPLAY       1   /* Raster display                   */

#define RDH_RECTANGLES		1

#define TRANSPARENT         1
#define OPAQUE              2

/**
 * This macro selects a red, green, blue (RGB) color based on the specified color values and the
 * capabilities of the output device.
 *
 * @param cRed Specifies the intensity of the red color.
 * @param cGreen Specifies the intensity of the green color.
 * @param cBlue Specifies the intensity of the blue color.
 *
 * @return The return value is the resultant RGB color.
 *
 * The intensity for each argument is in the range 0 through 255. If all three intensities are zero,
 * the result is black. If all three intensities are 255, the result is white.
 *
 * For information about using color values in a color palette, see the description of the
 * PALETTERGB macro.
 *
 * The RGB macro is defined as follows:
 *
 *     #define RGB(r, g ,b)  ((DWORD) (((BYTE) (r) | \
 *         ((WORD) (g) << 8)) | \
 *         (((DWORD) (BYTE) (b)) << 16)))
 */
#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
/**
 * This macro accepts three values that represent the relative intensities of red, green, and blue
 * and returns a palette-relative red, green, blue (RGB) specifier consisting of 2 in the high-order
 * byte and an RGB value in the three low-order bytes (with a value representing the intensity of
 * red, green, or blue in each of the bytes). An application using a color palette can pass this
 * specifier, instead of an explicit RGB value, to functions that expect a color.
 *
 * @param bRed Specifies the intensity of the red color field.
 * @param bGreen Specifies the intensity of the green color field.
 * @param bBlue Specifies the intensity of the blue color field.
 *
 * @return The return value is a palette-relative RGB specifier. For output devices that support
 *   logical palettes, the system matches a palette-relative RGB value to the nearest color in the
 *   logical palette of the device context as though the application had specified an index to that
 *   palette entry. If an output device does not support a system palette, the system uses the
 *   palette-relative RGB as though it were a conventional RGB doubleword returned by the RGB macro.
 *
 * The PALETTERGB macro is defined as follows:
 *
 *     #define PALETTERGB(r, g, b)  (0x02000000 | RGB(r, g, b))
 */
#define PALETTERGB(r,g,b)   (0x02000000 | RGB(r,g,b))
/* The PALETTEINDEX macro has been removed.  Use RGB or PALETTEINDEX2BPP instead. */
#define PALETTEINDEX2BPP(i)  (((i)==0)?0x00000000:(((i)==1)?0x00808080:(((i)==2)?0x00C0C0C0:0x00FFFFFF)))

/**
 * This macro retrieves an intensity value for the red component of a 32-bit red, green, blue (RGB)
 * value.
 *
 * @param rgb Specifies an RGB color value.
 *
 * @return The return value is the intensity of the red component of the specified RGB color.
 *
 * The intensity value is in the range 0 through 255.
 *
 * The GetRValue macro is defined as follows:
 *
 *     #define GetRValue(rgb)   ((BYTE) (rgb))
 */
#define GetRValue(rgb)  ((BYTE)(rgb))
/**
 * This macro retrieves an intensity value for the green component of a 32-bit red, green, blue
 * (RGB) value.
 *
 * @param rgb Specifies an RGB color value.
 *
 * @return The return value is the intensity of the green component of the specified RGB color.
 *
 * The intensity value is in the range 0 through 255.
 *
 * The GetGValue macro is defined as follows:
 *
 *     #define GetGValue(rgb)   ((BYTE) (((WORD) (rgb)) >> 8))
 */
#define GetGValue(rgb)  ((BYTE)(((WORD)(rgb)) >> 8))
/**
 * This macro retrieves an intensity value for the blue component of a 32-bit red, green, blue (RGB)
 * value.
 *
 * @param rgb Specifies an RGB color value.
 *
 * @return The return value is the intensity of the blue component of the specified RGB color.
 *
 * The intensity value is in the range 0 through 255.
 *
 * The GetBValue macro is defined as follows:
 *
 *     #define GetBValue(rgb)   ((BYTE) ((rgb) >> 16))
 */
#define GetBValue(rgb)  ((BYTE)((rgb) >> 16))

typedef DWORD COLORREF;

/**
 * This structure describes a color consisting of relative intensities of red, green, and blue.
 *
 * Windows CE does not support the rgbReserved member. It should be initialized to zero.
 *
 * The bmiColors member of the BITMAPINFO structure consists of an array of RGBQUAD structures.
 */
typedef struct tagRGBQUAD {
        /**
         * Specifies the intensity of blue in the color.
         */
        BYTE    rgbBlue;
        /**
         * Specifies the intensity of green in the color.
         */
        BYTE    rgbGreen;
        /**
         * Specifies the intensity of red in the color.
         */
        BYTE    rgbRed;
        /**
         * Reserved; set to zero.
         */
        BYTE    rgbReserved;
} RGBQUAD, FAR *LPRGBQUAD;

/**
 * This structure defines the type, width, height, color format, and bit values of a bitmap.
 *
 * The bitmap formats currently used are monochrome and color. The monochrome bitmap uses a one-bit,
 * one-plane format. Each scan is a multiple of 32 bits.
 *
 * Scans are organized as follows for a monochrome bitmap of height n:
 *
 *     Scan 0
 *     Scan 1
 *     .
 *     .
 *     .
 *     Scan n-2
 *     Scan n-1
 *
 * The pixels on a monochrome device are either black or white. If the corresponding bit in the
 * bitmap is 1, the pixel is set to the foreground color; if the corresponding bit in the bitmap is
 * zero, the pixel is set to the background color.
 *
 * All devices that have the RC_BITBLT device capability support bitmaps. For more information, see
 * GetDeviceCaps.
 *
 * Each device has a unique color format.
 */
typedef struct tagBITMAP {
    /**
     * Specifies the bitmap type; set to zero
     */
    LONG        bmType;
    /**
     * Specifies the width, in pixels, of the bitmap. The width must be greater than zero.
     */
    LONG        bmWidth;
    /**
     * Specifies the height, in pixels, of the bitmap. The height must be greater than zero.
     */
    LONG        bmHeight;
    /**
     * Specifies the number of bytes in each scan line. This value must be divisible by 2, because the
     * system assumes that the bit values of a bitmap form an array that is word aligned.
     */
    LONG        bmWidthBytes;
    /**
     * Specifies the count of color planes.
     */
    WORD        bmPlanes;
    /**
     * Specifies the number of bits required to indicate the color of a pixel.
     */
    WORD        bmBitsPixel;
    /**
     * Pointer to the location of the bit values for the bitmap. The bmBits member must be a long
     * pointer to an array of character (1-byte) values.
     */
    LPVOID      bmBits;
} BITMAP, *PBITMAP, FAR *LPBITMAP;

/**
 * This structure contains information about the dimensions and color format of a device-independent
 * bitmap (DIB).
 *
 * The BITMAPINFO structure combines the BITMAPINFOHEADER structure and a color table to provide a
 * complete definition of the dimensions and colors of a DIB.
 *
 * An application should use the information stored in the biSize member to locate the color table
 * in a BITMAPINFO structure, as follows:
 *
 *     pColor = ((LPSTR)pBitmapInfo +
 *         (WORD)(pBitmapInfo->bmiHeader.biSize));
 *
 * For Windows CE versions 1.0 and 1.01, the biBitCount member must be either one or two.
 */
typedef struct tagBITMAPINFOHEADER {
        /**
         * Specifies the number of bytes required by the structure.
         */
        DWORD      biSize;
        /**
         * Specifies the width of the bitmap, in pixels.
         */
        LONG       biWidth;
        /**
         * Specifies the height of the bitmap, in pixels. If biHeight is positive, the bitmap is a bottom-up
         * DIB and its origin is the lower-left corner. If biHeight is negative, the bitmap is a top-down
         * DIB and its origin is the upper-left corner.
         *
         * If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or
         * BI_BITFIELDS. Top-down DIBs cannot be compressed.
         */
        LONG       biHeight;
        /**
         * Specifies the number of planes for the target device. This value must be set to 1.
         */
        WORD       biPlanes;
        /**
         * Specifies the number of bits per pixel. The biBitCount member of the BITMAPINFOHEADER structure
         * determines the number of bits that define each pixel and the maximum number of colors in the
         * bitmap. This member must be one of the following values. Value Description 1 The bitmap is
         * monochrome, and the bmiColors member contains two entries. Each bit in the bitmap array
         * represents a pixel. If the bit is clear, the pixel is displayed with the color of the first entry
         * in the bmiColors table; if the bit is set, the pixel has the color of the second entry in the
         * table. 2 The bitmap has four possible color values. 4 The bitmap has a maximum of 16 colors, and
         * the bmiColors member contains up to 16 entries. Each pixel in the bitmap is represented by a
         * 4-bit index into the color table. For example, if the first byte in the bitmap is 0x1F, the byte
         * represents two pixels. The first pixel contains the color in the second table entry, and the
         * second pixel contains the color in the sixteenth table entry. 8 The bitmap has a maximum of 256
         * colors, and the bmiColors member contains up to 256 entries. In this case, each byte in the array
         * represents a single pixel. 16 The bitmap has a maximum of 2^16 colors. If the biCompression
         * member of the BITMAPINFOHEADER is BI_RGB, the bmiColors member is NULL. Each WORD in the bitmap
         * array represents a single pixel. The relative intensities of red, green, and blue are represented
         * with 5 bits for each color component. The value for blue is in the least significant 5 bits,
         * followed by 5 bits each for green and red. The most significant bit is not used. The bmiColors
         * color table is used for optimizing colors used on palette-based devices, and must contain the
         * number of entries specified by the biClrUsed member of the BITMAPINFOHEADER. 24 The bitmap has a
         * maximum of 2^24 colors, and the bmiColors member is NULL. Each 3-byte triplet in the bitmap array
         * represents the relative intensities of blue, green, and red, respectively, for a pixel. The
         * bmiColors color table is used for optimizing colors used on palette-based devices, and must
         * contain the number of entries specified by the biClrUsed member of the BITMAPINFOHEADER. 32 The
         * bitmap has a maximum of 2^32 colors. If the biCompression member of the BITMAPINFOHEADER is
         * BI_RGB, the bmiColors member is NULL. Each DWORD in the bitmap array represents the relative
         * intensities of blue, green, and red, respectively, for a pixel. The high byte in each DWORD is
         * not used. The bmiColors color table is used for optimizing colors used on palette-based devices,
         * and must contain the number of entries specified by the biClrUsed member of the BITMAPINFOHEADER.
         * If the biCompression member of the BITMAPINFOHEADER is BI_BITFIELDS, the bmiColors member
         * contains three DWORD color masks that specify the red, green, and blue components, respectively,
         * of each pixel. Each DWORD in the bitmap array represents a single pixel.
         */
        WORD       biBitCount;
        /**
         * Specifies the type of compression for a compressed bottom-up bitmap (top-down DIBs cannot be
         * compressed). This member must be the following value: Value Description BI_RGB An uncompressed
         * format
         */
        DWORD      biCompression;
        /**
         * Specifies the size, in bytes, of the image. This may be set to zero for BI_RGB bitmaps.
         */
        DWORD      biSizeImage;
        /**
         * Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap. An
         * application can use this value to select a bitmap from a resource group that best matches the
         * characteristics of the current device.
         */
        LONG       biXPelsPerMeter;
        /**
         * Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap
         */
        LONG       biYPelsPerMeter;
        /**
         * Specifies the number of color indexes in the color table that are actually used by the bitmap. If
         * this value is zero, the bitmap uses the maximum number of colors corresponding to the value of
         * the biBitCount member for the compression mode specified by biCompression.
         *
         * If biClrUsed is nonzero and the biBitCount member is less than 16, the biClrUsed member specifies
         * the actual number of colors the graphics engine or device driver accesses. If biBitCount is 16 or
         * greater, the biClrUsed member specifies the size of the color table used to optimize performance
         * of the system color palettes. If biBitCount equals 16 or 32, the optimal color palette starts
         * immediately following the three DWORD masks.
         *
         * If the bitmap is a packed bitmap (a bitmap in which the bitmap array immediately follows the
         * BITMAPINFO header and is referenced by a single pointer), the biClrUsed member must be either
         * zero or the actual size of the color table.
         */
        DWORD      biClrUsed;
        /**
         * Specifies the number of color indexes required for displaying the bitmap. If this value is zero,
         * all colors are required.
         */
        DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

/**
 * This structure defines the dimensions and color information of a Windows-based device-independent
 * bitmap (DIB).
 *
 * A device-independent bitmap consists of two distinct parts: a BITMAPINFO structure describing the
 * dimensions and colors of the bitmap, and an array of bytes defining the pixels of the bitmap. The
 * bits in the array are packed together, but each scan line must be padded with zeroes to end on a
 * LONG data-type boundary. If the height of the bitmap is positive, the bitmap is a bottom-up DIB
 * and its origin is the lower-left corner. If the height is negative, the bitmap is a top-down DIB
 * and its origin is the upper left corner.
 *
 * A bitmap is packed when the bitmap array immediately follows the BITMAPINFO header. Packed
 * bitmaps are referenced by a single pointer. For packed bitmaps, the ClrUsed member of the
 * BITMAPINFOHEADER structure must be set to an even number when using the DIB_PAL_COLORS mode so
 * the DIB bitmap array starts on a DWORD boundary.
 *
 * Note The bmiColors member should not contain palette indexes if the bitmap is stored in a file or
 * transferred to another application.
 *
 * Unless the application has exclusive use and control of the bitmap, the bitmap color table should
 * contain explicit RGB values.
 */
typedef struct tagBITMAPINFO {
    /**
     * Specifies a bitmap information header structure that contains information about the dimensions of
     * color format. Use the BITMAPINFOHEADER structure.
     */
    BITMAPINFOHEADER    bmiHeader;
    /**
     * Contains one of the following:
     *
     * An array of RGBQUAD. The elements of the array make up the color table.
     *
     * An array of 16-bit unsigned integers that specifies indexes into the currently realized logical
     * palette. This use of bmiColors is allowed for functions that use DIBs. When bmiColors elements
     * contain indexes to a realized logical palette, they must also call the following bitmap
     * functions: CreateDIBPatternBrushPt and CreateDIBSection. The iUsage parameter of CreateDIBSection
     * must be set to DIB_PAL_COLORS.
     *
     * The number of entries in the array depends on the values of the biBitCount and biClrUsed members
     * of the BITMAPINFOHEADER structure.
     *
     * The colors in the bmiColors table appear in order of importance. For more information, see the
     * "Remarks" section.
     */
    RGBQUAD             bmiColors[1];
} BITMAPINFO, FAR *LPBITMAPINFO, *PBITMAPINFO;

#include "pshpack2.h"
/**
 * This structure contains information about the type, size, and layout of a file that containing a
 * device-independent bitmap (DIB).
 *
 * A BITMAPINFO or BITMAPCOREINFO structure immediately follows the BITMAPFILEHEADER structure in
 * the DIB file.
 */
typedef struct _tagBITMAPFILEHEADER {
    /**
     * Specifies the file type. It must be BM.
     */
    WORD    bfType;
    /**
     * Specifies the size, in bytes, of the bitmap file
     */
    DWORD   bfSize;
    /**
     * Reserved; set to zero
     */
    WORD    bfReserved1;
    /**
     * Reserved; set to zero
     */
    WORD    bfReserved2;
    /**
     * Specifies the offset, in bytes, from the BITMAPFILEHEADER structure to the bitmap bits
     */
    DWORD   bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#include "poppack.h"

typedef struct tagHANDLETABLE {
    HGDIOBJ     objectHandle[1];
} HANDLETABLE, *PHANDLETABLE, FAR *LPHANDLETABLE;

/**
 * This function creates a memory device context (DC) compatible with the specified device.
 *
 * @param hdc [in] Handle to an existing device context. If this handle is NULL, the function
 *   creates a memory device context compatible with the application's current screen.
 *
 * @return The handle to a memory device context indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * A memory device context is a device context that exists only in memory. When the memory device
 * context is created, its display surface is exactly one monochrome pixel wide and one monochrome
 * pixel high. Before an application can use a memory device context for drawing operations, it must
 * select a bitmap of the correct width and height into the device context. This may be done by
 * using CreateCompatibleBitmap specifying the height, width, and color organization required in the
 * function call.
 *
 * When a memory device context is created, all attributes are set to normal default values. The
 * memory device context can be use as a normal device context. You can set the attributes to
 * non-default values, obtain the current setting of its attributes, select pens, brushes and
 * regions into it.
 *
 * The CreateCompatibleDC function can only be used with devices that support raster operations. An
 * application can determine whether a device supports these operations by calling the GetDeviceCaps
 * function.
 *
 * When you no longer need the memory device context, call the DeleteDC function to delete it.
 */
WINGDIAPI  HDC       WINAPI CreateCompatibleDC(HDC);
/**
 * This function deletes the specified device context (DC).
 *
 * @param hdc [in] Handle to the device context.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * An application must not delete a device context whose handle was obtained by calling the GetDC
 * function. Instead, it must call the ReleaseDC function to free the device context.
 */
WINGDIAPI  BOOL      WINAPI DeleteDC(HDC);
/**
 * This function deletes a logical pen, brush, font, bitmap, region, or palette, freeing all system
 * resources associated with the object. After the object is deleted, the specified handle is no
 * longer valid.
 *
 * @param hObject [in] Handle to a logical pen, brush, font, bitmap, region, or palette.
 *
 * @return Nonzero indicates success. Zero indicates that the specified handle is not valid or that
 *   the handle is currently selected into a device context. To get extended error information, call
 *   GetLastError.
 *
 * Do not delete a drawing object (pen or brush) while it is still selected into a device context.
 *
 * When a pattern brush is deleted, the bitmap associated with the brush is not deleted. The bitmap
 * must be deleted independently.
 */
WINGDIAPI  BOOL      WINAPI DeleteObject(HGDIOBJ);
/**
 * This function returns the current background color for the specified device context.
 *
 * @param hdc [in] Handle to the device context whose background color is to be returned.
 *
 * @return A COLORREF value for the current background color indicates success. CLR_INVALID
 *   indicates failure.
 */
WINGDIAPI  COLORREF  WINAPI GetBkColor(HDC);
/**
 * This function returns the current background mix mode for a specified device context. The
 * background mix mode of a device context affects text and dashed pens.
 *
 * @param hdc [in] Handle to the device context whose background mode is to be returned.
 *
 * @return Either OPAQUE or TRANSPARENT, which specifies the current background mix mode, indicates
 *   success. Zero indicates failure.
 *
 * The background mix mode value is stored internally as a single byte.
 */
WINGDIAPI  int       WINAPI GetBkMode(HDC);
/**
 * This function returns the currently selected object of the specified type.
 *
 * @param hdc [in] Handle to the device context.
 * @param uObjectType [in] Specifies the object type to be queried. It is one of the following
 *   values: Value Description OBJ_PEN Returns the current selected pen. OBJ_BRUSH Returns the current
 *   selected brush. OBJ_PAL Returns the current selected palette. Windows CE versions 1.0 and 1.01 do
 *   not support this value. OBJ_FONT Returns the current selected font. OBJ_BITMAP Returns the
 *   current selected bitmap.
 *
 * @return The handle of the specified object indicates success. NULL indicates failure. To get
 *   extended error information, call GetLastError.
 *
 * An application can use the GetCurrentObject and GetObject functions to retrieve descriptions of
 * the graphic objects currently selected into the given device context.
 */
WINGDIAPI  HGDIOBJ   WINAPI GetCurrentObject(HDC,UINT);
/**
 * This function retrieves information about the capabilities of a specified device.
 *
 * @param hdc [in] Handle to the device context.
 * @param nIndex [in] Specifies the item to return. This parameter can be one of the following
 *   values. Value Description DRIVERVERSION The device driver version. TECHNOLOGY Device technology.
 *   It can be any one of the following values. DT_PLOTTER Vector plotter DT_RASDISPLAY Raster display
 *   DT_RASPRINTER Raster printer DT_RASCAMERA Raster camera DT_CHARSTREAM Character stream
 *   DT_DISPFILE Display file HORZSIZE Width, in millimeters, of the physical screen. VERTSIZE Height,
 *   in millimeters, of the physical screen. HORZRES Width, in pixels, of the screen. VERTRES Height,
 *   in raster lines, of the screen. LOGPIXELSX Number of pixels per logical inch along the screen
 *   width. In a system with multiple display monitors, this value is the same for all monitors.
 *   LOGPIXELSY Number of pixels per logical inch along the screen height. In a system with multiple
 *   display monitors, this value is the same for all monitors. BITSPIXEL Number of adjacent color
 *   bits for each pixel. PLANES Number of color planes. NUMBRUSHES Number of device-specific brushes.
 *   NUMPENS Number of device-specific pens. NUMFONTS Number of device-specific fonts. NUMCOLORS
 *   Number of entries in the device's color table, if the device has a color depth of no more than 8
 *   bits per pixel. For devices with greater color depths, -1 is returned. ASPECTX Relative width of
 *   a device pixel used for line drawing. ASPECTY Relative height of a device pixel used for line
 *   drawing. ASPECTXY Diagonal width of the device pixel used for line drawing. PDEVICESIZE Reserved.
 *   CLIPCAPS Flag that indicates the clipping capabilities of the device. If the device can clip to a
 *   rectangle, it is 1. Otherwise, it is 0. SIZEPALETTE Number of entries in the system palette. This
 *   index is valid only if the device driver sets the RC_PALETTE bit in the RASTERCAPS index and is
 *   available only if the driver is compatible with 16-bit Windows. NUMRESERVED Number of reserved
 *   entries in the system palette. This index is valid only if the device driver sets the RC_PALETTE
 *   bit in the RASTERCAPS index and is available only if the driver is compatible with 16-bit
 *   Windows. COLORRES Actual color resolution of the device, in bits per pixel. This index is valid
 *   only if the device driver sets the RC_PALETTE bit in the RASTERCAPS index and is available only
 *   if the driver is compatible with 16-bit Windows. PHYSICALWIDTH For printing devices: the width of
 *   the physical page, in device units. For example, a printer set to print at 600 dpi on 8.5"x11"
 *   paper has a physical width value of 5100 device units. Note that the physical page is almost
 *   always greater than the printable area of the page, and never smaller. Windows CE versions 1.0
 *   and 1.01 do not support this value. PHYSICALHEIGHT For printing devices: the height of the
 *   physical page, in device units. For example, a printer set to print at 600 dpi on 8.5"x11" paper
 *   has a physical height value of 6600 device units. Note that the physical page is almost always
 *   greater than the printable area of the page, and never smaller. Windows CE versions 1.0 and 1.01
 *   do not support this value. PHYSICALOFFSETX For printing devices: the distance from the left edge
 *   of the physical page to the left edge of the printable area, in device units. For example, a
 *   printer set to print at 600 dpi on 8.5"x11" paper, that cannot print on the leftmost 0.25" of
 *   paper, has a horizontal physical offset of 150 device units. Windows CE versions 1.0 and 1.01 do
 *   not support this value. PHYSICALOFFSETY For printing devices: the distance from the top edge of
 *   the physical page to the top edge of the printable area, in device units. For example, a printer
 *   set to print at 600 dpi on 8.5"x11" paper, that cannot print on the topmost 0.5" of paper, has a
 *   vertical physical offset of 300 device units. Windows CE versions 1.0 and 1.01 do not support
 *   this value. RASTERCAPS Value that indicates the raster capabilities of the device, as shown in
 *   the following list: RC_BANDING Requires banding support. RC_BITBLT Capable of transferring
 *   bitmaps. RC_BITMAP64 Capable of supporting bitmaps larger than 64K. RC_DI_BITMAP Capable of
 *   supporting device independent bitmaps. RC_DIBTODEV Unsupported. RC_GDI20_OUTPUT Capable of
 *   supporting features of 16-bit Windows 2.0. RC_PALETTE Specifies a palette-based device.
 *   RC_SCALING Capable of scaling. RC_STRETCHBLT Unsupported. RC_STRETCHDIB Unsupported CURVECAPS
 *   Value that indicates the curve capabilities of the device, as shown in the following list:
 *   CC_NONE Device does not support curves. CC_CHORD Device can draw chord arcs. CC_CIRCLES Device
 *   can draw circles. CC_ELLIPSES Device can draw ellipses. CC_INTERIORS Device can draw interiors.
 *   CC_PIE Device can draw pie wedges. CC_ROUNDRECT Device can draw rounded rectangles. CC_STYLED
 *   Device can draw styled borders. CC_WIDE Device can draw wide borders. CC_WIDESTYLED Device can
 *   draw borders that are wide and styled. LINECAPS Value that indicates the line capabilities of the
 *   device, as shown in the following list: LC_NONE Device does not support lines. LC_INTERIORS
 *   Device can draw interiors. LC_MARKER Device can draw a marker. LC_POLYLINE Device can draw a
 *   polyline. LC_POLYMARKER Device can draw multiple markers. LC_STYLED Device can draw styled lines.
 *   LC_WIDE Device can draw wide lines. LC_WIDESTYLED Device can draw lines that are wide and styled.
 *   POLYGONALCAPS Value that indicates the polygon capabilities of the device, as shown in the
 *   following list: PC_NONE Device does not support polygons. PC_INTERIORS Device can draw interiors.
 *   PC_POLYGON Device can draw alternate-fill polygons. PC_RECTANGLE Device can draw rectangles.
 *   PC_SCANLINE Device can draw a single scanline. PC_STYLED Device can draw styled borders. PC_WIDE
 *   Device can draw wide borders. PC_WIDESTYLED Device can draw borders that are wide and styled.
 *   PC_WINDPOLYGON Device can draw winding-fill polygons. TEXTCAPS Value that indicates the text
 *   capabilities of the device, as shown in the following list: TC_OP_CHARACTER Device is capable of
 *   character output precision. TC_OP_STROKE Device is capable of stroke output precision.
 *   TC_CP_STROKE Device is capable of stroke clip precision. TC_CR_90 Device is capable of 90-degree
 *   character rotation. TC_CR_ANY Device is capable of any character rotation. TC_SF_X_YINDEP Device
 *   can scale independently in the x- and y-directions. TC_SA_DOUBLE Device is capable of doubled
 *   character for scaling. TC_SA_INTEGER Device uses integer multiples only for character scaling.
 *   TC_SA_CONTIN Device uses any multiples for exact character scaling. TC_EA_DOUBLE Device can draw
 *   double-weight characters. TC_IA_ABLE Device can italicize. TC_UA_ABLE Device can underline.
 *   TC_SO_ABLE Device can draw strikeouts. TC_RA_ABLE Device can draw raster fonts. TC_VA_ABLE Device
 *   can draw vector fonts. TC_RESERVED Reserved; must be zero. TC_SCROLLBLT Device cannot scroll
 *   using a bit-block transfer. Note that this meaning may be the opposite of what you expect.
 *
 * @return The return value specifies the value of the desired item.
 *
 * The following table shows the six indexes that GetDeviceCaps provides in place of printer
 * escapes.
 *
 * Index Printer escape replaced PHYSICALWIDTH GETPHYSPAGESIZE PHYSICALHEIGHT GETPHYSPAGESIZE
 * PHYSICALOFFSETX GETPRINTINGOFFSET PHYSICALOFFSETY GETPHYSICALOFFSET SCALINGFACTORX
 * GETSCALINGFACTOR SCALINGFACTORY GETSCALINGFACTOR
 *
 * Windows CE versions 1.0 and 1.01 do not support these indexes.
 */
WINGDIAPI  int       WINAPI GetDeviceCaps(HDC,int);
/**
 * This function obtains information about a specified graphics object. Depending on the graphics
 * object, the function places a filled-in BITMAP, DIBSECTON, LOGBRUSH, LOGFONT, or LOGPEN structure
 * into a specified buffer.
 *
 * @param hgdiobj [in] Handle to the graphics object of interest. This can be a handle to one of the
 *   following: a logical bitmap, a brush, a font, a palette, a pen, or a device-independent bitmap
 *   created by calling the CreateDIBSection function.
 * @param cbBuffer [in] Specifies the number of bytes of information to be written to the buffer.
 * @param lpvObject [out] Long pointer to a buffer that is to receive the information about the
 *   specified graphics object. The following table shows the type of information the buffer receives
 *   for each type of graphics object you can specify with hgdiobj: Object type Data written to
 *   *lpvObject HBITMAP BITMAP HBITMAP returned from a call to CreateDIBSection DIBSECTION, if
 *   cbBuffer is set to sizeof(DIBSECTION), or BITMAP, if cbBuffer is set to sizeof(BITMAP) HPALETTE A
 *   WORD count of the number of entries in the logical palette HPEN LOGPEN HBRUSH LOGBRUSH HFONT
 *   LOGFONT If the lpvObject parameter is NULL, the function return value is the number of bytes
 *   required to store the information it writes to the buffer for the specified graphics object. For
 *   Windows CE versions 1.0 and 1.01: The HPALETTE object type is not supported. GetObject always
 *   returns a BITMAP when it is used on a DIB section.
 *
 * @return If the function succeeds, and lpvObject is a valid pointer, the return value is the
 *   number of bytes stored into the buffer. If the function succeeds, and lpvObject is NULL, the
 *   return value is the number of bytes required to hold the information the function would store
 *   into the buffer. If the function fails, the return value is zero. To get extended error
 *   information, call GetLastError.
 *
 * The buffer pointed to by the lpvObject parameter must be sufficiently large to receive the
 * information about the graphics object.
 *
 * If hgdiobj identifies a bitmap created by calling CreateDIBSection, and the specified buffer is
 * large enough, the GetObject function returns a DIBSECTION structure. In addition, the bmBits
 * member of the BITMAP structure contained within the DIBSECTION will contain a pointer to the
 * bitmap's bit values.
 *
 * If hgdiobj identifies a bitmap created by any other means, GetObject returns only the width,
 * height, and color format information of the bitmap.
 *
 * If hgdiobj identifies a logical palette, GetObject retrieves a 2-byte integer that specifies the
 * number of entries in the palette. The function does not retrieve the LOGPALETTE structure
 * defining the palette. To retrieve information about palette entries, an application can call the
 * GetPaletteEntries function.
 */
WINGDIAPI  int       WINAPI GetObjectA(HGDIOBJ, int, LPVOID);
/**
 * This function obtains information about a specified graphics object. Depending on the graphics
 * object, the function places a filled-in BITMAP, DIBSECTON, LOGBRUSH, LOGFONT, or LOGPEN structure
 * into a specified buffer.
 *
 * @param hgdiobj [in] Handle to the graphics object of interest. This can be a handle to one of the
 *   following: a logical bitmap, a brush, a font, a palette, a pen, or a device-independent bitmap
 *   created by calling the CreateDIBSection function.
 * @param cbBuffer [in] Specifies the number of bytes of information to be written to the buffer.
 * @param lpvObject [out] Long pointer to a buffer that is to receive the information about the
 *   specified graphics object. The following table shows the type of information the buffer receives
 *   for each type of graphics object you can specify with hgdiobj: Object type Data written to
 *   *lpvObject HBITMAP BITMAP HBITMAP returned from a call to CreateDIBSection DIBSECTION, if
 *   cbBuffer is set to sizeof(DIBSECTION), or BITMAP, if cbBuffer is set to sizeof(BITMAP) HPALETTE A
 *   WORD count of the number of entries in the logical palette HPEN LOGPEN HBRUSH LOGBRUSH HFONT
 *   LOGFONT If the lpvObject parameter is NULL, the function return value is the number of bytes
 *   required to store the information it writes to the buffer for the specified graphics object. For
 *   Windows CE versions 1.0 and 1.01: The HPALETTE object type is not supported. GetObject always
 *   returns a BITMAP when it is used on a DIB section.
 *
 * @return If the function succeeds, and lpvObject is a valid pointer, the return value is the
 *   number of bytes stored into the buffer. If the function succeeds, and lpvObject is NULL, the
 *   return value is the number of bytes required to hold the information the function would store
 *   into the buffer. If the function fails, the return value is zero. To get extended error
 *   information, call GetLastError.
 *
 * The buffer pointed to by the lpvObject parameter must be sufficiently large to receive the
 * information about the graphics object.
 *
 * If hgdiobj identifies a bitmap created by calling CreateDIBSection, and the specified buffer is
 * large enough, the GetObject function returns a DIBSECTION structure. In addition, the bmBits
 * member of the BITMAP structure contained within the DIBSECTION will contain a pointer to the
 * bitmap's bit values.
 *
 * If hgdiobj identifies a bitmap created by any other means, GetObject returns only the width,
 * height, and color format information of the bitmap.
 *
 * If hgdiobj identifies a logical palette, GetObject retrieves a 2-byte integer that specifies the
 * number of entries in the palette. The function does not retrieve the LOGPALETTE structure
 * defining the palette. To retrieve information about palette entries, an application can call the
 * GetPaletteEntries function.
 */
WINGDIAPI  int       WINAPI GetObjectW(HGDIOBJ, int, LPVOID);
/**
 * This function returns the type of the specified object.
 *
 * @param h [in] Handle to the graphics object.
 *
 * @return If the function succeeds, the return value identifies the object. This value can be one
 *   of the following: Value Description OBJ_BITMAP Bitmap OBJ_BRUSH Brush OBJ_FONT Font OBJ_PAL
 *   Palette OBJ_PEN Pen OBJ_REGION Region OBJ_DC Device context OBJ_MEMDC Memory device context
 *   Windows CE versions 1.0 and 1.01 do not support the OBJ_PAL return value. If the function fails,
 *   the return value is zero. To get extended error information, call GetLastError.
 */
WINGDIAPI  DWORD     WINAPI GetObjectType(HGDIOBJ h);
/**
 * This function retrieves a handle to one of the predefined stock pens, brushes or fonts.
 *
 * @param fnObject [in] Specifies the type of stock object. It is one of the following values: Value
 *   Description BLACK_BRUSH Black brush. DKGRAY_BRUSH Dark gray brush. GRAY_BRUSH Gray brush.
 *   HOLLOW_BRUSH Hollow brush (equivalent to NULL_BRUSH). LTGRAY_BRUSH Light gray brush. NULL_BRUSH
 *   Null brush (equivalent to HOLLOW_BRUSH). WHITE_BRUSH White brush. BLACK_PEN Black pen. WHITE_PEN
 *   White pen. SYSTEM_FONT System font. By default, the system uses the system font to draw menus,
 *   dialog box controls, and text. DEFAULT_PALETTE Default palette. This palette consists of the
 *   static colors in the system palette. Windows CE versions 1.0 and 1.01 do not support this value.
 *
 * @return If the function succeeds, the return value identifies the logical object requested. NULL
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * Use the DKGRAY_BRUSH, GRAY_BRUSH, and LTGRAY_BRUSH stock objects only in windows with the
 * CS_HREDRAW and CS_VREDRAW styles. Using a gray stock brush in any other style of window can lead
 * to misalignment of brush patterns after a window is moved or sized. The origins of stock brushes
 * cannot be adjusted.
 *
 * The HOLLOW_BRUSH and NULL_BRUSH stock objects are equivalent.
 *
 * It is not necessary (but it is not harmful) to delete stock objects by calling DeleteObject.
 */
WINGDIAPI  HGDIOBJ   WINAPI GetStockObject(int);
/**
 * This function retrieves the current text color for the specified device context.
 *
 * @param hdc [in] Handle to the device context.
 *
 * @return The current text color as a COLORREF value indicates success. CLR_INVALID indicates
 *   failure.
 *
 * The text color defines the foreground color of characters drawn by using the ExtTextOut function.
 */
WINGDIAPI  COLORREF  WINAPI GetTextColor(HDC);
/**
 * This function selects an object into a specified device context. The new object replaces the
 * previous object of the same type.
 *
 * @param hdc [in] Handle to the device context.
 * @param hgdiobj [in] Handle to the object to be selected. The specified object must have been
 *   created by using one of the following functions: Object Functions Bitmap CreateBitmap,
 *   CreateCompatibleBitmap, CreateDIBSection (Bitmaps can be selected for memory device contexts
 *   only, and for only one device context at a time.) Brush CreateDIBPatternBrushPt,
 *   CreatePatternBrush, CreateSolidBrush Font CreateFontIndirect Pen CreatePen, CreatePenIndirect
 *   Region CombineRgn, CreateRectRgn, CreateRectRgnIndirect
 *
 * @return If the selected object is not a region, the handle of the object being replaced indicates
 *   success. If the selected object is a region, one of the following values indicates success: Value
 *   Description SIMPLEREGION Region consists of a single rectangle. COMPLEXREGION Region consists of
 *   more than one rectangle. NULLREGION Region is empty. NULL indicates that an error occurred and
 *   the selected object is not a region. Otherwise, a GDI_ERROR value is returned.
 *
 * This function returns the previously selected object of the specified type. An application should
 * always replace a new object with the original, default object after it has finished drawing with
 * the new object.
 *
 * An application cannot select a bitmap into more than one device context at a time.
 */
WINGDIAPI  HGDIOBJ   WINAPI SelectObject(HDC,HGDIOBJ);
/**
 * This function sets the current background color to the specified color. If the device cannot
 * represent the specified color, it sets the background color to the nearest physical color.
 *
 * @param hdc [in] Handle to the device context.
 * @param crColor [in] Specifies the new background color.
 *
 * @return If the function succeeds, the return value specifies the previous background color as a
 *   COLORREF value. If the function fails, the return value is CLR_INVALID. To get extended error
 *   information, call GetLastError.
 *
 * This function fills the gaps between styled lines drawn using a pen created by the CreatePen
 * function. The SetBKColor function also sets the background colors for the ExtTextOut function.
 *
 * If the background mode is OPAQUE, the background color is used to fill gaps between styled lines,
 * gaps between hatched lines in brushes, and character cells. The background color is also used
 * when converting bitmaps from color to monochrome and vice versa.
 */
WINGDIAPI  COLORREF  WINAPI SetBkColor(HDC,COLORREF);
/**
 * This function sets the background mix mode of the specified device context. The background mix
 * mode is used with text, hatched brushes, and with non-solid pen styles.
 *
 * @param hdc [in] Handle to the device context.
 * @param iBkMode [in] Specifies the background mode. It is either of the following values: Value
 *   Description OPAQUE Background is filled with the current background color before the text,
 *   hatched brush, or pen is drawn. TRANSPARENT Background remains untouched.
 *
 * @return If the function succeeds, the return value specifies the previous background mode. If the
 *   function fails, the return value is zero. To get extended error information, call GetLastError.
 *
 * The SetBkMode function affects the line styles for lines drawn using a pen created by the
 * CreatePen function. SetBkMode does not affect lines drawn using a pen created by the ExtCreatePen
 * function.
 *
 * The iBkMode parameter can also be set to driver-specific values. GDI passes such values to the
 * device driver and otherwise ignores them.
 *
 * The iBKMode parameter is stored internally as a single byte.
 */
WINGDIAPI  int       WINAPI SetBkMode(HDC,int);
/**
 * This function sets the text color of the specified device context to the specified color.
 *
 * @param hdc [in] Handle to the device context.
 * @param crColor [in] Specifies the color of the text.
 *
 * @return A color reference for the previous text color indicates success. CLR_INVALID indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * The text color is used to draw the face of each character written by the ExtTextOut function. The
 * text color is also used in converting bitmaps from color to monochrome and vice versa.
 */
WINGDIAPI  COLORREF  WINAPI SetTextColor(HDC,COLORREF);

#ifdef UNICODE
/**
 * This function obtains information about a specified graphics object. Depending on the graphics
 * object, the function places a filled-in BITMAP, DIBSECTON, LOGBRUSH, LOGFONT, or LOGPEN structure
 * into a specified buffer.
 *
 * @param hgdiobj [in] Handle to the graphics object of interest. This can be a handle to one of the
 *   following: a logical bitmap, a brush, a font, a palette, a pen, or a device-independent bitmap
 *   created by calling the CreateDIBSection function.
 * @param cbBuffer [in] Specifies the number of bytes of information to be written to the buffer.
 * @param lpvObject [out] Long pointer to a buffer that is to receive the information about the
 *   specified graphics object. The following table shows the type of information the buffer receives
 *   for each type of graphics object you can specify with hgdiobj: Object type Data written to
 *   *lpvObject HBITMAP BITMAP HBITMAP returned from a call to CreateDIBSection DIBSECTION, if
 *   cbBuffer is set to sizeof(DIBSECTION), or BITMAP, if cbBuffer is set to sizeof(BITMAP) HPALETTE A
 *   WORD count of the number of entries in the logical palette HPEN LOGPEN HBRUSH LOGBRUSH HFONT
 *   LOGFONT If the lpvObject parameter is NULL, the function return value is the number of bytes
 *   required to store the information it writes to the buffer for the specified graphics object. For
 *   Windows CE versions 1.0 and 1.01: The HPALETTE object type is not supported. GetObject always
 *   returns a BITMAP when it is used on a DIB section.
 *
 * @return If the function succeeds, and lpvObject is a valid pointer, the return value is the
 *   number of bytes stored into the buffer. If the function succeeds, and lpvObject is NULL, the
 *   return value is the number of bytes required to hold the information the function would store
 *   into the buffer. If the function fails, the return value is zero. To get extended error
 *   information, call GetLastError.
 *
 * The buffer pointed to by the lpvObject parameter must be sufficiently large to receive the
 * information about the graphics object.
 *
 * If hgdiobj identifies a bitmap created by calling CreateDIBSection, and the specified buffer is
 * large enough, the GetObject function returns a DIBSECTION structure. In addition, the bmBits
 * member of the BITMAP structure contained within the DIBSECTION will contain a pointer to the
 * bitmap's bit values.
 *
 * If hgdiobj identifies a bitmap created by any other means, GetObject returns only the width,
 * height, and color format information of the bitmap.
 *
 * If hgdiobj identifies a logical palette, GetObject retrieves a 2-byte integer that specifies the
 * number of entries in the palette. The function does not retrieve the LOGPALETTE structure
 * defining the palette. To retrieve information about palette entries, an application can call the
 * GetPaletteEntries function.
 */
#define GetObject   GetObjectW
#else
/**
 * This function obtains information about a specified graphics object. Depending on the graphics
 * object, the function places a filled-in BITMAP, DIBSECTON, LOGBRUSH, LOGFONT, or LOGPEN structure
 * into a specified buffer.
 *
 * @param hgdiobj [in] Handle to the graphics object of interest. This can be a handle to one of the
 *   following: a logical bitmap, a brush, a font, a palette, a pen, or a device-independent bitmap
 *   created by calling the CreateDIBSection function.
 * @param cbBuffer [in] Specifies the number of bytes of information to be written to the buffer.
 * @param lpvObject [out] Long pointer to a buffer that is to receive the information about the
 *   specified graphics object. The following table shows the type of information the buffer receives
 *   for each type of graphics object you can specify with hgdiobj: Object type Data written to
 *   *lpvObject HBITMAP BITMAP HBITMAP returned from a call to CreateDIBSection DIBSECTION, if
 *   cbBuffer is set to sizeof(DIBSECTION), or BITMAP, if cbBuffer is set to sizeof(BITMAP) HPALETTE A
 *   WORD count of the number of entries in the logical palette HPEN LOGPEN HBRUSH LOGBRUSH HFONT
 *   LOGFONT If the lpvObject parameter is NULL, the function return value is the number of bytes
 *   required to store the information it writes to the buffer for the specified graphics object. For
 *   Windows CE versions 1.0 and 1.01: The HPALETTE object type is not supported. GetObject always
 *   returns a BITMAP when it is used on a DIB section.
 *
 * @return If the function succeeds, and lpvObject is a valid pointer, the return value is the
 *   number of bytes stored into the buffer. If the function succeeds, and lpvObject is NULL, the
 *   return value is the number of bytes required to hold the information the function would store
 *   into the buffer. If the function fails, the return value is zero. To get extended error
 *   information, call GetLastError.
 *
 * The buffer pointed to by the lpvObject parameter must be sufficiently large to receive the
 * information about the graphics object.
 *
 * If hgdiobj identifies a bitmap created by calling CreateDIBSection, and the specified buffer is
 * large enough, the GetObject function returns a DIBSECTION structure. In addition, the bmBits
 * member of the BITMAP structure contained within the DIBSECTION will contain a pointer to the
 * bitmap's bit values.
 *
 * If hgdiobj identifies a bitmap created by any other means, GetObject returns only the width,
 * height, and color format information of the bitmap.
 *
 * If hgdiobj identifies a logical palette, GetObject retrieves a 2-byte integer that specifies the
 * number of entries in the palette. The function does not retrieve the LOGPALETTE structure
 * defining the palette. To retrieve information about palette entries, an application can call the
 * GetPaletteEntries function.
 */
#define GetObject   GetObjectA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBASE
/* palette entry flags */
#define PC_RESERVED     0x01    /* palette index used for animation */
#define PC_EXPLICIT     0x02    /* palette index is explicit to device */

/* constants for the biCompression field */
#define BI_BITFIELDS  3L

#include <pshpack1.h>
/**
 * This structure describes a color consisting of relative intensities of red, green, and blue. The
 * bmciColors member of the BITMAPCOREINFO structure consists of an array of RGBTRIPLE structures.
 */
typedef struct tagRGBTRIPLE {
        /**
         * Specifies the intensity of blue in the color.
         */
        BYTE    rgbtBlue;
        /**
         * Specifies the intensity of green in the color.
         */
        BYTE    rgbtGreen;
        /**
         * Specifies the intensity of red in the color.
         */
        BYTE    rgbtRed;
} RGBTRIPLE;
#include <poppack.h>

typedef struct  tagCOLORADJUSTMENT {
    WORD   caSize;
    WORD   caFlags;
    WORD   caIlluminantIndex;
    WORD   caRedGamma;
    WORD   caGreenGamma;
    WORD   caBlueGamma;
    WORD   caReferenceBlack;
    WORD   caReferenceWhite;
    SHORT  caContrast;
    SHORT  caBrightness;
    SHORT  caColorfulness;
    SHORT  caRedGreenTint;
} COLORADJUSTMENT, *PCOLORADJUSTMENT, FAR *LPCOLORADJUSTMENT;

/* size of a device name string */
#define CCHDEVICENAME 32

/* size of a form name string */
#define CCHFORMNAME 32

/**
 * This structure contains information about a printer environment and device initialization.
 *
 * A device driver's private data follows the public portion of the DEVMODE structure. The size of
 * the public data can vary for different versions of the structure. The dmSize member specifies the
 * number of bytes of public data, and the dmDriverExtra member specifies the number of bytes of
 * private data.
 *
 * All unsupported members should be initialized to zero.
 */
typedef struct _devicemodeA {
    /**
     * Unsupported; set to zero.
     */
    BYTE   dmDeviceName[CCHDEVICENAME];
    /**
     * Specifies the version number of the initialization data specification on which the structure is
     * based. Must be initialized to SPEC_VERSION.
     */
    WORD dmSpecVersion;
    /**
     * Unsupported; set to zero.
     */
    WORD dmDriverVersion;
    /**
     * Specifies the size, in bytes, of the DEVMODE structure, not including any private driver-specific
     * data that might follow the structure's public members. Set this member to sizeof(DEVMODE) to
     * indicate the version of the DEVMODE structure being used.
     */
    WORD dmSize;
    /**
     * Unsupported; set to zero.
     */
    WORD dmDriverExtra;
    /**
     * Unsupported; set to zero.
     */
    DWORD dmFields;
    /**
     * For printer devices only, specifies the orientation of the paper. It is either DMORIENT_PORTRAIT
     * (1) or DMORIENT_LANDSCAPE (2).
     */
    short dmOrientation;
    /**
     * For printer devices only, specifies the size of the paper to print on. This member is one of the
     * following predefined values: Value Description DMPAPER_LETTER Letter, 8 1/2- by 11-inches
     * DMPAPER_A4 A4 Sheet, 210- by 297-millimeters
     */
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    /**
     * Unsupported; set to zero.
     */
    short dmScale;
    /**
     * Unsupported; set to zero.
     */
    short dmCopies;
    /**
     * Unsupported; set to zero.
     */
    short dmDefaultSource;
    /**
     * Specifies the printer resolution. The following are predefined device-independent values:
     *
     * DMRES_DRAFT
     *
     * DMRES_HIGH
     */
    short dmPrintQuality;
    /**
     * Switches between color and monochrome on color printers. The following are possible values:
     *
     * DMCOLOR_COLOR
     *
     * DMCOLOR_MONOCHROME
     */
    short dmColor;
    /**
     * Unsupported; set to zero.
     */
    short dmDuplex;
    /**
     * Unsupported; set to zero.
     */
    short dmYResolution;
    /**
     * Unsupported; set to zero.
     */
    short dmTTOption;
    /**
     * Unsupported; set to zero.
     */
    short dmCollate;
    /**
     * Unsupported; set to zero.
     */
    BYTE   dmFormName[CCHFORMNAME];
    /**
     * Unsupported; set to zero.
     */
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    DWORD  dmDisplayFlags;
    DWORD  dmDisplayFrequency;
    DWORD  dmICMMethod;
    DWORD  dmICMIntent;
    DWORD  dmMediaType;
    DWORD  dmDitherType;
    DWORD  dmICCManufacturer;
    DWORD  dmICCModel;
    DWORD  dmPanningWidth;
    DWORD  dmPanningHeight;
} DEVMODEA, *PDEVMODEA, *NPDEVMODEA, *LPDEVMODEA;

/**
 * This structure contains information about a printer environment and device initialization.
 *
 * A device driver's private data follows the public portion of the DEVMODE structure. The size of
 * the public data can vary for different versions of the structure. The dmSize member specifies the
 * number of bytes of public data, and the dmDriverExtra member specifies the number of bytes of
 * private data.
 *
 * All unsupported members should be initialized to zero.
 */
typedef struct _devicemodeW {
    /**
     * Unsupported; set to zero.
     */
    WCHAR  dmDeviceName[CCHDEVICENAME];
    /**
     * Specifies the version number of the initialization data specification on which the structure is
     * based. Must be initialized to SPEC_VERSION.
     */
    WORD dmSpecVersion;
    /**
     * Unsupported; set to zero.
     */
    WORD dmDriverVersion;
    /**
     * Specifies the size, in bytes, of the DEVMODE structure, not including any private driver-specific
     * data that might follow the structure's public members. Set this member to sizeof(DEVMODE) to
     * indicate the version of the DEVMODE structure being used.
     */
    WORD dmSize;
    /**
     * Unsupported; set to zero.
     */
    WORD dmDriverExtra;
    /**
     * Unsupported; set to zero.
     */
    DWORD dmFields;
    /**
     * For printer devices only, specifies the orientation of the paper. It is either DMORIENT_PORTRAIT
     * (1) or DMORIENT_LANDSCAPE (2).
     */
    short dmOrientation;
    /**
     * For printer devices only, specifies the size of the paper to print on. This member is one of the
     * following predefined values: Value Description DMPAPER_LETTER Letter, 8 1/2- by 11-inches
     * DMPAPER_A4 A4 Sheet, 210- by 297-millimeters
     */
    short dmPaperSize;
    short dmPaperLength;
    short dmPaperWidth;
    /**
     * Unsupported; set to zero.
     */
    short dmScale;
    /**
     * Unsupported; set to zero.
     */
    short dmCopies;
    /**
     * Unsupported; set to zero.
     */
    short dmDefaultSource;
    /**
     * Specifies the printer resolution. The following are predefined device-independent values:
     *
     * DMRES_DRAFT
     *
     * DMRES_HIGH
     */
    short dmPrintQuality;
    /**
     * Switches between color and monochrome on color printers. The following are possible values:
     *
     * DMCOLOR_COLOR
     *
     * DMCOLOR_MONOCHROME
     */
    short dmColor;
    /**
     * Unsupported; set to zero.
     */
    short dmDuplex;
    /**
     * Unsupported; set to zero.
     */
    short dmYResolution;
    /**
     * Unsupported; set to zero.
     */
    short dmTTOption;
    /**
     * Unsupported; set to zero.
     */
    short dmCollate;
    /**
     * Unsupported; set to zero.
     */
    WCHAR  dmFormName[CCHFORMNAME];
    /**
     * Unsupported; set to zero.
     */
    WORD   dmLogPixels;
    DWORD  dmBitsPerPel;
    DWORD  dmPelsWidth;
    DWORD  dmPelsHeight;
    DWORD  dmDisplayFlags;
    DWORD  dmDisplayFrequency;
// #if (WINVER >= 0x0400)
//     DWORD  dmICMMethod;
//     DWORD  dmICMIntent;
//     DWORD  dmMediaType;
//     DWORD  dmDitherType;
//     DWORD  dmReserved1;
//     DWORD  dmReserved2;
// #endif /* WINVER */
} DEVMODEW, *PDEVMODEW, *NPDEVMODEW, *LPDEVMODEW;

#ifdef UNICODE
typedef DEVMODEW DEVMODE;
typedef PDEVMODEW PDEVMODE;
typedef NPDEVMODEW NPDEVMODE;
typedef LPDEVMODEW LPDEVMODE;
#else
typedef DEVMODEA DEVMODE;
typedef PDEVMODEA PDEVMODE;
typedef NPDEVMODEA NPDEVMODE;
typedef LPDEVMODEA LPDEVMODE;
#endif

/* field selection bits */
#define DM_ORIENTATION      0x00000001L
#define DM_PAPERSIZE        0x00000002L
#define DM_PAPERLENGTH      0x00000004L
#define DM_PAPERWIDTH       0x00000008L
#define DM_SCALE            0x00000010L
#define DM_COPIES           0x00000100L
#define DM_DEFAULTSOURCE    0x00000200L
#define DM_PRINTQUALITY     0x00000400L
#define DM_COLOR            0x00000800L
#define DM_DUPLEX           0x00001000L
#define DM_YRESOLUTION      0x00002000L
#define DM_TTOPTION         0x00004000L
#define DM_COLLATE          0x00008000L
#define DM_FORMNAME         0x00010000L
#define DM_LOGPIXELS        0x00020000L
#define DM_BITSPERPEL       0x00040000L
#define DM_PELSWIDTH        0x00080000L
#define DM_PELSHEIGHT       0x00100000L
#define DM_DISPLAYFLAGS     0x00200000L
#define DM_DISPLAYFREQUENCY 0x00400000L

/* orientation selections */
#define DMORIENT_PORTRAIT   1
#define DMORIENT_LANDSCAPE  2

/* paper selections */
#define DMPAPER_LETTER               1  /* Letter 8 1/2 x 11 in               */
#define DMPAPER_A4                   9  /* A4 210 x 297 mm                    */

/* print qualities */
#define DMRES_DRAFT         (-1)
#define DMRES_HIGH          (-4)

/* color enable/disable for color printers */
#define DMCOLOR_MONOCHROME  1
#define DMCOLOR_COLOR       2

/**
 * This function sets the viewpoint origin of a device context to the specified coordinates.
 *
 * @param hdc [in] Handle to the device context.
 * @param X [in] Specifies the x-coordinate, in device units, of the new viewport origin.
 * @param Y [in] Specifies the y-coordinate, in device units, of the new viewport origin.
 * @param lpPoint [in] Long pointer to a POINT structure. The previous viewport origin (in device
 *   coordinates) is placed in this structure. If lpPoint is NULL, nothing is returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINGDIAPI BOOL     WINAPI SetViewportOrgEx(HDC,int,int,LPPOINT);

// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGDRAW
/* Binary raster ops */
#define R2_BLACK            1   /*  0       */
#define R2_NOTMERGEPEN      2   /* DPon     */
#define R2_MASKNOTPEN       3   /* DPna     */
#define R2_NOTCOPYPEN       4   /* PN       */
#define R2_MASKPENNOT       5   /* PDna     */
#define R2_NOT              6   /* Dn       */
#define R2_XORPEN           7   /* DPx      */
#define R2_NOTMASKPEN       8   /* DPan     */
#define R2_MASKPEN          9   /* DPa      */
#define R2_NOTXORPEN        10  /* DPxn     */
#define R2_NOP              11  /* D        */
#define R2_MERGENOTPEN      12  /* DPno     */
#define R2_COPYPEN          13  /* P        */
#define R2_MERGEPENNOT      14  /* PDno     */
#define R2_MERGEPEN         15  /* DPo      */
#define R2_WHITE            16  /*  1       */
#define R2_LAST             16

/* Brush Styles */
#define BS_PATTERN          3
#define BS_INDEXED          4
#define BS_DIBPATTERN       5
#define BS_PATTERN8X8       7
#define BS_DIBPATTERN8X8    8
#define BS_MONOPATTERN      9

/**
 * This function creates a logical brush with the specified bitmap pattern.
 *
 * @param hbmp [in] Handle to the bitmap to be used to create the logical brush.
 *
 * @return A handle that identifies a logical brush indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * A pattern brush is a bitmap, which can be of an arbitrary size, that the system uses to paint the
 * interiors of filled shapes.
 *
 * After an application creates a brush by calling CreatePatternBrush, it can select that brush into
 * any device context by calling the SelectObject function.
 *
 * You can delete a pattern brush without affecting the associated bitmap by using the DeleteObject
 * function. Therefore, you can then use this bitmap to create any number of pattern brushes.
 *
 * A brush created by using a monochrome (1 bit per pixel) bitmap has the text and background colors
 * of the device context to which it is drawn. Pixels represented by a 0 bit are drawn with the
 * current text color; pixels represented by a 1 bit are drawn with the current background color.
 */
WINGDIAPI HBRUSH WINAPI CreatePatternBrush(HBITMAP);
/**
 * This function creates a logical pen that has the specified style, width, and color. The pen can
 * subsequently be selected into a device context and used to draw lines and curves.
 *
 * @param fnPenStyle [in] Specifies the pen style. It can be any one of the following values: Value
 *   Description PS_SOLID Pen is solid. PS_DASH Pen is dashed. This style is valid only when the pen
 *   width is one or less in device units. PS_NULL Pen is invisible.
 * @param nWidth [in] Specifies the width of the pen, in logical units. If nWidth is zero, the pen
 *   is a single pixel wide, regardless of the current transformation. CreatePen returns a pen with
 *   the specified width bit with the PS_SOLID style if you specify a width greater than one for the
 *   PS_DASH style.
 * @param crColor [in] Specifies a color reference for the pen color.
 *
 * @return Handle to a logical pen indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * After an application creates a logical pen, it can select that pen into a device context by
 * calling the SelectObject function. After a pen is selected into a device context, it can be used
 * to draw lines and curves.
 *
 * If the value specified by the nWidth parameter is zero, a line drawn with the created pen will
 * always be a single pixel wide regardless of the current transformation.
 *
 * If the value specified by nWidth is greater than 1, the fnPenStyle parameter must be PS_NULL or
 * PS_SOLID.
 *
 * User-specified endcap styles, such as PS_ENDCAP_ROUND, are not supported.
 *
 * When you no longer need the pen, call the DeleteObject function to delete it.
 */
WINGDIAPI HPEN   WINAPI CreatePen(int, int, COLORREF);
/**
 * This function fills a region using the specified brush.
 *
 * @param hdc [in] Handle to the device context.
 * @param hrgn [in] Handle to the region to be filled. The region's coordinates are presumed to be
 *   in logical units.
 * @param hbr [in] Handle to the brush to be used to fill the region.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINGDIAPI BOOL   WINAPI FillRgn(HDC, HRGN, HBRUSH);
/**
 * This function sets the current foreground mix mode. GDI uses the foreground mix mode to combine
 * pens and interiors of filled objects with the colors already on the screen. The foreground mix
 * mode defines how colors from the brush or pen are combined with the colors in the existing image.
 *
 * @param hdc [in] Handle to the device context.
 * @param fnDrawMode [in] Specifies the new mix mode. It is one of the following values: Value
 *   Description R2_BLACK Pixel is always 0. R2_COPYPEN Pixel is the pen color. R2_MASKNOTPEN Pixel is
 *   a combination of the colors common to both the screen and the inverse of the pen. R2_MASKPEN
 *   Pixel is a combination of the colors common to both the pen and the screen. R2_MASKPENNOT Pixel
 *   is a combination of the colors common to both the pen and the inverse of the screen.
 *   R2_MERGENOTPEN Pixel is a combination of the screen color and the inverse of the pen color.
 *   R2_MERGEPEN Pixel is a combination of the pen color and the screen color. R2_MERGEPENNOT Pixel is
 *   a combination of the pen color and the inverse of the screen color. R2_NOP Pixel remains
 *   unchanged. R2_NOT Pixel is the inverse of the screen color. R2_NOTCOPYPEN Pixel is the inverse of
 *   the pen color. R2_NOTMASKPEN Pixel is the inverse of the R2_MASKPEN color. R2_NOTMERGEPEN Pixel
 *   is the inverse of the R2_MERGEPEN color. R2_NOTXORPEN Pixel is the inverse of the R2_XORPEN
 *   color. R2_WHITE Pixel is always 1. R2_XORPEN Pixel is a combination of the colors in the pen and
 *   in the screen, but not in both.
 *
 * @return If the function succeeds, the return value is the previous mix mode. If the function
 *   fails, the return value is zero. To get extended error information, call GetLastError.
 *
 * Mix modes define how GDI combines source and destination colors when drawing with the current
 * pen. The mix modes are binary raster operation codes, representing all possible Boolean functions
 * of two variables, using the binary operations AND, OR, and XOR (exclusive OR), and the unary
 * operation NOT. The mix mode is for raster devices only; it is not available for vector devices.
 */
WINGDIAPI int    WINAPI SetROP2(HDC, int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDRAW
#define BS_SOLID            0
#define BS_NULL             1
#define BS_HOLLOW           BS_NULL
#define BS_DIBPATTERNPT     6

#define PS_SOLID            0
#define PS_DASH             1
#define PS_NULL             5

/**
 * This structure defines the style, color, and pattern of a logical brush.
 *
 * Windows CE version 1.0 supports only the following lbStyle values:
 *
 * BS_NULL
 *
 * BS_SOLID
 *
 * Windows CE version 2.0 supports the following additional lbStyle values:
 *
 * BS_DIBPATTERNPT
 *
 * BS_PATTERN
 *
 * Although lbColor controls the foreground color of a hatch brush, the SetBkMode and SetBkColor
 * functions control the background color.
 */
typedef struct tagLOGBRUSH {
    /**
     * Specifies the brush style. It is one of the following styles: Value Description BS_DIBPATTERN A
     * pattern brush defined by a device-independent bitmap (DIB) specification. If lbStyle is
     * BS_DIBPATTERN, the lbHatch member contains a handle to a packed DIB. Windows 95 and Windows 98:
     * Creating brushes from bitmaps or DIBs larger than 8x8 pixels is not supported. If a larger bitmap
     * is given, only a portion of the bitmap is used. BS_DIBPATTERN8X8 Same as BS_DIBPATTERN.
     * BS_DIBPATTERNPT A pattern brush defined by a device-independent bitmap (DIB) specification. If
     * lbStyle is BS_DIBPATTERNPT, the lbHatch member contains a pointer to a packed DIB. BS_HATCHED
     * Hatched brush. BS_HOLLOW Hollow brush. BS_NULL Same as BS_HOLLOW. BS_PATTERN Pattern brush
     * defined by a memory bitmap. BS_PATTERN8X8 Same as BS_PATTERN. BS_SOLID Solid brush.
     */
    UINT        lbStyle;
    /**
     * Specifies the color in which the brush is to be drawn. If lbStyle is the BS_HOLLOW or BS_PATTERN
     * style, lbColor is ignored.
     *
     * If lbStyle is BS_DIBPATTERN or BS_DIBPATTERNBT, the low-order word of lbColor specifies whether
     * the bmiColors members of the BITMAPINFO structure contain explicit red, green, blue (RGB) values
     * or indices into the currently realized logical palette. The lbColor member must be one of the
     * following values: Value Description DIB_PAL_COLORS The color table consists of an array of 16-bit
     * indices into the currently realized logical palette. DIB_RGB_COLORS The color table contains
     * literal RGB values.
     */
    COLORREF    lbColor;
    /**
     * Specifies a hatch style. The meaning depends on the brush style defined by lbStyle.
     *
     * If lbStyle is BS_DIBPATTERN, the lbHatch member contains a handle to a packed DIB. If lbStyle is
     * BS_DIBPATTERNPT, the lbHatch member contains a pointer to a packed DIB.
     *
     * If lbStyle is BS_HATCHED, the lbHatch member specifies the orientation of the lines used to
     * create the hatch. It can be one of the following values: Value Description HS_BDIAGONAL A
     * 45-degree upward, left-to-right hatch HS_CROSS Horizontal and vertical cross-hatch HS_DIAGCROSS
     * 45-degree crosshatch HS_FDIAGONAL A 45-degree downward, left-to-right hatch HS_HORIZONTAL
     * Horizontal hatch HS_VERTICAL Vertical hatch
     *
     * If lbStyle is BS_PATTERN, lbHatch is a handle to the bitmap that defines the pattern. The bitmap
     * cannot be a DIB section bitmap, which is created by the CreateDIBSection function.
     *
     * If lbStyle is BS_SOLID or BS_HOLLOW, lbHatch is ignored.
     */
    LONG        lbHatch;
} LOGBRUSH, *PLOGBRUSH, NEAR *NPLOGBRUSH, FAR *LPLOGBRUSH;

/**
 * This structure defines the style, width, and color of a pen. The CreatePenIndirect function uses
 * the LOGPEN structure.
 *
 * Windows CE does not support the following values for the lopnStyle member:
 *
 * PS_DOT
 *
 * PS_DASHDOT
 *
 * PS_DASHDOTDOT
 *
 * PS_INSIDEFRAME
 *
 * If the width of the pen is greater than 1 and the pen style is PS_INSIDEFRAME, the line is drawn
 * inside the frame of all GDI objects except polygons and polylines. If the pen color does not
 * match an available red, green, blue (RGB) value, the pen is drawn with a logical (dithered)
 * color. If the pen width is less than or equal to 1, the PS_INSIDEFRAME style is identical to the
 * PS_SOLID style.
 */
typedef struct tagLOGPEN {
    /**
     * Specifies the pen style, which is one of the following values: Value Description PS_SOLID Pen is
     * solid. PS_DASH Pen is dashed. PS_DOT Pen is dotted. PS_DASHDOT Pen has alternating dashes and
     * dots. PS_DASHDOTDOT Pen has dashes and double dots. PS_NULL Pen is invisible. PS_INSIDEFRAME Pen
     * is solid. When this pen is used in any graphics device interface (GDI) drawing function that
     * takes a bounding rectangle, the dimensions of the figure are shrunk so that it fits entirely in
     * the bounding rectangle, taking into account the width of the pen. This applies only to geometric
     * pens.
     */
    UINT        lopnStyle;
    /**
     * Specifies the POINT structure that contains the pen width, in logical units. If the pointer
     * member is NULL, the pen is one pixel wide on raster devices. The y member in the POINT structure
     * for lopnWidth is not used.
     */
    POINT       lopnWidth;
    /**
     * Specifies the pen color.
     */
    COLORREF    lopnColor;
} LOGPEN, *PLOGPEN, NEAR *NPLOGPEN, FAR *LPLOGPEN;

/**
 * This function creates a logical brush that has the pattern specified by the device-independent
 * bitmap (DIB).
 *
 * @param lpPackedDIB [in] Long pointer to a packed DIB consisting of a BITMAPINFO structure
 *   immediately followed by an array of bytes defining the pixels of the bitmap.
 * @param iUsage [in] Specifies whether the bmiColors member of the BITMAPINFO structure contains a
 *   valid color table and, if so, whether the entries in this color table contain explicit red,
 *   green, blue (RGB) values or palette indices. The iUsage parameter must be one of the following
 *   values: Value Description DIB_PAL_COLORS A color table is provided and consists of an array of
 *   16-bit indices into the logical palette of the device context into which the brush is to be
 *   selected. Windows CE versions 1.0 and 1.01 do not support this value. DIB_RGB_COLORS A color
 *   table is provided and contains literal RGB values. In Windows CE versions 2.0 and later, set the
 *   iUsage parameter to DIB_RGB_COLORS. When an 8 bpp bitmap is used, you can set iUsage to
 *   DIB_PAL_COLORS, however, in that case, Windows CE will ignore the values in the bmiColors array
 *   member of the BITMAPINFO structure.
 *
 * @return Handle to a logical brush indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * A brush is a bitmap that the system uses to paint the interiors of filled shapes.
 *
 * After an application creates a brush by calling CreateDIBPatternBrushPt, it can select that brush
 * into any device context by calling the SelectObject function.
 *
 * When you no longer need the brush, call the DeleteObject function to delete it.
 */
WINGDIAPI HBRUSH   WINAPI CreateDIBPatternBrushPt(CONST VOID *,UINT);
/**
 * This function creates a logical cosmetic pen that has the style, width, and color specified in
 * the LOGPEN structure.
 *
 * @param lplgpn [in] Long pointer to the LOGPEN structure that specifies the pen's style, width,
 *   and color.
 *
 * @return A handle that identifies a logical cosmetic pen indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * After an application creates a logical pen, it can select that pen into a device context by
 * calling the SelectObject function. After a pen is selected into a device context, it can be used
 * to draw lines and curves.
 *
 * When you no longer need the pen, call the DeleteObject function to delete it.
 */
WINGDIAPI HPEN     WINAPI CreatePenIndirect(CONST LOGPEN *);
/**
 * This function creates a logical brush that has the specified solid color.
 *
 * @param crColor [in] Specifies the color of the brush.
 *
 * @return A handle that identifies a logical brush indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * A solid brush is a bitmap that the system uses to paint the interiors of filled shapes.
 *
 * After an application creates a brush by calling CreateSolidBrush, it can select that brush into
 * any device context by calling the SelectObject function.
 *
 * Windows CE does not support dithered brushes.
 */
WINGDIAPI HBRUSH   WINAPI CreateSolidBrush(COLORREF);
/**
 * This function draws one or more edges of a rectangle.
 *
 * @param hdc [in] Handle to the device context.
 * @param qrc [in] Pointer to a RECT structure that contains the logical coordinates of the
 *   rectangle.
 * @param edge [in] Specifies the type of inner and outer edge to draw. This parameter must be a
 *   combination of one inner-border flag and one outer-border flag. The inner-border flags are as
 *   follows. Value Description BDR_RAISEDINNER Raised inner edge. BDR_SUNKENINNER Sunken inner edge.
 *   The outer-border flags are as follows. Value Description BDR_RAISEDOUTER Raised outer edge.
 *   BDR_SUNKENOUTER Sunken outer edge. Alternatively, the edge parameter can specify one of the
 *   following flags. Value Description EDGE_ETCHED Combination of BDR_SUNKENOUTER and
 *   BDR_RAISEDINNER. EDGE_RAISED Combination of BDR_RAISEDOUTER and BDR_RAISEDINNER. EDGE_SUNKEN
 *   Combination of BDR_SUNKENOUTER and BDR_SUNKENINNER.
 * @param grfFlags [in] Specifies the type of border. This parameter can be a combination of the
 *   following values. Value Description BF_ADJUST Rectangle to be adjusted to leave space for client
 *   area. BF_BOTTOM Bottom of border rectangle. BF_BOTTOMRIGHT Bottom and right side of border
 *   rectangle. BF_DIAGONAL Diagonal border. BF_DIAGONAL_ENDBOTTOMLEFT Diagonal border. The end point
 *   is the bottom-left corner of the rectangle; the origin is top-right corner.
 *   BF_DIAGONAL_ENDBOTTOMRIGHT Diagonal border. The end point is the bottom-right corner of the
 *   rectangle; the origin is top-left corner. BF_DIAGONAL_ENDTOPLEFT Diagonal border. The end point
 *   is the top-left corner of the rectangle; the origin is bottom-right corner.
 *   BF_DIAGONAL_ENDTOPRIGHT Diagonal border. The end point is the top-right corner of the rectangle;
 *   the origin is bottom-left corner. BF_FLAT Flat border. BF_LEFT Left side of border rectangle.
 *   BF_MIDDLE Interior of rectangle to be filled. BF_MONO One-dimensional border. BF_RECT Entire
 *   border rectangle. BF_RIGHT Right side of border rectangle. BF_SOFT Soft buttons instead of tiles.
 *   BF_TOP Top of border rectangle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINGDIAPI BOOL     WINAPI DrawEdge(HDC,RECT *,UINT,UINT);
/**
 * This function draws a rectangle in the style used to indicate that the rectangle has the focus.
 *
 * @param hDC [in] Handle to the device context.
 * @param lprc [in] Long pointer to a RECT structure that specifies the logical coordinates of the
 *   rectangle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * Because DrawFocusRect is an XOR function, calling it a second time with the same rectangle
 * removes the rectangle from the screen.
 *
 * This function draws a rectangle that cannot be scrolled. To scroll an area containing a rectangle
 * drawn by this function, call DrawFocusRect to remove the rectangle from the screen, scroll the
 * area, and then call DrawFocusRect again to draw the rectangle in the new position.
 */
WINGDIAPI BOOL     WINAPI DrawFocusRect(HDC,CONST RECT *);
/**
 * This function draws an ellipse. The center of the ellipse is the center of the specified bounding
 * rectangle. The ellipse is outlined by the currently selected pen and filled by the currently
 * selected brush.
 *
 * @param hdc [in] Handle to the device context.
 * @param nLeftRect [in] Specifies the x-coordinate of the upper-left corner of the bounding
 *   rectangle.
 * @param nTopRect [in] Specifies the y-coordinate of the upper-left corner of the bounding
 *   rectangle.
 * @param nRightRect [in] Specifies the x-coordinate of the lower-right corner of the bounding
 *   rectangle.
 * @param nBottomRect [in] Specifies the y-coordinate of the lower-right corner of the bounding
 *   rectangle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The current position is neither used nor updated by Ellipse.
 */
WINGDIAPI BOOL     WINAPI Ellipse(HDC,int,int,int,int);
/**
 * This function fills a rectangle using the specified brush. This function fills the rectangle's
 * left and top borders, but excludes the right and bottom borders.
 *
 * @param hDC [in] Handle to the device context.
 * @param lprc [in] Long pointer to a RECT structure that contains the logical coordinates of the
 *   rectangle to be filled.
 * @param hbr [in] Handle to the brush used to fill the rectangle. In Windows CE versions 1.0 and
 *   1.01, the hbr parameter cannot be a color brush.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The brush identified by the hbr parameter may be either a handle to a logical brush or a color
 * value. If specifying a handle to a logical brush, call one of the following functions to obtain
 * the handle: CreateHatchBrush, CreatePatternBrush, or CreateSolidBrush. Additionally, you may
 * retrieve a handle to one of the stock brushes by using the GetStockObject function. If specifying
 * a color value for the hbr parameter, it must be one of the standard system colors (the value 1
 * must be added to the chosen color). For example:
 *
 *     FillRect(hdc, &rect, (HBRUSH) (COLOR_ENDCOLORS+1));
 *
 * For a list of all the standard system colors, see GetSysColor.
 *
 * When filling the specified rectangle, FillRect does not include the rectangle's right and bottom
 * sides. GDI fills a rectangle up to, but not including, the right column and bottom row,
 * regardless of the current mapping mode.
 */
WINGDIAPI int      WINAPI FillRect(HDC,CONST RECT *,HBRUSH);
/**
 * This function retrieves the red, green, blue (RGB) color value of the pixel at the specified
 * coordinates.
 *
 * @param hdc [in] Handle to the device context.
 * @param nXPos [in] Specifies the logical x-coordinate of the pixel to be examined.
 * @param nYPos [in] Specifies the logical y-coordinate of the pixel to be examined.
 *
 * @return The RGB value of the pixel indicates success. CLR_INVALID indicates that the pixel is
 *   outside of the current clipping region.
 *
 * The pixel must be within the boundaries of the current clipping region.
 *
 * Not all devices support GetPixel. An application should call GetDeviceCaps to determine whether a
 * specified device supports this function.
 */
WINGDIAPI COLORREF WINAPI GetPixel(HDC,int,int);
/**
 * This function retrieves a handle identifying a logical brush that corresponds to the specified
 * color index.
 *
 * @param nIndex [in] Specifies a color index. This value corresponds to the color used to paint one
 *   of the 21 window elements.
 *
 * @return Handle to a logical brush indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * A brush is a bitmap that the system uses to paint the interiors of filled shapes. An application
 * can retrieve the current system colors by calling the GetSysColor function. An application can
 * set the current system colors by calling the SetSysColors function.
 *
 * An application must not register a window class for a window using a system brush.
 *
 * The values assigned to the COLOR_* flags in Windows CE are different from the values assigned to
 * these flags in Windows-based desktop platforms. Therefore, you should specify the COLOR_* flag
 * value, rather than the corresponding integer value, for the nIndex parameter. For a list of all
 * the standard system colors, see GetSysColor.
 */
WINGDIAPI HBRUSH   WINAPI GetSysColorBrush(int);
/**
 * This function draws a polygon consisting of two or more vertices connected by straight lines. The
 * current pen outlines the polygon, and the current brush fills it using the specified polygon fill
 * mode.
 *
 * @param hdc [in] Handle to the device context.
 * @param lpPoints [in] Long pointer to an array of POINT structures that specify the vertices of
 *   the polygon.
 * @param nCount [in] Specifies the number of vertices in the array. This value must be greater than
 *   or equal to 2.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The polygon is closed automatically by drawing a line from the last vertex to the first.
 *
 * The current position is neither used nor updated by the Polygon function.
 *
 * Windows CE versions 1.0 and 1.01 support only convex polygons.
 */
WINGDIAPI BOOL     WINAPI Polygon(HDC,CONST POINT *,int);
/**
 * This function draws a series of line segments by connecting the points in the specified array.
 *
 * @param hdc [in] Handle to a device context.
 * @param lppt [in] Long pointer to an array of POINT structures. Each structure in the array
 *   identifies a point in logical space.
 * @param cPoints [in] Specifies the number of points in the array. This number must be greater than
 *   or equal to two.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The lines are drawn from the first point through subsequent points by using the current pen.
 * Unlike the LineTo function, the Polyline function neither uses nor updates the current position.
 */
WINGDIAPI BOOL     WINAPI Polyline(HDC,CONST POINT *,int);
/**
 * This function draws a rectangle. The current brush outlines the rectangle and the current brush
 * fills it.
 *
 * @param hdc [in] Handle to the device context.
 * @param nLeftRect [in] Specifies the logical x-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nTopRect [in] Specifies the logical y-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nRightRect [in] Specifies width of the rectangle.
 * @param nBottomRect [in] Specifies height of the rectangle.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The current position is neither used nor updated by Rectangle. The extreme bottom and right edges
 * of rectangle are not drawn because the bottom and right coordinates are treated as the width and
 * height respectively of the rectangle instead of its edges.
 */
WINGDIAPI BOOL     WINAPI Rectangle(HDC,int,int,int,int);
/**
 * This function draws a rectangle with rounded corners. The current brush outlines the rectangle
 * and the current brush fills it.
 *
 * @param hdc [in] Handle to the device context.
 * @param nLeftRect [in] Specifies the x-coordinate of the upper-left corner of the rectangle.
 * @param nTopRect [in] Specifies the y-coordinate of the upper-left corner of the rectangle.
 * @param nRightRect [in] Specifies the x-coordinate of the lower-right corner of the rectangle.
 * @param nBottomRect [in] Specifies the y-coordinate of the lower-right corner of the rectangle.
 * @param nWidth [in] Specifies the width of the ellipse used to draw the rounded corners.
 * @param nHeight [in] Specifies the height of the ellipse used to draw the rounded corners.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The current position is neither used nor updated by this function.
 */
WINGDIAPI BOOL     WINAPI RoundRect(HDC,int,int,int,int,int,int);
/**
 * This function is called by an application to set the brush origin of the next brush selected into
 * the specified device context.
 *
 * @param hdc [in] Handle to the device context.
 * @param nXOrg [in] Specifies the x-coordinate, in device units, of the new brush origin. If this
 *   value is greater than the brush width, its value is reduced using the modulus operator (nXOrg mod
 *   brush width).
 * @param nYOrg [in] Specifies the y-coordinate, in device units, of the new brush origin. If this
 *   value is greater than the brush height, its value is reduced using the modulus operator (nYOrg
 *   mod brush height).
 * @param lppt [out] Long pointer to a POINT structure that receives the previous brush origin. This
 *   parameter can be NULL if the previous brush origin is not required.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * A brush is a bitmap that the system uses to paint the interiors of filled shapes.
 *
 * The brush origin is a pair of coordinates specifying the location of one pixel in the bitmap. The
 * default brush origin coordinates are (0,0). For horizontal coordinates, the value 0 corresponds
 * to the leftmost column of pixels; the width corresponds to the rightmost column. For vertical
 * coordinates, the value 0 corresponds to the uppermost row of pixels; the height corresponds to
 * the lowermost row.
 *
 * The system automatically tracks the origin of all window-managed device contexts and adjusts
 * their brushes as necessary to maintain an alignment of patterns on the surface. The brush origin
 * that is set with this call is relative to the upper-left corner of the client area.
 *
 * An application should call SetBrushOrgEx after using SetStretchBltMode to set the bitmap
 * stretching mode to HALFTONE. This must be done to avoid brush misalignment.
 *
 * Automatic tracking of the brush origin is not supported. Applications must call SetBrushOrgEx to
 * align the brush before using it and call the SelectObject function to select the modified brush..
 */
WINGDIAPI BOOL     WINAPI SetBrushOrgEx(HDC,int,int,LPPOINT);
/**
 * This function sets the pixel at the specified coordinates to the specified color.
 *
 * @param hdc [in] Handle to the device context.
 * @param X [in] Specifies the x-coordinate, in logical units, of the point to be set.
 * @param Y [in] Specifies the y-coordinate, in logical units, of the point to be set.
 * @param crColor [in] Specifies the color to be used to paint the point.
 *
 * @return The RGB value that the function sets the pixel to indicates success. This value may
 *   differ from the color specified by crColor; that happens when an exact match for the specified
 *   color cannot be found. -1 indicates failure. To get extended error information, call
 *   GetLastError.
 *
 * The function fails if the pixel coordinates lie outside of the current clipping region.
 *
 * Not all devices support the SetPixel function. For more information, see GetDeviceCaps.
 */
WINGDIAPI COLORREF WINAPI SetPixel(HDC,int,int,COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBITMAP
/**
 * This function creates a bitmap with the specified width, height, and bit depth.
 *
 * @param nWidth [in] Specifies the bitmap width, in pixels.
 * @param nHeight [in] Specifies the bitmap height, in pixels.
 * @param cPlanes [in] Specifies the number of color planes used by the device. The value of this
 *   parameter must be 1.
 * @param cBitsPerPel [in] Specifies the number of bits required to identify the color of a single
 *   pixel.
 * @param lpvBits [in] Long void pointer to an array of color data used to set the colors in a
 *   rectangle of pixels. Each scan line in the rectangle must be word aligned (scan lines that are
 *   not word aligned must be padded with zeros). If this parameter is NULL, the new bitmap is
 *   undefined.
 *
 * @return A handle to a bitmap indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * After a bitmap is created, it can be selected into a device context by calling the SelectObject
 * function.
 *
 * While the CreateBitmap function can be used to create color bitmaps, for performance reasons
 * applications should use CreateBitmap to create monochrome bitmaps and CreateCompatibleBitmap to
 * create color bitmaps. When a color bitmap returned from CreateBitmap is selected into a device
 * context, the system must ensure that the bitmap matches the format of the device context it is
 * being selected into. Since CreateCompatibleBitmap takes a device context, it returns a bitmap
 * that has the same format as the specified device context. Because of this, subsequent calls to
 * SelectObject are faster than with a color bitmap returned from CreateBitmap.
 *
 * If the bitmap is monochrome, zeros represent the foreground color and ones represent the
 * background color for the destination device context.
 *
 * If an application sets the nWidth or nHeight parameters to zero, CreateBitmap returns the handle
 * to a 1- by 1-pixel, monochrome bitmap.
 *
 * When you no longer need the bitmap, call the DeleteObject function to delete it.
 */
WINGDIAPI  HBITMAP   WINAPI CreateBitmap(int,int,UINT,UINT,CONST VOID *);
/**
 * This function creates a bitmap compatible with the device associated with the specified device
 * context.
 *
 * @param hdc [in] Handle to a device context.
 * @param nWidth [in] Specifies the bitmap width, in pixels.
 * @param nHeight [in] Specifies the bitmap height, in pixels.
 *
 * @return A handle to the bitmap indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The color format of the bitmap created by the CreateCompatibleBitmap function matches the color
 * format of the device identified by the hdc parameter. This bitmap can be selected into any memory
 * device context that is compatible with the original device.
 *
 * Because memory device contexts allow both color and monochrome bitmaps, the format of the bitmap
 * returned by the CreateCompatibleBitmap function differs when the specified device context is a
 * memory device context. However, a compatible bitmap that was created for a nonmemory device
 * context always possesses the same color format and uses the same color palette as the specified
 * device context.
 *
 * If an application sets the nWidth or nHeight parameters to zero, CreateCompatibleBitmap returns
 * the handle to a 1- by 1-pixel, monochrome bitmap.
 *
 * If a DIB section, which is a bitmap created by the CreateDIBSection function, is selected into
 * the device context identified by the hdc parameter, CreateCompatibleBitmap creates a DIB section.
 *
 * When you no longer need the bitmap, call the DeleteObject function to delete it.
 */
WINGDIAPI  HBITMAP   WINAPI CreateCompatibleBitmap(HDC,int,int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBITMAP || GWES_MGDX
/* structures for defining DIBs */
/**
 * This structure contains information about the dimensions and color format of a device-independent
 * bitmap (DIB).
 *
 * The BITMAPCOREINFO structure combines the BITMAPCOREHEADER structure and a color table to provide
 * a complete definition of DIB dimensions and colors. For more information about specifying a DIB,
 * see BITMAPCOREINFO.
 *
 * An application should use the information stored in the bcSize member to locate the color table
 * in a BITMAPCOREINFO structure. The following code sample shows how to locate the color table.
 *
 *     pColor = ((LPBYTE) pBitmapCoreInfo +
 *             (WORD) (pBitmapCoreInfo -> bcSize))
 */
typedef struct tagBITMAPCOREHEADER {
        /**
         * Specifies the number of bytes required by the structure
         */
        DWORD   bcSize;                 /* used to get to color table */
        /**
         * Specifies the width of the bitmap, in pixels
         */
        WORD    bcWidth;
        /**
         * Specifies the height of the bitmap, in pixels
         */
        WORD    bcHeight;
        /**
         * Specifies the number of planes for the target device. This value must be 1.
         */
        WORD    bcPlanes;
        /**
         * Specifies the number of bits per pixel. This value must be 1, 2, 4, 8, or 24.
         */
        WORD    bcBitCount;
} BITMAPCOREHEADER, FAR *LPBITMAPCOREHEADER, *PBITMAPCOREHEADER;

/**
 * This structure defines the dimensions and color information for a device independent bitmap
 * (DIB).
 *
 * A DIB consists of two parts: a BITMAPCOREINFO structure describing the dimensions and colors of
 * the bitmap, and an array of bytes defining the pixels of the bitmap. The bits in the array are
 * packed together, but each scan line must be padded with zeroes to end on a LONG boundary. The
 * origin of the bitmap is the lower left corner.
 *
 * The bcBitCount member of the BITMAPCOREHEADER structure determines the number of bits that define
 * each pixel and the maximum number of colors in the bitmap. This member can be one of the
 * following values:
 *
 * Value Description 1 The bitmap is monochrome, and the bmciColors member contains two entries.
 * Each bit in the bitmap array represents a pixel. If the bit is clear, the pixel is displayed with
 * the color of the first entry in the bmciColors table; if the bit is set, the pixel has the color
 * of the second entry in the table. 2 The bitmap has a maximum of 4 colors, and the bmciColors
 * member contains up to 4 entries. 4 The bitmap has a maximum of 16 colors, and the bmciColors
 * member contains up to 16 entries. Each pixel in the bitmap is represented by a 4-bit index into
 * the color table. For example, if the first byte in the bitmap is 0x1F, the byte represents two
 * pixels. The first pixel contains the color in the second table entry, and the second pixel
 * contains the color in the sixteenth table entry. 8 The bitmap has a maximum of 256 colors, and
 * the bmciColors member contains up to 256 entries. In this case, each byte in the array represents
 * a single pixel. 24 The bitmap has a maximum of 2^24 colors, and the bmciColors member is NULL.
 * Each three-byte triplet in the bitmap array represents the relative intensities of blue, green,
 * and red, respectively, for a pixel.
 *
 * The colors in the bmciColors table should appear in order of importance.
 *
 * Alternatively, for functions that use DIBs, the bmciColors member can be an array of 16-bit
 * unsigned integers that specify indexes into the currently realized logical palette, instead of
 * explicit RGB values. In this case, an application using the bitmap must call the DIB functions
 * (CreateDIBitmap, CreateDIBPatternBrush, and CreateDIBSection) with the iUsage parameter set to
 * DIB_PAL_COLORS.
 *
 * Note The bmciColors member should not contain palette indexes if the bitmap is to be stored in a
 * file or transferred to another application. Unless the application has exclusive use and control
 * of the bitmap, the bitmap color table should contain explicit RGB values.
 */
typedef struct tagBITMAPCOREINFO {
    /**
     * Specifies a BITMAPCOREHEADER structure that contains information about the dimensions and color
     * format of a DIB.
     */
    BITMAPCOREHEADER    bmciHeader;
    /**
     * Specifies an array of RGBTRIPLE structures that define the colors in the bitmap.
     */
    RGBTRIPLE           bmciColors[1];
} BITMAPCOREINFO, FAR *LPBITMAPCOREINFO, *PBITMAPCOREINFO;
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGRGN
/**
 * This structure describes the data returned by the GetRegionData function.
 */
typedef struct _RGNDATAHEADER {
    /**
     * Specifies the size, in bytes, of the header.
     */
    DWORD   dwSize;
    /**
     * Specifies the type of region. This value must be RDH_RECTANGLES.
     */
    DWORD   iType;
    /**
     * Specifies the number of rectangles that make up the region.
     */
    DWORD   nCount;
    /**
     * Specifies the size of the buffer required to receive the RECT structure that specifies the
     * coordinates of the rectangles that make up the region. If the size is not known, this member can
     * be zero.
     */
    DWORD   nRgnSize;
    /**
     * Specifies a bounding rectangle for the region.
     */
    RECT    rcBound;
} RGNDATAHEADER, *PRGNDATAHEADER;

/**
 * This structure contains a header and an array of rectangles that comprise a region. The
 * rectangles are sorted top to bottom, left to right. They do not overlap.
 */
typedef struct _RGNDATA {
    /**
     * Specifies a RGNDATAHEADER structure. The members of this structure specify the type of region
     * (whether it is rectangular or trapezoidal), the number of rectangles that make up the region, the
     * size of the buffer that contains the rectangle structures, and so on.
     */
    RGNDATAHEADER   rdh;
    /**
     * Specifies an arbitrary-size buffer that contains the RECT structures that make up the region.
     */
    char            Buffer[1];
} RGNDATA, *PRGNDATA, NEAR *NPRGNDATA, FAR *LPRGNDATA;
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGRGN
#define NULLREGION          1
#define SIMPLEREGION        2
#define COMPLEXREGION       3
#define RGN_ERROR			ERROR

#define RGN_AND             1
#define RGN_OR              2
#define RGN_XOR             3
#define RGN_DIFF            4
#define RGN_COPY            5
#define RGN_MIN             RGN_AND
#define RGN_MAX             RGN_COPY

/**
 * This function combines two regions and stores the result in a third region. The two regions are
 * combined according to the specified mode.
 *
 * @param hrgnDest [in] Handle to a new region with dimensions defined by combining two other
 *   regions. (This region must exist before CombineRgn is called.)
 * @param hrgnSrc1 [in] Handle to the first of two regions to be combined.
 * @param hrgnSrc2 [in] Handle to the second of two regions to be combined.
 * @param fnCombineMode [in] Specifies a mode indicating how the two regions will be combined. This
 *   parameter can be one of the following values: Value Description RGN_AND Creates the intersection
 *   of the two combined regions. RGN_COPY Creates a copy of the region identified by hrgnSrc1.
 *   RGN_DIFF Combines the parts of hrgnSrc1 that are not part of hrgnSrc2. RGN_OR Creates the union
 *   of two combined regions. RGN_XOR Creates the union of two combined regions except for any
 *   overlapping areas.
 *
 * @return The return value specifies the type of the resulting region. NULLREGION indicates that
 *   the region is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION
 *   indicates that the region is more than a single rectangle. ERROR indicates that no region is
 *   created.
 *
 * The three regions need not be distinct. For example, the hrgnSrc1 parameter can equal the
 * hrgnDest parameter.
 */
WINGDIAPI  int       WINAPI CombineRgn(HRGN,HRGN,HRGN,int);
/**
 * This function creates a rectangular region.
 *
 * @param lprc [in] Long pointer to a RECT structure that contains the coordinates of the upper-left
 *   and lower-right corners of the rectangle that defines the region.
 *
 * @return The handle to the region indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The region will be exclusive of the bottom and right edges.
 *
 * Windows CE represents regions using 16-bit values.
 */
WINGDIAPI  HRGN      WINAPI CreateRectRgnIndirect(CONST RECT *);
/**
 * This function checks the two specified regions to determine whether they are identical. The
 * function considers two regions identical if they are equal in size and shape.
 *
 * @param hSrcRgn1 [in] Handle to a region.
 * @param hSrcRgn2 [in] Handle to a region.
 *
 * @return Nonzero indicates that the two regions are equal. Zero indicates that the two regions are
 *   not equal. ERROR indicates that at least one of the region handles is invalid.
 */
WINGDIAPI  BOOL      WINAPI EqualRgn(HRGN,HRGN);
/**
 * This function creates a new clipping region that consists of the existing clipping region minus
 * the specified rectangle.
 *
 * @param hdc [in] Handle to the device context.
 * @param nLeftRect [in] Specifies the logical x-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nTopRect [in] Specifies the logical y-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nRightRect [in] Specifies the logical x-coordinate of the lower-right corner of the
 *   rectangle.
 * @param nBottomRect [in] Specifies the logical y-coordinate of the lower-right corner of the
 *   rectangle.
 *
 * @return The return value specifies the new clipping region's complexity. NULLREGION indicates
 *   that the region is empty. SIMPLEREGION indicates that the region is a single rectangle.
 *   COMPLEXREGION indicates that the region is more than one rectangle. ERROR indicates that no
 *   region was created.
 *
 * The lower and right edges of the specified rectangle are not excluded from the clipping region.
 */
WINGDIAPI  int       WINAPI ExcludeClipRect(HDC,int,int,int,int);
/**
 * This function retrieves the dimensions of the tightest bounding rectangle that can be drawn
 * around the current visible area on the device. The visible area is defined by the current
 * clipping region as well as any overlapping windows.
 *
 * @param hdc [in] Handle to the device context.
 * @param lprc [out] Long pointer to a RECT structure that is to receive the rectangle dimensions.
 *
 * @return The return value specifies the clipping box's complexity. NULLREGION indicates that the
 *   region is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION
 *   indicates that the region is more than one rectangle. ERROR indicates that an error occurred. To
 *   get extended error information, call GetLastError.
 *
 * GetClipBox returns logical coordinates based on the specified device context.
 */
WINGDIAPI  int       WINAPI GetClipBox(HDC,LPRECT);
/**
 * This function retrieves a handle identifying the current application-defined clipping region for
 * the specified device context.
 *
 * @param hdc [in] Handle to the device context.
 * @param hrgn [in/out] Handle to an existing region before the function is called. After the
 *   function returns, this parameter is a handle to a copy of the current clipping region.
 *
 * @return If there is no clipping region for the specified device context, zero indicates success.
 *   If there is a clipping region for the specified device context, 1 indicates success. -1 indicates
 *   that an error occurred. To get extended error information, call GetLastError.
 *
 * An application-defined clipping region is a clipping region identified by the SelectClipRgn
 * function. It is not a clipping region created when the application calls the BeginPaint function.
 *
 * If the function succeeds, the hrgn parameter is a handle to a copy of the current clipping
 * region. Subsequent changes to this copy will not affect the current clipping region.
 */
WINGDIAPI  int       WINAPI GetClipRgn(HDC,HRGN);
/**
 * This function fills the specified buffer with data describing a region. This data includes the
 * dimensions of the rectangles that make up the region.
 *
 * @param hRgn [in] Handle to the region.
 * @param dwCount [in] Specifies the size, in bytes, of the lpRgnData buffer.
 * @param lpRgnData [out] Long pointer to a RGNDATA structure that receives the information. If this
 *   parameter is NULL, the return value contains the number of bytes needed for the region data.
 *
 * @return If dwCount specifies an adequate number of bytes, 1 indicates success. If dwCount is too
 *   small or lpRgnData is NULL, the required number of bytes indicates success. Zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * The GetRegionData function is used in conjunction with the ExtCreateRegion function.
 *
 * Windows CE represents regions differently than other Windows-based desktop platforms. A Windows
 * CE implementation of GetRegionData may return a greater number of rectangles for a specified
 * region than Windows-based desktop platforms.
 */
WINGDIAPI  DWORD     WINAPI GetRegionData(HRGN,DWORD,LPRGNDATA);
/**
 * This function retrieves the bounding rectangle of the specified region.
 *
 * @param hrgn [in] Handle to the region.
 * @param lprc [out] Long pointer to a RECT structure that receives the bounding rectangle.
 *
 * @return The return value specifies the region's complexity. NULLREGION indicates that the region
 *   is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION indicates
 *   that the region is more than a single rectangle. Zero indicates that the hrgn parameter does not
 *   identify a valid region
 */
WINGDIAPI  int       WINAPI GetRgnBox(HRGN,RECT *);
/**
 * This function creates a new clipping region from the intersection of the current clipping region
 * and the specified rectangle.
 *
 * @param hdc [in] Handle to the device context.
 * @param nLeftRect [in] Specifies the logical x-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nTopRect [in] Specifies the logical y-coordinate of the upper-left corner of the
 *   rectangle.
 * @param nRightRect [in] Specifies the logical x-coordinate of the lower-right corner of the
 *   rectangle.
 * @param nBottomRect [in] Specifies the logical y-coordinate of the lower-right corner of the
 *   rectangle.
 *
 * @return The return value specifies the new clipping region's type. NULLREGION indicates that the
 *   region is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION
 *   indicates that the region is more than a single rectangle. ERROR indicates that an error
 *   occurred; the current clipping region is unaffected.
 *
 * The lower and rightmost edges of the specified rectangle are excluded from the clipping region.
 */
WINGDIAPI  int       WINAPI IntersectClipRect(HDC,int,int,int,int);
/**
 * This function moves a region by the specified offsets.
 *
 * @param hrgn [in] Handle to the region to be moved.
 * @param nXOffset [in] Specifies the number of logical units to move left or right.
 * @param nYOffset [in] Specifies the number of logical units to move up or down.
 *
 * @return The return value specifies the new region's complexity. NULLREGION indicates that the
 *   region is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION
 *   indicates that the region is more than a single rectangle. ERROR indicates that an error
 *   occurred; the current clipping region is unaffected.
 */
WINGDIAPI  int       WINAPI OffsetRgn(HRGN,int,int);
/**
 * This function determines whether the specified point is inside the specified region.
 *
 * @param hrgn [in] Handle to the region to be examined.
 * @param X [in] Specifies the x-coordinate of the point.
 * @param Y [in] Specifies the y-coordinate of the point.
 *
 * @return Nonzero indicates that the specified point is in the region. Zero indicates that the
 *   specified point is not in the region.
 */
WINGDIAPI  BOOL      WINAPI PtInRegion(HRGN,int,int);
/**
 * This function determines whether any part of the specified rectangle is within the boundaries of
 * a region.
 *
 * @param hrgn [in] Handle to the region.
 * @param lprc [in] Long pointer to a RECT structure that contains the coordinates of the rectangle.
 *   The lower and right edges of the rectangle are not included.
 *
 * @return Nonzero indicates that any part of the specified rectangle lies within the boundaries of
 *   the region. Zero indicates that no part of the specified rectangle lies within the boundaries of
 *   the region.
 */
WINGDIAPI  BOOL      WINAPI RectInRegion(HRGN,CONST RECT *);
/**
 * This function selects a region as the current clipping region for the specified device context.
 *
 * @param hdc [in] Handle to the device context.
 * @param hrgn [in] Handle to the region to be selected.
 *
 * @return The return value specifies the region's complexity. NULLREGION indicates that the region
 *   is empty. SIMPLEREGION indicates that the region is a single rectangle. COMPLEXREGION indicates
 *   that the region is more than a single rectangle. ERROR indicates that an error occurred; the
 *   current clipping region is unaffected. To get extended error Information, call GetLastError.
 *
 * Only a copy of the selected region is used. The region itself can be selected for any number of
 * other device contexts or it can be deleted.
 *
 * The SelectClipRgn function assumes that the coordinates for a region are specified in device
 * units.
 *
 * To remove a device-context's clipping region, specify a NULL region handle.
 */
WINGDIAPI  int       WINAPI SelectClipRgn(HDC,HRGN);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGRGN
/**
 * This function creates a rectangular region.
 *
 * @param nLeftRect [in] Specifies the x-coordinate of the upper-left corner of the region.
 * @param nTopRect [in] Specifies the y-coordinate of the upper-left corner of the region.
 * @param nRightRect [in] Specifies the x-coordinate of the lower-right corner of the region.
 * @param nBottomRect [in] Specifies the y-coordinate of the lower-right corner of the region.
 *
 * @return The handle to the region indicates success. NULL indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The region will be exclusive of the bottom and right edges.
 *
 * Windows CE represents regions using 16-bit values.
 */
WINGDIAPI HRGN  WINAPI  CreateRectRgn(int, int, int, int); 
/**
 * This function determines whether any part of the specified rectangle lies within the clipping
 * region of the specified device context.
 *
 * @param hdc [in] Handle to the device context.
 * @param lprc [in] Long pointer to a RECT structure that contains the logical coordinates of the
 *   specified rectangle.
 *
 * @return Nonzero indicates that some portion of the specified rectangle lies within the clipping
 *   region. Zero indicates that no portion of the specified rectangle lies within the clipping
 *   region.
 */
WINGDIAPI BOOL  WINAPI  RectVisible(HDC, CONST RECT *);
/**
 * This function changes a region into a rectangular region with the specified coordinates.
 *
 * @param hrgn [in] Handle to the region.
 * @param nLeftRect [in] Specifies the x-coordinate of the upper-left corner of the rectangular
 *   region.
 * @param nTopRect [in] Specifies the y-coordinate of the upper-left corner of the rectangular
 *   region.
 * @param nRightRect [in] Specifies the x-coordinate of the lower-right corner of the rectangular
 *   region.
 * @param nBottomRect [in] Specifies the y-coordinate of the lower-right corner of the rectangular
 *   region.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The region does not include the lower and right boundaries of the rectangle.
 */
WINGDIAPI BOOL  WINAPI  SetRectRgn(HRGN, int, int, int, int);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBLT
/* Ternary raster operations */
#define SRCCOPY             (DWORD)0x00CC0020 /* dest = source                   */
#define SRCPAINT            (DWORD)0x00EE0086 /* dest = source OR dest           */
#define SRCAND              (DWORD)0x008800C6 /* dest = source AND dest          */
#define SRCINVERT           (DWORD)0x00660046 /* dest = source XOR dest          */
#define SRCERASE            (DWORD)0x00440328 /* dest = source AND (NOT dest )   */
#define NOTSRCCOPY          (DWORD)0x00330008 /* dest = (NOT source)             */
#define NOTSRCERASE         (DWORD)0x001100A6 /* dest = (NOT src) AND (NOT dest) */
#define MERGECOPY           (DWORD)0x00C000CA /* dest = (source AND pattern)     */
#define MERGEPAINT          (DWORD)0x00BB0226 /* dest = (NOT source) OR dest     */
#define PATCOPY             (DWORD)0x00F00021 /* dest = pattern                  */
#define PATPAINT            (DWORD)0x00FB0A09 /* dest = DPSnoo                   */
#define PATINVERT           (DWORD)0x005A0049 /* dest = pattern XOR dest         */
#define DSTINVERT           (DWORD)0x00550009 /* dest = (NOT dest)               */
#define BLACKNESS           (DWORD)0x00000042 /* dest = BLACK                    */
#define WHITENESS           (DWORD)0x00FF0062 /* dest = WHITE                    */

/**
 * This function transfers pixels from a specified source rectangle to a specified destination
 * rectangle, altering the pixels according to the selected raster operation (ROP) code.
 *
 * @param hdcDest [in] Handle to the destination device context.
 * @param nXDest [in] Specifies the logical x-coordinate of the upper-left corner of the destination
 *   rectangle.
 * @param nYDest [in] Specifies the logical y-coordinate of the upper-left corner of the destination
 *   rectangle.
 * @param nWidth [in] Specifies the logical width of the source and destination rectangles.
 * @param nHeight [in] Specifies the logical height of the source and the destination rectangles.
 * @param hdcSrc [in] Handle to the source device context.
 * @param nXSrc [in] Specifies the logical x-coordinate of the upper-left corner of the source
 *   rectangle.
 * @param nYSrc [in] Specifies the logical y-coordinate of the upper-left corner of the source
 *   rectangle.
 * @param dwRop [in] Specifies a raster-operation code. These codes define how the color data for
 *   the source rectangle is to be combined with the color data for the destination rectangle to
 *   achieve the final color. The following list shows some common raster operation codes: Value
 *   Description BLACKNESS Fills the destination rectangle using the color associated with index 0 in
 *   the physical palette. (This color is black for the default physical palette.) DSTINVERT Inverts
 *   the destination rectangle. MERGECOPY Merges the colors of the source rectangle with the specified
 *   pattern by using the Boolean AND operator. MERGEPAINT Merges the colors of the inverted source
 *   rectangle with the colors of the destination rectangle by using the Boolean OR operator.
 *   NOTSRCCOPY Copies the inverted source rectangle to the destination. NOTSRCERASE Combines the
 *   colors of the source and destination rectangles by using the Boolean OR operator and then inverts
 *   the resultant color. PATCOPY Copies the specified pattern into the destination bitmap. PATINVERT
 *   Combines the colors of the specified pattern with the colors of the destination rectangle by
 *   using the Boolean XOR operator. PATPAINT Combines the colors of the pattern with the colors of
 *   the inverted source rectangle by using the Boolean OR operator. The result of this operation is
 *   combined with the colors of the destination rectangle by using the Boolean OR operator. SRCAND
 *   Combines the colors of the source and destination rectangles by using the Boolean AND operator.
 *   SRCCOPY Copies the source rectangle directly to the destination rectangle. SRCERASE Combines the
 *   inverted colors of the destination rectangle with the colors of the source rectangle by using the
 *   Boolean AND operator. SRCINVERT Combines the colors of the source and destination rectangles by
 *   using the Boolean XOR operator. SRCPAINT Combines the colors of the source and destination
 *   rectangles by using the Boolean OR operator. WHITENESS Fills the destination rectangle using the
 *   color associated with index 1 in the physical palette. This color is white for the default
 *   physical palette.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If a rotation or shear transformation is in effect in the source device context, BitBlt returns
 * an error. If other transformations exist in the source device context (and a matching
 * transformation is not in effect in the destination device context), the rectangle in the
 * destination device context is stretched, compressed, or rotated as necessary.
 *
 * If the color formats of the source and destination device contexts do not match, the BitBlt
 * function converts the source color format to match the destination format.
 *
 * When an enhanced metafile is being recorded, an error occurs if the source device context
 * identifies an enhanced-metafile device context.
 *
 * Not all devices support the BitBlt function. For more information, see the RC_BITBLT raster
 * capability entry in the GetDeviceCaps function, as well as the MaskBlt and StretchBlt functions.
 *
 * BitBlt returns an error if the source and destination device contexts represent different
 * devices.
 *
 * In Windows CE versions 1.0 and 1.01, the dwRop parameter can only be assigned the following
 * values:
 *
 * SRCAND
 *
 * SRCCOPY
 *
 * SRCINVERT
 *
 * SRCPAINT
 *
 * In Windows CE versions 2.0 and later, the dwRop parameter can be any ROP3.
 */
WINGDIAPI  BOOL      WINAPI BitBlt(HDC,int,int,int,int,HDC,int,int,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGBLT2
/* Quaternary raster codes */
/**
 * This macro creates a quaternary raster operation (ROP) code for use by the MaskBlt function. The
 * macro takes two ternary ROP codes as input, one for the foreground and one for the background,
 * and packs their Boolean operation indexes into the high-order word of a 32-bit value. MAKEROP4
 * ignores the low-order word.
 *
 * @param fore Specifies a foreground ternary raster operation code.
 * @param back Specifies a background ternary raster operation code
 *
 * @return The return value is a DWORD quaternary raster operation code for use with the MaskBlt
 *   function.
 *
 * The MAKEROP4 macro is defined as follows:
 *
 *     #define MAKEROP4(fore,back)
 *               (DWORD)((((back) << 8) & 0xFF000000) | (fore))
 */
#define MAKEROP4(fore,back) (DWORD)((((back) << 8) & 0xFF000000) | (fore))

/**
 * This function combines the color data for the source and destination bitmaps using the specified
 * mask and raster operation.
 *
 * @param hdcDest [in] Handle to the destination device context.
 * @param nXDest [in] Specifies the logical x-coordinate of the upper-left corner of the destination
 *   rectangle.
 * @param nYDest [in] Specifies the logical y-coordinate of the upper-left corner of the destination
 *   rectangle.
 * @param nWidth [in] Specifies the width, in logical units, of the destination rectangle and source
 *   bitmap.
 * @param nHeight [in] Specifies the height, in logical units, of the destination rectangle and
 *   source bitmap.
 * @param hdcSrc [in] Handle to the device context from which the bitmap is to be copied. It must be
 *   zero if the dwRop parameter specifies a raster operation that does not include a source.
 * @param nXSrc [in] Specifies the logical x-coordinate of the upper-left corner of the source
 *   bitmap.
 * @param nYSrc [in] Specifies the logical y-coordinate of the upper-left corner of the source
 *   bitmap.
 * @param hbmMask [in] Handle to the monochrome mask bitmap combined with the color bitmap in the
 *   source device context.
 * @param xMask [in] Specifies the horizontal pixel offset for the mask bitmap specified by the
 *   hbmMask parameter.
 * @param yMask [in] Specifies the vertical pixel offset for the mask bitmap specified by the
 *   hbmMask parameter.
 * @param dwRop [in] Specifies both foreground and background ternary raster operation codes that
 *   the function uses to control the combination of source and destination data. The background
 *   raster operation code is stored in the high-order byte of the high-order word of this value; the
 *   foreground raster operation code is stored in the low-order byte of the high-order word of this
 *   value; the low-order word of this value is ignored, and should be zero. The macro MAKEROP4
 *   creates such combinations of foreground and background raster operation codes. For a discussion
 *   of foreground and background in the context of this function, see the following Remarks section.
 *   For a list of common raster operation codes, see the BitBlt function. Windows CE versions 1.0 and
 *   1.01 support only the SRCCOPY and SRCINVERT raster operations.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * A value of 1 in the mask specified by hbmMask indicates that the foreground raster operation code
 * specified by dwRop should be applied at that location. A value of 0 in the mask indicates that
 * the background raster operation code specified by dwRop should be applied at that location.
 *
 * If the raster operations require a source, the mask rectangle must cover the source rectangle. If
 * it does not, the function will fail. If the raster operations do not require a source, the mask
 * rectangle must cover the destination rectangle. If it does not, the function will fail.
 *
 * If a rotation or shear transformation is in effect for the source device context when this
 * function is called, an error occurs. However, other types of transformation are allowed.
 *
 * If the color formats of the source, pattern, and destination bitmaps differ, this function
 * converts the pattern or source format, or both, to match the destination format.
 *
 * If the mask bitmap is not a monochrome bitmap, an error occurs.
 *
 * When an enhanced metafile is being recorded, an error occurs (and the function returns FALSE) if
 * the source device context identifies an enhanced-metafile device context.
 *
 * Not all devices support the MaskBlt function. An application should call the GetDeviceCaps
 * function to determine whether a device supports this function.
 *
 * If no mask bitmap is supplied, this function behaves exactly like BitBlt, using the foreground
 * raster operation code.
 */
WINGDIAPI  BOOL      WINAPI MaskBlt(HDC,int,int,int,int,HDC,int,int,HBITMAP,int,int,DWORD);
/**
 * This function paints the given rectangle using the brush that is currently selected into the
 * specified device context. The brush pixels and the surface pixels are combined according to the
 * specified raster operation.
 *
 * @param hdc [in] Handle to the device context.
 * @param nXLeft [in] Specifies the x-coordinate, in logical units, of the upper-left corner of the
 *   rectangle to be filled.
 * @param nYLeft [in] Specifies the y-coordinate, in logical units, of the upper-left corner of the
 *   rectangle to be filled.
 * @param nWidth [in] Specifies the width, in logical units, of the rectangle.
 * @param nHeight Specifies the height, in logical units, of the rectangle.
 * @param dwRop [in] Specifies the raster operation code. This code may be one of the following
 *   values: Value Description PATCOPY Copies the specified pattern into the destination bitmap.
 *   PATINVERT Combines the colors of the specified pattern with the colors of the destination
 *   rectangle by using the Boolean OR operator. DSTINVERT Inverts the destination rectangle.
 *   BLACKNESS Fills the destination rectangle using the color associated with index 0 in the physical
 *   palette. (This color is black for the default physical palette.) WHITENESS Fills the destination
 *   rectangle using the color associated with index 1 in the physical palette. (This color is white
 *   for the default physical palette.)
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The values of the dwRop parameter for this function are a limited subset of the full 256 ternary
 * raster-operation codes; in particular, an operation code that refers to a source rectangle cannot
 * be used.
 *
 * Not all devices support the PatBlt function. For more information, see the description of the
 * RC_BITBLT capability in the GetDeviceCaps function.
 */
WINGDIAPI  BOOL		 WINAPI PatBlt(HDC,int,int,int,int,DWORD);
/**
 * This function copies a bitmap from a source rectangle into a destination rectangle, stretching or
 * compressing the bitmap to fit the dimensions of the destination rectangle, if necessary. Windows
 * stretches or compresses the bitmap according to the stretching mode set in the destination device
 * context.
 *
 * @param hdcDest [in] Handle to the destination device context.
 * @param nXOriginDest [in] Specifies the x-coordinate, in logical units, of the upper-left corner
 *   of the destination rectangle.
 * @param nYOriginDest [in] Specifies the y-coordinate, in logical units, of the upper-left corner
 *   of the destination rectangle.
 * @param nWidthDest [in] Specifies the width, in logical units, of the destination rectangle.
 * @param nHeightDest [in] Specifies the height, in logical units, of the destination rectangle.
 * @param hdcSrc [in] Handle to the source device context.
 * @param nXOriginSrc [in] Specifies the x-coordinate, in logical units, of the upper-left corner of
 *   the source rectangle.
 * @param nYOriginSrc [in] Specifies the y-coordinate, in logical units, of the upper-left corner of
 *   the source rectangle.
 * @param nWidthSrc [in] Specifies the width, in logical units, of the source rectangle.
 * @param nHeightSrc [in] Specifies the height, in logical units, of the source rectangle.
 * @param dwRop [in] Specifies the raster operation to be performed. Raster operation codes define
 *   how the system combines colors in output operations that involve a brush, a source bitmap, and a
 *   destination bitmap. See BitBlt for a list of common raster operation codes. Windows CE versions
 *   1.0 and 1.01 support only the SRCCOPY and SRCINVERT raster operations.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * StretchBlt stretches or compresses the source bitmap in memory and then copies the result to the
 * destination rectangle. The color data for pattern or destination pixels is merged after the
 * stretching or compression occurs.
 *
 * When an enhanced metafile is being recorded, an error occurs (and the function returns FALSE) if
 * the source device context identifies an enhanced-metafile device context.
 *
 * If the specified raster operation requires a brush, the system uses the brush currently selected
 * into the destination device context.
 *
 * The destination coordinates are transformed by using the transformation currently specified for
 * the destination device context; the source coordinates are transformed by using the
 * transformation currently specified for the source device context.
 *
 * If the source transformation has a rotation or shear, an error occurs.
 *
 * If destination, source, and pattern bitmaps do not have the same color format, StretchBlt
 * converts the source and pattern bitmaps to match the destination bitmap.
 *
 * If StretchBlt must convert a monochrome bitmap to a color bitmap, it sets white bits (1) to the
 * background color and black bits (0) to the foreground color. To convert a color bitmap to a
 * monochrome bitmap, it sets pixels that match the background color to white (1) and sets all other
 * pixels to black (0). The foreground and background colors of the device context with color are
 * used.
 *
 * StretchBlt creates a mirror image of a bitmap if the signs of the nWidthSrc and nWidthDest
 * parameters or of the nHeightSrc and nHeightDest parameters differ. If nWidthSrc and nWidthDest
 * have different signs, the function creates a mirror image of the bitmap along the x-axis. If
 * nHeightSrc and nHeightDest have different signs, the function creates a mirror image of the
 * bitmap along the y-axis. Windows CE versions 1.0 and 1.01 do not support mirroring.
 *
 * Not all devices support the StretchBlt function. For more information, see the GetDeviceCaps.
 */
WINGDIAPI  BOOL      WINAPI StretchBlt(HDC,int,int,int,int,HDC,int,int,int,int,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGBLT2
/**
 * This function transfers a bitmap, omitting the portions drawn in a specified color.
 *
 * @param hdcDest [in] Handle to a device context.
 * @param DstX [in] Specifies the x-coordinate, in logical units, of the upper-left corner of the
 *   destination rectangle.
 * @param DstY [in] Specifies the y-coordinate, in logical units, of the upper-left corner of the
 *   destination rectangle.
 * @param DstCx [in] Specifies the width, in logical units, of the destination rectangle.
 * @param DistCy [in] Specifies the height, in logical units, of the destination rectangle.
 * @param hSrc [in] Specifies a source device context or a source bitmap.
 * @param SrcX [in] Specifies the x-coordinate, in logical units, of the upper-left corner of the
 *   source rectangle.
 * @param SrcY [in] Specifies the y-coordinate, in logical units, of the upper-left corner of the
 *   source rectangle.
 * @param SrcCx [in] Specifies the width, in logical units, of the source rectangle.
 * @param SrcCy [in] Specifies the height, in logical units, of the source rectangle.
 * @param TransparentColor [in] Indicates the color in the bitmap that will be rendered transparent.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the hSrc parameter is a HBITMAP, then that bitmap must not be selected into a device context
 * at the time TransparentImage is called.
 */
WINGDIAPI  BOOL      WINAPI TransparentImage(HDC,int,int,int,int,HANDLE,int,int,int,int,COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGTT || GWES_MGRAST
#define ETO_OPAQUE                   0x0002
#define ETO_CLIPPED                  0x0004

#define OUT_DEFAULT_PRECIS      0
#define OUT_STRING_PRECIS       1
#define OUT_RASTER_PRECIS       6
#define CLIP_DEFAULT_PRECIS     0
#define CLIP_CHARACTER_PRECIS   1
#define CLIP_STROKE_PRECIS      2

#define DEFAULT_QUALITY			0
#define DRAFT_QUALITY			1
#define RASTER_FONTTYPE			0x0001
#define NONANTIALIASED_QUALITY  3
#define ANTIALIASED_QUALITY     4

#ifdef UNICODE
#define LOGFONT					LOGFONTW
#define PLOGFONT				PLOGFONTW
#define NPLOGFONT				NPLOGFONTW
#define LPLOGFONT				LPLOGFONTW
#else
#define LOGFONT					LOGFONTA
#define PLOGFONT				PLOGFONTA
#define NPLOGFONT				NPLOGFONTA
#define LPLOGFONT				LPLOGFONTA
#endif //!UNICODE

#define DEFAULT_PITCH           0
#define FIXED_PITCH             1
#define VARIABLE_PITCH          2

#define ANSI_CHARSET            0
#define DEFAULT_CHARSET         1
#define SYMBOL_CHARSET          2
#ifdef INTERNATIONAL
#define SHIFTJIS_CHARSET        128
#endif

#define HANGEUL_CHARSET         129
#define GB2312_CHARSET          134
#define CHINESEBIG5_CHARSET     136
#define OEM_CHARSET             255

#define JOHAB_CHARSET           130
#define HEBREW_CHARSET          177
#define ARABIC_CHARSET          178
#define GREEK_CHARSET           161
#define TURKISH_CHARSET         162
#define VIETNAMESE_CHARSET      163
#define THAI_CHARSET            222
#define EASTEUROPE_CHARSET      238
#define RUSSIAN_CHARSET         204
#define MAC_CHARSET             77
#define BALTIC_CHARSET          186

#define FS_LATIN1               0x00000001L
#define FS_LATIN2               0x00000002L
#define FS_CYRILLIC             0x00000004L
#define FS_GREEK                0x00000008L
#define FS_TURKISH              0x00000010L
#define FS_HEBREW               0x00000020L
#define FS_ARABIC               0x00000040L
#define FS_BALTIC               0x00000080L
#define FS_VIETNAMESE           0x00000100L
#define FS_THAI                 0x00010000L
#define FS_JISJAPAN             0x00020000L
#define FS_CHINESESIMP          0x00040000L
#define FS_WANSUNG              0x00080000L
#define FS_CHINESETRAD          0x00100000L
#define FS_JOHAB                0x00200000L
#define FS_SYMBOL               0x80000000L

/* Font Families */
#define FF_DONTCARE         (0<<4)  /* Don't care or don't know. */
#define FF_ROMAN            (1<<4)  /* Variable stroke width, serifed. */
                                    /* Times Roman, Century Schoolbook, etc. */
#define FF_SWISS            (2<<4)  /* Variable stroke width, sans-serifed. */
                                    /* Helvetica, Swiss, etc. */
#define FF_MODERN           (3<<4)  /* Constant stroke width, serifed or sans-serifed. */
                                    /* Pica, Elite, Courier, etc. */
#define FF_SCRIPT           (4<<4)  /* Cursive, etc. */
#define FF_DECORATIVE       (5<<4)  /* Old English, etc. */

/* Font Weights */
#define FW_DONTCARE         0
#define FW_THIN             100
#define FW_EXTRALIGHT       200
#define FW_LIGHT            300
#define FW_NORMAL           400
#define FW_MEDIUM           500
#define FW_SEMIBOLD         600
#define FW_BOLD             700
#define FW_EXTRABOLD        800
#define FW_HEAVY            900

/* tmPitchAndFamily flags */
#define TMPF_FIXED_PITCH    0x01
#define TMPF_VECTOR         0x02
#define TMPF_DEVICE         0x08
#define TMPF_TRUETYPE       0x04

/**
 * This structure contains basic information about a physical font.
 */
typedef struct tagTEXTMETRICA
{
    /**
     * Specifies the height (ascent + descent) of characters.
     */
    LONG        tmHeight;
    /**
     * Specifies the ascent (units above the base line) of characters.
     */
    LONG        tmAscent;
    /**
     * Specifies the descent (units below the base line) of characters.
     */
    LONG        tmDescent;
    /**
     * Specifies the amount of leading (space) inside the bounds set by the tmHeight member. Accent
     * marks and other diacritical characters may occur in this area. The designer may set this member
     * to zero.
     */
    LONG        tmInternalLeading;
    /**
     * Specifies the amount of extra leading (space) that the application adds between rows. Since this
     * area is outside the font, it contains no marks and is not altered by text output calls in either
     * OPAQUE or TRANSPARENT mode. The designer may set this member to zero.
     */
    LONG        tmExternalLeading;
    /**
     * Specifies the average width of characters in the font (generally defined as the width of the
     * letter x). This value does not include the overhang required for bold or italic characters.
     */
    LONG        tmAveCharWidth;
    /**
     * Specifies the width of the widest character in the font.
     */
    LONG        tmMaxCharWidth;
    /**
     * Specifies the weight of the font.
     */
    LONG        tmWeight;
    /**
     * Specifies the extra width per string that may be added to some synthesized fonts. When
     * synthesizing some attributes, such as bold or italic, graphics device interface (GDI) or a device
     * may have to add width to a string on both a per-character and per-string basis. For example, GDI
     * makes a string bold by expanding the spacing of each character and overstriking by an offset
     * value; it italicizes a font by shearing the string. In either case, there is an overhang past the
     * basic string. For bold strings, the overhang is the distance by which the overstrike is offset.
     * For italic strings, the overhang is the amount the top of the font is sheared past the bottom of
     * the font.
     *
     * The tmOverhang member enables the application to determine how much of the character width
     * returned by a GetTextExtentPoint32 function call on a single character is the actual character
     * width and how much is the per-string extra width. The actual width is the extent minus the
     * overhang.
     */
    LONG        tmOverhang;
    /**
     * Specifies the horizontal aspect of the device for which the font was designed.
     */
    LONG        tmDigitizedAspectX;
    /**
     * Specifies the vertical aspect of the device for which the font was designed. The ratio of the
     * tmDigitizedAspectX and tmDigitizedAspectY members is the aspect ratio of the device for which the
     * font was designed.
     */
    LONG        tmDigitizedAspectY;
    /**
     * Specifies the value of the first character defined in the font.
     */
    char        tmFirstChar;
    /**
     * Specifies the value of the last character defined in the font.
     */
    char        tmLastChar;
    /**
     * Specifies the value of the character to be substituted for characters not in the font.
     */
    char        tmDefaultChar;
    /**
     * Specifies the value of the character that will be used to define word breaks for text
     * justification.
     */
    char        tmBreakChar;
    /**
     * Specifies an italic font if it is nonzero.
     */
    BYTE        tmItalic;
    /**
     * Specifies an underlined font if it is nonzero.
     */
    BYTE        tmUnderlined;
    /**
     * Specifies a strikeout font if it is nonzero.
     */
    BYTE        tmStruckOut;
    /**
     * Specifies information about the pitch, the technology, and the family of a physical font.
     *
     * The four low-order bits of this member specify information about the pitch and the technology of
     * the font. A constant is defined for each of the four bits: Value Description TMPF_FIXED_PITCH If
     * this bit is set the font is a variable pitch font. If this bit is clear the font is a fixed pitch
     * font. Note that those meanings are the opposite of what the constant name implies. TMPF_VECTOR If
     * this bit is set, the font is a vector font. TMPF_TRUETYPE If this bit is set, the font is a
     * TrueType font. TMPF_DEVICE If this bit is set, the font is a device font.
     *
     * An application should carefully test for qualities encoded in these low-order bits, making no
     * arbitrary assumptions. For example, besides having their own bits set, TrueType and PostScript
     * fonts set the TMPF_VECTOR bit. A monospace bitmap font has all of these low-order bits clear; a
     * proportional bitmap font sets the TMPF_FIXED_PITCH bit. A Postscript printer device font sets the
     * TMPF_DEVICE, TMPF_VECTOR, and TMPF_FIXED_PITCH bits.
     *
     * The four high-order bits of tmPitchAndFamily designate the font's font family. An application can
     * use the value 0xF0 and the bitwise AND operator to mask out the four low-order bits of
     * tmPitchAndFamily, thus obtaining a value that can be directly compared with font family names to
     * find an identical match. For information about font families, see the description of the LOGFONT
     * structure.
     */
    BYTE        tmPitchAndFamily;
    /**
     * Specifies the character set of the font. The character set is one of the following values:
     * ANSI_CHARSET DEFAULT_CHARSET SYMBOL_CHARSET SHIFTJIS_CHARSET HANGUL_CHARSET GB2312_CHARSET
     * CHINESEBIG5_CHARSET OEM_CHARSET JOHAB_CHARSET HEBREW_CHARSET ARABIC_CHARSET GREEK_CHARSET
     * TURKISH_CHARSET VIETNAMESE_CHARSET THAI_CHARSET EASTEUROPE_CHARSET RUSSIAN_CHARSET MAC_CHARSET
     * BALTIC_CHARSET
     */
    BYTE        tmCharSet;
} TEXTMETRICA, *PTEXTMETRICA, NEAR *NPTEXTMETRICA, FAR *LPTEXTMETRICA;

/**
 * This structure contains basic information about a physical font.
 */
typedef struct tagTEXTMETRICW
{
    /**
     * Specifies the height (ascent + descent) of characters.
     */
    LONG        tmHeight;
    /**
     * Specifies the ascent (units above the base line) of characters.
     */
    LONG        tmAscent;
    /**
     * Specifies the descent (units below the base line) of characters.
     */
    LONG        tmDescent;
    /**
     * Specifies the amount of leading (space) inside the bounds set by the tmHeight member. Accent
     * marks and other diacritical characters may occur in this area. The designer may set this member
     * to zero.
     */
    LONG        tmInternalLeading;
    /**
     * Specifies the amount of extra leading (space) that the application adds between rows. Since this
     * area is outside the font, it contains no marks and is not altered by text output calls in either
     * OPAQUE or TRANSPARENT mode. The designer may set this member to zero.
     */
    LONG        tmExternalLeading;
    /**
     * Specifies the average width of characters in the font (generally defined as the width of the
     * letter x). This value does not include the overhang required for bold or italic characters.
     */
    LONG        tmAveCharWidth;
    /**
     * Specifies the width of the widest character in the font.
     */
    LONG        tmMaxCharWidth;
    /**
     * Specifies the weight of the font.
     */
    LONG        tmWeight;
    /**
     * Specifies the extra width per string that may be added to some synthesized fonts. When
     * synthesizing some attributes, such as bold or italic, graphics device interface (GDI) or a device
     * may have to add width to a string on both a per-character and per-string basis. For example, GDI
     * makes a string bold by expanding the spacing of each character and overstriking by an offset
     * value; it italicizes a font by shearing the string. In either case, there is an overhang past the
     * basic string. For bold strings, the overhang is the distance by which the overstrike is offset.
     * For italic strings, the overhang is the amount the top of the font is sheared past the bottom of
     * the font.
     *
     * The tmOverhang member enables the application to determine how much of the character width
     * returned by a GetTextExtentPoint32 function call on a single character is the actual character
     * width and how much is the per-string extra width. The actual width is the extent minus the
     * overhang.
     */
    LONG        tmOverhang;
    /**
     * Specifies the horizontal aspect of the device for which the font was designed.
     */
    LONG        tmDigitizedAspectX;
    /**
     * Specifies the vertical aspect of the device for which the font was designed. The ratio of the
     * tmDigitizedAspectX and tmDigitizedAspectY members is the aspect ratio of the device for which the
     * font was designed.
     */
    LONG        tmDigitizedAspectY;
    /**
     * Specifies the value of the first character defined in the font.
     */
    WCHAR       tmFirstChar;
    /**
     * Specifies the value of the last character defined in the font.
     */
    WCHAR       tmLastChar;
    /**
     * Specifies the value of the character to be substituted for characters not in the font.
     */
    WCHAR       tmDefaultChar;
    /**
     * Specifies the value of the character that will be used to define word breaks for text
     * justification.
     */
    WCHAR       tmBreakChar;
    /**
     * Specifies an italic font if it is nonzero.
     */
    BYTE        tmItalic;
    /**
     * Specifies an underlined font if it is nonzero.
     */
    BYTE        tmUnderlined;
    /**
     * Specifies a strikeout font if it is nonzero.
     */
    BYTE        tmStruckOut;
    /**
     * Specifies information about the pitch, the technology, and the family of a physical font.
     *
     * The four low-order bits of this member specify information about the pitch and the technology of
     * the font. A constant is defined for each of the four bits: Value Description TMPF_FIXED_PITCH If
     * this bit is set the font is a variable pitch font. If this bit is clear the font is a fixed pitch
     * font. Note that those meanings are the opposite of what the constant name implies. TMPF_VECTOR If
     * this bit is set, the font is a vector font. TMPF_TRUETYPE If this bit is set, the font is a
     * TrueType font. TMPF_DEVICE If this bit is set, the font is a device font.
     *
     * An application should carefully test for qualities encoded in these low-order bits, making no
     * arbitrary assumptions. For example, besides having their own bits set, TrueType and PostScript
     * fonts set the TMPF_VECTOR bit. A monospace bitmap font has all of these low-order bits clear; a
     * proportional bitmap font sets the TMPF_FIXED_PITCH bit. A Postscript printer device font sets the
     * TMPF_DEVICE, TMPF_VECTOR, and TMPF_FIXED_PITCH bits.
     *
     * The four high-order bits of tmPitchAndFamily designate the font's font family. An application can
     * use the value 0xF0 and the bitwise AND operator to mask out the four low-order bits of
     * tmPitchAndFamily, thus obtaining a value that can be directly compared with font family names to
     * find an identical match. For information about font families, see the description of the LOGFONT
     * structure.
     */
    BYTE        tmPitchAndFamily;
    /**
     * Specifies the character set of the font. The character set is one of the following values:
     * ANSI_CHARSET DEFAULT_CHARSET SYMBOL_CHARSET SHIFTJIS_CHARSET HANGUL_CHARSET GB2312_CHARSET
     * CHINESEBIG5_CHARSET OEM_CHARSET JOHAB_CHARSET HEBREW_CHARSET ARABIC_CHARSET GREEK_CHARSET
     * TURKISH_CHARSET VIETNAMESE_CHARSET THAI_CHARSET EASTEUROPE_CHARSET RUSSIAN_CHARSET MAC_CHARSET
     * BALTIC_CHARSET
     */
    BYTE        tmCharSet;
} TEXTMETRICW, *PTEXTMETRICW, NEAR *NPTEXTMETRICW, FAR *LPTEXTMETRICW;

#ifdef UNICODE
typedef TEXTMETRICW TEXTMETRIC;
typedef PTEXTMETRICW PTEXTMETRIC;
typedef NPTEXTMETRICW NPTEXTMETRIC;
typedef LPTEXTMETRICW LPTEXTMETRIC;
#else
typedef TEXTMETRICA TEXTMETRIC;
typedef PTEXTMETRICA PTEXTMETRIC;
typedef NPTEXTMETRICA NPTEXTMETRIC;
typedef LPTEXTMETRICA LPTEXTMETRIC;
#endif // UNICODE

/* ntmFlags field flags */
#define NTM_REGULAR     0x00000040L
#define NTM_BOLD        0x00000020L
#define NTM_ITALIC      0x00000001L

/**
 * This structure contains data that describes a physical font.
 *
 * The last four members of the NEWTEXTMETRIC structure are not included in the TEXTMETRIC
 * structure; in all other respects, the structures are identical.
 *
 * The sizes in the NEWTEXTMETRIC structure are typically given in logical units; that is, they
 * depend on the current mapping mode of the display context.
 */
typedef struct tagNEWTEXTMETRICA
{
    /**
     * Specifies the height (ascent + descent) of characters.
     */
    LONG        tmHeight;
    /**
     * Specifies the ascent (units above the base line) of characters.
     */
    LONG        tmAscent;
    /**
     * Specifies the descent (units below the base line) of characters.
     */
    LONG        tmDescent;
    /**
     * Specifies the amount of leading (space) inside the bounds set by the tmHeight member. Accent
     * marks and other diacritical characters may occur in this area. The designer may set this member
     * to zero.
     */
    LONG        tmInternalLeading;
    /**
     * Specifies the amount of extra leading (space) that the application adds between rows. Since this
     * area is outside the font, it contains no marks and is not altered by text output calls in either
     * OPAQUE or TRANSPARENT mode. The designer may set this member to zero.
     */
    LONG        tmExternalLeading;
    /**
     * Specifies the average width of characters in the font (generally defined as the width of the
     * letter x). This value does not include overhang required for bold or italic characters.
     */
    LONG        tmAveCharWidth;
    /**
     * Specifies the width of the widest character in the font.
     */
    LONG        tmMaxCharWidth;
    /**
     * Specifies the weight of the font.
     */
    LONG        tmWeight;
    /**
     * Specifies the extra width per string that may be added to some synthesized fonts. When
     * synthesizing some attributes, such as bold or italic, graphics device interface (GDI) or a device
     * may have to add width to a string on both a per-character and per-string basis. For example, GDI
     * makes a string bold by expanding the spacing of each character and overstriking by an offset
     * value; it italicizes a font by shearing the string. In either case, there is an overhang past the
     * basic string. For bold strings, the overhang is the distance by which the overstrike is offset.
     * For italic strings, the overhang is the amount the top of the font is sheared past the bottom of
     * the font.
     *
     * The tmOverhang member enables the application to determine how much of the character width
     * returned by a GetTextExtentPoint32 function call on a single character is the actual character
     * width and how much is the per-string extra width. The actual width is the extent minus the
     * overhang.
     */
    LONG        tmOverhang;
    /**
     * Specifies the horizontal aspect of the device for which the font was designed.
     */
    LONG        tmDigitizedAspectX;
    /**
     * Specifies the vertical aspect of the device for which the font was designed. The ratio of the
     * tmDigitizedAspectX and tmDigitizedAspectY members is the aspect ratio of the device for which the
     * font was designed.
     */
    LONG        tmDigitizedAspectY;
    /**
     * Specifies the value of the first character defined in the font.
     */
    BYTE        tmFirstChar;
    /**
     * Specifies the value of the last character defined in the font.
     */
    BYTE        tmLastChar;
    /**
     * Specifies the value of the character to be substituted for characters that are not in the font.
     */
    BYTE        tmDefaultChar;
    /**
     * Specifies the value of the character to be used to define word breaks for text justification.
     */
    BYTE        tmBreakChar;
    /**
     * Specifies an italic font if it is nonzero.
     */
    BYTE        tmItalic;
    /**
     * Specifies an underlined font if it is nonzero.
     */
    BYTE        tmUnderlined;
    /**
     * Specifies a strikeout font if it is nonzero.
     */
    BYTE        tmStruckOut;
    /**
     * Specifies the pitch and family of the selected font. The low-order bit (bit 0) specifies the
     * pitch of the font. If it is 1, the font is variable pitch (or proportional). If it is 0, the font
     * is fixed pitch (or monospace). Bits 1 and 2 specify the font type. If both bits are 0, the font
     * is a raster font; if bit 1 is 1 and bit 2 is 0, the font is a vector font; if bit 1 is 0 and bit
     * 2 is set, or if both bits are 1, the font is some other type. Bit 3 is 1 if the font is a device
     * font; otherwise, it is 0.
     *
     * The four high-order bits designate the font family. The tmPitchAndFamily member can be combined
     * with the hexadecimal value 0xF0 by using the bitwise AND operator and can then be compared with
     * the font family names for an identical match. For more information about the font families, see
     * LOGFONT.
     */
    BYTE        tmPitchAndFamily;
    /**
     * Specifies the character set of the font.
     */
    BYTE        tmCharSet;
    /**
     * Specifies whether the font is italic, underscored, outlined, bold, and so forth. The following
     * list shows the bits corresponding to each font type: Bit Font 0 Italic 1 Underscore 2 Negative 3
     * Outline 4 Strikeout 5 Bold
     */
    DWORD       ntmFlags;
    /**
     * Specifies the size of the em square for the font. This value is in "notional units" (that is, the
     * units for which the font was designed).
     */
    UINT        ntmSizeEM;
    /**
     * Specifies the height, in notional units, of the font. This value should be compared with the
     * value of the ntmSizeEM member.
     */
    UINT        ntmCellHeight;
    /**
     * Specifies the average width of characters in the font, in notional units. This value should be
     * compared with the value of the ntmSizeEM member.
     */
    UINT        ntmAvgWidth;
} NEWTEXTMETRICA, *PNEWTEXTMETRICA, NEAR *NPNEWTEXTMETRICA, FAR *LPNEWTEXTMETRICA;

/**
 * This structure contains data that describes a physical font.
 *
 * The last four members of the NEWTEXTMETRIC structure are not included in the TEXTMETRIC
 * structure; in all other respects, the structures are identical.
 *
 * The sizes in the NEWTEXTMETRIC structure are typically given in logical units; that is, they
 * depend on the current mapping mode of the display context.
 */
typedef struct tagNEWTEXTMETRICW
{
    /**
     * Specifies the height (ascent + descent) of characters.
     */
    LONG        tmHeight;
    /**
     * Specifies the ascent (units above the base line) of characters.
     */
    LONG        tmAscent;
    /**
     * Specifies the descent (units below the base line) of characters.
     */
    LONG        tmDescent;
    /**
     * Specifies the amount of leading (space) inside the bounds set by the tmHeight member. Accent
     * marks and other diacritical characters may occur in this area. The designer may set this member
     * to zero.
     */
    LONG        tmInternalLeading;
    /**
     * Specifies the amount of extra leading (space) that the application adds between rows. Since this
     * area is outside the font, it contains no marks and is not altered by text output calls in either
     * OPAQUE or TRANSPARENT mode. The designer may set this member to zero.
     */
    LONG        tmExternalLeading;
    /**
     * Specifies the average width of characters in the font (generally defined as the width of the
     * letter x). This value does not include overhang required for bold or italic characters.
     */
    LONG        tmAveCharWidth;
    /**
     * Specifies the width of the widest character in the font.
     */
    LONG        tmMaxCharWidth;
    /**
     * Specifies the weight of the font.
     */
    LONG        tmWeight;
    /**
     * Specifies the extra width per string that may be added to some synthesized fonts. When
     * synthesizing some attributes, such as bold or italic, graphics device interface (GDI) or a device
     * may have to add width to a string on both a per-character and per-string basis. For example, GDI
     * makes a string bold by expanding the spacing of each character and overstriking by an offset
     * value; it italicizes a font by shearing the string. In either case, there is an overhang past the
     * basic string. For bold strings, the overhang is the distance by which the overstrike is offset.
     * For italic strings, the overhang is the amount the top of the font is sheared past the bottom of
     * the font.
     *
     * The tmOverhang member enables the application to determine how much of the character width
     * returned by a GetTextExtentPoint32 function call on a single character is the actual character
     * width and how much is the per-string extra width. The actual width is the extent minus the
     * overhang.
     */
    LONG        tmOverhang;
    /**
     * Specifies the horizontal aspect of the device for which the font was designed.
     */
    LONG        tmDigitizedAspectX;
    /**
     * Specifies the vertical aspect of the device for which the font was designed. The ratio of the
     * tmDigitizedAspectX and tmDigitizedAspectY members is the aspect ratio of the device for which the
     * font was designed.
     */
    LONG        tmDigitizedAspectY;
    /**
     * Specifies the value of the first character defined in the font.
     */
    WCHAR       tmFirstChar;
    /**
     * Specifies the value of the last character defined in the font.
     */
    WCHAR       tmLastChar;
    /**
     * Specifies the value of the character to be substituted for characters that are not in the font.
     */
    WCHAR       tmDefaultChar;
    /**
     * Specifies the value of the character to be used to define word breaks for text justification.
     */
    WCHAR       tmBreakChar;
    /**
     * Specifies an italic font if it is nonzero.
     */
    BYTE        tmItalic;
    /**
     * Specifies an underlined font if it is nonzero.
     */
    BYTE        tmUnderlined;
    /**
     * Specifies a strikeout font if it is nonzero.
     */
    BYTE        tmStruckOut;
    /**
     * Specifies the pitch and family of the selected font. The low-order bit (bit 0) specifies the
     * pitch of the font. If it is 1, the font is variable pitch (or proportional). If it is 0, the font
     * is fixed pitch (or monospace). Bits 1 and 2 specify the font type. If both bits are 0, the font
     * is a raster font; if bit 1 is 1 and bit 2 is 0, the font is a vector font; if bit 1 is 0 and bit
     * 2 is set, or if both bits are 1, the font is some other type. Bit 3 is 1 if the font is a device
     * font; otherwise, it is 0.
     *
     * The four high-order bits designate the font family. The tmPitchAndFamily member can be combined
     * with the hexadecimal value 0xF0 by using the bitwise AND operator and can then be compared with
     * the font family names for an identical match. For more information about the font families, see
     * LOGFONT.
     */
    BYTE        tmPitchAndFamily;
    /**
     * Specifies the character set of the font.
     */
    BYTE        tmCharSet;
    /**
     * Specifies whether the font is italic, underscored, outlined, bold, and so forth. The following
     * list shows the bits corresponding to each font type: Bit Font 0 Italic 1 Underscore 2 Negative 3
     * Outline 4 Strikeout 5 Bold
     */
    DWORD       ntmFlags;
    /**
     * Specifies the size of the em square for the font. This value is in "notional units" (that is, the
     * units for which the font was designed).
     */
    UINT        ntmSizeEM;
    /**
     * Specifies the height, in notional units, of the font. This value should be compared with the
     * value of the ntmSizeEM member.
     */
    UINT        ntmCellHeight;
    /**
     * Specifies the average width of characters in the font, in notional units. This value should be
     * compared with the value of the ntmSizeEM member.
     */
    UINT        ntmAvgWidth;
} NEWTEXTMETRICW, *PNEWTEXTMETRICW, NEAR *NPNEWTEXTMETRICW, FAR *LPNEWTEXTMETRICW;

#ifdef UNICODE
typedef NEWTEXTMETRICW NEWTEXTMETRIC;
typedef PNEWTEXTMETRICW PNEWTEXTMETRIC;
typedef NPNEWTEXTMETRICW NPNEWTEXTMETRIC;
typedef LPNEWTEXTMETRICW LPNEWTEXTMETRIC;
#else
typedef NEWTEXTMETRICA NEWTEXTMETRIC;
typedef PNEWTEXTMETRICA PNEWTEXTMETRIC;
typedef NPNEWTEXTMETRICA NPNEWTEXTMETRIC;
typedef LPNEWTEXTMETRICA LPNEWTEXTMETRIC;
#endif // UNICODE

/**
 * This function adds the font resource from the specified file to the Windows font table. The font
 * can subsequently be used for text output by any Windows-based application.
 *
 * @param lpszFilename [in] Long pointer to a null-terminated string that contains a valid font file
 *   filename. The file name can specify a font resource file (.fon), a raw bitmap font file (.fnt), a
 *   raw TrueType file (.ttf), a TrueType resource file (.fot), or a TrueType collection file (.ttc).
 *
 * @return The number of fonts added indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * Any application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the operating
 * system. The application should send this message by calling the SendMessage function and setting
 * the hwnd parameter to HWND_BROADCAST.
 *
 * When an application no longer needs a font resource that it loaded by calling the AddFontResource
 * function, it must remove the resource by calling the RemoveFontResource function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type is chosen at system design time, and cannot be changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI AddFontResourceA(LPWSTR);
/**
 * This function adds the font resource from the specified file to the Windows font table. The font
 * can subsequently be used for text output by any Windows-based application.
 *
 * @param lpszFilename [in] Long pointer to a null-terminated string that contains a valid font file
 *   filename. The file name can specify a font resource file (.fon), a raw bitmap font file (.fnt), a
 *   raw TrueType file (.ttf), a TrueType resource file (.fot), or a TrueType collection file (.ttc).
 *
 * @return The number of fonts added indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * Any application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the operating
 * system. The application should send this message by calling the SendMessage function and setting
 * the hwnd parameter to HWND_BROADCAST.
 *
 * When an application no longer needs a font resource that it loaded by calling the AddFontResource
 * function, it must remove the resource by calling the RemoveFontResource function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type is chosen at system design time, and cannot be changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI AddFontResourceW(LPCWSTR);
/**
 * This function creates a logical font that has the characteristics specified in the specified
 * structure. The font can subsequently be selected as the current font for any device context (DC).
 *
 * @param lplf [in] Long pointer to a LOGFONT structure that defines the characteristics of the
 *   logical font.
 *
 * @return A handle to a logical font indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * The CreateFontIndirect function creates a logical font with the characteristics specified in the
 * LOGFONT structure. When this font is selected by using the SelectObject function, GDI's font
 * mapper attempts to match the logical font with an existing physical font. If it fails to find an
 * exact match, it provides an alternative whose characteristics match as many of the requested
 * characteristics as possible.
 *
 * When you no longer need the font, call the DeleteObject function to delete it.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  HFONT     WINAPI CreateFontIndirectA(CONST LOGFONTA *);
/**
 * This function creates a logical font that has the characteristics specified in the specified
 * structure. The font can subsequently be selected as the current font for any device context (DC).
 *
 * @param lplf [in] Long pointer to a LOGFONT structure that defines the characteristics of the
 *   logical font.
 *
 * @return A handle to a logical font indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * The CreateFontIndirect function creates a logical font with the characteristics specified in the
 * LOGFONT structure. When this font is selected by using the SelectObject function, GDI's font
 * mapper attempts to match the logical font with an existing physical font. If it fails to find an
 * exact match, it provides an alternative whose characteristics match as many of the requested
 * characteristics as possible.
 *
 * When you no longer need the font, call the DeleteObject function to delete it.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  HFONT     WINAPI CreateFontIndirectW(CONST LOGFONTW *);
/**
 * This function draws a character string by using the currently selected font. An optional
 * rectangle may be provided, to be used for clipping, opaquing, or both.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param X [in] Specifies the logical x-coordinate of the reference point used to position the
 *   string.
 * @param Y [in] Specifies the logical y-coordinate of the reference point used to position the
 *   string.
 * @param fuOptions [in] Specifies how to use the application-defined rectangle. This parameter can
 *   be a combination of the following values: Value Description ETO_CLIPPED The text will be clipped
 *   to the rectangle. ETO_OPAQUE The current background color should be used to fill the rectangle.
 * @param lprc [in] Long pointer to an optional RECT structure that specifies the dimensions of a
 *   rectangle that is used for clipping, opaquing, or both.
 * @param lpString [in] Long pointer to the character string to be drawn. The string does not need
 *   to be zero-terminated, since cbCount specifies the length of the string.
 * @param cbCount [in] Specifies the number of characters in the string.
 * @param lpDx [in] Long pointer to an optional array of values that indicate the distance between
 *   origins of adjacent character cells. For example, lpDx[i] logical units separate the origins of
 *   character cell i and character cell i + 1.
 *
 * @return Nonzero indicates that the string is drawn. Zero indicates failureTo get extended error
 *   information, call GetLastError.
 *
 * The current text-alignment settings for the specified DC determine how the reference point is
 * used to position the text.
 *
 * If the lpDx parameter is NULL, the ExtTextOut function uses the default spacing between
 * characters. The character-cell origins and the contents of the array pointed to by the lpDx
 * parameter are given in logical units. A character-cell origin is defined as the upper-left corner
 * of the character cell.
 *
 * By default, the current position is not used or updated by this function. However, an application
 * can call the SetTextAlign function with the fMode parameter set to TA_UPDATECP to permit the
 * system to use and update the current position each time the application calls ExtTextOut for a
 * specified DC. When this flag is set, the system ignores the X and Y parameters on subsequent
 * ExtTextOut calls.
 */
WINGDIAPI  BOOL      WINAPI ExtTextOutA(HDC,int,int,UINT,CONST RECT *,LPCSTR,UINT,CONST INT *);
/**
 * This function draws a character string by using the currently selected font. An optional
 * rectangle may be provided, to be used for clipping, opaquing, or both.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param X [in] Specifies the logical x-coordinate of the reference point used to position the
 *   string.
 * @param Y [in] Specifies the logical y-coordinate of the reference point used to position the
 *   string.
 * @param fuOptions [in] Specifies how to use the application-defined rectangle. This parameter can
 *   be a combination of the following values: Value Description ETO_CLIPPED The text will be clipped
 *   to the rectangle. ETO_OPAQUE The current background color should be used to fill the rectangle.
 * @param lprc [in] Long pointer to an optional RECT structure that specifies the dimensions of a
 *   rectangle that is used for clipping, opaquing, or both.
 * @param lpString [in] Long pointer to the character string to be drawn. The string does not need
 *   to be zero-terminated, since cbCount specifies the length of the string.
 * @param cbCount [in] Specifies the number of characters in the string.
 * @param lpDx [in] Long pointer to an optional array of values that indicate the distance between
 *   origins of adjacent character cells. For example, lpDx[i] logical units separate the origins of
 *   character cell i and character cell i + 1.
 *
 * @return Nonzero indicates that the string is drawn. Zero indicates failureTo get extended error
 *   information, call GetLastError.
 *
 * The current text-alignment settings for the specified DC determine how the reference point is
 * used to position the text.
 *
 * If the lpDx parameter is NULL, the ExtTextOut function uses the default spacing between
 * characters. The character-cell origins and the contents of the array pointed to by the lpDx
 * parameter are given in logical units. A character-cell origin is defined as the upper-left corner
 * of the character cell.
 *
 * By default, the current position is not used or updated by this function. However, an application
 * can call the SetTextAlign function with the fMode parameter set to TA_UPDATECP to permit the
 * system to use and update the current position each time the application calls ExtTextOut for a
 * specified DC. When this flag is set, the system ignores the X and Y parameters on subsequent
 * ExtTextOut calls.
 */
WINGDIAPI  BOOL      WINAPI ExtTextOutW(HDC,int,int,UINT,CONST RECT *,LPCWSTR,UINT,CONST INT *);
/**
 * This function retrieves the number of characters in a specified string that will fit within a
 * specified space and fills an array with the text extent for each of those characters. A text
 * extent is the distance between the beginning of the space and a character that will fit in the
 * space.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszStr [in] Long pointer to the null-terminated string for which extents are to be
 *   retrieved.
 * @param cchString [in] Specifies the number of characters in the string pointed to by the lpszStr
 *   parameter.
 * @param nMaxExtent [in] Specifies the maximum allowable width, in logical units, of the formatted
 *   string.
 * @param lpnFit [out] Long pointer to an integer to receive a count of the maximum number of
 *   characters that will fit in the space specified by the nMaxExtent parameter. When the lpnFit
 *   parameter is NULL, the nMaxExtent parameter is ignored.
 * @param alpDx [out] Long pointer to an array of integers to receive partial string extents. Each
 *   element in the array gives the distance, in logical units, between the beginning of the string
 *   and one of the characters that fits in the space specified by the nMaxExtent parameter. Although
 *   this array should have at least as many elements as characters specified by the cchString
 *   parameter, the function fills the array with extents only for as many characters as are given by
 *   the lpnFit parameter. If alpDx is NULL, the function does not compute partial string widths.
 * @param lpSize [in] Long pointer to a SIZE structure that contains the dimensions of the string,
 *   in logical units when the function returns. This value cannot be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If both the lpnFit and alpDx parameters are NULL, calling the GetTextExtentExPoint function is
 * equivalent to calling the GetTextExtentPoint function.
 */
WINGDIAPI  BOOL      WINAPI GetTextExtentExPointA(HDC,LPCSTR,int,int,LPINT,LPINT,LPSIZE);
/**
 * This function retrieves the number of characters in a specified string that will fit within a
 * specified space and fills an array with the text extent for each of those characters. A text
 * extent is the distance between the beginning of the space and a character that will fit in the
 * space.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszStr [in] Long pointer to the null-terminated string for which extents are to be
 *   retrieved.
 * @param cchString [in] Specifies the number of characters in the string pointed to by the lpszStr
 *   parameter.
 * @param nMaxExtent [in] Specifies the maximum allowable width, in logical units, of the formatted
 *   string.
 * @param lpnFit [out] Long pointer to an integer to receive a count of the maximum number of
 *   characters that will fit in the space specified by the nMaxExtent parameter. When the lpnFit
 *   parameter is NULL, the nMaxExtent parameter is ignored.
 * @param alpDx [out] Long pointer to an array of integers to receive partial string extents. Each
 *   element in the array gives the distance, in logical units, between the beginning of the string
 *   and one of the characters that fits in the space specified by the nMaxExtent parameter. Although
 *   this array should have at least as many elements as characters specified by the cchString
 *   parameter, the function fills the array with extents only for as many characters as are given by
 *   the lpnFit parameter. If alpDx is NULL, the function does not compute partial string widths.
 * @param lpSize [in] Long pointer to a SIZE structure that contains the dimensions of the string,
 *   in logical units when the function returns. This value cannot be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If both the lpnFit and alpDx parameters are NULL, calling the GetTextExtentExPoint function is
 * equivalent to calling the GetTextExtentPoint function.
 */
WINGDIAPI  BOOL      WINAPI GetTextExtentExPointW(HDC,LPCWSTR,int,int,LPINT,LPINT,LPSIZE);
/**
 * This function fills the specified buffer with the metrics for the currently selected font.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lptm [out] Long pointer to the TEXTMETRIC structure that is to receive the metrics.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * For any given font, the text metric values in Windows CE will not necessarily match the text
 * metric values in Windows-based desktop platforms.
 */
WINGDIAPI  BOOL      WINAPI GetTextMetricsA(HDC,LPTEXTMETRICA);
/**
 * This function fills the specified buffer with the metrics for the currently selected font.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lptm [out] Long pointer to the TEXTMETRIC structure that is to receive the metrics.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * For any given font, the text metric values in Windows CE will not necessarily match the text
 * metric values in Windows-based desktop platforms.
 */
WINGDIAPI  BOOL      WINAPI GetTextMetricsW(HDC,LPTEXTMETRICW);
/**
 * This function removes the fonts in the specified file from the Windows CE font table.
 *
 * @param lpFileName [in] Long pointer to a null-terminated string that names a font resource file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * An application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the system. The
 * application sends this message by calling the SendMessage function with the hwnd parameter set to
 * HWND_BROADCAST.
 *
 * If there are outstanding references to a font, the associated resource remains loaded until no
 * device context (DC) is using it.
 */
WINGDIAPI  BOOL      WINAPI RemoveFontResourceA(LPCSTR);
/**
 * This function removes the fonts in the specified file from the Windows CE font table.
 *
 * @param lpFileName [in] Long pointer to a null-terminated string that names a font resource file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * An application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the system. The
 * application sends this message by calling the SendMessage function with the hwnd parameter set to
 * HWND_BROADCAST.
 *
 * If there are outstanding references to a font, the associated resource remains loaded until no
 * device context (DC) is using it.
 */
WINGDIAPI  BOOL      WINAPI RemoveFontResourceW(LPCWSTR);


/* GetTextExtentPoint variants */
#define GetTextExtentPointW(hdc, lpString, cbString, lpSize) \
        GetTextExtentExPointW(hdc, lpString, cbString, 0, NULL, NULL, lpSize)

#define GetTextExtentPointA(hdc, lpString, cbString, lpSize) \
        GetTextExtentExPointA(hdc, lpString, cbString, 0, NULL, NULL, lpSize)

#ifdef UNICODE
/**
 * This function computes the width and height of the specified string of text.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpString [in] Long pointer to the string of text. The string does not need to be
 *   zero-terminated, since cbString specifies the length of the string.
 * @param cbString [in] Specifies the number of characters in the string.
 * @param lpSize [out] Long pointer to a SIZE structure in which the dimensions of the string are to
 *   be returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The GetTextExtentPoint function uses the currently selected font to compute the dimensions of the
 * string. The width and height, in logical units, are computed without considering any clipping.
 *
 * Because some devices kern characters, the sum of the extents of the characters in a string may
 * not be equal to the extent of the string.
 *
 * The calculated string width takes into account the intercharacter spacing set by the
 * SetTextCharacterExtra function.
 *
 * The GetTextExtentPoint function is identical to the GetTextExtentPoint32 function.
 */
#define GetTextExtentPoint(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointW(hdc, lpString, cbString, lpSize)
#else
/**
 * This function computes the width and height of the specified string of text.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpString [in] Long pointer to the string of text. The string does not need to be
 *   zero-terminated, since cbString specifies the length of the string.
 * @param cbString [in] Specifies the number of characters in the string.
 * @param lpSize [out] Long pointer to a SIZE structure in which the dimensions of the string are to
 *   be returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The GetTextExtentPoint function uses the currently selected font to compute the dimensions of the
 * string. The width and height, in logical units, are computed without considering any clipping.
 *
 * Because some devices kern characters, the sum of the extents of the characters in a string may
 * not be equal to the extent of the string.
 *
 * The calculated string width takes into account the intercharacter spacing set by the
 * SetTextCharacterExtra function.
 *
 * The GetTextExtentPoint function is identical to the GetTextExtentPoint32 function.
 */
#define GetTextExtentPoint(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointA(hdc, lpString, cbString, lpSize)
#endif


/* GetTextExtentPoint32 variants */
#define GetTextExtentPoint32W(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointW(hdc, lpString, cbString, lpSize)

#define GetTextExtentPoint32A(hdc, lpString, cbString, lpSize) \
        GetTextExtentPointA(hdc, lpString, cbString, lpSize)

/**
 * This function computes the width and height of the specified string of text.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpString [in] Long pointer to the string of text. The string does not need to be
 *   zero-terminated, since cbString specifies the length of the string.
 * @param cbString [in] Specifies the number of characters in the string.
 * @param lpSize [out] Long pointer to a SIZE structure in which the dimensions of the string are to
 *   be returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The GetTextExtentPoint32 function uses the currently selected font to compute the dimensions of
 * the string. The width and height, in logical units, are computed without considering any
 * clipping.
 *
 * Because some devices kern characters, the sum of the extents of the characters in a string may
 * not be equal to the extent of the string.
 *
 * The calculated string width takes into account the intercharacter spacing set by the
 * SetTextCharacterExtra function.
 *
 * The GetTextExtentPoint32 function is identical to the GetTextExtentPoint function.
 */
#define GetTextExtentPoint32(hdc, lpString, cbString, lpSize) \
        GetTextExtentPoint(hdc, lpString, cbString, lpSize)


#ifdef UNICODE
/**
 * This function adds the font resource from the specified file to the Windows font table. The font
 * can subsequently be used for text output by any Windows-based application.
 *
 * @param lpszFilename [in] Long pointer to a null-terminated string that contains a valid font file
 *   filename. The file name can specify a font resource file (.fon), a raw bitmap font file (.fnt), a
 *   raw TrueType file (.ttf), a TrueType resource file (.fot), or a TrueType collection file (.ttc).
 *
 * @return The number of fonts added indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * Any application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the operating
 * system. The application should send this message by calling the SendMessage function and setting
 * the hwnd parameter to HWND_BROADCAST.
 *
 * When an application no longer needs a font resource that it loaded by calling the AddFontResource
 * function, it must remove the resource by calling the RemoveFontResource function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type is chosen at system design time, and cannot be changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define AddFontResource         AddFontResourceW
/**
 * This function creates a logical font that has the characteristics specified in the specified
 * structure. The font can subsequently be selected as the current font for any device context (DC).
 *
 * @param lplf [in] Long pointer to a LOGFONT structure that defines the characteristics of the
 *   logical font.
 *
 * @return A handle to a logical font indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * The CreateFontIndirect function creates a logical font with the characteristics specified in the
 * LOGFONT structure. When this font is selected by using the SelectObject function, GDI's font
 * mapper attempts to match the logical font with an existing physical font. If it fails to find an
 * exact match, it provides an alternative whose characteristics match as many of the requested
 * characteristics as possible.
 *
 * When you no longer need the font, call the DeleteObject function to delete it.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define CreateFontIndirect      CreateFontIndirectW
/**
 * This function draws a character string by using the currently selected font. An optional
 * rectangle may be provided, to be used for clipping, opaquing, or both.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param X [in] Specifies the logical x-coordinate of the reference point used to position the
 *   string.
 * @param Y [in] Specifies the logical y-coordinate of the reference point used to position the
 *   string.
 * @param fuOptions [in] Specifies how to use the application-defined rectangle. This parameter can
 *   be a combination of the following values: Value Description ETO_CLIPPED The text will be clipped
 *   to the rectangle. ETO_OPAQUE The current background color should be used to fill the rectangle.
 * @param lprc [in] Long pointer to an optional RECT structure that specifies the dimensions of a
 *   rectangle that is used for clipping, opaquing, or both.
 * @param lpString [in] Long pointer to the character string to be drawn. The string does not need
 *   to be zero-terminated, since cbCount specifies the length of the string.
 * @param cbCount [in] Specifies the number of characters in the string.
 * @param lpDx [in] Long pointer to an optional array of values that indicate the distance between
 *   origins of adjacent character cells. For example, lpDx[i] logical units separate the origins of
 *   character cell i and character cell i + 1.
 *
 * @return Nonzero indicates that the string is drawn. Zero indicates failureTo get extended error
 *   information, call GetLastError.
 *
 * The current text-alignment settings for the specified DC determine how the reference point is
 * used to position the text.
 *
 * If the lpDx parameter is NULL, the ExtTextOut function uses the default spacing between
 * characters. The character-cell origins and the contents of the array pointed to by the lpDx
 * parameter are given in logical units. A character-cell origin is defined as the upper-left corner
 * of the character cell.
 *
 * By default, the current position is not used or updated by this function. However, an application
 * can call the SetTextAlign function with the fMode parameter set to TA_UPDATECP to permit the
 * system to use and update the current position each time the application calls ExtTextOut for a
 * specified DC. When this flag is set, the system ignores the X and Y parameters on subsequent
 * ExtTextOut calls.
 */
#define ExtTextOut              ExtTextOutW
/**
 * This function retrieves the number of characters in a specified string that will fit within a
 * specified space and fills an array with the text extent for each of those characters. A text
 * extent is the distance between the beginning of the space and a character that will fit in the
 * space.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszStr [in] Long pointer to the null-terminated string for which extents are to be
 *   retrieved.
 * @param cchString [in] Specifies the number of characters in the string pointed to by the lpszStr
 *   parameter.
 * @param nMaxExtent [in] Specifies the maximum allowable width, in logical units, of the formatted
 *   string.
 * @param lpnFit [out] Long pointer to an integer to receive a count of the maximum number of
 *   characters that will fit in the space specified by the nMaxExtent parameter. When the lpnFit
 *   parameter is NULL, the nMaxExtent parameter is ignored.
 * @param alpDx [out] Long pointer to an array of integers to receive partial string extents. Each
 *   element in the array gives the distance, in logical units, between the beginning of the string
 *   and one of the characters that fits in the space specified by the nMaxExtent parameter. Although
 *   this array should have at least as many elements as characters specified by the cchString
 *   parameter, the function fills the array with extents only for as many characters as are given by
 *   the lpnFit parameter. If alpDx is NULL, the function does not compute partial string widths.
 * @param lpSize [in] Long pointer to a SIZE structure that contains the dimensions of the string,
 *   in logical units when the function returns. This value cannot be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If both the lpnFit and alpDx parameters are NULL, calling the GetTextExtentExPoint function is
 * equivalent to calling the GetTextExtentPoint function.
 */
#define GetTextExtentExPoint    GetTextExtentExPointW
/**
 * This function fills the specified buffer with the metrics for the currently selected font.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lptm [out] Long pointer to the TEXTMETRIC structure that is to receive the metrics.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * For any given font, the text metric values in Windows CE will not necessarily match the text
 * metric values in Windows-based desktop platforms.
 */
#define GetTextMetrics          GetTextMetricsW
/**
 * This function removes the fonts in the specified file from the Windows CE font table.
 *
 * @param lpFileName [in] Long pointer to a null-terminated string that names a font resource file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * An application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the system. The
 * application sends this message by calling the SendMessage function with the hwnd parameter set to
 * HWND_BROADCAST.
 *
 * If there are outstanding references to a font, the associated resource remains loaded until no
 * device context (DC) is using it.
 */
#define RemoveFontResource      RemoveFontResourceW
#else
/**
 * This function adds the font resource from the specified file to the Windows font table. The font
 * can subsequently be used for text output by any Windows-based application.
 *
 * @param lpszFilename [in] Long pointer to a null-terminated string that contains a valid font file
 *   filename. The file name can specify a font resource file (.fon), a raw bitmap font file (.fnt), a
 *   raw TrueType file (.ttf), a TrueType resource file (.fot), or a TrueType collection file (.ttc).
 *
 * @return The number of fonts added indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * Any application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the operating
 * system. The application should send this message by calling the SendMessage function and setting
 * the hwnd parameter to HWND_BROADCAST.
 *
 * When an application no longer needs a font resource that it loaded by calling the AddFontResource
 * function, it must remove the resource by calling the RemoveFontResource function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type is chosen at system design time, and cannot be changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define AddFontResource         AddFontResourceA
/**
 * This function creates a logical font that has the characteristics specified in the specified
 * structure. The font can subsequently be selected as the current font for any device context (DC).
 *
 * @param lplf [in] Long pointer to a LOGFONT structure that defines the characteristics of the
 *   logical font.
 *
 * @return A handle to a logical font indicates success. NULL indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * The CreateFontIndirect function creates a logical font with the characteristics specified in the
 * LOGFONT structure. When this font is selected by using the SelectObject function, GDI's font
 * mapper attempts to match the logical font with an existing physical font. If it fails to find an
 * exact match, it provides an alternative whose characteristics match as many of the requested
 * characteristics as possible.
 *
 * When you no longer need the font, call the DeleteObject function to delete it.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define CreateFontIndirect      CreateFontIndirectA
/**
 * This function draws a character string by using the currently selected font. An optional
 * rectangle may be provided, to be used for clipping, opaquing, or both.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param X [in] Specifies the logical x-coordinate of the reference point used to position the
 *   string.
 * @param Y [in] Specifies the logical y-coordinate of the reference point used to position the
 *   string.
 * @param fuOptions [in] Specifies how to use the application-defined rectangle. This parameter can
 *   be a combination of the following values: Value Description ETO_CLIPPED The text will be clipped
 *   to the rectangle. ETO_OPAQUE The current background color should be used to fill the rectangle.
 * @param lprc [in] Long pointer to an optional RECT structure that specifies the dimensions of a
 *   rectangle that is used for clipping, opaquing, or both.
 * @param lpString [in] Long pointer to the character string to be drawn. The string does not need
 *   to be zero-terminated, since cbCount specifies the length of the string.
 * @param cbCount [in] Specifies the number of characters in the string.
 * @param lpDx [in] Long pointer to an optional array of values that indicate the distance between
 *   origins of adjacent character cells. For example, lpDx[i] logical units separate the origins of
 *   character cell i and character cell i + 1.
 *
 * @return Nonzero indicates that the string is drawn. Zero indicates failureTo get extended error
 *   information, call GetLastError.
 *
 * The current text-alignment settings for the specified DC determine how the reference point is
 * used to position the text.
 *
 * If the lpDx parameter is NULL, the ExtTextOut function uses the default spacing between
 * characters. The character-cell origins and the contents of the array pointed to by the lpDx
 * parameter are given in logical units. A character-cell origin is defined as the upper-left corner
 * of the character cell.
 *
 * By default, the current position is not used or updated by this function. However, an application
 * can call the SetTextAlign function with the fMode parameter set to TA_UPDATECP to permit the
 * system to use and update the current position each time the application calls ExtTextOut for a
 * specified DC. When this flag is set, the system ignores the X and Y parameters on subsequent
 * ExtTextOut calls.
 */
#define ExtTextOut              ExtTextOutA
/**
 * This function retrieves the number of characters in a specified string that will fit within a
 * specified space and fills an array with the text extent for each of those characters. A text
 * extent is the distance between the beginning of the space and a character that will fit in the
 * space.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszStr [in] Long pointer to the null-terminated string for which extents are to be
 *   retrieved.
 * @param cchString [in] Specifies the number of characters in the string pointed to by the lpszStr
 *   parameter.
 * @param nMaxExtent [in] Specifies the maximum allowable width, in logical units, of the formatted
 *   string.
 * @param lpnFit [out] Long pointer to an integer to receive a count of the maximum number of
 *   characters that will fit in the space specified by the nMaxExtent parameter. When the lpnFit
 *   parameter is NULL, the nMaxExtent parameter is ignored.
 * @param alpDx [out] Long pointer to an array of integers to receive partial string extents. Each
 *   element in the array gives the distance, in logical units, between the beginning of the string
 *   and one of the characters that fits in the space specified by the nMaxExtent parameter. Although
 *   this array should have at least as many elements as characters specified by the cchString
 *   parameter, the function fills the array with extents only for as many characters as are given by
 *   the lpnFit parameter. If alpDx is NULL, the function does not compute partial string widths.
 * @param lpSize [in] Long pointer to a SIZE structure that contains the dimensions of the string,
 *   in logical units when the function returns. This value cannot be NULL.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If both the lpnFit and alpDx parameters are NULL, calling the GetTextExtentExPoint function is
 * equivalent to calling the GetTextExtentPoint function.
 */
#define GetTextExtentExPoint    GetTextExtentExPointA
/**
 * This function fills the specified buffer with the metrics for the currently selected font.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lptm [out] Long pointer to the TEXTMETRIC structure that is to receive the metrics.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * For any given font, the text metric values in Windows CE will not necessarily match the text
 * metric values in Windows-based desktop platforms.
 */
#define GetTextMetrics          GetTextMetricsA
/**
 * This function removes the fonts in the specified file from the Windows CE font table.
 *
 * @param lpFileName [in] Long pointer to a null-terminated string that names a font resource file.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * An application that adds or removes fonts from the system font table should notify other windows
 * of the change by sending a WM_FONTCHANGE message to all top-level windows in the system. The
 * application sends this message by calling the SendMessage function with the hwnd parameter set to
 * HWND_BROADCAST.
 *
 * If there are outstanding references to a font, the associated resource remains loaded until no
 * device context (DC) is using it.
 */
#define RemoveFontResource      RemoveFontResourceA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDRWTXT
/* DrawText() Format Flags */
#define DT_TOP              0x00000000
#define DT_LEFT             0x00000000
#define DT_CENTER           0x00000001
#define DT_RIGHT            0x00000002
#define DT_VCENTER          0x00000004
#define DT_BOTTOM           0x00000008
#define DT_WORDBREAK        0x00000010
#define DT_SINGLELINE       0x00000020
#define DT_EXPANDTABS       0x00000040
#define DT_TABSTOP          0x00000080
#define DT_NOCLIP           0x00000100
#define DT_EXTERNALLEADING  0x00000200
#define DT_CALCRECT         0x00000400
#define DT_NOPREFIX         0x00000800
#define DT_INTERNAL         0x00001000

/**
 * This function draws formatted text in the specified rectangle. It formats the text according to
 * the specified format method.
 *
 * @param hDC [in] Handle to the device context.
 * @param lpString [in] Long pointer to the string to be drawn. If the nCount parameter is -1, the
 *   string must be null-terminated. If uFormat includes DT_MODIFYSTRING, the function could add up to
 *   four additional characters to this string. The buffer containing the string should be large
 *   enough to accommodate these extra characters.
 * @param nCount [in] Specifies the number of characters in the string. If nCount is -1, then the
 *   lpString parameter is assumed to be a pointer to a null-terminated string and DrawText computes
 *   the character count automatically.
 * @param lpRect [in] Long pointer to a RECT structure that contains the rectangle (in logical
 *   coordinates) in which the text is to be formatted.
 * @param uFormat [in] Specifies the method of formatting the text. It can be any combination of the
 *   following values: Value Description DT_BOTTOM Justifies the text to the bottom of the rectangle.
 *   This value must be combined with DT_SINGLELINE. DT_CALCRECT Determines the width and height of
 *   the rectangle. If there are multiple lines of text, DrawText uses the width of the rectangle
 *   pointed to by the lpRect parameter and extends the base of the rectangle to bound the last line
 *   of text. If there is only one line of text, DrawText modifies the right side of the rectangle so
 *   that it bounds the last character in the line. In either case, DrawText returns the height of the
 *   formatted text but does not draw the text. Before calling DrawText, an application must set the
 *   right and bottom members of the RECT structure pointed to by lpRect. These members are updated
 *   with the call to DrawText. DT_CENTER Centers text horizontally in the rectangle. DT_EDITCONTROL
 *   Duplicates the text-displaying characteristics of a multiline edit control. Specifically, the
 *   average character width is calculated in the same manner as for an edit control, and the function
 *   does not display a partially visible last line. DT_END_ELLIPSIS or DT_PATH_ELLIPSIS Replaces part
 *   of the given string with ellipses, if necessary, so that the result fits in the specified
 *   rectangle. The given string is not modified unless the DT_MODIFYSTRING flag is specified. You can
 *   specify DT_END_ELLIPSIS to replace characters at the end of the string, or DT_PATH_ELLIPSIS to
 *   replace characters in the middle of the string. If the string contains backslash (\) characters,
 *   DT_PATH_ELLIPSIS preserves as much as possible of the text after the last backslash.
 *   DT_EXPANDTABS Expands tab characters. The default number of characters per tab is eight. The
 *   DT_WORD_ELLIPSIS, DT_PATH_ELLIPSIS, and DT_END_ELLIPSIS values cannot be used with the
 *   DT_EXPANDTABS value. DT_INTERNAL Uses the system font to calculate text metrics. DT_LEFT Aligns
 *   text to the left. DT_MODIFYSTRING Modifies the given string to match the displayed text. This
 *   flag has no effect unless the DT_END_ELLIPSIS or DT_PATH_ELLIPSIS flag is specified. DT_NOCLIP
 *   Draws without clipping. DrawText is somewhat faster when DT_NOCLIP is used. DT_NOPREFIX Turns off
 *   processing of prefix characters. Normally, DrawText interprets the mnemonic-prefix character & as
 *   a directive to underscore the character that follows, and the mnemonic-prefix characters && as a
 *   directive to print a single &. By specifying DT_NOPREFIX, this processing is turned off. DT_RIGHT
 *   Aligns text to the right. DT_RTLREADING Layout in right to left reading order for bi-directional
 *   text when the font selected into the hdc is a Hebrew or Arabic font. The default reading order
 *   for all text is left to right. DT_SINGLELINE Displays text on a single line only. Carriage
 *   returns and linefeeds do not break the line. DT_TABSTOP Sets tab stops. Bits 15-8 (high-order
 *   byte of the low-order word) of the uFormat parameter specify the number of characters for each
 *   tab. The default number of characters per tab is eight. The DT_CALCRECT, DT_EXTERNALLEADING,
 *   DT_INTERNAL, DT_NOCLIP, and DT_NOPREFIX values cannot be used with the DT_TABSTOP value. DT_TOP
 *   Top-justifies text (single line only). DT_VCENTER Centers text vertically (requires DT_SINGLELINE
 *   flag). DT_WORDBREAK Breaks words. Lines are automatically broken between words if a word would
 *   extend past the edge of the rectangle specified by the lpRect parameter. A carriage
 *   return-linefeed sequence also breaks the line. DT_WORD_ELLIPSIS Truncates text that does not fit
 *   in the rectangle and adds ellipses.
 *
 * @return The height of the text indicates success. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The DrawText function uses the device context's selected font, text color, and background color
 * to draw the text. Unless the DT_NOCLIP format is used, DrawText clips the text so that it does
 * not appear outside the specified rectangle. All formatting is assumed to have multiple lines
 * unless the DT_SINGLELINE format is specified.
 *
 * If the selected font is too large for the specified rectangle, the DrawText function does not
 * attempt to substitute a smaller font.
 *
 * For Windows CE versions 2.10 and later, line breaking is supported for the Chinese, Korean, and
 * Japanese languages.
 */
WINUSERAPI int WINAPI DrawTextA(HDC,LPCSTR,int,RECT *,UINT);
/**
 * This function draws formatted text in the specified rectangle. It formats the text according to
 * the specified format method.
 *
 * @param hDC [in] Handle to the device context.
 * @param lpString [in] Long pointer to the string to be drawn. If the nCount parameter is -1, the
 *   string must be null-terminated. If uFormat includes DT_MODIFYSTRING, the function could add up to
 *   four additional characters to this string. The buffer containing the string should be large
 *   enough to accommodate these extra characters.
 * @param nCount [in] Specifies the number of characters in the string. If nCount is -1, then the
 *   lpString parameter is assumed to be a pointer to a null-terminated string and DrawText computes
 *   the character count automatically.
 * @param lpRect [in] Long pointer to a RECT structure that contains the rectangle (in logical
 *   coordinates) in which the text is to be formatted.
 * @param uFormat [in] Specifies the method of formatting the text. It can be any combination of the
 *   following values: Value Description DT_BOTTOM Justifies the text to the bottom of the rectangle.
 *   This value must be combined with DT_SINGLELINE. DT_CALCRECT Determines the width and height of
 *   the rectangle. If there are multiple lines of text, DrawText uses the width of the rectangle
 *   pointed to by the lpRect parameter and extends the base of the rectangle to bound the last line
 *   of text. If there is only one line of text, DrawText modifies the right side of the rectangle so
 *   that it bounds the last character in the line. In either case, DrawText returns the height of the
 *   formatted text but does not draw the text. Before calling DrawText, an application must set the
 *   right and bottom members of the RECT structure pointed to by lpRect. These members are updated
 *   with the call to DrawText. DT_CENTER Centers text horizontally in the rectangle. DT_EDITCONTROL
 *   Duplicates the text-displaying characteristics of a multiline edit control. Specifically, the
 *   average character width is calculated in the same manner as for an edit control, and the function
 *   does not display a partially visible last line. DT_END_ELLIPSIS or DT_PATH_ELLIPSIS Replaces part
 *   of the given string with ellipses, if necessary, so that the result fits in the specified
 *   rectangle. The given string is not modified unless the DT_MODIFYSTRING flag is specified. You can
 *   specify DT_END_ELLIPSIS to replace characters at the end of the string, or DT_PATH_ELLIPSIS to
 *   replace characters in the middle of the string. If the string contains backslash (\) characters,
 *   DT_PATH_ELLIPSIS preserves as much as possible of the text after the last backslash.
 *   DT_EXPANDTABS Expands tab characters. The default number of characters per tab is eight. The
 *   DT_WORD_ELLIPSIS, DT_PATH_ELLIPSIS, and DT_END_ELLIPSIS values cannot be used with the
 *   DT_EXPANDTABS value. DT_INTERNAL Uses the system font to calculate text metrics. DT_LEFT Aligns
 *   text to the left. DT_MODIFYSTRING Modifies the given string to match the displayed text. This
 *   flag has no effect unless the DT_END_ELLIPSIS or DT_PATH_ELLIPSIS flag is specified. DT_NOCLIP
 *   Draws without clipping. DrawText is somewhat faster when DT_NOCLIP is used. DT_NOPREFIX Turns off
 *   processing of prefix characters. Normally, DrawText interprets the mnemonic-prefix character & as
 *   a directive to underscore the character that follows, and the mnemonic-prefix characters && as a
 *   directive to print a single &. By specifying DT_NOPREFIX, this processing is turned off. DT_RIGHT
 *   Aligns text to the right. DT_RTLREADING Layout in right to left reading order for bi-directional
 *   text when the font selected into the hdc is a Hebrew or Arabic font. The default reading order
 *   for all text is left to right. DT_SINGLELINE Displays text on a single line only. Carriage
 *   returns and linefeeds do not break the line. DT_TABSTOP Sets tab stops. Bits 15-8 (high-order
 *   byte of the low-order word) of the uFormat parameter specify the number of characters for each
 *   tab. The default number of characters per tab is eight. The DT_CALCRECT, DT_EXTERNALLEADING,
 *   DT_INTERNAL, DT_NOCLIP, and DT_NOPREFIX values cannot be used with the DT_TABSTOP value. DT_TOP
 *   Top-justifies text (single line only). DT_VCENTER Centers text vertically (requires DT_SINGLELINE
 *   flag). DT_WORDBREAK Breaks words. Lines are automatically broken between words if a word would
 *   extend past the edge of the rectangle specified by the lpRect parameter. A carriage
 *   return-linefeed sequence also breaks the line. DT_WORD_ELLIPSIS Truncates text that does not fit
 *   in the rectangle and adds ellipses.
 *
 * @return The height of the text indicates success. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The DrawText function uses the device context's selected font, text color, and background color
 * to draw the text. Unless the DT_NOCLIP format is used, DrawText clips the text so that it does
 * not appear outside the specified rectangle. All formatting is assumed to have multiple lines
 * unless the DT_SINGLELINE format is specified.
 *
 * If the selected font is too large for the specified rectangle, the DrawText function does not
 * attempt to substitute a smaller font.
 *
 * For Windows CE versions 2.10 and later, line breaking is supported for the Chinese, Korean, and
 * Japanese languages.
 */
WINUSERAPI int WINAPI WINAPI DrawTextW(HDC,LPCWSTR,int,RECT *,UINT);

#ifdef UNICODE
/**
 * This function draws formatted text in the specified rectangle. It formats the text according to
 * the specified format method.
 *
 * @param hDC [in] Handle to the device context.
 * @param lpString [in] Long pointer to the string to be drawn. If the nCount parameter is -1, the
 *   string must be null-terminated. If uFormat includes DT_MODIFYSTRING, the function could add up to
 *   four additional characters to this string. The buffer containing the string should be large
 *   enough to accommodate these extra characters.
 * @param nCount [in] Specifies the number of characters in the string. If nCount is -1, then the
 *   lpString parameter is assumed to be a pointer to a null-terminated string and DrawText computes
 *   the character count automatically.
 * @param lpRect [in] Long pointer to a RECT structure that contains the rectangle (in logical
 *   coordinates) in which the text is to be formatted.
 * @param uFormat [in] Specifies the method of formatting the text. It can be any combination of the
 *   following values: Value Description DT_BOTTOM Justifies the text to the bottom of the rectangle.
 *   This value must be combined with DT_SINGLELINE. DT_CALCRECT Determines the width and height of
 *   the rectangle. If there are multiple lines of text, DrawText uses the width of the rectangle
 *   pointed to by the lpRect parameter and extends the base of the rectangle to bound the last line
 *   of text. If there is only one line of text, DrawText modifies the right side of the rectangle so
 *   that it bounds the last character in the line. In either case, DrawText returns the height of the
 *   formatted text but does not draw the text. Before calling DrawText, an application must set the
 *   right and bottom members of the RECT structure pointed to by lpRect. These members are updated
 *   with the call to DrawText. DT_CENTER Centers text horizontally in the rectangle. DT_EDITCONTROL
 *   Duplicates the text-displaying characteristics of a multiline edit control. Specifically, the
 *   average character width is calculated in the same manner as for an edit control, and the function
 *   does not display a partially visible last line. DT_END_ELLIPSIS or DT_PATH_ELLIPSIS Replaces part
 *   of the given string with ellipses, if necessary, so that the result fits in the specified
 *   rectangle. The given string is not modified unless the DT_MODIFYSTRING flag is specified. You can
 *   specify DT_END_ELLIPSIS to replace characters at the end of the string, or DT_PATH_ELLIPSIS to
 *   replace characters in the middle of the string. If the string contains backslash (\) characters,
 *   DT_PATH_ELLIPSIS preserves as much as possible of the text after the last backslash.
 *   DT_EXPANDTABS Expands tab characters. The default number of characters per tab is eight. The
 *   DT_WORD_ELLIPSIS, DT_PATH_ELLIPSIS, and DT_END_ELLIPSIS values cannot be used with the
 *   DT_EXPANDTABS value. DT_INTERNAL Uses the system font to calculate text metrics. DT_LEFT Aligns
 *   text to the left. DT_MODIFYSTRING Modifies the given string to match the displayed text. This
 *   flag has no effect unless the DT_END_ELLIPSIS or DT_PATH_ELLIPSIS flag is specified. DT_NOCLIP
 *   Draws without clipping. DrawText is somewhat faster when DT_NOCLIP is used. DT_NOPREFIX Turns off
 *   processing of prefix characters. Normally, DrawText interprets the mnemonic-prefix character & as
 *   a directive to underscore the character that follows, and the mnemonic-prefix characters && as a
 *   directive to print a single &. By specifying DT_NOPREFIX, this processing is turned off. DT_RIGHT
 *   Aligns text to the right. DT_RTLREADING Layout in right to left reading order for bi-directional
 *   text when the font selected into the hdc is a Hebrew or Arabic font. The default reading order
 *   for all text is left to right. DT_SINGLELINE Displays text on a single line only. Carriage
 *   returns and linefeeds do not break the line. DT_TABSTOP Sets tab stops. Bits 15-8 (high-order
 *   byte of the low-order word) of the uFormat parameter specify the number of characters for each
 *   tab. The default number of characters per tab is eight. The DT_CALCRECT, DT_EXTERNALLEADING,
 *   DT_INTERNAL, DT_NOCLIP, and DT_NOPREFIX values cannot be used with the DT_TABSTOP value. DT_TOP
 *   Top-justifies text (single line only). DT_VCENTER Centers text vertically (requires DT_SINGLELINE
 *   flag). DT_WORDBREAK Breaks words. Lines are automatically broken between words if a word would
 *   extend past the edge of the rectangle specified by the lpRect parameter. A carriage
 *   return-linefeed sequence also breaks the line. DT_WORD_ELLIPSIS Truncates text that does not fit
 *   in the rectangle and adds ellipses.
 *
 * @return The height of the text indicates success. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The DrawText function uses the device context's selected font, text color, and background color
 * to draw the text. Unless the DT_NOCLIP format is used, DrawText clips the text so that it does
 * not appear outside the specified rectangle. All formatting is assumed to have multiple lines
 * unless the DT_SINGLELINE format is specified.
 *
 * If the selected font is too large for the specified rectangle, the DrawText function does not
 * attempt to substitute a smaller font.
 *
 * For Windows CE versions 2.10 and later, line breaking is supported for the Chinese, Korean, and
 * Japanese languages.
 */
#define DrawText                DrawTextW
#else
/**
 * This function draws formatted text in the specified rectangle. It formats the text according to
 * the specified format method.
 *
 * @param hDC [in] Handle to the device context.
 * @param lpString [in] Long pointer to the string to be drawn. If the nCount parameter is -1, the
 *   string must be null-terminated. If uFormat includes DT_MODIFYSTRING, the function could add up to
 *   four additional characters to this string. The buffer containing the string should be large
 *   enough to accommodate these extra characters.
 * @param nCount [in] Specifies the number of characters in the string. If nCount is -1, then the
 *   lpString parameter is assumed to be a pointer to a null-terminated string and DrawText computes
 *   the character count automatically.
 * @param lpRect [in] Long pointer to a RECT structure that contains the rectangle (in logical
 *   coordinates) in which the text is to be formatted.
 * @param uFormat [in] Specifies the method of formatting the text. It can be any combination of the
 *   following values: Value Description DT_BOTTOM Justifies the text to the bottom of the rectangle.
 *   This value must be combined with DT_SINGLELINE. DT_CALCRECT Determines the width and height of
 *   the rectangle. If there are multiple lines of text, DrawText uses the width of the rectangle
 *   pointed to by the lpRect parameter and extends the base of the rectangle to bound the last line
 *   of text. If there is only one line of text, DrawText modifies the right side of the rectangle so
 *   that it bounds the last character in the line. In either case, DrawText returns the height of the
 *   formatted text but does not draw the text. Before calling DrawText, an application must set the
 *   right and bottom members of the RECT structure pointed to by lpRect. These members are updated
 *   with the call to DrawText. DT_CENTER Centers text horizontally in the rectangle. DT_EDITCONTROL
 *   Duplicates the text-displaying characteristics of a multiline edit control. Specifically, the
 *   average character width is calculated in the same manner as for an edit control, and the function
 *   does not display a partially visible last line. DT_END_ELLIPSIS or DT_PATH_ELLIPSIS Replaces part
 *   of the given string with ellipses, if necessary, so that the result fits in the specified
 *   rectangle. The given string is not modified unless the DT_MODIFYSTRING flag is specified. You can
 *   specify DT_END_ELLIPSIS to replace characters at the end of the string, or DT_PATH_ELLIPSIS to
 *   replace characters in the middle of the string. If the string contains backslash (\) characters,
 *   DT_PATH_ELLIPSIS preserves as much as possible of the text after the last backslash.
 *   DT_EXPANDTABS Expands tab characters. The default number of characters per tab is eight. The
 *   DT_WORD_ELLIPSIS, DT_PATH_ELLIPSIS, and DT_END_ELLIPSIS values cannot be used with the
 *   DT_EXPANDTABS value. DT_INTERNAL Uses the system font to calculate text metrics. DT_LEFT Aligns
 *   text to the left. DT_MODIFYSTRING Modifies the given string to match the displayed text. This
 *   flag has no effect unless the DT_END_ELLIPSIS or DT_PATH_ELLIPSIS flag is specified. DT_NOCLIP
 *   Draws without clipping. DrawText is somewhat faster when DT_NOCLIP is used. DT_NOPREFIX Turns off
 *   processing of prefix characters. Normally, DrawText interprets the mnemonic-prefix character & as
 *   a directive to underscore the character that follows, and the mnemonic-prefix characters && as a
 *   directive to print a single &. By specifying DT_NOPREFIX, this processing is turned off. DT_RIGHT
 *   Aligns text to the right. DT_RTLREADING Layout in right to left reading order for bi-directional
 *   text when the font selected into the hdc is a Hebrew or Arabic font. The default reading order
 *   for all text is left to right. DT_SINGLELINE Displays text on a single line only. Carriage
 *   returns and linefeeds do not break the line. DT_TABSTOP Sets tab stops. Bits 15-8 (high-order
 *   byte of the low-order word) of the uFormat parameter specify the number of characters for each
 *   tab. The default number of characters per tab is eight. The DT_CALCRECT, DT_EXTERNALLEADING,
 *   DT_INTERNAL, DT_NOCLIP, and DT_NOPREFIX values cannot be used with the DT_TABSTOP value. DT_TOP
 *   Top-justifies text (single line only). DT_VCENTER Centers text vertically (requires DT_SINGLELINE
 *   flag). DT_WORDBREAK Breaks words. Lines are automatically broken between words if a word would
 *   extend past the edge of the rectangle specified by the lpRect parameter. A carriage
 *   return-linefeed sequence also breaks the line. DT_WORD_ELLIPSIS Truncates text that does not fit
 *   in the rectangle and adds ellipses.
 *
 * @return The height of the text indicates success. Zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * The DrawText function uses the device context's selected font, text color, and background color
 * to draw the text. Unless the DT_NOCLIP format is used, DrawText clips the text so that it does
 * not appear outside the specified rectangle. All formatting is assumed to have multiple lines
 * unless the DT_SINGLELINE format is specified.
 *
 * If the selected font is too large for the specified rectangle, the DrawText function does not
 * attempt to substitute a smaller font.
 *
 * For Windows CE versions 2.10 and later, line breaking is supported for the Chinese, Korean, and
 * Japanese languages.
 */
#define DrawText                DrawTextA
#endif
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGTT || GWES_MGRAST2
#define LF_FULLFACESIZE     64
/**
 * This structure defines a font's attributes, full name, and style.
 */
typedef struct tagENUMLOGFONT
{
    /**
     * Specifies a LOGFONT structure that defines the attributes of a font.
     */
    LOGFONT   elfLogFont;
    /**
     * Specifies a unique name for the font. For example, "ABCD Font Company TrueType Bold Italic Sans
     * Serif".
     */
    TCHAR     elfFullName[LF_FULLFACESIZE];
    /**
     * Specifies the style of the font, for example, "Bold Italic".
     */
    TCHAR     elfStyle[LF_FACESIZE];
} ENUMLOGFONT, FAR* LPENUMLOGFONT;

typedef int (CALLBACK* FONTENUMPROC)(CONST LOGFONT *, CONST TEXTMETRIC *, DWORD, LPARAM);

/**
 * This function enumerates the fonts in a specified font family that are available on a specified
 * device. This function supersedes the EnumFonts function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszFamily [in] Long pointer to a null-terminated string that specifies the family name of
 *   the desired fonts. If lpszFamily is NULL, EnumFontFamilies randomly selects and enumerates one
 *   font of each available type family.
 * @param lpEnumFontFamProc [in] Long pointer to the procedure-instance address of the
 *   application-defined callback function. For information about the callback function, see
 *   EnumFontFamProc.
 * @param lParam [in] Pointer to application-supplied data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * For each font having the typeface name specified by the lpszFamily parameter, the
 * EnumFontFamilies function retrieves information about that font and passes it to the function
 * pointed to by the lpEnumFontFamProc parameter. The application-defined callback function can
 * process the font information as desired. Enumeration continues until there are no more fonts or
 * the callback function returns zero.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI EnumFontFamiliesA(HDC,LPCSTR,FONTENUMPROC,LPARAM);
/**
 * This function enumerates the fonts in a specified font family that are available on a specified
 * device. This function supersedes the EnumFonts function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszFamily [in] Long pointer to a null-terminated string that specifies the family name of
 *   the desired fonts. If lpszFamily is NULL, EnumFontFamilies randomly selects and enumerates one
 *   font of each available type family.
 * @param lpEnumFontFamProc [in] Long pointer to the procedure-instance address of the
 *   application-defined callback function. For information about the callback function, see
 *   EnumFontFamProc.
 * @param lParam [in] Pointer to application-supplied data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * For each font having the typeface name specified by the lpszFamily parameter, the
 * EnumFontFamilies function retrieves information about that font and passes it to the function
 * pointed to by the lpEnumFontFamProc parameter. The application-defined callback function can
 * process the font information as desired. Enumeration continues until there are no more fonts or
 * the callback function returns zero.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI EnumFontFamiliesW(HDC,LPCWSTR,FONTENUMPROC,LPARAM);
/**
 * This function enumerates the fonts available on a specified device. This function is provided for
 * compatibility with earlier versions of the Microsoft Platform SDK. Whenever possible,
 * applications should use the EnumFontFamilies function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpFaceName [in] Long pointer to a null-terminated string that specifies the typeface name
 *   of the desired fonts. If lpFaceName is NULL, EnumFonts randomly selects and enumerates one font
 *   of each available typeface.
 * @param lpFontFunc [in] Long pointer to the application-defined callback function. For more
 *   information, see EnumFontsProc.
 * @param lParam [in] Pointer to any application-defined data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * Use EnumFontFamiliesEx instead of EnumFonts. The EnumFontFamiliesEx function differs from the
 * EnumFonts function in that it retrieves the style names associated with a TrueType font. With
 * EnumFontFamiliesEx, you can retrieve information about font styles that cannot be enumerated
 * using the EnumFonts function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI EnumFontsA(HDC,LPCSTR,FONTENUMPROC,LPARAM);
/**
 * This function enumerates the fonts available on a specified device. This function is provided for
 * compatibility with earlier versions of the Microsoft Platform SDK. Whenever possible,
 * applications should use the EnumFontFamilies function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpFaceName [in] Long pointer to a null-terminated string that specifies the typeface name
 *   of the desired fonts. If lpFaceName is NULL, EnumFonts randomly selects and enumerates one font
 *   of each available typeface.
 * @param lpFontFunc [in] Long pointer to the application-defined callback function. For more
 *   information, see EnumFontsProc.
 * @param lParam [in] Pointer to any application-defined data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * Use EnumFontFamiliesEx instead of EnumFonts. The EnumFontFamiliesEx function differs from the
 * EnumFonts function in that it retrieves the style names associated with a TrueType font. With
 * EnumFontFamiliesEx, you can retrieve information about font styles that cannot be enumerated
 * using the EnumFonts function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
WINGDIAPI  int       WINAPI EnumFontsW(HDC,LPCWSTR,FONTENUMPROC,LPARAM);
/**
 * This function retrieves the typeface name of the font that is selected into the specified device
 * context (DC).
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param nCount [in] Specifies the size, in characters, of the buffer.
 * @param lpFaceName [out] Long pointer to the buffer that is to receive the typeface name. If this
 *   parameter is NULL, the function returns the number of characters in the name, including the
 *   terminating null character.
 *
 * @return The number of characters copied to the buffer indicates success. Zero indicates failure.
 *   To get extended error information, call GetLastError.
 *
 * The typeface name is copied as a null-terminated character string.
 *
 * If the name is longer than the number of characters specified by the nCount parameter, the name
 * is truncated.
 */
WINGDIAPI  int       WINAPI GetTextFaceA(HDC,int,LPSTR);
/**
 * This function retrieves the typeface name of the font that is selected into the specified device
 * context (DC).
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param nCount [in] Specifies the size, in characters, of the buffer.
 * @param lpFaceName [out] Long pointer to the buffer that is to receive the typeface name. If this
 *   parameter is NULL, the function returns the number of characters in the name, including the
 *   terminating null character.
 *
 * @return The number of characters copied to the buffer indicates success. Zero indicates failure.
 *   To get extended error information, call GetLastError.
 *
 * The typeface name is copied as a null-terminated character string.
 *
 * If the name is longer than the number of characters specified by the nCount parameter, the name
 * is truncated.
 */
WINGDIAPI  int       WINAPI GetTextFaceW(HDC,int,LPWSTR);

#ifdef UNICODE
/**
 * This function enumerates the fonts in a specified font family that are available on a specified
 * device. This function supersedes the EnumFonts function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszFamily [in] Long pointer to a null-terminated string that specifies the family name of
 *   the desired fonts. If lpszFamily is NULL, EnumFontFamilies randomly selects and enumerates one
 *   font of each available type family.
 * @param lpEnumFontFamProc [in] Long pointer to the procedure-instance address of the
 *   application-defined callback function. For information about the callback function, see
 *   EnumFontFamProc.
 * @param lParam [in] Pointer to application-supplied data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * For each font having the typeface name specified by the lpszFamily parameter, the
 * EnumFontFamilies function retrieves information about that font and passes it to the function
 * pointed to by the lpEnumFontFamProc parameter. The application-defined callback function can
 * process the font information as desired. Enumeration continues until there are no more fonts or
 * the callback function returns zero.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define EnumFontFamilies        EnumFontFamiliesW
/**
 * This function enumerates the fonts available on a specified device. This function is provided for
 * compatibility with earlier versions of the Microsoft Platform SDK. Whenever possible,
 * applications should use the EnumFontFamilies function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpFaceName [in] Long pointer to a null-terminated string that specifies the typeface name
 *   of the desired fonts. If lpFaceName is NULL, EnumFonts randomly selects and enumerates one font
 *   of each available typeface.
 * @param lpFontFunc [in] Long pointer to the application-defined callback function. For more
 *   information, see EnumFontsProc.
 * @param lParam [in] Pointer to any application-defined data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * Use EnumFontFamiliesEx instead of EnumFonts. The EnumFontFamiliesEx function differs from the
 * EnumFonts function in that it retrieves the style names associated with a TrueType font. With
 * EnumFontFamiliesEx, you can retrieve information about font styles that cannot be enumerated
 * using the EnumFonts function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define EnumFonts               EnumFontsW
/**
 * This function retrieves the typeface name of the font that is selected into the specified device
 * context (DC).
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param nCount [in] Specifies the size, in characters, of the buffer.
 * @param lpFaceName [out] Long pointer to the buffer that is to receive the typeface name. If this
 *   parameter is NULL, the function returns the number of characters in the name, including the
 *   terminating null character.
 *
 * @return The number of characters copied to the buffer indicates success. Zero indicates failure.
 *   To get extended error information, call GetLastError.
 *
 * The typeface name is copied as a null-terminated character string.
 *
 * If the name is longer than the number of characters specified by the nCount parameter, the name
 * is truncated.
 */
#define GetTextFace             GetTextFaceW
#else
/**
 * This function enumerates the fonts in a specified font family that are available on a specified
 * device. This function supersedes the EnumFonts function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpszFamily [in] Long pointer to a null-terminated string that specifies the family name of
 *   the desired fonts. If lpszFamily is NULL, EnumFontFamilies randomly selects and enumerates one
 *   font of each available type family.
 * @param lpEnumFontFamProc [in] Long pointer to the procedure-instance address of the
 *   application-defined callback function. For information about the callback function, see
 *   EnumFontFamProc.
 * @param lParam [in] Pointer to application-supplied data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * For each font having the typeface name specified by the lpszFamily parameter, the
 * EnumFontFamilies function retrieves information about that font and passes it to the function
 * pointed to by the lpEnumFontFamProc parameter. The application-defined callback function can
 * process the font information as desired. Enumeration continues until there are no more fonts or
 * the callback function returns zero.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define EnumFontFamilies        EnumFontFamiliesA
/**
 * This function enumerates the fonts available on a specified device. This function is provided for
 * compatibility with earlier versions of the Microsoft Platform SDK. Whenever possible,
 * applications should use the EnumFontFamilies function.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param lpFaceName [in] Long pointer to a null-terminated string that specifies the typeface name
 *   of the desired fonts. If lpFaceName is NULL, EnumFonts randomly selects and enumerates one font
 *   of each available typeface.
 * @param lpFontFunc [in] Long pointer to the application-defined callback function. For more
 *   information, see EnumFontsProc.
 * @param lParam [in] Pointer to any application-defined data. The data is passed to the callback
 *   function along with the font information.
 *
 * @return The return value is the last value returned by the callback function. Its meaning is
 *   defined by the application.
 *
 * Use EnumFontFamiliesEx instead of EnumFonts. The EnumFontFamiliesEx function differs from the
 * EnumFonts function in that it retrieves the style names associated with a TrueType font. With
 * EnumFontFamiliesEx, you can retrieve information about font styles that cannot be enumerated
 * using the EnumFonts function.
 *
 * Windows CE versions 2.0 and later support systems that use either TrueType or raster fonts but
 * not both. The font type (raster or TrueType) is chosen at system design time, and cannot be
 * changed by an application.
 *
 * Windows CE versions 1.0 and 1.01 support only raster fonts.
 */
#define EnumFonts               EnumFontsA
/**
 * This function retrieves the typeface name of the font that is selected into the specified device
 * context (DC).
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param nCount [in] Specifies the size, in characters, of the buffer.
 * @param lpFaceName [out] Long pointer to the buffer that is to receive the typeface name. If this
 *   parameter is NULL, the function returns the number of characters in the name, including the
 *   terminating null character.
 *
 * @return The number of characters copied to the buffer indicates success. Zero indicates failure.
 *   To get extended error information, call GetLastError.
 *
 * The typeface name is copied as a null-terminated character string.
 *
 * If the name is longer than the number of characters specified by the nCount parameter, the name
 * is truncated.
 */
#define GetTextFace             GetTextFaceA
#endif //UNICODE
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGTT
/**
 * This function enables or disables end-user-defined characters (EUDC).
 *
 * @param fEnableEUDC [in] Boolean that is set to TRUE to enable EUDC, and to FALSE to disable EUDC.
 *
 * @return TRUE indicates success. FALSE indicates failure.
 *
 * Enabling EUDC allows text output functions to retrieve information about end-user-defined
 * characters from EUDC fonts. Disabling EUDC prevents output functions from accessing these fonts.
 * By default, Windows CE enables EUDC fonts during GWES initialization.
 *
 * For Windows CE versions 2.01 and later, this function is supported in TrueType font and no longer
 * supported in raster font.
 */
WINGDIAPI  BOOL      WINAPI EnableEUDC(BOOL);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGTCI
/**
 * This structure contains information identifying the code pages and Unicode subranges for which a
 * specified font provides glyphs.
 *
 * The graphics device interface (GDI) relies on Windows code pages fitting within a 32-bit value.
 * Furthermore, the highest two bits within this value are reserved for GDI internal use and may not
 * be assigned to code pages.
 */
typedef struct tagFONTSIGNATURE
{
    /**
     * Specifies a 128-bit Unicode subset bitfield (USB) identifying up to 126 Unicode subranges. Each
     * bit, except the two most significant bits, represents a single subrange. The most significant bit
     * is always 1 and identifies the bitfield as a font signature; the second most significant bit is
     * reserved and must be 0. Unicode subranges are numbered in accordance with the ISO 10646 standard.
     */
    DWORD fsUsb[4];
    /**
     * Specifies a 64-bit code-page bitfield (CPB) that identifies a specific character set or code
     * page. Code pages are in the lower 32 bits of this bitfield. The high 32 are used for non-Windows
     * code pages.
     */
    DWORD fsCsb[2];
} FONTSIGNATURE, *PFONTSIGNATURE,FAR *LPFONTSIGNATURE;

/**
 * This structure contains information about a character set.
 */
typedef struct tagCHARSETINFO
{
    /**
     * Character set value.
     */
    UINT ciCharset;
    /**
     * ANSI code-page identifier.
     */
    UINT ciACP;
    /**
     * FONTSIGNATURE structure that identifies the Unicode and code-page font signature values.
     */
    FONTSIGNATURE fs;
} CHARSETINFO, *PCHARSETINFO, NEAR *NPCHARSETINFO, FAR *LPCHARSETINFO;

#define TCI_SRCCHARSET  1
#define TCI_SRCCODEPAGE 2
#define TCI_SRCFONTSIG  3

/**
 * This function translates based on the specified character set, code page, or font signature
 * value, setting all members of the destination structure to appropriate values.
 *
 * @param lpSrc [in] Either a long pointer to a code page bitfield or a value as defined by the
 *   dwFlags parameter. If dwFlags is TCI_SRCFONTSIG, this parameter is the address of the fsCsb
 *   member of a FONTSIGNATURE structure. Otherwise, this parameter is a 32-bit value.
 * @param lpCs [out] Long pointer to a CHARSETINFO structure that receives the translated character
 *   set information.
 * @param dwFlags [in] Specifies a bitmask of translation flags. It is one of the following values:
 *   Value Description TCI_SRCCHARSET Source contains the character set value in the low word, and
 *   zero in the high word. TCI_SRCCODEPAGE Source is a code-page identifier in the low word and zero
 *   in the high word. TCI_SRCFONTSIG Source is the code-page bitfield portion of a FONTSIGNATURE
 *   structure. On input, you set one bit. Choose from the ANSI range (bits 0-15), the combined ANSI
 *   and OEM range (bits 16-31), or the OEM range (bits 32-63). On output, the structure has only one
 *   bit set. If the TCI_SRCFONTSIG value is given, the lpSrc parameter must be the address of the
 *   code-page bit field. If any other TCI_* value is given, the lpSrc parameter must be a value not
 *   an address.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * OEM code pages are not supported.
 *
 * Character sets, code pages, and font signature bitmaps supported by Windows CE are listed in the
 * following table.
 *
 * Character Sets Code Pages Font Signature Bitmaps ANSI_CHARSET 1252 FS_LATIN1 SHIFTJIS_CHARSET 932
 * FS_JISJAPAN HANGEUL_CHARSET 949 FS_WANSUNG JOHAB_CHARSET 1361 FS_JOHAB GB2312_CHARSET 936
 * FS_CHINESESIMP CHINESEBIG5_CHARSET 950 FS_CHINESETRAD HEBREW_CHARSET 1255 FS_HEBREW
 * ARABIC_CHARSET 1256 FS_ARABIC GREEK_CHARSET 1253 FS_GREEK TURKISH_CHARSET 1254 FS_TURKISH
 * BALTIC_CHARSET 1257 FS_BALTIC EASTEUROPE_CHARSET 1250 FS_LATIN2 RUSSIAN_CHARSET 1251 FS_CYRILLIC
 * THAI_CHARSET 874 FS_THAI
 *
 * The table entries are ordered exactly as they are translated. For example, specifying lpSrc as
 * HANGEUL_CHARSET and dwFlags as TCI_SRCCHARSET fills CHARSETINFO with HANGEUL_CHARSET, code page
 * 949, and FS_WANSUNG. Specifying lpSrc as code page 936 and dwFlags as TCI_SRCCODEPAGE fills
 * CHARSETINFO with GB2312_CHARSET, code page 936, and FS_CHINESESIMP.
 *
 * On output, the fsUSB and fsCsb members of the FONTSIGNATURE structure-specified by the fs member
 * of the CHARSETINFO structure-are zero-filled before setting the returned code-page bitfield
 * value.
 */
WINGDIAPI   BOOL    WINAPI TranslateCharsetInfo(DWORD *, LPCHARSETINFO, DWORD dwFlags);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDIBSEC
#define DIB_RGB_COLORS      0 /* color table in RGBs */
#define DIB_PAL_COLORS      1 /* color table in palette indices */

/**
 * This structure contains information about a device-independent bitmap (DIB).
 */
typedef struct tagDIBSECTION {
    /**
     * Specifies a BITMAP data structure that contains information about the device-independent bitmap:
     * its type, dimensions, color capacities, and a pointer to its bit values.
     */
    BITMAP              dsBm;
    /**
     * Specifies a bitmap information header structure that contains information about the color format
     * of the DIB. Use the BITMAPINFOHEADER structure.
     */
    BITMAPINFOHEADER    dsBmih;
    /**
     * Specifies three DWORD color masks for the device-independent bitmap. This member is only valid
     * when the BitCount member of the BITMAP INFORMATION HEADER structure has a value greater than 8.
     * Each color mask indicates the bits within a DWORD used to encode one of the three color channels
     * (red, green, and blue).
     */
    DWORD               dsBitfields[3];
    /**
     * Contains a handle to the file mapping object that the CreateDIBSection function used to create
     * the device-independent bitmap. If CreateDIBSection was called with a NULL value for its hSection
     * parameter, causing the system to allocate memory for the bitmap, the dshSection member will be
     * NULL.
     */
    HANDLE              dshSection;
    /**
     * Specifies the offset to the bitmap's bit values within the file mapping object referenced by
     * dshSection. If dshSection is NULL, the dsOffset value has no meaning.
     */
    DWORD               dsOffset;
} DIBSECTION, FAR *LPDIBSECTION, *PDIBSECTION;

/**
 * This function creates a device-independent bitmap (DIB) that applications can write to directly.
 * The function returns a handle to the bitmap.
 *
 * @param hdc [in] Handle to a device context. If the value of iUsage is DIB_PAL_COLORS, the
 *   function uses this device context's logical palette to initialize the device-independent bitmap's
 *   colors.
 * @param pbmi [in] Pointer to a BITMAPINFO structure that specifies various attributes of the
 *   device-independent bitmap, including the bitmap's dimensions and colors.
 * @param iUsage [in] Specifies the type of data contained in the bmiColors array member of the
 *   BITMAPINFO structure pointed to by pbmi (either logical palette indexes or literal RGB values).
 *   The following values are defined: Value Description DIB_RGB_COLORS The BITMAPINFO structure
 *   contains an array of literal RGB values. Specify this value except when an 8 bpp bitmap is used.
 *   DIB_PAL_COLORS Specify this value when an 8 bbp bitmap is used. When DIB_PAL_COLORS is used, the
 *   system ignores the bmiColors member of the BITMAPINFO structure and the dwOffset parameter. Set
 *   dwOffset to zero and the hSection parameter to NULL.
 * @param ppvBits [in] Pointer to a variable that receives a pointer to the location of the
 *   device-independent bitmap's bit values.
 * @param hSection [in] Handle to a file mapping object that the function will use to create the
 *   device-independent bitmap. This parameter can be NULL. If hSection is not NULL, it must be a
 *   handle to a file mapping object created by calling the CreateFileMapping function with the
 *   PAGE_READWRITE or PAGE_WRITECOPY flag. Read-only DIB sections are not supported. Handles created
 *   by other means will cause CreateDIBSection to fail. If hSection is not NULL, the CreateDIBSection
 *   function locates the bitmap's bit values at offset dwOffset in the file mapping object referred
 *   to by hSection. An application can later retrieve the hSection handle by calling the GetObject
 *   function with the HBITMAP returned by CreateDIBSection. If hSection is NULL, the system allocates
 *   memory for the device-independent bitmap. In this case, the CreateDIBSection function ignores the
 *   dwOffset parameter. An application cannot later obtain a handle to this memory. The dshSection
 *   member of the DIBSECTION structure filled in by calling the GetObject function will be NULL.
 * @param dwOffset [in] Specifies the offset from the beginning of the file mapping object
 *   referenced by hSection where storage for the bitmap's bit values is to begin. This value is
 *   ignored if hSection is NULL. The bitmap's bit values are aligned on doubleword boundaries, so
 *   dwOffset must be a multiple of the size of a DWORD.
 *
 * @return A handle to the newly created device-independent bitmap indicates success, and *ppvBits
 *   points to the bitmap's bit values. NULL indicates failure, and *ppvBits is NULL. To get extended
 *   error information, call GetLastError.
 *
 * As noted above, if hSection is NULL, the system allocates memory for the device-independent
 * bitmap. The system closes the handle to that memory when you later delete the device-independent
 * bitmap by calling the DeleteObject function. If hSection is not NULL, you must close the hSection
 * memory handle yourself after calling DeleteObject to delete the bitmap.
 *
 * In Windows CE versions 2.0 and later, the BITMAPINFO structure must include a color table if the
 * images are palettized (usually 1,2,4, and 8 bpp formats). For 16 bpp or 32 bpp non-palettized
 * images, the color table must be three entries long; the entries must specify the values of the
 * red, green, and blue bitmasks. GDI ignores the color table for 24 bpp images; their pixels must
 * be stored in Blue-Green-Red (BGR) format.
 *
 * In Windows CE versions 1.0 and 1.01, the BITMAPINFO structure pointed to by the pbmi parameter
 * must specify 1 or 2 bits per pixel.
 */
WINGDIAPI  HBITMAP   WINAPI CreateDIBSection(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGDC
/**
 * This function restores a device context (DC) to the specified state. The device context is
 * restored by popping state information off a stack created by earlier calls to the SaveDC
 * function.
 *
 * @param hdc [in] Handle to the device context.
 * @param nSavedDC [in] Specifies the instance of the device context to be restored. If this
 *   parameter is positive, nSavedDC represents a specific instance of the device context to be
 *   restored. If this parameter is negative, nSavedDC represents an instance relative to the current
 *   device context. For example, -1 restores the most recently saved state.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * The stack can contain the state information for several instances of the device context. If the
 * state specified by the given parameter is not at the top of the stack, RestoreDC deletes all
 * state information between the top of the stack and the specified instance.
 */
WINGDIAPI BOOL WINAPI RestoreDC(HDC,int);
/**
 * This function saves the current state of the specified device context by copying data describing
 * selected objects and graphic modes (such as the bitmap, brush, palette, font, pen, region, and
 * drawing mode) to a context stack.
 *
 * @param hdc [in] Handle to the device context to be saved.
 *
 * @return If the function succeeds, the return value identifies the saved device context. If the
 *   function fails, the return value is zero. To get extended error information, call GetLastError.
 *
 * The SaveDC function can be used any number of times to save any number of instances of the device
 * context's state.
 *
 * A saved state can later be restored by using the RestoreDC function.
 */
WINGDIAPI int  WINAPI SaveDC(HDC);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGDC
/**
 * This function creates a device context (DC) for a device.
 *
 * @param lpszDriver [in] Long pointer to a null-terminated string that specifies the file name of a
 *   driver. If this parameter is set to NULL, the system returns a screen DC.
 * @param lpszDevice [in] Long pointer to a null-terminated string that specifies the name of the
 *   specific output device being used, as shown by the Print Manager (for example, "Epson FX-80"). It
 *   is not the printer model name. The lpszDevice parameter must be used. In Windows CE versions 2.0
 *   and 2.01, this parameter is ignored.
 * @param lpszOutput [in] Long pointer to an output destination. It can be one of the following
 *   values, and the colon is required when specifying a port. Value Description COMx: Serial ports; x
 *   is a number from 1 to 9. LPTx: Parallel ports; x is a number from 1 to 9. IRDA: IRDA port. For
 *   Windows CE versions 2.0 and 2.01, use COM3: to specify the IRDA port. \\servername\sharename
 *   Universal naming convention (UNC) that identifies a network printer server.
 * @param lpInitData [in] Long pointer to a DEVMODE structure containing device-specific
 *   initialization data for the device driver. The lpInitData parameter must be NULL if the device
 *   driver is to use the default initialization (if any) specified by the user.
 *
 * @return The handle to a device context for the specified device indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE passes the lpInitData and lpszOutput parameters to the driver without modification.
 * The lpszOutput parameter must contain a colon after the port-that is, use "LPT1:" or
 * "COM1:"-otherwise, the connection fails.
 *
 * When you no longer need the device context, call the DeleteDC function to delete it.
 */
WINGDIAPI HDC  WINAPI CreateDCA(LPCSTR, LPCSTR , LPCSTR , CONST DEVMODEA *);
/**
 * This function creates a device context (DC) for a device.
 *
 * @param lpszDriver [in] Long pointer to a null-terminated string that specifies the file name of a
 *   driver. If this parameter is set to NULL, the system returns a screen DC.
 * @param lpszDevice [in] Long pointer to a null-terminated string that specifies the name of the
 *   specific output device being used, as shown by the Print Manager (for example, "Epson FX-80"). It
 *   is not the printer model name. The lpszDevice parameter must be used. In Windows CE versions 2.0
 *   and 2.01, this parameter is ignored.
 * @param lpszOutput [in] Long pointer to an output destination. It can be one of the following
 *   values, and the colon is required when specifying a port. Value Description COMx: Serial ports; x
 *   is a number from 1 to 9. LPTx: Parallel ports; x is a number from 1 to 9. IRDA: IRDA port. For
 *   Windows CE versions 2.0 and 2.01, use COM3: to specify the IRDA port. \\servername\sharename
 *   Universal naming convention (UNC) that identifies a network printer server.
 * @param lpInitData [in] Long pointer to a DEVMODE structure containing device-specific
 *   initialization data for the device driver. The lpInitData parameter must be NULL if the device
 *   driver is to use the default initialization (if any) specified by the user.
 *
 * @return The handle to a device context for the specified device indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE passes the lpInitData and lpszOutput parameters to the driver without modification.
 * The lpszOutput parameter must contain a colon after the port-that is, use "LPT1:" or
 * "COM1:"-otherwise, the connection fails.
 *
 * When you no longer need the device context, call the DeleteDC function to delete it.
 */
WINGDIAPI HDC  WINAPI CreateDCW(LPCWSTR, LPCWSTR , LPCWSTR , CONST DEVMODEW *);

#ifdef UNICODE
/**
 * This function creates a device context (DC) for a device.
 *
 * @param lpszDriver [in] Long pointer to a null-terminated string that specifies the file name of a
 *   driver. If this parameter is set to NULL, the system returns a screen DC.
 * @param lpszDevice [in] Long pointer to a null-terminated string that specifies the name of the
 *   specific output device being used, as shown by the Print Manager (for example, "Epson FX-80"). It
 *   is not the printer model name. The lpszDevice parameter must be used. In Windows CE versions 2.0
 *   and 2.01, this parameter is ignored.
 * @param lpszOutput [in] Long pointer to an output destination. It can be one of the following
 *   values, and the colon is required when specifying a port. Value Description COMx: Serial ports; x
 *   is a number from 1 to 9. LPTx: Parallel ports; x is a number from 1 to 9. IRDA: IRDA port. For
 *   Windows CE versions 2.0 and 2.01, use COM3: to specify the IRDA port. \\servername\sharename
 *   Universal naming convention (UNC) that identifies a network printer server.
 * @param lpInitData [in] Long pointer to a DEVMODE structure containing device-specific
 *   initialization data for the device driver. The lpInitData parameter must be NULL if the device
 *   driver is to use the default initialization (if any) specified by the user.
 *
 * @return The handle to a device context for the specified device indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE passes the lpInitData and lpszOutput parameters to the driver without modification.
 * The lpszOutput parameter must contain a colon after the port-that is, use "LPT1:" or
 * "COM1:"-otherwise, the connection fails.
 *
 * When you no longer need the device context, call the DeleteDC function to delete it.
 */
#define CreateDC  CreateDCW
#else
/**
 * This function creates a device context (DC) for a device.
 *
 * @param lpszDriver [in] Long pointer to a null-terminated string that specifies the file name of a
 *   driver. If this parameter is set to NULL, the system returns a screen DC.
 * @param lpszDevice [in] Long pointer to a null-terminated string that specifies the name of the
 *   specific output device being used, as shown by the Print Manager (for example, "Epson FX-80"). It
 *   is not the printer model name. The lpszDevice parameter must be used. In Windows CE versions 2.0
 *   and 2.01, this parameter is ignored.
 * @param lpszOutput [in] Long pointer to an output destination. It can be one of the following
 *   values, and the colon is required when specifying a port. Value Description COMx: Serial ports; x
 *   is a number from 1 to 9. LPTx: Parallel ports; x is a number from 1 to 9. IRDA: IRDA port. For
 *   Windows CE versions 2.0 and 2.01, use COM3: to specify the IRDA port. \\servername\sharename
 *   Universal naming convention (UNC) that identifies a network printer server.
 * @param lpInitData [in] Long pointer to a DEVMODE structure containing device-specific
 *   initialization data for the device driver. The lpInitData parameter must be NULL if the device
 *   driver is to use the default initialization (if any) specified by the user.
 *
 * @return The handle to a device context for the specified device indicates success. NULL indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Windows CE passes the lpInitData and lpszOutput parameters to the driver without modification.
 * The lpszOutput parameter must contain a colon after the port-that is, use "LPT1:" or
 * "COM1:"-otherwise, the connection fails.
 *
 * When you no longer need the device context, call the DeleteDC function to delete it.
 */
#define CreateDC  CreateDCA
#endif // !UNICODE
// @CESYSGEN ENDIF




// @CESYSGEN IF GWES_MGPAL
/**
 * This function creates a logical color palette.
 *
 * @param lplgpl [in] Long pointer to a LOGPALETTE structure that contains information about the
 *   colors in the logical palette.
 *
 * @return A handle that identifies a logical palette indicates success. NULL indicates failure. To
 *   get extended error information, call GetLastError.
 *
 * An application can determine whether a device supports palette operations by calling the
 * GetDeviceCaps function and specifying the RASTERCAPS constant.
 *
 * Once an application creates a logical palette, it can select that palette into a device context
 * by calling the SelectPalette function. A palette selected into a device context can be realized
 * by calling the RealizePalette function.
 *
 * When you no longer need the palette, call the DeleteObject function to delete it.
 *
 * Because Windows CE does not arbitrate between the palettes of the foreground and background
 * applications, palettes are not automatically padded with Windows systems colors. Therefore, the
 * number of color entries in the palette created by this function is always the same as the
 * palNumEntries member of the LOGPALETTE structure.
 */
WINGDIAPI HPALETTE WINAPI CreatePalette(CONST LOGPALETTE *);
/**
 * This function retrieves the index for the entry in the specified logical palette that most
 * closely matches a specified color value.
 *
 * @param hpal [in] Handle to a logical color palette.
 * @param crColor [in] Specifies a color to be matched.
 *
 * @return The index of an entry in a logical palette indicates success. CLR_INVALID indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * An application can determine whether a device supports palette operations by calling the
 * GetDeviceCaps function and specifying the RASTERCAPS constant.
 *
 * If the given logical palette contains entries with the PC_EXPLICIT flag set, the return value is
 * undefined.
 */
WINGDIAPI UINT     WINAPI GetNearestPaletteIndex(HPALETTE, COLORREF);
/**
 * This function retrieves a specified range of palette entries from the specified logical palette.
 *
 * @param hpal [in] Handle to the logical color palette.
 * @param iStartIndex [in] Index of the first entry in the logical palette to be retrieved.
 *   GetPaletteEntries fails if iStartIndex is greater than the number of palette entries.
 * @param nEntries [in] Specifies the number of entries in the logical palette to be retrieved.
 * @param lppe [out] Long pointer to an array of PALETTEENTRY structures to receive the palette
 *   entries. The array must contain at least as many structures as specified by the nEntries
 *   parameter.
 *
 * @return If the handle of the logical color palette is a valid pointer-not NULL-the number of
 *   entries retrieved from the logical palette indicates success. If the handle of the logical color
 *   palette is NULL, the number of entries in the specified palette indicates success. Zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * An application can determine whether a device supports palette operations by calling the
 * GetDeviceCaps function and specifying the RASTERCAPS constant.
 *
 * If the nEntries parameter specifies more entries than exist in the palette, the remaining members
 * of the PALETTEENTRY structure are not altered.
 */
WINGDIAPI UINT     WINAPI GetPaletteEntries(HPALETTE, UINT, UINT, LPPALETTEENTRY);
/**
 * This function retrieves a range of palette entries from the system palette associated with the
 * specified device context.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param iStartIndex [in] Index of the first entry to be retrieved from the system palette.
 * @param nEntries [in] Specifies the number of entries to be retrieved from the system palette.
 * @param lppe [out] Long pointer to an array of PALETTEENTRY structures to receive the palette
 *   entries. The array must contain at least as many structures as specified by the nEntries
 *   parameter. If this parameter is NULL, the function returns the total number of entries in the
 *   palette.
 *
 * @return The number of entries retrieved from the palette indicates success. Zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * GetSystemPaletteEntries fails if the device associated with hdc does not have a settable palette.
 * Call the GetDeviceCaps function, specifying the RASTERCAPS constant, to determine if the device
 * has a settable palette before calling GetSystemPaletteEntries.
 */
WINGDIAPI UINT     WINAPI GetSystemPaletteEntries(HDC, UINT, UINT, LPPALETTEENTRY);
/**
 * This function maps palette entries from the current logical palette to the system palette.
 *
 * @param hdc [in] Handle to the device context (DC) into which a logical palette has been selected.
 *
 * @return The number of entries in the logical palette mapped to the system palette indicates
 *   success. GDI_ERROR indicates failure. To get extended error information, call GetLastError.
 *
 * RealizePalette fails if the device associated with hdc does not have a settable palette. Call the
 * GetDeviceCaps function, specifying the RASTERCAPS constant, to determine if the device has a
 * settable palette before calling RealizePalette.
 *
 * RealizePalette modifies the palette for the device associated with the specified device context.
 * If the device context is a memory DC, the color table for the bitmap selected into the DC is
 * modified. If the device context is a display DC, the physical palette for that device is
 * modified.
 *
 * A logical color palette is a buffer between color-intensive applications and the system, allowing
 * these applications to use as many colors as needed without interfering with colors displayed by
 * other windows.
 *
 * When an application's window has the focus and it calls RealizePalette, the system attempts to
 * realize as many of the requested colors as possible. The same is also true for applications with
 * inactive windows.
 *
 * Windows CE does not arbitrate between the palettes of the background and foreground applications.
 * The foreground application has complete control of the system palette. Therefore, Windows CE does
 * not perform any color matching operations for foreground applications; it simply overwrites the
 * system palette entries with the hdc parameter's palette entries.
 *
 * Windows CE does not support RealizePalette for background applications.
 */
WINGDIAPI UINT     WINAPI RealizePalette(HDC);
/**
 * This function selects the specified logical palette into a device context.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param hpal [in] Handle to the logical palette to be selected.
 * @param bForceBackground [in] Ignored. Because Windows CE does not arbitrate between the palettes
 *   of the foreground and background applications, Windows CE ignores this parameter and always
 *   treats it as FALSE. This causes the logical palette to be copied into the device palette when the
 *   application is in the foreground.
 *
 * @return A handle that identifies the device context's previous logical palette indicates success.
 *   NULL indicates failure. To get extended error information, call GetLastError.
 *
 * An application can determine whether a device supports palette operations by calling the
 * GetDeviceCaps function and specifying the RASTERCAPS constant.
 *
 * An application can select a logical palette into more than one device context. However, changes
 * to a logical palette will affect all device contexts for which it is selected.
 */
WINGDIAPI HPALETTE WINAPI SelectPalette(HDC, HPALETTE, BOOL);
/**
 * This function sets RGB (red, green and blue) color values and flags in a range of entries in a
 * logical palette.
 *
 * @param hpal [in] Handle to the logical palette.
 * @param iStart [in] Specifies the first logical-palette entry to be set. This function fails if
 *   iStart is greater than the number of palette entries.
 * @param cEntries [in] Specifies the number of logical-palette entries to be set.
 * @param lppe [in] Long pointer to the first member of an array of PALETTEENTRY structures
 *   containing the RGB values and flags.
 *
 * @return The number of entries that were set in the logical palette indicates success. Zero
 *   indicates failure. To get extended error information, call GetLastError.
 *
 * An application can determine whether or not a device supports palette operations by calling the
 * GetDeviceCaps function and specifying the RASTERCAPS constant.
 *
 * Even if a logical palette has been selected and realized, changes to the palette do not affect
 * the physical palette in the surface. RealizePalette must be called again to set the new logical
 * palette into the surface.
 */
WINGDIAPI UINT     WINAPI SetPaletteEntries(HPALETTE, UINT, UINT, CONST PALETTEENTRY *);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_PGDI || GWES_MGPAL
/**
 * This function returns the system palette color that will be displayed when the specified color
 * value is used.
 *
 * @param hdc [in] Handle to the device context (DC).
 * @param crColor [in] Specifies a color value that identifies a requested color.
 *
 * @return If the function succeeds, the return value identifies a color from the system palette
 *   that corresponds to the specified color value. If the function fails, the return value is
 *   CLR_INVALID. To get extended error information, call GetLastError.
 *
 * The GetNearestColor function returns the color from the selected device context that most closely
 * matches the specified color value.
 */
WINGDIAPI COLORREF WINAPI GetNearestColor(HDC, COLORREF);
// @CESYSGEN ENDIF


// @CESYSGEN IF GWES_MGPRINT
/* Spooler Error Codes */
#define SP_ERROR                     (-1)

#ifdef STRICT
typedef BOOL (CALLBACK* ABORTPROC)(HDC, int);
#else
typedef FARPROC ABORTPROC;
#endif

/**
 * This structure contains the information necessary for printing documents.
 */
typedef struct _DOCINFOA {
    /**
     * Specifies the structure size, in bytes.
     */
    int     cbSize;
    /**
     * Long pointer to a null-terminated string that specifies the name of the document.
     */
    LPCSTR   lpszDocName;
    /**
     * Long pointer to a null-terminated string that specifies the name of an output file. If this
     * pointer is NULL, the output will be sent to the device identified by the device context handle
     * that was passed to the StartDoc function.
     */
    LPCSTR   lpszOutput;
    /**
     * Unsupported; set to zero.
     */
    LPCSTR   lpszDatatype;
    /**
     * Unsupported; set to zero.
     */
    DWORD    fwType;
} DOCINFOA, *LPDOCINFOA;

/**
 * This structure contains the information necessary for printing documents.
 */
typedef struct _DOCINFOW {
    /**
     * Specifies the structure size, in bytes.
     */
    int     cbSize;
    /**
     * Long pointer to a null-terminated string that specifies the name of the document.
     */
    LPCWSTR  lpszDocName;
    /**
     * Long pointer to a null-terminated string that specifies the name of an output file. If this
     * pointer is NULL, the output will be sent to the device identified by the device context handle
     * that was passed to the StartDoc function.
     */
    LPCWSTR  lpszOutput;
    /**
     * Unsupported; set to zero.
     */
    LPCWSTR  lpszDatatype;
    /**
     * Unsupported; set to zero.
     */
    DWORD    fwType;
} DOCINFOW, *LPDOCINFOW;

#ifdef UNICODE
typedef DOCINFOW DOCINFO;
typedef LPDOCINFOW LPDOCINFO;
#else
typedef DOCINFOA DOCINFO;
typedef LPDOCINFOA LPDOCINFO;
#endif // UNICODE

/**
 * This function stops the current print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 *
 * @return A value greater than zero indicates success. SP_ERROR indicates failure. To get extended
 *   error information, call GetLastError.
 *
 * Applications should call the AbortDoc function to stop a print job if an error occurs, or to stop
 * a print job after the user cancels that job. To end a successful print job, an application should
 * call the EndDoc function.
 *
 * If Print Manager was used to start the print job, calling AbortDoc erases the entire spool job,
 * so that the printer receives nothing. If Print Manager was not used to start the print job, the
 * data may already have been sent to the printer. In this case, the printer driver resets the
 * printer (when possible) and ends the print job.
 */
WINGDIAPI int WINAPI AbortDoc(HDC);
/**
 * This function ends a print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 *
 * @return A value greater than zero indicates success. A value less than or equal to zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * Applications should call EndDoc immediately after finishing a print job.
 */
WINGDIAPI int WINAPI EndDoc(HDC);
/**
 * This function informs the device that the application has finished writing to a page. This
 * function is typically used to direct the device driver to advance to a new page.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 *
 * @return A value greater than zero indicates success. A value less than or equal to zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * For Windows CE versions 1.0 through 2.01, the device context attributes are not retained between
 * a call to EndPage and a call StartPage. You must reselect objects and set up the mapping mode
 * again before printing the next page.
 *
 * For Windows CE versions 2.10 and later, neither EndPage or StartPage resets the device context
 * attributes. Device context attributes remain constant across subsequent pages. You do not need to
 * reselect objects and set up the mapping mode again before printing the next page; however, doing
 * so produces identical printer output and is compatible with earlier versions of Windows CE.
 */
WINGDIAPI int WINAPI EndPage(HDC);
/**
 * This function sets the application-defined function that allows a print job to be canceled during
 * printing.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 * @param lpAbortProc [in] Long pointer to the application-defined abort function.
 *
 * @return A value greater than zero indicates success. SP_ERROR indicates failure. To get extended
 *   error information, call GetLastError.
 */
WINGDIAPI int WINAPI SetAbortProc(HDC, ABORTPROC);
/**
 * This function starts a print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 * @param lpdi [in] Long pointer to a DOCINFO structure that contains the name of the document file
 *   and the name of the output file.
 *
 * @return A value greater than zero indicates success. This value is the print job identifier for
 *   the document. A value less than or equal to zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * Applications should call the StartDoc function immediately before beginning a print job. Using
 * this function ensures that multipage documents are not interspersed with other print jobs.
 *
 * Windows CE does not support printing to files. It ignores the lpszOutput member of the DOCINFO
 * structure.
 */
WINGDIAPI int WINAPI StartDocA(HDC, CONST DOCINFOA *);
/**
 * This function starts a print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 * @param lpdi [in] Long pointer to a DOCINFO structure that contains the name of the document file
 *   and the name of the output file.
 *
 * @return A value greater than zero indicates success. This value is the print job identifier for
 *   the document. A value less than or equal to zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * Applications should call the StartDoc function immediately before beginning a print job. Using
 * this function ensures that multipage documents are not interspersed with other print jobs.
 *
 * Windows CE does not support printing to files. It ignores the lpszOutput member of the DOCINFO
 * structure.
 */
WINGDIAPI int WINAPI StartDocW(HDC, CONST DOCINFOW *);
/**
 * This function prepares the printer driver to accept data.
 *
 * @param hDC [in] Handle to the device context (DC) for the print job.
 *
 * @return A value greater than zero indicates success. A value less than or equal to zero indicates
 *   failure. To get extended error information, call GetLastError.
 *
 * The system disables the ResetDC function between calls to the StartPage and EndPage functions.
 * This means that you cannot change the device mode except at page boundaries. After calling
 * EndPage, you can call ResetDC to change the device mode, if necessary. A call to ResetDC resets
 * all device context attributes back to default values.
 *
 * For Windows CE versions 1.0 through 2.01, the device context attributes are not retained between
 * a call to EndPage and a call. You must reselect objects and set up the mapping mode again before
 * printing the next page.
 *
 * For Windows CE versions 2.10 and later, neither EndPage or StartPage resets the device context
 * attributes. Device context attributes remain constant across subsequent pages. You do not need to
 * re-select objects and set up the mapping mode again before printing the next page; however, doing
 * so produces identical printer output and is compatible with earlier versions of Windows CE.
 */
WINGDIAPI int WINAPI StartPage(HDC);

#ifdef UNICODE
/**
 * This function starts a print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 * @param lpdi [in] Long pointer to a DOCINFO structure that contains the name of the document file
 *   and the name of the output file.
 *
 * @return A value greater than zero indicates success. This value is the print job identifier for
 *   the document. A value less than or equal to zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * Applications should call the StartDoc function immediately before beginning a print job. Using
 * this function ensures that multipage documents are not interspersed with other print jobs.
 *
 * Windows CE does not support printing to files. It ignores the lpszOutput member of the DOCINFO
 * structure.
 */
#define StartDoc  StartDocW
#else
/**
 * This function starts a print job.
 *
 * @param hdc [in] Handle to the device context (DC) for the print job.
 * @param lpdi [in] Long pointer to a DOCINFO structure that contains the name of the document file
 *   and the name of the output file.
 *
 * @return A value greater than zero indicates success. This value is the print job identifier for
 *   the document. A value less than or equal to zero indicates failure. To get extended error
 *   information, call GetLastError.
 *
 * Applications should call the StartDoc function immediately before beginning a print job. Using
 * this function ensures that multipage documents are not interspersed with other print jobs.
 *
 * Windows CE does not support printing to files. It ignores the lpszOutput member of the DOCINFO
 * structure.
 */
#define StartDoc  StartDocA
#endif // !UNICODE
// @CESYSGEN ENDIF

#ifdef UNDER_NT
            int         WINAPI MulDiv(int,int,int);
WINGDIAPI	int			WINAPI SetMapMode(HDC, int);
WINGDIAPI	BOOL		WINAPI SetViewportExtEx(HDC, int, int, LPSIZE);
/**
 * This function sets the viewpoint origin of a device context to the specified coordinates.
 *
 * @param hdc [in] Handle to the device context.
 * @param X [in] Specifies the x-coordinate, in device units, of the new viewport origin.
 * @param Y [in] Specifies the y-coordinate, in device units, of the new viewport origin.
 * @param lpPoint [in] Long pointer to a POINT structure. The previous viewport origin (in device
 *   coordinates) is placed in this structure. If lpPoint is NULL, nothing is returned.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 */
WINGDIAPI	BOOL		WINAPI SetViewportOrgEx(HDC, int, int, LPPOINT);
WINGDIAPI	int			WINAPI GetDIBits(HDC, HBITMAP, UINT, UINT, LPVOID, LPBITMAPINFO, UINT);
WINGDIAPI	LONG		WINAPI GetBitmapBits(HBITMAP, LONG, LPVOID);
WINGDIAPI	UINT		WINAPI GetDIBColorTable(HDC, UINT, UINT, RGBQUAD *);
WINGDIAPI	int			WINAPI StretchDIBits(HDC, int, int, int, int, int, int, int, 
								int, CONST VOID *, CONST BITMAPINFO *, UINT, DWORD);
WINGDIAPI	BOOL		WINAPI SetWindowExtEx(HDC, int, int, LPSIZE);
WINGDIAPI	BOOL		WINAPI SetWindowOrgEx(HDC, int, int, LPPOINT);
WINGDIAPI	int			WINAPI SetStretchBltMode(HDC, int);

#define COLORONCOLOR   3
#define MM_ANISOTROPIC 8
#endif // UNDER_NT


#ifdef __cplusplus
}
#endif


#ifdef WINCEOEM
#include <pwingdi.h>	// internal defines 
#ifndef GDI_SERVER
#ifdef WINCEMACRO
#include <mwingdi.h> 	// macro defines
#endif
#endif
#endif


#endif /* _WINGDI_H_ */
