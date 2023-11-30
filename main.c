/**
 * This is the main C program file for the best movie recommender in the world.
 * It contains various functions for managing streaming services, adjusting preferences, and providing movie recommendations.
 * The program uses structs to represent genres, streaming services, and movies.
 * It also includes file handling functions for reading and writing configuration files.
 */

/*
 * Bugs
 * Når input er andet end det forventede så fucker programmet
 *
 *
*/


// ######################
// ###### libraries #####
// ######################
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


// ###############################
// ###### Constant Variables #####
// ###############################
#define MAX_MOVIES 1000
#define STREAM_SERVICE_COUNT 11

// Læs om prepressor directives, med det her kan vi bruge system("CLEAR_SCREEN") på både mac, linux og windows
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else 
#define CLEAR_SCREEN "clear"
#endif

// ####################
// ###### Structs #####
// ####################
struct genre // Mangler muligvis nogle genrer
{
    int action;
    int adventure;
    int drama;
    int crime;
    int romance;
    int fantasy;
    int mystery;
    int music;
    int sport;
    int animation;
    int biography;
    int history;
    int sci_fi;
    int war;
    int family;
    int thriller;
    int horror;
    int comedy;
    int western;
    int musical;
};

struct services
{
    int netflix;
    int drtv;
    int hbo;
    int disney;
    int tv2play;
    int skyshowtime;
    int filmstriben;
    int viaplay;
    int cmore;
    int amazone_prime;
    int rakuten;
};

struct movie
{
    int id;
    char title[50];
    int pg;
    int runtime;
    struct genre genre;
    int score;
    char resume[250];
    struct services services;
};

typedef struct
{
    char key[50];
    int value;
} setting;


// #######################
// ###### Prototypes #####
// #######################
void welcome();
void adjust_s_services();
void print_services();
int change_service();
void printMenu();
int is_element_in_array(int x, int arr[], int array_length);
void quit_function();
void write_config(setting * key_value_pair);
void check_file_opening(FILE *f);
void read_config();
int toggle_setting(int offset, int setting);
//void import_movies(int movie_array[]); // Husk lige at tilføj den igen


// ##########################
// ###### Global Values #####
// ##########################
setting config[STREAM_SERVICE_COUNT] = {
    // Streaming service's
    {"Netflix", 1},
    {"DRTV", 1},
    {"HBO max", 1},
    {"Disney+", 1},
    {"TV2play", 1},
    {"SkyShowtime", 1},
    {"Filmstriben", 1},
    {"Viaplay", 1},
    {"Cmore", 1},
    {"Amazone Prime", 1},
    {"Rakuten", 1}
    // Other settings
    };


//////////////
/////MAIN/////
//////////////
int main(void)
{
    welcome();
    
    int running = 1;

    system(CLEAR_SCREEN);

    while (running){
        printMenu();
    }
    
    return 0;
}

// Function for welcomming the new user and loading up their config file
void welcome()
{
    read_config(config);
    printf("\nHey mate, welcome to this movie recommender\n");
    printf("\n");
}

// ########################### 
// ###### Menu functions #####
// ###########################

// Function that creats a main menu and handles it trough other functions
void printMenu()
{
    // Integer value for selecting menu option
    int selection;
    int menu_option[] = {1, 2, 3, 4};
    int array_menu_length = 4;

    // Array containing the functions that will be called from the main menu
    void (*array_of_functions[])() = {adjust_s_services, adjust_s_services, adjust_s_services, quit_function};

    // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: Change preferences\n");
    printf("4: EXIT\n");

    scanf("%d", &selection);

    // 
    if (is_element_in_array(selection, menu_option, array_menu_length)) {
        array_of_functions[selection - 1]();
    }
    else {
        printf("Invalid input!");
    }
}

// Function to check if x is in array
int is_element_in_array(int x, int arr[], int array_length)
{
    for (int i = 0; i < array_length; i++) {
        if (arr[i] == x) {
            return 1; // x found
        }
    }
    return 0; // x not found
}


//
//  Service sub menu functions
//

// Function for adjusting available streaming services
void adjust_s_services()
{
    while(1) {
        system(CLEAR_SCREEN);
        print_services();
        if (change_service() == 0) {
            system(CLEAR_SCREEN);
            break;
        }
        system(CLEAR_SCREEN);
    }
    write_config(config);
}

// Function for printing what is available at the moment
void print_services()
{
    printf("\nCurrently you have the following streaming services available:\n");

    for (int i = 0; i < STREAM_SERVICE_COUNT; i++) {      // Print available streaming services and whether you have them or not
        if (config[i].value == 1) {
            printf("%2d: %-13s   [x]\n", i + 1, config[i].key);  // Gør så [x] og [ ] står på en lige linje
        }
        else {
            printf("%2d: %-13s   [ ]\n", i + 1, config[i].key);
        }
    }
}   


