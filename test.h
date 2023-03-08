#ifndef TEST_H
#define TEST_H

#include <stdint.h>

void    generateArray  (int64_t *arr, int32_t n);
double  timeSort       (int64_t *arr, int32_t n, void (*sort)(int64_t *arr, int32_t n));

void testSortN2    ();
void testQuickSort ();
void testMergeSort ();
void testLsdSort   ();

#endif
