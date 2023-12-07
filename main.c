/*
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

// ###############################
// ###### Constant Variables #####
// ###############################
#define STREAM_SERVICE_COUNT 11
#define SETTING_COUNT 4
#define ARRAY_MENU_LENGTH 4
#define GENRE_COUNT 20
#define DEBUG 0

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
void get_recommendation(setting * config, /*int genre[],*/ struct movie movie[]/*, int adult_movies*/);
void print_config_items(setting *config, int offset, const char *header, int print_array_length, int valueBool);
void change_preferences(setting* config);
void movies_from_services(setting *config, struct movie movie[]);
void change_genre_config(setting *config);
void welcome(setting *config);
void adjust_s_services(setting * config);
void printMenu(setting *config, struct movie movies_array[]);
void quit_function();
void write_config(setting *key_value_pair);
void check_file_opening(FILE *f);
void read_config(setting *config);
void reset_conf(setting * config);
int toggle_setting(setting * config, int offset, int setting);
int get_value_from_key(setting *config, char *key);
int change_setting_value(setting *config, int setting);
int scanf_for_int(void);
void reset_conf(setting * config);
void get_recommendation(setting *config, struct movie all_movies[]);
void filter_and_rank_movies(setting *config, struct movie all_movies[], struct movie top_movies[], int top_count); 
int is_movie_already_selected(struct movie top_movies[], int top_count, struct movie movie);
void screen_clear();

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
   
    setting config[STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT] = {
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
        // Genres
        {"Action", 1},
        {"Adventure", 1},
        {"Drama", 1},
        {"Crime", 1},
        {"Romance", 1},
        {"Fantasy", 1},
        {"Mystery", 1},
        {"Music", 1},
        {"Sport", 1},
        {"Animation", 1},
        {"Biography", 1},
        {"History", 1},
        {"Scifi", 1},
        {"War", 1},
        {"Family", 1},
        {"Thriller", 1},
        {"Horror", 1},
        {"Comedy", 1},
        {"Western", 1},
        {"Musical", 1},
    };

    welcome(config);

    int running = 1;
    
    screen_clear();
    
    while (running) {
        printMenu(config, movie_array);
    }

    return 0;
}

void screen_clear() {
    if (DEBUG == 0)
        system(CLEAR_SCREEN);
}


// Function for welcoming the new user and loading up their config file
void welcome(setting * config)
{
    read_config(config);
}

// ###########################
// ###### Menu functions #####
// #########################

// Function that creates a main menu and handles it trough other functions
void printMenu(setting * config, struct movie movie_array[])
{
    // Integer value for selecting menu option
    int selection;

     // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: Change genre weights\n");
    printf("4: Change preferences\n");
    printf("0: EXIT\n");

    // Ask the user to select a menu option 
    printf("Enter a number: "); 
    int user_input = scanf_for_int();
        
    /*int wanted_genre[20] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};*/ //fiktiv indtil genre er lavet

    switch (user_input) {
    case 1:
      get_recommendation(config, /*wanted_genre,*/ movie_array/*, 1*/);
      break;
    case 2:
      adjust_s_services(config);
      break;
    case 3:
      change_genre_config(config);      
      break;
    case 4:
      change_preferences(config);      
      break;
    case 0:
      quit_function();
      break;
    
    default:
      screen_clear();
      printf("\nInvalid number, you can only use numbers represented by the menu: \n"); 
      break;
    }
 
} 
//  Service sub menu functions
//

// Checks if parameter is int and returns user_input/result
int scanf_for_int(void) {
    int user_input;
    int result;
    do
    {
        result = scanf("%d", &user_input);

        // Clear the input buffer if the input is not an integer
        if (result == 0)
        {
            while (getchar() != '\n')
                ;
            printf("You didn't enter a number try again: ");
        }
        } while (result != 1);
        return user_input;
}

