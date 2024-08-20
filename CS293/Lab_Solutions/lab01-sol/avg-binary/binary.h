#include <iostream>
#include <vector>
#include <compare>
#include <concepts>

/*
You are to implement binary search.
Read up on C++ concepts here: https://en.cppreference.com/w/cpp/language/constraints
Use concepts to replace the work "typename" before "T" in all four function signatures.
You can also use a "requires" condition, mentioned in the same link.
Then, implement the binary search function yourself.
Handle corner cases appropriately, ensuring that the algorithm runs in O(log n) time.
Implement the O(n) version as well, for benchmarking.
*/

template <std::totally_ordered T> bool binarySearch(std::vector<T> &data, T src) {
    int left = 0;
    int right = data.size() - 1;
    if (data[left] > src || data[right] < src) {
        return false;
    }
    while (left + 1 < right) {
        int mid = (left + right)/2;
        if (data[mid] < src) {
            left = mid;
        } else if (data[mid] > src) {
            right = mid;
        } else {
            return true;
        }
    }
    if (data[left] == src || data[right] == src) {
        return true;
    }
}

template <std::totally_ordered T> bool linearSearch(std::vector<T> &data, T src) {
    for (T elem : data) {
        if (elem == src) {
            return true;
        }
    }
    return false;
}

// OPTIONAL: Try implementing the lower bound function and benchmarking those.
template <std::totally_ordered T> T lowerBound(std::vector<T> &data, T src) {
    int left = 0;
    int right = data.size() - 1;
    if (data[left] > src) {
        return src;
    }
    if (data[right] < src) {
        return data[right];
    }
    while (left + 1 < right) {
        int mid = (left + right)/2;
        if (data[mid] < src) {
            left = mid;
        } else if (data[mid] > src) {
            right = mid;
        } else {
            return data[mid];
        }
    }
    if (data[right] <= src) {
        return data[right];
    }
    return data[left];
}
template <std::totally_ordered T> T linearLowerBound(std::vector<T> &data, T src) {
    T low_bound = data[0];
    for (auto elem : data) {
        if (elem > src) {
            continue;
        }
        if (low_bound < elem) {
            low_bound = elem;
        }
    }
    return low_bound;
}
