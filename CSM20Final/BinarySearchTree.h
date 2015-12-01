#ifndef BIN_SEARCH_TREE
#define BIN_SEARCH_TREE

#include "BinaryNodeTree.h"

template<class Type>
class BinarySearchTree : public BinaryNodeTree<Type>
{
public:
	/////////////////////////////
	// Constructors/Destructor //
	/////////////////////////////
	BinarySearchTree() : BinaryNodeTree<Type>() { }	// Default Contructor for BinarySearchTree.
	BinarySearchTree(const Type& rootItem) : BinaryNodeTree(rootItem) { }	// Overloaded constructor 1
	BinarySearchTree(const BinarySearchTree<Type>& aTree) : BinaryNodeTree(aTree) { }	// Copy constructor
	virtual ~BinarySearchTree() { }	// Destructor
	/////////////////////////////

	////////////////////////////////
	// Public interface functions //
	////////////////////////////////
	bool add(const Type& newData);
	bool remove(const Type& anEntry);
	Type getEntry(const Type& entry) const throw(NotFoundException);
	bool contains(const Type& entry) const;
	////////////////////////////////

	// Overloaded Operators //
	BinarySearchTree<Type>& operator=(const BinarySearchTree<Type>& right);

protected:
	///////////////////////////////
	// Private Utility Functions //
	///////////////////////////////
	BinaryNode<Type>* weightedAdd(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr);
	BinaryNode<Type>* findNode(BinaryNode<Type>* subTreePtr, const Type& value) const;
	BinaryNode<Type>* removeValue(BinaryNode<Type>* subTreePtr, const Type& target, bool& success);
	///////////////////////////////
};


// Begin add
template<class Type>
bool BinarySearchTree<Type>::add(const Type &newData)
{
	BinaryNode<Type>* newNodePtr = new BinaryNode<Type>(newData);
	BinaryNodeTree::rootPtr = weightedAdd(rootPtr, newNodePtr);

	return true;
}	// End add

// Begin weightedAdd; Adds new nodes to tree based on relative size of data.
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::weightedAdd(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		BinaryNode<Type>* leftPtr = subTreePtr->getLeft();
		BinaryNode<Type>* rightPtr = subTreePtr->getRight();

		if (newNodePtr->getItem() > subTreePtr->getItem())
		{
			rightPtr = weightedAdd(rightPtr, newNodePtr);
			subTreePtr->setRight(rightPtr);
		}
		else
		{
			leftPtr = weightedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeft(leftPtr);
		}

		return subTreePtr;
	}
}	// End balancedAdd

// Begin overload operator=
template<class Type>
BinarySearchTree<Type>& BinarySearchTree<Type>::operator=(const BinarySearchTree<Type>& right)
{
	clear();
	rootPtr = BinaryNodeTree<Type>::copyTree(right.rootPtr);

	return *this;
}	// End overload operator=

#if 1
// Begin findNode
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::findNode(BinaryNode<Type>* subTreePtr, const Type& value) const
{
	if (subTreePtr == nullptr)
		return nullptr;
	else if (subTreePtr->getItem() == value)
		return subTreePtr;
	else
	{
		if (value > subTreePtr->getItem())
			return findNode(subTreePtr->getRight(), value);
		else
			return findNode(subTreePtr->getLeft(), value);
	}
}	// End findNode
#endif

//Begin remove; Public interface for removing nodes by value.
template<class Type>
bool BinarySearchTree<Type>::remove(const Type& entry)
{
	bool status = false;
	rootPtr = removeValue(rootPtr, entry, status);
	return status;
}	// End remove

// Begin removeValue; Removes node containing the given value, then replaces it with its successor.
template<class Type>
BinaryNode<Type>* BinarySearchTree<Type>::removeValue(BinaryNode<Type>* subTreePtr, const Type& target, bool& success)
{
	if (subTreePtr == nullptr)	// If node is empty: removal fails, return null
	{
		success = false;
		return nullptr;
	}
	else if (subTreePtr->getItem() == target)	// If node contains the target: remove the node and return its successor.
	{
		subTreePtr = removeNode(subTreePtr);	// Remove node and re-link any children to main tree.
		success = true;
		return subTreePtr;
	}
	else		// If node does not contain target: proceed to search tree.
	{
		BinaryNode<Type>* tempPtr;
		if (target > subTreePtr->getItem())
		{
			tempPtr = removeValue(subTreePtr->getRight(), target, success);
			if (success)
				subTreePtr->setRight(tempPtr);
			return subTreePtr;
		}
		else
		{
			tempPtr = removeValue(subTreePtr->getLeft(), target, success);
			if (success)
				subTreePtr->setLeft(tempPtr);
			return subTreePtr;
		}
	}
}	// End removeValue

// Begin getEntry
template<class Type>
Type BinarySearchTree<Type>::getEntry(const Type& anEntry) const
{
	BinaryNode<Type>* nodeAt = findNode(rootPtr, anEntry);
	if (nodeAt == nullptr)
		throw (NotFoundException("Value not found in tree."));
	else
		return nodeAt->getItem();
}

// Being contains
template<class Type>
bool BinarySearchTree<Type>::contains(const Type& anEntry) const
{
	if (findNode(rootPtr, anEntry) == nullptr)
		return false;
	else
		return true;
}	// End contains
#endif