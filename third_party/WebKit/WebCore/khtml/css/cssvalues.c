/* ANSI-C code produced by gperf version 2.7.2 */
/* Command-line: gperf -L ANSI-C -E -C -n -o -t -k '*' -NfindValue -Hhash_val -Wwordlist_value -D cssvalues.gperf  */
/* This file is automatically generated from cssvalues.in by makevalues, do not edit */
/* Copyright 1999 W. Bastian */
#include "cssvalues.h"
struct css_value {
    const char *name;
    int id;
};
/* maximum key range = 1944, duplicates = 1 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash_val (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944,    5, 1944, 1944,    0,   15,
        20,   25,   30,   35,   40,    5,   10,    0, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944,    0,   99,   34,
        15,  205,  115,   94,  135,   55,    0,   84,    0,   93,
        30,  200,  145,   50,  140,   59,    0,  190,   68,  120,
       223,   30,   95, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944, 1944,
      1944, 1944, 1944, 1944, 1944, 1944
    };
  register int hval = 0;

  switch (len)
    {
      default:
      case 22:
        hval += asso_values[(unsigned char)str[21]];
      case 21:
        hval += asso_values[(unsigned char)str[20]];
      case 20:
        hval += asso_values[(unsigned char)str[19]];
      case 19:
        hval += asso_values[(unsigned char)str[18]];
      case 18:
        hval += asso_values[(unsigned char)str[17]];
      case 17:
        hval += asso_values[(unsigned char)str[16]];
      case 16:
        hval += asso_values[(unsigned char)str[15]];
      case 15:
        hval += asso_values[(unsigned char)str[14]];
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#endif
const struct css_value *
findValue (register const char *str, register unsigned int len)
{
  enum
    {
      TOTAL_KEYWORDS = 254,
      MIN_WORD_LENGTH = 2,
      MAX_WORD_LENGTH = 22,
      MIN_HASH_VALUE = 0,
      MAX_HASH_VALUE = 1943
    };

  static const struct css_value wordlist_value[] =
    {
      {"900", CSS_VAL_900},
      {"700", CSS_VAL_700},
      {"800", CSS_VAL_800},
      {"100", CSS_VAL_100},
      {"200", CSS_VAL_200},
      {"300", CSS_VAL_300},
      {"400", CSS_VAL_400},
      {"500", CSS_VAL_500},
      {"600", CSS_VAL_600},
      {"navy", CSS_VAL_NAVY},
      {"ltr", CSS_VAL_LTR},
      {"rtl", CSS_VAL_RTL},
      {"italic", CSS_VAL_ITALIC},
      {"static", CSS_VAL_STATIC},
      {"small", CSS_VAL_SMALL},
      {"disc", CSS_VAL_DISC},
      {"fast", CSS_VAL_FAST},
      {"wait", CSS_VAL_WAIT},
      {"hand", CSS_VAL_HAND},
      {"initial", CSS_VAL_INITIAL},
      {"katakana", CSS_VAL_KATAKANA},
      {"start", CSS_VAL_START},
      {"teal", CSS_VAL_TEAL},
      {"always", CSS_VAL_ALWAYS},
      {"black", CSS_VAL_BLACK},
      {"thin", CSS_VAL_THIN},
      {"fantasy", CSS_VAL_FANTASY},
      {"aqua", CSS_VAL_AQUA},
      {"end", CSS_VAL_END},
      {"gray", CSS_VAL_GRAY},
      {"blink", CSS_VAL_BLINK},
      {"table", CSS_VAL_TABLE},
      {"thick", CSS_VAL_THICK},
      {"bold", CSS_VAL_BOLD},
      {"icon", CSS_VAL_ICON},
      {"left", CSS_VAL_LEFT},
      {"solid", CSS_VAL_SOLID},
      {"slide", CSS_VAL_SLIDE},
      {"up", CSS_VAL_UP},
      {"avoid", CSS_VAL_AVOID},
      {"top", CSS_VAL_TOP},
      {"sub", CSS_VAL_SUB},
      {"inset", CSS_VAL_INSET},
      {"lime", CSS_VAL_LIME},
      {"ahead", CSS_VAL_AHEAD},
      {"red", CSS_VAL_RED},
      {"down", CSS_VAL_DOWN},
      {"mix", CSS_VAL_MIX},
      {"inline", CSS_VAL_INLINE},
      {"slow", CSS_VAL_SLOW},
      {"x-small", CSS_VAL_X_SMALL},
      {"middle", CSS_VAL_MIDDLE},
      {"auto", CSS_VAL_AUTO},
      {"small-caps", CSS_VAL_SMALL_CAPS},
      {"decimal", CSS_VAL_DECIMAL},
      {"loud", CSS_VAL_LOUD},
      {"hide", CSS_VAL_HIDE},
      {"block", CSS_VAL_BLOCK},
      {"inside", CSS_VAL_INSIDE},
      {"right", CSS_VAL_RIGHT},
      {"text", CSS_VAL_TEXT},
      {"dashed", CSS_VAL_DASHED},
      {"scroll", CSS_VAL_SCROLL},
      {"both", CSS_VAL_BOTH},
      {"dotted", CSS_VAL_DOTTED},
      {"large", CSS_VAL_LARGE},
      {"single", CSS_VAL_SINGLE},
      {"justify", CSS_VAL_JUSTIFY},
      {"run-in", CSS_VAL_RUN_IN},
      {"hiragana", CSS_VAL_HIRAGANA},
      {"hidden", CSS_VAL_HIDDEN},
      {"normal", CSS_VAL_NORMAL},
      {"caption", CSS_VAL_CAPTION},
      {"none", CSS_VAL_NONE},
      {"circle", CSS_VAL_CIRCLE},
      {"grey", CSS_VAL_GREY},
      {"list-item", CSS_VAL_LIST_ITEM},
      {"level", CSS_VAL_LEVEL},
      {"help", CSS_VAL_HELP},
      {"landscape", CSS_VAL_LANDSCAPE},
      {"pre", CSS_VAL_PRE},
      {"cross", CSS_VAL_CROSS},
      {"blue", CSS_VAL_BLUE},
      {"smaller", CSS_VAL_SMALLER},
      {"invert", CSS_VAL_INVERT},
      {"vertical", CSS_VAL_VERTICAL},
      {"compact", CSS_VAL_COMPACT},
      {"ridge", CSS_VAL_RIDGE},
      {"show", CSS_VAL_SHOW},
      {"white", CSS_VAL_WHITE},
      {"menu", CSS_VAL_MENU},
      {"crop", CSS_VAL_CROP},
      {"default", CSS_VAL_DEFAULT},
      {"silver", CSS_VAL_SILVER},
      {"olive", CSS_VAL_OLIVE},
      {"wider", CSS_VAL_WIDER},
      {"window", CSS_VAL_WINDOW},
      {"visible", CSS_VAL_VISIBLE},
      {"infinite", CSS_VAL_INFINITE},
      {"table-cell", CSS_VAL_TABLE_CELL},
      {"backwards", CSS_VAL_BACKWARDS},
      {"status-bar", CSS_VAL_STATUS_BAR},
      {"armenian", CSS_VAL_ARMENIAN},
      {"yellow", CSS_VAL_YELLOW},
      {"move", CSS_VAL_MOVE},
      {"above", CSS_VAL_ABOVE},
      {"stretch", CSS_VAL_STRETCH},
      {"serif", CSS_VAL_SERIF},
      {"larger", CSS_VAL_LARGER},
      {"alternate", CSS_VAL_ALTERNATE},
      {"fuchsia", CSS_VAL_FUCHSIA},
      {"capitalize", CSS_VAL_CAPITALIZE},
      {"bottom", CSS_VAL_BOTTOM},
      {"xx-small", CSS_VAL_XX_SMALL},
      {"fixed", CSS_VAL_FIXED},
      {"center", CSS_VAL_CENTER},
      {"embed", CSS_VAL_EMBED},
      {"inherit", CSS_VAL_INHERIT},
      {"small-caption", CSS_VAL_SMALL_CAPTION},
      {"below", CSS_VAL_BELOW},
      {"lighter", CSS_VAL_LIGHTER},
      {"nowrap", CSS_VAL_NOWRAP},
      {"-khtml-left", CSS_VAL__KHTML_LEFT},
      {"collapse", CSS_VAL_COLLAPSE},
      {"square", CSS_VAL_SQUARE},
      {"medium", CSS_VAL_MEDIUM},
      {"baseline", CSS_VAL_BASELINE},
      {"outset", CSS_VAL_OUTSET},
      {"bolder", CSS_VAL_BOLDER},
      {"maroon", CSS_VAL_MAROON},
      {"lower", CSS_VAL_LOWER},
      {"-khtml-body", CSS_VAL__KHTML_BODY},
      {"x-large", CSS_VAL_X_LARGE},
      {"orange", CSS_VAL_ORANGE},
      {"scrollbar", CSS_VAL_SCROLLBAR},
      {"relative", CSS_VAL_RELATIVE},
      {"green", CSS_VAL_GREEN},
      {"portrait", CSS_VAL_PORTRAIT},
      {"inline-table", CSS_VAL_INLINE_TABLE},
      {"multiple", CSS_VAL_MULTIPLE},
      {"graytext", CSS_VAL_GRAYTEXT},
      {"repeat", CSS_VAL_REPEAT},
      {"highlight", CSS_VAL_HIGHLIGHT},
      {"double", CSS_VAL_DOUBLE},
      {"-khtml-auto", CSS_VAL__KHTML_AUTO},
      {"inline-axis", CSS_VAL_INLINE_AXIS},
      {"outside", CSS_VAL_OUTSIDE},
      {"sans-serif", CSS_VAL_SANS_SERIF},
      {"repeat-y", CSS_VAL_REPEAT_Y},
      {"katakana-iroha", CSS_VAL_KATAKANA_IROHA},
      {"super", CSS_VAL_SUPER},
      {"-apple-aqua", CSS_VAL__APPLE_AQUA},
      {"-khtml-right", CSS_VAL__KHTML_RIGHT},
      {"transparent", CSS_VAL_TRANSPARENT},
      {"-khtml-text", CSS_VAL__KHTML_TEXT},
      {"cursive", CSS_VAL_CURSIVE},
      {"absolute", CSS_VAL_ABSOLUTE},
      {"separate", CSS_VAL_SEPARATE},
      {"lower-latin", CSS_VAL_LOWER_LATIN},
      {"block-axis", CSS_VAL_BLOCK_AXIS},
      {"higher", CSS_VAL_HIGHER},
      {"table-row", CSS_VAL_TABLE_ROW},
      {"table-caption", CSS_VAL_TABLE_CAPTION},
      {"pointer", CSS_VAL_POINTER},
      {"text-top", CSS_VAL_TEXT_TOP},
      {"-khtml-normal", CSS_VAL__KHTML_NORMAL},
      {"forwards", CSS_VAL_FORWARDS},
      {"condensed", CSS_VAL_CONDENSED},
      {"n-resize", CSS_VAL_N_RESIZE},
      {"inline-block", CSS_VAL_INLINE_BLOCK},
      {"oblique", CSS_VAL_OBLIQUE},
      {"georgian", CSS_VAL_GEORGIAN},
      {"crosshair", CSS_VAL_CROSSHAIR},
      {"s-resize", CSS_VAL_S_RESIZE},
      {"purple", CSS_VAL_PURPLE},
      {"activecaption", CSS_VAL_ACTIVECAPTION},
      {"infotext", CSS_VAL_INFOTEXT},
      {"expanded", CSS_VAL_EXPANDED},
      {"-khtml-box", CSS_VAL__KHTML_BOX},
      {"horizontal", CSS_VAL_HORIZONTAL},
      {"table-column", CSS_VAL_TABLE_COLUMN},
      {"underline", CSS_VAL_UNDERLINE},
      {"buttonface", CSS_VAL_BUTTONFACE},
      {"marquee", CSS_VAL_MARQUEE},
      {"w-resize", CSS_VAL_W_RESIZE},
      {"background", CSS_VAL_BACKGROUND},
      {"xx-large", CSS_VAL_XX_LARGE},
      {"captiontext", CSS_VAL_CAPTIONTEXT},
      {"overline", CSS_VAL_OVERLINE},
      {"hebrew", CSS_VAL_HEBREW},
      {"groove", CSS_VAL_GROOVE},
      {"inactivecaption", CSS_VAL_INACTIVECAPTION},
      {"nw-resize", CSS_VAL_NW_RESIZE},
      {"upper-latin", CSS_VAL_UPPER_LATIN},
      {"repeat-x", CSS_VAL_REPEAT_X},
      {"no-repeat", CSS_VAL_NO_REPEAT},
      {"-khtml-center", CSS_VAL__KHTML_CENTER},
      {"sw-resize", CSS_VAL_SW_RESIZE},
      {"menutext", CSS_VAL_MENUTEXT},
      {"buttontext", CSS_VAL_BUTTONTEXT},
      {"lower-alpha", CSS_VAL_LOWER_ALPHA},
      {"-khtml-nowrap", CSS_VAL__KHTML_NOWRAP},
      {"lowercase", CSS_VAL_LOWERCASE},
      {"monospace", CSS_VAL_MONOSPACE},
      {"windowtext", CSS_VAL_WINDOWTEXT},
      {"e-resize", CSS_VAL_E_RESIZE},
      {"narrower", CSS_VAL_NARROWER},
      {"hiragana-iroha", CSS_VAL_HIRAGANA_IROHA},
      {"ne-resize", CSS_VAL_NE_RESIZE},
      {"reverse", CSS_VAL_REVERSE},
      {"text-bottom", CSS_VAL_TEXT_BOTTOM},
      {"se-resize", CSS_VAL_SE_RESIZE},
      {"buttonshadow", CSS_VAL_BUTTONSHADOW},
      {"threedface", CSS_VAL_THREEDFACE},
      {"windowframe", CSS_VAL_WINDOWFRAME},
      {"upper-alpha", CSS_VAL_UPPER_ALPHA},
      {"uppercase", CSS_VAL_UPPERCASE},
      {"ultra-condensed", CSS_VAL_ULTRA_CONDENSED},
      {"highlighttext", CSS_VAL_HIGHLIGHTTEXT},
      {"lower-roman", CSS_VAL_LOWER_ROMAN},
      {"close-quote", CSS_VAL_CLOSE_QUOTE},
      {"activeborder", CSS_VAL_ACTIVEBORDER},
      {"ultra-expanded", CSS_VAL_ULTRA_EXPANDED},
      {"line-through", CSS_VAL_LINE_THROUGH},
      {"cjk-ideographic", CSS_VAL_CJK_IDEOGRAPHIC},
      {"semi-condensed", CSS_VAL_SEMI_CONDENSED},
      {"buttonhighlight", CSS_VAL_BUTTONHIGHLIGHT},
      {"-khtml-inline-box", CSS_VAL__KHTML_INLINE_BOX},
      {"threedshadow", CSS_VAL_THREEDSHADOW},
      {"open-quote", CSS_VAL_OPEN_QUOTE},
      {"message-box", CSS_VAL_MESSAGE_BOX},
      {"inactiveborder", CSS_VAL_INACTIVEBORDER},
      {"semi-expanded", CSS_VAL_SEMI_EXPANDED},
      {"bidi-override", CSS_VAL_BIDI_OVERRIDE},
      {"-khtml-around-floats", CSS_VAL__KHTML_AROUND_FLOATS},
      {"appworkspace", CSS_VAL_APPWORKSPACE},
      {"infobackground", CSS_VAL_INFOBACKGROUND},
      {"upper-roman", CSS_VAL_UPPER_ROMAN},
      {"inactivecaptiontext", CSS_VAL_INACTIVECAPTIONTEXT},
      {"-khtml-baseline-middle", CSS_VAL__KHTML_BASELINE_MIDDLE},
      {"extra-condensed", CSS_VAL_EXTRA_CONDENSED},
      {"no-close-quote", CSS_VAL_NO_CLOSE_QUOTE},
      {"lower-greek", CSS_VAL_LOWER_GREEK},
      {"threedhighlight", CSS_VAL_THREEDHIGHLIGHT},
      {"extra-expanded", CSS_VAL_EXTRA_EXPANDED},
      {"-khtml-xxx-large", CSS_VAL__KHTML_XXX_LARGE},
      {"decimal-leading-zero", CSS_VAL_DECIMAL_LEADING_ZERO},
      {"no-open-quote", CSS_VAL_NO_OPEN_QUOTE},
      {"threeddarkshadow", CSS_VAL_THREEDDARKSHADOW},
      {"threedlightshadow", CSS_VAL_THREEDLIGHTSHADOW},
      {"table-row-group", CSS_VAL_TABLE_ROW_GROUP},
      {"table-column-group", CSS_VAL_TABLE_COLUMN_GROUP},
      {"table-header-group", CSS_VAL_TABLE_HEADER_GROUP},
      {"table-footer-group", CSS_VAL_TABLE_FOOTER_GROUP}
    };

  static const short lookup[] =
    {
         0,   -1,   -1,   -1,   -1,    1,   -1,   -1,
        -1,   -1,    2,   -1,   -1,   -1,   -1,    3,
        -1,   -1,   -1,   -1,    4,   -1,   -1,   -1,
        -1,    5,   -1,   -1,   -1,   -1,    6,   -1,
        -1,   -1,   -1,    7,   -1,   -1,   -1,   -1,
         8,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
         9,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1, -396, -244,   -2,   -1,
        12,   -1,   -1,   -1,   13,   -1,   -1,   -1,
        14,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   15,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   16,   17,
        -1,   -1,   -1,   -1,   18,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   19,   -1,   -1,   20,   21,
        -1,   -1,   -1,   -1,   -1,   22,   -1,   -1,
        -1,   23,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   24,   -1,   -1,   25,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   26,   -1,   -1,   -1,   -1,   -1,
        27,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   28,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        29,   -1,   -1,   -1,   30,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        31,   -1,   -1,   -1,   32,   -1,   -1,   -1,
        -1,   -1,   33,   -1,   -1,   -1,   -1,   34,
        35,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   36,   -1,   -1,   -1,   -1,   37,   38,
        -1,   -1,   39,   -1,   -1,   -1,   -1,   -1,
        -1,   40,   -1,   -1,   41,   42,   -1,   -1,
        -1,   43,   -1,   44,   -1,   -1,   -1,   -1,
        45,   -1,   -1,   -1,   -1,   46,   -1,   -1,
        -1,   -1,   -1,   47,   -1,   -1,   -1,   48,
        -1,   -1,   -1,   49,   50,   -1,   -1,   51,
        -1,   -1,   -1,   -1,   -1,   -1,   52,   -1,
        -1,   -1,   -1,   53,   -1,   -1,   -1,   -1,
        -1,   -1,   54,   -1,   -1,   55,   -1,   -1,
        -1,   -1,   56,   -1,   -1,   -1,   -1,   -1,
        -1,   57,   -1,   58,   -1,   -1,   -1,   -1,
        59,   -1,   -1,   -1,   60,   61,   -1,   -1,
        -1,   62,   63,   64,   -1,   -1,   -1,   65,
        -1,   -1,   -1,   66,   -1,   -1,   -1,   -1,
        -1,   67,   68,   -1,   -1,   -1,   69,   70,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   71,
        72,   73,   -1,   -1,   74,   75,   -1,   -1,
        76,   -1,   -1,   -1,   -1,   -1,   77,   -1,
        -1,   -1,   -1,   -1,   -1,   78,   -1,   -1,
        79,   -1,   80,   -1,   81,   -1,   82,   -1,
        -1,   83,   84,   -1,   -1,   -1,   85,   -1,
        -1,   -1,   86,   -1,   -1,   87,   -1,   -1,
        -1,   -1,   88,   89,   -1,   -1,   90,   91,
        -1,   -1,   -1,   -1,   -1,   92,   -1,   93,
        94,   -1,   -1,   -1,   -1,   -1,   -1,   95,
        -1,   -1,   -1,   -1,   96,   97,   -1,   -1,
        -1,   98,   -1,   -1,   99,   -1,   -1,  100,
       101,  102,   -1,  103,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  104,   -1,
        -1,   -1,   -1,   -1,  105,  106,  107,   -1,
        -1,   -1,   -1,  108,  109,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  110,  111,   -1,   -1,
       112,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  113,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  114,  115,   -1,
        -1,  116,   -1,   -1,  117,  118,   -1,   -1,
       119,   -1,   -1,   -1,   -1,  120,   -1,   -1,
        -1,   -1,   -1,  121,   -1,   -1,   -1,   -1,
        -1,   -1,  122,  123,  124,   -1,   -1,   -1,
        -1,   -1,   -1,  125,   -1,  126,  127,   -1,
        -1,   -1,   -1,  128,   -1,   -1,   -1,  129,
        -1,  130,  131,  132,   -1,  133,   -1,   -1,
       134,  135,  136,   -1,   -1,   -1,   -1,   -1,
       137,   -1,   -1,   -1,  138,   -1,   -1,   -1,
       139,   -1,   -1,   -1,  140,   -1,   -1,  141,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  142,
        -1,   -1,   -1,   -1,   -1,  143,   -1,   -1,
       144,   -1,   -1,   -1,   -1,  145,   -1,   -1,
        -1,   -1,   -1,   -1,  146,   -1,   -1,  147,
        -1,   -1,  148,   -1,   -1,  149,   -1,   -1,
        -1,   -1,   -1,  150,   -1,   -1,   -1,   -1,
        -1,  151,  152,   -1,   -1,  153,  154,  155,
        -1,  156,  157,  158,   -1,   -1,   -1,  159,
        -1,   -1,   -1,   -1,  160,   -1,   -1,   -1,
        -1,  161,   -1,   -1,   -1,  162,   -1,  163,
        -1,   -1,  164,   -1,   -1,   -1,   -1,   -1,
        -1,  165,   -1,   -1,   -1,  166,   -1,   -1,
        -1,  167,  168,   -1,   -1,  169,   -1,  170,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  171,   -1,   -1,   -1,  172,  173,
        -1,  174,  175,   -1,  176,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  177,   -1,
        -1,   -1,   -1,   -1,  178,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  179,
       180,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  181,   -1,
        -1,  182,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  183,  184,   -1,  185,   -1,
        -1,   -1,  186,   -1,  187,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  188,
       189,   -1,   -1,  190,   -1,   -1,   -1,  191,
        -1,   -1,  192,  193,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  194,   -1,   -1,   -1,   -1,
        -1,   -1,  195,   -1,   -1,   -1,   -1,   -1,
       196,   -1,   -1,   -1,   -1,   -1,   -1,  197,
        -1,   -1,  198,  199,   -1,   -1,  200,   -1,
        -1,   -1,   -1,   -1,   -1,  201,   -1,   -1,
        -1,   -1,   -1,  202,   -1,   -1,  203,   -1,
       204,  205,   -1,   -1,   -1,   -1,   -1,  206,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  207,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  208,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  209,   -1,
        -1,  210,   -1,   -1,  211,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
       212,   -1,   -1,   -1,   -1,   -1,  213,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  214,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  215,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  216,   -1,   -1,   -1,   -1,
       217,   -1,   -1,  218,   -1,  219,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  220,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  221,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  222,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,  223,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  224,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  225,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  226,   -1,
       227,   -1,   -1,   -1,   -1,  228,  229,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,  230,   -1,   -1,   -1,  231,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  232,
        -1,  233,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,  234,  235,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  236,   -1,
        -1,   -1,   -1,   -1,   -1,  237,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  238,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  239,   -1,   -1,  240,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  241,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  242,   -1,
        -1,   -1,   -1,  243,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  244,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  245,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,  246,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  247,   -1,   -1,  248,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,  249,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  250,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,  251,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  252,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
        -1,   -1,   -1,   -1,   -1,   -1,   -1,  253
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash_val (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register int index = lookup[key];

          if (index >= 0)
            {
              register const char *s = wordlist_value[index].name;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return &wordlist_value[index];
            }
          else if (index < -TOTAL_KEYWORDS)
            {
              register int offset = - 1 - TOTAL_KEYWORDS - index;
              register const struct css_value *wordptr = &wordlist_value[TOTAL_KEYWORDS + lookup[offset]];
              register const struct css_value *wordendptr = wordptr + -lookup[offset + 1];

              while (wordptr < wordendptr)
                {
                  register const char *s = wordptr->name;

                  if (*str == *s && !strcmp (str + 1, s + 1))
                    return wordptr;
                  wordptr++;
                }
            }
        }
    }
  return 0;
}
static const char * const valueList[] = {
"",
"inherit", 
"initial", 
"none", 
"hidden", 
"inset", 
"groove", 
"ridge", 
"outset", 
"dotted", 
"dashed", 
"solid", 
"double", 
"-apple-aqua", 
"caption", 
"icon", 
"menu", 
"message-box", 
"small-caption", 
"status-bar", 
"italic", 
"oblique", 
"small-caps", 
"normal", 
"bold", 
"bolder", 
"lighter", 
"100", 
"200", 
"300", 
"400", 
"500", 
"600", 
"700", 
"800", 
"900", 
"xx-small", 
"x-small", 
"small", 
"medium", 
"large", 
"x-large", 
"xx-large", 
"-khtml-xxx-large", 
"smaller", 
"larger", 
"wider", 
"narrower", 
"ultra-condensed", 
"extra-condensed", 
"condensed", 
"semi-condensed", 
"semi-expanded", 
"expanded", 
"extra-expanded", 
"ultra-expanded", 
"serif", 
"sans-serif", 
"cursive", 
"fantasy", 
"monospace", 
"-khtml-body", 
"aqua", 
"black", 
"blue", 
"fuchsia", 
"gray", 
"green", 
"lime", 
"maroon", 
"navy", 
"olive", 
"orange", 
"purple", 
"red", 
"silver", 
"teal", 
"white", 
"yellow", 
"transparent", 
"activeborder", 
"activecaption", 
"appworkspace", 
"background", 
"buttonface", 
"buttonhighlight", 
"buttonshadow", 
"buttontext", 
"captiontext", 
"graytext", 
"highlight", 
"highlighttext", 
"inactiveborder", 
"inactivecaption", 
"inactivecaptiontext", 
"infobackground", 
"infotext", 
"menutext", 
"scrollbar", 
"threeddarkshadow", 
"threedface", 
"threedhighlight", 
"threedlightshadow", 
"threedshadow", 
"window", 
"windowframe", 
"windowtext", 
"grey", 
"-khtml-text", 
"repeat", 
"repeat-x", 
"repeat-y", 
"no-repeat", 
"baseline", 
"middle", 
"sub", 
"super", 
"text-top", 
"text-bottom", 
"top", 
"bottom", 
"-khtml-baseline-middle", 
"-khtml-auto", 
"left", 
"right", 
"center", 
"justify", 
"-khtml-left", 
"-khtml-right", 
"-khtml-center", 
"outside", 
"inside", 
"disc", 
"circle", 
"square", 
"decimal", 
"decimal-leading-zero", 
"lower-roman", 
"upper-roman", 
"lower-greek", 
"lower-alpha", 
"lower-latin", 
"upper-alpha", 
"upper-latin", 
"hebrew", 
"armenian", 
"georgian", 
"cjk-ideographic", 
"hiragana", 
"katakana", 
"hiragana-iroha", 
"katakana-iroha", 
"inline", 
"block", 
"list-item", 
"run-in", 
"compact", 
"inline-block", 
"table", 
"inline-table", 
"table-row-group", 
"table-header-group", 
"table-footer-group", 
"table-row", 
"table-column-group", 
"table-column", 
"table-cell", 
"table-caption", 
"-khtml-box", 
"-khtml-inline-box", 
"auto", 
"crosshair", 
"default", 
"pointer", 
"move", 
"e-resize", 
"ne-resize", 
"nw-resize", 
"n-resize", 
"se-resize", 
"sw-resize", 
"s-resize", 
"w-resize", 
"text", 
"wait", 
"help", 
"ltr", 
"rtl", 
"capitalize", 
"uppercase", 
"lowercase", 
"visible", 
"collapse", 
"above", 
"absolute", 
"always", 
"avoid", 
"below", 
"bidi-override", 
"blink", 
"both", 
"close-quote", 
"crop", 
"cross", 
"embed", 
"fixed", 
"hand", 
"hide", 
"higher", 
"invert", 
"landscape", 
"level", 
"line-through", 
"loud", 
"lower", 
"marquee", 
"mix", 
"no-close-quote", 
"no-open-quote", 
"nowrap", 
"open-quote", 
"overline", 
"portrait", 
"pre", 
"relative", 
"scroll", 
"separate", 
"show", 
"static", 
"thick", 
"thin", 
"underline", 
"-khtml-nowrap", 
"-khtml-normal", 
"-khtml-around-floats", 
"stretch", 
"start", 
"end", 
"reverse", 
"horizontal", 
"vertical", 
"inline-axis", 
"block-axis", 
"single", 
"multiple", 
"forwards", 
"backwards", 
"ahead", 
"up", 
"down", 
"slow", 
"fast", 
"infinite", 
"slide", 
"alternate", 
    0
};
DOMString getValueName(unsigned short id)
{
    if(id >= CSS_VAL_TOTAL || id == 0)
      return DOMString();
    else
      return DOMString(valueList[id]);
};

