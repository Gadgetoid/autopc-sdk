/**************************************************************************
*                                                                         *
* winnls.h -- NLS procedure declarations, constant definitions and macros *
*                                                                         *
* Copyright (c) 1991-1995, Microsoft Corp. All rights reserved.           *
*                                                                         *
**************************************************************************/


#ifndef _WINNLS_
#define _WINNLS_

// @CESYSGEN IF COREDLL_CORELOC

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NONLS

/***************************************************************************\
* Constants
*
* Define all constants for the NLS component here.
\***************************************************************************/

/*
 *  String Length Maximums.
 */
#define MAX_LEADBYTES        12             /* 5 ranges, 2 bytes ea., 0 term. */
#define MAX_DEFAULTCHAR      2              /* single or double byte */

/*
 *  MBCS and Unicode Translation Flags.
 */
#define MB_PRECOMPOSED       0x00000001     /* use precomposed chars */
#define MB_COMPOSITE         0x00000002     /* use composite chars */
#define MB_USEGLYPHCHARS     0x00000004     /* use glyph chars, not ctrl chars */
#define MB_ERR_INVALID_CHARS 0x00000008     /* error for invalid chars */

#define WC_DEFAULTCHECK      0x00000100     /* check for default char */
#define WC_COMPOSITECHECK    0x00000200     /* convert composite to precomposed */
#define WC_DISCARDNS         0x00000010     /* discard non-spacing chars */
#define WC_SEPCHARS          0x00000020     /* generate separate chars */
#define WC_DEFAULTCHAR       0x00000040     /* replace w/ default char */

/*
 *  Character Type Flags.
 */
#define CT_CTYPE1            0x00000001     /* ctype 1 information */
#define CT_CTYPE2            0x00000002     /* ctype 2 information */
#define CT_CTYPE3            0x00000004     /* ctype 3 information */

/*
 *  CType 1 Flag Bits.
 */
#define C1_UPPER             0x0001         /* upper case */
#define C1_LOWER             0x0002         /* lower case */
#define C1_DIGIT             0x0004         /* decimal digits */
#define C1_SPACE             0x0008         /* spacing characters */
#define C1_PUNCT             0x0010         /* punctuation characters */
#define C1_CNTRL             0x0020         /* control characters */
#define C1_BLANK             0x0040         /* blank characters */
#define C1_XDIGIT            0x0080         /* other digits */
#define C1_ALPHA             0x0100         /* any linguistic character */

/*
 *  CType 2 Flag Bits.
 */
#define C2_LEFTTORIGHT       0x0001         /* left to right */
#define C2_RIGHTTOLEFT       0x0002         /* right to left */

#define C2_EUROPENUMBER      0x0003         /* European number, digit */
#define C2_EUROPESEPARATOR   0x0004         /* European numeric separator */
#define C2_EUROPETERMINATOR  0x0005         /* European numeric terminator */
#define C2_ARABICNUMBER      0x0006         /* Arabic number */
#define C2_COMMONSEPARATOR   0x0007         /* common numeric separator */

#define C2_BLOCKSEPARATOR    0x0008         /* block separator */
#define C2_SEGMENTSEPARATOR  0x0009         /* segment separator */
#define C2_WHITESPACE        0x000A         /* white space */
#define C2_OTHERNEUTRAL      0x000B         /* other neutrals */

#define C2_NOTAPPLICABLE     0x0000         /* no implicit directionality */

/*
 *  CType 3 Flag Bits.
 */
#define C3_NONSPACING        0x0001         /* nonspacing character */
#define C3_DIACRITIC         0x0002         /* diacritic mark */
#define C3_VOWELMARK         0x0004         /* vowel mark */
#define C3_SYMBOL            0x0008         /* symbols */

#define C3_KATAKANA          0x0010         /* katakana character */
#define C3_HIRAGANA          0x0020         /* hiragana character */
#define C3_HALFWIDTH         0x0040         /* half width character */
#define C3_FULLWIDTH         0x0080         /* full width character */
#define C3_IDEOGRAPH         0x0100         /* ideographic character */
#define C3_KASHIDA           0x0200         /* Arabic kashida character */
#define C3_LEXICAL           0x0400         /* lexical character */

#define C3_ALPHA             0x8000         /* any linguistic char (C1_ALPHA) */

#define C3_NOTAPPLICABLE     0x0000         /* ctype 3 is not applicable */

/*
 *  String Flags.
 */
#define NORM_IGNORECASE         0x00000001  /* ignore case */
#define NORM_IGNORENONSPACE     0x00000002  /* ignore nonspacing chars */
#define NORM_IGNORESYMBOLS      0x00000004  /* ignore symbols */

#define NORM_IGNOREKANATYPE     0x00010000  /* ignore kanatype */
#define NORM_IGNOREWIDTH        0x00020000  /* ignore width */

/*
 *  Locale Independent Mapping Flags.
 */
#define MAP_FOLDCZONE           0x00000010  /* fold compatibility zone chars */
#define MAP_PRECOMPOSED         0x00000020  /* convert to precomposed chars */
#define MAP_COMPOSITE           0x00000040  /* convert to composite chars */
#define MAP_FOLDDIGITS          0x00000080  /* all digits to ASCII 0-9 */

/*
 *  Locale Dependent Mapping Flags.
 */
#define LCMAP_LOWERCASE         0x00000100  /* lower case letters */
#define LCMAP_UPPERCASE         0x00000200  /* upper case letters */
#define LCMAP_SORTKEY           0x00000400  /* WC sort key (normalize) */
#define LCMAP_BYTEREV           0x00000800  /* byte reversal */

#define LCMAP_HIRAGANA          0x00100000  /* map katakana to hiragana */
#define LCMAP_KATAKANA          0x00200000  /* map hiragana to katakana */
#define LCMAP_HALFWIDTH         0x00400000  /* map double byte to single byte */
#define LCMAP_FULLWIDTH         0x00800000  /* map single byte to double byte */

/*
 *  Locale Enumeration Flags.
 */
#define LCID_INSTALLED          0x00000001  /* installed locale ids */
#define LCID_SUPPORTED          0x00000002  /* supported locale ids */

/*
 *  Code Page Enumeration Flags.
 */
#define CP_INSTALLED            0x00000001  /* installed code page ids */
#define CP_SUPPORTED            0x00000002  /* supported code page ids */

/*
 *  Sorting Flags.
 *
 *    WORD Sort:    culturally correct sort
 *                  hyphen and apostrophe are special cased
 *                  example: "coop" and "co-op" will sort together in a list
 *
 *                        co_op     <-------  underscore (symbol)
 *                        coat
 *                        comb
 *                        coop
 *                        co-op     <-------  hyphen (punctuation)
 *                        cork
 *                        went
 *                        were
 *                        we're     <-------  apostrophe (punctuation)
 *
 *
 *    STRING Sort:  hyphen and apostrophe will sort with all other symbols
 *
 *                        co-op     <-------  hyphen (punctuation)
 *                        co_op     <-------  underscore (symbol)
 *                        coat
 *                        comb
 *                        coop
 *                        cork
 *                        we're     <-------  apostrophe (punctuation)
 *                        went
 *                        were
 */
#define SORT_STRINGSORT         0x00001000  /* use string sort method */

/*
 *  Code Page Default Values.
 */
#define CP_ACP               0              /* default to ANSI code page */
#define CP_OEMCP             1              /* default to OEM  code page */
#define CP_MACCP             2              /* default to MAC  code page */

/*
 *  Country Codes.
 */
#define CTRY_DEFAULT                     0

#define CTRY_AUSTRALIA                   61      /* Australia */
#define CTRY_AUSTRIA                     43      /* Austria */
#define CTRY_BELGIUM                     32      /* Belgium */
#define CTRY_BRAZIL                      55      /* Brazil */
#define CTRY_BULGARIA                    359     /* Bulgaria */
#define CTRY_CANADA                      2       /* Canada */
#define CTRY_CROATIA                     385     /* Croatia */
#define CTRY_CZECH                       42      /* Czech Republic */
#define CTRY_DENMARK                     45      /* Denmark */
#define CTRY_FINLAND                     358     /* Finland */
#define CTRY_FRANCE                      33      /* France */
#define CTRY_GERMANY                     49      /* Germany */
#define CTRY_GREECE                      30      /* Greece */
#define CTRY_HONG_KONG                   852     /* Hong Kong */
#define CTRY_HUNGARY                     36      /* Hungary */
#define CTRY_ICELAND                     354     /* Iceland */
#define CTRY_IRELAND                     353     /* Ireland */
#define CTRY_ITALY                       39      /* Italy */
#define CTRY_JAPAN                       81      /* Japan */
#define CTRY_MEXICO                      52      /* Mexico */
#define CTRY_NETHERLANDS                 31      /* Netherlands */
#define CTRY_NEW_ZEALAND                 64      /* New Zealand */
#define CTRY_NORWAY                      47      /* Norway */
#define CTRY_POLAND                      48      /* Poland */
#define CTRY_PORTUGAL                    351     /* Portugal */
#define CTRY_PRCHINA                     86      /* Peoples' Republic of China */
#define CTRY_ROMANIA                     40      /* Romania */
#define CTRY_RUSSIA                      7       /* Russia */
#define CTRY_SINGAPORE                   65      /* Singapore */
#define CTRY_SLOVAK                      42      /* Slovak Republic */
#define CTRY_SLOVENIA                    386     /* Slovenia */
#define CTRY_SOUTH_KOREA                 82      /* South Korea */
#define CTRY_SPAIN                       34      /* Spain */
#define CTRY_SWEDEN                      46      /* Sweden */
#define CTRY_SWITZERLAND                 41      /* Switzerland */
#define CTRY_TAIWAN                      886     /* Taiwan */
#define CTRY_TURKEY                      90      /* Turkey */
#define CTRY_UNITED_KINGDOM              44      /* United Kingdom */
#define CTRY_UNITED_STATES               1       /* United States */

/*
 *  Locale Types.
 *
 *  These types are used for the GetLocaleInfoW NLS API routine.
 *
 *  LOCALE_NOUSEROVERRIDE is also used in GetTimeFormatW and GetDateFormatW.
 *
 *  LOCALE_USE_CP_ACP is used in many of the A (Ansi) apis that need to do 
 *  string translation.
 */
#define LOCALE_NOUSEROVERRIDE       0x80000000   /* do not use user overrides */
#define LOCALE_USE_CP_ACP           0x40000000   /* use the system ACP */

#define LOCALE_ILANGUAGE            0x00000001   /* language id */
#define LOCALE_SLANGUAGE            0x00000002   /* localized name of language */
#define LOCALE_SENGLANGUAGE         0x00001001   /* English name of language */
#define LOCALE_SABBREVLANGNAME      0x00000003   /* abbreviated language name */
#define LOCALE_SNATIVELANGNAME      0x00000004   /* native name of language */
#define LOCALE_ICOUNTRY             0x00000005   /* country code */
#define LOCALE_SCOUNTRY             0x00000006   /* localized name of country */
#define LOCALE_SENGCOUNTRY          0x00001002   /* English name of country */
#define LOCALE_SABBREVCTRYNAME      0x00000007   /* abbreviated country name */
#define LOCALE_SNATIVECTRYNAME      0x00000008   /* native name of country */
#define LOCALE_IDEFAULTLANGUAGE     0x00000009   /* default language id */
#define LOCALE_IDEFAULTCOUNTRY      0x0000000A   /* default country code */
#define LOCALE_IDEFAULTCODEPAGE     0x0000000B   /* default oem code page */
#define LOCALE_IDEFAULTANSICODEPAGE 0x00001004   /* default ansi code page */

#define LOCALE_SLIST                0x0000000C   /* list item separator */
#define LOCALE_IMEASURE             0x0000000D   /* 0 = metric, 1 = US */

#define LOCALE_SDECIMAL             0x0000000E   /* decimal separator */
#define LOCALE_STHOUSAND            0x0000000F   /* thousand separator */
#define LOCALE_SGROUPING            0x00000010   /* digit grouping */
#define LOCALE_IDIGITS              0x00000011   /* number of fractional digits */
#define LOCALE_ILZERO               0x00000012   /* leading zeros for decimal */
#define LOCALE_INEGNUMBER           0x00001010   /* negative number mode */
#define LOCALE_SNATIVEDIGITS        0x00000013   /* native ascii 0-9 */

#define LOCALE_SCURRENCY            0x00000014   /* local monetary symbol */
#define LOCALE_SINTLSYMBOL          0x00000015   /* intl monetary symbol */
#define LOCALE_SMONDECIMALSEP       0x00000016   /* monetary decimal separator */
#define LOCALE_SMONTHOUSANDSEP      0x00000017   /* monetary thousand separator */
#define LOCALE_SMONGROUPING         0x00000018   /* monetary grouping */
#define LOCALE_ICURRDIGITS          0x00000019   /* # local monetary digits */
#define LOCALE_IINTLCURRDIGITS      0x0000001A   /* # intl monetary digits */
#define LOCALE_ICURRENCY            0x0000001B   /* positive currency mode */
#define LOCALE_INEGCURR             0x0000001C   /* negative currency mode */

#define LOCALE_SDATE                0x0000001D   /* date separator */
#define LOCALE_STIME                0x0000001E   /* time separator */
#define LOCALE_SSHORTDATE           0x0000001F   /* short date format string */
#define LOCALE_SLONGDATE            0x00000020   /* long date format string */
#define LOCALE_SYEARMONTH           0x00001020   /* year/month date format string */
#define LOCALE_STIMEFORMAT          0x00001003   /* time format string */
#define LOCALE_IDATE                0x00000021   /* short date format ordering */
#define LOCALE_ILDATE               0x00000022   /* long date format ordering */
#define LOCALE_ITIME                0x00000023   /* time format specifier */
#define LOCALE_ITIMEMARKPOSN        0x00001005   /* time marker position */
#define LOCALE_ICENTURY             0x00000024   /* century format specifier (short date) */
#define LOCALE_ITLZERO              0x00000025   /* leading zeros in time field */
#define LOCALE_IDAYLZERO            0x00000026   /* leading zeros in day field (short date) */
#define LOCALE_IMONLZERO            0x00000027   /* leading zeros in month field (short date) */
#define LOCALE_S1159                0x00000028   /* AM designator */
#define LOCALE_S2359                0x00000029   /* PM designator */

#define LOCALE_ICALENDARTYPE        0x00001009   /* type of calendar specifier */
#define LOCALE_IOPTIONALCALENDAR    0x0000100B   /* additional calendar types specifier */
#define LOCALE_IFIRSTDAYOFWEEK      0x0000100C   /* first day of week specifier */
#define LOCALE_IFIRSTWEEKOFYEAR     0x0000100D   /* first week of year specifier */

#define LOCALE_SDAYNAME1            0x0000002A   /* long name for Monday */
#define LOCALE_SDAYNAME2            0x0000002B   /* long name for Tuesday */
#define LOCALE_SDAYNAME3            0x0000002C   /* long name for Wednesday */
#define LOCALE_SDAYNAME4            0x0000002D   /* long name for Thursday */
#define LOCALE_SDAYNAME5            0x0000002E   /* long name for Friday */
#define LOCALE_SDAYNAME6            0x0000002F   /* long name for Saturday */
#define LOCALE_SDAYNAME7            0x00000030   /* long name for Sunday */
#define LOCALE_SABBREVDAYNAME1      0x00000031   /* abbreviated name for Monday */
#define LOCALE_SABBREVDAYNAME2      0x00000032   /* abbreviated name for Tuesday */
#define LOCALE_SABBREVDAYNAME3      0x00000033   /* abbreviated name for Wednesday */
#define LOCALE_SABBREVDAYNAME4      0x00000034   /* abbreviated name for Thursday */
#define LOCALE_SABBREVDAYNAME5      0x00000035   /* abbreviated name for Friday */
#define LOCALE_SABBREVDAYNAME6      0x00000036   /* abbreviated name for Saturday */
#define LOCALE_SABBREVDAYNAME7      0x00000037   /* abbreviated name for Sunday */
#define LOCALE_SMONTHNAME1          0x00000038   /* long name for January */
#define LOCALE_SMONTHNAME2          0x00000039   /* long name for February */
#define LOCALE_SMONTHNAME3          0x0000003A   /* long name for March */
#define LOCALE_SMONTHNAME4          0x0000003B   /* long name for April */
#define LOCALE_SMONTHNAME5          0x0000003C   /* long name for May */
#define LOCALE_SMONTHNAME6          0x0000003D   /* long name for June */
#define LOCALE_SMONTHNAME7          0x0000003E   /* long name for July */
#define LOCALE_SMONTHNAME8          0x0000003F   /* long name for August */
#define LOCALE_SMONTHNAME9          0x00000040   /* long name for September */
#define LOCALE_SMONTHNAME10         0x00000041   /* long name for October */
#define LOCALE_SMONTHNAME11         0x00000042   /* long name for November */
#define LOCALE_SMONTHNAME12         0x00000043   /* long name for December */
#define LOCALE_SMONTHNAME13         0x0000100E   /* long name for 13th month (if exists) */
#define LOCALE_SABBREVMONTHNAME1    0x00000044   /* abbreviated name for January */
#define LOCALE_SABBREVMONTHNAME2    0x00000045   /* abbreviated name for February */
#define LOCALE_SABBREVMONTHNAME3    0x00000046   /* abbreviated name for March */
#define LOCALE_SABBREVMONTHNAME4    0x00000047   /* abbreviated name for April */
#define LOCALE_SABBREVMONTHNAME5    0x00000048   /* abbreviated name for May */
#define LOCALE_SABBREVMONTHNAME6    0x00000049   /* abbreviated name for June */
#define LOCALE_SABBREVMONTHNAME7    0x0000004A   /* abbreviated name for July */
#define LOCALE_SABBREVMONTHNAME8    0x0000004B   /* abbreviated name for August */
#define LOCALE_SABBREVMONTHNAME9    0x0000004C   /* abbreviated name for September */
#define LOCALE_SABBREVMONTHNAME10   0x0000004D   /* abbreviated name for October */
#define LOCALE_SABBREVMONTHNAME11   0x0000004E   /* abbreviated name for November */
#define LOCALE_SABBREVMONTHNAME12   0x0000004F   /* abbreviated name for December */
#define LOCALE_SABBREVMONTHNAME13   0x0000100F   /* abbreviated name for 13th month (if exists) */

#define LOCALE_SPOSITIVESIGN        0x00000050   /* positive sign */
#define LOCALE_SNEGATIVESIGN        0x00000051   /* negative sign */
#define LOCALE_IPOSSIGNPOSN         0x00000052   /* positive sign position */
#define LOCALE_INEGSIGNPOSN         0x00000053   /* negative sign position */
#define LOCALE_IPOSSYMPRECEDES      0x00000054   /* mon sym precedes pos amt */
#define LOCALE_IPOSSEPBYSPACE       0x00000055   /* mon sym sep by space from pos amt */
#define LOCALE_INEGSYMPRECEDES      0x00000056   /* mon sym precedes neg amt */
#define LOCALE_INEGSEPBYSPACE       0x00000057   /* mon sym sep by space from neg amt */

#if(WINVER >= 0x0400)
#define LOCALE_FONTSIGNATURE       0x00000058   /* font signature */
#endif /* WINVER >= 0x0400 */

/*
 *  Time Flags for GetTimeFormatW.
 */
#define TIME_NOMINUTESORSECONDS    0x00000001  /* do not use minutes or seconds */
#define TIME_NOSECONDS             0x00000002  /* do not use seconds */
#define TIME_NOTIMEMARKER          0x00000004  /* do not use time marker */
#define TIME_FORCE24HOURFORMAT     0x00000008  /* always use 24 hour format */

/*
 *  Date Flags for GetDateFormatW.
 */
#define DATE_SHORTDATE             0x00000001  /* use short date picture */
#define DATE_LONGDATE              0x00000002  /* use long date picture */
#define DATE_USE_ALT_CALENDAR      0x00000004  /* use alternate calendar (if any) */

/*
 *  Calendar Types.
 *
 *  These types are used for the GetALTCalendarInfoW NLS API routine.
 */
