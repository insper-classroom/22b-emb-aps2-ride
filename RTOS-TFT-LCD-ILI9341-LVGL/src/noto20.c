/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/
#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef NOTO20
#define NOTO20 1
#endif

#if NOTO20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002C "," */
    0x6b, 0x68,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x6, 0xc, 0x10, 0x60, 0xc3, 0x6, 0x8, 0x30,
    0x60, 0x83, 0x6, 0x18, 0x0,

    /* U+0030 "0" */
    0x1e, 0x18, 0xc6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xd, 0x86, 0x63,
    0x87, 0x80,

    /* U+0031 "1" */
    0xc, 0xf6, 0xd3, 0xc, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0xc, 0x30,

    /* U+0032 "2" */
    0x3e, 0x71, 0x80, 0x60, 0x30, 0x18, 0xc, 0xc,
    0xe, 0xe, 0xe, 0xe, 0xe, 0x6, 0x7, 0xfc,

    /* U+0033 "3" */
    0x7e, 0x61, 0x80, 0x60, 0x30, 0x18, 0x18, 0xf0,
    0x6, 0x1, 0x80, 0xc0, 0x60, 0x38, 0x37, 0xf0,

    /* U+0034 "4" */
    0x3, 0x80, 0x70, 0x1e, 0x6, 0xc1, 0x98, 0x23,
    0xc, 0x63, 0xc, 0xc1, 0x9f, 0xfc, 0x6, 0x0,
    0xc0, 0x18, 0x3, 0x0,

    /* U+0035 "5" */
    0x7f, 0x20, 0x10, 0x8, 0xc, 0x7, 0xf0, 0xc,
    0x3, 0x1, 0x80, 0xc0, 0x60, 0x38, 0x37, 0xe0,

    /* U+0036 "6" */
    0xf, 0x8c, 0x6, 0x1, 0x80, 0xc0, 0x37, 0xce,
    0x1b, 0x3, 0xc0, 0xf0, 0x3c, 0xd, 0x83, 0x71,
    0x87, 0xc0,

    /* U+0037 "7" */
    0xff, 0xc0, 0x30, 0x18, 0x6, 0x3, 0x0, 0xc0,
    0x60, 0x18, 0xe, 0x3, 0x0, 0xc0, 0x60, 0x18,
    0xc, 0x0,

    /* U+0038 "8" */
    0x3e, 0x18, 0xcc, 0x1b, 0x6, 0xc1, 0x9d, 0xc3,
    0xc1, 0xdc, 0x61, 0xb0, 0x3c, 0xf, 0x3, 0x61,
    0x8f, 0xc0,

    /* U+0039 "9" */
    0x3c, 0x31, 0xb0, 0x58, 0x3c, 0x1e, 0xd, 0x8e,
    0x7b, 0x1, 0x80, 0xc0, 0xc0, 0x60, 0x63, 0xe0,

    /* U+003A ":" */
    0xf0, 0x0, 0x3c,

    /* U+004B "K" */
    0xc0, 0xd8, 0x33, 0xc, 0x63, 0xc, 0xc1, 0xb0,
    0x3e, 0x7, 0x60, 0xce, 0x18, 0xc3, 0xc, 0x60,
    0xcc, 0x1d, 0x81, 0x80,

    /* U+0054 "T" */
    0xff, 0xe1, 0x80, 0x30, 0x6, 0x0, 0xc0, 0x18,
    0x3, 0x0, 0x60, 0xc, 0x1, 0x80, 0x30, 0x6,
    0x0, 0xc0, 0x18, 0x0,

    /* U+0055 "U" */
    0xc0, 0x78, 0xf, 0x1, 0xe0, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x1, 0xa0,
    0x66, 0xc, 0x3e, 0x0,

    /* U+0061 "a" */
    0x3f, 0x11, 0xc0, 0x60, 0x30, 0x19, 0xff, 0x87,
    0x83, 0xc1, 0xe1, 0xdf, 0x60,

    /* U+0064 "d" */
    0x0, 0xc0, 0x30, 0xc, 0x3, 0x3e, 0xd8, 0x76,
    0x1f, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0x60,
    0xd8, 0x73, 0xec,

    /* U+0065 "e" */
    0x1e, 0x31, 0x98, 0x78, 0x3c, 0x1f, 0xff, 0x1,
    0x80, 0x60, 0x30, 0x7, 0xc0,

    /* U+0068 "h" */
    0xc0, 0x60, 0x30, 0x18, 0xd, 0xe7, 0x1b, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf,
    0x6,

    /* U+0069 "i" */
    0xf0, 0xff, 0xff, 0xfc,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xdf, 0x3c, 0xe3, 0xc6, 0xc1, 0x83, 0xc1, 0x83,
    0xc1, 0x83, 0xc1, 0x83, 0xc1, 0x83, 0xc1, 0x83,
    0xc1, 0x83, 0xc1, 0x83, 0xc1, 0x83,

    /* U+006E "n" */
    0xde, 0x71, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x60,

    /* U+006F "o" */
    0x1e, 0x18, 0x66, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0x61, 0x98, 0x61, 0xe0,

    /* U+0072 "r" */
    0xdd, 0xe3, 0x86, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0073 "s" */
    0x3f, 0xc2, 0xc0, 0xe0, 0xf8, 0x3e, 0xf, 0x3,
    0x3, 0x86, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 83, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 86, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3, .adv_w = 86, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 119, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 183, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 86, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 198, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 178, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 234, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 197, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 198, .box_w = 9, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 83, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 83, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 299, .box_w = 16, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 198, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 194, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xc, 0xe, 0xf, 0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x2b,
    0x34, 0x35, 0x41, 0x44, 0x45, 0x48, 0x49, 0x4c,
    0x4d, 0x4e, 0x4f, 0x52, 0x53
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 84, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 29, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    2, 17,
    2, 18,
    3, 17,
    3, 18,
    17, 2,
    17, 3,
    17, 17,
    17, 19,
    17, 20,
    17, 21,
    17, 25,
    17, 26,
    17, 27,
    17, 28,
    17, 29,
    18, 2,
    18, 3,
    28, 2,
    28, 3,
    28, 19,
    28, 20,
    28, 21,
    28, 27
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -22, -6, -22, -6, -19, -19, 6, -26,
    -22, -22, -16, -16, -22, -16, -19, -6,
    -6, -51, -51, -6, -6, -6, -6
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 23,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t noto20 = {
#else
lv_font_t noto20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if NOTO20*/

