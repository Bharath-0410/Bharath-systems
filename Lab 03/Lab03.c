#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion(char *sp[], int n) {
    int b, l;
    for (b = 1; b < n; b++) {
        char *val = sp[b];
        for (l = b - 1; l >= 0 && strcmp(sp[l], val) > 0; l--) {
            sp[l + 1] = sp[l];
        }
        sp[l + 1] = val;
    }
}

void readStrings(char *sp[], int n) {
    printf("Enter %d strings:\n", n);
    for (int i = 0; i < n; i++) {
        char buffer[100]; // Adjust the size based on your requirements
        scanf("%s", buffer);
        sp[i] = strdup(buffer);
    }
}

void displayStrings(char *sp[], int n) {
    printf("Sorted strings:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", sp[i]);
    }
}

int main() {
    int z;
    // Enter the number of array elements
    printf("Enter the number of array elements: ");
    scanf("%d", &z);

    char *sp[z]; // Declare an array of character pointers

    // Reading the array elements (strings) and allocating memory dynamically
    readStrings(sp, z);

    // Initiating the insertion sorting
    insertion(sp, z);

    // Displaying the sorted strings
    displayStrings(sp, z);

    // Freeing the dynamically allocated memory
    for (int i = 0; i < z; i++) {
        free(sp[i]);
    }

    return 0;
}
