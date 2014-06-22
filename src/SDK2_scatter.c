#include <pebble.h>


#define INVERTED false
#define TAP_SERVICE true


#define ANIMATION_DURATION 200
#define ANIMATION_DELAY 400
#define LAYERS 14
#define TIME_DIGITS 4


Window *window;

#if INVERTED
InverterLayer *inverter_layer;
#endif

Layer *colon_layer;
PropertyAnimation *colon_animation_in;

typedef struct {
	int x;
	int y;
	int w;
	int h;
} DigitComponent;

DigitComponent digit_components[11][LAYERS] = {
	{	//0
		{	4,	0,	22,	8},
		{	4,	30,	22,	8},
		{	0,	4,	8,	30},
		{	22,	4,	8,	30},
		{	5,	1,	1,	1},
		{	2,	1,	2,	36},
		{	26,	1,	2,	36},
		{	1,	2,	28,	2},
		{	1,	34,	28,	2},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//1
		{	22,	0,	4,	38},
		{	22,	1,	6,	36},
		{	22,	2,	7,	34},
		{	22,	4,	8,	30},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//2
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	0,	30,	30,	4},
		{	1,	30,	28,	6},
		{	2,	30,	26,	7},
		{	4,	30,	22,	8},
		{	4,	15,	26,	4},
		{	2,	16,	27,	5},
		{	1,	17,	27,	5},
		{	0,	19,	26,	4},
		{	22,	4,	8,	15},
		{	0,	19,	8,	15}
	},
	{	//3
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	0,	30,	30,	4},
		{	1,	30,	28,	6},
		{	2,	30,	26,	7},
		{	4,	30,	22,	8},
		{	13,	15,	17,	8},
		{	11,	16,	19,	6},
		{	10,	17,	20,	4},
		{	22,	4,	8,	30},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//4
		{	4,	0,	4,	23},
		{	2,	1,	6,	21},
		{	1,	2,	7,	19},
		{	0,	4,	8,	15},
		{	5,	15,	20,	8},
		{	22,	0,	4,	38},
		{	22,	1,	6,	36},
		{	22,	2,	7,	34},
		{	22,	4,	8,	30},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//5
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	0,	30,	30,	4},
		{	1,	30,	28,	6},
		{	2,	30,	26,	7},
		{	4,	30,	22,	8},
		{	0,	15,	26,	4},
		{	1,	16,	27,	5},
		{	2,	17,	27,	5},
		{	4,	19,	26,	4},
		{	0,	4,	8,	15},
		{	22,	19,	8,	15}
	},
	{	//6
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	0,	30,	30,	4},
		{	1,	30,	28,	6},
		{	2,	30,	26,	7},
		{	4,	30,	22,	8},
		{	0,	15,	26,	8},
		{	0,	16,	28,	7},
		{	0,	17,	29,	6},
		{	0,	19,	30,	4},
		{	0,	4,	8,	30},
		{	22,	19,	8,	15}
	},
	{	//7
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	22,	0,	4,	38},
		{	22,	1,	6,	36},
		{	22,	2,	7,	34},
		{	22,	4,	8,	30},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//8
		{	4,	0,	22,	8},
		{	4,	30,	22,	8},
		{	0,	4,	8,	30},
		{	22,	4,	8,	30},
		{	8,	15,	14,	8},
		{	2,	1,	2,	36},
		{	26,	1,	2,	36},
		{	1,	2,	28,	2},
		{	1,	34,	28,	2},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	},
	{	//9
		{	4,	0,	22,	8},
		{	2,	1,	26,	7},
		{	1,	2,	28,	6},
		{	0,	4,	30,	4},
		{	0,	30,	30,	4},
		{	1,	30,	28,	6},
		{	2,	30,	26,	7},
		{	4,	30,	22,	8},
		{	0,	15,	30,	4},
		{	1,	15,	29,	6},
		{	2,	15,	28,	7},
		{	4,	15,	26,	8},
		{	22,	4,	8,	30},
		{	0,	4,	8,	15}
	},
	{	//Hidden
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0},
		{	0,	0,	0,	0}
	}
};

