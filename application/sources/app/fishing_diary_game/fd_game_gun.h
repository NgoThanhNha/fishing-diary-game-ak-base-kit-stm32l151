#ifndef __AIR_GAME_AIRCRAFT_H__
#define __AIR_GAME_AIRCRAFT_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "scr_fd_game_play.h"

/* gun object defines */
#define GUN_X_ORIGIN            (5)
#define GUN_Y_ORIGIN            (49)

typedef struct {
    bool visible;
    uint32_t x, y;
} fd_game_gun_t;

extern fd_game_gun_t gun;

#endif //__AIR_GAME_AIRCRAFT_H__