#define CAL_ICALINTVALUE           0x00000001   /* calendar type */
#define CAL_SCALNAME               0x00000002   /* native name of calendar */
#define CAL_IYEAROFFSETRANGE       0x00000003   /* starting years of eras */
#define CAL_SERASTRING             0x00000004   /* era name for IYearOffsetRanges */
#define CAL_SSHORTDATE             0x00000005   /* short date format string */
#define CAL_SLONGDATE              0x00000006   /* long date format string */
#define CAL_SDAYNAME1              0x00000007   /* native name for Monday */
#define CAL_SDAYNAME2              0x00000008   /* native name for Tuesday */
#define CAL_SDAYNAME3              0x00000009   /* native name for Wednesday */
#define CAL_SDAYNAME4              0x0000000a   /* native name for Thursday */
#define CAL_SDAYNAME5              0x0000000b   /* native name for Friday */
#define CAL_SDAYNAME6              0x0000000c   /* native name for Saturday */
#define CAL_SDAYNAME7              0x0000000d   /* native name for Sunday */
#define CAL_SABBREVDAYNAME1        0x0000000e   /* abbreviated name for Monday */
#define CAL_SABBREVDAYNAME2        0x0000000f   /* abbreviated name for Tuesday */
#define CAL_SABBREVDAYNAME3        0x00000010   /* abbreviated name for Wednesday */
#define CAL_SABBREVDAYNAME4        0x00000011   /* abbreviated name for Thursday */
#define CAL_SABBREVDAYNAME5        0x00000012   /* abbreviated name for Friday */
#define CAL_SABBREVDAYNAME6        0x00000013   /* abbreviated name for Saturday */
#define CAL_SABBREVDAYNAME7        0x00000014   /* abbreviated name for Sunday */
#define CAL_SMONTHNAME1            0x00000015   /* native name for January */
#define CAL_SMONTHNAME2            0x00000016   /* native name for February */
#define CAL_SMONTHNAME3            0x00000017   /* native name for March */
#define CAL_SMONTHNAME4            0x00000018   /* native name for April */
#define CAL_SMONTHNAME5            0x00000019   /* native name for May */
#define CAL_SMONTHNAME6            0x0000001a   /* native name for June */
#define CAL_SMONTHNAME7            0x0000001b   /* native name for July */
#define CAL_SMONTHNAME8            0x0000001c   /* native name for August */
#define CAL_SMONTHNAME9            0x0000001d   /* native name for September */
#define CAL_SMONTHNAME10           0x0000001e   /* native name for October */
#define CAL_SMONTHNAME11           0x0000001f   /* native name for November */
#define CAL_SMONTHNAME12           0x00000020   /* native name for December */
#define CAL_SMONTHNAME13           0x00000021   /* native name for 13th month (if any) */
#define CAL_SABBREVMONTHNAME1      0x00000022   /* abbreviated name for January */
#define CAL_SABBREVMONTHNAME2      0x00000023   /* abbreviated name for February */
#define CAL_SABBREVMONTHNAME3      0x00000024   /* abbreviated name for March */
#define CAL_SABBREVMONTHNAME4      0x00000025   /* abbreviated name for April */
#define CAL_SABBREVMONTHNAME5      0x00000026   /* abbreviated name for May */
#define CAL_SABBREVMONTHNAME6      0x00000027   /* abbreviated name for June */
#define CAL_SABBREVMONTHNAME7      0x00000028   /* abbreviated name for July */
#define CAL_SABBREVMONTHNAME8      0x00000029   /* abbreviated name for August */
#define CAL_SABBREVMONTHNAME9      0x0000002a   /* abbreviated name for September */
#define CAL_SABBREVMONTHNAME10     0x0000002b   /* abbreviated name for October */
#define CAL_SABBREVMONTHNAME11     0x0000002c   /* abbreviated name for November */
#define CAL_SABBREVMONTHNAME12     0x0000002d   /* abbreviated name for December */
#define CAL_SABBREVMONTHNAME13     0x0000002e   /* abbreviated name for 13th month (if any) */

/*
 *  Calendar Enumeration Value.
 */
#define ENUM_ALL_CALENDARS         0xffffffff   /* enumerate all calendars */

/*
 *  Calendar ID Values.
 */
#define CAL_GREGORIAN        1         /* Gregorian (localized) calendar */
#define CAL_GREGORIAN_US     2         /* Gregorian (U.S.) calendar */
#define CAL_JAPAN            3         /* Japanese Emperor Era calendar */
#define CAL_TAIWAN           4         /* Republic of China Era calendar */
#define CAL_KOREA            5         /* Korean Tangun Era calendar */
#define CAL_HIRJI			 6		   /* Hirji (Arabic Lunar) calendar */
#define CAL_THAI			 7		   /* Thai calendar */
#define CAL_HEBREW			 8		   /* Hebrew calendar */

/***************************************************************************\
* Typedefs
*
* Define all types for the NLS component here.
\***************************************************************************/

/*
 *  Locale type constant.
 */
typedef DWORD LCTYPE;

/*
 *  Calendar type constant.
 */
typedef DWORD CALTYPE;

/*
 *  Calendar ID.
 */
typedef DWORD CALID;

/*
 *  CP Info.
 */

/**
 * This structure contains information about a code page.
 *
 * Lead bytes are unique to double-byte character sets (DBCS). A lead byte is the first byte of a
 * 2-byte character in a DBCS. Lead bytes occupy a specific range of byte values.
 */
typedef struct _cpinfo {
    /**
     * Specifies the maximum length, in bytes, of a character in this code page.
     */
    UINT    MaxCharSize;                    /* max length (bytes) of a char */
    /**
     * Specifies the default character used in translations into this code page. This character is used
     * by the WideCharToMultiByte function if an explicit default character is not given.
     */
    BYTE    DefaultChar[MAX_DEFAULTCHAR];   /* default character */
    /**
     * Specifies a fixed-length array of lead-byte ranges, where the number of lead-byte ranges is
     * variable. If there are no lead bytes in this code page, then every element of the array is NULL.
     * If there are lead bytes in this code page, a starting value and ending value is given for each
     * range. Ranges are inclusive. The maximum number of lead-byte ranges for any code page is 5. The
     * array uses two bytes to describe each range, with a double-byte terminating null character after
     * the last range.
     */
    BYTE    LeadByte[MAX_LEADBYTES];        /* lead byte ranges */
} CPINFO, *LPCPINFO;

/*
 *  Number format.
 */

/**
 * This structure contains information that defines the format of a number string. The
 * GetNumberFormat function uses this information to customize a number string for a specified
 * locale.
 *
 * For more information about the LCTYPE constants, see the Windows CE Programming Guide.
 */
typedef struct _numberfmtW {
    /**
     * Specifies the number of fractional digits. This is equivalent to the locale information specified
     * by the LCTYPE constant value LOCALE_IDIGITS.
     */
    UINT    NumDigits;                 /* number of decimal digits */
    /**
     * Specifies whether to use leading zeroes in decimal fields. This is equivalent to the locale
     * information specified by the LCTYPE constant value LOCALE_ILZERO.
     */
    UINT    LeadingZero;               /* if leading zero in decimal fields */
    /**
     * Specifies the size of each group of digits to the left of the decimal. Values in the range 0 - 9
     * are valid.
     */
    UINT    Grouping;                  /* group size left of decimal */
    /**
     * Long pointer to a null-terminated decimal separator string.
     */
    LPWSTR  lpDecimalSep;              /* ptr to decimal separator string */
    /**
     * Long pointer to a null-terminated thousand separator string.
     */
    LPWSTR  lpThousandSep;             /* ptr to thousand separator string */
    /**
     * Specifies the negative number mode. This is equivalent to the locale information specified by the
     * LCTYPE constant value LOCALE_INEGNUMBER.
     */
    UINT    NegativeOrder;             /* negative number ordering */
} NUMBERFMTW, *LPNUMBERFMTW;

typedef NUMBERFMTW NUMBERFMT;
typedef LPNUMBERFMTW LPNUMBERFMT;

/*
 *  Currency format.
 */

/**
 * This structure contains information that defines the format of a currency string. The
 * GetCurrencyFormat function uses this information to customize a currency string for a specified
 * locale.
 */
typedef struct _currencyfmtW {
    /**
     * Specifies the number of fractional digits. This is equivalent to the locale information specified
     * by the LCTYPE constant value LOCALE_IDIGITS.
     */
    UINT    NumDigits;                 /* number of decimal digits */
    /**
     * Specifies whether to use leading zeroes in decimal fields. This is equivalent to the locale
     * information specified by the LCTYPE constant value LOCALE_ILZERO.
     */
    UINT    LeadingZero;               /* if leading zero in decimal fields */
    /**
     * Specifies the size of each group of digits to the left of the decimal. Values in the range 0 - 9
     * are valid.
     */
    UINT    Grouping;                  /* group size left of decimal */
    /**
     * Pointer to a null-terminated decimal separator string.
     */
    LPWSTR  lpDecimalSep;              /* ptr to decimal separator string */
    /**
     * Pointer to a null-terminated thousand separator string.
     */
    LPWSTR  lpThousandSep;             /* ptr to thousand separator string */
    /**
     * Specifies the negative currency mode. This is equivalent to the locale information specified by
     * the LCTYPE constant value LOCALE_INEGCURR.
     */
    UINT    NegativeOrder;             /* negative currency ordering */
    /**
     * Specifies the positive currency mode. This is equivalent to the locale information specified by
     * the LCTYPE constant value LOCALE_ICURRENCY.
     */
    UINT    PositiveOrder;             /* positive currency ordering */
    /**
     * Pointer to a null-terminated currency symbol string.
     */
    LPWSTR  lpCurrencySymbol;          /* ptr to currency symbol string */
} CURRENCYFMTW, *LPCURRENCYFMTW;

typedef CURRENCYFMTW CURRENCYFMT;
typedef LPCURRENCYFMTW LPCURRENCYFMT;

/*
 *  Enumeration function constants.
 */

#ifdef STRICT

typedef BOOL (CALLBACK* LOCALE_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK* CODEPAGE_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK* DATEFMT_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK* TIMEFMT_ENUMPROCW)(LPWSTR);
typedef BOOL (CALLBACK* CALINFO_ENUMPROCW)(LPWSTR);

#else /* !STRICT */

typedef FARPROC LOCALE_ENUMPROCW;
typedef FARPROC CODEPAGE_ENUMPROCW;
typedef FARPROC DATEFMT_ENUMPROCW;
typedef FARPROC TIMEFMT_ENUMPROCW;
typedef FARPROC CALINFO_ENUMPROCW;

#endif /* !STRICT */

#define LOCALE_ENUMPROC    LOCALE_ENUMPROCW
#define CODEPAGE_ENUMPROC  CODEPAGE_ENUMPROCW
#define DATEFMT_ENUMPROC   DATEFMT_ENUMPROCW
#define TIMEFMT_ENUMPROC   TIMEFMT_ENUMPROCW
#define CALINFO_ENUMPROC   CALINFO_ENUMPROCW

/***************************************************************************\
* Function Prototypes
*
* Only prototypes for the NLS APIs should go here.
\***************************************************************************/

/*
 *  Code Page Dependent APIs.
 */

/**
 * This function determines whether a specified code page is valid.
 *
 * @param CodePage [in] Specifies the code page to check. Each code page is identified by a unique
 *   number.
 *
 * @return Nonzero indicates that the code page is valid. Zero indicates that the code page is not
 *   valid. To get extended error information, call GetLastError.
 *
 * A code page is considered valid only if it is installed in the system.
 *
 * Following are the code-page identifiers:
 *
 * Identifier Description 037 EBCDIC 437 MS-DOS United States 500 EBCDIC "500V1" 708 Arabic (ASMO
 * 708) 709 Arabic (ASMO 449+, BCON V4) 710 Arabic (Transparent Arabic) 720 Arabic (Transparent
 * ASMO) 737 Greek (formerly 437G) 775 Baltic 850 MS-DOS Multilingual (Latin I) 852 MS-DOS Slavic
 * (Latin II) 855 IBM Cyrillic (primarily Russian) 857 IBM Turkish 860 MS-DOS Portuguese 861 MS-DOS
 * Icelandic 862 Hebrew 863 MS-DOS Canadian-French 864 Arabic 865 MS-DOS Nordic 866 MS-DOS Russian
 * 869 IBM Modern Greek 874 Thai 875 EBCDIC 932 Japan 936 Chinese (PRC, Singapore) 949 Korean 950
 * Chinese (Taiwan Region; Hong Kong SAR, PRC) 1026 EBCDIC 1200 Unicode (BMP of ISO 10646) 1250
 * Windows 3.1 Eastern European 1251 Windows 3.1 Cyrillic 1252 Windows 3.1 US (ANSI) 1253 Windows
 * 3.1 Greek 1254 Windows 3.1 Turkish 1255 Hebrew 1256 Arabic 1257 Baltic 1361 Korean (Johab) 10000
 * Macintosh Roman 10001 Macintosh Japanese 10006 Macintosh Greek I 10007 Macintosh Cyrillic 10029
 * Macintosh Latin 2 10079 Macintosh Icelandic 10081 Macintosh Turkish
 */
BOOL WINAPI IsValidCodePage(UINT CodePage);

/**
 * This function retrieves the current ANSI code-page identifier for the system.
 *
 * @return The current ANSI code-page identifier for the system or a default identifier if no code
 *   page is current indicates success.
 *
 * Following are the ANSI code-page identifiers:
 *
 * Identifier Description 874 Thai 932 Japan 936 Chinese (PRC, Singapore) 949 Korean 950 Chinese
 * (Taiwan Region; Hong Kong SAR, PRC) 1200 Unicode (BMP of ISO 10646) 1250 Windows 3.1 Eastern
 * European 1251 Windows 3.1 Cyrillic 1252 Windows 3.1 Latin 1 (US, Western Europe) 1253 Windows 3.1
 * Greek 1254 Windows 3.1 Turkish 1255 Hebrew 1256 Arabic 1257 Baltic
 */
UINT WINAPI GetACP(void);

/**
 * This function retrieves the current original equipment manufacturer (OEM) code-page identifier
 * for the system.
 *
 * @return The current OEM code-page identifier for the system or a default identifier if no code
 *   page is current indicates success.
 *
 * Following are the OEM code-page identifiers:
 *
 * Identifier Description 437 MS-DOS United States 708 Arabic (ASMO 708) 709 Arabic (ASMO 449+, BCON
 * V4) 710 Arabic (Transparent Arabic) 720 Arabic (Transparent ASMO) 737 Greek (formerly 437G) 775
 * Baltic 850 MS-DOS Multilingual (Latin I) 852 MS-DOS Slavic (Latin II) 855 IBM Cyrillic (primarily
 * Russian) 857 IBM Turkish 860 MS-DOS Portuguese 861 MS-DOS Icelandic 862 Hebrew 863 MS-DOS
 * Canadian-French 864 Arabic 865 MS-DOS Nordic 866 MS-DOS Russian (former USSR) 869 IBM Modern
 * Greek 874 Thai 932 Japan 936 Chinese (PRC, Singapore) 949 Korean 950 Chinese (Taiwan Region; Hong
 * Kong SAR, PRC) 1361 Korean (Johab)
 */
UINT WINAPI GetOEMCP(void);

/**
 * This function retrieves information about any valid installed or available code page.
 *
 * @param CodePage [in] Specifies the code page about which information is to be retrieved. You can
 *   specify the code page identifier for any installed or available code page, or you can specify one
 *   of the following predefined values: Value Description CP_ACP Use the system default ANSI code
 *   page CP_MACCP Not supported. CP_OEMCP Use the system default OEM code page
 * @param lpCPInfo [out] Pointer to a CPINFO structure that receives information about the code
 *   page.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError.
 *
 * If the specified code page is not installed or not available, GetCPInfo sets the last-error value
 * to ERROR_INVALID_PARAMETER.
 */
BOOL WINAPI GetCPInfo(UINT CodePage, LPCPINFO lpCPInfo);

/**
 * This function determines whether a character is a lead byte - that is, the first byte of a
 * character in a double-byte character set (DBCS).
 *
 * @param TestChar [in] Specifies the character to be tested.
 *
 * @return TRUE indicates that the character is a lead byte. FALSE indicates that either the
 *   character is not a lead byte or an error was generated. For extended error information, call
 *   GetLastError.
 *
 * Lead bytes are unique to double-byte character sets. A lead byte introduces a double-byte
 * character. Lead bytes occupy a specific range of byte values. The IsDBCSLeadByte function uses
 * the ANSI code page to check lead-byte ranges. To specify a different code page, use the
 * IsDBCSLeadByteEx function.
 */
BOOL WINAPI IsDBCSLeadByte(BYTE TestChar);

/**
 * This function determines whether a character is a lead byte - that is, the first byte of a
 * character in a double-byte character set (DBCS).
 *
 * @param CodePage [in] Identifier of the code page to use to check lead-byte ranges. Can be one of
 *   the values listed in the Code Page Identifiers in Unicode and character set Constants or one the
 *   following predefined values: Value Description 0 Use system default ANSI code page. CP_ACP Use
 *   system default ANSI code page. CP_OEMCP Use system default OEM code page.
 * @param TestChar [in] Character to test.
 *
 * @return TRUE indicates that the character is a lead byte. FALSE indicates that either the
 *   character is not a lead byte or an error was generated. For extended error information, call
 *   GetLastError.
 */
BOOL WINAPI IsDBCSLeadByteEx(UINT CodePage, BYTE TestChar);

/**
 * This function maps a character string to a wide-character (Unicode) string. The character string
 * mapped by this function is not necessarily from a multibyte character set.
 *
 * @param CodePage [in] Specifies the code page to be used to perform the conversion. This parameter
 *   can be given the value of any code page that is installed or available in the system. You can
 *   also specify one of the following values: Value Description CP_ACP ANSI code page CP_MACCP Not
 *   supported CP_OEMCP OEM code page CP_SYMBOL Not supported CP_THREAD_ACP Not supported
 * @param dwFlags [in] Specifies whether to translate to precomposed or composite wide characters
 *   (if a composite form exists), whether to use glyph characters in place of control characters, and
 *   how to deal with invalid characters. You can specify a combination of the following flag
 *   constants: Value Description MB_PRECOMPOSED Always use precomposed characters-that is, characters
 *   in which a base character and a nonspacing character have a single character value. This is the
 *   default translation option. Cannot be used with MB_COMPOSITE. MB_COMPOSITE Always use composite
 *   characters-that is, characters in which a base character and a nonspacing character have
 *   different character values. Cannot be used with MB_PRECOMPOSED. MB_ERR_INVALID_CHARS If the
 *   function encounters an invalid input character, it fails and GetLastError returns
 *   ERROR_NO_UNICODE_TRANSLATION. MB_USEGLYPHCHARS Use glyph characters instead of control
 *   characters. A composite character consists of a base character and a nonspacing character, each
 *   having different character values. A precomposed character has a single character value for a
 *   base/non-spacing character combination. In the character e, the e is the base character and the
 *   accent grave mark is the nonspacing character. The function's default behavior is to translate to
 *   the precomposed form. If a precomposed form does not exist, the function attempts to translate to
 *   a composite form. The flags MB_PRECOMPOSED and MB_COMPOSITE are mutually exclusive. The
 *   MB_USEGLYPHCHARS flag and the MB_ERR_INVALID_CHARS can be set regardless of the state of the
 *   other flags.
 * @param lpMultiByteStr [in] Pointer to the character string to be converted.
 * @param cbMultiByte [in] Specifies the size in bytes of the string pointed to by the
 *   lpMultiByteStr parameter. If this value is -1, the string is assumed to be null terminated and
 *   the length is calculated automatically.
 * @param lpWideCharStr [out] Pointer to a buffer that receives the translated string.
 * @param cchWideChar [in] Specifies the size, in wide characters, of the buffer pointed to by the
 *   lpWideCharStr parameter. If this value is zero, the function returns the required buffer size, in
 *   wide characters, and makes no use of the lpWideCharStr buffer.
 *
 * @return If cchWideChar is nonzero, the number of wide characters written to the buffer pointed to
 *   by lpWideCharStr indicates success. If cchWideChar is zero, the required size, in wide
 *   characters, for a buffer that can receive the translated string indicates success. Zero indicates
 *   failure. To get extended error information, call GetLastError. Possible values for GetLastError
 *   include the following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *   ERROR_NO_UNICODE_TRANSLATION
 *
 * The lpMultiByteStr and lpWideCharStr pointers must not be the same. If they are the same, the
 * function fails, and GetLastError returns the value ERROR_INVALID_PARAMETER.
 *
 * The function fails if MB_ERR_INVALID_CHARS is set and it encounters an invalid character in the
 * source string. An invalid character is one that would translate to the default character if
 * MB_ERR_INVALID_CHARS was not set, but is not the default character in the source string, or when
 * a lead byte is found in a string and there is no valid trail byte for DBCS strings. When an
 * invalid character is found, and MB_ERR_INVALID_CHARS is set, the function returns 0 and sets
 * GetLastError with the error ERROR_NO_UNICODE_TRANSLATION.
 */
int WINAPI MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr,
	int cchMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

