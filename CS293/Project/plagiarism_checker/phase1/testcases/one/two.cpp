#include <iostream>
#include <span>
#include <thread>
#include <vector>

struct D_ADAC {
    int dugc;
    int dpgc;
    int hod;
};

struct ADAC : public D_ADAC {
    int dean;
    int adean;
};

int binary_search(std::span<int> vec, int idx) {
    int l = 0;
    int r = vec.size();
    int mid;
    while (l < r + 1) {
        mid = (l + r) / 2;
        (vec[mid] == idx) ? r = mid : l = mid + 1;
    }
    return (vec[l] == idx) ? l : (vec[r] == idx) ? r : -1;
}

int lower_bound(std::span<int> vec, int idx) {
    int l = 0;
    int r = vec.size();
    int mid;
    while (l < r) {
        mid = (l + r) / 2;
        (vec[mid] < idx) ? l = mid + 1 : r = mid;
    }
    return l;
}

void merge(std::span<int> vec1, std::span<int> vec2, 
        std::span<int> vec0) {
    int pos1 = 0;
    int pos2 = 0;
    int pos0 = 0;
    while (pos1 < vec1.size() && pos2 < vec2.size()) {
        if (vec1[pos1] < vec2[pos2]) {
            vec0[pos0] = vec1[pos1];
            pos1++;
        } else {
            vec0[pos0] = vec2[pos2];
            pos2++;
        }
        pos0++;
    }
    while (pos1 < vec1.size()) {
        vec0[pos0] = vec1[pos1];
        pos1++;
        pos0++;
    }
    while (pos2 < vec2.size()) {
        vec0[pos0] = vec2[pos2];
        pos2++;
        pos0++;
    }
}

void merge_sort(std::span<int> vec, std::span<int> other) {
    int n = vec.size();
    if (n <= 1) {
        return;
    }
    merge_sort(other.subspan(0, n / 2), vec.subspan(0, n / 2));
    merge_sort(other.subspan(n / 2), vec.subspan(n / 2));
    merge(other.subspan(0, n / 2), other.subspan(n / 2), vec);
}

void sort_half(std::span<int> vec, std::span<int> other) {
    int n = vec.size();
    if (n <= 1) {
        return;
    }
    std::thread t1(merge_sort, other.subspan(0, n / 2), vec.subspan(0, n / 2));
    merge_sort(other.subspan(n / 2), vec.subspan(n / 2));
    t1.join();
    merge(other.subspan(0, n / 2), other.subspan(n / 2), vec);
}

void sort(std::vector<int> &vec) {
    std::vector<int> other = vec;
    std::span<int> vec_span = vec;
    std::span<int> other_span = other;
    std::thread t1(sort_half, other_span.subspan(0, vec.size() / 2), 
            vec_span.subspan(0, vec.size() / 2));
    sort_half(other_span.subspan(vec.size() / 2),
            vec_span.subspan(vec.size() / 2));
    t1.join();
    merge(other_span.subspan(0, vec.size() / 2), 
            other_span.subspan(vec.size() / 2), vec_span);
}

int main(void) {
    std::vector<int> vec = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    sort(vec);
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 1; i < 11; i++) {
        printf("%d ", binary_search(std::span(vec), i));
    }
    printf("\n");
    return 0;
}