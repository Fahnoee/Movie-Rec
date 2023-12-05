
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

int check_for_genre(int movie_done[], struct movie movie_array[], 
                struct movie your_movies[], int genre, int h);
/*void write_config_genre(setting *key_value_pair, int genre[]);
void read_config_genre(setting * config, int genre[]);*/
void genre_menu(int genre[], struct movie movie_array[], int movie_done[], struct movie your_movies[]);


int genre_main(struct movie movie_array[], int genre[]){
    struct movie your_movies[MAX_MOVIES];
    int movie_done[MAX_MOVIES];

    for (int i = 0; i < MAX_MOVIES; i++)
    {
        movie_done[i] = 0;
    }
     
    genre_menu(genre, movie_array, movie_done, your_movies);


    /*for(int j = 0; j < MAX_MOVIES; j++){
        printf("  TITLE %d: %s \n", j, your_movies[j].title);
    }
*/
        //write_config()

    return 0;
}


int check_for_genre(int movie_done[], struct movie movie_array[],  //Checks if the movie already has been selected for your_movies[]
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

/*void write_config_genre(setting *key_value_pair, int genre[])
{
    FILE *config_file;                    // Creates pointer to file
    config_file = fopen("conf.txt", "w"); // Opens file
    check_file_opening(config_file);      // Checks if it is read correctly

    for (int i = 0; i < MAX_GENRES; i++) { // Forloop that writes the config file
        fprintf(config_file, "genre: %d=%d \n", i, genre[i]);
    }

    fclose(config_file); // Close file
}*/

// Function for reading a config, used to save available streaming servives
/*void read_config_genre(setting * config, int genre[])
{
    FILE *file;
    file = fopen("conf.txt", "r");
    if (file == NULL) {                         // In case of first opening of program the config will be missing
        write_config(config); // Here a config is writting from the global variable.

        file = fopen("conf.txt", "r"); // Re-open the file after creating it
        check_file_opening(file);
    }

    for (int i = 0; i < MAX_GENRES; i++) {
        fscanf(file, "%[^=]=%d ", &genre[i]);
    }
    fclose(file);
}*/

void genre_menu(int genre[], struct movie movie_array[], int movie_done[], struct movie your_movies[])

{
    int place;
    do{
        system(CLEAR_SCREEN);
        printf("Choose your genres: \n");

        printf(" 1.  Action:    [%d]\n", genre[0]);

        printf(" 2.  Adventure: [%d]\n",  genre[1]);

        printf(" 3.  Drama:     [%d]\n", genre[2]);

        printf(" 4.  Crime:     [%d]\n", genre[3]);

        printf(" 5.  Romance:   [%d]\n", genre[4]);

        printf(" 6.  Fantasy:   [%d]\n", genre[5]);

        printf(" 7.  Mystery:   [%d]\n", genre[6]);

        printf(" 8.  Music:     [%d]\n", genre[7]);

        printf(" 9.  Sport:     [%d]\n", genre[8]);

        printf(" 10. Animation: [%d]\n", genre[9]);

        printf(" 11. Biography: [%d]\n", genre[10]);

        printf(" 12. History:   [%d]\n", genre[11]);

        printf(" 13. Scifi:     [%d]\n", genre[12]);

        printf(" 14. War:       [%d]\n", genre[13]);

        printf(" 15. Family:    [%d]\n", genre[14]);

        printf(" 16. Thriller:  [%d]\n", genre[15]);

        printf(" 17. Horror:    [%d]\n", genre[16]);

        printf(" 18. Comedy:    [%d]\n", genre[17]);
 
        printf(" 19. Western:   [%d]\n", genre[18]);

        printf(" 20. Musical:   [%d]\n", genre[19]);
 
        printf("\nSelect a genre: ");
        scanf(" %d", &place);
    
        do{
            printf("Assign preference from 1-10 ");
            scanf(" %d", &genre[place - 1]);
        }while(genre[place - 1] > 10 || genre[place - 1] < 0);

        if(genre[place - 1] == 0){
            system(CLEAR_SCREEN);
            break;
        }
    }while (genre[place - 1] > 0);

    int h = 0;
    for(int j = 0; j < MAX_GENRES; j++){
        if(genre[j] > 0){
            h = check_for_genre(movie_done, movie_array, your_movies, j, h);
        }
    }
}