/**
 * This function maps a wide-character string to a new character string. The new character string is
 * not necessarily from a multibyte character set.
 *
 * @param CodePage [in] Specifies the code page used to perform the conversion. This parameter can
 *   be given the value of any code page that is installed or available in the system. You can also
 *   specify one of the following values: Value Description CP_ACP ANSI code page CP_MACCP Not
 *   supported CP_OEMCP OEM code page CP_SYMBOL Not supported CP_THREAD_ACP Not supported
 * @param dwFlags [in] Specifies the handling of unmapped characters. The function performs more
 *   quickly when none of these flags is set. The following flag constants are defined: Value
 *   Description WC_COMPOSITECHECK Convert composite characters to precomposed characters.
 *   WC_DISCARDNS Discard nonspacing characters during conversion. WC_SEPCHARS Generate separate
 *   characters during conversion. This is the default conversion behavior. WC_DEFAULTCHAR Replace
 *   exceptions with the default character during conversion. When WC_COMPOSITECHECK is specified, the
 *   function converts composite characters to precomposed characters. A composite character consists
 *   of a base character and a nonspacing character, each having different character values. A
 *   precomposed character has a single character value for a base/nonspacing character combination.
 *   In the character e, the e is the base character, and the accent grave mark is the nonspacing
 *   character. When an application specifies WC_COMPOSITECHECK, it can use the last three flags in
 *   this list (WC_DISCARDNS, WC_SEPCHARS, and WC_DEFAULTCHAR) to customize the conversion to
 *   precomposed characters. These flags determine the function's behavior when there is no
 *   precomposed mapping for a base/nonspace character combination in a wide-character string. These
 *   last three flags can only be used if the WC_COMPOSITECHECK flag is set. The function's default
 *   behavior is to generate separate characters (WC_SEPCHARS) for unmapped composite characters.
 * @param lpWideCharStr [in] Pointer to the wide-character string to be converted.
 * @param cchWideChar [in] Specifies the number of Unicode (16-bit) characters in the string pointed
 *   to by the lpWideCharStr parameter. If this value is -1, the string is assumed to be
 *   null-terminated and the length is calculated automatically.
 * @param lpMultiByteStr [out] Pointer to the buffer to receive the translated string.
 * @param cbMultiByte [in] Specifies the size in bytes of the buffer pointed to by the
 *   lpMultiByteStr parameter. If this value is zero, the function returns the number of bytes
 *   required for the buffer. (In this case, the lpMultiByteStr buffer is not used.)
 * @param lpDefaultChar [in] Pointer to the character used if a wide character cannot be represented
 *   in the specified code page. If this parameter is NULL, a system default value is used. The
 *   function is faster when both lpDefaultChar and lpUsedDefaultChar are NULL.
 * @param lpUsedDefaultChar [in/out] Pointer to a flag that indicates whether a default character
 *   was used. The flag is set to TRUE if one or more wide characters in the source string cannot be
 *   represented in the specified code page. Otherwise, the flag is set to FALSE. This parameter may
 *   be NULL. The function is faster when both lpDefaultChar and lpUsedDefaultChar are NULL.
 *
 * @return If cbMultiByte is nonzero, the number of bytes written to the buffer pointed to by
 *   lpMultiByteStr indicates success. If cbMultiByte is zero, the required size, in bytes, for a
 *   buffer that can receive the translated string indicates success. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The lpMultiByteStr and lpWideCharStr pointers must not be the same. If they are the same, the
 * function fails, and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * An application can use the lpDefaultChar parameter to change the default character used for the
 * conversion.
 *
 * As noted earlier, the WideCharToMultiByte function operates most efficiently when both
 * lpDefaultChar and lpUsedDefaultChar are NULL. The following table shows the behavior of
 * WideCharToMultiByte for the four combinations of lpDefaultChar and lpUsedDefaultChar :
 *
 * lpDefaultChar lpUsedDefaultChar Result NULL NULL No default checking. This is the most efficient,
 * quick way to use this function. non-NULL NULL Uses the specified default character, but does not
 * set lpUsedDefaultChar. NULL non-NULL Uses the system default character and sets lpUsedDefaultChar
 * if necessary. non-NULL non-NULL Uses the specified default character and sets lpUsedDefaultChar
 * if necessary.
 */
int WINAPI WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr,
    int cchWideChar, LPSTR lpMultiByteStr, int cchMultiByte, LPCSTR lpDefaultChar,
    LPBOOL lpUsedDefaultChar);

#define CSTR_LESS_THAN 1
#define CSTR_EQUAL 2
#define CSTR_GREATER_THAN 3

/**
 * This function compares two character strings, using the locale specified by the given identifier
 * as the basis for the comparison.
 *
 * @param Locale [in] Specifies the locale used for the comparison. This parameter can be one of the
 *   following predefined locale identifiers: Value Description LOCALE_SYSTEM_DEFAULT The system's
 *   default locale. LOCALE_USER_DEFAULT The current user's default locale. This parameter can also be
 *   a locale identifier created by the MAKELCID macro.
 * @param dwCmpFlags [in] A set of flags that indicate how the function compares the two strings. By
 *   default, these flags are not set. This parameter can specify zero to get the default behavior, or
 *   it can be any combination of the following values: Value Description NORM_IGNORECASE Ignore case.
 *   NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters. Corresponding
 *   Hiragana and Katakana characters compare as equal. NORM_IGNORENONSPACE Ignore nonspacing
 *   characters. NORM_IGNORESYMBOLS Ignore symbols. NORM_IGNOREWIDTH Do not differentiate between a
 *   single-byte character and the same character as a double-byte character. SORT_STRINGSORT Treat
 *   punctuation the same as symbols.
 * @param lpString1 [in] Pointer to the first string to be compared.
 * @param cchCount1 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString1 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 * @param lpString2 [in] Pointer to the second string to be compared.
 * @param cchCount2 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString2 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 *
 * @return If the function succeeds, the return value is one of the following values: Value
 *   Description CSTR_LESS_THAN The string pointed to by the lpString1 parameter is less in lexical
 *   value than the string pointed to by the lpString2 parameter. CSTR_EQUAL The string pointed to by
 *   lpString1 is equal in lexical value to the string pointed to by lpString2. CSTR_GREATER_THAN The
 *   string pointed to by lpString1 is greater in lexical value than the string pointed to by
 *   lpString2. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * Notice that if the return value is CSTR_EQUAL, which is the value 2, the two strings are "equal"
 * in the collation sense, though not necessarily identical.
 *
 * To maintain the C run-time convention of comparing strings, the value 2 can be subtracted from a
 * nonzero return value. The meaning of < 0, ==0 and > 0 is then consistent with the C run times.
 *
 * If the two strings are of different lengths, they are compared up to the length of the shortest
 * one. If they are equal to that point, then the return value will indicate that the longer string
 * is greater. For more information about locale identifiers, see Locale Identifiers.
 *
 * Strings are compared using what is called a "string sort" technique. In a string sort, the hyphen
 * and apostrophe are treated just like any other nonalphanumeric symbols: they come before the
 * alphanumeric symbols.
 *
 * The following list of words is sorted using a string sort:
 *
 * bill's t-ant billet t-aria bills tanya can't sue's cannot sued cant sues co-op we're con went
 * coop were
 *
 * The LCMapString function defaults to using a word sort, but uses a string sort if their caller
 * sets the SORT_STRINGSORT flag.
 *
 * The CompareString function is optimized to run at the highest speed when dwCmpFlags is set to 0
 * or NORM_IGNORECASE, and cchCount1 and cchCount2 have the value -1.
 */
int WINAPI CompareStringW(LCID Locale, DWORD dwCmpFlags, LPCWSTR lpString1,
	int cchCount1, LPCWSTR lpString2, int cchCount2);

#ifdef UNICODE
/**
 * This function compares two character strings, using the locale specified by the given identifier
 * as the basis for the comparison.
 *
 * @param Locale [in] Specifies the locale used for the comparison. This parameter can be one of the
 *   following predefined locale identifiers: Value Description LOCALE_SYSTEM_DEFAULT The system's
 *   default locale. LOCALE_USER_DEFAULT The current user's default locale. This parameter can also be
 *   a locale identifier created by the MAKELCID macro.
 * @param dwCmpFlags [in] A set of flags that indicate how the function compares the two strings. By
 *   default, these flags are not set. This parameter can specify zero to get the default behavior, or
 *   it can be any combination of the following values: Value Description NORM_IGNORECASE Ignore case.
 *   NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters. Corresponding
 *   Hiragana and Katakana characters compare as equal. NORM_IGNORENONSPACE Ignore nonspacing
 *   characters. NORM_IGNORESYMBOLS Ignore symbols. NORM_IGNOREWIDTH Do not differentiate between a
 *   single-byte character and the same character as a double-byte character. SORT_STRINGSORT Treat
 *   punctuation the same as symbols.
 * @param lpString1 [in] Pointer to the first string to be compared.
 * @param cchCount1 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString1 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 * @param lpString2 [in] Pointer to the second string to be compared.
 * @param cchCount2 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString2 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 *
 * @return If the function succeeds, the return value is one of the following values: Value
 *   Description CSTR_LESS_THAN The string pointed to by the lpString1 parameter is less in lexical
 *   value than the string pointed to by the lpString2 parameter. CSTR_EQUAL The string pointed to by
 *   lpString1 is equal in lexical value to the string pointed to by lpString2. CSTR_GREATER_THAN The
 *   string pointed to by lpString1 is greater in lexical value than the string pointed to by
 *   lpString2. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * Notice that if the return value is CSTR_EQUAL, which is the value 2, the two strings are "equal"
 * in the collation sense, though not necessarily identical.
 *
 * To maintain the C run-time convention of comparing strings, the value 2 can be subtracted from a
 * nonzero return value. The meaning of < 0, ==0 and > 0 is then consistent with the C run times.
 *
 * If the two strings are of different lengths, they are compared up to the length of the shortest
 * one. If they are equal to that point, then the return value will indicate that the longer string
 * is greater. For more information about locale identifiers, see Locale Identifiers.
 *
 * Strings are compared using what is called a "string sort" technique. In a string sort, the hyphen
 * and apostrophe are treated just like any other nonalphanumeric symbols: they come before the
 * alphanumeric symbols.
 *
 * The following list of words is sorted using a string sort:
 *
 * bill's t-ant billet t-aria bills tanya can't sue's cannot sued cant sues co-op we're con went
 * coop were
 *
 * The LCMapString function defaults to using a word sort, but uses a string sort if their caller
 * sets the SORT_STRINGSORT flag.
 *
 * The CompareString function is optimized to run at the highest speed when dwCmpFlags is set to 0
 * or NORM_IGNORECASE, and cchCount1 and cchCount2 have the value -1.
 */
#define CompareString  CompareStringW
#else
/**
 * This function compares two character strings, using the locale specified by the given identifier
 * as the basis for the comparison.
 *
 * @param Locale [in] Specifies the locale used for the comparison. This parameter can be one of the
 *   following predefined locale identifiers: Value Description LOCALE_SYSTEM_DEFAULT The system's
 *   default locale. LOCALE_USER_DEFAULT The current user's default locale. This parameter can also be
 *   a locale identifier created by the MAKELCID macro.
 * @param dwCmpFlags [in] A set of flags that indicate how the function compares the two strings. By
 *   default, these flags are not set. This parameter can specify zero to get the default behavior, or
 *   it can be any combination of the following values: Value Description NORM_IGNORECASE Ignore case.
 *   NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters. Corresponding
 *   Hiragana and Katakana characters compare as equal. NORM_IGNORENONSPACE Ignore nonspacing
 *   characters. NORM_IGNORESYMBOLS Ignore symbols. NORM_IGNOREWIDTH Do not differentiate between a
 *   single-byte character and the same character as a double-byte character. SORT_STRINGSORT Treat
 *   punctuation the same as symbols.
 * @param lpString1 [in] Pointer to the first string to be compared.
 * @param cchCount1 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString1 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 * @param lpString2 [in] Pointer to the second string to be compared.
 * @param cchCount2 [in] Specifies the size, in characters, of the string pointed to by the
 *   lpString2 parameter. If this parameter is -1, the string is assumed to be null terminated and the
 *   length is calculated automatically.
 *
 * @return If the function succeeds, the return value is one of the following values: Value
 *   Description CSTR_LESS_THAN The string pointed to by the lpString1 parameter is less in lexical
 *   value than the string pointed to by the lpString2 parameter. CSTR_EQUAL The string pointed to by
 *   lpString1 is equal in lexical value to the string pointed to by lpString2. CSTR_GREATER_THAN The
 *   string pointed to by lpString1 is greater in lexical value than the string pointed to by
 *   lpString2. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * Notice that if the return value is CSTR_EQUAL, which is the value 2, the two strings are "equal"
 * in the collation sense, though not necessarily identical.
 *
 * To maintain the C run-time convention of comparing strings, the value 2 can be subtracted from a
 * nonzero return value. The meaning of < 0, ==0 and > 0 is then consistent with the C run times.
 *
 * If the two strings are of different lengths, they are compared up to the length of the shortest
 * one. If they are equal to that point, then the return value will indicate that the longer string
 * is greater. For more information about locale identifiers, see Locale Identifiers.
 *
 * Strings are compared using what is called a "string sort" technique. In a string sort, the hyphen
 * and apostrophe are treated just like any other nonalphanumeric symbols: they come before the
 * alphanumeric symbols.
 *
 * The following list of words is sorted using a string sort:
 *
 * bill's t-ant billet t-aria bills tanya can't sue's cannot sued cant sues co-op we're con went
 * coop were
 *
 * The LCMapString function defaults to using a word sort, but uses a string sort if their caller
 * sets the SORT_STRINGSORT flag.
 *
 * The CompareString function is optimized to run at the highest speed when dwCmpFlags is set to 0
 * or NORM_IGNORECASE, and cchCount1 and cchCount2 have the value -1.
 */
#define CompareString  CompareStringA
#endif

/**
 * This function maps one character string to another, performing a specified locale-dependent
 * transformation. LCMapString can also be used to generate a sort key for the input string.
 *
 * @param Locale [in] Specifies a locale identifier. The locale provides a context for the string
 *   mapping or sort key generation. An application can use the MAKELCID macro to create a locale
 *   identifier.
 * @param dwMapFlags [in] Specifies the type of transformation to be used during string mapping or
 *   sort key generation. An application can specify more than one of these options on a single
 *   transformation, although some combinations are invalid. The following mapping options are
 *   defined; restrictions are noted following the table: Value Description LCMAP_BYTEREV Use byte
 *   reversal. For example, if you pass in 0x3450 0x4822 the result is 0x5034 0x2248. LCMAP_FULLWIDTH
 *   Wide characters (where applicable). LCMAP_HALFWIDTH Narrow characters (where applicable).
 *   LCMAP_HIRAGANA Hiragana. LCMAP_KATAKANA Katakana. LCMAP_LOWERCASE Use lowercase. LCMAP_SORTKEY
 *   Produce a normalized wide-character sort key. LCMAP_UPPERCASE Use uppercase. NORM_IGNORECASE
 *   Ignore case. NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters.
 *   Corresponding Hiragana and Katakana will compare as equal. NORM_IGNORENONSPACE Ignore nonspacing.
 *   This flag also removes Japanese accent characters. NORM_IGNORESYMBOLS Ignore symbols.
 *   NORM_IGNOREWIDTH Do not differentiate between a single-byte character and the same character as a
 *   double-byte character. SORT_STRINGSORT Treat punctuation the same as symbols. If the
 *   LCMAP_SORTKEY flag is not specified, the LCMapString function performs string mapping. In this
 *   case the following restrictions apply: LCMAP_LOWERCASE and LCMAP_UPPERCASE are mutually
 *   exclusive. LCMAP_HIRAGANA and LCMAP_KATAKANA are mutually exclusive. LCMAP_HALFWIDTH and
 *   LCMAP_FULLWIDTH are mutually exclusive. SORT_STRINGSORT, NORM_IGNOREKANATYPE, NORM_IGNOREWIDTH,
 *   and NORM_IGNORECASE are not valid. LCMAP_TRADITIONAL_CHINESE and LCMAP_SIMPLIFIED_CHINESE are
 *   mutually exclusive. LCMAP_LOWERCASE and LCMAP_UPPERCASE are not valid in combination with any of
 *   the following flags: LCMAP_HIRAGANA, LCMAP_KATAKANA, LCMAP_HALFWIDTH, and LCMAP_FULLWIDTH. When
 *   the LCMAP_SORTKEY flag is specified, the LCMapString function generates a sort key. In this case
 *   the following restriction applies: LCMAP_SORTKEY is mutually exclusive with all other LCMAP_*
 *   flags, with the sole exception of LCMAP_BYTEREV.
 * @param lpSrcStr [in] Pointer to a source string that the function maps or uses for sort key
 *   generation.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. This count can include the NULL terminator, or not include it. If the NULL terminator
 *   is included in the character count, it does not greatly affect the mapping behavior. That is
 *   because NULL is considered to be unsortable, and always maps to itself. A cchSrc value of -1
 *   specifies that the string pointed to by lpSrcStr is null-terminated. If this is the case, and
 *   LCMapString is being used in its string-mapping mode, the function calculates the string's length
 *   itself, and null-terminates the mapped string stored into *lpDestStr.
 * @param lpDestStr [out] Long pointer to a buffer into which the function stores the mapped string
 *   or sort key. If LCMAP_SORTKEY is specified, LCMapString stores a sort key into the buffer. The
 *   sort key is stored as an array of byte values in the following format: Note that the sort key is
 *   null-terminated. This is true regardless of the value of cchSrc. Also note that, even if some of
 *   the sort weights are absent from the sort key, due to the presence of one or more ignore flags in
 *   dwMapFlags, the 0x01 separators and the 0x00 terminator are still present.
 * @param cchDest [in] Specifies the size, in characters, of the buffer pointed to by lpDestStr. If
 *   the function is being used for string mapping, the size is a character count. If space for a NULL
 *   terminator is included in cchSrc, then cchDest must also include space for a NULL terminator. If
 *   the function is being used to generate a sort key, the size is a byte count. This byte count must
 *   include space for the sort key 0x00 terminator. If cchDest is zero, the function's return value
 *   is the number of characters, or bytes if LCMAP_SORTKEY is specified, required to hold the mapped
 *   string or sort key. In this case, the buffer pointed to by lpDestStr is not used.
 *
 * @return If the value of cchDest is nonzero, the number of characters, or bytes if LCMAP_SORTKEY
 *   is specified, written to the buffer indicates success. This count includes room for a NULL
 *   terminator. If the value of cchDest is zero, the size of the buffer in characters, or bytes if
 *   LCMAP_SORTKEY is specified, required to receive the translated string or sort key indicates
 *   success. This size includes room for a NULL terminator. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null terminated if the source string is null terminated.
 *
 * If the LCMAP_HIRAGANA flag is specified to map Katakana characters to Hiragana characters, and
 * LCMAP_FULLWIDTH is not specified, the function only maps full-width characters to Hiragana. In
 * this case, any half-width Katakana characters are placed as-is in the output string, with no
 * mapping to Hiragana. An application must specify LCMAP_FULLWIDTH if it wants half-width Katakana
 * characters mapped to Hiragana.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails, and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * Even though Windows CE supports only the Unicode version of this function, the output string is
 * only in WCHAR or CHAR format if the string mapping mode of LCMapString is used. If the sort key
 * generation mode is used, specified by LCMAP_SORTKEY, the output is an array of byte values. An
 * application can compare sort keys by using a byte-by-byte comparison.
 *
 * An application can call the function with the NORM_IGNORENONSPACE and NORM_IGNORESYMBOLS flags
 * set, and all other options flags cleared, in order to simply strip characters from the input
 * string. If this is done with an input string that is not null-terminated, it is possible for
 * LCMapString to return an empty string and not return an error.
 *
 * The LCMapString function ignores the Arabic Kashida. If an application calls the function to
 * create a sort key for a string that contains an Arabic Kashida, there will be no sort key value
 * for the Kashida.
 *
 * The function treats the hyphen and apostrophe a bit differently than other punctuation symbols,
 * so that words like coop and co-op stay together in a list. All punctuation symbols other than the
 * hyphen and apostrophe sort before the alphanumeric characters. An application can change this
 * behavior by setting the SORT_STRINGSORT flag. See CompareString for a more detailed discussion of
 * this issue.
 *
 * When LCMapString is used to generate a sort key, by setting the LC_MAPSORTKEY flag, the sort key
 * stored into *lpDestStr may contain an odd number of bytes. The LCMAP_BYTEREV option only reverses
 * an even number of bytes. If both options are chosen, the last (odd-positioned) byte in the sort
 * key is not reversed. If the terminating 0x00 byte is an odd-positioned byte, then it remains the
 * last byte in the sort key. If the terminating 0x00 byte is an even-positioned byte, it exchanges
 * positions with the byte that precedes it.
 */
int WINAPI LCMapStringW(LCID Locale, DWORD dwMapFlags, LPCWSTR lpSrcStr,
	int cchSrc, LPWSTR lpDestStr, int cchDest);

