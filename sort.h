#ifndef SORT_H
#define SORT_H

#include <stdint.h>

void    mergeSort     (int64_t *arr, int32_t n);
void    mergeSortRec  (int64_t *arr, int32_t n, int64_t *buf);
void    merge         (int64_t *dest, int64_t *a, int32_t len_a,
                                      int64_t *b, int32_t len_b);

void    insertionSort (int64_t *arr,  int32_t  n);
void    bubbleSort    (int64_t *arr,  int32_t  n);
void    selectionSort (int64_t *arr,  int32_t  n);

void    quickSort     (int32_t  n,    int64_t *arr, int64_t (*select)(int32_t n, int64_t *arr));
int64_t medOf3        (int32_t  n,    int64_t *arr);
int64_t centralSelect (int32_t  n,    int64_t *arr);
int64_t randomSelect  (int32_t  n,    int64_t *arr);
int64_t medOfMed      (int32_t  n,    int64_t *arr);
int64_t kthElement    (int32_t  n,    int64_t *arr, int32_t k);
int32_t partition     (int32_t  n,    int64_t *arr, int64_t pivot);

void    lsdSort       (int64_t *arr,  int32_t  n);

void    swap          (int64_t *lhs,  int64_t *rhs);
int64_t min           (int64_t  lhs,  int64_t  rhs);

#endif
