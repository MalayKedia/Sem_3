#include <iostream>
#include <vector>
#include <string>

#define MODULO 1000000007

class NNmaker { 
public:
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

int num_ways_reach(int x, int y, int z) {
    std::vector<std::vector<std::vector<int>>> DP(x + 1, 
            std::vector<std::vector<int>>(y + 1, std::vector<int>(z + 1, 0)));
    DP[0][0][0] = 1;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            for (int k = 0; k <= z; k++) {
                if (i > 0) DP[i][j][k] = (DP[i][j][k] + DP[i - 1][j][k]) % MODULO;
                if (j > 0) DP[i][j][k] = (DP[i][j][k] + DP[i][j - 1][k]) % MODULO;
                if (k > 0) DP[i][j][k] = (DP[i][j][k] + DP[i][j][k - 1]) % MODULO;
            }
        }
    }
    return DP[x][y][z];
}

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

void fun0(void) {
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
}

void fun1(void) {
    std::vector<std::vector<std::pair<int, int>>> graph = {
        {{1, 2}, {2, 3}},
        {{2, 4}},
        {{1, 1}, {3, 5}},
        {{0, 6}},
        {{2, 7}, {4, 8}},
        {{0, 9}, {3, 10}},
        {{1, 11}, {5, 12}},
        {{2, 13}, {6, 14}},
        {{3, 15}, {7, 16}},
        {{4, 17}, {8, 18}},
        {{5, 19}, {9, 20}}
    };
    int wt = shortest_path_wt(graph);
    std::cout << num_ways_reach(wt, wt*2, wt*3) << std::endl;
}

void fun2(void) {
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
}

std::vector<std::mutex> locks;
void fun(int n) {
    for (int i = 0; i < 100; i++) {
        locks[n].lock();
        switch (n) {
            case 0:
                fun0();
                break;
            case 1:
                fun1();
                break;
            case 2:
                fun2();
                break;
        }
        locks[(n + 1) % locks.size()].unlock();
    }
}

int main(void) {
    int n = 3;
    locks = std::vector<std::mutex>(n);
    locks[0].unlock();
    for (int i = 1; i < n; i++) {
        locks[i].lock();
    }
    std::vector<std::thread> threads;
    for (int i = 0; i < n; i++) {
        threads.push_back(std::thread(fun, i));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    return 0;
}
