#include <fstream>
#include "introsort.cpp"

int main(int argc, char **argv) {
    if (argc != 3) return 1;
    
    vector<int> v;

    std::fstream inp(argv[1]); int x;
    while (inp >> x) v.push_back(x);

    introsort(v);
    
    std::fstream out(argv[2], std::ios::out);
    for (int i = 0; i < v.size(); ++i) out << v[i] << '\n';
}
