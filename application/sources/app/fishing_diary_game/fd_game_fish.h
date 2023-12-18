#ifndef __FD_GAME_FISH_H__
#define __FD_GAME_FISH_H__

#include <stdio.h>
#include <stdlib.h>

#include "fsm.h"
#include "port.h"
#include "message.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"
#include "scr_fd_game_play.h" 

/* fish object defines */
#define MAX_NUM_FISH            (3)
#define MAX_POSITION_X_AXIS     (128)
#define FISH_X_POSITION_ORIGIN  (0)
#define FISH_Y_POSITION_ORIGIN  (10)

typedef struct {
    bool visible;
    uint8_t x, y;
    uint8_t action_image;
    uint8_t shooted;
} fd_game_fish_t;

extern fd_game_fish_t fish[MAX_NUM_FISH];
extern uint32_t fd_game_random(uint32_t a, uint32_t b);

#endif //__FD_GAME_FISH_H__