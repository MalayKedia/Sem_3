#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct NNmaker {
    NNmaker(std::vector<std::vector<int>> &__v) : v(__v) {
        cum = v;
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < v[i].size(); j++) {
                if (i > 0) cum[i][j] += cum[i - 1][j];
            }
        }   
    }
    std::vector<int> get_nearest(std::vector<int> query) {
        std::vector<int> result(1, dotProduct(v[0], query));
        for (int i = 1; i < cum.size(); i++) {
            result.push_back(dotProduct(cum[i], query) - dotProduct(cum[i-1], query));
        }
        return result;
    }
protected:
    std::vector<std::vector<int>> v, cum;
    int dotProduct(std::vector<int> &a, std::vector<int> &b) {
        int result = 0;
        for (int i = 0; i < a.size(); i++) {
            result += a[i] * b[i];
        }
        return result;
    }
};

int main(void) {
    NNmaker nn = NNmaker(std::vector<std::vector<int>>{
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    });
    std::vector<int> result = nn.get_nearest(std::vector<int>{1, 4, 9, 16, 25});
    for (auto &elem : result) {
        printf("%d ", elem);
    }
    std::cout << std::endl;
    return 0;
}
