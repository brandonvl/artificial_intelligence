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

	if (VERTEX->getXPos() != container.VERTEX->getXPos())
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

std::vector<Vertex*> AStarSearch::reconstructPath(std::map<int, Vertex*> &cameFrom, const int &current)
{
	std::vector<Vertex*> path;

	int quickFix = current;

	while (cameFrom.find(quickFix) != cameFrom.end()) {
		path.push_back(cameFrom[quickFix]);
		quickFix = cameFrom[quickFix]->getKey();
	}
	

	return path;
}

std::vector<Vertex*> AStarSearch::getShortestPath(Graph &graph, const int &source, const int &target)
{
	AStarSearch instance = AStarSearch::instance();
	instance.clear();
	std::vector<Vertex*> path;
	std::map<int, Vertex*> cameFrom;
	std::set<FCostContainer> openList;
	std::vector<FCostContainer> _closedList;

	std::vector<double> g_Costs = std::vector<double>(graph.numVertexes()+1);
	std::vector<double> f_Costs = std::vector<double>(graph.numVertexes()+1);

	g_Costs[source] = 0;
	f_Costs[source] = instance.estimatedDistance(*graph.getVertex(source), *graph.getVertex(target));

	openList.insert({ f_Costs[source], g_Costs[source], *graph.getVertex(source) });

	while (!openList.empty()) {

		FCostContainer nextClosestVertex = *openList.begin();

		if (nextClosestVertex.VERTEX->getKey() == target)
			return instance.reconstructPath(cameFrom, target);

		openList.erase(nextClosestVertex);
		_closedList.push_back(nextClosestVertex);

		std::list<Edge*> edges = graph.getEdges(nextClosestVertex.VERTEX->getKey());

		for (auto edge : edges)
		{
			if (std::find_if(_closedList.begin(), _closedList.end(), [&edge](const FCostContainer &arg) { return arg.VERTEX->getKey() == edge->getDestination(); }) != _closedList.end())
				continue;

			double g_score = nextClosestVertex.DISTANCETOSOURCE + edge->getWeight(); // todo function actualy fucked up shit

			if (std::find_if(openList.begin(), openList.end(), [&edge](const FCostContainer &arg) { return arg.VERTEX->getKey() == edge->getDestination(); }) == openList.end() || g_score < g_Costs[edge->getDestination()])
			{
				if (cameFrom.find(edge->getDestination()) == cameFrom.end())
					cameFrom.insert(std::make_pair(edge->getDestination(), nextClosestVertex.VERTEX));
				else
					cameFrom[edge->getDestination()] = nextClosestVertex.VERTEX;

				g_Costs[edge->getDestination()] = g_score;
				f_Costs[edge->getDestination()] = g_Costs[edge->getDestination()] + instance.estimatedDistance(*graph.getVertex(edge->getDestination()), *graph.getVertex(target));

				if (std::find_if(openList.begin(), openList.end(), [&edge](const FCostContainer &arg) { return arg.VERTEX->getKey() == edge->getDestination(); }) == openList.end())
				{
					openList.insert({ f_Costs[edge->getDestination()], g_Costs[edge->getDestination()], *graph.getVertex(edge->getDestination()) });
				}

			}
		}
	}

	return path;
}
