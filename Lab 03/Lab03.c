#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Insertion fucnction created. 
// here the function implements the insertion algorithm on the array of strings. 
// here we use Strcmp to compare the strings. 
void insertion(char *sp[], int n) {
    int x, y;
    for (x = 1; x < n; x++) {
        char *val = sp[x];
        for (y = x - 1; y >= 0 && strcmp(sp[y], val) > 0; y--) {
            sp[y + 1] = sp[y];
        }
        sp[y + 1] = val;
    }
}


// Function for readstrings created.
// this function is used to read the n number of strings created dynamically .  
void readStrings(char *sp[], int k) {
    printf("Enter %d strings:\n", k);
    for (int i = 0; i < k; i++) {
        char buffer[100]; // Adjust the size based on your requirements
        scanf("%s", buffer);
        sp[i] = strdup(buffer);
    }
}


// function for displaystrings created. 
// here this function helps in displaying the strings one by one.
void displayStrings(char *sp[], int l) {
    printf("Sorted strings:\n");
    for (int i = 0; i < l; i++) {
        printf("%s\n", sp[i]);
    }
}


// main funnction started.
// the main function is created by using the above mentioned functions. 
int main() {
    int z;
    // Enter the number of array elements
    printf("Enter the number of array elements: ");
    scanf("%d", &z); // reading the number of array elements 

    char *sp[z]; // Declare an array of character pointers

    // Reading the array elements (strings) and allocating memory dynamically
    readStrings(sp, z);

    // Initiating the insertion sorting for the given array. 
    insertion(sp, z);

    // Displaying the sorted strings 
    displayStrings(sp, z);

    // Freeing the dynamically allocated memory after finishing the insertion algorithm. 
    for (int i = 0; i < z; i++) {
        free(sp[i]);
    }

    return 0;
}
