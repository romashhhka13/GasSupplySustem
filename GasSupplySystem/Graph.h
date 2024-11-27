#pragma once
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <map>
#include <stack>
#include "Addition.h"
#include "Station.h"
#include "Pipe.h"
#include "GasSupplySystem.h"

class Station;
class Pipe;
struct Edge;

class Graph
{
public:
	bool isDAG();
	std::vector<int> TopologicalSorting();
	std::unordered_map<int, double> Dijkstra(int start_vertex);
	double FordFulkerson(int source, int sink);

	Graph(std::unordered_map<int, Station>& cs_objects,
		std::unordered_map<int, Pipe>& pipe_objects,
		std::unordered_map<int, Edge>& connections);
private:
	std::unordered_set<int> GetNeighboringVertexes(int vertex) const;
	void DFS(std::vector<bool>& visited, int vertex, std::stack<int>& result);
	bool hasCycleUtil(int vertex, std::vector<bool>& visited,
		std::vector<bool>& recursion_stack);

	std::vector<std::vector<int>> adj_matrix;
	std::vector<std::vector<double>> weights_matrix;
	std::vector<std::vector<double>> cap_matrix;
	std::unordered_map<int, int> cs_ids;
	int num_V;
};

