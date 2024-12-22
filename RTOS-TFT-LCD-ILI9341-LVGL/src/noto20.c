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

    /* U+0027 "'" */
    0xfd, 0x40,

    /* U+0028 "(" */
    0x19, 0x98, 0xc6, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x31, 0x86, 0x30, 0xc0,

    /* U+0029 ")" */
    0xc3, 0xc, 0x63, 0xc, 0x63, 0x18, 0xc6, 0x31,
    0x98, 0xcc, 0x66, 0x0,

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
    {.bitmap_index = 1, .adv_w = 72, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 15, .adv_w = 96, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 27, .adv_w = 86, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 29, .adv_w = 86, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 119, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 183, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 183, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 183, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 86, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 198, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 178, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 234, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 197, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 180, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 198, .box_w = 9, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 83, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 83, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 299, .box_w = 16, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 198, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 194, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x7, 0x8, 0x9, 0xc, 0xe, 0xf, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    0x19, 0x1a, 0x2b, 0x34, 0x35, 0x41, 0x44, 0x45,
    0x48, 0x49, 0x4c, 0x4d, 0x4e, 0x4f, 0x52, 0x53
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 84, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 32, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 0, 0, 2, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3, 4, 5, 0,
    5, 5, 0, 0, 5, 5, 5, 6,
    0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0, 0, 2, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3, 4, 5, 6,
    6, 0, 0, 0, 7, 7, 6, 7,
    8
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 6, 0, -13, -19, -10, -10,
    0, 0, -22, -6, 0, 0, 0, 0,
    0, -19, 6, 0, -26, -22, -16, -19,
    0, -6, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    13, -51, 0, 0, -6, -6, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 6,
    .right_class_cnt     = 8,
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
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
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
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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

