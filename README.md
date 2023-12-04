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
- Maybe a struct that takes the settings so you could parse it into functions.
- Implement age rating setting
- Implement genre selection
- implement Content filtering

## Known Bugs
- When input is other then expected input, the program ends it own life

## Libraries
```
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
```

## Constant Variables
```
#define STREAM_SERVICE_COUNT 11
#define SETTING_COUNT 4

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
void welcome(setting * config);
void adjust_s_services(setting * config);
void printMenu(setting * config);
int is_element_in_array(int x, int arr[], int array_length);
void quit_function();
void write_config(setting *key_value_pair);
void check_file_opening(FILE *f);
void read_config();
int toggle_setting(setting * config, int offset, int setting);
void print_config_items(setting * config, int offset, const char* header, int print_array_length);
void change_preferences();
```


