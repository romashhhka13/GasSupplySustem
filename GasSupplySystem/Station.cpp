#include "Station.h"
#include "Addition.h"

using namespace std;

std::istream& operator>>(std::istream& in, Station& cs)
{
	cout << "Title: ";
	cs.title = EnterLine();

	cout << "Number of all workshops (1 - 25): ";
	cs.all_workshop = GetCorrectNumber(1, 25);

	cout << "Number of active workshops (0 - " << cs.all_workshop <<"): ";
	cs.active_workshop = GetCorrectNumber(0, cs.all_workshop);

	cout << "Efficiency (0.0 - 1.0): ";
	cs.efficiency = GetCorrectNumber(0.0, 1.0);

	return in;
}

std::ostream& operator<<(std::ostream& out, const Station& cs)
{
	char symbol = 249;
	out << "Information about CS "
		<< "\"" << cs.title << "\":\n"
		<< symbol << "ID: " << cs.id << "\n"
		<< symbol << "Title: " << cs.title << "\n"
		<< symbol << "All workshops: " << cs.all_workshop << "\n"
		<< symbol << "Active workshops: " << cs.active_workshop << "\n"
		<< symbol << "Efficiency: " << cs.efficiency * 100 << " %" << "\n\n";

	return out;
}

std::ifstream& operator>>(std::ifstream& fin, Station& cs)
{
	fin >> cs.id;
	fin >> ws;
	getline(fin, cs.title);
	fin >> cs.all_workshop;
	fin >> cs.active_workshop;
	fin >> cs.efficiency;
	int id = cs.id;
	cs.max_id = cs.max_id <= id ? cs.max_id = ++id : cs.max_id;
	return fin;
}

std::ofstream& operator<<(std::ofstream& fout, const Station& cs)
{
	fout << cs.id << "\n"
		<< cs.title << "\n"
		<< cs.all_workshop << "\n"
		<< cs.active_workshop << "\n"
		<< cs.efficiency << "\n";
	return fout;
}


void Station::IncreaseActiveWS()
{
	if (active_workshop < all_workshop)
		++active_workshop;
}

void Station::DecreaseActiveWS()
{
	if (active_workshop > 0)
		--active_workshop;
}

void Station::ResetMaxID()
{
	max_id = 1;
}


double Station::GetPercentUnused() const
{
	return (1 - ((double)active_workshop/double(all_workshop))) * 100;
}


std::string Station::GetTitle() const
{
	return title;
}


int Station::GetId() const
{
	return id;
}

int Station::max_id = 1;


Station::Station()
{
	id = max_id++;
}
