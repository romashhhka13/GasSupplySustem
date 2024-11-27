#pragma once
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <stack>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pipe.h"
#include "Station.h"
#include "Addition.h"
#include "Graph.h"

class Graph;

struct Edge
{
	int id_out;
	int id_in;
	Edge(int out, int in){
		id_out = out;
		id_in = in;
	}
};

class GasSupplySystem
{	
public:
	// Добавлление труб и станций
	void AddPipe();
	Pipe AddPipe(int diameter);
	void AddCS();

	// Просмотр труб, станций и связей
	void ShowPipes();
	void ShowCS();
	void ShortShowPipes();
	void ShortShowCS();
	void ShowFoundPipes(std::unordered_set<int>& id_pipes);
	void ShowFoundCS(std::unordered_set<int>& id_cs);
	void ShowConnections();

	// Сохранение в файл, загрузка из файла, очищение системы
	void Save(std::string filename);
	void Load(std::string filename);
	void ClearSystem();

	// Поиск труб по нужным параметрам
	std::unordered_set<int> SearchPipesByKmMark(std::string km_mark);
	std::unordered_set<int> SearchPipesByStatus(int status);
	std::unordered_set<int> SearchFreePipesByDiameters(int diameter);
	std::unordered_set<int> SearchPipesByIDs();

	// Редактирование труб
	void EditOnePipe(int id_pipe);
	void ChangeStatusToOpposite(std::unordered_set<int>& id_pipes);
	void ChangeStatusToRepair(std::unordered_set<int>& id_pipes);
	void ChangeStatusToWork(std::unordered_set<int>& id_pipes);
	void EditAllPipes();

	// Поиск станций по нужным параметрам
	std::unordered_set<int> SearchCSByTitle(std::string title);
	std::unordered_set<int> SearchCSByWorkshops(double percent);
	std::unordered_set<int> SearchCSByIDs();

	// Редактирование станций
	void EditOneCS(int id_cs);
	void EditCSPackage(std::unordered_set<int>& id_cs, int action);
	void EditAllCS(int action);

	// Функции удаления
	void DeletePipe(int id_pipe);
	void DeleteCS(int id_cs);
	void DeleteConnection(int id_pipe);

	// Работа с газотранспортной сетью
	void ConnectStations(int id_out, int id_in, int id_pipe);
	Graph InitGraph();
	std::vector<int> TopologicalSorting();
	std::unordered_map<int, double> ShortestDistance(int id_cs);

	// Проверка на наличие объектов
	bool IsPipeObjectsEmpty();
	bool IsCSObjectsEmpty();
	bool PipeExist(int id_pipe);
	bool CSExist(int id_cs);
	bool IsPipeConnected(int id_object);
	bool IsCSConnected(int id_cs);

private:
	std::unordered_map<int, Pipe> pipe_objects;
	std::unordered_map<int, Station> cs_objects;
	std::unordered_map<int, Edge> connections;
};

