#include "min-max-queue.cpp"
#include<fstream>
// #include<algorithm>
#include<cstring>
#include<string>
#include<sstream>

void processTestCase(const string filename) {
    ifstream infile(filename);
    string line;

    if (!infile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    MinMaxQueue queue;

    while (getline(infile, line)) {
        istringstream iss(line);
        string operation;
        iss >> operation;

        if (operation == "push") {
            int value;
            iss >> value;
            queue.push(value);
        } else if (operation == "pop") {
            queue.pop();
        } else if (operation == "front") {
            cout << "Front: " << queue.front() << endl;
        } else if (operation == "getMin") {
            cout << "Min: " << queue.getMin() << endl;
        } else if (operation == "getMax") {
            cout << "Max: " << queue.getMax() << endl;
        } else if (operation == "empty") {
            cout << "Empty: " << (queue.empty() ? "Yes" : "No") << endl;
        } else {
            cerr << "Unknown operation: " << operation << endl;
        }
    }

    infile.close();
}

int main(int argc, char** argv) {

    if( strcmp(argv[1], "short") == 0 ) {
        processTestCase("testcases/input_short.txt");
    } else {
        processTestCase("testcases/input_long.txt");
    }
    return 0;
}
