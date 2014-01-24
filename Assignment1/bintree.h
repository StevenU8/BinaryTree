#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"

class BinTree
{

	//overloaded operator<<
	friend ostream & operator<<(ostream &, const BinTree &);

private: 
	struct Node { 
		NodeData* data; // pointer to data object 
		Node* left;		// left subtree pointer 
		Node* right;	// right subtree pointer 
	}; 
	Node* root;			// root of the tree 
 
	// provided, helper for displaySideways()
	void sideways(Node*, int) const; 
	
	//helper to operator<<
	void DisplayInOrder(ostream &, const Node*) const;  

	//helper for copy constructor assignment operator
	void CopyTree(Node* &current, const Node* otherCurrent);

	//helper function to recursively find depth of a specific NodeData
	int getDepthHelper(const NodeData &,  Node*, int) const;

	//helper function to determine if two trees are equal by traversing recursively
	bool equal(const Node* current, const Node* otherCurrent) const;

	//helper to take data from a tree and put it into an array
	void bstreeToArrayHelper(NodeData* TreeArray[], int &index, Node* current);

	//helper to take NodeData from an array and put it into a tree
	Node* arrayToBSTreeHelper(NodeData* TreeArray[], int low, int high, Node* &current);

	//helper to find how many items are in the array
	int getArraySize(NodeData* TreeArray[]) const;

	//helper to get the next smallest item. Used in remove
	NodeData* getNextSmallest(Node* current);

	//helper function to make the tree empty
	void makeEmptyHelper(Node* &);

public:

	//default constructor 
	BinTree(); 

	//copy constructor 
	BinTree(const BinTree &); 

	//destructor
	~BinTree(); 

	//check if the tree is empty. True if tree is empty, otherwise false 
	bool isEmpty() const; 

	//make the tree empty so isEmpty returns true 
	void makeEmpty(); 
	
	//assignment operator
	BinTree& operator=(const BinTree &); 

	//equals and not equals operators
	bool operator==(const BinTree &) const; 
	bool operator!=(const BinTree &) const;

	//finds the depth of a specific NodeData
	int getDepth(const NodeData &) const;

	//inserts a NodeData element into the binary search tree
	bool insert(NodeData*); 

	//removes a NodeData from the tree and sets a pointer to it so it is not lost
	bool remove(const NodeData &, NodeData*&);

	//retrieves the location of a NodeData
	bool retrieve(const NodeData &, NodeData*&) const; 

	//provided, displays the tree sideways 
	void displaySideways() const; 

	//ake NodeData from a tree and puts it into an array
	void bstreeToArray(NodeData* []);
	
	//take NodeData from an array and put it into a tree
	void arrayToBSTree(NodeData* []); 

};

#endif
