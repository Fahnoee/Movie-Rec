// Program running the best movie recommender in the world

// ######################
// ###### libraries #####
// ######################
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int scifi;
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
void change_service();
void printMenu();
int is_element_in_array(int x, int arr[], int arrayLength);
void import_movies(int movie_array[]);

// ##########################
// ###### Global Values #####
// ##########################
availableServices streamingServices[11] = {
    {"netflix", 0},
    {"drtv", 0},
    {"hbo", 0},
    {"disney", 0},
    {"tv2play", 0},
    {"skyshowtime", 0},
    {"filmstriben", 0},
    {"viaplay", 0},
    {"cmore", 0},
    {"amazone_prime", 0},
    {"rakuten", 0}};

//////////////
/////MAIN/////
//////////////
void main(void)
{
    int running = 1;

    system(CLEAR_SCREEN);

    while (running)
    {
        printMenu();
    }
}

// Function for welcomming the new user
void welcome()
{
    printf("\nHey mate, welcome to this movie recommender\n");
    printf("\n");
}

// ########################### // Go from global variable to pointers
// ###### Menu functions #####
// ###########################
void printMenu()
{
    // Integer value for selecting menu option
    int selection;
    void (*arrayOfFunctions[])() = {adjust_s_services, adjust_s_services, adjust_s_services, adjust_s_services};
    int menuOption[] = {1, 2, 3, 4};
    int arrayMenuLength = 4;

    // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: EXIT\n");

    scanf("%d", &selection);

    if (is_element_in_array(selection, menuOption, arrayMenuLength))
    {
        arrayOfFunctions[selection - 1]();
    }
    else
    {
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

// Function for adjusting available streaming services
void adjust_s_services()
{
    system(CLEAR_SCREEN);
    print_services();
    change_service();
    system(CLEAR_SCREEN);
}

// function for printing what is available at the moment
void print_services()
{
    printf("\nCurrently you have the following streaming services available:\n");

    // Print available streaming services and whether you have them or not
    for (int i = 0; i < STREAM_SERVICE_COUNT; i++)
    {
        if (streamingServices[i].toggle == 1)
        {
            printf("%d: \"%s\" is Active\n", i + 1, streamingServices[i].service);
        }
        else
        {
            printf("%d: \"%s\" is Not Active\n", i + 1, streamingServices[i].service);
        }
    }
}

void change_service()
{
    int numberChoice;
    // Ask user which streaming service they want to activate/deactivate
    printf("\nWhich streaming service do you want to activate/deactivate?\n");
    printf("If you dont wanna change any press -1.\n");
    printf("Enter number:\n");

    scanf("%d", &numberChoice);

    if (numberChoice == -1)
    {
        return; // Går tilbage til while loopet
    }
    else if (numberChoice >= 0 && numberChoice <= 11)
    {
        numberChoice--; // Skal minus med en da arrayet starter på 0 og menuen starter på 1
        // change the value of the streaming service
        if (streamingServices[numberChoice].toggle == 1)
        {
            streamingServices[numberChoice].toggle = 0;
        }
        else
        {
            streamingServices[numberChoice].toggle = 1;
        }
    }
    else
    {
        printf("Invalid input! We try again\n");

        adjust_s_services();
    }
}

// ####################################
// ###### File handling functions #####
// ####################################

/*
void run()
{
    movie_array[MAX_MOVIES];

    import_movies(movie_array);
}

void import_movies(int movie_array[])
{

    FILE *f = fopen("movies.txt", "r");
    if (f == NULL)
    {
        printf("Det mislykkedes at aabne tekstfilen.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_MOVIES; i++)
    {

        fscanf(f, "%d;%s;%d;%d;%struct;%d;%s;%struct", &movie_array.);
    }

    f(close);
}

match import_matches(FILE *f, movie_array[])
{

    for (int i = 0; i < MAX_GAMES; i++)
    {
        fscanf(f, "%d;%s;%d;%d;",
               &movie[i].id,
               movie[i].title,
               &movie[i].pg,
               &movie[i].runtime);

        % struct

            fscanf(f, ";%d;%s;",
                   &movie[i].score, movie[i].resume);

        % struct
    }
}

import_genre(FILE *f, int movie_array[]){
    fscanf(f, % s)}

import_services(FILE *f, int movie_array[])

*/