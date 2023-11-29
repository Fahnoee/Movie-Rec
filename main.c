//Program running the best movie recommender in the world

//Including of different liberieys
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Structs
typedef struct {
    int available_s[11];
} Settings;


// prototyper
void welcome();
void adjust_s_services(int * available_s);
void print_services(int * available_s);
void select_change(available_s);
void printMenu();
int is_element_in_array(int x, int arr[]);

//////////////
/////MAIN/////
//////////////
void main(void) {
    welcome();

    settings mySettings = {
        .available_s = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} 
    }


}

//menu
void printMenu() {
    // Integer value for selecting menu option
    int selection;
    int (*arrayOfFunctions[])() = {f1, f2, adjust_s_services, f4};
    int menuOption[] = {1, 2, 3};


    // Print menu options
    printf("== MENU ==\n");
    printf("1: Get a recommendation\n");
    printf("2: Adjust your streaming services\n");
    printf("3: EXIT\n");
    
    
    
    scanf("%d", &selection);
    
    if (is_element_in_array(selection, menuOption)) {
        arrayOfFunctions[selection]()
    } else {
        printf("Invalid input!")
    }
} 

// Function to check if x is in array
int is_element_in_array(int x, int arr[]) {
    int arrayLength = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arrayLength; i++) {
        if (arr[i] == x) {
            return 1;  // x found
        }
    }
    return 0;  // x not found
}


// Function for adjusting available streaming services
void adjust_s_services(int * available_s){
    print_services(available_s)
    select_change(available_s)

    printMenu();
}

// function for printing what is available at the moment
void print_services(int * available_s) {
    printf("\nCurrently you have the following streaming services available:\n");
    
    // Print available streaming services and whether you have them or not
    if (available_s[0] == 1){
    printf("0: Active: Netflix\n")}
    else {"0: Not active: Netflix\n"}
    
    if (available_s[1] == 1){
    printf("1: Active: DRTV\n")}
    else {"1: Not active: DRTV\n"}

    if (available_s[2] == 1){
    printf("2: Active: HBO Max\n")}
    else {"2: Not active: HBO max \n"}
    
    if (available_s[3] == 1){
    printf("3: Active: Disney+\n")}
    else {"3: Not active: Disney+\n"} 

    if (available_s[4] == 1){
    printf("4: Active: TV2 Play\n")}
    else {"4: Not active: TV2 Play\n"}

    if (available_s[5] == 1){
    printf("5: Active: SkyShowtime\n")}
    else {"5: Not active: SkyShowtime\n"}

    if (available_s[6] == 1){
    printf("6: Active: Viaplay\n")}
    else {"6: Not active: Viaplay\n"}

    if (available_s[7] == 1){
    printf("7: Active: Film Striben\n")}
    else {"7: Not active: Film Striben\n"}

    if (available_s[8] == 1){
    printf("8: Active: C-More\n")}
    else {"8: Not active: C-more\n"}
    
    if (available_s[9] == 1){
    printf("9: Active: Amazon Prime\n")}
    else {"9: Not active: Amazon Prime\n"}

    if (available_s[10] == 1){
    printf("10: Active: Rakuten\n")}
    else {"10: Not active: Rakuten\n"}

    int number_of_choice = 0;
}

void select_change(available_s){
    // Ask user which streaming service they want to activate/deactivate
    printf("\nWhich streaming service do you want to activate/deactivate?\n");
    printf("If you dont wanna change any press -1.\n");
    printf("Enter number:\n")

    scanf("%d", &number_of_choice);
    
    if (number_of_choice==-1){
        //to go main menu
        printMenu();
    }
    else if (number_of_choice>=0 && number_of_choice<=10){
        //change the value of the streaming service

        //to go main menu
        printMenu();
    }
    else {
        printf("Invalid input! We try again\n")
        //to go main menu

        adjust_s_services(available_s);
    }
    
}



// datasaet




//Function for welcomming the new user
void welcome(){
    printf("\nHey mate, welcome to this movie recommender\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
}
