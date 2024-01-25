#include <stdio.h>
#include<conio.h>
// Function to print details of an array
void arrayDetails(int arr[]) {
    // Variables to store details
    int minVal = arr[0];
    int minIndex = 0;
    int maxVal = arr[0];
    int maxIndex = 0;
    double sum = arr[0];

    // Find minimum and maximum values along with their indices
    for (int i = 1; i < 6; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIndex = i;
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            maxIndex = i;
        }
        sum += arr[i];
    }

    // Calculate mean
    double mean = sum / 6.0;

    // Print the details
    printf("Minimum Value: %d\n", minVal);
    printf("Minimum Value Index: %d\n", minIndex);
    printf("Mean: %.2lf\n", mean);
    printf("Maximum Value: %d\n", maxVal);
    printf("Maximum Value Index: %d\n", maxIndex);
}

int main() {
    // Declare an array of 6 integers
    int arr[6];

    // Ask the user to enter 6 integers
    printf("Enter the 6 elements of the array:\n");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &arr[i]);
    }

    // Call the arrayDetails function
    arrayDetails(arr);

    return 0;
}

