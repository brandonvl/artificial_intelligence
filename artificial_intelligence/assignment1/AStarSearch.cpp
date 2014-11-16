#include "AStarSearch.h"
#include "Vertex.h"
#include "Graph.h"
#include "Edge.h"

AStarSearch::AStarSearch()
{
}


AStarSearch::~AStarSearch()
{
}

void AStarSearch::clear()
{
	_GCosts.clear();
	_FCosts.clear();
	_SearchFrontier.clear();
	_ShortestPathTree.clear();
	_Source = "";
	_Target = "";
}

std::vector<Vertex*> AStarSearch::getShortestPath(const Graph &graph, const std::string &source, const std::string &target)
{
	AStarSearch instance = AStarSearch::instance();
	std::vector<Vertex*> path;

	return path;
}
