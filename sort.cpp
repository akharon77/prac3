#include <stdlib.h>
#include <string.h>

#include "sort.h"

void lsdSort(int64_t *arr, int32_t n)   // arr[i] >= 0
{
    uint64_t *buf = (uint64_t*) calloc(n, sizeof(uint64_t));

    int32_t cnt [1 << 8] = {0},
            pref[1 << 8] = {0};

    for (int32_t i = 0; i < 64 / 8; ++i)
    {
        for (int32_t j = 0; j < n; ++j)
            ++cnt[(arr[j] >> (8 * i)) & 0xFF];

        pref[0] = 0;
        for (int32_t j = 1; j < (1 << 8); ++j)
            pref[j] = pref[j - 1] + cnt[j - 1];

        for (int32_t j = 0; j < n; ++j)
        {
            uint8_t lstByte = (arr[j] >> (8 * i)) & 0xFF;
            buf[pref[lstByte]++] = arr[j];
        }

        memset(cnt, 0,   sizeof(int32_t) * (1 << 8));
        memcpy(arr, buf, sizeof(uint64_t) * n);
    }

    free(buf);
}

int64_t medOfMed(int32_t n, int64_t *arr)
{
    int32_t cntGroups = (n + 4) / 5;

    for (int32_t i = 0; i < cntGroups; ++i)
    {
        int32_t len = min(5 * (i + 1), n) - 5 * i;
        insertionSort(arr + 5 * i, len);

        swap(arr + i, arr + 5 * i + len / 2);
    }

    return kthElement(cntGroups, arr, cntGroups / 2 + 1);
}

void swap(int64_t *lhs, int64_t *rhs)
{
    int64_t buf = *lhs;
    *lhs = *rhs;
    *rhs = buf;
}

void insertionSort(int64_t *arr, int32_t n)
{
    for (int32_t i = 1, j = 1; i < n; j = ++i)
        while (j > 0 && arr[j] < arr[j - 1])
        {
            swap(arr + j, arr + j - 1);
            --j;
        }
}

void bubbleSort(int64_t *arr, int32_t n)
{
    char flag = 1;
    while (flag)
    {
        flag = 0;
        for (int32_t i = 0; i < n; ++i)
            for (int32_t j = 1; j < n; ++j)
                if (arr[j] < arr[j - 1])
                {
                    swap(arr + j, arr + j -1);
                    flag = 1;
                }
    }
}

void selectionSort(int64_t *arr, int32_t n)
{
    for (int32_t i = 0; i < n; ++i)
    {
        int32_t mn = i;

        for (int32_t j = i + 1; j < n; ++j)
            if (arr[j] < arr[mn])
                mn = j;

        swap(arr + mn, arr + i);
    }
}

int64_t min(int64_t lhs, int64_t rhs)
{
    if (lhs > rhs)
        return rhs;

    return lhs;
}

int64_t kthElement(int32_t n, int64_t *arr, int32_t k)
{
    while (1)
    {
        if (n == 1)
            return arr[0];

        int64_t pivot    = medOfMed(n, arr);
        int32_t leftSize = partition(n, arr, pivot);

        if (k <= leftSize)
        {
            n = leftSize;
        }
        else
        {
            n   -= leftSize;
            k   -= leftSize;
            arr += leftSize;
        }
    }
}

void quickSort(int32_t n, int64_t *arr, int64_t (*select)(int32_t n, int64_t *arr))
{
    if (n <= 1)
        return;

    int64_t pivot    = select(n, arr);
    int32_t leftSize = partition(n, arr, pivot);

    quickSort(leftSize,     arr,            select);
    quickSort(n - leftSize, arr + leftSize, select);
}

int32_t partition(int32_t n, int64_t *arr, int64_t pivot)
{
    int32_t left = 0, right = n - 1;

    while (left <= right)
    {
        while (left < n && arr[left] < pivot)
            ++left;
        while (right > -1 && arr[right] > pivot)
            --right;

        if (left >= right)
            break;

        swap(arr + left, arr + right);
        ++left;
        --right;
    }

    return left;
}

void mergeSort(int64_t *arr, int32_t n)
{
    int64_t *buf = (int64_t*) calloc(n, sizeof(int64_t));
    
    mergeSortRec(arr, n, buf);

    free(buf);
}

void mergeSortRec(int64_t *arr, int32_t n, int64_t *buf)
{
    if (n == 1)
        return;

    int64_t *a = arr,
            *b = arr + n / 2;

    int32_t len_a = n / 2,
            len_b = n - n / 2;

    mergeSortRec(a, len_a, buf);
    mergeSortRec(b, len_b, buf);

    merge(buf, a, len_a, b, len_b);
    memcpy(arr, buf, sizeof(int64_t) * n);
}

void merge(int64_t *dest, int64_t *a, int32_t len_a,
                          int64_t *b, int32_t len_b)
{
    int64_t *i = a,
            *j = b;

    int32_t cnt = 0;

    while (i - a < len_a && j - b < len_b)
    {
        if (*i < *j)
            dest[cnt] = *i++;
        else
            dest[cnt] = *j++;

        ++cnt;
    }

    while (i - a < len_a)
        dest[cnt++] = *i++;

    while (j - b < len_b)
        dest[cnt++] = *j++;
}

int64_t medOf3(int32_t n, int64_t *arr)
{
    int64_t a = arr[0],
            b = arr[n / 2],
            c = arr[n - 1];

    if (a > b)
        swap(&a, &b);
    if (b > c)
        swap(&b, &c);
    if (a > b)
        swap(&a, &b);

    return b;
}

int64_t centralSelect(int32_t n, int64_t *arr)
{
    return arr[n / 2];
}

int64_t randomSelect(int32_t n, int64_t *arr)
{
    return arr[rand() % n];
}

