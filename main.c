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
#include <time.h>
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
void change_settings(setting* config);
void change_genre_config(setting *config);
void welcome(setting *config);
void change_s_services(setting * config);
void print_menu(setting *config, struct movie movies_array[]);
void quit_function();
void write_config(setting *key_value_pair);
void check_file_opening(FILE *f);
void read_config(setting *config);
void reset_conf(setting * config);
int toggle_setting(setting *config, int offset, int setting, int valueBool);
int change_setting_value(setting *config, int setting);
int scanf_for_int(int min_value, int max_value);
void reset_conf(setting * config);
void get_recommendation(setting *config, struct movie all_movies[]);
void filter_and_rank_movies(setting *config, struct movie all_movies[], struct movie top_movies[], int top_count); 
void subtract_weight(struct movie movie, setting *config);
void add_weight(struct movie movie, setting *config);
void weight_genre(struct movie movie, setting *config);
int print_info(struct movie movie, setting *config, int movie_pick);
void select_movie(struct movie show_five_movie_arr[], setting *config);
void explain(struct movie movie, setting *config, char *genre_array[], int movie_pick);
double BALANCING_FACTOR(double genre_count, setting * config);

void screen_clear();


//////////////
/////MAIN/////
//////////////
int main(void)
{
    srand(time(NULL));
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
        {"Square root scaling", 1},
        {"Linear scaling", 0},
        {"Logarithmic scaling", 0},
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
        print_menu(config, movie_array);
    }
    
    return 0;
}
// ############MAIN-END###################

// Function to check if the program is in "debug-mode"
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
// ###########################

// Function that creates a main menu and handles it trough other functions
void print_menu(setting * config, struct movie movie_array[])
{
    // Integer value for selecting menu option
    int selection;

     // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: Change genre weights\n");
    printf("4: Settings menu\n");
    printf("0: EXIT\n");

    // Ask the user to select a menu option 
    printf("Enter a number: "); 
    int user_input = scanf_for_int(0, 4);
        
    switch (user_input) {
    case 1:
      get_recommendation(config, movie_array);
      break;
    case 2:
      change_s_services(config);
      break;
    case 3:
      change_genre_config(config);      
      break;
    case 4:
      change_settings(config);      
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

// Checks if parameter is int and returns user_input/result
int scanf_for_int(int min_value, int max_value) {
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
            printf("You didn't enter a number. Please try again: ");
        }
        else if (user_input < min_value || user_input > max_value)
        {
            printf("Invalid number. Please enter a number between %d and %d: ", min_value, max_value);
            result = 0; // Set result to 0 to continue the loop
        }
    } while (result != 1);
    return user_input;
}

// Function to handle user input and toggle the status of active services
void change_s_services(setting * config) {
    int user_input;

    while (1) {
        screen_clear();
        print_config_items(config, 0, "Currently you have the following streaming services available", STREAM_SERVICE_COUNT, 0);

        // Ask the user which streaming service they want to activate/deactivate
        printf("\nWhich streaming service do you want to activate/deactivate?\n");
        printf("If you don't want to change any, press 0.\n");
        printf("Enter number: ");
        user_input = scanf_for_int(0, 11);

        // Toggle the setting and break the loop if the result is 0
        if (toggle_setting(config, 0, user_input, 0) == 0) {
            screen_clear();
            break;
        }
    }

    write_config(config);
}

// Reset conf function
void reset_conf(setting * config) {
    int lines_in_config = STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT;
        for (int i = 0; i < lines_in_config; i++) {
        if (i == 11){ // reset settings
            config[i].value = 0;
        } else if (i >= STREAM_SERVICE_COUNT && i < STREAM_SERVICE_COUNT + SETTING_COUNT) { // reset scaling
            if (i == 12) {
                config[i].value = 1;
            } else {
                config[i].value = 0;
            }
            
        } else if (i >= STREAM_SERVICE_COUNT + SETTING_COUNT && i < lines_in_config) { // reset genre
            config[i].value = 5;
        } else {  // reset streaming services
            config[i].value = 1;
        }
    }
    
    screen_clear();
    write_config(config);
    printf("\nAll of your settings have been reset :) \n");

}

