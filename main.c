#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// prototyper

void main(void)
{
    int available_s[11] = {1,1,1,1,1,1,1,1,1,1,1};
}

// main menu
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
void adjust_s_services(int * available_s) {
    printf("Currently yo");
}




// datasaet
