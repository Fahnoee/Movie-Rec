#include<stdio.h>

void print_info(struct movie movie);

void select_movie(struct movie show_five_movie_arr[])
{
    
    int movie_pick = 0;
    printf("Type a movienumber to show information.\n\n");
    for(int i = 0; i < 5; i++){
        printf("Movie %d: '%s'\n", i, show_five_movie_arr[i].title);
    }   
    scanf(" %d", &movie_pick);
    movie_pick -= 1;

    print_info(show_five_movie_arr[movie_pick]);
}   

void printf_info(struct movie movie)
{
    char *genre_array[] = {"Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Scifi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};
    char *service_array[] = {"Netflix", "DRTV","HBO Max", "Disney +", 
                            "TV2 Play", "SkyShowtime", "Filmstriben", "Viaplay", 
                            "C more", "Amazon Prime", "Rakuten"};
    
    
    printf("Year of release: %d\n",movie.year);
    printf("PG-rating: %s\n", movie.pg);
    printf("Runtime: %d\n", movie.runtime);
    printf("IMDB rating: %d", );
    printf(" Resume: %s", mo)

    printf("Genres:");
    for(int i = 0; i < MAX_GENRES; i++){
        if(movie.genre[i] == 1){
            printf(" %s", genre_array[i]);
        }
    }
    printf("\n");

    printf("Avaiable on the following services:");
    for(int i = 0; i < MAX_SERVICES; i++){
        if(movie.services[i] == 1){
            printf(" %s", genre_array[i]);
        }
    }
    printf("\n");
}