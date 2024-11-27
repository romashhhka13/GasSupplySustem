#include "MainMenu.h"

using namespace std;

void MenuShowObjects(GasSupplySystem& gss)
{
	vector<string> menu = { "Show pipes", "Show stations", "Show connections", "Show all" };
	const string menu_information[3] =
	{ "-----------------------------------------------\n"
	"\tINFORMATION ABOUT ALL PIPES\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tINFORMATION ABOUT ALL CS\n"
	"-----------------------------------------------\n\n",
	"-----------------------------------------------\n"
	"\tINFORMATION ABOUT CONNECTIONS\n"
	"-----------------------------------------------\n\n" };
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << menu_information[0];
		gss.ShowPipes();
		break;
	}
	case 2:
	{
		cout << menu_information[1];
		gss.ShowCS();
		break;
	}
	case 3:
	{
		cout << menu_information[2];
		gss.ShowConnections();
		break;
	}
	case 4:
	{
		cout << menu_information[0];
		gss.ShowPipes();
		cout << menu_information[1];
		gss.ShowCS();
		cout << menu_information[2];
		gss.ShowConnections();
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void MenuSave(GasSupplySystem& gss)
{
	cout << "Enter the file name: ";
	gss.Save(EnterLine());
}

void MenuLoad(GasSupplySystem& gss) 
{
	cout << "Enter the file name: ";
	gss.Load(EnterLine());
}

int EnterPipesID()
{
	cout << "Enter ID of pipe: ";
	return GetCorrectNumber(1, INT_MAX);
}

bool FoundPipesExist(GasSupplySystem& gss, unordered_set<int> found_pipes)
{
	if (ObjectsExist(found_pipes)) {
		gss.ShowFoundPipes(found_pipes);
		return true;
	}
	else {
		cout << "Pipes are not found!\n";
		return false;
	}
}

void MenuChangeStatusToOpposite(GasSupplySystem& gss, unordered_set<int>& id_pipes)
{
	cout << "Change status (\"1\" - yes, \"0\" - no)?: ";
	if (GetCorrectNumber(0, 1))
		gss.ChangeStatusToOpposite(id_pipes);
}

void MenuEditPipeSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_pipes, bool for_status)
{
	if (!for_status) {
		vector<string> menu = {
		"Change the status to the opposite",
		"Change the status to the \"In repair\"",
		"Change the status to the \"In working condition\"" };
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.ChangeStatusToOpposite(id_pipes);
			break;
		}
		case 2:
		{
			gss.ChangeStatusToRepair(id_pipes);
			break;
		}
		case 3:
		{
			gss.ChangeStatusToWork(id_pipes);
			break;
		}
		default:
			break;
		}
	}
	else
		MenuChangeStatusToOpposite(gss, id_pipes);
}

void MenuSelectionPipesByIDs(GasSupplySystem& gss,
	unordered_set<int>& id_pipes, bool for_status)
{
	cout << "Select pipes (\"1\" - yes, \"0\" - no)?: ";
	if (GetCorrectNumber(0, 1)) {
		unordered_set<int> found_pipes = SelectByIDs(id_pipes);
		if (FoundPipesExist(gss, found_pipes))
			if (found_pipes.size() > 1)
				MenuEditPipeSubpackage(gss, found_pipes, for_status);
			else
				MenuChangeStatusToOpposite(gss, found_pipes);
	}
	else
		MenuEditPipeSubpackage(gss, id_pipes, for_status);
}

void MenuEditPipePackage(GasSupplySystem& gss)
{
	unordered_set<int> found_pipes;
	bool for_status = false;
	bool with_select = true;
	vector<string> menu = {
		"Search by kilometer mark", "Search by status",
		"Select pipes"};
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Enter the Kilometer Mark: ";
		found_pipes = gss.SearchPipesByKmMark(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Enter the status (\"1\"-in repair, \"0\"-in working condition): ";
		found_pipes = gss.SearchPipesByStatus(GetCorrectNumber(0, 1));
		for_status = true;
		break;
	}
	case 3:
	{
		found_pipes = gss.SearchPipesByIDs();
		with_select = false;
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}

	if (FoundPipesExist(gss, found_pipes)){
		if (with_select && found_pipes.size() > 1)
			MenuSelectionPipesByIDs(gss, found_pipes, for_status);
		else
			MenuChangeStatusToOpposite(gss, found_pipes);
	}
		
}

void MenuEditPipes(GasSupplySystem& gss)
{
	if (!gss.IsPipeObjectsEmpty()){
		vector<string> menu = { "Edit one pipe",
			"Edit pipe package", "Edit all pipes"};
		gss.ShortShowPipes();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.EditOnePipe(EnterPipesID());
			break;
		}
		case 2:
		{
			MenuEditPipePackage(gss);
			break;
		}
		case 3:
		{
			gss.EditAllPipes();
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}
	}
}

