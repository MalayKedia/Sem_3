Given a BST, identify the k-th smallest and k-th largest elements using recursive functions, findKthSmallest and findKthLargest. 
Consider the following BST: 6 8 10 12 15 17 19 20 25. If k_small = 2 and k_large = 5, the 2nd smallest element is 8, while the 5th largest element is 17.

        15
       /  \
     10    20
    /  \   /  \
   8   12 17  25
  /           \
 6            19

Return -1 if kth largest/smallest node does not exists!

Write your implementation in kth.cpp

Please test your code for small inputs, for example, BST with no nodes, 1 node, and 2 nodes.