// Function for quitting the program
void quit_function()
{
    screen_clear();
    printf("You have chosen to exit our program. We hope you have had a good\n");
    printf("time with the recommended movie(s) :D\n");
    printf("Your choice of streaming services and genre weightings have been saved.\n");
    exit(EXIT_SUCCESS);
}

// Change preferences menu printing and toggling
void change_settings(setting * config) {
    int user_input;
    int setting_offset = STREAM_SERVICE_COUNT;
    
    while (1) {
        screen_clear();
        print_config_items(config , setting_offset, "===== Settings Menu =====", SETTING_COUNT, 0);
        printf("  0: Exit menu\n");

        printf("\nThe different scaling options has an effect on how your recommendations are generated.\n");
        printf("If you are unsure, the recommended option is square root. Here are some descriptions:\n\n");
        printf("Square root scaling: An approach where movies with one, two or three genres are\n");
        printf("                     approximately valued the same.\n");
        printf("Linear scaling:      Simplest approach, but undervalues genres with more than one genre.\n");
        printf("                     This is smart if you want one specific genre.\n");
        printf("Logarithm scaling:   An approach where movies with more than one genre is prefered.\n\n");

        printf("====================\n");
        printf("Enter number: ");
        user_input = scanf_for_int(0, 4);

        if (user_input == 1) {
            reset_conf(config);
            break;
        }

        if (user_input >= 2 && user_input <= 4) {
            // Set values from STREAM_SERVICE_COUNT + 1 to STREAM_SERVICE_COUNT + SETTING_COUNT to 0
            for (int i = STREAM_SERVICE_COUNT + 1; i <= STREAM_SERVICE_COUNT + SETTING_COUNT; i++) {
                config[i].value = 0;
            }

            // Set value number user_input + STREAM_SERVICE_COUNT to 1 
            // Minus 1 is to account for the array starting at 0
            config[user_input + STREAM_SERVICE_COUNT - 1 ].value = 1;            
            printf("Exiting settings menu.\n");
            screen_clear();
        }

        if ((toggle_setting(config, setting_offset, user_input, 1) == 0) && (user_input != 1)) {
            printf("Exiting settings menu.\n");
            screen_clear();
            break;
        }
    }
    write_config(config);
}

//Sub menu for changing genre config
void change_genre_config(setting * config) 
{
    int user_input;
    int setting_offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    
    while (1) {
        int user_input;
        screen_clear();
        print_config_items(config , setting_offset,
        "===== Genre Menu =====\n Write 0 to exit menu\n The genres can be rated from 1-10 where 10 is the highest", GENRE_COUNT, 1);
        
        printf("Select Genre: ");
        user_input = scanf_for_int(0, 20);
        if (change_setting_value(config, user_input) == 0) {
            screen_clear();
            break;
        } 
    }
    write_config(config);
}


//Function for printing what is available at the moment
void print_config_items(setting * config, int offset, const char* header, int print_array_length, int valueBool) 
{
    printf("%s:\n", header);
    if (valueBool == 0) {
        for (int i = 0; i < print_array_length; i++) {
            if (config[i + offset].value == 1) {
                printf("%3d: %-21s   [x]\n", i + 1, config[i + offset].key);
            } else {
                printf("%3d: %-21s   [ ]\n", i + 1, config[i + offset].key);
            }
        }
    } else if (valueBool == 1) {
        for (int i = 0; i < print_array_length; i++) {
            printf("%3d: %-13s   [%d]\n", i + 1, config[i + offset].key, config[i + offset].value);
        }
    }    
}


// changes a value in the config array of structs
int change_setting_value(setting * config, int setting) 
{
    int offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    int user_input;

    if (setting == 0) {
        return 0;
    }
   
    if (setting >= 1 && setting <= STREAM_SERVICE_COUNT + SETTING_COUNT + GENRE_COUNT) {
        setting = (setting + offset) - 1;
        printf("Enter a value for %s: ", config[setting].key);
        user_input = scanf_for_int(0, 10);
        if (user_input) {
             config[setting].value = user_input;
             return 1;
        }
       
        
    }
    return 0;
}

