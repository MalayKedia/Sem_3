#include <iostream>
#include <span>
#include <memory>
#include <vector>

template <typename T, size_t... Dims>
class ndarray {
public:
    ndarray(size_t __size, size_t __dims[sizeof...(Dims)]) : size(__size) {
        for (int i = 0; i < sizeof...(Dims); i++) {
            dims[i] = __dims[i];
        }
        strides[sizeof...(Dims) - 1] = 1;
        for (int i = sizeof...(Dims) - 2; i >= 0; i--) {
            strides[i] = strides[i + 1] * dims[i + 1];
        }
        data = std::make_unique<T[]>(size);
    }

    T& operator()(size_t indices[sizeof...(Dims)]) {
        size_t index = 0;
        for (int i = 0; i < sizeof...(Dims); i++) {
            index += indices[i] * strides[i];
        }
        return data[index];
    }

    T& operator()(std::span<size_t> indices) {
        size_t index = 0;
        for (int i = 0; i < sizeof...(Dims); i++) {
            index += indices[i] * strides[i];
        }
        return data[index];
    }

    size_t get_size(void) {
        return size;
    }

    size_t get_dim(int i) {
        return dims[i];
    }

    size_t get_stride(int i) {
        return strides[i];
    }
protected:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t dims[sizeof...(Dims)];
    size_t strides[sizeof...(Dims)];
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

void sort(std::vector<int> &vec) {
    std::vector<int> other = vec;
    merge_sort(span(vec), span(other));
}

int main(void) {
    std::vector<int> vec = {5, 4, 3, 2, 1};
    sort(vec);
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}