#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


class Pipe
{
public:
	bool status;

	static int EnterCorrectDiameter();

	std::string PrintStatus() const;
	void ChangeStatus();
	static void ResetMaxID();

	std::string GetKmMark() const;
	int GetDiameter() const;
	double GetTransportationCost() const;
	double GetCapacity() const;
	int GetId() const;

	void SetDiameter(int d);

	Pipe();

	void InitPipe(int diam = 0);
	//friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);

	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);
	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);

private:
	static int max_id;
	std::string km_mark;
	float length;
	static int pipe_diameters[];
	int diameter;
	int id;
};

