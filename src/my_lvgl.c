

#include "lvgl/lvgl.h"


	lv_obj_t* createSlider(lv_obj_t *parent, lv_align_t align, int32_t x_ofs, int32_t y_ofs, int width, int height){
		//Create a slider
		lv_obj_t * value_slider = lv_slider_create(parent);
		lv_obj_align(value_slider, align, x_ofs, y_ofs);
		lv_obj_set_size(value_slider, width, height);
		lv_slider_set_value(value_slider, 0, LV_ANIM_OFF);
		lv_obj_set_style_bg_color(value_slider, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
		lv_obj_set_style_bg_color(value_slider, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
		lv_obj_set_style_bg_color(value_slider, lv_color_black(), LV_PART_KNOB);
		return value_slider;
	}


	lv_obj_t *createLabel(lv_obj_t *parent, lv_align_t align, int32_t x_ofs, int32_t y_ofs, int width, int height){

		lv_obj_t *text_field = lv_label_create(parent);
		//lv_label_set_text(text_field, "Value: " );
		lv_obj_align(text_field, align,  x_ofs, y_ofs);
		lv_obj_set_size(text_field, width, height);
		lv_obj_set_style_text_font(text_field, &lv_font_montserrat_22, 0);
		return text_field;
	}


	lv_obj_t *createCircle(lv_obj_t *parent, int width){
		lv_obj_t *circle = lv_obj_create(parent);
		lv_obj_set_size(circle, width, width);
		lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
		lv_obj_set_style_bg_color(circle, lv_palette_main(LV_PALETTE_DEEP_ORANGE),	0);
		lv_obj_center(circle);
		return circle;

	}
	/*


	lv_obj_t * img1_obj = lv_img_create(current_screen);
	lv_img_set_src(img1_obj, &brain_art_min);
	lv_obj_align(img1_obj, LV_ALIGN_LEFT_MID, 10, 0);

	lv_obj_t * img2_obj = lv_img_create(current_screen);
	lv_img_set_src(img2_obj, &Small_scream);
	lv_obj_align(img2_obj, LV_ALIGN_RIGHT_MID, -10, 0);


	*/

	lv_obj_t *myCreateImg(lv_obj_t *parent, lv_align_t align, int32_t x_ofs, int32_t y_ofs, int width, int height, const lv_img_dsc_t * img){
		lv_obj_t *myImg = lv_image_create(parent);
		lv_img_set_src(myImg, img);
		lv_obj_align(myImg, align, x_ofs, y_ofs);
		//lv_obj_set_size(myImg, width, height);

		return myImg;
	}


/*

	//Add an image to the screen
	lv_obj_t *img = lv_image_create(current_screen);
	lv_obj_align(img, LV_ALIGN_CENTER, 0, 120);
	lv_obj_set_size(img, 80, 80);
	lv_img_set_src(img, &Small_scream);

*/
