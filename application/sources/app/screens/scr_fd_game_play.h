#ifndef __SCR_AIRCRAFT_GAME_PLAY_H__
#define __SCR_AIRCRAFT_GAME_PLAY_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "buzzer.h"

/* fishing game includes */
#include "fd_game_gun.h"
#include "fd_game_bullet.h"
#include "fd_game_fish.h"


#include "screens_bitmap_object_game.h"
#include "screens.h"

#define GAME_OFF    0
#define GAME_PLAY   1

extern uint8_t fd_game_state;

extern view_dynamic_t dyn_view_item_fd_game_play;
extern view_screen_t scr_fd_game_play;
extern volatile uint8_t score_game_play;
extern volatile uint8_t current_num_bullet_game_play;

extern void scr_fd_game_handle(ak_msg_t* msg);

#endif //__SCR_AIRCRAFT_GAME_PLAY_H__