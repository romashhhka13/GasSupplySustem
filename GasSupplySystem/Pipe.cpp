#include "Pipe.h"
#include "Addition.h"

using namespace std;

int Pipe::max_id = 1;
int Pipe::pipe_diameters[] = {500, 700, 1000, 1400};

int Pipe::EnterCorrectDiameter()
{
	cout << "Diameter (500, 700, 1000, 1400 mm): ";
	int diameter = GetCorrectNumber(1, INT_MAX);
	while (!count(begin(pipe_diameters), end(pipe_diameters), diameter)) {
		cout << "Enter the correct diameter (500, 700, 1000, 1400 mm): ";
		diameter = GetCorrectNumber(1, INT_MAX);
	}
	return diameter;
}

string Pipe::PrintStatus() const
{
	return status ? "In repair" : "In Working condition";

}

void Pipe::ChangeStatus()
{
	status = !status;
}

void Pipe::ResetMaxID()
{
	max_id = 1;
}

std::string Pipe::GetKmMark() const
{
	return km_mark;
}

int Pipe::GetDiameter() const
{
	return diameter;
}

double Pipe::GetTransportationCost() const
{
	return status ? DBL_MAX : length;
}

double Pipe::GetCapacity() const
{
	return status ? 0 : length;
}

int Pipe::GetId() const
{
	return id;
}

void Pipe::SetDiameter(int d)
{
	diameter = d;
}

Pipe::Pipe()
{
	id = max_id++;
}

void Pipe::InitPipe(int diam)
{
	cout << "Kilometer mark: ";
	km_mark = EnterLine();

	cout << "Length (0.1 - 5000 km): ";
	length = GetCorrectNumber(0.1, 5000.0);

	if (!diam)
		diameter = EnterCorrectDiameter();
	else
		diameter = diam;

	cout << "Status (\"1\" - in repair, \"0\" - in working condition): ";
	status = GetCorrectNumber(0, 1);
}

ostream& operator<<(ostream& out, const Pipe& p)
{
	char symbol = 249; // marker
	out << "Information about Pipe " <<
		"\"" << p.km_mark << "\":\n"
		<< symbol << " ID: " << p.id << "\n"
		<< symbol << " Kilometer mark: " << p.km_mark << "\n"
		<< symbol << " Length: " << p.length << " km" << "\n"
		<< symbol << " Diameter: " << p.diameter << " mm" << "\n"
		<< symbol << " " << p.PrintStatus() << "\n\n";

	return out;
}

ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> p.id;
	fin >> ws;
	getline(fin, p.km_mark);
	fin >> p.length;
	fin >> p.diameter;
	fin >> p.status;
	int id = p.id;
	p.max_id = p.max_id <= id ? p.max_id = ++id : p.max_id;
	return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p)
{
	fout << p.id << "\n"
		<< p.km_mark << "\n"
		<< p.length << "\n"
		<< p.diameter << "\n"
		<< p.status << "\n";
	return fout;
}