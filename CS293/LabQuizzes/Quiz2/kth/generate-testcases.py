import random
import os
import sys
import math

if len(sys.argv) < 4:
    print("python3 generate_multiple_test_cases.py [base_path] [num_tests] [max_nodes] ")
    exit()
    
# Set paths for Google Drive
base_path      = sys.argv[1] #'./tmp/'
num_test_cases = int(sys.argv[2]) # Number of test cases
max_nodes      = int(sys.argv[3]) # Maximum value for the BST nodes

os.system(f'mkdir {base_path}')
input_tree_file = base_path + '/input_tree.txt'
input_k_file = base_path + '/input_k.txt'
output_file = base_path + '/expected_outputs.txt'

class TreeNode:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.value = key

# Function to insert a node in the BST
def insert(root, key):
    if root is None:
        return TreeNode(key)
    else:
        if root.value < key:
            root.right = insert(root.right, key)
        else:
            root.left = insert(root.left, key)
    return root

# Function to generate a valid BST and return its root
def generate_bst(num_elements, max_value):
    values = random.sample(range(1, max_value + 1), num_elements)
    root = None
    for value in values:
        root = insert(root, value)
    return root, values

# Function to save BST values to the input file
def save_bst_input(test_case_num, nums):
    with open(input_tree_file, 'a') as f:
        f.write(f'{" ".join(map(str, nums))}\n')

# Function to save k values to the input file
def save_k_values(test_case_num, k_small, k_large):
    with open(input_k_file, 'a') as f:
        f.write(f'{k_small} {k_large}\n')

# Function to save the output data to the output file
def save_output(test_case_num, kth_smallest, kth_largest):
    with open(output_file, 'a') as f:
        f.write(f"{kth_smallest} {kth_largest}\n")

# Function to find the k-th smallest element in the BST
def find_kth_smallest(root, k):
    if root is None:
        return None

    # Traverse left subtree
    left = find_kth_smallest(root.left, k)
    if left is not None:
        return left

    k[0] -= 1
    if k[0] == 0:
        return root.value

    # Traverse right subtree
    return find_kth_smallest(root.right, k)

# Function to find the k-th largest element in the BST
def find_kth_largest(root, k):
    if root is None:
        return None

    # Traverse right subtree
    right = find_kth_largest(root.right, k)
    if right is not None:
        return right

    k[0] -= 1
    if k[0] == 0:
        return root.value

    # Traverse left subtree
    return find_kth_largest(root.left, k)

def main():
    # num_test_cases = 1  # Number of test cases

    for test_case_num in range(1, num_test_cases + 1):
        # Random number of elements for each BST
        num_elements = random.randint(2, max_nodes)  # Adjust range as needed
        max_value    = 2*num_elements # Maximum value for the BST nodes

        # Generate a valid BST
        bst_root, bst_values = generate_bst(num_elements, max_value)

        # Determine valid k values based on the number of elements in the BST
        k_small = [random.randint(1, math.floor(math.log2(num_elements)) )]
        k_large = [random.randint(1, math.floor(math.log2(num_elements)) )]
        # k_small = [random.randint(1, 2000)]
        # k_large = [random.randint(1, 2000)]

        # Save BST values and k values to separate files
        save_bst_input(test_case_num, bst_values)
        # print(sorted(bst_values))
        save_k_values(test_case_num, k_small[0], k_large[0])
        # print(k_small[0], k_large[0])

        # Find the k-th smallest and largest elements
        kth_smallest = find_kth_smallest(bst_root, k_small)
        # print(kth_smallest)
        kth_largest = find_kth_largest(bst_root, k_large)
        # print(kth_largest)

        # Save output data
        save_output(test_case_num, kth_smallest, kth_largest)

if __name__ == "__main__":
    main()

