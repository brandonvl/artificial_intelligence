#pragma once

#include <string>
#include <vector>

class Graph;
class Vertex;
class Edge;

class AStarSearch
{
public:
	static std::vector<Vertex*> getShortestPath(const Graph &graph, const int &source, const int &target);
private:
	static AStarSearch &instance() {
		static AStarSearch _instance;
		return _instance;
	}
	AStarSearch();
	virtual ~AStarSearch();
	void clear();
	bool operator()(const int &left, const int &right);

	Graph *_graph;

	std::vector<double> _GCosts;
	std::vector<double> _FCosts;

	std::vector<const Edge*> _ShortestPathTree;
	std::vector<const Edge*> _SearchFrontier;

	std::string _Source = "";
	std::string _Target = "";
	
};

