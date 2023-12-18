#include "scr_fd_game_play.h"

uint8_t fd_game_state = GAME_OFF;
volatile uint8_t count_trans_action_image = 0;
volatile uint8_t score_game_play = 0;
volatile uint8_t current_num_bullet_game_play = MAX_NUM_BULLET;

static void fd_game_frame_display();
static void fd_game_gun_display();
static void fd_game_bullet_display();
static void fd_game_fish_display();
static void view_scr_fd_game_play();

view_dynamic_t dyn_view_item_fd_game_play = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_fd_game_play
};

view_screen_t scr_fd_game_play = {
	&dyn_view_item_fd_game_play,
	NULL,
	NULL,

	.focus_item = 0,
};

/* display objects */
void fd_game_frame_display() {
	view_render.fillRect(100, 0, 28, 64, 0);
	view_render.drawRect(0, 0, 128, 64, 1);
	view_render.drawFastVLine(100, 0, 64, 1);

	/* draw score frame */
	view_render.drawBitmap(107, 4, fish_bitmap_action_center, 14, 9, 1);\
	view_render.setTextSize(1);
	view_render.setTextColor(1);
	if(score_game_play < 10){
		view_render.setCursor(111, 17);
		view_render.print(score_game_play);
	}
	else if(score_game_play >= 10){
		view_render.setCursor(108, 17);
		view_render.print(score_game_play);
	}

	/* draw bullet frame */
	view_render.drawCircle(113, 42, 3, 1);
	if(current_num_bullet_game_play < 10){
		view_render.setCursor(111, 50);
		view_render.print(current_num_bullet_game_play);
	}
	else if(current_num_bullet_game_play >= 10){
		view_render.setCursor(108, 50);
		view_render.print(current_num_bullet_game_play);
	}

	/* draw temp */
	if(current_num_bullet_game_play == 0){
		/*
		view_render.setTextSize(2);
		view_render.setTextColor(1);
		view_render.setCursor(5, 20);
		view_render.print("Game Over!");
		*/
	}


}

void fd_game_gun_display(){
    view_render.drawBitmap(gun.x, gun.y, gun_bitmap_I, 11, 13, 1);
}

void fd_game_bullet_display(){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        if(bullet[i].visible == WHITE){
			view_render.drawCircle(bullet[i].x, bullet[i].y, 2, 1);
        }
		if(bullet[i].shooted_effect == 1){
			view_render.drawBitmap(current_shooted_pos_x, current_shooted_pos_y, shooted_bitmap, 7, 7, 1);
			bullet[i].shooted_effect = 0;
		}
    }
}

void fd_game_fish_display(){
	for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
		if(fish[i].visible == WHITE){
			if(fish[i].action_image == 1){
				view_render.drawBitmap(fish[i].x, fish[i].y, fish_bitmap_action_I, 14, 9, 1);
			}
			else if (fish[i].action_image == 2){
				view_render.drawBitmap(fish[i].x, fish[i].y, fish_bitmap_action_center, 14, 9, 1);
			}
			else if (fish[i].action_image == 3){
				view_render.drawBitmap(fish[i].x, fish[i].y, fish_bitmap_action_II, 14, 9, 1);
			}
			else if (fish[i].action_image == 4){
				view_render.drawBitmap(fish[i].x, fish[i].y, fish_bitmap_action_center, 14, 9, 1);
			}
		}
	}
}

void view_scr_fd_game_play(){
	fd_game_gun_display();
	fd_game_bullet_display();
	fd_game_fish_display();
	fd_game_frame_display();
}

void fd_game_time_tick_setup() {
	timer_set(AC_TASK_DISPLAY_ID, FD_GAME_TIME_TICK, FD_GAME_TIME_TICK_INTERVAL, TIMER_PERIODIC);
}

void scr_fd_game_handle(ak_msg_t* msg){
    switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		
		task_post_pure_msg(FD_GAME_GUN_ID, FD_GAME_GUN_SETUP);
		task_post_pure_msg(FD_GAME_BULLET_ID, FD_GAME_BULLET_SETUP);
		task_post_pure_msg(FD_GAME_FISH_ID, FD_GAME_FISH_SETUP);

        fd_game_time_tick_setup();
		fd_game_state = GAME_PLAY;
	}
		break;
    case FD_GAME_TIME_TICK: {
		//APP_DBG_SIG("FD_GAME_TIME_TICK\n");
        task_post_pure_msg(FD_GAME_GUN_ID, FD_GAME_GUN_UPDATE);
		task_post_pure_msg(FD_GAME_BULLET_ID, FD_GAME_BULLET_UPDATE);
        task_post_pure_msg(FD_GAME_FISH_ID, FD_GAME_FISH_UPDATE);
		task_post_pure_msg(FD_GAME_FISH_ID, FD_GAME_FISH_MOTION);
		count_trans_action_image++;
		if(count_trans_action_image == 2){
			count_trans_action_image = 0;
			for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
				fish[i].action_image++;
				if(fish[i].action_image > 4){
					fish[i].action_image = 1;
				}
			}
		}
	}
		break;
    
    }
}
