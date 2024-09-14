#include "rb.h"
using ptr = RedBlackTree::ptr;

RedBlackTree::RedBlackTree(){}

const ptr RedBlackTree::getRoot() const
{ 
	return root; 
}

ptr RedBlackTree::insert(int data)
{
	ptr newnodePtr = new node(data);
	if (!root) {
		root = newnodePtr;
		root->color = 0; // set root color as black
		return newnodePtr;
	}
	insert(root, newnodePtr);
	return newnodePtr;
}

// auxiliary function to perform RBT insertion of a node.
// you may assume start is not nullptr
void RedBlackTree::insert(ptr start, ptr newnodePtr)
{
	// recurse down the tree
	bool isLeftChild = (newnodePtr->data < start->data);
	ptr newstart = (isLeftChild) ? start->left : start->right;
	
	if (newstart)
		insert(newstart, newnodePtr);
	else {
		if (isLeftChild)
			start->left = newnodePtr;
		else
			start->right = newnodePtr;
		newnodePtr->parent = start;
	}
}


// Credits to Adrian Schneider
void RedBlackTree::printRBT(ptr start, const std::string& prefix, bool isLeftChild) const
{
	if (!start) return;

	std::cout << prefix;
	std::cout << (isLeftChild ? "|--" : "|__" );
	// print the value of the node
	std::cout << start->data << "(" << start->color << ")" << std::endl;
	// enter the next tree level - left and right branch
	printRBT(start->left, prefix + (isLeftChild ? "│   " : "    "), true);
	printRBT(start->right, prefix + (isLeftChild ? "│   " : "    "), false);
}

// Function performing right rotation
// of the passed node
void RedBlackTree::rightrotate(ptr loc)
{
	ptr left = loc->left;
	loc->left = left->right;
	if (loc->left)
		loc->left->parent = loc;
	left->parent = loc->parent;
	if (!loc->parent)
		root = left;
	else if (loc == loc->parent->left)
		loc->parent->left = left;
	else
		loc->parent->right = left;
	left->right = loc;
	loc->parent = left;
}

// Function performing left rotation
// of the passed node
void RedBlackTree::leftrotate(ptr loc)
{
	ptr right = loc->right;
	loc->right = right->left;
	if (loc->right)
		loc->right->parent = loc;
	right->parent = loc->parent;
	if (!loc->parent)
		root = right;
	else if (loc == loc->parent->left)
		loc->parent->left = right;
	else
		loc->parent->right = right;
	right->left = loc;
	loc->parent = right;
}

// This function fixes violations
// caused by RBT insertion
void RedBlackTree::fixup(ptr loc)
{
	ptr parent_pt = nullptr;
	ptr grand_parent_pt = nullptr;
	while ((loc != root) && (loc->color != 0)
		&& (loc->parent->color == 1))
	{
		parent_pt = loc->parent;
		grand_parent_pt = loc->parent->parent;

		/* Case : A
			Parent of loc is left child
			of Grand-parent of
		loc */
		if (parent_pt == grand_parent_pt->left)
		{

			ptr uncle_pt = grand_parent_pt->right;

			/* Case : 1
				The uncle of loc is also red
				Only Recoloring required */
			if (uncle_pt != nullptr && uncle_pt->color == 1)
			{
				grand_parent_pt->color = 1;
				parent_pt->color = 0;
				uncle_pt->color = 0;
				loc = grand_parent_pt;
			}

			else {

				/* Case : 2
					loc is right child of its parent
					Left-rotation required */
				if (loc == parent_pt->right) {
					leftrotate(parent_pt);
					loc = parent_pt;
					parent_pt = loc->parent;
				}

				/* Case : 3
					loc is left child of its parent
					Right-rotation required */
				rightrotate(grand_parent_pt);
				int t = parent_pt->color;
				parent_pt->color = grand_parent_pt->color;
				grand_parent_pt->color = t;
				loc = parent_pt;
			}
		}

		/* Case : B
			Parent of loc is right
			child of Grand-parent of
		loc */
		else {
			ptr uncle_pt = grand_parent_pt->left;

			/* Case : 1
				The uncle of loc is also red
				Only Recoloring required */
			if ((uncle_pt != nullptr) && (uncle_pt->color == 1))
			{
				grand_parent_pt->color = 1;
				parent_pt->color = 0;
				uncle_pt->color = 0;
				loc = grand_parent_pt;
			}
			else {
				/* Case : 2
				loc is left child of its parent
				Right-rotation required */
				if (loc == parent_pt->left) {
					rightrotate(parent_pt);
					loc = parent_pt;
					parent_pt = loc->parent;
				}

				/* Case : 3
					loc is right child of its parent
					Left-rotation required */
				leftrotate(grand_parent_pt);
				int t = parent_pt->color;
				parent_pt->color = grand_parent_pt->color;
				grand_parent_pt->color = t;
				loc = parent_pt;
			}
		}
	} root->color = 0; // reset color of root as black
}

// Function to print inorder traversal
// of the fixated tree
void RedBlackTree::inorder(ptr start) const
{
	if (!start)
		return;
	
	inorder(start->left);
	std::cout << start->data << " ";
	inorder(start->right);
}

// driver code
int main()
{
	int n; std :: cin >> n;
	assert (n < 10000 && n >= 0);
	int a[10000];
	RedBlackTree tree;

	for (int i = 0; i < n; i++) {
		std::cin >> a[i];

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array

		// calling function that performs rbt insertion of
		// this newly created node
		auto newnodePtr = tree.insert(a[i]);

		// calling function to preserve properties of rb
		// tree
		tree.fixup(newnodePtr);
	}
	tree.printRBT(tree.getRoot());

	return 0;
}
