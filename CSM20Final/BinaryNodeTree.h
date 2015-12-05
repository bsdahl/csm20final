#pragma warning(disable : 4290)

#ifndef BINODE_TREE_H
#define BINODE_TREE_H

//#define BNT_DEBUG

#ifdef BNT_DEBUG
const int TREE_ROWS = 20;
#endif

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>


#include "BinaryNode.h"

template<class Type>
class BinaryNodeTree
{
protected:
	BinaryNode<Type>* rootPtr;

	////////////////////////////////
	// Protected helper functions //
	////////////////////////////////
	int getHeightHelper(BinaryNode<Type>*) const;
	int getNumberOfNodesHelper(BinaryNode<Type>*) const;
	BinaryNode<Type>* balancedAdd(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr);
	BinaryNode<Type>* removeValue(BinaryNode<Type>* subTreePtr, const Type& target, bool& success);
	BinaryNode<Type>* removeNode(BinaryNode<Type>* nodePtr);
	BinaryNode<Type>* findInorderSuccessor(BinaryNode<Type>* parentNodePtr, BinaryNode<Type>* subTreePtr);
	BinaryNode<Type>* copyTree(const BinaryNode<Type>* treePtr) const;
	BinaryNode<Type>* findNode(BinaryNode<Type>* subTreePtr, const Type& value) const;
	void destroyTree(BinaryNode<Type>* subTreePtr);
	////////////////////////////////

	///////////////////////////////////
	// Recursive Traversal Functions //
	///////////////////////////////////
	template<class Function>
	void preorder(Function& visit, BinaryNode<Type>* treePtr) const;
	template<class Function>
	void inorder(Function& visit, BinaryNode<Type>* treePtr) const;
	template<class Function>
	void postorder(Function& visit, BinaryNode<Type>* treePtr) const;

	///////////////////////
	// Exception Classes //
	///////////////////////
	class NotFoundException : public std::logic_error
	{
	public:
		NotFoundException(const std::string& message = "") : logic_error("Not Found Exception: " + message) {}
	}; // end NotFoundExcep

	class PrecondViolatedExcep : public std::runtime_error
	{
	public:
		PrecondViolatedExcep(std::string message) : runtime_error("\nPrecondition Violated Exception: " + message + "\n") { }
	};


#ifdef BNT_DEBUG
	void drawTreeHelper(BinaryNode<Type>*, std::string*, int);
#endif

public:
	/////////////////////////////
	// Constructors/Destructor //
	/////////////////////////////
	BinaryNodeTree() : rootPtr(nullptr) { }	// Default Contructor for BinaryNodeTree.
	BinaryNodeTree(const Type& rootItem) { rootPtr = new BinaryNode<Type>(rootItem, nullptr, nullptr); }	// Overloaded constructor 1
	BinaryNodeTree(const Type& rootItem, const BinaryNodeTree<Type>* leftPtr, const BinaryNodeTree<Type>* rightPtr)
		{ rootPtr = new BinaryNode<Type>(rootItem, copyTree(leftPtr), copyTree(rightPtr)); }// Overloaded constructor 2

	BinaryNodeTree(const BinaryNodeTree<Type>& aTree) { rootPtr = copyTree(aTree.rootPtr); }	// Copy constructor

	virtual ~BinaryNodeTree() { clear(); }	// Destructor
	/////////////////////////////

	////////////////////////////////
	// Public interface functions //
	////////////////////////////////
	bool isEmpty() const { return (rootPtr == nullptr); }
	int getHeight() const { return getHeightHelper(rootPtr); }
	int getNumberOfNodes() const { return getNumberOfNodesHelper(rootPtr); }
	Type getRootData() const throw(PrecondViolatedExcep);
	void setRootData(const Type& newData);
	Type getEntry(const Type& entry) const throw(NotFoundException);
	bool add(const Type& newData);
	bool remove(const Type& entry);
	bool contains(const Type& entry) const;
	void clear() { destroyTree(rootPtr); }
	template<class Function>
	void preorderTraverse(Function& visit) const { preorder(visit, rootPtr); }
	template<class Function>
	void inorderTraverse(Function& visit) const { inorder(visit, rootPtr); }
	template<class Function>
	void postorderTraverse(Function& visit) const { postorder(visit, rootPtr); }
	///////////////////////////////
	
	// Overloaded Operators //
	BinaryNodeTree<Type>& operator=(const BinaryNodeTree<Type>& right);

#ifdef BNT_DEBUG
	void drawTree();
#endif
};

	// Begin getRootData
template<class Type>
Type BinaryNodeTree<Type>::getRootData() const throw (PrecondViolatedExcep)
{
	if (!isEmpty())
		return rootPtr->getItem();
	else
		throw(PrecondViolatedExcep("Tree is empty."));
}	// End getRootData

	// Begin setRootData
