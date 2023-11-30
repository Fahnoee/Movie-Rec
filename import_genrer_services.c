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

int import_genre(FILE *f);
void import_movies(struct movie movie_array[]);

struct movie
{
    int id;
    char title[50];
    int year;
    int pg;
    int runtime;
    int genre[20]; //måske mindre
    int score;
    char resume[250];
    int services[11];
};



int main (void)
{
    struct movie movie_array[MAX_MOVIES];

    
    import_movies;


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

        fscanf(f, "%d;%s;(%d);%d;%d min;",  
                &movie_array[i].id,
                movie_array[i].title,
                &movie_array[i].year,
                &movie_array[i].pg,
                &movie_array[i].runtime); 
                
                int genre[] = import_genre(f);
                
    for(int j = 0; j < MAX_GENRES; j++){
        movie_array[i].genre[j] = genre[j];
        }
        
        fscanf(f, ";%d;%s;", 
        &movie_array[i].score, movie_array[i].resume);
    
        //import service struct
    }
}

int import_genre(FILE *f)
{
    struct movie movie;
    char *one[10];
    char *two[10];
    char *three[10];
    char genre_array[] = { "Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Sci_fi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};


    fscanf(f, "%s, %s, %s", one, two, three);
    

        // Initialize movie.genre array to 0
        for(int i = 0; i < MAX_GENRES; i++)
        {
                movie.genre[i] = 0;
        }

        //Compare first genre n .csv to list of genres:: genre_array[]
        for(int i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(one, genre_array[i]) == 0)
            {
                movie.genre[i] = 1;
                break;
            }
        }

        for(int i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(two, genre_array[i]) == 0)
            {
                movie.genre[i] = 1;
                break;
            }
        }

        for(int i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(three, genre_array[i]) == 0)
            {
                movie.genre[i] = 1;
                break;
            }
        }


        for(int i = 0; i < MAX_GENRES; i++){
            printf(" %d", movie.genre[i]);
        }

    return movie.genre;
}

// 0;The Shawshank Redemption (1994);R;142 min;Drama;93;80;Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.;Director: Frank Darabont | Stars: Tim Robbins, Morgan Freeman, Bob Gunton, William Sadler;Votes: 2,295,987 | Gross: $28.34M;0;;0;0;0;0;1;1;0;0;0;0;