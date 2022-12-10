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
#include "ride.h"

#include "arm_math.h"

#define TASK_SIMULATOR_STACK_SIZE (4096 / sizeof(portSTACK_TYPE))
#define TASK_SIMULATOR_STACK_PRIORITY (tskIDLE_PRIORITY)

#define RAIO 0.508/2
#define VEL_MAX_KMH  5.0f
#define VEL_MIN_KMH  0.5f

LV_FONT_DECLARE(noto50);
LV_FONT_DECLARE(noto30);
LV_FONT_DECLARE(noto20);
LV_FONT_DECLARE(settings_icon);
LV_FONT_DECLARE(playpause_icon);
LV_FONT_DECLARE(updown_icon);

#define MY_SETTINGS_SYMBOL "\xEF\x80\x93"
#define MY_PLAY_SYMBOL "\xEF\x81\x8B"
#define MY_PAUSE_SYMBOL "\xEF\x81\x8C"
#define MY_UP_ARROW_SYMBOL "\xEF\x84\x82"
#define MY_DOWN_ARROW_SYMBOL "\xEF\x84\x83"

#define CICLE_PIO PIOA
#define CICLE_PIO_ID ID_PIOA
#define CICLE_IDX_MASK (1 << 19)



typedef struct  {
  uint32_t year;
  uint32_t month;
  uint32_t day;
  uint32_t week;
  uint32_t hour;
  uint32_t minute;
  uint32_t second;
} calendar;
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
static lv_obj_t * loading_scr;  // load screen 0
static lv_obj_t * main_scr;  // main screen 1
static lv_obj_t * settings_scr;  // settings screen 2

//TELA 1

static  lv_obj_t * label_settings_btn;
static  lv_obj_t * label_play_btn;
static  lv_obj_t * label_pause_btn;
static  lv_obj_t * label_up_arrow;

static  lv_obj_t * label_speed;
static  lv_obj_t * label_speed_txt;

static  lv_obj_t * label_average_speed_txt;
static  lv_obj_t * label_average_speed_number;

static  lv_obj_t * label_distance_txt;
static  lv_obj_t * label_distance_number;

static  lv_obj_t * label_time_number;
static  lv_obj_t * label_duration_number;

//TELA 2

static  lv_obj_t * label_back_btn;

static  lv_obj_t * label_bike_rim;
static  lv_obj_t * label_markdown_rim;

static  lv_obj_t * label_measure;
static  lv_obj_t * label_km_btn;
static  lv_obj_t * label_miles_btn;


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

SemaphoreHandle_t xSemaphoreRTC;

QueueHandle_t xQueueScreens;
QueueHandle_t xQueueTime;


void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type);
static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);


/************************************************************************/
/* lvgl                                                                 */
/************************************************************************/