typedef struct {
	int x;
	int y;
	Layer *digit_layers[LAYERS];
	PropertyAnimation *animations_out[LAYERS];
	PropertyAnimation *animations_in[LAYERS];
} TimeDigit;

TimeDigit time_digits[TIME_DIGITS];

long random_seed;

/**/


void digit_layer_update_callback(Layer *layer, GContext* ctx) {
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}


void colon_layer_update_callback(Layer *layer, GContext* ctx) {
	(void)layer;

	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(0, 0, 4, 4), 1, GCornersAll);
	graphics_fill_rect(ctx, GRect(0, 14, 4, 4), 1, GCornersAll);
}


int random(int max)
{
	random_seed = (((random_seed * 214013L + 2531011L) >> 16) & 32767);
	return ((random_seed % max) + 0);
}


void animation_stopped(Animation *animation, bool finished, void *property_animation) {
	if(finished){property_animation_destroy(property_animation);}
}


void trigger_animation(TimeDigit *time_digit, int digit, int delay) {
	GRect random_rect;
	GRect home_rect;
	int layer;

	for(layer = 0; layer < LAYERS; layer++) {
		random_rect = GRect(random(142), random(166), 2, 2); 	// 144 - 2, 168 - 2
		home_rect = GRect(time_digit->x + digit_components[digit][layer].x, time_digit->y + digit_components[digit][layer].y, digit_components[digit][layer].w, digit_components[digit][layer].h);

		time_digit->animations_out[layer] = property_animation_create_layer_frame(time_digit->digit_layers[layer], NULL, &random_rect);
		animation_set_curve(&time_digit->animations_out[layer]->animation, AnimationCurveEaseOut);
		animation_set_delay(&time_digit->animations_out[layer]->animation, 0 + delay);
		animation_set_duration(&time_digit->animations_out[layer]->animation, ANIMATION_DURATION);
		animation_set_handlers(&time_digit->animations_out[layer]->animation, 
														(AnimationHandlers) {
															.started = NULL,
															.stopped = (AnimationStoppedHandler) animation_stopped,
														},
														time_digit->animations_out[layer]);
		animation_schedule(&time_digit->animations_out[layer]->animation);

		time_digit->animations_in[layer] = property_animation_create_layer_frame(time_digit->digit_layers[layer], &random_rect, &home_rect);
		animation_set_curve(&time_digit->animations_in[layer]->animation, AnimationCurveEaseIn);
		animation_set_delay(&time_digit->animations_in[layer]->animation, ANIMATION_DELAY + delay);
		animation_set_duration(&time_digit->animations_in[layer]->animation, ANIMATION_DURATION);
		animation_set_handlers(&time_digit->animations_in[layer]->animation,
														(AnimationHandlers) {
															.started = NULL,
															.stopped = (AnimationStoppedHandler) animation_stopped,
														},
														time_digit->animations_in[layer]);
		animation_schedule(&time_digit->animations_in[layer]->animation);	
	}
}


void handle_tick(struct tm *tick_time, TimeUnits units_changed) {
	int tm_hour;
	int tm_min;
	int hour_tens_digit;
	int hour_ones_digit;
	int minute_tens_digit;
	int minute_ones_digit;

	/**/

	// Set local time variables and optionally adjust for 12h style
	tm_hour = tick_time->tm_hour;
	tm_min = tick_time->tm_min;

	if(!clock_is_24h_style()) {
		tm_hour = tm_hour % 12;
		if(tm_hour == 0) { tm_hour = 12; }
	}

	/**/

	// Compute digit values
	hour_tens_digit = (tm_hour) / 10;
	hour_ones_digit = (tm_hour) % 10;
	minute_tens_digit = (tm_min) / 10;
	minute_ones_digit = (tm_min) % 10;

	if(!clock_is_24h_style() && (hour_tens_digit == 0)) {
		hour_tens_digit = 10; // Hide the digit
	}

	/**/

	if ((units_changed & HOUR_UNIT) || (units_changed & DAY_UNIT)) {
		if((hour_ones_digit == 0) || (units_changed & DAY_UNIT)) { trigger_animation(&time_digits[0], hour_tens_digit, 0); }
		trigger_animation(&time_digits[1], hour_ones_digit, 0);
	}

	if ((units_changed & MINUTE_UNIT) || (units_changed & DAY_UNIT)) {
		if((minute_ones_digit == 0) || (units_changed & DAY_UNIT)) { trigger_animation(&time_digits[2], minute_tens_digit, 0); }
		trigger_animation(&time_digits[3], minute_ones_digit, 0);
	}
}