// Function to handle user input and toggle the status of active services
int change_service()
{
    int user_input;
    // Ask user which streaming service they want to activate/deactivate
    printf("\nWhich streaming service do you want to activate/deactivate?\n");
    printf("If you dont wanna change any press 0.\n");
    printf("Enter number:");

    scanf("%d", &user_input);
    if ((toggle_setting(0, user_input)) == 0) {
        return 0;
    } else {
        return 1;
    } 
}

// Function for quiting the program
void quit_function()
{
    system(CLEAR_SCREEN);
    printf("You have choosen to exit our program, we hope you have a good\n");
    printf("time with the recommended movie  :D\n");
    printf("Your choice of streaming services have been saved \n");
    exit(EXIT_FAILURE);
}  
/*
void change_preferences() 
{
    int user_input;
    char settingOptions[100000] = {};

    printf("===== Settings Menu =====\n
            1. Setting 1\n
            2. Setting 2\n
            3. Setting 3\n
            4. Setting 4\n
            5. reset your settings\n");
    printf("Enter number:");
    scanf("%d", user_input);
    if ((toggle_setting(11, user_input)) == 0) {
        return 0;
    } else {
        return 1;
    } 
    
}
*/
int toggle_setting(int offset, int setting) 
{
    if (setting == 0) {
        return 0; 
    }
    else if (setting >= 0 && setting <= 11) {
        setting = (setting + offset) - 1;        // Needs to be 1 less then input due to arrays starting at 0
                                                 // change the value of the streaming service
        if (config[setting].value == 1) {
            config[setting].value = 0;
        }
        else {
            config[setting].value = 1; 
        }
    }
    else {
        printf("Invalid input! We try again\n");
        return 1;
    }
}

// ####################################
// ###### File handling functions #####
// ####################################

//Function for creating a config, used to save available streaming servives
void write_config(setting* key_value_pair)
{
    FILE *config_file;                              //Creates pointer to file
    config_file = fopen("conf.txt", "w");           //Opens file
    check_file_opening(config_file);                //Checks if it is read correctly
    
    for (int i = 0; i < STREAM_SERVICE_COUNT; i++) {        //Forloop that writes the config file
        fprintf(config_file, "%s=%d \n", key_value_pair[i].key, key_value_pair[i].value);
    }

    fclose(config_file);                            //Close file
}

//Function for reading a config, used to save available streaming servives
void read_config()
{
    FILE *file;
    file = fopen("conf.txt", "r");
    if (file == NULL) {                     //In case of first opening of program the config will be missing
        write_config(config);               //Here a config is writting from the global variable.

        file = fopen("conf.txt", "r");      //Re-open the file after creating it
        check_file_opening(file);
    }
    
    for (int i = 0; i < STREAM_SERVICE_COUNT; i++) {
        fscanf(file, "%[^=]=%d ", config[i].key, &config[i].value);
    }
    fclose(file);
}

/* Function for testing if a file is read correctly */
void check_file_opening(FILE *f) {
    if (f == NULL) {
        printf("There has been a fail in loading your file, now exiting...\n");
        exit(EXIT_FAILURE);
    }
}

/* Function for getting a new recommendation */
void get_new_recommendation(){

    /* kald tidligere recommendation, men tillad ikke de x første/bedste matches at blive vist
       så den tager måske i+5, i+6, i+7, i+8 osv som valg. */

    printf("You have choosen to get new recommendations\n");
    printf("Based on your previous genre-settings and choice of streaming\n");
    printf("platforms, these new options is available: \n");

    /* Print på samme måde som den almindelige recommendation (nok via en func)
       så der blot vises de nye recommendations */

}



/* 
void run()
{
    struct movie movie_array[MAX_MOVIES];

    import_movies(movie_array);
}



void import_movies(struct movie movie_array[])
{

    FILE *f = fopen("movies.txt", "r");
    if (f == NULL)
    {
        printf("Det mislykkedes at aabne tekstfilen.\n");
        exit(EXIT_FAILURE);
    }


    for(int i = 0; i < MAX_MOVIES; i++)
    {

        fscanf(f, "%d;%s;%d;%d;",  
                &movie_array[i].id,
                movie_array[i].title,
                &movie_array[i].pg,
                &movie_array[i].runtime); 
                
        //import genre struct
        
        fscanf(f, ";%d;%s;", 
        &movie_array[i].score, movie_array[i].resume);
    
        //import service struct
    }
}

import_genre(FILE *f, int movie_array[]){

    char *1[10];
    char *2[10];
    char *3[10];
    char genre_array[] = { "Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Sci_fi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};

    fscanf(f, "%s, %s, %s", 1, 2, genre_3 );

    for(int j = 0; i > 3; i++)
    {    
        for(int i = 0; i < (sizeof(genre_array))/sizeof(genre_array[0]); i++)
        {
            
            if(strcmp(j, genre_array[i]) = 0)
            {
                genre.action
            }
        }
    }




}


import_services(FILE *f, int movie_array[])
{

}

 */ 