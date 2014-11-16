#pragma once

#include <string>
#include <vector>

class Graph;
class Vertex;
class Edge;

class AStarSearch
{
public:
	static std::vector<Vertex*> getShortestPath(const Graph &graph, const std::string &source, const std::string &target);
private:
	static AStarSearch &instance() {
		static AStarSearch _instance;
		return _instance;
	}
	AStarSearch();
	virtual ~AStarSearch();
	void clear();

	std::vector<std::string> _GCosts;
	std::vector<std::string> _FCosts;

	std::vector<const Edge*> _ShortestPathTree;
	std::vector<const Edge*> _SearchFrontier;

	std::string _Source = "";
	std::string _Target = "";
	
};

