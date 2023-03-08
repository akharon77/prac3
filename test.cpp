#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "test.h"
#include "sort.h"

#define MAX_VAL_ARR_GEN 100000000ll
#define CNT_PER_SORT    5
#define MIN_SIZE_ARR_N2 1000
#define MAX_SIZE_ARR_N2 10000
#define STEP_ARR_N2     90

#define MIN_SIZE_ARR_Q  3501000
#define MAX_SIZE_ARR_Q  5501000
#define STEP_ARR_Q      100000

#define MIN_SIZE_ARR_M  1000
#define MAX_SIZE_ARR_M  10000000 
#define STEP_ARR_M      100000

#define MIN_SIZE_ARR_LSD  1000
#define MAX_SIZE_ARR_LSD  10000000 
#define STEP_ARR_LSD      100000

void generateArray(int64_t *arr, int32_t n)
{
    srand(time(NULL));

    for (int32_t i = 0; i < n; ++i)
        arr[i] = rand() % MAX_VAL_ARR_GEN;
}

double timeSort(int64_t *arr, int32_t n, void (*sort)(int64_t *arr, int32_t n))
{
    clock_t t1 = clock();
    sort(arr, n);
    clock_t t2 = clock();

    return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
}

void testSortN2()
{
    int64_t sumRes = 0;
    int64_t *arr = (int64_t*) calloc(MAX_SIZE_ARR_N2, sizeof(int64_t)),
            *buf = (int64_t*) calloc(MAX_SIZE_ARR_N2, sizeof(int64_t));
    
    int32_t tableSize = (MAX_SIZE_ARR_N2 - MIN_SIZE_ARR_N2) / STEP_ARR_N2 + 1;
    double  table[3][tableSize] = {0};

    for (int32_t n = MIN_SIZE_ARR_N2, i = 0; n < MAX_SIZE_ARR_N2 + 1; n += STEP_ARR_N2, ++i)
    {
        generateArray(arr, n);

        for (int32_t j = 0; j < 5; ++j)
        {
            memcpy(buf, arr, sizeof(int64_t) * n);
            table[0][i] += timeSort(buf, n, insertionSort);

            memcpy(buf, arr, sizeof(int64_t) * n);
            table[1][i] += timeSort(buf, n, bubbleSort);

            memcpy(buf, arr, sizeof(int64_t) * n);
            table[2][i] += timeSort(buf, n, selectionSort);
        }

        for (int32_t j = 0; j < 3; ++j)
            table[j][i] /= 5;
    }

    for (int32_t i = 0; i < 3; ++i)
    {
        for (int32_t j = 0; j < tableSize; ++j)
            printf("%.0lf ", 1000. * table[i][j]);
        printf("\n");
    }

    free(arr);
    free(buf);
}

void testQuickSort()
{
    int64_t *arr = (int64_t*) calloc(MAX_SIZE_ARR_Q, sizeof(int64_t)),
            *buf = (int64_t*) calloc(MAX_SIZE_ARR_Q, sizeof(int64_t));
    
    int64_t (*select[])(int32_t n, int64_t *arr) = 
        {
            medOf3,
            centralSelect,
            randomSelect,
            medOfMed
        };

    int32_t tableSize = (MAX_SIZE_ARR_Q - MIN_SIZE_ARR_Q) / STEP_ARR_Q + 1;
    double  table[4][tableSize] = {0};

    for (int32_t n = MIN_SIZE_ARR_Q, i = 0; n < MAX_SIZE_ARR_Q + 1; n += STEP_ARR_Q, ++i)
    {
        dprintf(2, "%d\n", i);
        generateArray(arr, n);

        for (int32_t j = 0; j < 4; ++j)
        {
            table[j][i] = 0;

            for (int32_t k = 0; k < 5; ++k)
            {
                memcpy(buf, arr, sizeof(int64_t) * n);

                clock_t t1 = clock();
                quickSort(n, buf, select[j]);
                clock_t t2 = clock();

                table[j][i] += 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
            }

            table[j][i] /= 5;
        }
    }

    for (int32_t i = 0; i < 4; ++i)
    {
        for (int32_t j = 0; j < tableSize; ++j)
            printf("%.2lf ", table[i][j]);
        printf("\n");
    }

    free(arr);
    free(buf);
}

void testMergeSort()
{
    int64_t *arr = (int64_t*) calloc(MAX_SIZE_ARR_M, sizeof(int64_t)),
            *buf = (int64_t*) calloc(MAX_SIZE_ARR_M, sizeof(int64_t));
    
    int32_t tableSize = (MAX_SIZE_ARR_M - MIN_SIZE_ARR_M) / STEP_ARR_M + 1;
    double  table[tableSize] = {0};

    for (int32_t n = MIN_SIZE_ARR_M, i = 0; n < MAX_SIZE_ARR_M + 1; n += STEP_ARR_M, ++i)
    {
        dprintf(2, "%d\n", i);
        generateArray(arr, n);

        table[i] = 0;

        for (int32_t j = 0; j < 5; ++j)
        {
            memcpy(buf, arr, sizeof(int64_t) * n);
            table[i] += timeSort(buf, n, mergeSort);
        }

        table[i] /= 5;
    }

    for (int32_t j = 0; j < tableSize; ++j)
        printf("%.3lf ", table[j]);
    printf("\n");

    free(arr);
    free(buf);
}

void testLsdSort()
{
    int64_t *arr = (int64_t*) calloc(MAX_SIZE_ARR_LSD, sizeof(int64_t)),
            *buf = (int64_t*) calloc(MAX_SIZE_ARR_LSD, sizeof(int64_t));
    
    int32_t tableSize = (MAX_SIZE_ARR_LSD - MIN_SIZE_ARR_LSD) / STEP_ARR_LSD + 1;
    double  table[tableSize] = {0};

    for (int32_t n = MIN_SIZE_ARR_LSD, i = 0; n < MAX_SIZE_ARR_LSD + 1; n += STEP_ARR_LSD, ++i)
    {
        dprintf(2, "%d\n", i);
        generateArray(arr, n);

        table[i] = 0;

        for (int32_t j = 0; j < 5; ++j)
        {
            memcpy(buf, arr, sizeof(int64_t) * n);
            table[i] += timeSort(buf, n, lsdSort);
        }

        table[i] /= 5;
    }

    for (int32_t j = 0; j < tableSize; ++j)
        printf("%.3lf ", table[j]);
    printf("\n");

    free(arr);
    free(buf);
}

