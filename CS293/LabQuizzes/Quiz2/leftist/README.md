# Leftist Heaps

PLEASE READ THIS FILE CAREFULLY!

## PROBLEM STATEMENT

Implement a LeftistHeap class that supports the following operations:

- Insert a key into the heap.
- Merge two heaps into one.
- Delete the minimum key from the heap.
- Check if the heap is empty.
- Make the heap empty.
- Retrieve the minimum key from the heap.
- Additionally, you need to maintain the leftist heap property after each operation.

Heap Property: For every node, the key of the parent is less than or equal to the keys of its children.
Leftist Property: The null path length (NPL) of the left child is always greater than or equal to the NPL of the right child.

Ensure that there are no memory leaks (nodes not deleted). You will be penalized otherwise.
Also, deleting a node does not automatically delete its children. Keep this in mind.

READ MORE ABOUT IT IN THE "LH.pdf"!

YOU HAVE TO ONLY WRITE CODE IN "leftistHeap.cpp"!

## SAMPLE TESTCASES

Some testcases are provided for you to check if your implementation of different class method are correct.
You can also access the interactive mode to check your implementation on custom testcases.
Interactive mode can be accessed by `make interactive`.

## INTERACTIVE MODE

The interactive mode allows you to interact with two Leftist Heaps (heap1 and heap2) using a series of commands. The mode lets you load data into heaps, merge them, print them, empty them, delete the minimum element, and more. Below is a guide on how to use each command.

- LOAD <filename>

      > Loads a heap with data from the specified file (filename).
      > If both heaps are already loaded, the system will prompt you to empty one heap before loading another.
      > Example: LOAD testcase1_1.txt
      > There small test files testcases/1.txt testcases/2.txt, which can be used to test your code. If needed, you may write more such files for testing.

- MERGE

  > Merges heap2 into heap1. After merging, heap2 is empty.
  > Example: MERGE

- PRINT <heap_number>

  > Prints the structure of the specified heap (either heap1 or heap2).
  > You must specify which heap to print by providing either 1 or 2.
  > Example: PRINT 1

- EMPTY <heap_number>

  > Empties the specified heap (heap1 or heap2).
  > You need to provide the heap number as either 1 or 2.
  > Example: EMPTY 1

- DELETEMIN

  > Deletes the minimum element from heap1.
  > After deletion, the minimum value is printed.
  > Example: DELETEMIN

- QUIT

  > Exits the interactive mode.
  > Example: QUIT

## TIME COMPLEXITY

You are expected to implement the Leftist Heap so that it adheres to the following time complexity characteristics:

- Insertion:

  > Average Time Complexity: 𝑂(log n)

- Merge:

  > Time Complexity: 𝑂(log n)

- Delete Min:

  > Average Time Complexity: 𝑂(log n)

- Find Min:

  > Time Complexity: 𝑂(1)

- Make Empty:

  > Time Complexity: 𝑂(n)

## SCORING

Use `make check` to test your implementation on the provided testcases.

We will be using different testcases (but similar to the ones provided) while grading.
The code will also be evaluated based on the time complexity of each operation.
