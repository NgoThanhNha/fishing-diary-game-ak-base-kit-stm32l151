#include "fd_game_gun.h"


fd_game_gun_t gun;
static uint8_t gun_x_position = GUN_X_ORIGIN;

/* functional gun object */
void fd_game_gun_setup(void){
    gun.x = GUN_X_ORIGIN;
    gun.y = GUN_Y_ORIGIN;
}

void fd_game_gun_left(void){
    if(gun_x_position <= 3){
        gun_x_position = 3;
    }
    else{
        gun_x_position = gun_x_position - 10;
    }
}
void fd_game_gun_right(void){
    if(gun_x_position >= 85){
        gun_x_position = 85;
    }
    else{
        gun_x_position = gun_x_position + 10;
    }
}

void fd_game_gun_update(void){
    gun.x = gun_x_position;
}


void fd_game_gun_handle(ak_msg_t* msg) {
    switch (msg->sig) {
        case FD_GAME_GUN_SETUP: {
            fd_game_gun_setup();
            xprintf("x positon: %d", gun_x_position);
            
        }
            break;
        case FD_GAME_GUN_UPDATE: {
            fd_game_gun_update();
            
            break;
        case FD_GAME_GUN_LEFT: {
            fd_game_gun_left();
            xprintf("x positon: %d", gun_x_position);
            
        }
            break;
        case FD_GAME_GUN_RIGHT: {
            fd_game_gun_right();
            xprintf("x positon: %d", gun_x_position);
            
        }
            break;
        }
    }
}