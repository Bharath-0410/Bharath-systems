#include <stdio.h>
#include<conio.h>
#include <math.h>

// writing the function to know whether the given iniput is prime or not. 
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

// writing the function to findout the nearest lower prime number to the input . 
int nearestPrimeBelow(int x) {
    for (int i = x - 1; i >= 2; i--) {
        if (isPrime(i)) {
            return i;
        }
    }
    return 0; // No prime numbers found. 
}

// function for writing sum of digits of the input given.
int sumOfDigits(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

// function for printing the output as per the condition. 
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
	
	
	int n,k;
	printf("Enter 1 to give input or any other integer to check the predefined outputs:");
	scanf("%d",&k);
	if(k==1) // condition to check the output by giving run time inputs. 
	{
		printf("Enter the positive integer: n=");
		scanf("%d",&n);
		numberTransformer(n);
	}
	else // condition to check the output by the predefined inputs. 
	{
		printf("predefined output values are follows : \n");
		numberTransformer(3);   // Output: "CS"
		numberTransformer(64);  // Output: "125" [64 + 61]
		numberTransformer(17);  // Output: "Go Blazers"
		numberTransformer(10);  // Output: "1" [(1+0)^2]
		numberTransformer(30);  // Output: "UAB CS 332&532"
	}
    

    return 0;
}


