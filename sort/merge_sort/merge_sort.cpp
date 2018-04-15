#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <cassert>
#include <vector>

void merge(int a[], int n, int k)
{
    int l1 = 0;
    int h1 = k - 1;

    while (h1 < n - 1)
    {
        int l2 = h1+1;
        int h2 = l2+k-1;
        if (h2 > n - 1) h2 = n - 1;

        int p1 = l1;
        int p2 = l2;
        for (; p1 <= h1 && p2 <= h2; )
        {
            if (a[p1] <= a[p2]) {
                p1++;
            }
            else {
                // insert a[h1] to right array
                int k = a[p2];
                int i = l2;
                for (; i <= h2; i++) {
                    if (a[i] > a[h1]) {
                        break;
                    }
                }
                i = i - 1;
                for (int j = l2 + 1; j <= i; ++j) {
                    a[j - 1] = a[j];
                }
                a[i] = a[h1];
                //insert a[p2] to left array
                for (int j = h1 - 1; j >= p1; --j) {
                    a[j + 1] = a[j];
                }
                a[p1] = k;
                p1++;
            }
        }

        l1 = h2 + 1;
        h1 = l1 + k-1;
    }
}

void merge_sort(int a[], int n) {
    int k = 1;
    while (k < n) {
        merge(a, n, k);
        k *= 2;
    }
}

void assert_array_same(int a1[], size_t s1, int a2[], size_t s2)
{
    assert(s1 == s2);

    for (size_t i = 0; i < s1; ++i)
    {
        assert(a1[i] == a2[i]);
    }
}

void test()
{
    int a10[1] = { 1 };
    int a11[1] = { 1 }; merge_sort(a11, 1); assert_array_same(a11, 1, a10, 1);

    int a20[2] = { 1, 2 };
    int a21[2] = { 1, 2 }; merge_sort(a21, 2); assert_array_same(a21, 2, a20, 2);
    int a22[2] = { 2, 1 }; merge_sort(a22, 2); assert_array_same(a22, 2, a20, 2);

    int a30[3] = { 1, 2, 3 };
    int a31[3] = { 1, 2, 3 }; merge_sort(a31, 3); assert_array_same(a31, 3, a30, 3);
    int a32[3] = { 1, 3, 2 }; merge_sort(a32, 3); assert_array_same(a32, 3, a30, 3);
    int a33[3] = { 3, 2, 1 }; merge_sort(a33, 3); assert_array_same(a33, 3, a30, 3);
    int a34[3] = { 3, 1, 2 }; merge_sort(a34, 3); assert_array_same(a34, 3, a30, 3);
    int a35[3] = { 2, 3, 1 }; merge_sort(a35, 3); assert_array_same(a35, 3, a30, 3);
    int a36[3] = { 2, 1, 3 }; merge_sort(a36, 3); assert_array_same(a36, 3, a30, 3);

    int a40[4] = { 1, 2, 2, 3 };
    int a41[4] = { 1, 2, 2, 3 }; merge_sort(a41, 4); assert_array_same(a41, 4, a40, 4);
    int a42[4] = { 1, 3, 2, 2 }; merge_sort(a42, 4); assert_array_same(a42, 4, a40, 4);
    int a43[4] = { 1, 2, 3, 2 }; merge_sort(a43, 4); assert_array_same(a43, 4, a40, 4);
    int a44[4] = { 2, 2, 3, 1 }; merge_sort(a44, 4); assert_array_same(a44, 4, a40, 4);
    int a45[4] = { 2, 2, 1, 3 }; merge_sort(a45, 4); assert_array_same(a45, 4, a40, 4);

    int a70[7] = { 1, 3, 3, 3, 4, 5, 7 };
    int a71[7] = { 3, 4, 3, 5, 3, 7, 1 }; merge_sort(a71, 7); assert_array_same(a71, 7, a70, 7);
    int a72[7] = { 3, 3, 3, 5, 4, 7, 1 }; merge_sort(a72, 7); assert_array_same(a72, 7, a70, 7);
    int a73[7] = { 3, 3, 1, 5, 4, 7, 3 }; merge_sort(a73, 7); assert_array_same(a73, 7, a70, 7);
    int a74[7] = { 4, 3, 3, 3, 7, 5, 1 }; merge_sort(a74, 7); assert_array_same(a74, 7, a70, 7);

    int a90[9] = { 1, 2, 2, 3, 5, 6, 6, 7, 9 };
    int a91[9] = { 1, 2, 2, 3, 5, 6, 6, 7, 9 }; merge_sort(a91, 9); assert_array_same(a91, 9, a90, 9);
    int a92[9] = { 3, 2, 6, 5, 7, 2, 6, 9, 1 }; merge_sort(a92, 9); assert_array_same(a92, 9, a90, 9);
    int a93[9] = { 1, 9, 6, 5, 6, 7, 2, 2, 3 }; merge_sort(a93, 9); assert_array_same(a93, 9, a90, 9);
    int a94[9] = { 9, 1, 6, 5, 6, 7, 2, 2, 3 }; merge_sort(a94, 9); assert_array_same(a94, 9, a90, 9);
    int a95[9] = { 5, 6, 6, 9, 2, 2, 3, 7, 1 }; merge_sort(a95, 9); assert_array_same(a95, 9, a90, 9);
    int a96[9] = { 9, 7, 6, 6, 5, 3, 2, 2, 1 }; merge_sort(a96, 9); assert_array_same(a96, 9, a90, 9);

    while (true) {
        std::vector<int> a;
        int s = std::rand()%1000;
        for (int i = 0; i < s; ++i) {
            a.push_back(std::rand()%1000);
        }
        std::vector<int> b = a;
        std::sort(b.begin(), b.end());
        for (int i = 0; i < 10; i++) {
            merge_sort(a.data(), s);
            assert(a == b);
            std::random_shuffle(a.begin(), a.end());
        }
    }
}

int main()
{
    test();
    return 0;
}