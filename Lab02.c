#include <stdio.h>
void insertion(int sp[], int n) {    // insertion function
    int b = 1,l;
    while (b < n) {
        int val = sp[b];
        for (l= b - 1 ; l >= 0 && sp[l] > val ; l--) {
            sp[l + 1] = sp[l];
        }
        sp[l + 1] = val;
        b++;
    }
}
// Main function 
int main() {
    int z;
    // Enter the number of array elements
    printf("Enter the number of array elements: ");
    scanf("%d", &z);
    int sp[n];
    // Reading the array elements
    printf("Enter %d elements:\n", z);
    int f=0;
    while(f<z)
    {
        scanf("%d", &sp[f]);
        f++;
    }
    // initiating the insertion sorting
    insertion(sp, z);
    // Printing the sorted array
    printf("Sorted array:");
    printf("\n");
    int h=0;
    do{
        printf("%d ", sp[h]);
        h++;
    }
        while(h<z);
    printf("\n");

    return 0;
}