static void settings_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		int scr_idx = 2;
		BaseType_t xHigherPriorityTaskWoken = pdTRUE;
		xQueueSendFromISR(xQueueScreens, &scr_idx, &xHigherPriorityTaskWoken);
	}
	else if (code == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

static void back_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if (code == LV_EVENT_CLICKED) {
		int scr_idx = 1;
		BaseType_t xHigherPriorityTaskWoken = pdTRUE;
		xQueueSendFromISR(xQueueScreens, &scr_idx, &xHigherPriorityTaskWoken);
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

static void km_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		printf("Clicked\n");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

static void miles_handler(lv_event_t * e) {
	lv_event_code_t code = lv_event_get_code(e);

	if(code == LV_EVENT_CLICKED) {
		printf("Clicked\n");
	}
	else if(code == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

static void dropdown_handler(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        char buf[32];
        lv_roller_get_selected_str(obj, buf, sizeof(buf));
        LV_LOG_USER("Selected month: %s\n", buf);
		printf("Selected measure: %s\n", buf);
    }
}

void RTC_Handler(void) {
    uint32_t ul_status = rtc_get_status(RTC);

	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC) {
    	//  Entrou por segundo! 
    	rtc_clear_status(RTC, RTC_SCCR_SECCLR);
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreRTC, &xHigherPriorityTaskWoken);
	}

    rtc_clear_status(RTC, RTC_SCCR_SECCLR);
    rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
    rtc_clear_status(RTC, RTC_SCCR_ACKCLR);
    rtc_clear_status(RTC, RTC_SCCR_TIMCLR);
    rtc_clear_status(RTC, RTC_SCCR_CALCLR);
    rtc_clear_status(RTC, RTC_SCCR_TDERRCLR);
}

void cicle_callback(){
	uint32_t dt = rtt_read_timer_value(RTT);
	RTT_init(18000, 0, 0);
	xQueueSendFromISR(xQueueTime, &dt, 0);

	// printf("handler\n");
	
	// if(pio_get(ECHO_PIO, PIO_INPUT, ECHO_PIO_PIN_MASK)){
	// } else {
	// 	xQueueSendFromISR(xQueueTime, &dt, 0);
	// }
}

void lv_main_scr(void) {

	printf("Criando widgets main screen\n");
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

	// Up Image
	lv_obj_t * up_arrow = lv_imgbtn_create(main_scr);
	lv_obj_set_width(up_arrow, 60); 
	lv_obj_set_height(up_arrow, 60);

	label_up_arrow = lv_label_create(up_arrow);
	lv_obj_align(up_arrow, LV_ALIGN_CENTER, 45, -55);
	lv_obj_add_style(up_arrow, &style, 0);
	lv_obj_set_style_text_font(label_up_arrow, &updown_icon, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_up_arrow, MY_UP_ARROW_SYMBOL);
	lv_obj_center(label_up_arrow); 

	// Speed number
	label_speed = lv_label_create(main_scr);
	lv_obj_align(label_speed, LV_ALIGN_CENTER, -5 , -55);
	lv_obj_set_style_text_font(label_speed, &noto50, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_speed, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_speed, "%02d", 30);

	// Speed text
	label_speed_txt = lv_label_create(main_scr);
	lv_obj_align(label_speed_txt, LV_ALIGN_CENTER, 0 , -15);
	lv_obj_set_style_text_font(label_speed_txt, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_speed_txt, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_speed_txt, "Km/h");
	
	// Average speed text
	label_average_speed_txt = lv_label_create(main_scr);
	lv_obj_align(label_average_speed_txt, LV_ALIGN_CENTER, -30 , 40);
	lv_obj_set_style_text_font(label_average_speed_txt, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_average_speed_txt, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_average_speed_txt, "Km/h");

	// Average speed number
	label_average_speed_number = lv_label_create(main_scr);
	lv_obj_align(label_average_speed_number, LV_ALIGN_CENTER, -65 , 40);
	lv_obj_set_style_text_font(label_average_speed_number, &noto30, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_average_speed_number, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_average_speed_number, "0");
	
	// Distance text
	label_distance_txt = lv_label_create(main_scr);
	lv_obj_align(label_distance_txt, LV_ALIGN_CENTER, 80 , 40);
	lv_obj_set_style_text_font(label_distance_txt, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_distance_txt, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_distance_txt, "Km");

	// Distance number
	label_distance_number = lv_label_create(main_scr);
	lv_obj_align(label_distance_number, LV_ALIGN_CENTER, 55 , 40);
	lv_obj_set_style_text_font(label_distance_number, &noto30, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_distance_number, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_distance_number, "0");

	// Time number
	label_time_number = lv_label_create(main_scr);
	lv_obj_align(label_time_number, LV_ALIGN_TOP_RIGHT, -10 , 10);
	lv_obj_set_style_text_font(label_time_number, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_time_number, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_time_number, "00:00:00");

	// Duration number
	label_duration_number = lv_label_create(main_scr);
	lv_obj_align(label_duration_number, LV_ALIGN_BOTTOM_MID, 0 , -15);
	lv_obj_set_style_text_font(label_duration_number, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_duration_number, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_duration_number, "00:00");
}

void lv_settings_scr(void){
	printf("Criando widgets settings screen\n");
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_bg_color(&style, lv_color_white());
	lv_style_set_border_color(&style, lv_color_white());
	lv_style_set_border_width(&style, 0);

	// Bike rim number
	label_bike_rim = lv_label_create(settings_scr);
	lv_obj_align(label_bike_rim, LV_ALIGN_CENTER, 0 , -100);
	lv_obj_set_style_text_font(label_bike_rim, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_bike_rim, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_bike_rim, "Tamanho do aro");

	// Rims Markdowns
	lv_obj_t * roller1 = lv_roller_create(settings_scr);
    lv_roller_set_options(roller1,
                          "14''\n"
                          "16''\n"
                          "18''\n"
                          "20''\n"
                          "22''\n"
                          "24''\n",
                          LV_ROLLER_MODE_INFINITE);

    lv_roller_set_visible_row_count(roller1, 2);
    lv_obj_center(roller1);
    lv_obj_add_event_cb(roller1, dropdown_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(roller1, LV_ALIGN_CENTER, 0, -40);
	

	// Return button
	lv_obj_t * back_btn = lv_imgbtn_create(settings_scr);
	lv_obj_set_width(back_btn, 32); 
	lv_obj_set_height(back_btn, 32);

	lv_obj_add_event_cb(back_btn, back_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(back_btn, LV_ALIGN_OUT_LEFT_TOP, 5, 5);
	lv_obj_add_style(back_btn, &style, 0);

	label_back_btn = lv_label_create(back_btn);
	lv_label_set_text_fmt(label_back_btn, LV_SYMBOL_LEFT);
	lv_obj_center(label_back_btn);

	// Measure number
	label_measure = lv_label_create(settings_scr);
	lv_obj_align(label_measure, LV_ALIGN_CENTER, 0 , 30);
	lv_obj_set_style_text_font(label_measure, &noto20, LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label_measure, lv_color_black(), LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_measure, "Unidade");

	// Km button
	lv_obj_t * km_btn = lv_imgbtn_create(settings_scr);
	lv_obj_set_width(km_btn, 32); 
	lv_obj_set_height(km_btn, 32);

	lv_obj_add_event_cb(km_btn, km_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(km_btn, LV_ALIGN_CENTER, -50, 70);
	lv_obj_add_style(km_btn, &style, 0);

	label_km_btn = lv_label_create(km_btn);
	lv_obj_set_style_text_font(label_km_btn, &noto20, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_km_btn, "Km");
	lv_obj_center(label_km_btn);

	// Miles button
	lv_obj_t * miles_btn = lv_imgbtn_create(settings_scr);
	lv_obj_set_width(miles_btn, 64); 
	lv_obj_set_height(miles_btn, 32);

	lv_obj_add_event_cb(miles_btn, miles_handler, LV_EVENT_ALL, NULL);
	lv_obj_align(miles_btn, LV_ALIGN_CENTER, 50, 70);
	lv_obj_add_style(miles_btn, &style, 0);

	label_miles_btn = lv_label_create(miles_btn);
	lv_obj_set_style_text_font(label_miles_btn, &noto20, LV_STATE_DEFAULT);
	lv_label_set_text_fmt(label_miles_btn, "milhas");
	lv_obj_center(label_miles_btn);

}
/************************************************************************/
/* TASKS                                                                */
/************************************************************************/

static void task_lcd(void *pvParameters) {
	int px, py;

	// Cria loading screens

	lv_color_t bege = lv_color_hex(0xF5FFF4);

	loading_scr = lv_obj_create(NULL);
	lv_obj_set_style_bg_color(loading_scr, bege, LV_PART_MAIN );
	lv_obj_t * img = lv_img_create(loading_scr);
	lv_img_set_src(img, &ride);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
	lv_scr_load(loading_scr); // exibe tela 0

	main_scr = lv_obj_create(NULL);
	settings_scr = lv_obj_create(NULL);
	lv_main_scr();
	lv_settings_scr();

	// lv_scr_load(main_scr); // exibe tela 1
	// lv_scr_load(settings_scr); // exibe tela 2


	int screen = 0;

	for (;;)  {
		lv_tick_inc(50);
		lv_task_handler();
		vTaskDelay(50);

		if (screen == 0) {
			lv_scr_load(loading_scr); // exibe tela 0
			vTaskDelay(5000);
			screen = 1;
			lv_scr_load(main_scr); // exibe tela 1
		}

		if (xQueueReceive(xQueueScreens, &screen, 10)) {
			printf("Screen: %d\n", screen);
			if (screen == 1) {
				lv_scr_load(main_scr); // exibe tela 1
			} else if (screen == 2) {
				lv_scr_load(settings_scr); // exibe tela 2
			}
		}
	}
}

static void task_rtc(void *pvParameters){
	uint32_t current_hour, current_min, current_sec;
	calendar rtc_initial = {2018, 3, 19, 12, 15, 45 ,1};
	int second_flag = 0;
	int id;

	RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_ALREN | RTC_IER_SECEN);
	rtc_get_time(RTC, &current_hour, &current_min, &current_sec);
	lv_label_set_text_fmt(label_time_number, "%02d:%02d:%02d", current_hour, current_min, current_sec);    

	for (;;)  {
		if (xSemaphoreTake(xSemaphoreRTC, 0)) {		
			rtc_get_time(RTC, &current_hour, &current_min, &current_sec);
			if (second_flag == 0) {
				lv_label_set_text_fmt(label_time_number, "%02d:%02d:%02d", current_hour, current_min, current_sec);
				second_flag = 1;
			} else {
				lv_label_set_text_fmt(label_time_number, "%02d %02d %02d", current_hour, current_min, current_sec);  
				second_flag = 0;
			}
		}
	}
}

static void task_speed(void *pvParameters){
	int instant_speed = 0;
	int dt_rtt;
	float dt;
	float w, r;
	int pol = 20;

	for (;;)  {
		if (xQueueReceive(xQueueTime, &dt_rtt, 0)) {
			printf("Dt rtt: %d\n",dt_rtt);
			// dt = dt_rtt / 18000;
			// w = 2 * 3.14 / dt;
			// r = pol * 0.0254;
			// instant_speed = w * r;
			// printf("Instant speed: %d\n",instant_speed);
		}		
	}
}

float kmh_to_hz(float vel, float raio) {
    float f = vel / (2*PI*raio*3.6);
    return(f);
}

static void task_simulador(void *pvParameters) {
    pmc_enable_periph_clk(ID_PIOC);
    pio_set_output(PIOC, PIO_PC31, 1, 0, 0);

    float vel = VEL_MAX_KMH;
    float f;
    int ramp_up = 1;
	int ramp = 0;

    while(1) {
        pio_clear(PIOC, PIO_PC31);
        delay_ms(1);
        pio_set(PIOC, PIO_PC31);

		if (ramp) {
			if (ramp_up) {
				printf("[SIMU] ACELERANDO: %d \n", (int) (10*vel));
				vel += 0.5;
			} else {
				printf("[SIMU] DESACELERANDO: %d \n",  (int) (10*vel));
				vel -= 0.5;
			}

			if (vel >= VEL_MAX_KMH) {
				ramp_up = 0;
			} else if (vel <= VEL_MIN_KMH) {
				ramp_up = 1;
			}

		} else {
			vel = 5;
			printf("[SIMU] CONSTANTE: %d \n", (int) (10*vel));
		}
        f = kmh_to_hz(vel, RAIO);
        int t = 965*(1.0/f); //UTILIZADO 965 como multiplicador ao invés de 1000
                             //para compensar o atraso gerado pelo Escalonador do freeRTOS
        delay_ms(t);
    }
}

/************************************************************************/
/* configs                                                              */
/************************************************************************/

void cicle_init(void) {
	pmc_enable_periph_clk(CICLE_PIO_ID);

	pio_configure(CICLE_PIO, PIO_INPUT, CICLE_IDX_MASK, PIO_PULLUP| PIO_DEBOUNCE);

	pio_handler_set(CICLE_PIO, CICLE_PIO_ID, CICLE_IDX_MASK, PIO_IT_FALL_EDGE, cicle_callback);

	pio_enable_interrupt(CICLE_PIO, CICLE_IDX_MASK);

	pio_get_interrupt_status(CICLE_PIO);

	NVIC_EnableIRQ(CICLE_PIO_ID);
	NVIC_SetPriority(CICLE_PIO_ID, 4);
}

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

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource) {

  uint16_t pllPreScale = (int) (((float) 32768) / freqPrescale);
	
  rtt_sel_source(RTT, false);
  rtt_init(RTT, pllPreScale);
  
  if (rttIRQSource & RTT_MR_ALMIEN) {
	uint32_t ul_previous_time;
  	ul_previous_time = rtt_read_timer_value(RTT);
  	while (ul_previous_time == rtt_read_timer_value(RTT));
  	rtt_write_alarm_time(RTT, IrqNPulses+ul_previous_time);
  }

  /* config NVIC */
  NVIC_DisableIRQ(RTT_IRQn);
  NVIC_ClearPendingIRQ(RTT_IRQn);
  NVIC_SetPriority(RTT_IRQn, 4);
  NVIC_EnableIRQ(RTT_IRQn);

  /* Enable RTT interrupt */
  if (rttIRQSource & (RTT_MR_RTTINCIEN | RTT_MR_ALMIEN))
	rtt_enable_interrupt(RTT, rttIRQSource);
  else
	rtt_disable_interrupt(RTT, RTT_MR_RTTINCIEN | RTT_MR_ALMIEN);
		  
}

void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type) {
	/* Configura o PMC */
	pmc_enable_periph_clk(ID_RTC);

	/* Default RTC configuration, 24-hour mode */
	rtc_set_hour_mode(rtc, 0);

	/* Configura data e hora manualmente */
	rtc_set_date(rtc, t.year, t.month, t.day, t.week);
	rtc_set_time(rtc, t.hour, t.minute, t.second);

	/* Configure RTC interrupts */
	NVIC_DisableIRQ(id_rtc);
	NVIC_ClearPendingIRQ(id_rtc);
	NVIC_SetPriority(id_rtc, 4);
	NVIC_EnableIRQ(id_rtc);

	/* Ativa interrupcao via alarme */
	rtc_enable_interrupt(rtc,  irq_type);
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

	cicle_init();

	xSemaphoreRTC = xSemaphoreCreateBinary();

	xQueueScreens = xQueueCreate(32, sizeof(uint32_t));
	xQueueTime = xQueueCreate(32, sizeof(uint32_t));

	/* Create task to control oled */
	if (xTaskCreate(task_lcd, "LCD", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create lcd task\r\n");
	}

	if (xTaskCreate(task_rtc, "RTC", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create rtc task\r\n");
	}

	if (xTaskCreate(task_simulador, "SIMUL", TASK_SIMULATOR_STACK_SIZE, NULL, TASK_SIMULATOR_STACK_PRIORITY, NULL) != pdPASS) {
        printf("Failed to create lcd task\r\n");
    }

	if (xTaskCreate(task_speed, "speed", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL) != pdPASS) {
		printf("Failed to create speed task\r\n");
	}

	
	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1){ }
}
