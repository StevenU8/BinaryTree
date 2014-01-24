#include "bintree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// BinTree: Default Constructor
// Pre Conditions: N/A
// Post Conditions: Creates an empty binary tree. 
////////////////////////////////////////////////////////////////////////////////////////////////////
	BinTree::BinTree() { root = NULL; }


////////////////////////////////////////////////////////////////////////////////////////////////////
// Copy Constructor: Makes a deep copy of an existing tree by calling helper function (CopyTree)
// Pre Conditions: Source Tree is initialized properly
// Post Conditions: New Binary tree is created
////////////////////////////////////////////////////////////////////////////////////////////////////
	BinTree::BinTree(const BinTree &source)
	{
		CopyTree(this->root, source.root);
	}
	

////////////////////////////////////////////////////////////////////////////////////////////////////
// Assignment Operator: assigns a tree (via CopyTree). 
// Pre Conditions: Trees are properly initialized
// Post Conditions: copies the source tree into its own tree if they are not the same
////////////////////////////////////////////////////////////////////////////////////////////////////
	BinTree& BinTree::operator=(const BinTree &source)
	{
		if (&source != this) { 
			makeEmptyHelper(this->root);
			CopyTree(this->root, source.root);
		}
		return *this;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// CopyTree: Copy Helper function copies a tree recursively
// Pre Conditions: Trees are properly initialized
// Post Conditions: current node is set to a copy of source Node
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::CopyTree(Node* &current, const Node* sourceCurrent)
	{
		if(sourceCurrent == NULL) {
			current = NULL;
		} else {
			current = new Node;
			current->data = sourceCurrent->data;
			current->left = NULL;
			current->right = NULL;
			CopyTree(current->left, sourceCurrent->left);
			CopyTree(current->right, sourceCurrent->right);
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Insert: Insert NodeData into the tree in BST fassion
// Pre Conditions: NodeData is properly initialized
// Post Conditions: left for <,  right for >=,  ignored for ==
////////////////////////////////////////////////////////////////////////////////////////////////////
	bool BinTree::insert(NodeData* dataptr) 
	{
		Node* ptr = new Node;     // exception is thrown if memory is not allocated
		ptr->data = dataptr;
		dataptr = NULL;
		ptr->left = NULL;
		ptr->right = NULL;

		if (isEmpty()) {
			root = ptr;
		} else {
			Node* current = root;
			bool inserted = false;

			// if item is less than current item, insert in left subtree,
			// otherwise insert in right subtree
			while (!inserted) {
				if (*ptr->data == *current->data) {
					delete ptr;
					return false;
				}else if(*ptr->data < *current->data) {
					if (current->left == NULL) {              // at leaf, insert left
						current->left = ptr;
						inserted = true;
					} else {
						current = current->left;               // one step left
					}
				} else {
					if (current->right == NULL) {             // at leaf, insert right
						current->right = ptr;
						inserted = true;
					} else {
					current = current->right;              // one step right
					}
				}
			}
		}
		return true;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Deallocation~: Default deconstructor. Deallocates the tree to free up memory
// Pre Conditions: Tree is properly initialized
// Post Conditions: frees up all memory in the tree 
////////////////////////////////////////////////////////////////////////////////////////////////////
	BinTree::~BinTree() { makeEmpty(); }


////////////////////////////////////////////////////////////////////////////////////////////////////
// isEmpty: Checks if the tree is empty
// Pre Conditions: Tree is properly initialized
// Post Conditions: Returns true if empty; false if not empty
////////////////////////////////////////////////////////////////////////////////////////////////////
	bool BinTree::isEmpty() const { return root == NULL; }


////////////////////////////////////////////////////////////////////////////////////////////////////
// makeEmpty: Function to make tree empty
// Pre Conditions: Tree is properly initialized
// Post Conditions: Tree is empty and root is set to NULL
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::makeEmpty() { 
		makeEmptyHelper(root); 
		root = NULL;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// makeEmptyhelper: Helper function to make the tree empty recursively
// Pre Conditions: Tree is properly initialized
// Post Conditions: tree is made empty 
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::makeEmptyHelper(Node* &current)  
	{	
		if (current == NULL) {
			return;
		}

		if (current->left != NULL || current->right != NULL) {
			makeEmptyHelper(current->left);
			makeEmptyHelper(current->right);
			current->left = NULL;
			current->right = NULL;
		}
		
		if (current->left == NULL && current->right == NULL)  {
			delete current;
			return;
		} 
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator<< and helper function: overloaded operator to print out tree using in order traversal
// Pre Conditions: Tree is properly initialized
// Post Conditions: ostream is printed
////////////////////////////////////////////////////////////////////////////////////////////////////
	ostream& operator<<(ostream &output, const BinTree &bt)
	{
		bt.DisplayInOrder(output, bt.root);
		output << endl;
		return output;
	}

	void BinTree::DisplayInOrder(ostream &output, const Node* current) const
	{
		if(current == NULL) {
			return;
		}
		
		DisplayInOrder(output, current->left);
		output << *current->data << " ";
		DisplayInOrder(output, current->right);
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator==, Operator!= and helper function: determines if two trees are equal by traversing them and comparing one node at a time
// Pre Conditions:  Trees are properly initialized
// Post Conditions: returns whether the trees are equal or not
////////////////////////////////////////////////////////////////////////////////////////////////////
	bool BinTree::operator==(const BinTree &other) const { return equal(root, other.root); }

	bool BinTree::operator!=(const BinTree &other) const { return !(*this == other); }
	
	bool BinTree::equal(const Node* current, const Node* otherCurrent) const
	{
		if (current == NULL && otherCurrent == NULL) {
			return true;
		} else if (current == NULL || otherCurrent == NULL) {
			return false;
		} else if (current->data != otherCurrent->data) {
			return false;
		} else {
			return equal(current->left, otherCurrent->left);
			return equal(current->right, otherCurrent->right);
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Retrieve: retrieve the location of a particular NodeData
// Pre Conditions: Tree and NodeData is properly initialized
// Post Conditions: pointer passed in by reference is set to the location of the NodeData if found
///////////////////////////////////////////////////////////////////////////////////////////////////
	bool BinTree::retrieve(const NodeData &targetData, NodeData*&p) const
	{
		if (isEmpty()) {
			return false;
		} else {
			Node* current = root;
			bool found = false;

			while (!found) {
				if (targetData == *current->data) {
					p = current->data;
					found = true;
				}else if(targetData < *current->data) {
					if (current->left == NULL) {              
						return false;
					} else {
						current = current->left;               
					}
				} else {
					if (current->right == NULL) {
						return false;
					} else {
						current = current->right;         
					}
				}
			}
			return true;
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove and Helper Function: traverse the tree to find the NodeData and remove it
// Pre Conditions: Tree is properly initialized
// Post Conditions: Once the NodeData is found, change the data pointer to the highest in the left subtree
// left for <,  right for >=,  ignored for ==
///////////////////////////////////////////////////////////////////////////////////////////////////
	bool BinTree::remove(const NodeData &targetData, NodeData*&p) 
	{
		if (isEmpty()) {
			return false;
		} else {
			Node* current = root;
			bool found = false;

			while (!found) {
				if (targetData == *current->data) {
					p = current->data;

					if (current->left == NULL) {
						current->data = current->right->data;
						current->right = NULL;
					} else {						
						current->data = getNextSmallest(current);
					}

					found = true;
				}else if(targetData < *current->data) {
					if (current->left == NULL) {              
						return false;
					} else {
						current = current->left;               
					}
				} else {
					if (current->right == NULL) {
						return false;
					} else {
						current = current->right;         
					}
				}
			}
			return true;
		}
	}

	//helper function to find the next smallest NodeData (largest in the left subtree)
	NodeData* BinTree::getNextSmallest(Node* current)
	{
		current = current->left;

		while(current->right != NULL) {
			current = current->right;
		}

		return current->data;
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// GetDepth: recursively traverses the Tree to find the depth of a particualar NodeData
// Pre Conditions: Tree is properly initialized
// Post Conditions: returns depth of the NodeData or returns 0 if not found
///////////////////////////////////////////////////////////////////////////////////////////////////
	int BinTree::getDepth(const NodeData &targetData) const
	{
		return getDepthHelper(targetData, root, 1);
	}

	int BinTree::getDepthHelper(const NodeData &targetData, Node* current, int depth) const
	{
		if (current == NULL) {
			return 0;
		} 
		
		if (*current->data == targetData) {
			return depth;
		}

		int lDepth = getDepthHelper(targetData, current->left, depth + 1);
		if (lDepth != 0) {
			return lDepth;
		} else {
			int rDepth = getDepthHelper(targetData, current->right, depth + 1);
			return max(lDepth, rDepth);
		}
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// displaySideways: displays the tree by traversing the tree recursively
// Pre Conditions: Tree is properly initialized
// Post Conditions: Displays a binary tree as though you are viewing it from the side
// hard coded displaying to standard output.
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::displaySideways() const {
	   sideways(root, 0);
	}

	void BinTree::sideways(Node* current, int level) const {
	   if (current != NULL) {
		  level++;
		  sideways(current->right, level);

		  // indent for readability, 4 spaces per depth level 
		  for(int i = level; i >= 0; i--) {
			  cout << "    ";
		  }

		  cout << *current->data << endl;        // display information of object
		  sideways(current->left, level);
	   }
	}


////////////////////////////////////////////////////////////////////////////////////////////////////
// bstreeToArray: Fills in an array with data from the tree
// Pre Conditions: Tree and array are properly inialized
// Post Conditions: Array of NodeData is filled in
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::bstreeToArray(NodeData* TreeArray[])
	{
		int index = 0;
		bstreeToArrayHelper(TreeArray, index, root);
		makeEmpty();
	}

	void BinTree::bstreeToArrayHelper(NodeData* TreeArray[], int &index, Node* current)
	{
		if(current == NULL) {
			return;
		}
		
		bstreeToArrayHelper(TreeArray, index, current->left);
		TreeArray[index] = current->data;
		index++;
		bstreeToArrayHelper(TreeArray, index, current->right);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// arrayToBSTree: Recreates the a tree based on the array of NodeData
// Pre Conditions: Tree and array are properly inialized
// Post Conditions: Tree is returned
////////////////////////////////////////////////////////////////////////////////////////////////////
	void BinTree::arrayToBSTree(NodeData* TreeArray[])
	{
		int high = getArraySize(TreeArray);
		int low = 0;
		root = arrayToBSTreeHelper(TreeArray, low, high, root);
	}

	BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData* TreeArray[], int low, int high, Node* &current) 
	{

		if (low > high) {
			return NULL;
		} else {
			current = new Node;     // exception is thrown if memory is not allocated
			current->data = TreeArray[(low + high) / 2];
			TreeArray[(low + high) / 2] = NULL;

			if (low == high) {
				current->left = NULL;
				current->right = NULL;
				return current;
			} else {
				int mid = (low + high) / 2;
				current->right = arrayToBSTreeHelper(TreeArray, mid + 1, high, current->right);
				current->left = arrayToBSTreeHelper(TreeArray, low, mid - 1, current->left);
				return current;
			}
		}
	}

	int BinTree::getArraySize(NodeData* TreeArray[]) const
	{
		int counter = 0;

		while (TreeArray[counter] != NULL) {
			counter++;
		}
		return counter - 1;
	}
