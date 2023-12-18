#ifndef __SCREENS_H__
#define __SCREENS_H__

#include "scr_fd_game_play.h"
#include "scr_fd_menu_game.h"

/* screen menu game */
extern view_dynamic_t dyn_view_item_menu_game;
extern view_screen_t scr_menu_game;
extern void scr_menu_game_handle(ak_msg_t* msg);

/* screen game play */
extern uint8_t fd_game_state;
extern view_dynamic_t dyn_view_item_aircraft_game;
extern view_screen_t scr_aircraft_game;
extern void scr_aircraft_game_handle(ak_msg_t* msg);

#endif //__SCREENS_H__