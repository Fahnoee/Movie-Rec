/**
 * This is the main C program file for the best movie recommender in the world.
 * It contains various functions for managing streaming services, adjusting preferences, and providing movie recommendations.
 * The program uses structs to represent genres, streaming services, and movies.
 * It also includes file handling functions for reading and writing configuration files.
 */


// ######################
// ###### libraries #####
// ######################
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "fscanf.c"
#include "genreinput.c"

// ###############################
// ###### Constant Variables #####
// ###############################
#define STREAM_SERVICE_COUNT 11
#define SETTING_COUNT 4
#define ARRAY_MENU_LENGTH 4

// Læs om prepressor directives, med det her kan vi bruge system("CLEAR_SCREEN") på både mac, linux og windows
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// ####################
// ###### Structs #####
// ####################

typedef struct
{
    char key[50];
    int value;
} setting;


// #######################
// ###### Prototypes #####
// #######################
void welcome(setting * config);
void adjust_s_services(setting * config);
void printMenu(setting *config, struct movie movies_array[]);
void quit_function();
void write_config(setting *key_value_pair);
void check_file_opening(FILE *f);
void read_config(setting * config);
int toggle_setting(setting * config, int offset, int setting);
void print_config_items(setting * config, int offset, const char* header, int print_array_length);
void change_preferences(setting* config);
void movies_from_services(setting * config, struct movie movie[]);
int get_value_from_key(setting *config, char *key);
void get_recommendation(setting * config, int genre[], struct movie movie[], int adult_movies);

// void import_movies(int movie_array[]); // Husk lige at tilføj den igen

//////////////
/////MAIN/////
//////////////
int main(void)
{
    struct movie movie_array[MAX_MOVIES];

    FILE *f = fopen("movies.txt", "r");
    if (f == NULL)
    {
        printf("FILE WAS NOT OPENED.\n"); 
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_MOVIES; i++) {
        movie_array[i] = import_movies(f);
    }
    fclose(f);
   
    setting config[STREAM_SERVICE_COUNT + SETTING_COUNT] = {
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
        {"Rakuten", 1},
        // Other settings
        {"Reset all", 0},
        {"Setting 2", 1},
        {"Setting 3", 1},
        {"Setting 4", 1},
    };

    welcome(config);

    int running = 1;
    
    system(CLEAR_SCREEN);
    
    while (running) {
        printMenu(config, movie_array);
        if (config[STREAM_SERVICE_COUNT].value == 1) {
            remove("conf.txt");
            running = 0;
        }
    }

    return 0;
}


// Function for welcomming the new user and loading up their config file
void welcome(setting * config)
{
    read_config(config);
    printf("\nHey mate, welcome to this movie recommender\n");
    printf("\n");
}

// ###########################
// ###### Menu functions #####
// #########################

