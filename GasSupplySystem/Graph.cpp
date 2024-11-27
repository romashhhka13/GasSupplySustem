#include "Graph.h"

using namespace std;

bool Graph::isDAG()
{
	std::vector<bool> visited(num_V, false);
	std::vector<bool> recursion_stack(num_V, false);

	for (int i = 0; i < num_V; ++i) {
		if (!visited[i] && hasCycleUtil(i, visited, recursion_stack)) {
			return false;  // Граф содержит цикл
		}
	}

	return true;  // Граф ацикличен
}

vector<int> Graph::TopologicalSorting()
{
	vector<int> sorted_vertexes;
	vector<bool> visited(num_V, false);
	stack<int> result_dfs;

	for (int vertex = 0; vertex < num_V; vertex++) {
		if (!visited[vertex])
			DFS(visited, vertex, result_dfs);
	}

	vector<int> stations(cs_ids.size());
	for (auto& [id_cs, i] : cs_ids)
		stations[i] = id_cs;

	while (!result_dfs.empty()) {
		sorted_vertexes.push_back(stations[result_dfs.top()]);
		result_dfs.pop();
	}

	return sorted_vertexes;
}

unordered_map<int, double> Graph::Dijkstra(int start_vertex)
{
	int curr = cs_ids[start_vertex];

	vector<bool> visited(num_V, false);
	vector<double> distances(num_V, DBL_MAX);
	distances[curr] = 0;
	visited[curr];

	while (count(visited.begin(), visited.end(), false) != 0)
	{
		for (auto& vertex : GetNeighboringVertexes(curr)) {
			if (!visited[vertex])
				distances[vertex] = Min(distances[vertex], distances[curr] +
				weights_matrix[curr][vertex]);
		}

		double min_dist = DBL_MAX;
		for (int vertex = 0; vertex < num_V; vertex++) {
			if (!visited[vertex]) {
				if (distances[vertex] <= min_dist) {
					min_dist = distances[vertex];
					curr = vertex;
				}
			}
		}

		visited[curr] = true;
	}

	unordered_map<int, double> result;
	for (auto& [id_cs, i] : cs_ids) {
		result.insert({id_cs, distances[i]});
	}

	return result;
}

double Graph::FordFulkerson(int source, int sink)
{
	source = cs_ids[source];
	sink = cs_ids[sink];

	// Создаем резервную матрицу для хранения остаточных пропускных способностей
	vector<vector<double>> r_matrix = cap_matrix;

	vector<int> parent(num_V, -1); // Заполняется с помощью обхода в ширину и хранит пути
	int max_flow = 0;

	while (true) {
		// Поиск пути от источника к стоку с использованием BFS
		parent.assign(num_V, -1);
		queue<pair<int, double>> q;
		q.push({ source, DBL_MAX });
		parent[source] = source;

		while (!q.empty()) {
			int u = q.front().first;
			double path_flow = q.front().second;
			q.pop();

			for (int v = 0; v < num_V; v++) {
				if (parent[v] == -1 && r_matrix[u][v] > 0) {
					// Найден непосещенный узел с ненулевой пропускной способностью в резервной матрице
					parent[v] = u;
					int min_capacity = Min(path_flow, r_matrix[u][v]);
					if (v == sink) {
						// Если достигнут сток, обновляем пропускные способности на пути
						while (v != source) {
							u = parent[v];
							r_matrix[u][v] -= min_capacity;
							r_matrix[v][u] += min_capacity;
							v = u;
						}
						max_flow += min_capacity;
						break;
					}
					q.push({ v, min_capacity });
				}
			}
		}
		// Если BFS не может найти путь, завершаем цикл
		if (parent[sink] == -1)
			break;
	}
	return max_flow;
}

Graph::Graph(unordered_map<int, Station>& cs_objects,
	unordered_map<int, Pipe>& pipe_objects,
	unordered_map<int, Edge>& connections)
{
	num_V = cs_objects.size();
	adj_matrix.resize(num_V, (vector<int>(num_V, 0)));
	weights_matrix.resize(num_V, (vector<double>(num_V, 0.0)));
	cap_matrix.resize(num_V, (vector<double>(num_V, 0.0)));

	int i = 0;
	for (auto& [id, cs] : cs_objects)
		cs_ids.insert({ id, i++});


	for (auto& [id_pipe, edge] : connections) {

		adj_matrix[cs_ids.at(edge.id_out)][cs_ids.at(edge.id_in)] = 1;

		weights_matrix[cs_ids.at(edge.id_out)][cs_ids.at(edge.id_in)]
			= pipe_objects.at(id_pipe).GetTransportationCost();;
		weights_matrix[cs_ids.at(edge.id_in)][cs_ids.at(edge.id_out)]
			= DBL_MAX;

		cap_matrix[cs_ids.at(edge.id_out)][cs_ids.at(edge.id_in)] =
			pipe_objects.at(id_pipe).GetCapacity();
	}

}

unordered_set<int> Graph::GetNeighboringVertexes(int vertex) const
{
	unordered_set<int> neighb_vert;
	int neighbor = 0;
	for (auto& adjacency : adj_matrix[vertex]) {
		if (adjacency)
			neighb_vert.insert(neighbor);
		neighbor++;
	}

	return neighb_vert;
}

void Graph::DFS(vector<bool>& visited,
	int vertex, stack<int>& result)
{
	visited[vertex] = true;
	int neighbor = 0;
	for (int adjacency : adj_matrix[vertex]) {
		if (!visited[neighbor] && adjacency == 1)
			DFS(visited, neighbor, result);
		neighbor++;
	}

	result.push(vertex);
}

bool Graph::hasCycleUtil(int vertex, vector<bool>& visited,
	vector<bool>& recursion_stack)
{
	visited[vertex] = true;
	recursion_stack[vertex] = true;

	for (int neighbor = 0; neighbor < num_V; ++neighbor) {
		if (adj_matrix[vertex][neighbor] && !visited[neighbor]) {
			if (hasCycleUtil(neighbor, visited, recursion_stack)) {
				return true;  // Обнаружен цикл
			}
		}
		else if (adj_matrix[vertex][neighbor] && recursion_stack[neighbor]) {
			return true;  // Обратное ребро, обнаружен цикл
		}
	}

	recursion_stack[vertex] = false;
	return false;
}