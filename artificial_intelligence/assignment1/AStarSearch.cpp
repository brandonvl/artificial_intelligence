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

bool AStarSearch::operator()(const std::string &left, const std::string &right)
{
	
}

std::vector<Vertex*> AStarSearch::getShortestPath(const Graph &graph, const std::string &source, const std::string &target)
{
	AStarSearch instance = AStarSearch::instance();
	instance.clear();
	std::vector<Vertex*> path;
	std::priority_queue<std::string, std::vector<std::string>, AStarSearch> pq;

	return path;
}
