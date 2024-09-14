/*
    In this problem, you will implement a Deque class that will be inherited by a Queue and a Stack class.
    The Deque class will have the following functions:

    1. Constructors: Take arguments like the capacity of the deque, scaling factor etc.
    2. Destructor: Deallocate the dynamic array that stores the deque.

    3. push_back: Push data to the back of the deque.
    4. pop_front: Remove and return the front element of the deque.
    5. push_front: Push data to the front of the deque.
    6. pop_back: Remove and return the back element of the deque.
    7. peek_front: Return the front element of the deque without removing it.
    8. peek_back: Return the back element of the deque without removing it.

    9. get_capacity: Return the capacity of the deque.
    10. get_size: Return the size of the deque.
    11. is_empty: Return true if the deque is empty, and false otherwise.

    NOTE: The Deque class should be able to resize itself when it is full and auto_resize is true. The capacity
    of the deque should be scaled by the resize factor. 

    -> Rescaling should only happen when the deque is full and auto_resize is true. If the existing array is not full,
    but the back of the array is the end of the array, then you need to work in a circular manner and keep track of the 
    start and end of the array. 

    You need to implement the Deque, Queue, and Stack classes as described above. 
    Overload << operator so that cout works. You need to implement the overloaded << operator for the Queue
    class. You need to implement the overloaded << operator for the Stack class. You need to implement the copy
    constructor for the Queue class. You need to implement the copy constructor for the Stack class. You need to
    make the necessary member functions of the Deque class public in the Queue and Stack classes.

    Read about class inheritance and friend functions. Understand copy constructors and how to use them before you 
    attempt this problem.

    Run your code:
    g++ deque_inheritance.cpp -o deque_inheritance
    ./deque_inheritance
    
    Use command line inputs from the Inputs floder to test your code and validate against the Outputs folder.
*/


# include "bits/stdc++.h"

using namespace std;

template <typename T>
class Deque
{
    // Write a "Friend" function that overloads the "<<"" operator, and can be used to "cout" a deque.
    // Read about friend functions. Note that friend functions have access to private, public and 
    // protected members! 
    friend ostream& operator<<(ostream& out, const Deque& dq)
    { 
        // TODO: Complete the overloading function. 
        // HINT: You just have to populate the ostream (output stream) with the members of the deque
        // array!
      return out;
    }

// Think about why we are declaring these variables as protected and not private. Read about 
// different ways of scoping and their functions and uses in class inheritance. 
protected:
// TODO: Suitably initialize the queue parameters (Feel free to add any other variables as needed) 
    T* arr;
    int capacity;
    int size;
    bool auto_resize;
    int resize_factor;

public:
    Deque(int cap, bool resize = true, int resize_factor = 2) 
    {                                           
        // TODO: Implement the constructor that initializes the Deque with a given capacity
        // and optionally the resize factor
    }

    Deque(bool resize = true, int resize_factor = 2)
    {
        // TODO: Implement the constructor that initializes the Deque with a default capacity
        // and optionally given the resize factor
    }

    Deque(const Deque& dq)
    {
        // TODO: Implement the copy constructor for the Deque. 
        // What you need to do is copy the contents of the Deque object dq to the new Deque object
        // being instantiated.
    }

    ~Deque()
    {
        // TODO: Implement the destructor
    }

    int get_capacity()
    {
        // TODO: Implement a getter for the capacity of the Deque
      return 0; //Dummy
    }

    int get_size()
    {
        // TODO: Implement a getter for the size of the Deque
      return 0; //Dummy
    }

    bool is_empty()
    {
        // TODO: Implement the is_empty method to check if the deque is empty
      return false; //Dummy
    }  

// ATTENTION S'il vous plait !!
// We DO NOT want to use Deque as a data structure for the purpose of this lab,
// but want to be able to inherit it's functions selectively and create our 
// Stack and Queue. Therefore, we do not make the following functions public.
protected:
    bool push_back(T data)
    {
        // TODO: Implement the push_back method to push the data into the back of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
      return false; //Dummy return
    }

    T pop_front()
    {
        // TODO: Implement the pop_front method to pop the data from the front of the deque
        // Throw exception if the deque is empty
    }

    bool push_front(T data)
    {
        // TODO: Implement the push_front method to push the data into the front of the deque
        // If the deque is full and auto_resize is true, scale the capacity of the deque
        // Returns true if push succeds else returns false
      return false; //Dummy
    }

    T pop_back()
    {
        // TODO: Implement the pop_back method to pop the data from the back of the deque
        // Throw exception if the deque is empty
    }

    T peek_front()
    {
        // TODO: Implement the peek_front method to return the front element of the deque
        // Throw exception if the deque is empty
    }

    T peek_back()
    {
        // TODO: Implement the peek_back method to return the last element of the deque
        // Throw exception if the deque is empty
    }
};

// Before you go on to this part, read about class inheritance and understand the 3 types below:

// Public inheritance: public->public, protected->protected
// Protected inheritance: public->protected, protected->protected
// Private inheritance (default): public->private, protected->private

//To access private members of the base class, you need to declare derived class as a friend class

// Now, create the Queue class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Queue : public Deque<T>
{
    // TODO: Write a similar friend function to overload << as Deque
    
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Queue(int cap, bool resize = true, int resize_factor = 2) 
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Queue(bool resize = true, int resize_factor = 2)
    {}

    // TODO: Write a custom copy constructor for the Queue. It must take a const reference to a
    // Queue object and copy its contents to the new Queue object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque

    // NOTE: Since Queue inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Queue 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Queue as Public members
    // HINT: do it by "using" 
};

// Now, create the Stack class, and you must derive it from Deque. Why implement everything again!

template<typename T>
class Stack : public Deque<T>
{
    // TODO: Write a similar friend function to overload << as Deque
    
public:
    // TODO: Inherit the constructor that initializes the queue with a given capacity
    // and optionally the resize factor from Deque
    Stack(int cap, bool resize = true, int resize_factor = 2) 
    {}

    // TODO: Inherit the constructor that initializes the queue with a default capacity
    // and optionally given the resize factor from Deque
    Stack(bool resize = true, int resize_factor = 2)
    {}

    // TODO: Write a custom copy constructor for the Stack. It must take a const reference to a
    // Stack object and copy its contents to the new Stack object being created.
    // HINT: You can use the copy constructor of the Deque class to copy the contents of the Deque

    // NOTE: Since Stack inherits from Deque, and Deque already has a destructor that correctly
    // deallocates the dynamic array arr, you don't need to write an additional destructor for Stack 

    // TODO: Make the (protected) member functions from Deque that are needed publicly by a 
    // Stack as Public members
    // HINT: do it by "using" the necessary functions
};
