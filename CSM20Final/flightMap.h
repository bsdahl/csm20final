// flightMap.h
// Jose Lopez -> Beto
// CS M20
// Final Project

#include <limits>
#include "Graph.h"

using namespace std;

template <class ItemType>
class flightMap : public Graph<ItemType>
{

public:
	flightMap() : Graph<ItemType>() {}  // Constructor -> inline function

	size_t shortestPath(const ItemType & start, const ItemType & end);
};

/* shorterstPath()
Function will calculates the shortest path between
the starting vertex (start), and the end vertex (end).
* @pre The vertices exist in the graph.
input: starting and ending vertices.
output: the shortest path between the two vertices (size_t)
*/
template<class ItemType>
size_t flightMap<ItemType>::shortestPath(const ItemType & start, const ItemType & end)
{
	// This is an implementation of Dijkstra's algorithm to find the 
	// shortest path between two vertices --> used BFS traversals

	bool found = false;
	queue<pair<ItemType, int>> Q;
	map<ItemType, int> distance;  // Will contain the distances from origin to all other vertices

    for (Graph<ItemType>::iter2 = Graph<ItemType>::adjList.begin();
	Graph<ItemType>::iter2 != Graph<ItemType>::adjList.end(); ++Graph<ItemType>::iter2)
		distance[Graph<ItemType>::iter2->first] = std::numeric_limits<int>::max(); // first make all distances infinite

	distance[start] = 0;		// from-and-to starting vertex is distance zero
	Q.push(make_pair(start, distance[start]));

	while (!Q.empty() && !found)
	{
		ItemType u = Q.front().first;
		Q.pop();

		if (u == end)
			found = true;  // Because we're only interested in destination vertex.

		if (!found)
		{
			for (Graph<ItemType>::iter = Graph<ItemType>::adjList[u].begin();
			Graph<ItemType>::iter != Graph<ItemType>::adjList[u].end(); ++Graph<ItemType>::iter)
			{
				ItemType v = Graph<ItemType>::iter->first;	    // get adjecent vertex
				int w = Graph<ItemType>::iter->second;           // get edge weight

				if (distance[v] > distance[u] + w)  // Looks for shortest path
				{
					distance[v] = distance[u] + w;
					Q.push(make_pair(v, distance[v]));
				}
			}
		}
	}

	return static_cast<size_t>(distance[end]); // return cost of desired route
}