#ifdef UNICODE
/**
 * This function maps one character string to another, performing a specified locale-dependent
 * transformation. LCMapString can also be used to generate a sort key for the input string.
 *
 * @param Locale [in] Specifies a locale identifier. The locale provides a context for the string
 *   mapping or sort key generation. An application can use the MAKELCID macro to create a locale
 *   identifier.
 * @param dwMapFlags [in] Specifies the type of transformation to be used during string mapping or
 *   sort key generation. An application can specify more than one of these options on a single
 *   transformation, although some combinations are invalid. The following mapping options are
 *   defined; restrictions are noted following the table: Value Description LCMAP_BYTEREV Use byte
 *   reversal. For example, if you pass in 0x3450 0x4822 the result is 0x5034 0x2248. LCMAP_FULLWIDTH
 *   Wide characters (where applicable). LCMAP_HALFWIDTH Narrow characters (where applicable).
 *   LCMAP_HIRAGANA Hiragana. LCMAP_KATAKANA Katakana. LCMAP_LOWERCASE Use lowercase. LCMAP_SORTKEY
 *   Produce a normalized wide-character sort key. LCMAP_UPPERCASE Use uppercase. NORM_IGNORECASE
 *   Ignore case. NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters.
 *   Corresponding Hiragana and Katakana will compare as equal. NORM_IGNORENONSPACE Ignore nonspacing.
 *   This flag also removes Japanese accent characters. NORM_IGNORESYMBOLS Ignore symbols.
 *   NORM_IGNOREWIDTH Do not differentiate between a single-byte character and the same character as a
 *   double-byte character. SORT_STRINGSORT Treat punctuation the same as symbols. If the
 *   LCMAP_SORTKEY flag is not specified, the LCMapString function performs string mapping. In this
 *   case the following restrictions apply: LCMAP_LOWERCASE and LCMAP_UPPERCASE are mutually
 *   exclusive. LCMAP_HIRAGANA and LCMAP_KATAKANA are mutually exclusive. LCMAP_HALFWIDTH and
 *   LCMAP_FULLWIDTH are mutually exclusive. SORT_STRINGSORT, NORM_IGNOREKANATYPE, NORM_IGNOREWIDTH,
 *   and NORM_IGNORECASE are not valid. LCMAP_TRADITIONAL_CHINESE and LCMAP_SIMPLIFIED_CHINESE are
 *   mutually exclusive. LCMAP_LOWERCASE and LCMAP_UPPERCASE are not valid in combination with any of
 *   the following flags: LCMAP_HIRAGANA, LCMAP_KATAKANA, LCMAP_HALFWIDTH, and LCMAP_FULLWIDTH. When
 *   the LCMAP_SORTKEY flag is specified, the LCMapString function generates a sort key. In this case
 *   the following restriction applies: LCMAP_SORTKEY is mutually exclusive with all other LCMAP_*
 *   flags, with the sole exception of LCMAP_BYTEREV.
 * @param lpSrcStr [in] Pointer to a source string that the function maps or uses for sort key
 *   generation.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. This count can include the NULL terminator, or not include it. If the NULL terminator
 *   is included in the character count, it does not greatly affect the mapping behavior. That is
 *   because NULL is considered to be unsortable, and always maps to itself. A cchSrc value of -1
 *   specifies that the string pointed to by lpSrcStr is null-terminated. If this is the case, and
 *   LCMapString is being used in its string-mapping mode, the function calculates the string's length
 *   itself, and null-terminates the mapped string stored into *lpDestStr.
 * @param lpDestStr [out] Long pointer to a buffer into which the function stores the mapped string
 *   or sort key. If LCMAP_SORTKEY is specified, LCMapString stores a sort key into the buffer. The
 *   sort key is stored as an array of byte values in the following format: Note that the sort key is
 *   null-terminated. This is true regardless of the value of cchSrc. Also note that, even if some of
 *   the sort weights are absent from the sort key, due to the presence of one or more ignore flags in
 *   dwMapFlags, the 0x01 separators and the 0x00 terminator are still present.
 * @param cchDest [in] Specifies the size, in characters, of the buffer pointed to by lpDestStr. If
 *   the function is being used for string mapping, the size is a character count. If space for a NULL
 *   terminator is included in cchSrc, then cchDest must also include space for a NULL terminator. If
 *   the function is being used to generate a sort key, the size is a byte count. This byte count must
 *   include space for the sort key 0x00 terminator. If cchDest is zero, the function's return value
 *   is the number of characters, or bytes if LCMAP_SORTKEY is specified, required to hold the mapped
 *   string or sort key. In this case, the buffer pointed to by lpDestStr is not used.
 *
 * @return If the value of cchDest is nonzero, the number of characters, or bytes if LCMAP_SORTKEY
 *   is specified, written to the buffer indicates success. This count includes room for a NULL
 *   terminator. If the value of cchDest is zero, the size of the buffer in characters, or bytes if
 *   LCMAP_SORTKEY is specified, required to receive the translated string or sort key indicates
 *   success. This size includes room for a NULL terminator. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null terminated if the source string is null terminated.
 *
 * If the LCMAP_HIRAGANA flag is specified to map Katakana characters to Hiragana characters, and
 * LCMAP_FULLWIDTH is not specified, the function only maps full-width characters to Hiragana. In
 * this case, any half-width Katakana characters are placed as-is in the output string, with no
 * mapping to Hiragana. An application must specify LCMAP_FULLWIDTH if it wants half-width Katakana
 * characters mapped to Hiragana.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails, and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * Even though Windows CE supports only the Unicode version of this function, the output string is
 * only in WCHAR or CHAR format if the string mapping mode of LCMapString is used. If the sort key
 * generation mode is used, specified by LCMAP_SORTKEY, the output is an array of byte values. An
 * application can compare sort keys by using a byte-by-byte comparison.
 *
 * An application can call the function with the NORM_IGNORENONSPACE and NORM_IGNORESYMBOLS flags
 * set, and all other options flags cleared, in order to simply strip characters from the input
 * string. If this is done with an input string that is not null-terminated, it is possible for
 * LCMapString to return an empty string and not return an error.
 *
 * The LCMapString function ignores the Arabic Kashida. If an application calls the function to
 * create a sort key for a string that contains an Arabic Kashida, there will be no sort key value
 * for the Kashida.
 *
 * The function treats the hyphen and apostrophe a bit differently than other punctuation symbols,
 * so that words like coop and co-op stay together in a list. All punctuation symbols other than the
 * hyphen and apostrophe sort before the alphanumeric characters. An application can change this
 * behavior by setting the SORT_STRINGSORT flag. See CompareString for a more detailed discussion of
 * this issue.
 *
 * When LCMapString is used to generate a sort key, by setting the LC_MAPSORTKEY flag, the sort key
 * stored into *lpDestStr may contain an odd number of bytes. The LCMAP_BYTEREV option only reverses
 * an even number of bytes. If both options are chosen, the last (odd-positioned) byte in the sort
 * key is not reversed. If the terminating 0x00 byte is an odd-positioned byte, then it remains the
 * last byte in the sort key. If the terminating 0x00 byte is an even-positioned byte, it exchanges
 * positions with the byte that precedes it.
 */
#define LCMapString  LCMapStringW
#else
/**
 * This function maps one character string to another, performing a specified locale-dependent
 * transformation. LCMapString can also be used to generate a sort key for the input string.
 *
 * @param Locale [in] Specifies a locale identifier. The locale provides a context for the string
 *   mapping or sort key generation. An application can use the MAKELCID macro to create a locale
 *   identifier.
 * @param dwMapFlags [in] Specifies the type of transformation to be used during string mapping or
 *   sort key generation. An application can specify more than one of these options on a single
 *   transformation, although some combinations are invalid. The following mapping options are
 *   defined; restrictions are noted following the table: Value Description LCMAP_BYTEREV Use byte
 *   reversal. For example, if you pass in 0x3450 0x4822 the result is 0x5034 0x2248. LCMAP_FULLWIDTH
 *   Wide characters (where applicable). LCMAP_HALFWIDTH Narrow characters (where applicable).
 *   LCMAP_HIRAGANA Hiragana. LCMAP_KATAKANA Katakana. LCMAP_LOWERCASE Use lowercase. LCMAP_SORTKEY
 *   Produce a normalized wide-character sort key. LCMAP_UPPERCASE Use uppercase. NORM_IGNORECASE
 *   Ignore case. NORM_IGNOREKANATYPE Do not differentiate between Hiragana and Katakana characters.
 *   Corresponding Hiragana and Katakana will compare as equal. NORM_IGNORENONSPACE Ignore nonspacing.
 *   This flag also removes Japanese accent characters. NORM_IGNORESYMBOLS Ignore symbols.
 *   NORM_IGNOREWIDTH Do not differentiate between a single-byte character and the same character as a
 *   double-byte character. SORT_STRINGSORT Treat punctuation the same as symbols. If the
 *   LCMAP_SORTKEY flag is not specified, the LCMapString function performs string mapping. In this
 *   case the following restrictions apply: LCMAP_LOWERCASE and LCMAP_UPPERCASE are mutually
 *   exclusive. LCMAP_HIRAGANA and LCMAP_KATAKANA are mutually exclusive. LCMAP_HALFWIDTH and
 *   LCMAP_FULLWIDTH are mutually exclusive. SORT_STRINGSORT, NORM_IGNOREKANATYPE, NORM_IGNOREWIDTH,
 *   and NORM_IGNORECASE are not valid. LCMAP_TRADITIONAL_CHINESE and LCMAP_SIMPLIFIED_CHINESE are
 *   mutually exclusive. LCMAP_LOWERCASE and LCMAP_UPPERCASE are not valid in combination with any of
 *   the following flags: LCMAP_HIRAGANA, LCMAP_KATAKANA, LCMAP_HALFWIDTH, and LCMAP_FULLWIDTH. When
 *   the LCMAP_SORTKEY flag is specified, the LCMapString function generates a sort key. In this case
 *   the following restriction applies: LCMAP_SORTKEY is mutually exclusive with all other LCMAP_*
 *   flags, with the sole exception of LCMAP_BYTEREV.
 * @param lpSrcStr [in] Pointer to a source string that the function maps or uses for sort key
 *   generation.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. This count can include the NULL terminator, or not include it. If the NULL terminator
 *   is included in the character count, it does not greatly affect the mapping behavior. That is
 *   because NULL is considered to be unsortable, and always maps to itself. A cchSrc value of -1
 *   specifies that the string pointed to by lpSrcStr is null-terminated. If this is the case, and
 *   LCMapString is being used in its string-mapping mode, the function calculates the string's length
 *   itself, and null-terminates the mapped string stored into *lpDestStr.
 * @param lpDestStr [out] Long pointer to a buffer into which the function stores the mapped string
 *   or sort key. If LCMAP_SORTKEY is specified, LCMapString stores a sort key into the buffer. The
 *   sort key is stored as an array of byte values in the following format: Note that the sort key is
 *   null-terminated. This is true regardless of the value of cchSrc. Also note that, even if some of
 *   the sort weights are absent from the sort key, due to the presence of one or more ignore flags in
 *   dwMapFlags, the 0x01 separators and the 0x00 terminator are still present.
 * @param cchDest [in] Specifies the size, in characters, of the buffer pointed to by lpDestStr. If
 *   the function is being used for string mapping, the size is a character count. If space for a NULL
 *   terminator is included in cchSrc, then cchDest must also include space for a NULL terminator. If
 *   the function is being used to generate a sort key, the size is a byte count. This byte count must
 *   include space for the sort key 0x00 terminator. If cchDest is zero, the function's return value
 *   is the number of characters, or bytes if LCMAP_SORTKEY is specified, required to hold the mapped
 *   string or sort key. In this case, the buffer pointed to by lpDestStr is not used.
 *
 * @return If the value of cchDest is nonzero, the number of characters, or bytes if LCMAP_SORTKEY
 *   is specified, written to the buffer indicates success. This count includes room for a NULL
 *   terminator. If the value of cchDest is zero, the size of the buffer in characters, or bytes if
 *   LCMAP_SORTKEY is specified, required to receive the translated string or sort key indicates
 *   success. This size includes room for a NULL terminator. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null terminated if the source string is null terminated.
 *
 * If the LCMAP_HIRAGANA flag is specified to map Katakana characters to Hiragana characters, and
 * LCMAP_FULLWIDTH is not specified, the function only maps full-width characters to Hiragana. In
 * this case, any half-width Katakana characters are placed as-is in the output string, with no
 * mapping to Hiragana. An application must specify LCMAP_FULLWIDTH if it wants half-width Katakana
 * characters mapped to Hiragana.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails, and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * Even though Windows CE supports only the Unicode version of this function, the output string is
 * only in WCHAR or CHAR format if the string mapping mode of LCMapString is used. If the sort key
 * generation mode is used, specified by LCMAP_SORTKEY, the output is an array of byte values. An
 * application can compare sort keys by using a byte-by-byte comparison.
 *
 * An application can call the function with the NORM_IGNORENONSPACE and NORM_IGNORESYMBOLS flags
 * set, and all other options flags cleared, in order to simply strip characters from the input
 * string. If this is done with an input string that is not null-terminated, it is possible for
 * LCMapString to return an empty string and not return an error.
 *
 * The LCMapString function ignores the Arabic Kashida. If an application calls the function to
 * create a sort key for a string that contains an Arabic Kashida, there will be no sort key value
 * for the Kashida.
 *
 * The function treats the hyphen and apostrophe a bit differently than other punctuation symbols,
 * so that words like coop and co-op stay together in a list. All punctuation symbols other than the
 * hyphen and apostrophe sort before the alphanumeric characters. An application can change this
 * behavior by setting the SORT_STRINGSORT flag. See CompareString for a more detailed discussion of
 * this issue.
 *
 * When LCMapString is used to generate a sort key, by setting the LC_MAPSORTKEY flag, the sort key
 * stored into *lpDestStr may contain an odd number of bytes. The LCMAP_BYTEREV option only reverses
 * an even number of bytes. If both options are chosen, the last (odd-positioned) byte in the sort
 * key is not reversed. If the terminating 0x00 byte is an odd-positioned byte, then it remains the
 * last byte in the sort key. If the terminating 0x00 byte is an even-positioned byte, it exchanges
 * positions with the byte that precedes it.
 */
#define LCMapString  LCMapStringA
#endif

/**
 * This function retrieves information about a locale.
 *
 * @param Locale [in] Specifies the locale to retrieve information for. This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale.
 * @param LCType [in] Specifies one of the LCTYPE constants to indicate the type of information to
 *   be retrieved. All LCTYPE values are mutually exclusive, with the exception of
 *   LOCALE_NOUSEROVERRIDE. An application may use the binary-OR operator to combine
 *   LOCALE_NOUSEROVERRIDE with any other LCTYPE value. If passed such an LCType value, the function
 *   bypasses user overrides, and returns the system default value for the requested LCID.
 * @param lpLCData [out] Pointer to a buffer to receive the requested data.
 * @param cchData [in] Specifies the size, in characters, of the lpLCData buffer. If cchData is
 *   zero, the function returns the number of characters required to hold the information, and the
 *   buffer pointed to by lpLCData is not used.
 *
 * @return The number of bytes or characters written to the destination buffer, or, if the cchData
 *   parameter is zero, the number of characters required to hold the locale information indicates
 *   success. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetLocaleInfo function always retrieves information in text format. If the information is a
 * numeric value, the function converts the number to text using decimal notation.
 */
int WINAPI GetLocaleInfoW(LCID Locale, LCTYPE LCType, LPWSTR lpLCData, int cchData);

#ifdef UNICODE
/**
 * This function retrieves information about a locale.
 *
 * @param Locale [in] Specifies the locale to retrieve information for. This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale.
 * @param LCType [in] Specifies one of the LCTYPE constants to indicate the type of information to
 *   be retrieved. All LCTYPE values are mutually exclusive, with the exception of
 *   LOCALE_NOUSEROVERRIDE. An application may use the binary-OR operator to combine
 *   LOCALE_NOUSEROVERRIDE with any other LCTYPE value. If passed such an LCType value, the function
 *   bypasses user overrides, and returns the system default value for the requested LCID.
 * @param lpLCData [out] Pointer to a buffer to receive the requested data.
 * @param cchData [in] Specifies the size, in characters, of the lpLCData buffer. If cchData is
 *   zero, the function returns the number of characters required to hold the information, and the
 *   buffer pointed to by lpLCData is not used.
 *
 * @return The number of bytes or characters written to the destination buffer, or, if the cchData
 *   parameter is zero, the number of characters required to hold the locale information indicates
 *   success. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetLocaleInfo function always retrieves information in text format. If the information is a
 * numeric value, the function converts the number to text using decimal notation.
 */
#define GetLocaleInfo  GetLocaleInfoW
#else
/**
 * This function retrieves information about a locale.
 *
 * @param Locale [in] Specifies the locale to retrieve information for. This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale.
 * @param LCType [in] Specifies one of the LCTYPE constants to indicate the type of information to
 *   be retrieved. All LCTYPE values are mutually exclusive, with the exception of
 *   LOCALE_NOUSEROVERRIDE. An application may use the binary-OR operator to combine
 *   LOCALE_NOUSEROVERRIDE with any other LCTYPE value. If passed such an LCType value, the function
 *   bypasses user overrides, and returns the system default value for the requested LCID.
 * @param lpLCData [out] Pointer to a buffer to receive the requested data.
 * @param cchData [in] Specifies the size, in characters, of the lpLCData buffer. If cchData is
 *   zero, the function returns the number of characters required to hold the information, and the
 *   buffer pointed to by lpLCData is not used.
 *
 * @return The number of bytes or characters written to the destination buffer, or, if the cchData
 *   parameter is zero, the number of characters required to hold the locale information indicates
 *   success. Zero indicates failure. To get extended error information, call GetLastError. Possible
 *   values for GetLastError include the following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetLocaleInfo function always retrieves information in text format. If the information is a
 * numeric value, the function converts the number to text using decimal notation.
 */
#define GetLocaleInfo  GetLocaleInfoA
#endif

/**
 * This function sets an item of locale information. It does so by making an entry in the process
 * portion of the locale table. This setting only affects the user override portion of the locale
 * settings; it does not set the system defaults.
 *
 * @param Locale [in] Specifies the locale whose information the function will set. The locale
 *   provides a context for the string mapping or sort key generation. An application can use the
 *   MAKELCID macro to create a locale identifier.
 * @param LCType [in] Specifies the type of locale information to be set by the function. Note that
 *   only one LCTYPE may be specified per call. Not all LCTYPE values are valid; see the list of valid
 *   LCTYPE values in the following Remarks section.
 * @param lpLCData [in] Pointer to a null-terminated string that contains the locale information the
 *   function will set. The information must be in the specified LCTYPE's particular format.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_ACCESS
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The following LCTYPE values are valid for this function:
 *
 * LOCALE_ICALENDARTYPE LOCALE_SDATE LOCALE_ICURRDIGITS LOCALE_SDECIMAL LOCALE_ICURRENCY
 * LOCALE_SGROUPING LOCALE_IDIGITS LOCALE_SLIST LOCALE_IFIRSTDAYOFWEEK LOCALE_SLONGDATE
 * LOCALE_IFIRSTWEEKOFYEAR LOCALE_SMONDECIMALSEP LOCALE_ILZERO LOCALE_SMONGROUPING LOCALE_IMEASURE
 * LOCALE_SMONTHOUSANDSEP LOCALE_INEGCURR LOCALE_SNEGATIVESIGN LOCALE_INEGNUMBER
 * LOCALE_SPOSITIVESIGN LOCALE_IPAPERSIZE LOCALE_SSHORTDATE LOCALE_ITIME LOCALE_STHOUSAND
 * LOCALE_S1159 LOCALE_STIME LOCALE_S2359 LOCALE_STIMEFORMAT LOCALE_SCURRENCY LOCALE_SYEARMONTH
 *
 * Windows CE versions 1.0 through 2.01 do not support the LOCALE_IPAPERSIZE LCTYPE value.
 */
BOOL WINAPI SetLocaleInfoW(LCID Locale, LCTYPE LCType, LPCWSTR lpLCData);

#ifdef UNICODE
/**
 * This function sets an item of locale information. It does so by making an entry in the process
 * portion of the locale table. This setting only affects the user override portion of the locale
 * settings; it does not set the system defaults.
 *
 * @param Locale [in] Specifies the locale whose information the function will set. The locale
 *   provides a context for the string mapping or sort key generation. An application can use the
 *   MAKELCID macro to create a locale identifier.
 * @param LCType [in] Specifies the type of locale information to be set by the function. Note that
 *   only one LCTYPE may be specified per call. Not all LCTYPE values are valid; see the list of valid
 *   LCTYPE values in the following Remarks section.
 * @param lpLCData [in] Pointer to a null-terminated string that contains the locale information the
 *   function will set. The information must be in the specified LCTYPE's particular format.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_ACCESS
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The following LCTYPE values are valid for this function:
 *
 * LOCALE_ICALENDARTYPE LOCALE_SDATE LOCALE_ICURRDIGITS LOCALE_SDECIMAL LOCALE_ICURRENCY
 * LOCALE_SGROUPING LOCALE_IDIGITS LOCALE_SLIST LOCALE_IFIRSTDAYOFWEEK LOCALE_SLONGDATE
 * LOCALE_IFIRSTWEEKOFYEAR LOCALE_SMONDECIMALSEP LOCALE_ILZERO LOCALE_SMONGROUPING LOCALE_IMEASURE
 * LOCALE_SMONTHOUSANDSEP LOCALE_INEGCURR LOCALE_SNEGATIVESIGN LOCALE_INEGNUMBER
 * LOCALE_SPOSITIVESIGN LOCALE_IPAPERSIZE LOCALE_SSHORTDATE LOCALE_ITIME LOCALE_STHOUSAND
 * LOCALE_S1159 LOCALE_STIME LOCALE_S2359 LOCALE_STIMEFORMAT LOCALE_SCURRENCY LOCALE_SYEARMONTH
 *
 * Windows CE versions 1.0 through 2.01 do not support the LOCALE_IPAPERSIZE LCTYPE value.
 */
