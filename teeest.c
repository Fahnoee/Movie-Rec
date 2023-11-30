
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MOVIES 1000
#define MAX_GENRES 20

/*struct genre // Mangler muligvis nogle genrer
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
};*/

/*struct services
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
};*/



struct movie
{
    int id;
    char title[30];
    int year;
    char pg[20];
    int runtime;
    int genre[20]; //måske mindre
    int score;
    char resume[250];
    int services[11];
};


void import_genre(FILE *f, int genre[]);
struct movie import_movies(FILE *f);

int main (void)
{
    struct movie movie_array[MAX_MOVIES];
    
FILE *f = fopen("movies.txt", "r");
    if (f == NULL)
    {
        printf("FILE WAS NOT OPENED.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < MAX_MOVIES; i++){
        movie_array[i] = import_movies(f);
    }

    fclose(f);
}


struct movie import_movies(FILE *f)
{
      struct movie movie;

        fscanf(f, "%d, %[^(] (%d),%[^,],%d min",  
                &movie.id,
                movie.title,
                &movie.year,
                movie.pg,
                &movie.runtime); 
            printf(" \n ID: %d \n TITLE: %s \n YEAR: %d \n PG: %s \n RUNTIME: %d ",movie.id, movie.title, movie.year, movie.pg, movie.runtime);
                
                //int genre[] = import_genre(f);
            //import_genre(f, movie_array[i].genre);
        
        //fscanf(f, "%d;%s;", 
        //&movie_array[i].score, movie_array[i].resume);
    
        //import service struct

        return movie;
}

void import_genre(FILE *f, int genre[])
{
    char one[10];
    char two[10];
    char three[10];
    char buffer1, buffer2;
    char *genre_array[] = { "Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Sci_fi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};


    fscanf(f, "%c%[^,], %[^,], %[^]", buffer1, one, two, three, buffer2);
    
        int i = 0;
        // Initialize movie.genre array to 0
        for(i = 0; i < MAX_GENRES; i++)
        {
                genre[i] = 0;
        }

        //Compare first genre n .csv to list of genres:: genre_array[]
        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(one, genre_array[i]) == 0)
            {
                genre[i] = 1;
                break;
            }
        }

        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(two, genre_array[i]) == 0)
            {
                genre[i] = 1;
                break;
            }
        }

        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(three, genre_array[i]) == 0)
            {
                genre[i] = 1;
                break;
            }
        }


        for(i = 0; i < MAX_GENRES; i++){
            printf(" FISSE: %d %d",i, genre[i]);
        }
}