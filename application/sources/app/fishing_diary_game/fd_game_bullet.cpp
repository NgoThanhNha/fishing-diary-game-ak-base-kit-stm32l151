#include "fd_game_bullet.h"

#include "fd_game_gun.h"
#include "fd_game_fish.h"
#include "scr_fd_game_play.h"

fd_game_bullet_t bullet[MAX_NUM_BULLET];
uint8_t current_num_bullet = MAX_NUM_BULLET;
volatile uint8_t current_shooted_pos_x, current_shooted_pos_y;

void fd_game_bullet_setup(void){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        bullet[i].x = GUN_X_ORIGIN + 5;
        bullet[i].y = BULLET_Y_POSITON_ORIGIN;
        bullet[i].visible = BLACK;
        bullet[i].shooted_effect = 0;
    }
}

void fd_game_bullet_update(void){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        if(bullet[i].visible == WHITE){
            bullet[i].y = bullet[i].y - 5;
            if(bullet[i].y == MAX_POSITON_Y_AXIS){
                bullet[i].visible = BLACK;
                bullet[i].y = BULLET_Y_POSITON_ORIGIN;
                current_num_bullet++;
                
            }
        }
    }
}

void fd_game_bullet_shoot(void){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        if((bullet[i].visible == BLACK) && (current_num_bullet != 0)){
            current_num_bullet--;
            if(current_num_bullet_game_play == 0){
                current_num_bullet_game_play = 0;
            }
            else{
                current_num_bullet_game_play--;
            }
            
            bullet[i].visible = WHITE;
            bullet[i].x = gun.x + 5;
            break; 
        }
        else if(current_num_bullet == 0){
            /* do nothing */
        }
        
    }
}

void check_collision(void){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        if(bullet[i].visible == WHITE){
            for(uint8_t j = 0; j < MAX_NUM_FISH; j++){
                if(bullet[i].y < (fish[j].y + 9)){
                    if(bullet[i].x > (fish[j].x + 1)){
                        if(bullet[i].x < (fish[j].x + 14)){
                            current_shooted_pos_x = bullet[i].x;
                            current_shooted_pos_y = bullet[i].y;
                            bullet[i].visible = BLACK;
                            bullet[i].y = BULLET_Y_POSITON_ORIGIN;
                            bullet[i].shooted_effect = 1;
                            current_num_bullet++;
                            fish[j].shooted++;
                            if(fish[j].shooted == 3){
                                fish[j].shooted = 0;
                                fish[j].visible = BLACK;
                                fish[j].x = fd_game_random(1, 3) * 5;
                                score_game_play++;
                                current_num_bullet_game_play++;  
                            }
                        }
                    }
                }
            }
        }
    }
}

void fd_game_bullet_reset(void){
    for(uint8_t i = 0; i < MAX_NUM_BULLET; i++){
        bullet[i].x = GUN_X_ORIGIN + 5;
        bullet[i].y = BULLET_Y_POSITON_ORIGIN;
        bullet[i].visible = BLACK;
    }
}

void fd_game_bullet_handle(ak_msg_t* msg){
    switch (msg->sig) {
    case FD_GAME_BULLET_SETUP: {
        APP_DBG_SIG("FD_GAME_BULLET_SETUP\n");
        fd_game_bullet_setup();
    }
        break;

    case FD_GAME_BULLET_UPDATE: {
        APP_DBG_SIG("FD_GAME_BULLET_RUN\n");
        fd_game_bullet_update();
        check_collision();
    }
        break;
    case FD_GAME_BULLET_SHOOT: {
        APP_DBG_SIG("FD_GAME_BULLET_SHOOT\n");
        fd_game_bullet_shoot();
    }
        break;
    case FD_GAME_BULLET_RESET: {
        APP_DBG_SIG("FD_GAME_BULLET_SHOOT\n");
        fd_game_bullet_reset();
    }
        break;

}
}