// Function to handle user input and toggle the status of active services
void adjust_s_services(setting * config) {
    int user_input;

    while (1) {
        screen_clear();
        print_config_items(config, 0, "Currently you have the following streaming services available", STREAM_SERVICE_COUNT, 0);

        // Ask the user which streaming service they want to activate/deactivate
        printf("\nWhich streaming service do you want to activate/deactivate?\n");
        printf("If you don't want to change any, press 0.\n");
        printf("Enter number: ");
        user_input = scanf_for_int();

        // Toggle the setting and break the loop if the result is 0
        if (toggle_setting(config, 0, user_input) == 0) {
            screen_clear();
            break;
        }
    }

    write_config(config);
}

// Reset conf function
void reset_conf(setting * config) {
    int lines_in_config = STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT;
    if (config[STREAM_SERVICE_COUNT + 1].value == 1) {
        for (int i = 0; i < lines_in_config; i++) {
            if (i == 11){ 
                config[i].value = 0;    // 
                continue;               //skips the line where reset config has been written
            }
            config[i].value = 1;
        }
        screen_clear();
        write_config(config);
        printf("\nAll of your settings have been reset :) \n");
    }
}    

// Function for quitting the program
void quit_function()
{
    screen_clear();
    printf("You have choosen to exit our program, we hope you have a good\n");
    printf("time with the recommended movie  :D\n");
    printf("Your choice of streaming services have been saved \n");
    exit(EXIT_SUCCESS);
}

// Change preferences menu printing and toggling
void change_preferences(setting * config) {
    int user_input;
    int setting_offset = STREAM_SERVICE_COUNT;
    
    while (1) {
        screen_clear();
        print_config_items(config , setting_offset, "===== Settings Menu =====\n Write 0 to exit menu", SETTING_COUNT, 0);

        printf("Enter number: ");
        user_input = scanf_for_int();

        if (user_input == 1) {
            reset_conf(config);
            break;
        }

        if ((toggle_setting(config, setting_offset, user_input) == 0) && (user_input != 1)) {
            printf("Exiting settings menu.\n");
            screen_clear();
            break;
        }
    }
    write_config(config);
}


// sub menu for changing genre config
void change_genre_config(setting * config) 
{
    int user_input;
    int setting_offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    
    while (1) {
        int user_input;
        
        
        screen_clear();
        print_config_items(config , setting_offset, "===== Genre Menu =====\n Write 0 to exit menu", GENRE_COUNT, 1);

        printf("Select Genre: ");
        user_input = scanf_for_int();
        if (change_setting_value(config, user_input) == 0) {
            screen_clear();
            break;
        } 
    }
    write_config(config);
}


// Function for printing what is available at the moment
void print_config_items(setting * config, int offset, const char* header, int print_array_length, int valueBool) {
    printf("\n%s:\n", header);
    if (valueBool == 0) {
        for (int i = 0; i < print_array_length; i++) {
            if (config[i + offset].value == 1) {
                printf("%3d: %-13s   [x]\n", i + 1, config[i + offset].key);
            } else {
                printf("%3d: %-13s   [ ]\n", i + 1, config[i + offset].key);
            }
        }
    } else if (valueBool == 1) {
        for (int i = 0; i < print_array_length; i++) {
            printf("%3d: %-13s   [%d]\n", i + 1, config[i + offset].key, config[i + offset].value);
        }
    }    
}


// changes a value in the config array of structs
int change_setting_value(setting * config, int setting) {
    int offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    int user_input;

    if (setting == 0) {
        return 0;
    }
   
    if (setting >= 1 && setting <= STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT) {
        setting = (setting + offset) - 1;
        printf("Enter a value for %s: ", config[setting].key);
        user_input = scanf_for_int();
        if (user_input >= 1 && user_input <= 10) {
            config[setting].value = user_input;
        } 
        else {
        printf("Invalid input! We try again\n");
        return 1;
        }
    }
    return 1;
}

