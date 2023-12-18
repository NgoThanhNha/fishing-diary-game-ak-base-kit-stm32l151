#ifndef __FD_GAME_BULLET_H__
#define __FD_GAME_BULLET_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

#include "buzzer.h"
#include "scr_fd_game_play.h"

/* bullet object defines */
#define MAX_NUM_BULLET                  (5)
#define MAX_POSITON_Y_AXIS              (0)
#define BULLET_Y_POSITON_ORIGIN         (50) 


typedef struct {
    bool visible;
    uint8_t x, y;
    bool shooted_effect;
} fd_game_bullet_t;

extern fd_game_bullet_t bullet[MAX_NUM_BULLET];
extern volatile uint8_t current_shooted_pos_x, current_shooted_pos_y;

#endif //__FD_GAME_BULLET_H__