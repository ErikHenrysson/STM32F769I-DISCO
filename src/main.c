/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */


#include "stm32f7xx.h"
#include "stm32f769i_discovery.h"
#include "hal_stm_lvgl/tft/tft.h"
#include "hal_stm_lvgl/touchpad/touchpad.h"
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
#include <stdio.h>
#include <math.h>
#include "my_lvgl.h"

static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);


//extern lv_img_dsc_t Small_scream;
//extern lv_img_dsc_t brain_art_min;



int button_presses = 0;


static void button_event_handler(lv_event_t * e){
	lv_event_code_t code = lv_event_get_code(e);

	    if(code == LV_EVENT_CLICKED) {
	        button_presses++;
	    }
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_current_target(e);

    if(code == LV_EVENT_VALUE_CHANGED) {
        lv_calendar_date_t date;
        if(lv_calendar_get_pressed_date(obj, &date)) {
            LV_LOG_USER("Clicked date: %02d.%02d.%d", date.day, date.month, date.year);
        }
    }
}

void calendar(void){
    lv_obj_t  * calendar = lv_calendar_create(lv_screen_active());
    lv_obj_set_size(calendar, 185, 230);
    lv_obj_align(calendar, LV_ALIGN_BOTTOM_LEFT, 30, -30);
    lv_obj_add_event_cb(calendar, event_handler, LV_EVENT_ALL, NULL);

    lv_calendar_set_today_date(calendar, 2025, 02, 17);
    lv_calendar_set_showed_date(calendar, 2025, 2);

    /*Highlight a few days*/
    static lv_calendar_date_t highlighted_days[3];       /*Only its pointer will be saved so should be static*/
    highlighted_days[0].year = 2025;
    highlighted_days[0].month = 02;
    highlighted_days[0].day = 17;

    highlighted_days[1].year = 2025;
    highlighted_days[1].month = 02;
    highlighted_days[1].day = 18;

    highlighted_days[2].year = 2025;
    highlighted_days[2].month = 02;
    highlighted_days[2].day = 22;

    lv_calendar_set_highlighted_dates(calendar, highlighted_days, 3);

#if LV_USE_CALENDAR_HEADER_DROPDOWN
    lv_calendar_header_dropdown_create(calendar);
#elif LV_USE_CALENDAR_HEADER_ARROW
    lv_calendar_header_arrow_create(calendar);
#endif
}


int main(void) {

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	       - Configure the Flash prefetch
	       - Systick timer is configured by default as source of time base, but user
	         can eventually implement his proper time base source (a general purpose
	         timer for example or other time source), keeping in mind that Time base
	         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
	         handled in milliseconds basis.
	       - Set NVIC Group Priority to 4
	       - Low Level Initialization
	 */
	HAL_Init();

	SystemClock_Config();

	lv_init();

	tft_init();
	touchpad_init();

	//lv_demo_widgets();
		//lv_demo_scroll();
		//lv_demo_stress();

		//Get current current_screen
		lv_obj_t * current_screen = lv_screen_active();
		lv_obj_set_style_bg_color(current_screen, lv_palette_main(LV_PALETTE_GREY), 0);

		// Slider for resizing the circle
		lv_obj_t * value_slider = createSlider(current_screen, LV_ALIGN_OUT_LEFT_TOP, 34, 30, 220, 40);

		// Slider value text field
		lv_obj_t * text_field = createLabel(current_screen, LV_ALIGN_OUT_LEFT_TOP, 30, 100, 180, 120);

		//Circle to be resized by the slider
		lv_obj_t * circle = createCircle(current_screen, 50);

		// Black and white image to display
		LV_IMG_DECLARE(brain_art_min);

		LV_IMG_DECLARE(Small_scream);

		lv_obj_t * black_n_white_img = myCreateImg(current_screen, LV_ALIGN_CENTER, 0, 120, 80, 80, &Small_scream);

		// Color image to display
		lv_obj_t * color_img = myCreateImg(current_screen, LV_ALIGN_CENTER, 250, 120, 150, 150, &brain_art_min);



		// THEME TEST
		// Försöker just nu få knappen i mittne att ärva stilen från skärmen (grad color...)
		static lv_style_t style;
		lv_style_init(&style);
		lv_style_set_radius(&style, 5);
		lv_style_set_bg_color(&style, lv_palette_main(LV_PALETTE_RED));



		lv_style_set_bg_opa(&style, LV_OPA_COVER);
		static lv_grad_dsc_t grad;
		grad.dir = LV_GRAD_DIR_HOR;
		grad.stops_count = 3;
		grad.stops[0].color = lv_color_black();
		grad.stops[0].opa = LV_OPA_COVER;
		grad.stops[1].color = lv_palette_main(LV_PALETTE_RED);
		grad.stops[1].opa = LV_OPA_COVER;
		grad.stops[2].color = lv_palette_main(LV_PALETTE_ORANGE);
		grad.stops[2].opa = LV_OPA_COVER;

		grad.stops[0].frac  = 0;
		grad.stops[1].frac  = 85;
		grad.stops[2].frac  = 170;

		//grad.stops[2].frac  = 255;
		lv_style_set_bg_grad(&style, &grad);
		lv_obj_add_style(current_screen, &style, 0);



		lv_obj_t * test = lv_button_create(current_screen);

		lv_obj_set_size(test, 120, 120);
		lv_obj_align(test, LV_ALIGN_CENTER, 0, 0);

		// THEME TEST



		// Button with text
		lv_obj_t * button = lv_button_create(current_screen);
		lv_obj_add_event_cb(button, button_event_handler, LV_EVENT_ALL, NULL);
		lv_obj_set_size(button, 140, 120);
		lv_obj_align(button, LV_ALIGN_TOP_RIGHT, -120, 60);
		lv_obj_t * button_label = createLabel(button, LV_ALIGN_CENTER, 0, -15, 110, 20);
		lv_obj_set_style_text_align(button_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_label_set_text(button_label, "Press me");

		// Counter on button
		lv_obj_remove_flag(button, LV_OBJ_FLAG_PRESS_LOCK);
		lv_obj_t * button_counter = createLabel(button, LV_ALIGN_CENTER, 0, 30, 40, 20);
		lv_obj_set_style_outline_width(button_counter, 3, LV_PART_MAIN);
		lv_obj_set_style_outline_color(button_counter, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
		lv_obj_set_style_text_align(button_counter, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
		lv_obj_set_style_bg_color(button, lv_color_black(), LV_PART_MAIN);



		calendar();





	char str[60];
	char str1[60];
	//lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
	bool circle_exists = true;
	while(1) {
		lv_task_handler();
		HAL_Delay(1);

		sprintf(str, "%d", button_presses);
		lv_label_set_text(button_counter, str);

		int32_t slider_val = lv_slider_get_value(value_slider);
		// Convert slider value text
		sprintf(str, "Slider value: %d", slider_val);
		lv_label_set_text(text_field, str);
		// Resize the circle depending on the slider value
		if (circle_exists){
			lv_obj_set_size(circle, slider_val, slider_val);

		}
		if (100 == slider_val && circle_exists){
			lv_obj_delete(circle);
			circle_exists = false;
		}
		if (0 == slider_val && !circle_exists){
			circle = createCircle(current_screen, 0);
			circle_exists = true;
		}


	}
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 216 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}


/**
* @brief  CPU L1-Cache enable.
* @param  None
* @retval None
*/
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
