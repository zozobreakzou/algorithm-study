#include <cstdint>
#include <stdlib.h>
#include <cassert>

int binary_search(int a[], size_t s, int n)
{
    int low = 0;
    int high = s-1;
    while (low <= high) {
        int m = low + (high - low) / 2;
        if (n == a[m])
            return m;
        if (n > a[m]) {
            low = m + 1;
        }
        else {
            high = m - 1;
        }
    }

    return -1;
}

int main()
{
    int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    for (int i = 0; i < 9; ++i) {
        assert(binary_search(a, 9, i) == i);
    }

    assert(binary_search(a, 9, 10) == -1);

    return 0;
}