#define SetLocaleInfo  SetLocaleInfoW
#else
/**
 * This function sets an item of locale information. It does so by making an entry in the process
 * portion of the locale table. This setting only affects the user override portion of the locale
 * settings; it does not set the system defaults.
 *
 * @param Locale [in] Specifies the locale whose information the function will set. The locale
 *   provides a context for the string mapping or sort key generation. An application can use the
 *   MAKELCID macro to create a locale identifier.
 * @param LCType [in] Specifies the type of locale information to be set by the function. Note that
 *   only one LCTYPE may be specified per call. Not all LCTYPE values are valid; see the list of valid
 *   LCTYPE values in the following Remarks section.
 * @param lpLCData [in] Pointer to a null-terminated string that contains the locale information the
 *   function will set. The information must be in the specified LCTYPE's particular format.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_ACCESS
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The following LCTYPE values are valid for this function:
 *
 * LOCALE_ICALENDARTYPE LOCALE_SDATE LOCALE_ICURRDIGITS LOCALE_SDECIMAL LOCALE_ICURRENCY
 * LOCALE_SGROUPING LOCALE_IDIGITS LOCALE_SLIST LOCALE_IFIRSTDAYOFWEEK LOCALE_SLONGDATE
 * LOCALE_IFIRSTWEEKOFYEAR LOCALE_SMONDECIMALSEP LOCALE_ILZERO LOCALE_SMONGROUPING LOCALE_IMEASURE
 * LOCALE_SMONTHOUSANDSEP LOCALE_INEGCURR LOCALE_SNEGATIVESIGN LOCALE_INEGNUMBER
 * LOCALE_SPOSITIVESIGN LOCALE_IPAPERSIZE LOCALE_SSHORTDATE LOCALE_ITIME LOCALE_STHOUSAND
 * LOCALE_S1159 LOCALE_STIME LOCALE_S2359 LOCALE_STIMEFORMAT LOCALE_SCURRENCY LOCALE_SYEARMONTH
 *
 * Windows CE versions 1.0 through 2.01 do not support the LOCALE_IPAPERSIZE LCTYPE value.
 */
#define SetLocaleInfo  SetLocaleInfoA
#endif

/**
 * This function formats a time as a time string for a specified locale. The function formats either
 * a specified time or the local system time.
 *
 * @param Locale [in] Specifies the locale for which the time string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the time format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's time markers). This parameter can be a locale
 *   identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. You can specify a combination of the
 *   following flags: Value Description TIME_NOMINUTESORSECONDS Do not use minutes or seconds.
 *   TIME_NOSECONDS Do not use seconds. TIME_NOTIMEMARKER Do not use a time marker.
 *   TIME_FORCE24HOURFORMAT Always use a 24-hour time format. LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default time format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default time
 *   format. This flag cannot be set if lpFormat is non-NULL.
 * @param lpTime [in] Pointer to a SYSTEMTIME structure that contains the time information to be
 *   formatted. If this pointer is NULL, the function uses the current local system time.
 * @param lpFormat [in] Pointer to a format picture to use to form the time string. If lpFormat is
 *   NULL, the function uses the time format of the specified locale. Use the following elements to
 *   construct a format picture string. If you use spaces to separate the elements in the format
 *   string, these spaces will appear in the same location in the output string. The letters must be
 *   in uppercase or lowercase as shown (for example, "ss", not "SS"). Characters in the format string
 *   that are enclosed in single quotation marks will appear in the same location and unchanged in the
 *   output string. Value Description h Hours with no leading zero for single-digit hours; 12-hour
 *   clock hh Hours with leading zero for single-digit hours; 12-hour clock H Hours with no leading
 *   zero for single-digit hours; 24-hour clock HH Hours with leading zero for single-digit hours;
 *   24-hour clock m Minutes with no leading zero for single-digit minutes mm Minutes with leading
 *   zero for single-digit minutes s Seconds with no leading zero for single-digit seconds ss Seconds
 *   with leading zero for single-digit seconds t One character time marker string, such as A or P tt
 *   Multicharacter time marker string, such as AM or PM For example, to get the time string "11:29:40
 *   PM" use the following picture string: "hh':'mm':'ss tt"
 * @param lpTimeStr [out] Pointer to a buffer that receives the formatted time string.
 * @param cchTime [in] Specifies the size, in characters, of the lpTimeStr buffer. If cchTime is
 *   zero, the function returns the number of characters required to hold the formatted time string,
 *   and the buffer pointed to by lpTimeStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpTimeStr indicates success.
 *   If the cchTime parameter is zero, the number of characters required to hold the formatted time
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * If a time marker exists and the TIME_NOTIMEMARKER flag is not set, the function localizes the
 * time marker based on the specified locale identifier. Examples of time markers are "AM" and "PM"
 * for US English.
 *
 * The time values in the SYSTEMTIME structure pointed to by lpTime must be valid. The function
 * checks each of the time values to determine that it is within the appropriate range of values. If
 * any of the time values are outside the correct range, the function fails, and sets the last-error
 * to ERROR_INVALID_PARAMETER.
 *
 * The function ignores the date portions of the SYSTEMTIME structure pointed to by lpTime: wYear,
 * wMonth, wDayOfWeek, and wDay.
 *
 * If TIME_NOMINUTESORSECONDS or TIME_NOSECONDS is specified, the function removes the separator(s)
 * preceding the minutes and/or seconds element(s).
 *
 * If TIME_NOTIMEMARKER is specified, the function removes the separator(s) preceding and following
 * the time marker.
 *
 * If TIME_FORCE24HOURFORMAT is specified, the function displays any existing time marker, unless
 * the TIME_NOTIMEMARKER flag is also set.
 *
 * The function does not include milliseconds as part of the formatted time string.
 *
 * To use the LOCALE_NOUSEROVERRIDE flag, lpFormat must be NULL.
 *
 * No errors are returned for a bad format string. The function simply forms the best time string
 * that it can. If more than two hour, minute, second, or time marker format pictures are passed in,
 * then the function defaults to two. For example, the only time marker pictures that are valid are
 * L"t" and L"tt" .The 'L' indicates a string consisting of Unicode 16-bit characters. If L"ttt" is
 * passed in, the function assumes L"tt".
 */
int WINAPI GetTimeFormatW(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpTime,
    LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime);

#ifdef UNICODE
/**
 * This function formats a time as a time string for a specified locale. The function formats either
 * a specified time or the local system time.
 *
 * @param Locale [in] Specifies the locale for which the time string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the time format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's time markers). This parameter can be a locale
 *   identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. You can specify a combination of the
 *   following flags: Value Description TIME_NOMINUTESORSECONDS Do not use minutes or seconds.
 *   TIME_NOSECONDS Do not use seconds. TIME_NOTIMEMARKER Do not use a time marker.
 *   TIME_FORCE24HOURFORMAT Always use a 24-hour time format. LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default time format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default time
 *   format. This flag cannot be set if lpFormat is non-NULL.
 * @param lpTime [in] Pointer to a SYSTEMTIME structure that contains the time information to be
 *   formatted. If this pointer is NULL, the function uses the current local system time.
 * @param lpFormat [in] Pointer to a format picture to use to form the time string. If lpFormat is
 *   NULL, the function uses the time format of the specified locale. Use the following elements to
 *   construct a format picture string. If you use spaces to separate the elements in the format
 *   string, these spaces will appear in the same location in the output string. The letters must be
 *   in uppercase or lowercase as shown (for example, "ss", not "SS"). Characters in the format string
 *   that are enclosed in single quotation marks will appear in the same location and unchanged in the
 *   output string. Value Description h Hours with no leading zero for single-digit hours; 12-hour
 *   clock hh Hours with leading zero for single-digit hours; 12-hour clock H Hours with no leading
 *   zero for single-digit hours; 24-hour clock HH Hours with leading zero for single-digit hours;
 *   24-hour clock m Minutes with no leading zero for single-digit minutes mm Minutes with leading
 *   zero for single-digit minutes s Seconds with no leading zero for single-digit seconds ss Seconds
 *   with leading zero for single-digit seconds t One character time marker string, such as A or P tt
 *   Multicharacter time marker string, such as AM or PM For example, to get the time string "11:29:40
 *   PM" use the following picture string: "hh':'mm':'ss tt"
 * @param lpTimeStr [out] Pointer to a buffer that receives the formatted time string.
 * @param cchTime [in] Specifies the size, in characters, of the lpTimeStr buffer. If cchTime is
 *   zero, the function returns the number of characters required to hold the formatted time string,
 *   and the buffer pointed to by lpTimeStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpTimeStr indicates success.
 *   If the cchTime parameter is zero, the number of characters required to hold the formatted time
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * If a time marker exists and the TIME_NOTIMEMARKER flag is not set, the function localizes the
 * time marker based on the specified locale identifier. Examples of time markers are "AM" and "PM"
 * for US English.
 *
 * The time values in the SYSTEMTIME structure pointed to by lpTime must be valid. The function
 * checks each of the time values to determine that it is within the appropriate range of values. If
 * any of the time values are outside the correct range, the function fails, and sets the last-error
 * to ERROR_INVALID_PARAMETER.
 *
 * The function ignores the date portions of the SYSTEMTIME structure pointed to by lpTime: wYear,
 * wMonth, wDayOfWeek, and wDay.
 *
 * If TIME_NOMINUTESORSECONDS or TIME_NOSECONDS is specified, the function removes the separator(s)
 * preceding the minutes and/or seconds element(s).
 *
 * If TIME_NOTIMEMARKER is specified, the function removes the separator(s) preceding and following
 * the time marker.
 *
 * If TIME_FORCE24HOURFORMAT is specified, the function displays any existing time marker, unless
 * the TIME_NOTIMEMARKER flag is also set.
 *
 * The function does not include milliseconds as part of the formatted time string.
 *
 * To use the LOCALE_NOUSEROVERRIDE flag, lpFormat must be NULL.
 *
 * No errors are returned for a bad format string. The function simply forms the best time string
 * that it can. If more than two hour, minute, second, or time marker format pictures are passed in,
 * then the function defaults to two. For example, the only time marker pictures that are valid are
 * L"t" and L"tt" .The 'L' indicates a string consisting of Unicode 16-bit characters. If L"ttt" is
 * passed in, the function assumes L"tt".
 */
#define GetTimeFormat  GetTimeFormatW
#else
/**
 * This function formats a time as a time string for a specified locale. The function formats either
 * a specified time or the local system time.
 *
 * @param Locale [in] Specifies the locale for which the time string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the time format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's time markers). This parameter can be a locale
 *   identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. You can specify a combination of the
 *   following flags: Value Description TIME_NOMINUTESORSECONDS Do not use minutes or seconds.
 *   TIME_NOSECONDS Do not use seconds. TIME_NOTIMEMARKER Do not use a time marker.
 *   TIME_FORCE24HOURFORMAT Always use a 24-hour time format. LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default time format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default time
 *   format. This flag cannot be set if lpFormat is non-NULL.
 * @param lpTime [in] Pointer to a SYSTEMTIME structure that contains the time information to be
 *   formatted. If this pointer is NULL, the function uses the current local system time.
 * @param lpFormat [in] Pointer to a format picture to use to form the time string. If lpFormat is
 *   NULL, the function uses the time format of the specified locale. Use the following elements to
 *   construct a format picture string. If you use spaces to separate the elements in the format
 *   string, these spaces will appear in the same location in the output string. The letters must be
 *   in uppercase or lowercase as shown (for example, "ss", not "SS"). Characters in the format string
 *   that are enclosed in single quotation marks will appear in the same location and unchanged in the
 *   output string. Value Description h Hours with no leading zero for single-digit hours; 12-hour
 *   clock hh Hours with leading zero for single-digit hours; 12-hour clock H Hours with no leading
 *   zero for single-digit hours; 24-hour clock HH Hours with leading zero for single-digit hours;
 *   24-hour clock m Minutes with no leading zero for single-digit minutes mm Minutes with leading
 *   zero for single-digit minutes s Seconds with no leading zero for single-digit seconds ss Seconds
 *   with leading zero for single-digit seconds t One character time marker string, such as A or P tt
 *   Multicharacter time marker string, such as AM or PM For example, to get the time string "11:29:40
 *   PM" use the following picture string: "hh':'mm':'ss tt"
 * @param lpTimeStr [out] Pointer to a buffer that receives the formatted time string.
 * @param cchTime [in] Specifies the size, in characters, of the lpTimeStr buffer. If cchTime is
 *   zero, the function returns the number of characters required to hold the formatted time string,
 *   and the buffer pointed to by lpTimeStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpTimeStr indicates success.
 *   If the cchTime parameter is zero, the number of characters required to hold the formatted time
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * If a time marker exists and the TIME_NOTIMEMARKER flag is not set, the function localizes the
 * time marker based on the specified locale identifier. Examples of time markers are "AM" and "PM"
 * for US English.
 *
 * The time values in the SYSTEMTIME structure pointed to by lpTime must be valid. The function
 * checks each of the time values to determine that it is within the appropriate range of values. If
 * any of the time values are outside the correct range, the function fails, and sets the last-error
 * to ERROR_INVALID_PARAMETER.
 *
 * The function ignores the date portions of the SYSTEMTIME structure pointed to by lpTime: wYear,
 * wMonth, wDayOfWeek, and wDay.
 *
 * If TIME_NOMINUTESORSECONDS or TIME_NOSECONDS is specified, the function removes the separator(s)
 * preceding the minutes and/or seconds element(s).
 *
 * If TIME_NOTIMEMARKER is specified, the function removes the separator(s) preceding and following
 * the time marker.
 *
 * If TIME_FORCE24HOURFORMAT is specified, the function displays any existing time marker, unless
 * the TIME_NOTIMEMARKER flag is also set.
 *
 * The function does not include milliseconds as part of the formatted time string.
 *
 * To use the LOCALE_NOUSEROVERRIDE flag, lpFormat must be NULL.
 *
 * No errors are returned for a bad format string. The function simply forms the best time string
 * that it can. If more than two hour, minute, second, or time marker format pictures are passed in,
 * then the function defaults to two. For example, the only time marker pictures that are valid are
 * L"t" and L"tt" .The 'L' indicates a string consisting of Unicode 16-bit characters. If L"ttt" is
 * passed in, the function assumes L"tt".
 */
#define GetTimeFormat  GetTimeFormatA
#endif

/**
 * This function formats a date as a date string for a specified locale. The function formats either
 * a specified date or the local system date.
 *
 * @param Locale [in] Specifies the locale for which the date string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the date format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's day and month names). This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values. Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. If lpFormat is non-NULL, this parameter
 *   must be zero. If lpFormat is NULL, you can specify a combination of the following flags: Value
 *   Description DATE_SHORTDATE Use the short date format. This is the default. Cannot be used with
 *   DATE_LONGDATE. DATE_LONGDATE Use the long date format. Cannot be used with DATE_SHORTDATE.
 *   DATE_LTRREADING Not supported. DATE_RTLREADING Not supported LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default date format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default-date
 *   format. LOCALE_USE_CP_ACP Not supported DATE_YEARMONTH Not supported. DATE_USE_ALT_CALENDAR Uses
 *   the alternate calendar, if one exists, to format the date string. If this flag is set, the
 *   function uses the default format for that alternate calendar, rather than using any user
 *   overrides. The user overrides will be used only in the event that there is no default format for
 *   the specified alternate calendar.
 * @param lpDate [in] Pointer to a SYSTEMTIME structure that contains the date information to be
 *   formatted. If this pointer is NULL, the function uses the current local system date.
 * @param lpFormat [in] Pointer to a format picture string to use to form the date string. If
 *   lpFormat is NULL, the function uses the date format of the specified locale. Use the following
 *   elements to construct a format picture string. If you use spaces to separate the elements in the
 *   format string, these spaces will appear in the same location in the output string. The letters
 *   must be in uppercase or lowercase as shown in the table (for example, "MM" not "mm"). Characters
 *   in the format string that are enclosed in single quotation marks will appear in the same location
 *   and unchanged in the output string. Value Description d Day of month as digits with no leading
 *   zero for single-digit days. dd Day of month as digits with leading zero for single-digit days.
 *   ddd Day of week as a three-letter abbreviation. The function uses the LOCALE_SABBREVDAYNAME value
 *   associated with the specified locale. dddd Day of week as its full name. The function uses the
 *   LOCALE_SDAYNAME value associated with the specified locale. M Month as digits with no leading
 *   zero for single-digit months. MM Month as digits with leading zero for single-digit months. MMM
 *   Month as a three-letter abbreviation. The function uses the LOCALE_SABBREVMONTHNAME value
 *   associated with the specified locale. MMMM Month as its full name. The function uses the
 *   LOCALE_SMONTHNAME value associated with the specified locale. y Year as last two digits, with a
 *   leading zero for years less than 10. The same format as "yy." yy Year as last two digits, with a
 *   leading zero for years less than 10. yyyy Year represented by full four digits. gg Period/era
 *   string. The function uses the CAL_SERASTRING value associated with the specified locale. This
 *   element is ignored if the date to be formatted does not have an associated era or period string.
 *   For example, to get the date string "Wed, Aug 31 94" use the following picture string: "ddd','
 *   MMM dd yy"
 * @param lpDateStr [out] Pointer to a buffer that receives the formatted date string.
 * @param cchDate [in] Specifies the size, in characters, of the lpDateStr buffer. If cchDate is
 *   zero, the function returns the number of characters required to hold the formatted date string,
 *   and the buffer pointed to by lpDateStr is not used.
 *
 * @return The number of characters written to the lpDateStr buffer, or, if the cchDate parameter is
 *   zero, the number of characters required to hold the formatted date string indicates success. The
 *   count includes the terminating null. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The day name, abbreviated day name, month name, and abbreviated month name are all localized
 * based on the given locale identifier.
 *
 * The date values in the SYSTEMTIME structure pointed to by lpDate must be valid. The function
 * checks each of the date values: year, month, day, and day of week. If the day of the week is
 * incorrect, the function uses the correct value, and returns no error. If any of the other date
 * values are outside the correct range, the function fails, and sets the last-error to
 * ERROR_INVALID_PARAMETER.
 *
 * The function ignores the time portions of the SYSTEMTIME structure pointed to by lpDate: wHour,
 * wMinute, wSecond, and wMilliseconds.
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flag options are mutually exclusive. If neither one is
 * specified and lpFormat is NULL, then DATE_SHORTDATE is the default.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date (L"dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 */
int WINAPI GetDateFormatW(LCID Locale, DWORD dwFlags, const SYSTEMTIME *lpDate,
    LPCWSTR lpFormat, LPWSTR lpDateStr, int cchDate);

#ifdef UNICODE
/**
 * This function formats a date as a date string for a specified locale. The function formats either
 * a specified date or the local system date.
 *
 * @param Locale [in] Specifies the locale for which the date string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the date format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's day and month names). This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values. Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. If lpFormat is non-NULL, this parameter
 *   must be zero. If lpFormat is NULL, you can specify a combination of the following flags: Value
 *   Description DATE_SHORTDATE Use the short date format. This is the default. Cannot be used with
 *   DATE_LONGDATE. DATE_LONGDATE Use the long date format. Cannot be used with DATE_SHORTDATE.
 *   DATE_LTRREADING Not supported. DATE_RTLREADING Not supported LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default date format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default-date
 *   format. LOCALE_USE_CP_ACP Not supported DATE_YEARMONTH Not supported. DATE_USE_ALT_CALENDAR Uses
 *   the alternate calendar, if one exists, to format the date string. If this flag is set, the
 *   function uses the default format for that alternate calendar, rather than using any user
 *   overrides. The user overrides will be used only in the event that there is no default format for
 *   the specified alternate calendar.
 * @param lpDate [in] Pointer to a SYSTEMTIME structure that contains the date information to be
 *   formatted. If this pointer is NULL, the function uses the current local system date.
 * @param lpFormat [in] Pointer to a format picture string to use to form the date string. If
 *   lpFormat is NULL, the function uses the date format of the specified locale. Use the following
 *   elements to construct a format picture string. If you use spaces to separate the elements in the
 *   format string, these spaces will appear in the same location in the output string. The letters
 *   must be in uppercase or lowercase as shown in the table (for example, "MM" not "mm"). Characters
 *   in the format string that are enclosed in single quotation marks will appear in the same location
 *   and unchanged in the output string. Value Description d Day of month as digits with no leading
 *   zero for single-digit days. dd Day of month as digits with leading zero for single-digit days.
 *   ddd Day of week as a three-letter abbreviation. The function uses the LOCALE_SABBREVDAYNAME value
 *   associated with the specified locale. dddd Day of week as its full name. The function uses the
 *   LOCALE_SDAYNAME value associated with the specified locale. M Month as digits with no leading
 *   zero for single-digit months. MM Month as digits with leading zero for single-digit months. MMM
 *   Month as a three-letter abbreviation. The function uses the LOCALE_SABBREVMONTHNAME value
 *   associated with the specified locale. MMMM Month as its full name. The function uses the
 *   LOCALE_SMONTHNAME value associated with the specified locale. y Year as last two digits, with a
 *   leading zero for years less than 10. The same format as "yy." yy Year as last two digits, with a
 *   leading zero for years less than 10. yyyy Year represented by full four digits. gg Period/era
 *   string. The function uses the CAL_SERASTRING value associated with the specified locale. This
 *   element is ignored if the date to be formatted does not have an associated era or period string.
 *   For example, to get the date string "Wed, Aug 31 94" use the following picture string: "ddd','
 *   MMM dd yy"
 * @param lpDateStr [out] Pointer to a buffer that receives the formatted date string.
 * @param cchDate [in] Specifies the size, in characters, of the lpDateStr buffer. If cchDate is
 *   zero, the function returns the number of characters required to hold the formatted date string,
 *   and the buffer pointed to by lpDateStr is not used.
 *
 * @return The number of characters written to the lpDateStr buffer, or, if the cchDate parameter is
 *   zero, the number of characters required to hold the formatted date string indicates success. The
 *   count includes the terminating null. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The day name, abbreviated day name, month name, and abbreviated month name are all localized
 * based on the given locale identifier.
 *
 * The date values in the SYSTEMTIME structure pointed to by lpDate must be valid. The function
 * checks each of the date values: year, month, day, and day of week. If the day of the week is
 * incorrect, the function uses the correct value, and returns no error. If any of the other date
 * values are outside the correct range, the function fails, and sets the last-error to
 * ERROR_INVALID_PARAMETER.
 *
 * The function ignores the time portions of the SYSTEMTIME structure pointed to by lpDate: wHour,
 * wMinute, wSecond, and wMilliseconds.
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flag options are mutually exclusive. If neither one is
 * specified and lpFormat is NULL, then DATE_SHORTDATE is the default.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date (L"dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 */
