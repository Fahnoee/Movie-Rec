#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nummer;
    char titel[100];
    char alders_rating[10];
    char spilletid[10];
    char genre[50];
    int score;
    char resume[500];
    int platforms[10]; // Assuming 10 platform columns in the CSV
} Movie;

Movie *movies = NULL; // Global array of movies
int movieCount = 0;   // Counter for the number of movies

void parseLine(char *line, Movie *movie) {
    char *token;

    // Parsing each column
    token = strtok(line, ";");
    movie->nummer = atoi(token);

    token = strtok(NULL, ";");
    strcpy(movie->titel, token);

    token = strtok(NULL, ";");
    strcpy(movie->alders_rating, token);

    token = strtok(NULL, ";");
    strcpy(movie->spilletid, token);

    token = strtok(NULL, ";");
    strcpy(movie->genre, token);

    token = strtok(NULL, ";");
    movie->score = atoi(token);

    token = strtok(NULL, ";");
    strcpy(movie->resume, token);

    // Parsing platforms (assuming 10 platforms)
    for (int i = 0; i < 10; i++) {
        token = strtok(NULL, ";");
        movie->platforms[i] = atoi(token);
    }
}

void readCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Unable to open file\n");
        return;
    }

    char buffer[1024];
    int row = 0;
    while (fgets(buffer, 1024, file)) {
        if (row == 0) {
            // Skipping the header row
            row++;
            continue;
        }

        movies = realloc(movies, (movieCount + 1) * sizeof(Movie));
        if (movies == NULL) {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }

        parseLine(buffer, &movies[movieCount]);
        movieCount++;

        row++;
    }
    fclose(file);
}

int main() {
    const char *filename = "path_to_your_csv_file.csv";
    readCSV(filename);

    // Example usage: Print details of each movie
    for (int i = 0; i < movieCount; i++) {
        printf("Movie: %s, Genre: %s, Score: %d\n", movies[i].titel, movies[i].genre, movies[i].score);
    }

    // Free the allocated memory
    free(movies);
    return 0;
}
