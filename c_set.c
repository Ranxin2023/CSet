#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_SIZE 100000
typedef struct int_set
{
    size_t size;
    int *arr;
} CINTSET;
CINTSET *initialize_int_set();
CINTSET *initialize_int_set_with_arr(int *arr, size_t size);
int compare(const void *a, const void *b);
void sort(CINTSET *s);
void append(CINTSET *s, int value);
int normal_find(int *arr, int size, int target);
int set_find(CINTSET *s, int target);

CINTSET *initialize_int_set()
{
    CINTSET *s = malloc(sizeof(CINTSET));
    s->size = 0;
    return s;
}
CINTSET *initialize_int_set_with_arr(int *arr, size_t size)
{
    CINTSET *s = malloc(sizeof(CINTSET));
    s->size = size;
    s->arr = malloc(sizeof(int) * size);
    memcpy(s->arr, arr, s->size);
    sort(s);
    return s;
}

int compare(const void *a, const void *b)
{
    int diff = *(int *)a - *(int *)b;
    return diff < 0 ? -1 : 1;
}

void sort(CINTSET *s)
{
    qsort(s->arr, s->size, sizeof(int), compare);
}

void append(CINTSET *s, int value)
{
    if (s->size == 0)
    {
        s->arr = malloc(sizeof(int));
        s->arr[0] = value;
        return;
    }

    s->arr = (int *)realloc(s->arr, sizeof(int) * (s->size + 1));
    s->arr[s->size] = value;
    s->size += 1;
}
int normal_find(int *arr, int size, int target)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            return 1;
        }
    }
    return 0;
}
int set_find(CINTSET *s, int target)
{
    int l = 0, r = s->size - 1;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        if (s->arr[m] == target)
        {
            return 1;
        }
        if (s->arr[m] < target)
        {
            l = m + 1;
        }
        else
        {
            r = m - 1;
        }
    }
    return 0;
}
void test1()
{
    // initialize an array with 10^5
    clock_t time_init_start = clock();
    int *arr = malloc(TEST_SIZE * sizeof(int));
    int *s_arr = malloc(TEST_SIZE * sizeof(int));
    // Check if allocation was successful
    if (!arr)
    {
        printf("Failed to allocate memory for arr");
        exit(EXIT_FAILURE);
    }
    if (!s_arr)
    {
        printf("Failed to allocate memory for arr");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    // printf("%d\n", RAND_MAX);
    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        int random_number = (rand() << 15) | rand();
        // printf("%d\n", random_number);
        s_arr[i] = random_number;
        arr[i] = random_number;
    }
    clock_t time_init_end = clock();
    double time_difference = (double)(time_init_end - time_init_start) / CLOCKS_PER_SEC;
    printf("time spent for initialize array with size %d:%f\n", TEST_SIZE, time_difference);

    CINTSET *s = initialize_int_set_with_arr(s_arr, TEST_SIZE);
    clock_t time_normal_start = clock();

    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        int random_number = (rand() << 15) | rand();
        normal_find(arr, TEST_SIZE, random_number);
    }
    clock_t time_normal_end = clock();
    time_difference = (double)(time_normal_end - time_normal_start) / CLOCKS_PER_SEC;
    printf("time spent for normal_find with size %d:%f\n", TEST_SIZE, time_difference);
    clock_t time_set_start = clock();
    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        int random_number = (rand() << 15) | rand();
        set_find(s, random_number);
    }
    clock_t time_set_end = clock();
    time_difference = (double)(time_set_end - time_set_start) / CLOCKS_PER_SEC;
    printf("time spent for set_find with size %d:%f\n", TEST_SIZE, time_difference);
    free(s->arr);
    free(s);
}
int main()
{
    // int arr[5] = {6, 0, 5, 3, 4};
    // CINTSET *s = initialize_int_set_with_arr(arr, 5);
    // append(s, 10);
    // printf("Whether 100 exist in set:%d", set_find(s, 100));
    test1();
    return 0;
}