#define GetDateFormat  GetDateFormatW
#else
/**
 * This function formats a date as a date string for a specified locale. The function formats either
 * a specified date or the local system date.
 *
 * @param Locale [in] Specifies the locale for which the date string is to be formatted. If lpFormat
 *   is NULL, the function formats the string according to the date format for this locale. If
 *   lpFormat is not NULL, the function uses the locale only for information not specified in the
 *   format picture string (for example, the locale's day and month names). This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values. Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user locale.
 *   LOCALE_NEUTRAL Default language-neutral locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwFlags [in] Specifies various function options. If lpFormat is non-NULL, this parameter
 *   must be zero. If lpFormat is NULL, you can specify a combination of the following flags: Value
 *   Description DATE_SHORTDATE Use the short date format. This is the default. Cannot be used with
 *   DATE_LONGDATE. DATE_LONGDATE Use the long date format. Cannot be used with DATE_SHORTDATE.
 *   DATE_LTRREADING Not supported. DATE_RTLREADING Not supported LOCALE_NOUSEROVERRIDE If set, the
 *   function formats the string using the system default date format for the specified locale. If not
 *   set, the function formats the string using any user overrides to the locale's default-date
 *   format. LOCALE_USE_CP_ACP Not supported DATE_YEARMONTH Not supported. DATE_USE_ALT_CALENDAR Uses
 *   the alternate calendar, if one exists, to format the date string. If this flag is set, the
 *   function uses the default format for that alternate calendar, rather than using any user
 *   overrides. The user overrides will be used only in the event that there is no default format for
 *   the specified alternate calendar.
 * @param lpDate [in] Pointer to a SYSTEMTIME structure that contains the date information to be
 *   formatted. If this pointer is NULL, the function uses the current local system date.
 * @param lpFormat [in] Pointer to a format picture string to use to form the date string. If
 *   lpFormat is NULL, the function uses the date format of the specified locale. Use the following
 *   elements to construct a format picture string. If you use spaces to separate the elements in the
 *   format string, these spaces will appear in the same location in the output string. The letters
 *   must be in uppercase or lowercase as shown in the table (for example, "MM" not "mm"). Characters
 *   in the format string that are enclosed in single quotation marks will appear in the same location
 *   and unchanged in the output string. Value Description d Day of month as digits with no leading
 *   zero for single-digit days. dd Day of month as digits with leading zero for single-digit days.
 *   ddd Day of week as a three-letter abbreviation. The function uses the LOCALE_SABBREVDAYNAME value
 *   associated with the specified locale. dddd Day of week as its full name. The function uses the
 *   LOCALE_SDAYNAME value associated with the specified locale. M Month as digits with no leading
 *   zero for single-digit months. MM Month as digits with leading zero for single-digit months. MMM
 *   Month as a three-letter abbreviation. The function uses the LOCALE_SABBREVMONTHNAME value
 *   associated with the specified locale. MMMM Month as its full name. The function uses the
 *   LOCALE_SMONTHNAME value associated with the specified locale. y Year as last two digits, with a
 *   leading zero for years less than 10. The same format as "yy." yy Year as last two digits, with a
 *   leading zero for years less than 10. yyyy Year represented by full four digits. gg Period/era
 *   string. The function uses the CAL_SERASTRING value associated with the specified locale. This
 *   element is ignored if the date to be formatted does not have an associated era or period string.
 *   For example, to get the date string "Wed, Aug 31 94" use the following picture string: "ddd','
 *   MMM dd yy"
 * @param lpDateStr [out] Pointer to a buffer that receives the formatted date string.
 * @param cchDate [in] Specifies the size, in characters, of the lpDateStr buffer. If cchDate is
 *   zero, the function returns the number of characters required to hold the formatted date string,
 *   and the buffer pointed to by lpDateStr is not used.
 *
 * @return The number of characters written to the lpDateStr buffer, or, if the cchDate parameter is
 *   zero, the number of characters required to hold the formatted date string indicates success. The
 *   count includes the terminating null. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The day name, abbreviated day name, month name, and abbreviated month name are all localized
 * based on the given locale identifier.
 *
 * The date values in the SYSTEMTIME structure pointed to by lpDate must be valid. The function
 * checks each of the date values: year, month, day, and day of week. If the day of the week is
 * incorrect, the function uses the correct value, and returns no error. If any of the other date
 * values are outside the correct range, the function fails, and sets the last-error to
 * ERROR_INVALID_PARAMETER.
 *
 * The function ignores the time portions of the SYSTEMTIME structure pointed to by lpDate: wHour,
 * wMinute, wSecond, and wMilliseconds.
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flag options are mutually exclusive. If neither one is
 * specified and lpFormat is NULL, then DATE_SHORTDATE is the default.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 *
 * No errors are returned for a bad format string. The function simply forms the best date string
 * that it can. For example, the only year pictures that are valid are L"yyyy" and L"yy" (the 'L'
 * indicates a Unicode (16-bit characters) string). If L"y" is passed in, the function assumes
 * L"yy". If L"yyy" is passed in, the function assumes L"yyyy". If more than 4 date (L"dddd") or 4
 * month (L"MMMM") pictures are passed in, then the function defaults to L"dddd" or L"MMMM".
 *
 * Any text that should remain in its exact form in the date string should be enclosed within single
 * quotation marks in the date format picture. The single quotation mark may also be used as an
 * escape character to allow the single quotation mark itself to be displayed in the date string.
 * However, the escape sequence must be enclosed within two single quotation marks. For example, to
 * display the date as "May '93", the format string would be: L"MMMM ''''yy" The first and last
 * single quotation marks are the enclosing quotation marks. The second and third single quotation
 * marks are the escape sequence to allow the single quotation mark to be displayed before the
 * century.
 */
#define GetDateFormat  GetDateFormatA
#endif

/**
 * This function formats a number string as a number string customized for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the number string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the number format for this locale.
 *   If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the NUMBERFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values. Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Contains a bit flag that controls the operation of the function. If lpFormat
 *   is non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default number format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default number format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can only contain the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a NUMBERFMT structure that contains number formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the number format of the specified locale.
 * @param lpNumberStr [out] Pointer to a buffer to receive the formatted number string.
 * @param cchNumber [in] Specifies the size, in characters, of the lpNumberStr buffer. If cchNumber
 *   is zero, the function returns the number of characters required to hold the formatted number
 *   string, and the buffer pointed to by lpNumberStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpNumberStr, or, if the
 *   cchNumber parameter is zero, the number of characters required to hold the formatted number
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
int WINAPI GetNumberFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
    const NUMBERFMTW *lpFormat, LPWSTR lpNumberStr, int cchNumber);

#ifdef UNICODE
/**
 * This function formats a number string as a number string customized for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the number string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the number format for this locale.
 *   If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the NUMBERFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values. Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Contains a bit flag that controls the operation of the function. If lpFormat
 *   is non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default number format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default number format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can only contain the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a NUMBERFMT structure that contains number formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the number format of the specified locale.
 * @param lpNumberStr [out] Pointer to a buffer to receive the formatted number string.
 * @param cchNumber [in] Specifies the size, in characters, of the lpNumberStr buffer. If cchNumber
 *   is zero, the function returns the number of characters required to hold the formatted number
 *   string, and the buffer pointed to by lpNumberStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpNumberStr, or, if the
 *   cchNumber parameter is zero, the number of characters required to hold the formatted number
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
#define GetNumberFormat  GetNumberFormatW
#else
/**
 * This function formats a number string as a number string customized for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the number string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the number format for this locale.
 *   If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the NUMBERFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values. Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Contains a bit flag that controls the operation of the function. If lpFormat
 *   is non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default number format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default number format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can only contain the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a NUMBERFMT structure that contains number formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the number format of the specified locale.
 * @param lpNumberStr [out] Pointer to a buffer to receive the formatted number string.
 * @param cchNumber [in] Specifies the size, in characters, of the lpNumberStr buffer. If cchNumber
 *   is zero, the function returns the number of characters required to hold the formatted number
 *   string, and the buffer pointed to by lpNumberStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpNumberStr, or, if the
 *   cchNumber parameter is zero, the number of characters required to hold the formatted number
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
#define GetNumberFormat  GetNumberFormatA
#endif

/**
 * This function formats a number string as a currency string for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the currency string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the currency format for this
 *   locale. If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the CURRENCYFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] A bit flag that controls the operation of the function. If lpFormat is
 *   non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default currency format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default currency format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can contain only the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a CURRENCYFMT structure that contains currency formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the currency format of the specified locale.
 * @param lpCurrencyStr [out] Pointer to a buffer to receive the formatted currency string.
 * @param cchCurrency [in] Specifies the size, in characters, of the lpCurrencyStr buffer. If
 *   cchCurrency is zero, the function returns the number of bytes or characters required to hold the
 *   formatted currency string, and the buffer pointed to by lpCurrencyStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpCurrencyStr, or, if the
 *   cchCurrency parameter is zero, the number of characters required to hold the formatted currency
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
int WINAPI GetCurrencyFormatW(LCID Locale, DWORD dwFlags, LPCWSTR lpValue,
    const CURRENCYFMTW *lpFormat, LPWSTR  lpCurrencyStr, int cchCurrency);

#ifdef UNICODE
/**
 * This function formats a number string as a currency string for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the currency string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the currency format for this
 *   locale. If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the CURRENCYFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] A bit flag that controls the operation of the function. If lpFormat is
 *   non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default currency format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default currency format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can contain only the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a CURRENCYFMT structure that contains currency formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the currency format of the specified locale.
 * @param lpCurrencyStr [out] Pointer to a buffer to receive the formatted currency string.
 * @param cchCurrency [in] Specifies the size, in characters, of the lpCurrencyStr buffer. If
 *   cchCurrency is zero, the function returns the number of bytes or characters required to hold the
 *   formatted currency string, and the buffer pointed to by lpCurrencyStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpCurrencyStr, or, if the
 *   cchCurrency parameter is zero, the number of characters required to hold the formatted currency
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
#define GetCurrencyFormat  GetCurrencyFormatW
#else
/**
 * This function formats a number string as a currency string for a specified locale.
 *
 * @param Locale [in] Specifies the locale for which the currency string is to be formatted. If
 *   lpFormat is NULL, the function formats the string according to the currency format for this
 *   locale. If lpFormat is not NULL, the function uses the locale only for formatting information not
 *   specified in the CURRENCYFMT structure (for example, the locale's string value for the negative
 *   sign). This parameter can be a locale identifier created by the MAKELCID macro, or one of the
 *   following predefined values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale.
 *   LOCALE_USER_DEFAULT Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] A bit flag that controls the operation of the function. If lpFormat is
 *   non-NULL, this parameter must be zero. If lpFormat is NULL, you can specify the
 *   LOCALE_NOUSEROVERRIDE flag to format the string using the system default currency format for the
 *   specified locale; or you can specify zero to format the string using any user overrides to the
 *   locale's default currency format.
 * @param lpValue [in] Pointer to a null-terminated string that contains the number string to
 *   format. This string can contain only the following characters: Characters '0' through '9' One
 *   decimal point (dot) if the number is a floating-point value A minus sign in the first character
 *   position if the number is a negative value All other characters are invalid. The function returns
 *   an error if the string pointed to by lpValue deviates from these rules.
 * @param lpFormat [in] Pointer to a CURRENCYFMT structure that contains currency formatting
 *   information. All members in the structure pointed to by lpFormat must contain appropriate values.
 *   If lpFormat is NULL, the function uses the currency format of the specified locale.
 * @param lpCurrencyStr [out] Pointer to a buffer to receive the formatted currency string.
 * @param cchCurrency [in] Specifies the size, in characters, of the lpCurrencyStr buffer. If
 *   cchCurrency is zero, the function returns the number of bytes or characters required to hold the
 *   formatted currency string, and the buffer pointed to by lpCurrencyStr is not used.
 *
 * @return The number of characters written to the buffer pointed to by lpCurrencyStr, or, if the
 *   cchCurrency parameter is zero, the number of characters required to hold the formatted currency
 *   string indicates success. The count includes the terminating null. Zero indicates failure. To get
 *   extended error information, call GetLastError. Possible values for GetLastError include the
 *   following: ERROR_INSUFFICIENT_BUFFER ERROR_INVALID FLAGS ERROR_INVALID_PARAMETER
 */
#define GetCurrencyFormat  GetCurrencyFormatA
#endif

/**
 * This function enumerates the calendar information by calling an application-defined callback
 * function. It passes the callback function a pointer to a string buffer that contains the
 * requested calendar information. This continues until either the last applicable calendar is found
 * or the callback function returns FALSE.
 *
 * @param lpCalInfoEnumProc [in] Pointer to an application-defined callback function. For more
 *   information, see the EnumCalendarInfoProc callback function.
 * @param Locale [in] Specifies the locale to retrieve calendar information for. This parameter can
 *   be a locale identifier created by the MAKELCID macro, or one of the following predefined values:
 *   Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user
 *   locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param Calendar [in] Specifies the calendar for which information is requested. The following
 *   values are defined: Value Description ENUM_ALL_CALENDARS Enumerate all applicable calendars for
 *   the locale specified by Locale. CAL_GREGORIAN Gregorian (localized) CAL_GREGORIAN_US Gregorian
 *   (English strings always) CAL_JAPAN Japanese Emperor Era CAL_TAIWAN Taiwan Region Era CAL_KOREA
 *   Korean Tangun Era CAL_HIJRI Hijri (Arabic Lunar) CAL_THAI Thai CAL_HEBREW Hebrew
 *   CAL_GREGORIAN_ME_FRENCH Gregorian Middle East French CAL_GREGORIAN_ARABIC Gregorian Arabic
 *   CAL_GREGORIAN_XLIT_ENGLISH Gregorian transliterated English CAL_GREGORIAN_XLIT_FRENCH Gregorian
 *   transliterated French
 * @param CalType [in] Indicates the type of calendar information to be returned. See the listing of
 *   constant values in the "Remarks" section.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_BADDB
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The CALTYPE constants define particular pieces of calendar information. The following table shows
 * CALTYPE constants that are mutually exclusive-that is, they cannot be used in combination with
 * each other in a function call.
 *
 * Type Description CAL_ICALINTVALUE An integer value indicating the calendar type of the alternate
 * calendar. CAL_IYEAROFFSETRANGE One or more null-terminated strings that specify the year offsets
 * for each of the era ranges. The last string has an extra terminating null character.
 * CAL_SABBREVDAYNAME1 Abbreviated native name of the first day of the week. CAL_SABBREVDAYNAME2
 * Abbreviated native name of the second day of the week. CAL_SABBREVDAYNAME3 Abbreviated native
 * name of the third day of the week. CAL_SABBREVDAYNAME4 Abbreviated native name of the fourth day
 * of the week. CAL_SABBREVDAYNAME5 Abbreviated native name of the fifth day of the week.
 * CAL_SABBREVDAYNAME6 Abbreviated native name of the sixth day of the week. CAL_SABBREVDAYNAME7
 * Abbreviated native name of the seventh day of the week. CAL_SABBREVMONTHNAME1 Abbreviated native
 * name of the first month of the year. CAL_SABBREVMONTHNAME2 Abbreviated native name of the second
 * month of the year. CAL_SABBREVMONTHNAME3 Abbreviated native name of the third month of the year.
 * CAL_SABBREVMONTHNAME4 Abbreviated native name of the fourth month of the year.
 * CAL_SABBREVMONTHNAME5 Abbreviated native name of the fifth month of the year.
 * CAL_SABBREVMONTHNAME6 Abbreviated native name of the sixth month of the year.
 * CAL_SABBREVMONTHNAME7 Abbreviated native name of the seventh month of the year.
 * CAL_SABBREVMONTHNAME8 Abbreviated native name of the eighth month of the year.
 * CAL_SABBREVMONTHNAME9 Abbreviated native name of the ninth month of the year.
 * CAL_SABBREVMONTHNAME10 Abbreviated native name of the tenth month of the year.
 * CAL_SABBREVMONTHNAME11 Abbreviated native name of the eleventh month of the year.
 * CAL_SABBREVMONTHNAME12 Abbreviated native name of the twelfth month of the year.
 * CAL_SABBREVMONTHNAME13 Abbreviated native name of the thirteenth month of the year, if it exists.
 * CAL_SCALNAME Native name of the alternate calendar. CAL_SDAYNAME1 Native name of the first day of
 * the week. CAL_SDAYNAME2 Native name of the second day of the week. CAL_SDAYNAME3 Native name of
 * the third day of the week. CAL_SDAYNAME4 Native name of the fourth day of the week. CAL_SDAYNAME5
 * Native name of the fifth day of the week. CAL_SDAYNAME6 Native name of the sixth day of the week.
 * CAL_SDAYNAME7 Native name of the seventh day of the week. CAL_SERASTRING One or more
 * null-terminated strings that specify each of the Unicode codepoints specifying the era associated
 * with the given CAL_IYEAROFFSETRANGE. The last string has an extra terminating null character. See
 * example below. CAL_SLONGDATE Long date formats for this calendar type. CAL_SMONTHNAME1 Native
 * name of the first month of the year. CAL_SMONTHNAME2 Native name of the second month of the year.
 * CAL_SMONTHNAME3 Native name of the fifth month of the year. CAL_SMONTHNAME4 Native name of the
 * fourth month of the year. CAL_SMONTHNAME5 Native name of the fifth month of the year.
 * CAL_SMONTHNAME6 Native name of the sixth month of the year. CAL_SMONTHNAME7 Native name of the
 * seventh month of the year. CAL_SMONTHNAME8 Native name of the eighth month of the year.
 * CAL_SMONTHNAME9 Native name of the ninth month of the year. CAL_SMONTHNAME10 Native name of the
 * tenth month of the year. CAL_SMONTHNAME11 Native name of the eleventh month of the year.
 * CAL_SMONTHNAME12 Native name of the twelfth month of the year. CAL_SMONTHNAME13 Native name of
 * the thirteenth month of the year, if it exists. CAL_SSHORTDATE Short date formats for this
 * calendar type.
 *
 * If the native name for the day of the week or for a month is an empty string, that name is
 * identical to the name given in the corresponding locale information and therefore is not
 * duplicated here.
 *
 * The CAL_IYEAROFFSETRANGE and CAL_SERASTRING values vary in format depending on the type of
 * optional calendar. The following example shows the values for these types (for each supported
 * alternate calendar type) along with the formula for how to use the CAL_IYEAROFFSETRANGE value to
 * compute the correct year given the Gregorian current year value Y:
 *
 *     CAL_ICALINTVALUE = "1"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "2"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "3"
 *     CAL_IYEAROFFSETRANGE = "1989\01926\01912\01868\0"
 *     CAL_SERASTRING = "Ux337B\0Ux337C\0Ux337D\0Ux337E\0"
 *     if (Y>=1989) { Y = (Y-1989)+1; }
 *     if (Y>=1926 && Y<1989) { Y = (Y-1926)+1; }
 *     if (Y>=1912 && Y<1926) { Y = (Y-1912)+1; }
 *     if (Y>=1868 && Y<1912) { Y = (Y-1868)+1; }
 *     if (Y<1868) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "4"
 *     CAL_IYEAROFFSETRANGE = "1912\0"
 *     CAL_SERASTRING = "Ux4E2D\0Ux83EF\0Ux6C11\0Ux570B\0"
 *     if (Y>=1912) { Y = (Y-1912)+1; }
 *     if (Y<1912) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "5"
 *     CAL_IYEAROFFSETRANGE = "2333\0"
 *     CAL_SERASTRING = ""
 *     Y = Y+2333;
 */
BOOL WINAPI EnumCalendarInfoW(CALINFO_ENUMPROCW lpCalInfoEnumProc,
    LCID Locale, CALID Calendar, CALTYPE CalType);

