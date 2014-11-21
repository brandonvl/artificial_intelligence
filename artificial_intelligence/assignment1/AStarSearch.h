#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

class Graph;
class Vertex;
class Edge;

class AStarSearch
{
public:
	static std::vector<Vertex*> getShortestPath(Graph &graph, const int &source, const int &target);
private:
	struct FCostContainer
	{
		FCostContainer(double totalDistance, double distanceToSource, Vertex &vertex)
		{
			TOTALDISTANCE = totalDistance;
			DISTANCETOSOURCE = distanceToSource;
			VERTEX = &vertex;
			
		}

		double TOTALDISTANCE;
		double DISTANCETOSOURCE;
		Vertex *VERTEX;
		bool operator<(const FCostContainer &container) const;
	};

	double estimatedDistance(Vertex &from, Vertex &to);
	std::vector<Vertex*> reconstructPath(std::map<int, Vertex*> &cameFrom, const int &current);



	static AStarSearch &instance() {
		static AStarSearch _instance;
		return _instance;
	}
	AStarSearch();
	virtual ~AStarSearch();
	void clear();	
};

