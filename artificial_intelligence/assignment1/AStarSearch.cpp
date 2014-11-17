#include "AStarSearch.h"
#include "Vertex.h"
#include "Graph.h"
#include "Edge.h"
#include <queue>

AStarSearch::AStarSearch()
{
}


AStarSearch::~AStarSearch()
{
}

void AStarSearch::clear()
{
	_graph = nullptr;
	_GCosts.clear();
	_FCosts.clear();
	_SearchFrontier.clear();
	_ShortestPathTree.clear();
	_Source = "";
	_Target = "";
}

bool AStarSearch::operator()(const int &left, const int &right)
{
	return left > right;
}

std::vector<Vertex*> AStarSearch::getShortestPath(const Graph &graph, const int &source, const int &target)
{
	AStarSearch instance = AStarSearch::instance();
	instance.clear();
	std::vector<Vertex*> path;
	//std::priority_queue<int>

	return path;
}