#ifdef UNICODE
/**
 * This function enumerates the calendar information by calling an application-defined callback
 * function. It passes the callback function a pointer to a string buffer that contains the
 * requested calendar information. This continues until either the last applicable calendar is found
 * or the callback function returns FALSE.
 *
 * @param lpCalInfoEnumProc [in] Pointer to an application-defined callback function. For more
 *   information, see the EnumCalendarInfoProc callback function.
 * @param Locale [in] Specifies the locale to retrieve calendar information for. This parameter can
 *   be a locale identifier created by the MAKELCID macro, or one of the following predefined values:
 *   Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user
 *   locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param Calendar [in] Specifies the calendar for which information is requested. The following
 *   values are defined: Value Description ENUM_ALL_CALENDARS Enumerate all applicable calendars for
 *   the locale specified by Locale. CAL_GREGORIAN Gregorian (localized) CAL_GREGORIAN_US Gregorian
 *   (English strings always) CAL_JAPAN Japanese Emperor Era CAL_TAIWAN Taiwan Region Era CAL_KOREA
 *   Korean Tangun Era CAL_HIJRI Hijri (Arabic Lunar) CAL_THAI Thai CAL_HEBREW Hebrew
 *   CAL_GREGORIAN_ME_FRENCH Gregorian Middle East French CAL_GREGORIAN_ARABIC Gregorian Arabic
 *   CAL_GREGORIAN_XLIT_ENGLISH Gregorian transliterated English CAL_GREGORIAN_XLIT_FRENCH Gregorian
 *   transliterated French
 * @param CalType [in] Indicates the type of calendar information to be returned. See the listing of
 *   constant values in the "Remarks" section.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_BADDB
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The CALTYPE constants define particular pieces of calendar information. The following table shows
 * CALTYPE constants that are mutually exclusive-that is, they cannot be used in combination with
 * each other in a function call.
 *
 * Type Description CAL_ICALINTVALUE An integer value indicating the calendar type of the alternate
 * calendar. CAL_IYEAROFFSETRANGE One or more null-terminated strings that specify the year offsets
 * for each of the era ranges. The last string has an extra terminating null character.
 * CAL_SABBREVDAYNAME1 Abbreviated native name of the first day of the week. CAL_SABBREVDAYNAME2
 * Abbreviated native name of the second day of the week. CAL_SABBREVDAYNAME3 Abbreviated native
 * name of the third day of the week. CAL_SABBREVDAYNAME4 Abbreviated native name of the fourth day
 * of the week. CAL_SABBREVDAYNAME5 Abbreviated native name of the fifth day of the week.
 * CAL_SABBREVDAYNAME6 Abbreviated native name of the sixth day of the week. CAL_SABBREVDAYNAME7
 * Abbreviated native name of the seventh day of the week. CAL_SABBREVMONTHNAME1 Abbreviated native
 * name of the first month of the year. CAL_SABBREVMONTHNAME2 Abbreviated native name of the second
 * month of the year. CAL_SABBREVMONTHNAME3 Abbreviated native name of the third month of the year.
 * CAL_SABBREVMONTHNAME4 Abbreviated native name of the fourth month of the year.
 * CAL_SABBREVMONTHNAME5 Abbreviated native name of the fifth month of the year.
 * CAL_SABBREVMONTHNAME6 Abbreviated native name of the sixth month of the year.
 * CAL_SABBREVMONTHNAME7 Abbreviated native name of the seventh month of the year.
 * CAL_SABBREVMONTHNAME8 Abbreviated native name of the eighth month of the year.
 * CAL_SABBREVMONTHNAME9 Abbreviated native name of the ninth month of the year.
 * CAL_SABBREVMONTHNAME10 Abbreviated native name of the tenth month of the year.
 * CAL_SABBREVMONTHNAME11 Abbreviated native name of the eleventh month of the year.
 * CAL_SABBREVMONTHNAME12 Abbreviated native name of the twelfth month of the year.
 * CAL_SABBREVMONTHNAME13 Abbreviated native name of the thirteenth month of the year, if it exists.
 * CAL_SCALNAME Native name of the alternate calendar. CAL_SDAYNAME1 Native name of the first day of
 * the week. CAL_SDAYNAME2 Native name of the second day of the week. CAL_SDAYNAME3 Native name of
 * the third day of the week. CAL_SDAYNAME4 Native name of the fourth day of the week. CAL_SDAYNAME5
 * Native name of the fifth day of the week. CAL_SDAYNAME6 Native name of the sixth day of the week.
 * CAL_SDAYNAME7 Native name of the seventh day of the week. CAL_SERASTRING One or more
 * null-terminated strings that specify each of the Unicode codepoints specifying the era associated
 * with the given CAL_IYEAROFFSETRANGE. The last string has an extra terminating null character. See
 * example below. CAL_SLONGDATE Long date formats for this calendar type. CAL_SMONTHNAME1 Native
 * name of the first month of the year. CAL_SMONTHNAME2 Native name of the second month of the year.
 * CAL_SMONTHNAME3 Native name of the fifth month of the year. CAL_SMONTHNAME4 Native name of the
 * fourth month of the year. CAL_SMONTHNAME5 Native name of the fifth month of the year.
 * CAL_SMONTHNAME6 Native name of the sixth month of the year. CAL_SMONTHNAME7 Native name of the
 * seventh month of the year. CAL_SMONTHNAME8 Native name of the eighth month of the year.
 * CAL_SMONTHNAME9 Native name of the ninth month of the year. CAL_SMONTHNAME10 Native name of the
 * tenth month of the year. CAL_SMONTHNAME11 Native name of the eleventh month of the year.
 * CAL_SMONTHNAME12 Native name of the twelfth month of the year. CAL_SMONTHNAME13 Native name of
 * the thirteenth month of the year, if it exists. CAL_SSHORTDATE Short date formats for this
 * calendar type.
 *
 * If the native name for the day of the week or for a month is an empty string, that name is
 * identical to the name given in the corresponding locale information and therefore is not
 * duplicated here.
 *
 * The CAL_IYEAROFFSETRANGE and CAL_SERASTRING values vary in format depending on the type of
 * optional calendar. The following example shows the values for these types (for each supported
 * alternate calendar type) along with the formula for how to use the CAL_IYEAROFFSETRANGE value to
 * compute the correct year given the Gregorian current year value Y:
 *
 *     CAL_ICALINTVALUE = "1"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "2"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "3"
 *     CAL_IYEAROFFSETRANGE = "1989\01926\01912\01868\0"
 *     CAL_SERASTRING = "Ux337B\0Ux337C\0Ux337D\0Ux337E\0"
 *     if (Y>=1989) { Y = (Y-1989)+1; }
 *     if (Y>=1926 && Y<1989) { Y = (Y-1926)+1; }
 *     if (Y>=1912 && Y<1926) { Y = (Y-1912)+1; }
 *     if (Y>=1868 && Y<1912) { Y = (Y-1868)+1; }
 *     if (Y<1868) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "4"
 *     CAL_IYEAROFFSETRANGE = "1912\0"
 *     CAL_SERASTRING = "Ux4E2D\0Ux83EF\0Ux6C11\0Ux570B\0"
 *     if (Y>=1912) { Y = (Y-1912)+1; }
 *     if (Y<1912) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "5"
 *     CAL_IYEAROFFSETRANGE = "2333\0"
 *     CAL_SERASTRING = ""
 *     Y = Y+2333;
 */
#define EnumCalendarInfo  EnumCalendarInfoW
#else
/**
 * This function enumerates the calendar information by calling an application-defined callback
 * function. It passes the callback function a pointer to a string buffer that contains the
 * requested calendar information. This continues until either the last applicable calendar is found
 * or the callback function returns FALSE.
 *
 * @param lpCalInfoEnumProc [in] Pointer to an application-defined callback function. For more
 *   information, see the EnumCalendarInfoProc callback function.
 * @param Locale [in] Specifies the locale to retrieve calendar information for. This parameter can
 *   be a locale identifier created by the MAKELCID macro, or one of the following predefined values:
 *   Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT Default user
 *   locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param Calendar [in] Specifies the calendar for which information is requested. The following
 *   values are defined: Value Description ENUM_ALL_CALENDARS Enumerate all applicable calendars for
 *   the locale specified by Locale. CAL_GREGORIAN Gregorian (localized) CAL_GREGORIAN_US Gregorian
 *   (English strings always) CAL_JAPAN Japanese Emperor Era CAL_TAIWAN Taiwan Region Era CAL_KOREA
 *   Korean Tangun Era CAL_HIJRI Hijri (Arabic Lunar) CAL_THAI Thai CAL_HEBREW Hebrew
 *   CAL_GREGORIAN_ME_FRENCH Gregorian Middle East French CAL_GREGORIAN_ARABIC Gregorian Arabic
 *   CAL_GREGORIAN_XLIT_ENGLISH Gregorian transliterated English CAL_GREGORIAN_XLIT_FRENCH Gregorian
 *   transliterated French
 * @param CalType [in] Indicates the type of calendar information to be returned. See the listing of
 *   constant values in the "Remarks" section.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_BADDB
 *   ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The CALTYPE constants define particular pieces of calendar information. The following table shows
 * CALTYPE constants that are mutually exclusive-that is, they cannot be used in combination with
 * each other in a function call.
 *
 * Type Description CAL_ICALINTVALUE An integer value indicating the calendar type of the alternate
 * calendar. CAL_IYEAROFFSETRANGE One or more null-terminated strings that specify the year offsets
 * for each of the era ranges. The last string has an extra terminating null character.
 * CAL_SABBREVDAYNAME1 Abbreviated native name of the first day of the week. CAL_SABBREVDAYNAME2
 * Abbreviated native name of the second day of the week. CAL_SABBREVDAYNAME3 Abbreviated native
 * name of the third day of the week. CAL_SABBREVDAYNAME4 Abbreviated native name of the fourth day
 * of the week. CAL_SABBREVDAYNAME5 Abbreviated native name of the fifth day of the week.
 * CAL_SABBREVDAYNAME6 Abbreviated native name of the sixth day of the week. CAL_SABBREVDAYNAME7
 * Abbreviated native name of the seventh day of the week. CAL_SABBREVMONTHNAME1 Abbreviated native
 * name of the first month of the year. CAL_SABBREVMONTHNAME2 Abbreviated native name of the second
 * month of the year. CAL_SABBREVMONTHNAME3 Abbreviated native name of the third month of the year.
 * CAL_SABBREVMONTHNAME4 Abbreviated native name of the fourth month of the year.
 * CAL_SABBREVMONTHNAME5 Abbreviated native name of the fifth month of the year.
 * CAL_SABBREVMONTHNAME6 Abbreviated native name of the sixth month of the year.
 * CAL_SABBREVMONTHNAME7 Abbreviated native name of the seventh month of the year.
 * CAL_SABBREVMONTHNAME8 Abbreviated native name of the eighth month of the year.
 * CAL_SABBREVMONTHNAME9 Abbreviated native name of the ninth month of the year.
 * CAL_SABBREVMONTHNAME10 Abbreviated native name of the tenth month of the year.
 * CAL_SABBREVMONTHNAME11 Abbreviated native name of the eleventh month of the year.
 * CAL_SABBREVMONTHNAME12 Abbreviated native name of the twelfth month of the year.
 * CAL_SABBREVMONTHNAME13 Abbreviated native name of the thirteenth month of the year, if it exists.
 * CAL_SCALNAME Native name of the alternate calendar. CAL_SDAYNAME1 Native name of the first day of
 * the week. CAL_SDAYNAME2 Native name of the second day of the week. CAL_SDAYNAME3 Native name of
 * the third day of the week. CAL_SDAYNAME4 Native name of the fourth day of the week. CAL_SDAYNAME5
 * Native name of the fifth day of the week. CAL_SDAYNAME6 Native name of the sixth day of the week.
 * CAL_SDAYNAME7 Native name of the seventh day of the week. CAL_SERASTRING One or more
 * null-terminated strings that specify each of the Unicode codepoints specifying the era associated
 * with the given CAL_IYEAROFFSETRANGE. The last string has an extra terminating null character. See
 * example below. CAL_SLONGDATE Long date formats for this calendar type. CAL_SMONTHNAME1 Native
 * name of the first month of the year. CAL_SMONTHNAME2 Native name of the second month of the year.
 * CAL_SMONTHNAME3 Native name of the fifth month of the year. CAL_SMONTHNAME4 Native name of the
 * fourth month of the year. CAL_SMONTHNAME5 Native name of the fifth month of the year.
 * CAL_SMONTHNAME6 Native name of the sixth month of the year. CAL_SMONTHNAME7 Native name of the
 * seventh month of the year. CAL_SMONTHNAME8 Native name of the eighth month of the year.
 * CAL_SMONTHNAME9 Native name of the ninth month of the year. CAL_SMONTHNAME10 Native name of the
 * tenth month of the year. CAL_SMONTHNAME11 Native name of the eleventh month of the year.
 * CAL_SMONTHNAME12 Native name of the twelfth month of the year. CAL_SMONTHNAME13 Native name of
 * the thirteenth month of the year, if it exists. CAL_SSHORTDATE Short date formats for this
 * calendar type.
 *
 * If the native name for the day of the week or for a month is an empty string, that name is
 * identical to the name given in the corresponding locale information and therefore is not
 * duplicated here.
 *
 * The CAL_IYEAROFFSETRANGE and CAL_SERASTRING values vary in format depending on the type of
 * optional calendar. The following example shows the values for these types (for each supported
 * alternate calendar type) along with the formula for how to use the CAL_IYEAROFFSETRANGE value to
 * compute the correct year given the Gregorian current year value Y:
 *
 *     CAL_ICALINTVALUE = "1"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "2"
 *     CAL_IYEAROFFSETRANGE = ""
 *     CAL_SERASTRING = ""
 *
 *     CAL_ICALINTVALUE = "3"
 *     CAL_IYEAROFFSETRANGE = "1989\01926\01912\01868\0"
 *     CAL_SERASTRING = "Ux337B\0Ux337C\0Ux337D\0Ux337E\0"
 *     if (Y>=1989) { Y = (Y-1989)+1; }
 *     if (Y>=1926 && Y<1989) { Y = (Y-1926)+1; }
 *     if (Y>=1912 && Y<1926) { Y = (Y-1912)+1; }
 *     if (Y>=1868 && Y<1912) { Y = (Y-1868)+1; }
 *     if (Y<1868) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "4"
 *     CAL_IYEAROFFSETRANGE = "1912\0"
 *     CAL_SERASTRING = "Ux4E2D\0Ux83EF\0Ux6C11\0Ux570B\0"
 *     if (Y>=1912) { Y = (Y-1912)+1; }
 *     if (Y<1912) { Y = Y; }
 *
 *     CAL_ICALINTVALUE = "5"
 *     CAL_IYEAROFFSETRANGE = "2333\0"
 *     CAL_SERASTRING = ""
 *     Y = Y+2333;
 */
#define EnumCalendarInfo  EnumCalendarInfoA
#endif

/**
 * This function enumerates the time formats that are available for a specified locale.
 *
 * @param lpTimeFmtEnumProc [in] Pointer to an application-defined callback function. See the
 *   EnumTimeFormatsProc callback function for further details.
 * @param Locale [in] Specifies the locale to retrieve time format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Currently unused; set to zero.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 */
BOOL WINAPI EnumTimeFormatsW(TIMEFMT_ENUMPROCW lpTimeFmtEnumProc,
    LCID Locale, DWORD dwFlags);

#ifdef UNICODE
/**
 * This function enumerates the time formats that are available for a specified locale.
 *
 * @param lpTimeFmtEnumProc [in] Pointer to an application-defined callback function. See the
 *   EnumTimeFormatsProc callback function for further details.
 * @param Locale [in] Specifies the locale to retrieve time format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Currently unused; set to zero.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 */
#define EnumTimeFormats  EnumTimeFormatsW
#else
/**
 * This function enumerates the time formats that are available for a specified locale.
 *
 * @param lpTimeFmtEnumProc [in] Pointer to an application-defined callback function. See the
 *   EnumTimeFormatsProc callback function for further details.
 * @param Locale [in] Specifies the locale to retrieve time format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Currently unused; set to zero.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 */
#define EnumTimeFormats  EnumTimeFormatsA
#endif

/**
 * This function enumerates the long or short date formats that are available for a specified
 * locale, including date formats for any alternate calendars.
 *
 * @param lpDateFmtEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumDateFormats function enumerates date formats by making repeated calls to this callback
 *   function. For more information, see the EnumDateFormatsProc callback function.
 * @param Locale [in] Specifies the locale to retrieve date format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Specifies the date formats that are of interest. Use one of the following
 *   values: Value Description DATE_SHORTDATE Return short date formats. DATE_LONGDATE Return long
 *   date formats.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flags are mutually exclusive. Use one or the other, but not
 * both.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 */
BOOL WINAPI EnumDateFormatsW(DATEFMT_ENUMPROCW lpDateFmtEnumProc,
    LCID Locale, DWORD dwFlags);

#ifdef UNICODE
/**
 * This function enumerates the long or short date formats that are available for a specified
 * locale, including date formats for any alternate calendars.
 *
 * @param lpDateFmtEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumDateFormats function enumerates date formats by making repeated calls to this callback
 *   function. For more information, see the EnumDateFormatsProc callback function.
 * @param Locale [in] Specifies the locale to retrieve date format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Specifies the date formats that are of interest. Use one of the following
 *   values: Value Description DATE_SHORTDATE Return short date formats. DATE_LONGDATE Return long
 *   date formats.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flags are mutually exclusive. Use one or the other, but not
 * both.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 */
#define EnumDateFormats  EnumDateFormatsW
#else
/**
 * This function enumerates the long or short date formats that are available for a specified
 * locale, including date formats for any alternate calendars.
 *
 * @param lpDateFmtEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumDateFormats function enumerates date formats by making repeated calls to this callback
 *   function. For more information, see the EnumDateFormatsProc callback function.
 * @param Locale [in] Specifies the locale to retrieve date format information for. This parameter
 *   can be a locale identifier created by the MAKELCID macro, or one of the following predefined
 *   values: Value Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT
 *   Default user locale. LOCALE_NEUTRAL Default language-neutral locale.
 * @param dwFlags [in] Specifies the date formats that are of interest. Use one of the following
 *   values: Value Description DATE_SHORTDATE Return short date formats. DATE_LONGDATE Return long
 *   date formats.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The DATE_SHORTDATE and DATE_LONGDATE flags are mutually exclusive. Use one or the other, but not
 * both.
 *
 * For Windows CE versions 2.10 and later, default DATE_SHORTDATE formats for non-U.S. English
 * locales that include the four-digit year are added. The following table shows the formats.
 *
 * Locale Date Format United Kingdom dd/MM/yyyy Canada dd/MM/yyyy New Zealand dd/MM/yyyy Ireland
 * dd/MM/yyyy South Africa dd/MM/yyyy Caribbean MM/dd/yyyy Belize dd/MM/yyyy Trinidad dd/MM/yyyy
 */
#define EnumDateFormats  EnumDateFormatsA
#endif

/**
 * This function applies a validity test to a locale identifier. The dwFlags parameter determines
 * the nature of the validity test. Currently, the function tests whether a locale identifier is
 * installed or supported on the calling system.
 *
 * @param Locale [in] Specifies the locale identifier to be validated. You can use the MAKELCID
 *   macro to create a locale identifier.
 * @param dwFlags [in] Specifies the validity test to apply to the locale identifier. This parameter
 *   can be one of the following values: Value Description LCID_INSTALLED Test whether the locale
 *   identifier is both supported and installed. LCID_SUPPORTED Test whether the locale identifier is
 *   supported.
 *
 * @return Nonzero indicates that the locale identifier passes the specified validity test. Zero
 *   indicates that the locale identifier does not pass the specified validity test.
 *
 * If the LCID_INSTALLED flag is specified and this function returns a nonzero value, the locale
 * identifier is both supported and installed on the system.
 *
 * If the LCID_SUPPORTED flag is specified and this function returns zero, the locale identifier is
 * supported in the release, but not necessarily installed on the system. Windows CE does not
 * support the downloading of code pages to a device.
 */
BOOL WINAPI IsValidLocale(LCID Locale, DWORD dwFlags);

/**
 * This function converts a special default locale value to an actual locale identifier.
 *
 * @param Locale [in] Default locale value that the function converts to a locale identifier (LCID).
 *   The following list shows the default locale values: Value Description LOCALE_SYSTEM_DEFAULT The
 *   system's default locale. LOCALE_USER_DEFAULT The current user's default locale. LOCALE_NEUTRAL
 *   The language-neutral default locale. Any sublanguage-neutral locale A locale identifier
 *   constructed by calling MAKELCID with a primary language identifier, such as LANG_ENGLISH, and the
 *   SUBLANG_NEUTRAL secondary language identifier.
 *
 * @return The appropriate LCID indicates success. The Locale parameter indicates failure. The
 *   function fails when Locale is not one of the default locale values listed above.
 *
 * A call to ConvertDefaultLocale(LOCALE_SYSTEM_DEFAULT) is equivalent to a call to
 * GetSystemDefaultLCID. A call to ConvertDefaultLocale(LOCALE_USER_DEFAULT) is equivalent to a call
 * to GetUserDefaultLCID.
 *
 * For more information, see Locale Identifiers.
 */
LCID WINAPI ConvertDefaultLocale(LCID Locale);

/**
 * This function retrieves the system default language identifier.
 *
 * @return The system default language identifier indicates success.
 *
 * For more information about language identifiers, see Locale Identifiers.
 */
LANGID WINAPI GetSystemDefaultLangID(void);

/**
 * This function retrieves the user-default language identifier.
 *
 * @return The user -default language identifier indicates success.
 *
 * Windows CE does not support a separate system LANGID and therefore GetSystemDefaultLangID returns
 * the same value.
 *
 * For more information about language identifiers, see Locale Identifiers.
 */
LANGID WINAPI GetUserDefaultLangID(void);

/**
 * This function retrieves the system default locale identifier.
 *
 * @return The system default locale identifier indicates success.
 *
 * For more information about locale identifiers, see Locale Identifiers.
 */