int EnterStationsID()
{
	cout << "Enter ID of station: ";
	return GetCorrectNumber(0, INT_MAX);
}

bool FoundCSExist(GasSupplySystem& gss, unordered_set<int> found_stations)
{
	if (ObjectsExist(found_stations)) {
		gss.ShowFoundCS(found_stations);
		return true;
	}
	else {
		cout << "Stations are not found!\n";
		return false;
	}
}

void MenuEditCSSubpackage(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "\"1\" - Increase,\"0\" - Decrease: ";
	gss.EditCSPackage(id_stations, GetCorrectNumber(0, 1));
}

void MenuSelectionCSByIDs(GasSupplySystem& gss,
	unordered_set<int>& id_stations)
{
	cout << "Select stations (\"1\" - yes, \"0\" - no)?: ";
	if (GetCorrectNumber(0, 1)) {
		unordered_set<int> found_stations = SelectByIDs(id_stations);
		if (FoundCSExist(gss, found_stations))
			MenuEditCSSubpackage(gss, found_stations);
	}
	else
		MenuEditCSSubpackage(gss, id_stations);
}

void MenuEditCSPackage(GasSupplySystem& gss)
{
	unordered_set<int> found_stations;
	vector<string> menu = {
		"Search by title", "Search by percent of unused workshops",
		"Select stations" };
	bool with_select = true;
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		cout << "Enter the title: ";
		found_stations = gss.SearchCSByTitle(EnterLine());
		break;
	}
	case 2:
	{
		cout << "Enter the percent of unused workshops: ";
		found_stations = gss.SearchCSByWorkshops(GetCorrectNumber(0.0, 100.0));
		break;
	}
	case 3:
	{
		found_stations = gss.SearchCSByIDs();
		with_select = false;
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}

	if (FoundCSExist(gss, found_stations)) {
		if (with_select && found_stations.size() > 1)
			MenuSelectionCSByIDs(gss, found_stations);

		else
			MenuEditCSSubpackage(gss, found_stations);
	}

}

void MenuEditCS(GasSupplySystem& gss)
{
	if (!gss.IsCSObjectsEmpty()) {
		vector<string> menu = { "Edit one station",
			"Edit station package", "Edit all stations" };
		gss.ShortShowCS();
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			gss.EditOneCS(EnterStationsID());
			break;
		}
		case 2:
		{
			MenuEditCSPackage(gss);
			break;
		}
		case 3:
		{

			cout << "\"1\" - Increase,\"0\" - Decrease: ";
			gss.EditAllCS(GetCorrectNumber(0, 1));
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}
	}
}

void MenuDeletePipe(GasSupplySystem& gss)
{
	if (!gss.IsPipeObjectsEmpty()) {
		int id_pipe = EnterPipesID();
		if (gss.IsPipeConnected(id_pipe)) {
			cout << "The pipe is part of the graph.\n"
				<< "Do you want to delete? (\"1\" - yes, \"0\" - no): ";
			if (GetCorrectNumber(0, 1))
				gss.DeletePipe(id_pipe);
		}
		else
			gss.DeletePipe(id_pipe);
	}
}

void MenuDeleteCS(GasSupplySystem& gss)
{
	if (!gss.IsCSObjectsEmpty()) {
		int id_cs = EnterStationsID();
		if (gss.IsCSConnected(id_cs)) {
			cout << "The station is part of the graph.\n"
				<< "Do you want to delete? (\"1\" - yes, \"0\" - no): ";
			if (GetCorrectNumber(0, 1))
				gss.DeleteCS(id_cs);
		}
		else
			gss.DeleteCS(id_cs);
	}
}

void MenuDelete(GasSupplySystem& gss)
{
	vector<string> menu = { "Delete pipe", "Delete station", "Delete connection"};
	switch (ChooseActionMenu(menu, true))
	{
	case 1:
	{
		MenuDeletePipe(gss);
		break;
	}
	case 2:
	{
		MenuDeleteCS(gss);
		break;
	}
	case 3:
	{
		gss.DeleteConnection(EnterPipesID());
		break;
	}
	case 0:
	{
		break;
	}
	default:
		break;
	}
}

