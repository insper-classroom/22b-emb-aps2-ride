/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include <asf.h>
#include <string.h>
#include "ili9341.h"
#include "lvgl.h"
#include "touch/touch.h"
#include "imgUX1.h"
#include "settings_img.h"

LV_FONT_DECLARE(noto50);
LV_FONT_DECLARE(noto20);
LV_FONT_DECLARE(settings_icon);
LV_FONT_DECLARE(playpause_icon);
LV_FONT_DECLARE(updown_icon);

#define MY_SETTINGS_SYMBOL "\xEF\x80\x93"
#define MY_PLAY_SYMBOL "\xEF\x81\x8B"
#define MY_PAUSE_SYMBOL "\xEF\x81\x8C"
#define MY_UP_ARROW_SYMBOL "\xEF\x84\x82"
#define MY_DOWN_ARROW_SYMBOL "\xEF\x84\x83"

/************************************************************************/
/* LCD / LVGL                                                           */
/************************************************************************/

// #define LV_HOR_RES_MAX          (320)
// #define LV_VER_RES_MAX          (240)

#define LV_HOR_RES_MAX          (240)
#define LV_VER_RES_MAX          (320)

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
static lv_indev_drv_t indev_drv;

// declarar a tela como global e estática
static lv_obj_t * main_scr;  // main screen 1
static lv_obj_t * settings_scr;  // settings screen 2

static  lv_obj_t * label_settings_btn;
static  lv_obj_t * label_play_btn;
static  lv_obj_t * label_pause_btn;
static  lv_obj_t * label_up_arrow;
static  lv_obj_t * label_speed;
static  lv_obj_t * label_speed_txt;


/************************************************************************/
/* RTOS                                                                 */
/************************************************************************/

#define TASK_LCD_STACK_SIZE                (1024*6/sizeof(portSTACK_TYPE))
#define TASK_LCD_STACK_PRIORITY            (tskIDLE_PRIORITY)

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,  signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	for (;;) {	}
}

extern void vApplicationIdleHook(void) { }

extern void vApplicationTickHook(void) { }

extern void vApplicationMallocFailedHook(void) {
	configASSERT( ( volatile void * ) NULL );
}

/************************************************************************/
/* lvgl                                                                 */
/************************************************************************/

static void event_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		LV_LOG_USER("Clicked");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		LV_LOG_USER("Toggled");
	}
}

static void settings_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		printf("Clicked\n");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