LCID WINAPI GetSystemDefaultLCID(void);

/**
 * This function retrieves the user-default locale identifier.
 *
 * @return The user-default locale identifier indicates success.
 *
 * Windows CE does not support a separate system LCID and therefore GetSystemDefaultLCID returns the
 * same value.
 *
 * For more information about locale identifiers, see Locale Identifiers.
 */
LCID WINAPI GetUserDefaultLCID(void);

/*
 *  Locale Independent APIs.
 */

/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, the function sets one or more bits in the corresponding
 * 16-bit element of the output array. Each bit identifies a given character type, such as whether
 * the character is a letter, a digit, or neither.
 *
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated. This must be a Unicode string.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for the number of characters specified in the cchSrc
 *   parameter. When the function returns, this array contains one word corresponding to each Unicode
 *   character in the source string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetStringType function is designed for Unicode strings only. In the Microsoft Platform SDK,
 * this function is named GetStringTypeW to distinguish it from the similar ANSI-string function,
 * GetStringTypeA. Because Windows CE only supports Unicode, it requires only the single
 * GetStringType function.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blanks
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
BOOL WINAPI GetStringTypeW(DWORD dwInfoType, LPCWSTR lpSrcStr, int cchSrc, LPWORD lpCharType);

#ifdef UNICODE
/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, the function sets one or more bits in the corresponding
 * 16-bit element of the output array. Each bit identifies a given character type, such as whether
 * the character is a letter, a digit, or neither.
 *
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated. This must be a Unicode string.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for the number of characters specified in the cchSrc
 *   parameter. When the function returns, this array contains one word corresponding to each Unicode
 *   character in the source string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetStringType function is designed for Unicode strings only. In the Microsoft Platform SDK,
 * this function is named GetStringTypeW to distinguish it from the similar ANSI-string function,
 * GetStringTypeA. Because Windows CE only supports Unicode, it requires only the single
 * GetStringType function.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blanks
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
#define GetStringType GetStringTypeW
#else
/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, the function sets one or more bits in the corresponding
 * 16-bit element of the output array. Each bit identifies a given character type, such as whether
 * the character is a letter, a digit, or neither.
 *
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated. This must be a Unicode string.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for the number of characters specified in the cchSrc
 *   parameter. When the function returns, this array contains one word corresponding to each Unicode
 *   character in the source string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * The GetStringType function is designed for Unicode strings only. In the Microsoft Platform SDK,
 * this function is named GetStringTypeW to distinguish it from the similar ANSI-string function,
 * GetStringTypeA. Because Windows CE only supports Unicode, it requires only the single
 * GetStringType function.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blanks
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
#define GetStringType GetStringTypeA
#endif

/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, GetStringTypeEx sets one or more bits in the
 * corresponding 16-bit element of the output array. Each bit identifies a given character type,
 * such as whether the character is a letter, a digit, or neither.
 *
 * @param Locale [in] Specifies the locale identifier. This value uniquely defines the ANSI code
 *   page to use to translate the string pointed to by lpSrcStr from ANSI to Unicode. The function
 *   then analyzes each Unicode character for character type information This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT. Default user
 *   locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for each character in the source string. When the
 *   function returns, this array contains one word corresponding to each character in the source
 *   string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale
 * parameter.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blank
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
BOOL WINAPI GetStringTypeExW(LCID Locale, DWORD dwInfoType, LPCWSTR lpSrcStr,
    int cchSrc, LPWORD lpCharType);

#ifdef UNICODE
/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, GetStringTypeEx sets one or more bits in the
 * corresponding 16-bit element of the output array. Each bit identifies a given character type,
 * such as whether the character is a letter, a digit, or neither.
 *
 * @param Locale [in] Specifies the locale identifier. This value uniquely defines the ANSI code
 *   page to use to translate the string pointed to by lpSrcStr from ANSI to Unicode. The function
 *   then analyzes each Unicode character for character type information This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT. Default user
 *   locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for each character in the source string. When the
 *   function returns, this array contains one word corresponding to each character in the source
 *   string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale
 * parameter.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blank
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
#define GetStringTypeEx  GetStringTypeExW
#else
/**
 * This function returns character-type information for the characters in the specified source
 * string. For each character in the string, GetStringTypeEx sets one or more bits in the
 * corresponding 16-bit element of the output array. Each bit identifies a given character type,
 * such as whether the character is a letter, a digit, or neither.
 *
 * @param Locale [in] Specifies the locale identifier. This value uniquely defines the ANSI code
 *   page to use to translate the string pointed to by lpSrcStr from ANSI to Unicode. The function
 *   then analyzes each Unicode character for character type information This parameter can be a
 *   locale identifier created by the MAKELCID macro, or one of the following predefined values: Value
 *   Description LOCALE_SYSTEM_DEFAULT Default system locale. LOCALE_USER_DEFAULT. Default user
 *   locale. For Windows CE version 1.0, Locale is ignored.
 * @param dwInfoType [in] Specifies the type of character information the user wants to retrieve.
 *   The various types are divided into different levels (see the following Remarks section for a list
 *   of the information included in each type). This parameter can specify one of the following
 *   character type flags: Value Description CT_CTYPE1 Retrieve character type information. CT_CTYPE2
 *   Retrieve bidirectional layout information. CT_CTYPE3 Retrieve text processing information.
 * @param lpSrcStr [in] Pointer to the string for which character types are requested. If cchSrc is
 *   -1, the string is assumed to be null terminated.
 * @param cchSrc [in] Specifies the size, in characters, of the string pointed to by the lpSrcStr
 *   parameter. If this count includes a terminating null character, the function returns character
 *   type information for the terminating null character. If this value is -1, the string is assumed
 *   to be null terminated and the length is calculated automatically.
 * @param lpCharType [out] Pointer to an array of 16-bit values. The length of this array must be
 *   large enough to receive one 16-bit value for each character in the source string. When the
 *   function returns, this array contains one word corresponding to each character in the source
 *   string.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following: ERROR_INVALID_FLAGS
 *   ERROR_INVALID_PARAMETER
 *
 * Windows CE supports only the Unicode version of GetStringTypeEx, which ignores the Locale
 * parameter.
 *
 * The lpSrcStr and lpCharType pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The character-type bits are divided into several levels. The information for one level can be
 * retrieved by a single call to this function. Each level is limited to 16 bits of information so
 * that the other mapping routines, which are limited to 16 bits of representation per character,
 * can also return character-type information.
 *
 * The character types supported by this function include the following.
 *
 * - Ctype 1: These types support ANSI C and POSIX (LC_CTYPE) character-typing functions. A
 * combination of these values is returned in the array pointed to by the lpCharType parameter when
 * the dwInfoType parameter is set to CT_CTYPE1. Name Value Description C1_UPPER 0x0001 Uppercase
 * C1_LOWER 0x0002 Lowercase C1_DIGIT 0x0004 Decimal digits C1_SPACE 0x0008 Space characters
 * C1_PUNCT 0x0010 Punctuation C1_CNTRL 0x0020 Control characters C1_BLANK 0x0040 Blank characters
 * C1_XDIGIT 0x0080 Hexadecimal digits C1_ALPHA 0x0100 Any linguistic character: alphabetic,
 * syllabary, or ideographic The following character types are either constant or computable from
 * basic types and do not need to be supported by this function. Type Description Alphanumeric
 * Alphabetic characters and digits (C1_ALPHA and C1_DIGIT) Printable Graphic characters and blank
 * (all C1_* types except C1_CNTRL)
 *
 * - Ctype 2: These types support proper layout of Unicode text. The direction attributes are
 * assigned so that the bidirectional layout algorithm standardized by Unicode produces accurate
 * results. These types are mutually exclusive. For more information about the use of these
 * attributes, see The Unicode Standard: Worldwide Character Encoding, Volumes 1 and 2, Addison
 * Wesley Publishing Company: 1991, 1992, ISBN 0201567881. Name Value Description Strong
 * C2_LEFTTORIGHT 0x0001 Left to right C2_RIGHTTOLEFT 0x0002 Right to left Weak C2_EUROPENUMBER
 * 0x0003 European number, European digit C2_EUROPESEPARATOR 0x0004 European numeric separator
 * C2_EUROPETERMINATOR 0x0005 European numeric terminator C2_ARABICNUMBER 0x0006 Arabic number
 * C2_COMMONSEPARATOR 0x0007 Common numeric separator Neutral C2_BLOCKSEPARATOR 0x0008 Block
 * separator C2_SEGMENTSEPARATOR 0x0009 Segment separator C2_WHITESPACE 0x000A White space
 * C2_OTHERNEUTRAL 0x000B Other neutrals Not applicable C2_NOTAPPLICABLE 0x0000 No implicit
 * directionality (for example, control codes)
 *
 * - Ctype 3: These types are intended to be placeholders for extensions to the POSIX types required
 * for general text processing or for the standard C library functions. A combination of these
 * values is returned when dwInfoType is set to CT_CTYPE3. Name Value Description C3_NONSPACING
 * 0x0001 Nonspacing mark C3_DIACRITIC 0x0002 Diacritic nonspacing mark C3_VOWELMARK 0x0004 Vowel
 * nonspacing mark C3_SYMBOL 0x0008 Symbol C3_KATAKANA 0x0010 Katakana character C3_HIRAGANA 0x0020
 * Hiragana character C3_HALFWIDTH 0x0040 Half-width character C3_FULLWIDTH 0x0080 Full-width
 * character C3_IDEOGRAPH 0x0100 Ideographic character C3_KASHIDA 0x0200 Arabic Kashida character
 * C3_LEXICAL 0x0400 Punctuation which is counted as part of the word (Kashida, hyphen,
 * feminine/masculine ordinal indicators, equal sign, and so forth) C3_ALPHA 0x8000 All linguistic
 * characters (alphabetic, syllabary, and ideographic) Not applicable C3_NOTAPPLICABLE 0x0000 Not
 * applicable
 */
#define GetStringTypeEx  GetStringTypeExA
#endif

/**
 * This function maps one string to another, performing a specified transformation option.
 *
 * @param dwMapFlags [in] Specifies the type of transformation to be used during mapping. This value
 *   can be a combination of the following bit-flag constants: Value Description MAP_FOLDCZONE Fold
 *   compatibility zone characters into standard Unicode equivalents. For information about
 *   compatibility zone characters, see the following Remarks section. MAP_FOLDDIGITS Map all digits
 *   to Unicode characters 0 through 9. MAP_PRECOMPOSED Map accented characters to precomposed
 *   characters, in which the accent and base character are combined into a single character value.
 *   This value cannot be combined with MAP_COMPOSITE. MAP_COMPOSITE Map accented characters to
 *   composite characters, in which the accent and base character are represented by two character
 *   values. This value cannot be combined with MAP_PRECOMPOSED. MAP_EXPAND_LIGATURES Not supported.
 * @param lpSrcStr [in] Pointer to the string to be mapped.
 * @param cchSrc [in] Specifies the size, in characters, of the lpSrcStr buffer. If cchSrc is -1,
 *   lpSrcStr is assumed to be null-terminated, and the length is calculated automatically.
 * @param lpDestStr [out] Pointer to the buffer to store the mapped string.
 * @param cchDest [in] Specifies the size, in characters, of the lpDestStr buffer. If cchDest is
 *   zero, the function returns the number of bytes or characters required to hold the mapped string,
 *   and the buffer pointed to by lpDestStr is not used.
 *
 * @return The number of bytes (ANSI version) or characters (Unicode version) written to the
 *   destination buffer, or, if the cchDest parameter is zero, the number of bytes or characters
 *   required to hold the mapped string indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null-terminated if the source string is null-terminated.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The compatibility zone in Unicode consists of characters in the range 0xF900 through 0xFFEF that
 * are assigned to characters from other character-encoding standards but are actually variants of
 * characters that are already in Unicode. The compatibility zone is used to support round-trip
 * mapping to these standards. Applications can use the MAP_FOLDCZONE flag to avoid supporting the
 * duplication of characters in the compatibility zone.
 */
int WINAPI FoldStringW(DWORD dwMapFlags, LPCWSTR lpSrcStr,  int cchSrc, LPWSTR lpDestStr, int cchDest);

#ifdef UNICODE
/**
 * This function maps one string to another, performing a specified transformation option.
 *
 * @param dwMapFlags [in] Specifies the type of transformation to be used during mapping. This value
 *   can be a combination of the following bit-flag constants: Value Description MAP_FOLDCZONE Fold
 *   compatibility zone characters into standard Unicode equivalents. For information about
 *   compatibility zone characters, see the following Remarks section. MAP_FOLDDIGITS Map all digits
 *   to Unicode characters 0 through 9. MAP_PRECOMPOSED Map accented characters to precomposed
 *   characters, in which the accent and base character are combined into a single character value.
 *   This value cannot be combined with MAP_COMPOSITE. MAP_COMPOSITE Map accented characters to
 *   composite characters, in which the accent and base character are represented by two character
 *   values. This value cannot be combined with MAP_PRECOMPOSED. MAP_EXPAND_LIGATURES Not supported.
 * @param lpSrcStr [in] Pointer to the string to be mapped.
 * @param cchSrc [in] Specifies the size, in characters, of the lpSrcStr buffer. If cchSrc is -1,
 *   lpSrcStr is assumed to be null-terminated, and the length is calculated automatically.
 * @param lpDestStr [out] Pointer to the buffer to store the mapped string.
 * @param cchDest [in] Specifies the size, in characters, of the lpDestStr buffer. If cchDest is
 *   zero, the function returns the number of bytes or characters required to hold the mapped string,
 *   and the buffer pointed to by lpDestStr is not used.
 *
 * @return The number of bytes (ANSI version) or characters (Unicode version) written to the
 *   destination buffer, or, if the cchDest parameter is zero, the number of bytes or characters
 *   required to hold the mapped string indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null-terminated if the source string is null-terminated.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The compatibility zone in Unicode consists of characters in the range 0xF900 through 0xFFEF that
 * are assigned to characters from other character-encoding standards but are actually variants of
 * characters that are already in Unicode. The compatibility zone is used to support round-trip
 * mapping to these standards. Applications can use the MAP_FOLDCZONE flag to avoid supporting the
 * duplication of characters in the compatibility zone.
 */
#define FoldString  FoldStringW
#else
/**
 * This function maps one string to another, performing a specified transformation option.
 *
 * @param dwMapFlags [in] Specifies the type of transformation to be used during mapping. This value
 *   can be a combination of the following bit-flag constants: Value Description MAP_FOLDCZONE Fold
 *   compatibility zone characters into standard Unicode equivalents. For information about
 *   compatibility zone characters, see the following Remarks section. MAP_FOLDDIGITS Map all digits
 *   to Unicode characters 0 through 9. MAP_PRECOMPOSED Map accented characters to precomposed
 *   characters, in which the accent and base character are combined into a single character value.
 *   This value cannot be combined with MAP_COMPOSITE. MAP_COMPOSITE Map accented characters to
 *   composite characters, in which the accent and base character are represented by two character
 *   values. This value cannot be combined with MAP_PRECOMPOSED. MAP_EXPAND_LIGATURES Not supported.
 * @param lpSrcStr [in] Pointer to the string to be mapped.
 * @param cchSrc [in] Specifies the size, in characters, of the lpSrcStr buffer. If cchSrc is -1,
 *   lpSrcStr is assumed to be null-terminated, and the length is calculated automatically.
 * @param lpDestStr [out] Pointer to the buffer to store the mapped string.
 * @param cchDest [in] Specifies the size, in characters, of the lpDestStr buffer. If cchDest is
 *   zero, the function returns the number of bytes or characters required to hold the mapped string,
 *   and the buffer pointed to by lpDestStr is not used.
 *
 * @return The number of bytes (ANSI version) or characters (Unicode version) written to the
 *   destination buffer, or, if the cchDest parameter is zero, the number of bytes or characters
 *   required to hold the mapped string indicates success. Zero indicates failure. To get extended
 *   error information, call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INSUFFICIENT_BUFFER ERROR_INVALID_FLAGS ERROR_INVALID_PARAMETER
 *
 * The mapped string is null-terminated if the source string is null-terminated.
 *
 * The lpSrcStr and lpDestStr pointers must not be the same. If they are the same, the function
 * fails and GetLastError returns ERROR_INVALID_PARAMETER.
 *
 * The compatibility zone in Unicode consists of characters in the range 0xF900 through 0xFFEF that
 * are assigned to characters from other character-encoding standards but are actually variants of
 * characters that are already in Unicode. The compatibility zone is used to support round-trip
 * mapping to these standards. Applications can use the MAP_FOLDCZONE flag to avoid supporting the
 * duplication of characters in the compatibility zone.
 */
#define FoldString  FoldStringA
#endif

/**
 * This function enumerates the locales that are either installed on or supported by a system.
 *
 * @param lpLocaleEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemLocales function enumerates locales by making repeated calls to this callback function.
 *   For more information, see the EnumLocalesProc callback function.
 * @param dwFlags [in] Specifies the locale identifiers to enumerate. This parameter can be one of
 *   the following values: Value Description LCID_INSTALLED Enumerate only installed locale
 *   identifiers. LCID_SUPPORTED Enumerate all supported locale identifiers.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The LCID_INSTALLED and LCID_SUPPORTED flags are mutually exclusive.
 */
BOOL WINAPI EnumSystemLocalesW(LOCALE_ENUMPROCW lpLocaleEnumProc, DWORD dwFlags);

#ifdef UNICODE
/**
 * This function enumerates the locales that are either installed on or supported by a system.
 *
 * @param lpLocaleEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemLocales function enumerates locales by making repeated calls to this callback function.
 *   For more information, see the EnumLocalesProc callback function.
 * @param dwFlags [in] Specifies the locale identifiers to enumerate. This parameter can be one of
 *   the following values: Value Description LCID_INSTALLED Enumerate only installed locale
 *   identifiers. LCID_SUPPORTED Enumerate all supported locale identifiers.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The LCID_INSTALLED and LCID_SUPPORTED flags are mutually exclusive.
 */
#define EnumSystemLocales  EnumSystemLocalesW
#else
/**
 * This function enumerates the locales that are either installed on or supported by a system.
 *
 * @param lpLocaleEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemLocales function enumerates locales by making repeated calls to this callback function.
 *   For more information, see the EnumLocalesProc callback function.
 * @param dwFlags [in] Specifies the locale identifiers to enumerate. This parameter can be one of
 *   the following values: Value Description LCID_INSTALLED Enumerate only installed locale
 *   identifiers. LCID_SUPPORTED Enumerate all supported locale identifiers.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The LCID_INSTALLED and LCID_SUPPORTED flags are mutually exclusive.
 */
#define EnumSystemLocales  EnumSystemLocalesA
#endif

/**
 * This function enumerates the code pages that are either installed on or supported by a system.
 *
 * @param lpCodePageEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemCodePages function enumerates code pages by making repeated calls to this callback
 *   function. For more information, see the EnumCodePagesProc callback function.
 * @param dwFlags [in] Specifies the code pages to enumerate. This parameter can be one of the
 *   following values: Value Description CP_INSTALLED Enumerate only installed code pages.
 *   CP_SUPPORTED Enumerate all supported code pages.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The CP_INSTALLED and CP_SUPPORTED flags are mutually exclusive.
 */
BOOL WINAPI EnumSystemCodePagesW(CODEPAGE_ENUMPROCW lpCodePageEnumProc, DWORD dwFlags);

#ifdef UNICODE
/**
 * This function enumerates the code pages that are either installed on or supported by a system.
 *
 * @param lpCodePageEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemCodePages function enumerates code pages by making repeated calls to this callback
 *   function. For more information, see the EnumCodePagesProc callback function.
 * @param dwFlags [in] Specifies the code pages to enumerate. This parameter can be one of the
 *   following values: Value Description CP_INSTALLED Enumerate only installed code pages.
 *   CP_SUPPORTED Enumerate all supported code pages.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The CP_INSTALLED and CP_SUPPORTED flags are mutually exclusive.
 */
#define EnumSystemCodePages  EnumSystemCodePagesW
#else
/**
 * This function enumerates the code pages that are either installed on or supported by a system.
 *
 * @param lpCodePageEnumProc [in] Pointer to an application-defined callback function. The
 *   EnumSystemCodePages function enumerates code pages by making repeated calls to this callback
 *   function. For more information, see the EnumCodePagesProc callback function.
 * @param dwFlags [in] Specifies the code pages to enumerate. This parameter can be one of the
 *   following values: Value Description CP_INSTALLED Enumerate only installed code pages.
 *   CP_SUPPORTED Enumerate all supported code pages.
 *
 * @return Nonzero indicates success. Zero indicates failure. To get extended error information,
 *   call GetLastError. Possible values for GetLastError include the following:
 *   ERROR_INVALID_PARAMETER ERROR_BADDB ERROR_INVALID FLAGS
 *
 * The CP_INSTALLED and CP_SUPPORTED flags are mutually exclusive.
 */
#define EnumSystemCodePages  EnumSystemCodePagesA
#endif

BOOL SetSystemDefaultLCID(LCID Locale);
BOOL SetOEMCP(UINT oemcp);
BOOL SetACP(UINT acp);

#endif   // NONLS

#ifdef __cplusplus
}
#endif

// @CESYSGEN ENDIF

#endif   // _WINNLS_

