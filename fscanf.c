/* This code is a subsidiary c program that helps the main program read a given movie data set */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MOVIES 398
#define MAX_GENRES 20
#define MAX_SERVICES 11

struct movie                            //Movie struct, including every piece of info of a movie
{
    int id;
    char title[100];
    int year;
    char pg[20];
    int runtime;
    int genre[20];
    int score;
    char resume[1000];
    int services[11];
    double genre_score;
    int service_id;
};

/* Prototypes */
void print_movie(struct movie movie);
void import_genre(FILE *f, int genre[]);
struct movie import_movies(FILE *f);

                                        //Main fscanf.c function. Called in the main file on line 79
struct movie import_movies(FILE *f)     //File opened in main file on line 75
{
      struct movie movie;
      char str[3];

        fscanf(f, "%d;%[^(](%d);%[^;];%d min;", 
                &movie.id,              //Reads movie id, title, year, pg and runtime
                movie.title,
                &movie.year,
                movie.pg,
                &movie.runtime);
        
        import_genre(f, movie.genre);   //A seperate function that reads genres
        
        fscanf(f, "%d;%[^;];", &movie.score, movie.resume); //Reads imdb score and resume

        for(int j = 0; j < MAX_SERVICES - 1; j++){
            fscanf(f, "%d;", &movie.services[j]); //Reads which services - 1 the movie is available on
        }
        
        fscanf(f, "%d%*[^\n]", &movie.services[MAX_SERVICES - 1]); //Reads the last service and newline

        return movie; //Return the movie as a struct
}

void import_genre(FILE *f, int genre[]) //Function called on line 44 to read genres seperately
{
    char one[20] = "";
    char two[20] = "";
    char three[20] = "";
    char buffer = 'p'; 
    int i = 0;
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", //Genre array in order to string compare
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Scifi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};


    fscanf(f, "%[A-Za-z]%c", one, &buffer); //Reads first genre. If buffer character is "," it reads the next genre
        if(buffer == ','){
            fscanf(f, " %[A-Za-z]%c", two, &buffer); //Reads second genre and checks buffer again
                if(buffer == ','){
                    fscanf(f, " %[A-Za-z];", three); //Reads third genre and ";"
                }
                else{
                fscanf(f, ";"); //Reads ";" if there were two genres
                }
        }
        else{
            fscanf(f, ";"); //Reads ";" if there were one genre
        }
    
        for(i = 0; i < MAX_GENRES; i++)
        {
                genre[i] = 0; //Sets all genres in the given movie to 0
        }

        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(one, genre_array[i]) == 0) //String compare with genre array
            {
                genre[i] = 1; //Sets that genre to active on that movie is string compare returns true
                break;
            }
        }

        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(two, genre_array[i]) == 0) //String compare with second genre
            {                                    //Nothing happens if there was only one genre
                genre[i] = 1;
                break;
            }
        }

        for(i = 0; i < MAX_GENRES; i++)
        {
            if(strcmp(three, genre_array[i]) == 0) //String compare with third genre
            {                                      //Nothing happens if there was only one or two genres
                genre[i] = 1;
                break;
            }
        }
}