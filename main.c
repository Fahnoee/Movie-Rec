// Program running the best movie recommender in the world

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

// ###########################
// ###### Structs #####
// ###########################
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
    char service[50];
    int toggle;
} availableServices;


// #######################
// ###### Prototypes #####
// #######################
void welcome();
void adjust_s_services();
void print_services();
int change_service();
void printMenu();
int is_element_in_array(int x, int arr[], int arrayLength);
void quit_function();
void import_movies(int movie_array[]); // Husk lige at tilføj den igen


// ##########################
// ###### Global Values #####
// ##########################
availableServices streamingServices[11] = {
    {"Netflix", 0},
    {"DRTV", 0},
    {"HBO max", 0},
    {"Disney+", 0},
    {"TV2play", 0},
    {"SkyShowtime", 0},
    {"Filmstriben", 0},
    {"Viaplay", 0},
    {"Cmore", 0},
    {"Amazone Prime", 0},
    {"Rakuten", 0}};


//////////////
/////MAIN/////
//////////////
void main(void)
{
    int running = 1;

    system(CLEAR_SCREEN);

    while (running){
        printMenu();
    }
}

// Function for welcomming the new user
void welcome()
{
    printf("\nHey mate, welcome to this movie recommender\n");
    printf("\n");
}

// ########################### 
// ###### Menu functions #####
// ###########################

void printMenu()
{
    // Integer value for selecting menu option
    int selection;
    void (*arrayOfFunctions[])() = {adjust_s_services, adjust_s_services, adjust_s_services, quit_function};
    int menuOption[] = {1, 2, 3, 4};
    int arrayMenuLength = 4;

    // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: Change preferences\n");
    printf("4: EXIT\n");

    scanf("%d", &selection);

    if (is_element_in_array(selection, menuOption, arrayMenuLength)) {
        arrayOfFunctions[selection - 1]();
    }
    else {
        printf("Invalid input!");
    }
}

// Function to check if x is in array
int is_element_in_array(int x, int arr[], int arrayLength)
{
    for (int i = 0; i < arrayLength; i++)
    {
        if (arr[i] == x)
        {
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
}

// Function for printing what is available at the moment
void print_services()
{
    printf("\nCurrently you have the following streaming services available:\n");

    // Print available streaming services and whether you have them or not

    for (int i = 0; i < STREAM_SERVICE_COUNT; i++) {
        if (streamingServices[i].toggle == 1) {
            printf("%d: \"%s\" is Active\n", i + 1, streamingServices[i].service);
        }
        else {
            printf("%d: \"%s\" is Not Active\n", i + 1, streamingServices[i].service);
        }
    }
}

int change_service()
{
    int numberChoice;
    // Ask user which streaming service they want to activate/deactivate
    printf("\nWhich streaming service do you want to activate/deactivate?\n");
    printf("If you dont wanna change any press 0.\n");
    printf("Enter number:\n");

    scanf("%d", &numberChoice);

    if (numberChoice == 0) {
        return 0; 
    }
    else if (numberChoice >= 0 && numberChoice <= 11) {
        numberChoice--; // Needs to be 1 less then input due to arrays starting at 0
        // change the value of the streaming service
        if (streamingServices[numberChoice].toggle == 1) {
            streamingServices[numberChoice].toggle = 0;
        }
        else {
            streamingServices[numberChoice].toggle = 1;
        }
    }
    else {
        printf("Invalid input! We try again\n");


        return 1;
    }
}

// Function for quiting the program
void quit_function()
{
    system(CLEAR_SCREEN);
    printf("You have choosen to exit our program, we hope you have a good\n");
    printf("time with the recommended movie :D\n");
    exit(EXIT_FAILURE);
}   


// ####################################
// ###### File handling functions #####
// ####################################


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

