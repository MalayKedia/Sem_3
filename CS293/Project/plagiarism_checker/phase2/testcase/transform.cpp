#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

template <typename T, U>
std::vector<std::vector<U>> transform(std::vector<std::vector<T>> &v, 
        std::function<U(T)> f) {
    std::vector<std::vector<U>> result;
    for (auto &row : v) {
        std::vector<U> new_row;
        for (auto &elem : row) {
            new_row.push_back(f(elem));
        }
        result.push_back(new_row);
    }
    return result;
}

template <typename T>
std::vector<T> compress(std::vector<std::vector<T>> &v) {
    std::vector<T> result;
    for (auto &row : v) {
        for (auto &elem : row) {
            result.push_back(elem);
        }
    }
    return result;
}

template <typename T>
std::vector<std::vector<T>> matmul(std::vector<std::vector<T>> &a, 
        std::vector<std::vector<T>> &b) {
    std::vector<std::vector<T>> result;
    for (int i = 0; i < a.size(); i++) {
        std::vector<T> row;
        for (int j = 0; j < b[0].size(); j++) {
            T sum = 0;
            for (int k = 0; k < a[0].size(); k++) {
                sum += a[i][k] * b[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}

int main(void) {
    std::vector<std::vector<int>> v = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<int>> result = transform<int, int>(v, [](int x) {
        return x * x;
    });
    for (auto &row : result) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> a = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> b = {
        {7, 8},
        {9, 10},
        {11, 12}
    };
    std::vector<std::vector<int>> result2 = matmul<int>(a, b);
    for (auto &row : result2) {
        for (auto &elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> v2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<int> result3 = compress<int>(v2);
    for (auto &elem : result3) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
