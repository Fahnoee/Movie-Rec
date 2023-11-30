Netflix=1=1 
DRTV=0=0 
HBO=1 
max=1=1 
Disney+=1=1 
TV2play=0=1 
SkyShowtime=1=1 
Filmstriben=1=1 
Viaplay=1=1 
Cmore=1=1 
Amazone=1 

void run()
{
    struct movie movie_array[MAX_MOVIES];

    import_movies(movie_array);
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

        fscanf(f, "%d;%s;%d;%d;",  
                &movie_array[i].id,
                movie_array[i].title,
                &movie_array[i].pg,
                &movie_array[i].runtime); 
                
        //import genre struct
        
        fscanf(f, ";%d;%s;", 
        &movie_array[i].score, movie_array[i].resume);
    
        //import service struct
    }
}

import_genre(FILE *f, int movie_array[]){

    char *1[10];
    char *2[10];
    char *3[10];
    char genre_array[] = { "Action", "Adventure","Drama", "Crime", 
                            "Romance", "Fantasy", "Mystery", "Music", 
                            "Sport", "Animation", "Biography", "History", 
                            "Sci_fi", "War", "Family", "Thriller", "Horror", 
                            "Comedy", "Western","Musical"};

    fscanf(f, "%s, %s, %s", 1, 2, genre_3 );

    for(int j = 0; i > 3; i++)
    {    
        for(int i = 0; i < (sizeof(genre_array))/sizeof(genre_array[0]); i++)
        {
            
            if(strcmp(j, genre_array[i]) = 0)
            {
                genre.action
            }
        }
    }




}


import_services(FILE *f, int movie_array[])
{

}

