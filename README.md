# Movie Recommender

## Overview
This C program is designed to be the best movie recommender in the world. It includes various functions for managing streaming services, adjusting preferences, and providing movie recommendations. The program uses structs to represent genres, streaming services, and movies. Additionally, it includes file handling functions for reading and writing configuration files.

## Table of Contents
* TODO List
* Known Bugs
* Libraries
* Constant Variables
* Structs
* Prototypes


## TODO List
- Implement age rating setting
- implement Content filtering

## Known Bugs
- NULL

## Libraries
```
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fscanf.c"
```

## Constant Variables
```
#define STREAM_SERVICE_COUNT 11
#define SETTING_COUNT 4
#define ARRAY_MENU_LENGTH 4
#define GENRE_COUNT 20

// Læs om prepressor directives, med det her kan vi bruge system("CLEAR_SCREEN") på både mac, linux og windows
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif
```

## Structs
```
typedef struct
{
    char key[50];
    int value;
} setting;
```

## Prototypes
```
void get_recommendation(setting * config, /*int genre[],*/ struct movie movie[]/*, int adult_movies*/);
void print_config_items(setting *config, int offset, const char *header, int print_array_length, int valueBool);
void change_preferences(setting* config);
void movies_from_services(setting * config, struct movie movie[]);
void change_genre_config(setting *config);
void welcome(setting * config);
void adjust_s_services(setting * config);
void printMenu(setting *config, struct movie movies_array[]);
void quit_function();
void write_config(setting *key_value_pair);
void check_file_opening(FILE *f);
void read_config(setting * config);
int toggle_setting(setting * config, int offset, int setting);
int get_value_from_key(setting *config, char *key);
int change_setting_value(setting *config, int setting);
int scanf_for_int(void);
```


