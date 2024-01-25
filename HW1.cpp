#include <stdio.h>
#include <conio.h>
#include <math.h>

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

// Function to reverse the order of digits in a number
int reverseNum(int z) {
    int reverse = 0;

    // Logic for reversing the digits
    while (z > 0) {
        int digit = z % 10;
        reverse = reverse * 10 + digit;
        z /= 10;
    }

    return reverse;
}

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

// Function to check if a number is a UABNumber
int isUABNumber(int number) {
    // Variables to store the sum of divisors
    int sumOfDivisors = 0;

    // Iterate through potential divisors from 1 to number/2
    for (int divisor = 1; divisor <= number / 2; divisor++) {
        // Check if divisor is a divisor of number
        if (number % divisor == 0) {
            sumOfDivisors += divisor; // Add the divisor to the sum
        }
    }

    // Check if the sum of divisors is equal to the original number
    return (sumOfDivisors == number);
}

// Main function
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

    // Variable to store the runtime input
    int x, k;

    // Ask the user to enter a positive integer
    printf("Enter the positive integer: ");
    scanf("%d", &x);

    // Calling the reverseNum function and print the result
    k = reverseNum(x);
    printf("Reversed value of the integer: %d\n", k);

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

    // Variable to store user input
    int userNumber;

    // Ask the user to enter an integer
    printf("Enter an integer: ");
    scanf("%d", &userNumber);

    // Call the isUABNumber function and print the result as true or false
    printf("%s\n", isUABNumber(userNumber) ? "True" : "False");

    return 0;
}