// Function that creats a (Btw Emil var imod det) main menu and handles it trough other functions
void printMenu(setting * config, struct movie movie_array[])
{
    // Integer value for selecting menu option
    int selection;

     // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: Change preferences\n");
    printf("4: EXIT\n");

    // Ask the user to select a menu option 
    printf("Enter a number:"); 
    int result;
        do {
            result = scanf("%d", &selection);

            // Clear the input buffer if the input is not an integer
            if (result == 0) {
                while (getchar() != '\n');
                printf("You didn't enter a number try again: ");
            }
        } while (result != 1);

    
    int wanted_genre[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //fiktiv indtil genre er lavet

    switch (selection) {
    case 1:
      get_recommendation(config, wanted_genre, movie_array, 1);
      break;
    case 2:
      adjust_s_services(config);
      break;
    case 3:
      change_preferences(config);      
      break;
    case 4:
      quit_function();
      break;
    
    default:
      printf("invalid input"); 
      break;
    }
 
} 
//  Service sub menu functions
//

// Function to handle user input and toggle the status of active services
void adjust_s_services(setting * config) {
    int user_input;

    while (1) {
        system(CLEAR_SCREEN);
        print_config_items(config, 0, "Currently you have the following streaming services available", STREAM_SERVICE_COUNT);

        // Ask the user which streaming service they want to activate/deactivate
        printf("\nWhich streaming service do you want to activate/deactivate?\n");
        printf("If you don't want to change any, press 0.\n");
        printf("Enter number: ");
        int result;
        do {
            result = scanf("%d", &user_input);

            // Clear the input buffer if the input is not an integer
            if (result == 0) {
                while (getchar() != '\n');
                printf("You didn't enter a number try again: ");
            }
        } while (result != 1);

        // Toggle the setting and break the loop if the result is 0
        if (toggle_setting(config, 0, user_input) == 0) {
            system(CLEAR_SCREEN);
            break;
        }
    }

    write_config(config);
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

// Change preferences menu printing and toggling
void change_preferences(setting * config) {
    int user_input;
    int setting_offset = STREAM_SERVICE_COUNT;
    
    while (1) {
        system(CLEAR_SCREEN);
        print_config_items(config , setting_offset, "===== Settings Menu =====\n Write 0 to exit menu", SETTING_COUNT);

        printf("Enter number:");
        scanf("%d", &user_input); 

        if (toggle_setting(config, setting_offset, user_input) == 0) {
            printf("Exiting setting s menu.\n");
            system(CLEAR_SCREEN);
            break;
        } else if (user_input == (SETTING_COUNT + 1)) {
            // Run reset setting function here
        }
        
    }
    write_config(config);
}

// Function for printing what is available at the moment
void print_config_items(setting * config, int offset, const char* header, int print_array_length) {
    printf("\n%s:\n", header);

    for (int i = 0; i < print_array_length; i++) {
        if (config[i + offset].value == 1) {
            printf("%3d: %-13s   [x]\n", i + 1, config[i + offset].key);
        } else {
            printf("%3d: %-13s   [ ]\n", i + 1, config[i + offset].key);
        }
    }
}
// Toggles a value in the config array of structs
int toggle_setting(setting * config, int offset, int setting)
{
    if (setting == 0) {
        return 0;
    }
    else if (setting >= 0 && setting <= STREAM_SERVICE_COUNT) {
        setting = (setting + offset) - 1; // Needs to be 1 less then input due to arrays starting at 0
                                          // change the value of the streaming service
        if (config[setting].value == 1)
        {
            config[setting].value = 0;
            
        }
        else
        {
            config[setting].value = 1;
        }
        return 1;
    }
    else {
        printf("Invalid input! We try again\n");
        return 1;
    }
}

// ####################################
// ###### File handling functions #####
// ####################################

// Function for creating a config, used to save available streaming servives
void write_config(setting *key_value_pair)
{
    FILE *config_file;                    // Creates pointer to file
    config_file = fopen("conf.txt", "w"); // Opens file
    check_file_opening(config_file);      // Checks if it is read correctly

    for (int i = 0; i < (STREAM_SERVICE_COUNT + SETTING_COUNT); i++) { // Forloop that writes the config file
        fprintf(config_file, "%s=%d \n", key_value_pair[i].key, key_value_pair[i].value);
    }

    fclose(config_file); // Close file
}

// Function for reading a config, used to save available streaming servives
void read_config(setting * config)
{
    FILE *file;
    file = fopen("conf.txt", "r");
    if (file == NULL) {                         // In case of first opening of program the config will be missing
        write_config(config); // Here a config is writting from the global variable.

        file = fopen("conf.txt", "r"); // Re-open the file after creating it
        check_file_opening(file);
    }

    for (int i = 0; i < (STREAM_SERVICE_COUNT + SETTING_COUNT); i++) {
        fscanf(file, "%[^=]=%d ", config[i].key, &config[i].value);
    }
    fclose(file);
}

/* Function for testing if a file is read correctly */
void check_file_opening(FILE *f)
{
    if (f == NULL) {
        printf("There has been a fail in loading your file, now exiting...\n");
        exit(EXIT_FAILURE);
    }
}

/* Function for getting a new recommendation */
void get_new_recommendation()
{
    /* kald tidligere recommendation, men tillad ikke de x første/bedste matches at blive vist
       så den tager måske i+5, i+6, i+7, i+8 osv som valg. */

    printf("You have choosen to get new recommendations\n");
    printf("Based on your previous genre-settings and choice of streaming\n");
    printf("platforms, these new options is available: \n");

    /* Print på samme måde som den almindelige recommendation (nok via en func)
       så der blot vises de nye recommendations */
}


// ##################################
// ###### Recommendation system #####
// ##################################

/* Function for getting a reommendation */
void get_recommendation(setting * config, int genre[], struct movie movie[], int adult_movies) 
{
    int g = 0;
    for(int i = 0; i < MAX_GENRES; i++){
        g += genre[i];
    }
    if(g == 0){
        genre_main(movie, genre);
    }
    printf("%d, %d", genre[0], genre[9]);




    movies_from_services(config, movie);

}

/* Function for finding movies availbel on the given streaming services */
void movies_from_services(setting * config, struct movie movie[]) 
{
     // Assuming 'movie[]' is an array of 'struct movie' and 'service[]' is an array indicating which services are active
    int filteredMovieIndex = 0;
    struct movie movie_watchable[MAX_MOVIES];
    for (int movieIndex = 0; movieIndex < MAX_MOVIES; movieIndex++) {
        for (int serviceIndex = 0; serviceIndex < STREAM_SERVICE_COUNT; serviceIndex++) {
            if (config[serviceIndex].value == 1 && movie[movieIndex].services[serviceIndex] == 1) {
                movie_watchable[filteredMovieIndex] = movie[movieIndex];
                filteredMovieIndex++;
                break; // Break the inner loop if the movie is available on any of the selected services
            }
        }
    }

    // Print the movies that are available on the selected services
    printf("The following movies are available on the selected services:\n");
    for (int i = 0; i < filteredMovieIndex; i++) {
        printf("%s\n", movie_watchable[i].title);
    }
    

    
}

/* Function for printing the recommendation */
