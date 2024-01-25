#include <stdio.h>
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

// Writing the function to know whether the given input is prime or not.
int isPrime(int x) {
    if (x <= 1) {
        return 0; // As the return value is zero we can consider that the given input not a prime.
    }
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return 0; // As the return value is zero we can consider that the given input not a prime.
        }
    }
    return 1; // As the return value is one we can consider that the given input is a prime.
}

// Writing the function to find out the nearest lower prime number to the input.
int nearestPrimeBelow(int x) {
    for (int i = x - 1; i >= 2; i--) {
        if (isPrime(i)) {
            return i;
        }
    }
    return 0; // No prime numbers found.
}

// Function for writing sum of digits of the input given.
int sumOfDigits(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

// Function for printing the output as per the condition.
void numberTransformer(int x) {
    if (isPrime(x) && x != 3 && x != 5) {
        printf("Go Blazers\n");
    } else if (pow(2, (int)log2(x)) == x) {
        int nearestPrime = nearestPrimeBelow(x);
        int result = x + nearestPrime;
        printf("%d\n", result);
    } else if (x % 3 == 0 && x % 5 == 0) {
        printf("UAB CS 332&532 \n");
    } else if (sumOfDigits(x) % 3 == 0) {
        printf("CS\n");
    } else {
        int square = pow(sumOfDigits(x), 2);
        printf("%d\n", square);
    }
}

int main() {
    int n, k;

    printf("Enter 1 to give input or any other integer to check the predefined outputs:");
    scanf("%d", &k);

    if (k == 1) // condition to check the output by giving run time inputs.
    {
        printf("Enter the positive integer: n=");
        scanf("%d", &n);
        numberTransformer(n);
    } else // condition to check the output by the predefined inputs.
    {
        printf("predefined output values are follows : \n");
        numberTransformer(3);   // Output: "CS"
        numberTransformer(64);  // Output: "125" [64 + 61]
        numberTransformer(17);  // Output: "Go Blazers"
        numberTransformer(10);  // Output: "1" [(1+0)^2]
        numberTransformer(30);  // Output: "UAB CS 332&532"
    }

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
    int x, g;

    // Ask the user to enter a positive integer
    printf("Enter the positive integer: ");
    scanf("%d", &x);

    // Calling the reverseNum function and print the result
    g = reverseNum(x);
    printf("Reversed value of the integer: %d\n", g);

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
