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

        fscanf(f, "%d; %[^(] (%d);%[^;];%d min",  
                &movie.id,
                movie.title,
                &movie.year,
                movie.pg,
                &movie.runtime); 
            printf(" \n ID: %d \n TITLE: %s \n YEAR: %d \n PG: %s \n RUNTIME: %d ",movie.id, movie.title, movie.year, movie.pg, movie.runtime);

            import_genre(f, movie.genre);
                
                //int genre[] = import_genre(f);
            //import_genre(f, movie_array[i].genre);
        
        fscanf(f, "%d; %[^;];", &movie.score, movie.resume);


        for(int j = 0; j < MAX_GENRES; j++){
            fscanf(f, "%d;", &movie.services[j]); //Import service
        }
        
        fscanf(f, "\n"); //Next line

        return movie;
}

void import_genre(FILE *f, int genre[])
{
    char one[20] = "";
    char two[20] = "";
    char three[20] = "";
    char buffer; 
    //char buffer1, buffer2;
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Sci_fi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};


    fscanf(f, "%[A-Za-z]%c", one, &buffer);
        if(buffer == ','){
            fscanf(f, "%[A-Za-z]%c", two, &buffer);
            if(buffer == ','){
                fscanf(f, "%[A-Za-z]", three);
            }
        }
    fscanf(f, ";");
        

    printf("GENRE 1: %s GENRE: 2 %s GENRE: 3 %s \n", one, two, three);
    
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
// 0;The Shawshank Redemption (1994);R;142 min;Drama;93;80;Two imprisoned men bond over a number of years, finding solace and eventual redemption through acts of common decency.;Director: Frank Darabont | Stars: Tim Robbins, Morgan Freeman, Bob Gunton, William Sadler;Votes: 2,295,987 | Gross: $28.34M;0;;0;0;0;0;1;1;0;0;0;0;