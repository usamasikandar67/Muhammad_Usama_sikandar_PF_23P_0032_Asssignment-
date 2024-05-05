#include<stdio.h>

int collatz_sequence_length(int number) {
    int length = 1;  // Initialize length to 1 because we count the initial number
    while(number != 1) {
        if(number % 2 == 0) {
            number = number / 2;
        } else {
            number = (number * 3) + 1;
        }
        length++;
    }
    return length;
}

void max_length_collatz(int n) {
    int starting_number;
    int length;
    int maximum_length = 0;
    int j = 2;
    
    while(j < n) {
        length = collatz_sequence_length(j);
        if(maximum_length < length) {
            maximum_length = length;
            starting_number = j;
        }
        j++;
    }
    printf("The length of the largest sequence is %d for number %d \n", maximum_length, starting_number);
}

int main() {
    int n;
    printf("Enter the number: \n");
    scanf("%d", &n);
    max_length_collatz(n);
    
    return 0;
}