// Toggles a value in the config array of structs
int toggle_setting(setting * config, int offset, int setting, int valueBool)
{
    if (setting == 0) {
        return 0;
    } else if (valueBool == 1) {
        return 1;
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

// Function for creating a config, used to save available streaming services
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
/* Function for getting a recommendation */
// The main recommendation function
void get_recommendation(setting *config, struct movie all_movies[]) 
{
    struct movie top_movies[5];
    filter_and_rank_movies(config, all_movies, top_movies, 5);
    select_movie(top_movies, config);
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

    return 0;
}

// Helper function to filter and rank movies 
void filter_and_rank_movies(setting *config, struct movie all_movies[], struct movie top_movies[], int top_count) 
{
    // Calculate scores for each movie
    int movie_score_given = 0;
    for (int i = 0; i < MAX_MOVIES; i++) {
        all_movies[i].genre_score = 0;
        double genre_count = 0.0;
        // Check if the movie is available on any active streaming service
        for (int j = 0; j < STREAM_SERVICE_COUNT; j++) {
            if (config[j].value == 1 && all_movies[i].services[j] == 1) {
                movie_score_given++;
                // Calculate score based on genre weights
                for (int k = 0; k < GENRE_COUNT; k++) {
                    if (all_movies[i].genre[k] == 1) {
                        int genre_weight = config[STREAM_SERVICE_COUNT + SETTING_COUNT + k].value;
                        all_movies[i].genre_score += genre_weight;
                        genre_count = genre_count + 1.0;
                        
                    }
                }
                
                // Option from config: Adds a balancing factor for movies with multiple genres
                all_movies[i].genre_score /= BALANCING_FACTOR(genre_count, config);

                break; // No need to check other streaming services
            }
        }
    }

    // Use qsort to sort movies based on scores
    qsort(all_movies, MAX_MOVIES, sizeof(struct movie), compareMovies);

    // Copy the top movies to the result array
    for (int i = 0; i < top_count; i++) {
        top_movies[i] = all_movies[i];
    }

    
    int rand_one = (rand() % (movie_score_given - 3)) + 3;    
    int rand_two = (rand() % (movie_score_given - 3)) + 3;

    while (rand_one == rand_two) {                         //checks if the two random movies are differet
        rand_one = (rand() % (movie_score_given - 3)) + 3;
    }
    top_movies[3] = all_movies[rand_one];
    top_movies[4] = all_movies[rand_two];
}

double BALANCING_FACTOR(double genre_count, setting * config)
{
    if (config[12].value == 1) {
        return sqrt(genre_count);
    }
    
    else if (config[13].value == 1) {
        return(genre_count);
    }
    else if (config[14].value == 1) {
        return(log(genre_count+1));
    }
}

// ############################
// ###### print functions #####
// ############################

// ######################
// ###### Weighting #####
// ######################

void weight_genre(struct movie movie, setting *config)
{
    int user_input = 2;
    do{
        screen_clear();
        printf("Return to the program when you have watched the movie...\n");
        printf("Did you enjoy this movie?\n");
        printf("1:  Yes\n");
        printf("2:  No\n");
        printf("0:  Don't know\n"); 
        user_input = scanf_for_int(0, 2);
    }
    while(user_input < 0 || user_input > 2);
    screen_clear();
    if(user_input == 2){
        subtract_weight(movie, config);
    }

    else if(user_input == 1){
        add_weight(movie, config);
    }
    write_config(config);
}

void subtract_weight(struct movie movie, setting *config)
{
    int config_offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    
    for(int i = 0; i < MAX_GENRES; i++){
        if(movie.genre[i] == 1){
            if(config[config_offset + i].value > 7 && config[config_offset + i].value <= 10){
                
                if(config[config_offset + i].value == 10){
                    config[config_offset + i].value -= 3;
                }
                else{
                    config[config_offset + i].value -= 2;
                }
            }
            else if(config[config_offset + i].value == 1){
                continue;
            }
            else{
                config[config_offset + i].value -= 1;
            }
        }

    }

        
}

void add_weight(struct movie movie, setting *config)
{
    int config_offset = STREAM_SERVICE_COUNT + SETTING_COUNT;
    
    for(int i = 0; i < MAX_GENRES; i++){
        if(movie.genre[i] == 1){
            if(config[config_offset + i].value < 4 && config[config_offset + i].value > 0){
                
                if(config[config_offset + i].value == 1){
                    config[config_offset + i].value += 3;
                }
                else{
                    config[config_offset + i].value += 2;
                }
            }
            else if(config[config_offset + i].value == 10){
                continue;
            }
            else{
                config[config_offset + i].value += 1;
            }
        }
    } 
}

void select_movie(struct movie show_five_movie_arr[], setting *config)
{
    int i = 0;
    int movie_pick = 0;
    do{
        screen_clear();
        printf("===== Recommendations =====\n\n");
        for(int i = 0; i < 5; i++){
            printf("Movie %d: %s\n", i+1, show_five_movie_arr[i].title);
        }   
        printf("\nSelect a movie to show information (1-5) or 0 to return:\n");
        movie_pick = scanf_for_int(0, 5);
        if(movie_pick == 0){
            break;
        }

        i = print_info(show_five_movie_arr[movie_pick - 1], config, (movie_pick - 1));
    }while(i == 0);
    
    screen_clear();
    if(movie_pick > 0){
        weight_genre(show_five_movie_arr[movie_pick - 1], config);
    }
}

int print_info(struct movie movie, setting *config, int movie_pick)
{
    int user_input;
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Scifi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};
    char *service_array[] = {"Netflix", "DRTV","HBO Max", "Disney+", 
                            "TV2 Play", "SkyShowtime", "Filmstriben", "Viaplay", 
                            "C more", "Amazon Prime", "Rakuten"};
    do{
        screen_clear();
        printf("=== Movie info ===\n\n");
        printf("Title:           %s\n", movie.title);
        printf("Year of release: %d\n",movie.year);
        printf("PG-rating:       %s\n", movie.pg);
        printf("Runtime:         %d min\n", movie.runtime);
        printf("Genre(s):       ");
        for(int i = 0; i < MAX_GENRES; i++){
            if(movie.genre[i] == 1){
                printf(" %s", genre_array[i]);
            }
        }
        printf("\n");
        printf("IMDB rating:     %d/100\n\n", movie.score);
        printf("Resume:\n%s\n\n", movie.resume);
    
        printf("Avaliable on the following services:\n");
        for(int i = 0; i < MAX_SERVICES; i++){
            if(movie.services[i] == 1){
                printf(" --> %s\n", service_array[i]);
            }
        }
        printf("\n");
        printf("======================================\n");
        printf("Type 1 to watch\n");
        printf("Type 2 to explain this recommendation\n");
        printf("Type 0 to return to recommendations\n");
        printf("======================================\n");
        user_input = scanf_for_int(0, 2);
    
        if(user_input == 2){
            explain(movie, config, genre_array, movie_pick);
        }
    }while (user_input > 1 || user_input < 0);

    if(user_input == 1){
        return user_input;
    }
    return 0;
}

void explain(struct movie movie, setting *config, char *genre_array[], int movie_pick)
{
    screen_clear();
    int user_input;
    printf(" === Recommendation Explanation ===\n\n");
    if(movie_pick < 3){
        printf("%swas recommended", movie.title); 
        printf(" based on your genre preferences and/or previously watched titles.\n\n");
    
        printf("This movie had the following genre(s) with individual weighting(s):\n");
        for(int i = 0; i < MAX_GENRES; i++){
            if(movie.genre[i] == 1){
                printf("%s: %d\n", genre_array[i], config[STREAM_SERVICE_COUNT + SETTING_COUNT + i].value);
            }
        }
        printf("This means your collected genre score for this movie is: %.2f\n\n", movie.genre_score);

        printf("The collected genre score was calculated with:");
        for(int i = STREAM_SERVICE_COUNT; i < STREAM_SERVICE_COUNT + SETTING_COUNT; i++){
            if(config[i].value == 1){  
                printf(" %s \n", config[i].key);
                break;
            }
        }
        printf("This score is calculated from your genre weigts, the amount of\n");
        printf("genre on the movie and your prefered choice of scaling.\n");
        printf("You can read more about your scaling options in the setting menu.\n");
    }
    else{
        printf("%swas selected randomnly.\n", movie.title); 
        printf("This way, you will be presented to movies,\n");
        printf("that can help you expand your horizon but\n");
        printf("also prevent you from entering filter bubbles.\n");
    }

    do{
        printf("\nEnter 0 to return:\n");
        user_input = scanf_for_int(0,0);
    }while(user_input != 0); 
    //if this is zero is shuld return to movie info page
}
