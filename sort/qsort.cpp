#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <cassert>

int partition1(int a[], int low, int high)
{
    int k = a[low];
    int i = low, j = high;

    while (i < j)
    {
        while (i < j && a[j] >= k) {
            --j;
        }
        while (i < j && a[i] <= k) {
            ++i;
        }

        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    a[low] = a[i];
    a[i] = k;

    return i;
}

void qsort1(int a[], int low, int high)
{
    assert(a);
    if (low >= high)
        return;

    int pivot = partition1(a, low, high);
    qsort1(a, low, pivot - 1);
    qsort1(a, pivot + 1, high);
}


int partition2(int a[], int low, int high)
{
    int p = low + rand() % (high - low);
    int k = a[p];
    int i = low, j = high;

    while (i < j)
    {
        while (i < j && a[j] > k) {
            --j;
        }
        while (i < j && a[i] <= k) {
            ++i;
        }

        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    if (i > p) {
        a[p] = a[i];
        a[i] = k;
    }

    return i;
}

void qsort2(int a[], int low, int high)
{
    assert(a);
    if (low >= high)
        return;

    int pivot = partition2(a, low, high);
    qsort2(a, low, pivot - 1);
    qsort2(a, pivot + 1, high);
}

int partition3(int a[], int low, int high)
{
    int k = a[high];
    int i = low - 1;
    int j = low;

    while (j<high) {
        if (a[j] <= k) {
            ++i;
            std::swap(a[i], a[j]);
        }
        ++j;
    }
    std::swap(a[i+1], a[high]);
    return i + 1;
}

void qsort3(int a[], int low, int high)
{
    assert(a);
    if (low >= high)
        return;

    int pivot = partition3(a, low, high);
    qsort3(a, low, pivot - 1);
    qsort3(a, pivot + 1, high);
}

void assert_array_same(int a1[], size_t s1, int a2[], size_t s2)
{
    assert(s1 == s2);

    for (size_t i = 0; i < s1; ++i)
    {
        assert(a1[i] == a2[i]);
    }
}

void test( void (*qsort)(int a[], int, int) )
{
    int a10[1] = { 1 };
    int a11[1] = { 1 }; qsort(a11, 0, 0); assert_array_same(a11, 1, a10, 1);

    int a20[2] = { 1, 2 };
    int a21[2] = { 1, 2 }; qsort(a21, 0, 1); assert_array_same(a21, 2, a20, 2);
    int a22[2] = { 2, 1 }; qsort(a22, 0, 1); assert_array_same(a22, 2, a20, 2);

    int a30[3] = { 1, 2, 3 };
    int a31[3] = { 1, 2, 3 }; qsort(a31, 0, 2); assert_array_same(a31, 3, a30, 3);
    int a32[3] = { 1, 3, 2 }; qsort(a32, 0, 2); assert_array_same(a32, 3, a30, 3);
    int a33[3] = { 3, 2, 1 }; qsort(a33, 0, 2); assert_array_same(a33, 3, a30, 3);
    int a34[3] = { 3, 1, 2 }; qsort(a34, 0, 2); assert_array_same(a34, 3, a30, 3);
    int a35[3] = { 2, 3, 1 }; qsort(a35, 0, 2); assert_array_same(a35, 3, a30, 3);
    int a36[3] = { 2, 1, 3 }; qsort(a36, 0, 2); assert_array_same(a36, 3, a30, 3);

    int a70[7] = { 1, 3, 3, 3, 4, 5, 7 };
    int a71[7] = { 3, 4, 3, 5, 3, 7, 1 }; qsort(a71, 0, 6); assert_array_same(a71, 7, a70, 7);
    int a72[7] = { 3, 3, 3, 5, 4, 7, 1 }; qsort(a72, 0, 6); assert_array_same(a72, 7, a70, 7);
    int a73[7] = { 3, 3, 1, 5, 4, 7, 3 }; qsort(a73, 0, 6); assert_array_same(a73, 7, a70, 7);
    int a74[7] = { 4, 3, 3, 3, 7, 5, 1 }; qsort(a74, 0, 6); assert_array_same(a74, 7, a70, 7);

    int a90[9] = { 1, 2, 2, 3, 5, 6, 6, 7, 9 };
    int a91[9] = { 1, 2, 2, 3, 5, 6, 6, 7, 9 }; qsort(a91, 0, 8); assert_array_same(a91, 9, a90, 9);
    int a92[9] = { 3, 2, 6, 5, 7, 2, 6, 9, 1 }; qsort(a92, 0, 8); assert_array_same(a92, 9, a90, 9);
    int a93[9] = { 1, 9, 6, 5, 6, 7, 2, 2, 3 }; qsort(a93, 0, 8); assert_array_same(a93, 9, a90, 9);
    int a94[9] = { 9, 1, 6, 5, 6, 7, 2, 2, 3 }; qsort(a94, 0, 8); assert_array_same(a94, 9, a90, 9);
    int a95[9] = { 5, 6, 6, 9, 2, 2, 3, 7, 1 }; qsort(a95, 0, 8); assert_array_same(a95, 9, a90, 9);
}

int main()
{
    test(qsort1);
    test(qsort2);
    test(qsort3);

    return 0;
}