// Toggles a value in the config array of structs
int toggle_setting(setting * config, int offset, int setting)
{
    if (setting == 0) {
        return 0;
    }
    
    
    if (setting >= 1 && setting <= STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT) {
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

    for (int i = 0; i < (STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT); i++) { // Forloop that writes the config file
        fprintf(config_file, "%s=%d \n", key_value_pair[i].key, key_value_pair[i].value);
    }

    fclose(config_file); // Close file
}

// Function for reading a config, used to save available streaming services
void read_config(setting * config)
{
    FILE *file;
    file = fopen("conf.txt", "r");
    if (file == NULL) {                         // In case of first opening of program the config will be missing
        write_config(config); // Here a config is writing from the global variable.

        file = fopen("conf.txt", "r"); // Re-open the file after creating it
        check_file_opening(file);
    }

    for (int i = 0; i < (STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT); i++) {
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
// The main recommendation function
void get_recommendation(setting *config, struct movie all_movies[]) {
    struct movie top_movies[3];
    filter_and_rank_movies(config, all_movies, top_movies, 3);

    printf("\nTop 3 Recommended Movies:\n");
    for (int i = 0; i < 3; i++) {
        print_movie(top_movies[i]);
    }

}


// Helper function to compare movies for qsort
int compareMovies(const void *a, const void *b) {
    struct movie *movieA = (struct movie *)a;
    struct movie *movieB = (struct movie *)b;

    // Compare genre scores
    if ((*movieA).genre_score > (*movieB).genre_score) {
        return -1;  // A comes before B
    } else if ((*movieA).genre_score < (*movieB).genre_score) {
        return 1;   // B comes before A
    }

    // If genre scores are equal, compare movie titles
    int titleComparison = strcmp((*movieA).title, (*movieB).title);

    return titleComparison;
}

// Helper function to filter and rank movies 

void filter_and_rank_movies(setting *config, struct movie all_movies[], struct movie top_movies[], int top_count) {
    // Calculate scores for each movie
    for (int i = 0; i < MAX_MOVIES; i++) {
        all_movies[i].genre_score = 0;
        int genre_count = 0;
        // Check if the movie is available on any active streaming service
        for (int j = 0; j < STREAM_SERVICE_COUNT; j++) {
            if (config[j].value == 1 && all_movies[i].services[j] == 1) {
                // Calculate score based on genre weights
                for (int k = 0; k < GENRE_COUNT; k++) {
                    if (all_movies[i].genre[k] == 1) {
                        int genre_weight = config[STREAM_SERVICE_COUNT + SETTING_COUNT + k].value;
                        all_movies[i].genre_score += genre_weight;
                        genre_count++;
                    }
                }
                all_movies[i].genre_score /= sqrt((double)genre_count);
                // Optional: Add a balancing factor for movies with multiple genres
                // all_movies[i].genre_score += BALANCING_FACTOR * (genre_count - 1);

                break; // No need to check other streaming services
            }
        }
    }

    // Use qsort to sort movies based on scores
    qsort(all_movies, MAX_MOVIES, sizeof(struct movie), compareMovies);

    // Copy the top movies to the result array
    for (int i = 0; i < top_count && i < MAX_MOVIES; i++) {
        top_movies[i] = all_movies[i];
    }
}








void movies_from_services(setting* config, struct movie movie[]) {
    // Assuming 'movie[]' is an array of 'struct movie' and 'service[]' is an array indicating which services are active
    int filteredMovieIndex = 0;
    struct movie movie_watchable[MAX_MOVIES];

    // Iterate through movies and services to filter watchable movies
    for (int movieIndex = 0; movieIndex < MAX_MOVIES; movieIndex++) {
        for (int serviceIndex = 0; serviceIndex < STREAM_SERVICE_COUNT; serviceIndex++) {
            if (config[serviceIndex].value == 1 && movie[movieIndex].services[serviceIndex] == 1) {
                // Movie is available on the selected service, add it to watchable movies
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
