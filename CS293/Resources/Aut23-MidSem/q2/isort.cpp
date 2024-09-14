#include <vector>

// insertion sort
void isort(std::vector<int>& v, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int j = i - 1, x = v[i];
        while (j >= left && v[j] > x) {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = x;
    }
}