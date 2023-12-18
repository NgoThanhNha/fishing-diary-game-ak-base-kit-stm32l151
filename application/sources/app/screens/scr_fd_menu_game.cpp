#include "scr_fd_menu_game.h"

/* How to add new items to the list items of menu screen
	1. Change the number of items by:  #define NUM_ITEM_MAX 6
	2. Add new characters to the array: menu_items_name[]
*/

#define NUM_ITEM_MAX 4
static void view_scr_menu_game();
static uint8_t cursor_select = 0;
static uint8_t buffer_view_items = 0;
static const char* menu_items_name[] = {
	"     Play Game",		
	"     Setting",
	"     Charts",
	"     Exit",
	"     Temp_1",
	"     Temp_2",
	"     Temp_3",
	"     Temp_n"
};

view_dynamic_t dyn_view_item_menu_game = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_menu_game
};

view_screen_t scr_menu_game = {
	&dyn_view_item_menu_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_menu_game(){

	view_render.clear();
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);

	/* load optional selections */
	switch (cursor_select){
	case 0:
		view_render.setTextColor(BLACK);
		view_render.fillRoundRect(0, 0, 128, 20, 5, WHITE);
		view_render.setCursor(0, 6);
		view_render.print(menu_items_name[buffer_view_items]);

		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 22, 128, 20, 5, WHITE);
		view_render.setCursor(0, 28);
		view_render.print(menu_items_name[buffer_view_items + 1]);

		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 44, 128, 20, 5, WHITE);
		view_render.setCursor(0, 50);
		view_render.print(menu_items_name[buffer_view_items + 2]);
		break;

	case 1:
		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 0, 128, 20, 5, WHITE);
		view_render.setCursor(0, 6);
		view_render.print(menu_items_name[buffer_view_items]);

		view_render.setTextColor(BLACK);
		view_render.fillRoundRect(0, 22, 128, 20, 5, WHITE);
		view_render.setCursor(0, 28);
		view_render.print(menu_items_name[buffer_view_items + 1]);

		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 44, 128, 20, 5, WHITE);
		view_render.setCursor(0, 50);
		view_render.print(menu_items_name[buffer_view_items + 2]);
		break;
	case 2:
		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 0, 128, 20, 5, WHITE);
		view_render.setCursor(0, 6);
		view_render.print(menu_items_name[buffer_view_items]);

		view_render.setTextColor(WHITE);
		view_render.drawRoundRect(0, 22, 128, 20, 5, WHITE);
		view_render.setCursor(0, 28);
		view_render.print(menu_items_name[buffer_view_items + 1]);

		view_render.setTextColor(BLACK);
		view_render.fillRoundRect(0, 44, 128, 20, 5, WHITE);
		view_render.setCursor(0, 50);
		view_render.print(menu_items_name[buffer_view_items + 2]);
		break;
	}

    /* update screen */
    view_render.update();
}

void scr_menu_game_handle(ak_msg_t* msg){
    switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
	}
		break;
	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		if(buffer_view_items == 0){
			switch (cursor_select){
			case 0:
				xprintf("Transition to playgame \n");
				SCREEN_TRAN(scr_fd_game_handle, &scr_fd_game_play);
				break;
			
			default:
				break;
			}
		}
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		//BUZZER_PlayTones(tones_3beep);
		if(cursor_select == 0){
			if(buffer_view_items > 0){
				buffer_view_items--;
			}
		}
		else{
			if(cursor_select > 0){
				cursor_select--;
			}
			
		}
		xprintf("cursor select: %d \n", cursor_select);
		xprintf("buffer view: %d \n", buffer_view_items);
		SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}
		break;
	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		//BUZZER_PlayTones(tones_3beep);
		cursor_select++;
		if(cursor_select > 2){
			buffer_view_items++;
			cursor_select = 2;
			if(buffer_view_items > (NUM_ITEM_MAX - 3)){
				buffer_view_items = (NUM_ITEM_MAX - 3);
			}
		}
		xprintf("cursor select: %d \n", cursor_select);
		xprintf("buffer view: %d \n", buffer_view_items);
		SCREEN_TRAN(scr_menu_game_handle, &scr_menu_game);
	}
		break;
    }
}