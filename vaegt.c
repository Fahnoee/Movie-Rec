#include <stdlib.h>
#include <stdio.h>
#include "main.c"

#define STREAM_SERVICE_COUNT 11
#define SETTING_COUNT 4
#define ARRAY_MENU_LENGTH 4
#define GENRE_COUNT 20
#define MAX_MOVIES 395
#define MAX_GENRES 20
#define MAX_SERVICES 11
#define DEBUG 0
#define ADDITIONAL_OFFSET 1

void subtract_weight(struct movie movie, setting *config);
void add_weight(struct movie movie, setting *config);


void weight_genre(struct movie movie, /*struct*/ setting *config)
{
    int user_input = 2;
    do{
    printf("Did you enjoy this movie?\n");
    printf("Type '1' for yes, '-1' for no and '0' for don'\n");
    user_input = scanf_for_int();
    }
    while(user_input < -1 && user_input > 1);

    if(user_input == -1){
        subtract_weight(movie, config);
    }

    else if(user_input == 1){
        add_weight(movie, config);
    }
    write_config(config);
}

void subtract_weight(struct movie movie, setting *config)
{
    int config_offset = STREAM_SERVICE_COUNT + SETTING_COUNT + ADDITIONAL_OFFSET;
    
    for(int i = 0; i < MAX_GENRES; i++){
        if(movie.genre[i] == 1){
            if(config[config_offset + i].value > 6 || config[config_offset + i].value < 5){
                config[config_offset + i].value -= 1;
            }
            else if(config[config_offset + i].value == 1){
                continue;
            }
            else{
                config[config_offset + i].value -= 2;
            }
        }
    }
}

void add_weight(struct movie movie, setting *config)
{
    int config_offset = STREAM_SERVICE_COUNT + SETTING_COUNT + ADDITIONAL_OFFSET;
    
    for(int i = 0; i < MAX_GENRES; i++){
        if(movie.genre[i] == 1){
            if(config[config_offset + i].value > 5 || config[config_offset + i].value < 4){
                config[config_offset + i].value += 1 ;
            }
            else if(config[config_offset + i].value == 10){
                continue;   
            }
            else{
                config[config_offset + i].value += 2;
            }  
        }
    } 
}