template<class Type>
void BinaryNodeTree<Type>::setRootData(const Type& newData)
{
	if (!isEmpty())	
		rootPtr->setItem(newData);
	else
		add(newData); // If tree is empty, add a new node with the given data.
}	// End setRootData


	// Begin getEntry
template<class Type>
Type BinaryNodeTree<Type>::getEntry(const Type& anEntry) const throw(NotFoundException)
{
	BinaryNode<Type>* nodeAt = findNode(rootPtr, anEntry);
	if (nodeAt == nullptr)
		throw (NotFoundException("Value not found in tree."));
	else
		return nodeAt->getItem();
}

	// Being contains
template<class Type>
bool BinaryNodeTree<Type>::contains(const Type& anEntry) const
{
	if (findNode(rootPtr, anEntry) == nullptr)
		return false;
	else
		return true;
}	// End contains

	// Begin findNode
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::findNode(BinaryNode<Type>* subTreePtr, const Type& value) const
{
	if (subTreePtr == nullptr)
		return nullptr;
	else if (subTreePtr->getItem() == value)
		return subTreePtr;
	else
	{
		BinaryNode<Type>* nextPtr = findNode(subTreePtr->getLeft(), value);
		if (nextPtr == nullptr)
			nextPtr = findNode(subTreePtr->getRight(), value);

		return nextPtr;
	}
}	// End findNode

	// Begin add
template<class Type>
bool BinaryNodeTree<Type>::add(const Type &newData)
{
	BinaryNode<Type>* newNodePtr = new BinaryNode<Type>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);

	return true;
}	// End add

	// Begin balancedAdd; Adds new nodes to shortest side of tree in order of left to right.
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::balancedAdd(BinaryNode<Type>* subTreePtr, BinaryNode<Type>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		BinaryNode<Type>* leftPtr = subTreePtr->getLeft();
		BinaryNode<Type>* rightPtr = subTreePtr->getRight();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRight(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeft(leftPtr);
		}

		return subTreePtr;
	}
}	// End balancedAdd

	//Begin remove; Public interface for removing nodes by value.
