#include <iostream>
#include <vector>
#include <string>

// a program that can change array A by user input and gets()

int main(void) {
    char x[6] = "hello";
    int A[100] = {1, 2, 3, 4, 5};
    gets(x);
    for (int i = 0; i < 5; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
