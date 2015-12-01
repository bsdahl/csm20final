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
	flightMap() : Graph() {}  // Constructor -> inline function 

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

	for (iter2 = adjList.begin(); iter2 != adjList.end(); ++iter2)
		distance[iter2->first] = std::numeric_limits<int>::max(); // first make all distances infinite

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
			for (iter = adjList[u].begin(); iter != adjList[u].end(); ++iter)
			{
				ItemType v = iter->first;	    // get adjecent vertex
				int w = iter->second;           // get edge weight

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