#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 9

int input_array[ARRAY_SIZE] = {7, 2, 1, 3, 8, 4, -5, 6, 9};
int output_array_1[ARRAY_SIZE];
int output_array_2[ARRAY_SIZE];

void* calculate_sum_plus(void* arg) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += input_array[i];
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        output_array_1[i] = sum + input_array[i];
    }
    return NULL;
}

void* calculate_sum_minus(void* arg) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += input_array[i];
    }
    for (int i = 0; i < ARRAY_SIZE; i++) {
        output_array_2[i] = sum - input_array[i];
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, calculate_sum_plus, NULL);
    pthread_create(&thread2, NULL, calculate_sum_minus, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Output Array 1 (sum + array[i]):\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", output_array_1[i]);
    }
    printf("\n");

    printf("Output Array 2 (sum - array[i]):\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", output_array_2[i]);
    }
    printf("\n");

    return 0;
}

