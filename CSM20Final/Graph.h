// Graph.h
// Jose Lopez -> Beto
// CS M20
// Final Project

/** @file Graph.h */

#include <map>
#include <set>
#include <queue>

#include "NotFoundException.h"

using namespace std;

/** An adjacency list representation of an undirected,
* weighted graph. */
template<class ItemType>
class Graph
{
protected:
	int numVertices;   /** Number of vertices in the graph. */
	int numEdges;      /** Number of edges in the graph. */

	/** Adjacency list representation of the graph;
	*Outer map-> the first map pair consists of the main vertex (key)
	*Outer map-> The second map pair consists of the (second map) adjacent vertices
	*Inner map-> the first map pair is adjacent vertex (key)
	*Inner map-> the second map pair is the edge weight */
	map<ItemType, map<ItemType, int>> adjList;

	// iterators
	typename map<ItemType, int>::const_iterator iter;
	typename map<ItemType, map<ItemType, int>>::const_iterator iter2;

public:

	/** Constructor.
	* @pre The graph is empty.*/
	Graph();

	/** Determines the number of vertices in the graph.
	* @pre None.
	* @post None.
	* @return The number of vertices in the graph. */
	int getNumVertices() const { return numVertices; } // inline

	/** Determines the number of edges in the graph.
	* @pre None.
	* @post None.
	* @return The number of edges in the graph. */
	int getNumEdges() const { return numEdges; } // inline

	/* getVertex()
	Will return vertex, if the vertex exists.
	input: ItemType item in vertex
	output: ItemType vertex
	*/
	ItemType getVertex(const ItemType & vert) throw(NotFoundException);

	/** Determines the weight of an edge.
	* @pre The edge exists in the graph.
	* @post None.
	* @return The weight of the edge parameter. */
	int getWeight(ItemType start, ItemType end) throw(NotFoundException);

	/** Creates an edge in the graph.
	* @pre The vertices exist in the graph.
	* @post Adds to both v and w's list. */
	bool add(const ItemType & start, const ItemType & end, const int & weight);

	/** Removes an edge from the graph.
	* @pre The vertices exist in the graph.
	* @post Removes edges from both v and w's list. */
	bool remove(const ItemType & start, const ItemType & end);

	/* isEmpty()
	checks to see if the graph is empty
	input: none
	output: true if it's empty, false otherwise
	*/
	bool isEmpty() const { return numVertices == 0; }  // inline

	/*
	Performs a breadth-first search of this graph beginning at the given
	vertex and calls a given function one for each vertex visited.
	input: start (ItemType) vertex to begin BFS. visit, a client-defined
	function that performs an operation on or with each visited vertex.
	output: none
	*/
	void breadthFirstTraversal(const ItemType & start, void visit(ItemType &));

}; // end Graph
   // End of header file

   /** @file Graph.cpp
   * An adjacency list representation of an undirected,
   * weighted graph. */

template<class ItemType>
Graph<ItemType>::Graph() : numVertices(0), numEdges(0)
{}  // end constructor

template<class ItemType>
ItemType Graph<ItemType>::getVertex(const ItemType & vert) throw(NotFoundException)
{
	if (adjList.count(vert))
		return adjList.find(vert)->first;  // if in graph, return vertex
	else
	{
		string message = "Vertex not in the graph";
		throw(NotFoundException(message));
	}
}

template<class ItemType>
int Graph<ItemType>::getWeight(ItemType start, ItemType end)
throw(NotFoundException)
{
	if (adjList.count(start) && adjList[start].count(end)) // Does the edge exist?
		return adjList[start].find(end)->second; // The weight is in the inner map
	else
	{
		string message = "edge not in the graph";
		throw(NotFoundException(message));
	}

}  // end getWeight

template<class ItemType>
bool Graph<ItemType>::add(const ItemType & start, const ItemType & end, const int & weight)
{
	if (!adjList.count(start))  // Is the first vertex already established?
		numVertices++;       // If not it will be created by map class, just add to count

	adjList[start].insert(make_pair(end, weight));

	// Going the opposite direction
	if (!adjList.count(end))  // Is the first vertex already established?
		numVertices++;       // If not it will be created by map class, just add to count

	adjList[end].insert(make_pair(start, weight));

	numEdges++;    // New edge added

	return true;  // Notify client that it was added
}  // end add

template<class ItemType>
bool Graph<ItemType>::remove(const ItemType & start, const ItemType & end)
{
	bool success = false;	// Be pessimistic

	// count() returns 1 if the key is in map, otherwise 0
	if (adjList[start].count(end))   // Does the edge exist?
	{
		adjList[start].erase(end); // Erase adjacent vertex

		if (adjList[start].empty())  // is the vertex empty?
		{
			adjList.erase(start);   // If yes, remove.
			numVertices--;          // Remove vertex from count
		}

		//Going the opposite direction
		adjList[end].erase(start);  // Erase the other adjacent vertex

		if (adjList[end].empty()) // is the vertex (from opposite direction) empty?
		{
			adjList.erase(end);   // if yes, remove
			numVertices--;        // Remove vertex from count
		}

		numEdges--;     // edge removed
		success = true; // To notify the clien that the edge was removed successfully
	}

	return success;
}  // end remove()

template<class ItemType>
void Graph<ItemType>::breadthFirstTraversal(const ItemType & start, void visit(ItemType &))
{

	set<ItemType> mark;  // To mark visited vertices
	ItemType item, buf;  // for visit function
	queue<ItemType> q;	// a new empty queue

	item = adjList.find(start)->first;
	q.push(item);  // Add to queue and mark it
	mark.insert(item);
	visit(item);		// call client function

	while (!q.empty())
	{
		buf = q.front();  // Access first element
		q.pop();

		// use const_iterator to walk through elements
		for (iter = adjList[buf].begin(); iter != adjList[buf].end(); ++iter)
		{
			item = iter->first;

			if (!mark.count(item))  // To make sure we haven't visited this node
			{
				visit(item); // call client function
				q.push(item); // add to queue after visit
				mark.insert(item);
			}
		}
	}
}  // end breadthFirstTraversal()