template<class Type>
bool BinaryNodeTree<Type>::remove(const Type& entry)
{
	bool status = false;
	rootPtr = removeValue(rootPtr, entry, status);
	return status;
}	// End remove

	// Begin removeValue; Removes node containing the given value, then replaces it with its successor.
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::removeValue(BinaryNode<Type>* subTreePtr, const Type& target, bool& success)
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
	else		// If node does not contain target: proceed to traverse tree in pre-order until target is found.
	{
		BinaryNode<Type>* tempPtr = removeValue(subTreePtr->getLeft(), target, success);	// Recursively check left side of sub-tree
		if (success)
			subTreePtr->setLeft(tempPtr);	// If target found as node left of current node: set current node leftPtr to removed node's successor.
		else
		{
			tempPtr = removeValue(subTreePtr->getRight(), target, success);	// If target is not found in left tree: recursively check right sub-tree.
			subTreePtr->setRight(tempPtr);	// If target found as node right of current node: set current node rightPtr to removed node's successor.
		}
		return subTreePtr;
	}
}	// End removeValue

	// Begin removeNode: deletes a node and returns any children back to the main tree to be re-linked.
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::removeNode(BinaryNode<Type>* nodePtr)
{
	// Case if target is leaf: delete leaf and return nullptr.
	if ((nodePtr->getLeft() == nullptr) && (nodePtr->getRight() == nullptr))
	{
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	// Case if target has one child: return pointer to child of deleted node.
	else if (!(nodePtr->getLeft() != nullptr) != !(nodePtr->getRight() != nullptr))	// Exclusive or checking for left child or right child
	{
		BinaryNode<Type>* nodeToConnectPtr;
		if (nodePtr->getLeft() != nullptr)
			nodeToConnectPtr = nodePtr->getLeft();
		else
			nodeToConnectPtr = nodePtr->getRight();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	// Case if target has two children: Find inorder successor of deleted node, connect it to deleted node's children, then return the successor.
	else
	{
		BinaryNode<Type>* nodeToConnectTo = findInorderSuccessor(nodePtr, nodePtr->getRight());
		nodeToConnectTo->setLeft(nodePtr->getLeft());
		if (nodeToConnectTo != nodePtr->getRight()) // If successor is right child of deleted node: do not change right child of successor.
			nodeToConnectTo->setRight(nodePtr->getRight());	// Else: set successor right child to deleted node's right child.
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectTo;
	}
}

	// Begin findInorderSuccessor: Locate left-most node in right sub-tree of deleted node.
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::findInorderSuccessor(BinaryNode<Type>* parentNodePtr, BinaryNode<Type>* subTreePtr)
{
	if (subTreePtr->getLeft() != nullptr)	// If not leftmost node: recursively run again with left child.
		return findInorderSuccessor(subTreePtr, subTreePtr->getLeft());
	else	// If leftmost node: set left-child of parent node to the right-child of successor node, then return successor.
	{
		if (parentNodePtr->getRight() != subTreePtr)		// If parent node is the removed node: do not change left child of parent node.
			parentNodePtr->setLeft(subTreePtr->getRight()); // Else: Set parent node's left child to right child of successor node.
		return subTreePtr;
	}

}	// End findInorderSuccessor
	// Begin getHeightHelper
template<class Type>
int BinaryNodeTree<Type>::getHeightHelper(BinaryNode<Type>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + std::max(getHeightHelper(subTreePtr->getLeft()), getHeightHelper(subTreePtr->getRight()));
}	// End getHeightHelper

	// Begin getNumberOfNodesHelper
template<class Type>
int BinaryNodeTree<Type>::getNumberOfNodesHelper(BinaryNode<Type>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
	{
		int numNodes = 1;
		numNodes += getNumberOfNodesHelper(subTreePtr->getLeft());
		numNodes += getNumberOfNodesHelper(subTreePtr->getRight());
		return numNodes;
	}
}

	// Begin copyTree
template<class Type>
BinaryNode<Type>* BinaryNodeTree<Type>::copyTree(const BinaryNode<Type>* treePtr) const
{
	BinaryNode<Type>* newTreePtr = nullptr;

	if (treePtr != nullptr)
	{
		// Traverse target tree in preorder and create copies of each node recursively.
		newTreePtr = new BinaryNode<Type>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeft(copyTree(treePtr->getLeft()));
		newTreePtr->setRight(copyTree(treePtr->getRight()));
	}

	return newTreePtr;
}	// End copyTree

	// Begin overload operator=
template<class Type>
BinaryNodeTree<Type>& BinaryNodeTree<Type>::operator=(const BinaryNodeTree<Type>& right)
{
	clear();
	rootPtr = copyTree(right.rootPtr);

	return *this;
}	// End overload operator=

	// Begin destroyTree
template<class Type>
void BinaryNodeTree<Type>::destroyTree(BinaryNode<Type>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		// Traverse target tree in postorder and delete nodes recursively.
		destroyTree(subTreePtr->getLeft());
		destroyTree(subTreePtr->getRight());
		delete subTreePtr;
		subTreePtr = nullptr;
	}
}	 // End destroyTree

	// Start preorder
template<class Type>
template<class Function>
void BinaryNodeTree<Type>::preorder(Function& visit, BinaryNode<Type>* treePtr) const
{
	if (treePtr != nullptr)
	{
		Type nodeItem = treePtr->getItem();
		visit(nodeItem);
		preorder(visit, treePtr->getLeft());
		preorder(visit, treePtr->getRight());
	}

}	// End preorder

// Start inorder
template<class Type>
template<class Function>
void BinaryNodeTree<Type>::inorder(Function& visit, BinaryNode<Type>* treePtr) const
{
	if (treePtr != nullptr)
	{
		Type nodeItem = treePtr->getItem();
		inorder(visit, treePtr->getLeft());
		visit(nodeItem);
		inorder(visit, treePtr->getRight());
	}

}	// End inorder

// Start postorder
template<class Type>
template<class Function>
void BinaryNodeTree<Type>::postorder(Function& visit, BinaryNode<Type>* treePtr) const
{
	if (treePtr != nullptr)
	{
		Type nodeItem = treePtr->getItem();
		postorder(visit, treePtr->getLeft());
		postorder(visit, treePtr->getRight());
		visit(nodeItem);
	}

}	// End postorder

#ifdef BNT_DEBUG	// begin DEBUG
template<class Type>
void BinaryNodeTree<Type>::drawTree()
{
	std::string rows[TREE_ROWS];
	int layer = 0;
	drawTreeHelper(rootPtr, rows, layer);
	
	for (int i = 0; i < TREE_ROWS; i++)
		std::cout << rows[i] << "\n";
}

template<class Type>
void BinaryNodeTree<Type>::drawTreeHelper(BinaryNode<Type>* subTreePtr, std::string* arr, int layer)
{
	if (layer < TREE_ROWS)
	{
		std::stringstream buffer;
		buffer.str("");
		if (subTreePtr != nullptr)
		{
			buffer << subTreePtr->getItem();
		}
		arr[layer] += "\t" + buffer.str();
		if (subTreePtr != nullptr)
		{
			layer++;
			drawTreeHelper(subTreePtr->getLeft(), arr, layer);
			arr[layer] += "L";
			drawTreeHelper(subTreePtr->getRight(), arr, layer);
			arr[layer] += "R\t||";

		}
	}
}
#endif	// End DEBUG

#endif