#if TAP_SERVICE
void handle_tap(AccelAxisType axis, int32_t direction) {
	time_t now;
	struct tm *tick_time;

	light_enable_interaction();

	now = time(NULL);
	tick_time = localtime(&now);
	handle_tick(tick_time, DAY_UNIT);  // Passing DAY_UNIT forces complete redraw
}
#endif


void handle_init(void) {
	int layer;
	int digit;

	time_t now;
	struct tm *tick_time;

	GRect to_rect;

	/**/

	window = window_create();
	window_stack_push(window, true /* Animated */);
	window_set_background_color(window, GColorBlack);

	time_digits[0].x = 3; time_digits[0].y = 65;
	time_digits[1].x = 38; time_digits[1].y = 65;
	time_digits[2].x = 76; time_digits[2].y = 65;
	time_digits[3].x = 111; time_digits[3].y = 65;

	colon_layer = layer_create(GRect(72, 84, 0, 0));
	layer_set_update_proc(colon_layer, colon_layer_update_callback);
	layer_add_child(window_get_root_layer(window), colon_layer);

	for(digit = 0; digit < TIME_DIGITS; digit++) {
		for(layer = 0; layer < LAYERS; layer++) {
			time_digits[digit].digit_layers[layer] = layer_create(GRect(72, 84, 0, 0));
			layer_set_update_proc(time_digits[digit].digit_layers[layer], digit_layer_update_callback);
			layer_add_child(window_get_root_layer(window), time_digits[digit].digit_layers[layer]);			
		}
	}

	#if INVERTED
	// The inverter layer (probably) has to be the last layer added to the window
	inverter_layer = inverter_layer_create(layer_get_frame(window_get_root_layer(window)));
	layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter_layer));
	#endif

	//force initial render
	now = time(NULL);
	tick_time = localtime(&now);
	handle_tick(tick_time, DAY_UNIT);  // Passing DAY_UNIT forces complete redraw

	to_rect = GRect(70, 75, 4, 18);
	colon_animation_in = property_animation_create_layer_frame(colon_layer, NULL, &to_rect);
	animation_set_curve(&colon_animation_in->animation, AnimationCurveEaseOut);
	animation_set_delay(&colon_animation_in->animation, ANIMATION_DELAY + 500);
	animation_set_duration(&colon_animation_in->animation, ANIMATION_DURATION);
	animation_schedule(&colon_animation_in->animation);

	tick_timer_service_subscribe(MINUTE_UNIT, handle_tick);
	#if TAP_SERVICE
	accel_tap_service_subscribe(handle_tap);
	#endif
}


void handle_deinit(void)
{
	tick_timer_service_unsubscribe();
	#if TAP_SERVICE
	accel_tap_service_unsubscribe();
	#endif
	animation_unschedule_all();

	#if INVERTED
	inverter_layer_destroy(inverter_layer);
	#endif

	int digit;
	int layer;
	for(digit = 0; digit < TIME_DIGITS; digit++) {
		for(layer = 0; layer < LAYERS; layer++) {
			layer_destroy(time_digits[digit].digit_layers[layer]);
		}
	}

	layer_destroy(colon_layer);
	window_destroy(window);
}


int main(void) {
	handle_init();

	app_event_loop();
  
	handle_deinit();
}
