#include <stdio.h>
#include<conio.h>
// Function to count the number of integers in the array smaller than their index
int smallerThanIndex(int numbers[]) {
    int count = 0;

    // Iterate through the array
    for (int i = 0; i < 5; i++) {
        // Check if the value is smaller than its index
        if (numbers[i] < i) {
            count++;
        }
    }

    return count;
}

int main() {
    // Declare an array of 5 integers
    int numbers[5];

    // Ask the user to enter 5 integers
    printf("Enter 5 integers:\n");
    for (int i = 0; i < 5; i++) {
        printf("Number %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Call the smallerThanIndex function and print the result
    int result = smallerThanIndex(numbers);
    printf("Number of integers smaller than their index: %d\n", result);

    return 0;
}

