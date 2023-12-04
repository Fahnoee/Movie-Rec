#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MOVIES 90
#define MAX_GENRES 20
#define MAX_SERVICES 12

struct movie
{
    int id;
    char title[50];
    int year;
    char pg[20];
    int runtime;
    int genre[20]; //måske mindre
    int score;
    char resume[250];
    int services[11];
};

void print_movie(struct movie movie);
void import_genre(FILE *f, int genre[]);
struct movie import_movies(FILE *f);

int fscanf_main (void)
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

void print_movie(struct movie movie){
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Scifi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};

    printf("\nID: %d\nTITLE: %s\nYEAR: %d\nPG: %s\nRUNTIME: %d\nSCORE: %d\nRESUME: %s\nSERVICES: %d\n", movie.id, movie.title, movie.year, movie.pg, movie.runtime, movie.score, movie.resume, movie.services[6]);
    
    printf("GENRE:\n");
    for(int i = 0; i < MAX_GENRES; i++){
        printf("%s: %d\n", genre_array[i], movie.genre[i]);
    }

}

struct movie import_movies(FILE *f)
{
      struct movie movie;
      char str[3];

        fscanf(f, "%d;%[^(](%d);%[^;];%d min;",  
                &movie.id,
                movie.title,
                &movie.year,
                movie.pg,
                &movie.runtime);
        
            import_genre(f, movie.genre);   
        
        fscanf(f, "%d;%[^;];", &movie.score, movie.resume);

        for(int j = 0; j < MAX_SERVICES; j++){
            fscanf(f, "%d;", &movie.services[j]); //Import service
        }

        return movie;
}

void import_genre(FILE *f, int genre[])
{
    char one[20] = "";
    char two[20] = "";
    char three[20] = "";
    char buffer = 'p'; 
    int i = 0;
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Scifi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};


    fscanf(f, "%[A-Za-z]%c", one, &buffer);
        if(buffer == ','){
            fscanf(f, " %[A-Za-z]%c", two, &buffer);
                if(buffer == ','){
                    fscanf(f, " %[A-Za-z];", three);
                }
                else{
                fscanf(f, ";");
                }
        }
        else{
            fscanf(f, ";");
        }
    
        for(i = 0; i < MAX_GENRES; i++)
        {
                genre[i] = 0;
        }

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
}
