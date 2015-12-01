#ifndef BINODE_H
#define BINODE_H

template<class Type>
class BinaryNode
{
private:
	Type		item;
	BinaryNode<Type>*	left;
	BinaryNode<Type>*	right;
public:
	BinaryNode() : left(nullptr), right(nullptr) {}	// Default Constructor
	BinaryNode(const Type& anItem) : item(anItem), left(nullptr), right(nullptr) {}
	BinaryNode(const Type& anItem, BinaryNode<Type>* leftNodePtr, BinaryNode<Type>* rightNodePtr) : item(anItem), left(leftNodePtr), right(rightNodePtr) {}

	void setItem(const Type& anItem) { item = anItem; }	// Set's item to specified value
	Type getItem() const { return item; }	// Return value stored in node

	void setLeft(BinaryNode<Type>* LeftNodePtr) { left = LeftNodePtr; }	// Set left pointer to left child node's address
	void setRight(BinaryNode<Type>* RightNodePtr) { right = RightNodePtr; }	// Set left pointer to right child node's address
	BinaryNode<Type>* getLeft() const { return left; }	// Return address of left child
	BinaryNode<Type>* getRight() const { return right; }	// Return address of right child

	bool isLeaf() { return ((left == nullptr) && (right == nullptr)) };
};
#endif