#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MOVIES 1000

// prototyper
void import_movies(int movie_array[]);


// Mangler muligvis nogle genrer
struct genre{
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

struct services{
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

struct movie{
    int id;
    char title[50];
    int pg;
    int runtime;
    struct genre genre;
    int score;
    char resume[250];
    struct services services;
};

void main(void)
{
    ()
}

run()
{
    movie_array[MAX_MOVIES];

    import_movies(movie_array);
}


void import_movies(int movie_array[]){

    FILE *f = fopen("movies.txt", "r");
    if (f == NULL){
        printf("Det mislykkedes at aabne tekstfilen.\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < MAX_MOVIES; i++){
        
        fscanf(f, "%d;%s;%d;%d;%struct;%d;%s;%struct", &movie_array. );
    }
    

    f(close);
}

match import_matches(FILE *f, movie_array[])
{

    for(int i = 0; i < MAX_GAMES; i++)
    {
        fscanf(f, "%d;%s;%d;%d;",  
                &movie[i].id,
                movie[i].title,
                &movie[i].pg,
                &movie[i].runtime); 
                
        fscanf(f, "%d;", &movie[i].genre.
        
        fscanf(f, ";%d;%s;", 
        &movie[i].score, movie[i].resume);
        
        %struct
    }
}

import_genre(FILE *f, int movie_array[]){
    fscanf(f, %s)
}

import_services(FILE *f, int movie_array[])






// main menu

// datasaet


