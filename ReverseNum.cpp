#include <stdio.h>
#include<conio.h>
// writing the function to reverse the order of digits in a number
int reverseNum(int z) {
    int reverse = 0;

    //logic for  Reversing the digits
    while (z > 0) {
        int digit = z % 10;
        reverse =reverse * 10 + digit;
        z /= 10;
    }

    return reverse;
}

int main() {
    // Variable to store the run time input. 
    int x,k;

    // Ask the user to enter a positive integer
    printf("Enter the positive integer: ");
    scanf("%d", &x);

    // Calling the reverseNum function and print the result
    k=reverseNum(x);
    printf("Reversed value of the integer: %d", k);

    return 0;
}
