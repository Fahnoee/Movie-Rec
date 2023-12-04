void genre(struct movie your_movies[], struct movie movie_array[]);

int check_for_genre(int movie_done[], struct movie movie_array[], 
                struct movie your_movies[], int genre, int h);
int genre_main(struct movie movie_array[]){
    struct movie your_movies[MAX_MOVIES];
    int movie_done[MAX_MOVIES];
    int genre[20];

    for (int i = 0; i < MAX_MOVIES; i++)
    {
        movie_done[i] = 0;
        genre[i] = 0;
    }

    printf("Action, Adventure, Drama, Crime, "); 
    printf("Romance, Fantasy, Mystery, Music, ");   
    printf("Sport, Animation, Biography, History, ");
    printf("Scifi, War, Family, Thriller, Horror, ");
    printf("Comedy, Western, Musical");
    int h = 0; 
    do{
        scanf("%d\n", &genre[h]);
        h++;
    }while(h < MAX_GENRES);
    
    h = 0;
    for(int j = 0; j < MAX_GENRES; j++){
        if(genre[j] > 0){
            h = check_for_genre(movie_done, movie_array, your_movies, j, h);
        }
    }

    for(int j = 0; j < MAX_MOVIES; j++){
        printf("  TITLE %d: %s \n", j, your_movies[j].title);
    }
    return 0;
}


int check_for_genre(int movie_done[], struct movie movie_array[], 
                struct movie your_movies[], int genre, int h)
{
    
    for(int j = 0; j < MAX_MOVIES; j++){

        if(movie_array[j].genre[genre] > 0){
            if (movie_done[j] == 1){
                break;
            }
            else{
                your_movies[h] = movie_array[j];
                movie_done[j] = 1;
                h++;
            }  
        }
    } 
    return h;
}





