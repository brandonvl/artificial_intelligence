#include "AStarSearch.h"
#include "Vertex.h"
#include "Graph.h"
#include "Edge.h"
#include <queue>

AStarSearch::AStarSearch()
{
}

bool AStarSearch::FCostContainer::operator<(const FCostContainer &container) const
{
	if (TOTALDISTANCE != container.TOTALDISTANCE)
		return TOTALDISTANCE < container.TOTALDISTANCE;

	if (VERTEX->getXPos() == container.VERTEX->getXPos())
		return VERTEX->getYPos() < container.VERTEX->getYPos();
	else
		return VERTEX->getXPos() < container.VERTEX->getXPos();
}


AStarSearch::~AStarSearch()
{
}

double AStarSearch::estimatedDistance(Vertex &from, Vertex &to)
{
	float x1 = from.getXPos();
	float x2 = to.getXPos();
	float y1 = from.getYPos();
	float y2 = to.getYPos();

	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

}

void AStarSearch::clear()
{
	/*_graph = nullptr;
	//_GCosts.clear();
	_FCosts.clear();
	_SearchFrontier.clear();
	_ShortestPathTree.clear();
	_Source = -1;
	_Target = -1;*/
}

std::stack<Vertex*> AStarSearch::reconstructPath(Graph &graph, std::map<int, Vertex*> &cameFrom, const int &current)
{
	std::stack<Vertex*> path;
	int quickFix = current;

	path.push(graph.getVertex(current));

	while (cameFrom.find(quickFix) != cameFrom.end()) {
		path.push(cameFrom[quickFix]);
		quickFix = cameFrom[quickFix]->getKey();
		
	}

	return path;
}

std::stack<Vertex*> AStarSearch::getShortestPath(Graph &graph, const int &source, const int &target)
{
	AStarSearch instance = AStarSearch::instance();
	instance.clear();
	std::stack<Vertex*> path;
	std::map<int, Vertex*> cameFrom;
	std::set<FCostContainer> openList;
	std::vector<FCostContainer> _closedList;

	std::vector<double> g_Costs = std::vector<double>(graph.numVertexes()+1);
	std::vector<double> f_Costs = std::vector<double>(graph.numVertexes()+1);

	g_Costs[source] = 0;
	f_Costs[source] = instance.estimatedDistance(*graph.getVertex(source), *graph.getVertex(target));

	openList.insert({ f_Costs[source], g_Costs[source], *graph.getVertex(source) });

	while (!openList.empty()) {

		// Get node with lowest F value
		FCostContainer nextClosestVertex = *openList.begin();

		// Target path found (return shortest path)
		if (nextClosestVertex.VERTEX->getKey() == target)
			return instance.reconstructPath(graph, cameFrom, target);

		// Remove from openlist and add to closedlist
		openList.erase(nextClosestVertex);
		_closedList.push_back(nextClosestVertex);

		// Get all edges to the nextClosedCandidate
		std::list<Edge*> edges = graph.getEdges(nextClosestVertex.VERTEX->getKey());

		for (auto edge : edges)
		{
			// Neighbour in closedlist, skip then
			if (std::find_if(_closedList.begin(), _closedList.end(), [&edge](const FCostContainer &arg) { return arg.VERTEX->getKey() == edge->getDestination(); }) != _closedList.end())
				continue;

			// Calculate distance from source (tentative)
			double g_score = nextClosestVertex.DISTANCETOSOURCE + edge->getWeight();

			auto edgeInOpenList = std::find_if(openList.begin(), openList.end(), [&edge](const FCostContainer &arg) { return arg.VERTEX->getKey() == edge->getDestination(); });

			// edge Not in open list or calculated cost is lower than the one in the open list
			if (edgeInOpenList == openList.end() || g_score < g_Costs[edge->getDestination()])
			{
				// Update parent/child nodes to reflect shortest path
				if (cameFrom.find(edge->getDestination()) == cameFrom.end())
					cameFrom.insert(std::make_pair(edge->getDestination(), nextClosestVertex.VERTEX));
				else
					cameFrom[edge->getDestination()] = nextClosestVertex.VERTEX;

				// Update scores (distance to source & F = G + H(estimated distance)
				g_Costs[edge->getDestination()] = g_score;
				f_Costs[edge->getDestination()] = g_Costs[edge->getDestination()] + instance.estimatedDistance(*graph.getVertex(edge->getDestination()), *graph.getVertex(target));

				// Erase the node if its in the priority queue since we updated the values for this vertex
				if (edgeInOpenList != openList.end())
					openList.erase(edgeInOpenList);

				// Add node to priority queue with correct values (priority will be determined by operator overloading in object (FCostContainer)
				openList.insert({ f_Costs[edge->getDestination()], g_Costs[edge->getDestination()], *graph.getVertex(edge->getDestination()) });
			}
		}
	}

	return path;
}
