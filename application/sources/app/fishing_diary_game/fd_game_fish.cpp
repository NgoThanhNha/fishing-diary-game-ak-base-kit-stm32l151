#include "fd_game_fish.h"

fd_game_fish_t fish[MAX_NUM_FISH];

/* functional fish object */
uint32_t fd_game_random(uint32_t a, uint32_t b){
    /* random number from a to b */
    return (rand() % ((b - a + 1) + a));
}


void fd_game_fish_setup(void){
    for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
        fish[i].visible = BLACK;
        fish[i].action_image = fd_game_random(1,4);
        fish[i].x = fd_game_random(1, 3) * 2;
        fish[i].y = FISH_Y_POSITION_ORIGIN + i*10;
        fish[i].shooted = 0;
    }
}

void fd_game_fish_update(void){                                
    for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
        fish[i].x = fish[i].x + 1;
        if(fish[i].x == MAX_POSITION_X_AXIS){
            fish[i].visible = BLACK;
            fish[i].x = (rand() % 3 + 1) * 5;
        }
    }
}

void fd_game_fish_motion(void){
    for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
        if((fish[i].visible == BLACK)){
            fish[i].visible = WHITE;
            break;
        }
    }
}

void fd_game_fish_reset(void){
    for(uint8_t i = 0; i < MAX_NUM_FISH; i++){
        fish[i].visible = BLACK;
        fish[i].x = FISH_X_POSITION_ORIGIN;
        fish[i].y = FISH_Y_POSITION_ORIGIN;
    }
}

void fd_game_fish_handle(ak_msg_t* msg){
    switch (msg->sig) {
    case FD_GAME_FISH_SETUP: {
        APP_DBG_SIG("FD_GAME_FISH_SETUP\n");
        fd_game_fish_setup();
    }
        break;
    case FD_GAME_FISH_UPDATE: {
        APP_DBG_SIG("FD_GAME_FISH_UPDATE\n");
        fd_game_fish_update();
    }
        break;
    case FD_GAME_FISH_MOTION: {
        APP_DBG_SIG("FD_GAME_FISH_MOTION\n");
        fd_game_fish_motion();
    }
        break;
    case FD_GAME_FISH_RESET: {
        APP_DBG_SIG("FD_GAME_FISH_RESET\n");
        fd_game_fish_reset();
    }
        break;
    }


}
