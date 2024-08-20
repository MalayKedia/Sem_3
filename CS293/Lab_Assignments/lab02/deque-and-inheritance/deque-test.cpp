# include "bits/stdc++.h"
# include "deque-inheritance.cpp"

using namespace std;

int main (){
    int cap;
    cout << "Choose capacity: ";
    cin >> cap;
    // Test constructors and push
    Queue<int> q1(cap);
    q1.push_back(1);
    q1.push_back(2);
    q1.push_back(3);
    q1.push_back(4);
    q1.push_back(5);
    cout << q1 << endl;
    cout << "Size: " << q1.get_size() << endl;
    cout << "Capacity: " << q1.get_capacity() << endl;

    // Test copy constructor
    Queue<int> q2(q1);
    cout << q2 << endl;
    cout << "Size: " << q2.get_size() << endl;
    cout << "Capacity: " << q2.get_capacity() << endl;

    // Test auto resize
    q1.push_back(6);
    cout << q1 << endl;
    cout << "capacity: " << q1.get_capacity() << endl;
    q1.push_back(7);
    cout << "capacity: " << q1.get_capacity() << endl;

    // Test pop and peek
    for (int i = 0; i < 5; i++) {
        cout << "Popped: " << q1.pop_front() << endl;
        cout << "Peek: " << q1.peek_front() << endl;
    }

    // Write similar tests for Stack and validate your implementation
}
