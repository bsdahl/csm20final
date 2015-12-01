/*
Definition file for AVLTree class.
*/

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include "BinarySearchTree.h"
#include "BinaryNode.h"

template<class Type>
class AVLTree : public BinarySearchTree<Type>
{
public:
	/////////////////
	// Constructor //
	/////////////////
	AVLTree() : BinarySearchTree<Type>() {}

	////////////////////////////////
	// Public interface functions //
	////////////////////////////////
	bool add(const Type&);
	bool remove(const Type&);


private:
	///////////////////////////////
	// Private utility functions //
	///////////////////////////////
	int checkBalance(const BinaryNode<Type>* aNode) const;
	int getBalance() const { return checkBalance(BinaryNodeTree<Type>::rootPtr); }
	BinaryNode<Type>* rebalanceTree(BinaryNode<Type>* nextNode);
	BinaryNode<Type>* rotateLeft(BinaryNode<Type>*);
	BinaryNode<Type>* rotateRight(BinaryNode<Type>*);

	///////////////////////////////
	// Private, unused functions //
	///////////////////////////////
	AVLTree(AVLTree<Type>&);
	AVLTree& operator=(const AVLTree<Type>&);
};


template<class Type>
int AVLTree<Type>::checkBalance(const BinaryNode<Type>* aNode) const
{
	return BinaryNodeTree<Type>::getHeightHelper(aNode->getLeft()) - BinaryNodeTree<Type>::getHeightHelper(aNode->getRight());
}	// End checkBalance

template<class Type>
bool AVLTree<Type>::add(const Type& newData)
{
	if (BinarySearchTree<Type>::contains(newData))
		return false;
	BinarySearchTree<Type>::add(newData);
	BinaryNodeTree<Type>::rootPtr = rebalanceTree(BinaryNodeTree<Type>::rootPtr);

	return true;
}	// End add

template<class Type>
bool AVLTree<Type>::remove(const Type& entry)
{
	if (!BinarySearchTree<Type>::contains(entry))
		return false;
	BinarySearchTree<Type>::remove(entry);
	BinaryNodeTree<Type>::rootPtr = rebalanceTree(BinaryNodeTree<Type>::rootPtr);

	return true;
}	// End remove

template<class Type>
BinaryNode<Type>* AVLTree<Type>::rebalanceTree(BinaryNode<Type>* thisNode)
{
	int balance = checkBalance(thisNode);
	if (balance > 1)	// Left High
	{
		int childBalance = checkBalance(thisNode->getLeft());
		if (childBalance > 1 || childBalance < -1)	// Left child still too high
		{
			thisNode->setLeft(rebalanceTree(thisNode->getLeft()));
			return thisNode;
		}
		else if (childBalance == 1) // Left of Left imbalance
		{
			return rotateRight(thisNode);
		}
		else if (childBalance == -1) // Right of Left imbalance
		{
			BinaryNode<Type>* nodePtr = rotateLeft(thisNode->getLeft());
			thisNode->setLeft(nodePtr);
			return rotateRight(thisNode);
		}
		else
			return thisNode;
	}
	else if (balance < -1) // Right High
	{
		int childBalance = checkBalance(thisNode->getRight());
		if (childBalance > 1 || childBalance < -1)	// Right child still too high
		{
			thisNode->setRight(rebalanceTree(thisNode->getRight()));
			return thisNode;
		}
		else if (childBalance == 1) // Left of Right imbalance
		{
			BinaryNode<Type>* nodePtr = rotateRight(thisNode->getRight());
			thisNode->setRight(nodePtr);
			return rotateLeft(thisNode);
		}
		else if (childBalance == -1) // Right of Right imbalance
		{
			return rotateLeft(thisNode);
		}
		thisNode->setRight(rebalanceTree(thisNode->getRight()));
		return thisNode;
	}
	else	// Equal balance
		return thisNode;
}	// End rebalanceTree

template<class Type>
BinaryNode<Type>* AVLTree<Type>::rotateLeft(BinaryNode<Type>* nodePtr)
{
	BinaryNode<Type>* childNode = nodePtr->getRight();
	nodePtr->setRight(childNode->getLeft());
	childNode->setLeft(nodePtr);

	return childNode;
}

template<class Type>
BinaryNode<Type>* AVLTree<Type>::rotateRight(BinaryNode<Type>* nodePtr)
{
	BinaryNode<Type>* childNode = nodePtr->getLeft();
	nodePtr->setLeft(childNode->getRight());
	childNode->setRight(nodePtr);
	return childNode;
}	// End rotateRight
#endif