void lv_main_scr(void) {

	printf("Criando widgets \n");
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);

	// Settings button
	lv_obj_t * settings_btn = lv_imgbtn_create(main_scr);
	lv_obj_set_width(settings_btn, 32); 
	lv_obj_set_height(settings_btn, 32);

	lv_obj_add_event_cb(settings_btn, settings_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(settings_btn, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(settings_btn, &style, 0);

	label_settings_btn = lv_label_create(settings_btn);
	lv_obj_set_style_text_font(label_settings_btn, &settings_icon, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_settings_btn, MY_SETTINGS_SYMBOL);
	lv_obj_center(label_settings_btn);

	// Play button
	lv_obj_t * play_btn = lv_imgbtn_create(main_scr);
	lv_obj_set_width(play_btn, 32); 
	lv_obj_set_height(play_btn, 32);

	lv_obj_add_event_cb(play_btn, settings_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(play_btn, LV_ALIGN_BOTTOM_LEFT, 10, -10);
	lv_obj_add_style(play_btn, &style, 0);

	label_play_btn = lv_label_create(play_btn);
	lv_obj_set_style_text_font(label_play_btn, &playpause_icon, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_play_btn, MY_PLAY_SYMBOL);
	lv_obj_center(label_play_btn);


	// Pause button
	lv_obj_t * pause_btn = lv_imgbtn_create(main_scr);
	lv_obj_set_width(pause_btn, 32); 
	lv_obj_set_height(pause_btn, 32);

	lv_obj_add_event_cb(pause_btn, settings_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(pause_btn, LV_ALIGN_BOTTOM_RIGHT, -10, -10);
	lv_obj_add_style(pause_btn, &style, 0);

	label_pause_btn = lv_label_create(pause_btn);
	lv_obj_set_style_text_font(label_pause_btn, &playpause_icon, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_pause_btn, MY_PAUSE_SYMBOL);
	lv_obj_center(label_pause_btn);

	// Up button
	lv_obj_t * up_arrow = lv_imgbtn_create(main_scr);
	lv_obj_set_width(up_arrow, 60); 
	lv_obj_set_height(up_arrow, 60);

	label_up_arrow = lv_label_create(up_arrow);
	lv_obj_align(up_arrow, LV_ALIGN_CENTER, 45, -30);
	lv_obj_add_style(up_arrow, &style, 0);
	lv_obj_set_style_text_font(label_up_arrow, &updown_icon, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_up_arrow, MY_UP_ARROW_SYMBOL);
	lv_obj_center(label_up_arrow); 

	// Speed number
	label_speed = lv_label_create(main_scr);
	lv_obj_align(label_speed, LV_ALIGN_CENTER, -5 , -30);
	lv_obj_set_style_text_font(label_speed, &noto50, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_speed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_speed, "%02d", 30);


	// Speed text
	label_speed_txt = lv_label_create(main_scr);
	lv_obj_align(label_speed_txt, LV_ALIGN_CENTER, 0 , 10);
	lv_obj_set_style_text_font(label_speed_txt, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_speed_txt, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_speed_txt, "Km/h");

}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/

static void task_lcd(void *pvParameters) {
	int px, py;
	
	// lv_obj_t * img = lv_img_create(lv_scr_act());
	// lv_img_set_src(img, &imgUX1);
	// lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

	// Cria main screen
	main_scr  = lv_obj_create(NULL);
	lv_main_scr();
	lv_scr_load(main_scr); // exibe tela 1

	//lv_ex_btn_1();

	for (;;)  {
		lv_tick_inc(50);
		lv_task_handler();
		vTaskDelay(50);
	}
}

/************************************************************************/
/* configs                                                              */
/************************************************************************/

static void configure_lcd(void) {
	/**LCD pin configure on SPI*/
	pio_configure_pin(LCD_SPI_MISO_PIO, LCD_SPI_MISO_FLAGS);  //
	pio_configure_pin(LCD_SPI_MOSI_PIO, LCD_SPI_MOSI_FLAGS);
	pio_configure_pin(LCD_SPI_SPCK_PIO, LCD_SPI_SPCK_FLAGS);
	pio_configure_pin(LCD_SPI_NPCS_PIO, LCD_SPI_NPCS_FLAGS);
	pio_configure_pin(LCD_SPI_RESET_PIO, LCD_SPI_RESET_FLAGS);
	pio_configure_pin(LCD_SPI_CDS_PIO, LCD_SPI_CDS_FLAGS);
	
	ili9341_init();
	ili9341_backlight_on();
}

static void configure_console(void) {
	const usart_serial_options_t uart_serial_options = {
		.baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT,
	};

	/* Configure console UART. */
	stdio_serial_init(CONSOLE_UART, &uart_serial_options);

	/* Specify that stdout should not be buffered. */
	setbuf(stdout, NULL);
}

/************************************************************************/
/* port lvgl                                                            */
/************************************************************************/

void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
	ili9341_set_top_left_limit(area->x1, area->y1);   ili9341_set_bottom_right_limit(area->x2, area->y2);
	ili9341_copy_pixels_to_screen(color_p,  (area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1));
	
	/* IMPORTANT!!!
	* Inform the graphics library that you are ready with the flushing*/
	lv_disp_flush_ready(disp_drv);
}

void my_input_read(lv_indev_drv_t * drv, lv_indev_data_t*data) {
	int px, py, pressed;
	
	if (readPoint(&px, &py))
		data->state = LV_INDEV_STATE_PRESSED;
	else
		data->state = LV_INDEV_STATE_RELEASED; 
	
	data->point.x = py;
	data->point.y = 320 - px;
}

void configure_lvgl(void) {
	lv_init();
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);
	
	lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
	disp_drv.flush_cb = my_flush_cb;        /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = LV_HOR_RES_MAX;      /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = LV_VER_RES_MAX;      /*Set the vertical resolution in pixels*/

	lv_disp_t * disp;
	disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/
	
	/* Init input on LVGL */
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_input_read;
	lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
}

/************************************************************************/
/* main                                                                 */
/************************************************************************/
int main(void) {
	/* board and sys init */
	board_init();
	sysclk_init();
	configure_console();

	/* LCd, touch and lvgl init*/
	configure_lcd();
	configure_touch();
	configure_lvgl();
	ili9341_set_orientation(ILI9341_FLIP_Y | ILI9341_SWITCH_XY);

	/* Create task to control oled */
	if (xTaskCreate(task_lcd, "LCD", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create lcd task\r\n");
	}
	
	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1){ }
}
