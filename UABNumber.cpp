#include <stdio.h>

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

int main() {
    // Variable to store user input
    int userNumber;

    // Ask the user to enter an integer
    printf("Enter an integer: ");
    scanf("%d", &userNumber);

    // Call the isUABNumber function and print the result as true or false
    printf("%s\n", isUABNumber(userNumber) ? "True" : "False");

    return 0;
}

