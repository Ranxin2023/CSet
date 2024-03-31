#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_SIZE 30000
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
    s->arr = NULL;
    return s;
}
CINTSET *initialize_int_set_with_arr(int *arr, size_t size)
{
    CINTSET *s = malloc(sizeof(CINTSET));
    qsort(arr, size, sizeof(int), compare);
    int repeat = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            repeat += 1;
        }
    }
    s->size = size - repeat;
    s->arr = malloc(sizeof(int) * s->size);
    s->arr[0] = arr[0];
    int count = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] != arr[i - 1])
        {
            s->arr[i - count] = arr[i];
        }
        else
        {
            count += 1;
        }
    }
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
    if (set_find(s, value))
    {
        return;
    }
    if (s->size == 0)
    {
        s->arr = malloc(sizeof(int));
    }
    else
    {
        s->arr = (int *)realloc(s->arr, sizeof(int) * (s->size + 1));
    }
    s->arr[s->size] = value;
    s->size += 1;
    sort(s);
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
    if (s->size == 0)
    {
        return 0;
    }
    // sort(s);
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

void print_set(CINTSET *s)
{
    printf("All the elements in set is:\n");
    for (size_t i = 0; i < s->size; i++)
    {
        printf("%d\t", s->arr[i]);
    }
}

// This is test for time complexity of set
void test1()
{
    // initialize an array with 10^5
    // clock_t time_init_start = clock();
    int *arr = NULL;
    // int *s_arr = NULL;
    // Check if allocation was successful

    srand(time(NULL));
    // printf("%d\n", RAND_MAX);
    CINTSET *s = initialize_int_set();
    size_t repeat = 0;
    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        int random_number = (rand() << 15) | rand();
        // printf("%d\n", random_number);
        // s_arr[i] = random_number;
        if (!set_find(s, random_number))
        {

            arr = (int *)realloc(arr, sizeof(int) * (i - repeat + 1));
            arr[i - repeat] = random_number;
            append(s, random_number);
        }
        else
        {
            repeat += 1;
        }
    }
    // clock_t time_init_end = clock();
    // double time_difference = (double)(time_init_end - time_init_start) / CLOCKS_PER_SEC;
    // printf("time spent for initialize array with size %d:%f\n", TEST_SIZE, time_difference);

    clock_t time_normal_start = clock();

    for (size_t i = 0; i < TEST_SIZE; i++)
    {
        int random_number = (rand() << 15) | rand();
        normal_find(arr, TEST_SIZE, random_number);
    }
    clock_t time_normal_end = clock();
    double time_difference = (double)(time_normal_end - time_normal_start) / CLOCKS_PER_SEC;
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
    free(arr);
    // free(s_arr);
    free(s->arr);
    free(s);
}

int main()
{
    // int arr[] = {6, 0, 5, 3, 4, 5, 2, 6, 5, 1, 10, 6, 7};
    // CINTSET *s = initialize_int_set_with_arr(arr, sizeof(arr) / sizeof(int));
    // append(s, 10);
    // print_set(s);
    // printf("Whether 100 exist in set:%d", set_find(s, 100));
    test1();
    return 0;
}