void EnteringIDs(int& id_out, int& id_in)
{
	cout << "Enter id first station: ";
	id_out = GetCorrectNumber(1, INT_MAX);
	cout << "Enter id second station: ";
	id_in = GetCorrectNumber(1, INT_MAX);

	while (id_out == id_in) {
		cout << "IDs match! Enter IDs again\n";
		cout << "Enter id first station: ";
		id_out = GetCorrectNumber(1, INT_MAX);
		cout << "Enter id second station: ";
		id_in = GetCorrectNumber(1, INT_MAX);
	}
}

void MenuConnectStations(GasSupplySystem& gss)
{
	gss.ShortShowPipes();
	gss.ShortShowCS();
	gss.ShowConnections();
	int id_out;
	int id_in;
	EnteringIDs(id_out, id_in);

	if (gss.CSExist(id_in) && gss.CSExist(id_out)) {
		int diameter = Pipe::EnterCorrectDiameter();
		unordered_set<int> found_pipes = gss.SearchFreePipesByDiameters(diameter);

		if (ObjectsExist(found_pipes)) {
			gss.ShowFoundPipes(found_pipes);
			int id_pipe = EnterPipesID();
			if (found_pipes.contains(id_pipe))
				gss.ConnectStations(id_out, id_in, id_pipe);
			else
				cout << "Pipe with this id is not in the found pipes!\n";
		}
		else {
			cout << "There are no free pipes with this diameter!\n" <<
				"Want to create (\"1\" - yes, \"0\" - no)?: ";
			if (GetCorrectNumber(0, 1)) {
				Pipe p = gss.AddPipe(diameter);
				gss.ConnectStations(id_out, id_in, p.GetId());
			}

		}
	}
}

void MenuTopologicalSorting(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	if (graph.isDAG()) {
		vector<int> result = graph.TopologicalSorting();
		cout << "TOPOLOGICAL SORTING: ";
		for (auto& id_cs : result)
			cout << id_cs << " ";
		cout << "\n";
	}
	else 
		cout << "Topological sorting is not possible. There are cycles!\n";
}

void OutputDistance(unordered_map<int, double>& distances, int id_second_cs)
{
	if (distances.at(id_second_cs) == DBL_MAX)
		cout << "no way\n";
	else
		cout << distances.at(id_second_cs) << "\n";
}

void MenuShortestDistance(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	cout << "Enter the id station you want to search from: ";
	int id_first_cs = GetCorrectNumber(1, INT_MAX);
	if (gss.IsCSConnected(id_first_cs)) {
		unordered_map<int, double> found_distances = graph.Dijkstra(id_first_cs);
		cout << "Distance to one station or for all? (\"1\" - one, \"0\" - all): ";
		if (GetCorrectNumber(0, 1)) {
			int id_second_cs = EnterStationsID();
			if (gss.IsCSConnected(id_second_cs)) {
				cout << "Distance to the station " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);
			}
		}
		else {
			for (auto& [id_second_cs, dist] : found_distances) {
				cout << "Distance to the station " << id_second_cs
					<< ": ";
				OutputDistance(found_distances, id_second_cs);
			}
		}

	}
	else
		cout << "Station not in graph!\n";
}

void MenuMaxFlow(GasSupplySystem& gss)
{
	Graph graph = gss.InitGraph();
	int id_out, id_in;
	EnteringIDs(id_out, id_in);
	if (gss.IsCSConnected(id_out) && gss.IsPipeConnected(id_in))
	{
		cout << "Maximum flow from station " << id_out << " to "
			<< "station " << id_in << ": " << graph.FordFulkerson(id_out, id_in) << "\n";
	}
}

void MenuNetwork(GasSupplySystem& gss)
{
	vector<string> menu = { "Connect stations", "Topological sorting",
	"Shortest distance", "Max Flow"};
	if (!gss.IsCSObjectsEmpty() && !gss.IsPipeObjectsEmpty()) {
		switch (ChooseActionMenu(menu, true))
		{
		case 1:
		{
			MenuConnectStations(gss);
			break;
		}
		case 2:
		{
			MenuTopologicalSorting(gss);
			break;
		}
		case 3:
		{
			MenuShortestDistance(gss);
			break;
		}
		case 4:
		{
			MenuMaxFlow(gss);
			break;
		}
		case 0:
		{
			break;
		}
		default:
			break;
		}
	}
}

